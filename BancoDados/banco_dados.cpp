#include "../Headers/banco_dados.hpp"
#include <sqlite3.h>
#include <stdexcept>

/**
 * @file banco_dados.cpp
 * @brief Abertura, configuração e fechamento do banco relacional SQLite.
 *
 * As tabelas seguem as colunas utilizadas pelos repositórios. A inicialização
 * preserva os registros de um banco já existente e cria apenas as tabelas e
 * os índices ausentes. Validações de domínio, permissões, movimentações e
 * cálculos de métricas continuam nas respectivas classes do sistema.
 */

BancoDados::BancoDados(const std::string& caminhoArquivo) {
    // Um caminho vazio criaria um banco temporário no SQLite. Um NUL interno
    // truncaria o caminho recebido pela API. Nenhum dos casos é um arquivo válido
    // para esta classe; bancos temporários de teste usam explicitamente :memory:.
    if (caminhoArquivo.empty() || caminhoArquivo.find('\0') != std::string::npos)
        throw std::runtime_error("Caminho do banco de dados invalido.");

    try {
        const int resultado = sqlite3_open_v2(
            caminhoArquivo.c_str(), &conexao,
            SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);

        if (resultado != SQLITE_OK) {
            const char* motivo = conexao != nullptr
                ? sqlite3_errmsg(conexao) : "Memoria insuficiente para abrir a conexao.";
            throw std::runtime_error(std::string("Erro ao abrir o banco de dados: ") + motivo);
        }

        // SQLite pode abrir um arquivo protegido apenas para leitura.
        // O sistema precisa de escrita para cadastrar e atualizar os registros.
        if (sqlite3_db_readonly(conexao, "main") != 0)
            throw std::runtime_error("O banco de dados nao permite leitura e escrita.");

        // Aguarda até cinco segundos por bloqueios temporários de outra conexão.
        if (sqlite3_busy_timeout(conexao, 5000) != SQLITE_OK)
            throw std::runtime_error(std::string("Erro ao configurar o banco de dados: ") +
                                     sqlite3_errmsg(conexao));

        // A verificação de chaves estrangeiras é habilitada por conexão e deve
        // ocorrer antes da transação que cria as tabelas.
        executarSQL("PRAGMA foreign_keys = ON;");

        sqlite3_stmt* consulta = nullptr;
        if (sqlite3_prepare_v2(conexao, "PRAGMA foreign_keys;", -1,
                               &consulta, nullptr) != SQLITE_OK)
            throw std::runtime_error(std::string("Erro ao verificar as chaves estrangeiras: ") +
                                     sqlite3_errmsg(conexao));

        const bool chavesAtivas = sqlite3_step(consulta) == SQLITE_ROW &&
                                  sqlite3_column_int(consulta, 0) == 1;
        const int finalizacao = sqlite3_finalize(consulta);
        if (!chavesAtivas || finalizacao != SQLITE_OK)
            throw std::runtime_error("Nao foi possivel ativar a integridade referencial do banco.");

        criarTabelas();
    } catch (...) {
        // O destrutor não é chamado quando o construtor falha. Libera também
        // uma conexão parcialmente aberta, preservando a exceção original.
        sqlite3_close_v2(conexao);
        conexao = nullptr;
        throw;
    }
}

BancoDados::~BancoDados() noexcept {
    // Os repositórios liberam seus comandos antes do gerenciador. close_v2
    // também permite concluir a liberação se houver algum comando pendente.
    sqlite3_close_v2(conexao);
    conexao = nullptr;
}

void BancoDados::executarSQL(const char* sql) {
    // A mensagem é obtida da própria conexão; não há buffer de erro alocado
    // por sqlite3_exec para ser liberado pelo chamador.
    if (sqlite3_exec(conexao, sql, nullptr, nullptr, nullptr) != SQLITE_OK)
        throw std::runtime_error(std::string("Erro ao executar comando SQL: ") +
                                 sqlite3_errmsg(conexao));
}

void BancoDados::criarTabelas() {
    // A criação é atômica: uma falha não deixa um esquema parcialmente criado.
    executarSQL("BEGIN IMMEDIATE;");
    try {
        executarSQL(
            "CREATE TABLE IF NOT EXISTS pessoas ("
            "    email TEXT NOT NULL PRIMARY KEY,"
            "    nome TEXT NOT NULL,"
            "    senha TEXT NOT NULL,"
            "    papel TEXT NOT NULL CHECK (papel IN ('GESTOR', 'DESENVOLVEDOR'))"
            ");"
        );

        executarSQL(
            "CREATE TABLE IF NOT EXISTS projetos ("
            "    identificador TEXT NOT NULL PRIMARY KEY,"
            "    nome TEXT NOT NULL,"
            "    descricao TEXT NOT NULL,"
            "    inicio TEXT NOT NULL,"
            "    termino TEXT NOT NULL,"
            "    email_gestor TEXT NOT NULL,"
            "    FOREIGN KEY (email_gestor) REFERENCES pessoas(email)"
            "        ON UPDATE RESTRICT ON DELETE RESTRICT"
            ");"
        );

        executarSQL(
            "CREATE TABLE IF NOT EXISTS quadros ("
            "    identificador TEXT NOT NULL PRIMARY KEY,"
            "    nome TEXT NOT NULL,"
            "    limite INTEGER NOT NULL CHECK (limite BETWEEN 1 AND 25),"
            "    id_projeto TEXT NOT NULL,"
            "    FOREIGN KEY (id_projeto) REFERENCES projetos(identificador)"
            "        ON UPDATE RESTRICT ON DELETE RESTRICT"
            ");"
        );

        executarSQL(
            "CREATE TABLE IF NOT EXISTS cartoes ("
            "    identificador TEXT NOT NULL PRIMARY KEY,"
            "    nome TEXT NOT NULL,"
            "    descricao TEXT NOT NULL,"
            "    prioridade TEXT NOT NULL CHECK (prioridade IN ('ALTA', 'MEDIA', 'BAIXA')),"
            "    estado TEXT NOT NULL CHECK (estado IN ('A FAZER', 'FAZENDO', 'FEITO')),"
            "    tamanho TEXT NOT NULL CHECK (tamanho IN ('GRANDE', 'MEDIO', 'PEQUENO')),"
            "    entrada TEXT NOT NULL,"
            "    inicio TEXT,"
            "    termino TEXT,"
            "    id_quadro TEXT NOT NULL,"
            "    email_desenvolvedor TEXT NOT NULL,"
            "    FOREIGN KEY (id_quadro) REFERENCES quadros(identificador)"
            "        ON UPDATE RESTRICT ON DELETE RESTRICT,"
            "    FOREIGN KEY (email_desenvolvedor) REFERENCES pessoas(email)"
            "        ON UPDATE RESTRICT ON DELETE RESTRICT"
            ");"
        );

        // As chaves primárias já possuem índices. Estes índices adicionais
        // atendem às consultas de vínculos e às verificações de integridade.
        executarSQL(
            "CREATE INDEX IF NOT EXISTS idx_projetos_gestor ON projetos(email_gestor);"
            "CREATE INDEX IF NOT EXISTS idx_quadros_projeto ON quadros(id_projeto);"
            "CREATE INDEX IF NOT EXISTS idx_cartoes_quadro ON cartoes(id_quadro);"
            "CREATE INDEX IF NOT EXISTS idx_cartoes_dev ON cartoes(email_desenvolvedor);"
        );

        // As tabelas mantêm o rowid, utilizado pelos repositórios para listar
        // os registros na ordem de inserção. Não se utiliza WITHOUT ROWID.
        executarSQL("COMMIT;");
    } catch (...) {
        // O rollback não pode substituir a exceção que causou a falha.
        sqlite3_exec(conexao, "ROLLBACK;", nullptr, nullptr, nullptr);
        throw;
    }
}
