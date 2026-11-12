#include "../Headers/repositorios.hpp"
#include "../Headers/banco_dados.hpp"
#include <sqlite3.h>
#include <limits>
#include <stdexcept>

/**
 * @file repositorios.cpp
 * @brief Persistência dos contêineres em tabelas relacionais SQLite.
 *
 * BancoDados::getConexao() deve fornecer uma conexão sqlite3* já aberta.
 * A criação das tabelas e a ativação de PRAGMA foreign_keys = ON pertencem
 * a BancoDados. O esquema esperado por este arquivo é:
 * - pessoas(email, nome, senha, papel);
 * - projetos(identificador, nome, descricao, inicio, termino, email_gestor);
 * - quadros(identificador, nome, limite, id_projeto);
 * - cartoes(identificador, nome, descricao, prioridade, estado, tamanho,
 *           entrada, inicio, termino, id_quadro, email_desenvolvedor).
 *
 * As chaves primárias são email e identificador, respectivamente. Os vínculos
 * usam chaves estrangeiras com exclusão restrita, sem remoção em cascata.
 * As tabelas devem manter o rowid do SQLite: as listagens o utilizam para
 * preservar a ordem de inserção dos antigos vetores. As colunas são TEXT,
 * exceto limite (INTEGER); inicio e termino dos cartões admitem NULL.
 *
 * Operações de escrita retornam false quando não encontram o registro ou
 * violam uma restrição de integridade. Falhas de acesso ou execução do SQL
 * lançam std::runtime_error. As regras de negócio continuam nas controladoras.
 */

namespace {

/**
 * @brief Prepara e libera automaticamente um comando SQL parametrizado.
 *
 * A conexão é emprestada; somente o comando pertence a este objeto.
 * O destrutor libera o comando inclusive quando uma operação lança exceção.
 */
class ComandoSQL {
private:
    sqlite3* conexao;
    sqlite3_stmt* comando;

    void verificar(int resultado, const char* operacao) const {
        if (resultado != SQLITE_OK)
            throw std::runtime_error(std::string(operacao) + ": " +
                                     sqlite3_errmsg(conexao));
    }

public:
    /** @brief Prepara o SQL usando a conexão recebida, sem executá-lo. */
    ComandoSQL(sqlite3* conexaoBanco, const char* sql)
        : conexao(conexaoBanco), comando(0) {
        if (conexao == 0)
            throw std::runtime_error("Conexao com o banco de dados indisponivel.");

        // Em caso de erro, sqlite3_prepare_v2 deixa comando nulo.
        verificar(sqlite3_prepare_v2(conexao, sql, -1, &comando, 0),
                  "Erro ao preparar comando SQL");
    }

    /** @brief Libera o comando preparado, sem fechar a conexão compartilhada. */
    ~ComandoSQL() {
        sqlite3_finalize(comando);
    }

    ComandoSQL(const ComandoSQL&) = delete;
    ComandoSQL& operator=(const ComandoSQL&) = delete;

    /** @brief Associa uma cópia do texto a um parâmetro, numerado a partir de 1. */
    void vincularTexto(int indice, const std::string& valor) {
        if (valor.size() > static_cast<std::size_t>(std::numeric_limits<int>::max()))
            throw std::runtime_error("Texto excede o tamanho aceito pelo SQLite.");

        verificar(sqlite3_bind_text(comando, indice, valor.c_str(),
                                    static_cast<int>(valor.size()), SQLITE_TRANSIENT),
                  "Erro ao vincular texto ao comando SQL");
    }

    /** @brief Associa um inteiro a um parâmetro, numerado a partir de 1. */
    void vincularInteiro(int indice, int valor) {
        verificar(sqlite3_bind_int(comando, indice, valor),
                  "Erro ao vincular inteiro ao comando SQL");
    }

    /** @brief Armazena NULL para um instante ainda não definido no cartão. */
    void vincularInstanteOpcional(int indice, const std::string& valor) {
        if (valor.empty()) {
            verificar(sqlite3_bind_null(comando, indice),
                      "Erro ao vincular instante nulo ao comando SQL");
        } else {
            vincularTexto(indice, valor);
        }
    }

    /** @brief Avança uma consulta; retorna false somente ao terminar as linhas. */
    bool proximaLinha() {
        const int resultado = sqlite3_step(comando);
        if (resultado == SQLITE_ROW) return true;
        if (resultado == SQLITE_DONE) return false;
        verificar(resultado, "Erro ao consultar o banco de dados");
        return false;
    }

    /** @brief Executa uma escrita; retorna false se ausente ou impedida por restrição. */
    bool executarAlteracao() {
        const int resultado = sqlite3_step(comando);
        // Os oito bits inferiores também identificam códigos de erro estendidos.
        if ((resultado & 0xFF) == SQLITE_CONSTRAINT) return false;
        if (resultado != SQLITE_DONE)
            verificar(resultado, "Erro ao alterar o banco de dados");
        return sqlite3_changes(conexao) > 0;
    }

    /** @brief Lê uma coluna textual da linha atual; NULL é representado por "". */
    std::string texto(int coluna) const {
        const unsigned char* valor = sqlite3_column_text(comando, coluna);
        if (valor == 0) {
            if (sqlite3_column_type(comando, coluna) != SQLITE_NULL)
                throw std::runtime_error("Erro ao ler texto do banco de dados.");
            return std::string();
        }
        return std::string(reinterpret_cast<const char*>(valor),
                           static_cast<std::size_t>(sqlite3_column_bytes(comando, coluna)));
    }

    /** @brief Lê uma coluna inteira da linha atual, numerada a partir de 0. */
    int inteiro(int coluna) const {
        return sqlite3_column_int(comando, coluna);
    }
};

// Os textos são sempre parâmetros; nenhum dado recebido é concatenado ao SQL.
bool existeRegistro(sqlite3* conexao, const char* sql, const std::string& chave) {
    ComandoSQL comando(conexao, sql);
    comando.vincularTexto(1, chave);
    return comando.proximaLinha();
}

std::vector<std::string> listarValores(ComandoSQL& comando) {
    std::vector<std::string> resultado;
    while (comando.proximaLinha())
        resultado.push_back(comando.texto(0));
    return resultado;
}

// Ambas as consultas de cartões usam esta mesma ordem explícita de colunas.
CartaoDeAtividade lerCartao(const ComandoSQL& comando) {
    CartaoDeAtividade cartao;
    cartao.setIdentificador(comando.texto(0));
    cartao.setNome(comando.texto(1));
    cartao.setDescricao(comando.texto(2));
    cartao.setPrioridade(comando.texto(3));
    cartao.setEstado(comando.texto(4));
    cartao.setTamanho(comando.texto(5));
    cartao.setEntrada(comando.texto(6));

    // Timestamp não aceita vazio no setter. Uma entidade nova já representa
    // corretamente os instantes ainda não definidos com strings vazias.
    const std::string inicio = comando.texto(7);
    const std::string termino = comando.texto(8);
    if (!inicio.empty()) cartao.setInicio(inicio);
    if (!termino.empty()) cartao.setTermino(termino);
    return cartao;
}

} // namespace

// -----------------------------------------------------------------------------
// Pessoas
// -----------------------------------------------------------------------------

bool ContainerPessoas::inserir(const Pessoa& pessoa) {
    ComandoSQL comando(banco.getConexao(),
        "INSERT INTO pessoas (email, nome, senha, papel) VALUES (?, ?, ?, ?)");
    comando.vincularTexto(1, pessoa.getEmail());
    comando.vincularTexto(2, pessoa.getNome());
    comando.vincularTexto(3, pessoa.getSenha());
    comando.vincularTexto(4, pessoa.getPapel());
    return comando.executarAlteracao();
}

bool ContainerPessoas::obter(const std::string& email, Pessoa& pessoa) const {
    ComandoSQL comando(banco.getConexao(),
        "SELECT email, nome, senha, papel FROM pessoas WHERE email = ?");
    comando.vincularTexto(1, email);
    if (!comando.proximaLinha()) return false;

    Pessoa encontrada;
    encontrada.setEmail(comando.texto(0));
    encontrada.setNome(comando.texto(1));
    encontrada.setSenha(comando.texto(2));
    encontrada.setPapel(comando.texto(3));
    pessoa = encontrada;
    return true;
}

bool ContainerPessoas::substituir(const std::string& email, const Pessoa& pessoa) {
    if (email != pessoa.getEmail()) return false; // preserva a chave primária
    ComandoSQL comando(banco.getConexao(),
        "UPDATE pessoas SET nome = ?, senha = ?, papel = ? WHERE email = ?");
    comando.vincularTexto(1, pessoa.getNome());
    comando.vincularTexto(2, pessoa.getSenha());
    comando.vincularTexto(3, pessoa.getPapel());
    comando.vincularTexto(4, email);
    return comando.executarAlteracao();
}

bool ContainerPessoas::remover(const std::string& email) {
    ComandoSQL comando(banco.getConexao(), "DELETE FROM pessoas WHERE email = ?");
    comando.vincularTexto(1, email);
    return comando.executarAlteracao();
}

bool ContainerPessoas::existe(const std::string& email) const {
    return existeRegistro(banco.getConexao(),
        "SELECT 1 FROM pessoas WHERE email = ? LIMIT 1", email);
}

std::vector<std::string> ContainerPessoas::listarEmails() const {
    ComandoSQL comando(banco.getConexao(), "SELECT email FROM pessoas ORDER BY rowid");
    return listarValores(comando);
}

// -----------------------------------------------------------------------------
// Projetos
// -----------------------------------------------------------------------------

bool ContainerProjetos::inserir(const Projeto& projeto, const std::string& emailGestor) {
    ComandoSQL comando(banco.getConexao(),
        "INSERT INTO projetos (identificador, nome, descricao, inicio, termino, email_gestor) "
        "VALUES (?, ?, ?, ?, ?, ?)");
    comando.vincularTexto(1, projeto.getIdentificador());
    comando.vincularTexto(2, projeto.getNome());
    comando.vincularTexto(3, projeto.getDescricao());
    comando.vincularTexto(4, projeto.getInicio());
    comando.vincularTexto(5, projeto.getTermino());
    comando.vincularTexto(6, emailGestor);
    return comando.executarAlteracao();
}

bool ContainerProjetos::obter(const std::string& id, Projeto& projeto,
                               std::string* emailGestor) const {
    ComandoSQL comando(banco.getConexao(),
        "SELECT identificador, nome, descricao, inicio, termino, email_gestor "
        "FROM projetos WHERE identificador = ?");
    comando.vincularTexto(1, id);
    if (!comando.proximaLinha()) return false;

    Projeto encontrado;
    encontrado.setIdentificador(comando.texto(0));
    encontrado.setNome(comando.texto(1));
    encontrado.setDescricao(comando.texto(2));
    encontrado.setInicio(comando.texto(3));
    encontrado.setTermino(comando.texto(4));
    const std::string gestor = comando.texto(5);
    projeto = encontrado;
    if (emailGestor != 0) *emailGestor = gestor;
    return true;
}

bool ContainerProjetos::substituir(const std::string& id, const Projeto& projeto) {
    if (id != projeto.getIdentificador()) return false;
    // O gestor e a chave primária são preservados pelo UPDATE.
    ComandoSQL comando(banco.getConexao(),
        "UPDATE projetos SET nome = ?, descricao = ?, inicio = ?, termino = ? "
        "WHERE identificador = ?");
    comando.vincularTexto(1, projeto.getNome());
    comando.vincularTexto(2, projeto.getDescricao());
    comando.vincularTexto(3, projeto.getInicio());
    comando.vincularTexto(4, projeto.getTermino());
    comando.vincularTexto(5, id);
    return comando.executarAlteracao();
}

bool ContainerProjetos::remover(const std::string& id) {
    ComandoSQL comando(banco.getConexao(), "DELETE FROM projetos WHERE identificador = ?");
    comando.vincularTexto(1, id);
    return comando.executarAlteracao();
}

bool ContainerProjetos::existe(const std::string& id) const {
    return existeRegistro(banco.getConexao(),
        "SELECT 1 FROM projetos WHERE identificador = ? LIMIT 1", id);
}

bool ContainerProjetos::gestorDoProjeto(const std::string& id, std::string& emailGestor) const {
    ComandoSQL comando(banco.getConexao(),
        "SELECT email_gestor FROM projetos WHERE identificador = ?");
    comando.vincularTexto(1, id);
    if (!comando.proximaLinha()) return false;
    emailGestor = comando.texto(0);
    return true;
}

bool ContainerProjetos::temProjetoGerenciadoPor(const std::string& emailGestor) const {
    return existeRegistro(banco.getConexao(),
        "SELECT 1 FROM projetos WHERE email_gestor = ? LIMIT 1", emailGestor);
}

std::vector<std::string> ContainerProjetos::listarIds() const {
    ComandoSQL comando(banco.getConexao(),
        "SELECT identificador FROM projetos ORDER BY rowid");
    return listarValores(comando);
}

// -----------------------------------------------------------------------------
// Quadros
// -----------------------------------------------------------------------------

bool ContainerQuadros::inserir(const Quadro& quadro, const std::string& idProjeto) {
    ComandoSQL comando(banco.getConexao(),
        "INSERT INTO quadros (identificador, nome, limite, id_projeto) VALUES (?, ?, ?, ?)");
    comando.vincularTexto(1, quadro.getIdentificador());
    comando.vincularTexto(2, quadro.getNome());
    comando.vincularInteiro(3, quadro.getLimite());
    comando.vincularTexto(4, idProjeto);
    return comando.executarAlteracao();
}

bool ContainerQuadros::obter(const std::string& id, Quadro& quadro,
                              std::string* idProjeto) const {
    ComandoSQL comando(banco.getConexao(),
        "SELECT identificador, nome, limite, id_projeto FROM quadros WHERE identificador = ?");
    comando.vincularTexto(1, id);
    if (!comando.proximaLinha()) return false;

    Quadro encontrado;
    encontrado.setIdentificador(comando.texto(0));
    encontrado.setNome(comando.texto(1));
    encontrado.setLimite(comando.inteiro(2));
    const std::string projeto = comando.texto(3);
    quadro = encontrado;
    if (idProjeto != 0) *idProjeto = projeto;
    return true;
}

bool ContainerQuadros::substituir(const std::string& id, const Quadro& quadro) {
    if (id != quadro.getIdentificador()) return false;
    // Somente os dados do quadro são alterados; o vínculo com o projeto permanece.
    ComandoSQL comando(banco.getConexao(),
        "UPDATE quadros SET nome = ?, limite = ? WHERE identificador = ?");
    comando.vincularTexto(1, quadro.getNome());
    comando.vincularInteiro(2, quadro.getLimite());
    comando.vincularTexto(3, id);
    return comando.executarAlteracao();
}

bool ContainerQuadros::remover(const std::string& id) {
    ComandoSQL comando(banco.getConexao(), "DELETE FROM quadros WHERE identificador = ?");
    comando.vincularTexto(1, id);
    return comando.executarAlteracao();
}

bool ContainerQuadros::existe(const std::string& id) const {
    return existeRegistro(banco.getConexao(),
        "SELECT 1 FROM quadros WHERE identificador = ? LIMIT 1", id);
}

bool ContainerQuadros::projetoDoQuadro(const std::string& id, std::string& idProjeto) const {
    ComandoSQL comando(banco.getConexao(),
        "SELECT id_projeto FROM quadros WHERE identificador = ?");
    comando.vincularTexto(1, id);
    if (!comando.proximaLinha()) return false;
    idProjeto = comando.texto(0);
    return true;
}

bool ContainerQuadros::temQuadroDoProjeto(const std::string& idProjeto) const {
    return existeRegistro(banco.getConexao(),
        "SELECT 1 FROM quadros WHERE id_projeto = ? LIMIT 1", idProjeto);
}

std::vector<std::string> ContainerQuadros::listarIds() const {
    ComandoSQL comando(banco.getConexao(),
        "SELECT identificador FROM quadros ORDER BY rowid");
    return listarValores(comando);
}

std::vector<std::string> ContainerQuadros::listarIdsDoProjeto(const std::string& idProjeto) const {
    ComandoSQL comando(banco.getConexao(),
        "SELECT identificador FROM quadros WHERE id_projeto = ? ORDER BY rowid");
    comando.vincularTexto(1, idProjeto);
    return listarValores(comando);
}

// -----------------------------------------------------------------------------
// Cartões
// -----------------------------------------------------------------------------

bool ContainerCartoes::inserir(const CartaoDeAtividade& cartao,
                               const std::string& idQuadro,
                               const std::string& emailDesenvolvedor) {
    ComandoSQL comando(banco.getConexao(),
        "INSERT INTO cartoes (identificador, nome, descricao, prioridade, estado, tamanho, "
        "entrada, inicio, termino, id_quadro, email_desenvolvedor) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    comando.vincularTexto(1, cartao.getIdentificador());
    comando.vincularTexto(2, cartao.getNome());
    comando.vincularTexto(3, cartao.getDescricao());
    comando.vincularTexto(4, cartao.getPrioridade());
    comando.vincularTexto(5, cartao.getEstado());
    comando.vincularTexto(6, cartao.getTamanho());
    comando.vincularTexto(7, cartao.getEntrada());
    comando.vincularInstanteOpcional(8, cartao.getInicio());
    comando.vincularInstanteOpcional(9, cartao.getTermino());
    comando.vincularTexto(10, idQuadro);
    comando.vincularTexto(11, emailDesenvolvedor);
    return comando.executarAlteracao();
}

bool ContainerCartoes::obter(const std::string& id, CartaoDeAtividade& cartao,
                              std::string* idQuadro,
                              std::string* emailDesenvolvedor) const {
    ComandoSQL comando(banco.getConexao(),
        "SELECT identificador, nome, descricao, prioridade, estado, tamanho, entrada, "
        "inicio, termino, id_quadro, email_desenvolvedor FROM cartoes WHERE identificador = ?");
    comando.vincularTexto(1, id);
    if (!comando.proximaLinha()) return false;

    const CartaoDeAtividade encontrado = lerCartao(comando);
    const std::string quadro = comando.texto(9);
    const std::string desenvolvedor = comando.texto(10);
    cartao = encontrado;
    if (idQuadro != 0) *idQuadro = quadro;
    if (emailDesenvolvedor != 0) *emailDesenvolvedor = desenvolvedor;
    return true;
}

bool ContainerCartoes::substituir(const std::string& id, const CartaoDeAtividade& cartao) {
    if (id != cartao.getIdentificador()) return false;
    // Os vínculos quadro/desenvolvedor não são alterados nesta operação.
    ComandoSQL comando(banco.getConexao(),
        "UPDATE cartoes SET nome = ?, descricao = ?, prioridade = ?, estado = ?, tamanho = ?, "
        "entrada = ?, inicio = ?, termino = ? WHERE identificador = ?");
    comando.vincularTexto(1, cartao.getNome());
    comando.vincularTexto(2, cartao.getDescricao());
    comando.vincularTexto(3, cartao.getPrioridade());
    comando.vincularTexto(4, cartao.getEstado());
    comando.vincularTexto(5, cartao.getTamanho());
    comando.vincularTexto(6, cartao.getEntrada());
    comando.vincularInstanteOpcional(7, cartao.getInicio());
    comando.vincularInstanteOpcional(8, cartao.getTermino());
    comando.vincularTexto(9, id);
    return comando.executarAlteracao();
}

bool ContainerCartoes::remover(const std::string& id) {
    ComandoSQL comando(banco.getConexao(), "DELETE FROM cartoes WHERE identificador = ?");
    comando.vincularTexto(1, id);
    return comando.executarAlteracao();
}

bool ContainerCartoes::existe(const std::string& id) const {
    return existeRegistro(banco.getConexao(),
        "SELECT 1 FROM cartoes WHERE identificador = ? LIMIT 1", id);
}

bool ContainerCartoes::temCartaoNoQuadro(const std::string& idQuadro) const {
    return existeRegistro(banco.getConexao(),
        "SELECT 1 FROM cartoes WHERE id_quadro = ? LIMIT 1", idQuadro);
}

bool ContainerCartoes::temCartaoDoDesenvolvedor(const std::string& emailDesenvolvedor) const {
    return existeRegistro(banco.getConexao(),
        "SELECT 1 FROM cartoes WHERE email_desenvolvedor = ? LIMIT 1", emailDesenvolvedor);
}

std::vector<std::string> ContainerCartoes::listarIdsDoQuadro(const std::string& idQuadro) const {
    ComandoSQL comando(banco.getConexao(),
        "SELECT identificador FROM cartoes WHERE id_quadro = ? ORDER BY rowid");
    comando.vincularTexto(1, idQuadro);
    return listarValores(comando);
}

std::vector<CartaoDeAtividade> ContainerCartoes::listarCartoesDoQuadro(const std::string& idQuadro) const {
    ComandoSQL comando(banco.getConexao(),
        "SELECT identificador, nome, descricao, prioridade, estado, tamanho, entrada, "
        "inicio, termino FROM cartoes WHERE id_quadro = ? ORDER BY rowid");
    comando.vincularTexto(1, idQuadro);
    std::vector<CartaoDeAtividade> resultado;
    while (comando.proximaLinha())
        resultado.push_back(lerCartao(comando));
    return resultado;
}
