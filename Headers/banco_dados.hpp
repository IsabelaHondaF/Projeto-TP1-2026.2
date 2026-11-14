#ifndef BANCO_DADOS_HPP_INCLUDED
#define BANCO_DADOS_HPP_INCLUDED

#include <string>

// Declaração antecipada do tipo de conexão definido pela biblioteca SQLite.
struct sqlite3;

/**
 * @brief Gerencia a conexão com o banco de dados relacional SQLite do sistema.
 *
 * O objeto é responsável por abrir a conexão, ativar a integridade referencial,
 * criar as tabelas pessoas, projetos, quadros e cartoes quando ainda não
 * existirem e fechar a conexão ao ser destruído.
 *
 * Os contêineres compartilham a conexão por meio de referências a BancoDados.
 * O gerenciador deve ser criado antes dos contêineres e destruído depois deles.
 * As regras de negócio permanecem nas controladoras de serviço.
 *
 * @note Não permite cópia nem movimentação, evitando compartilhar a propriedade
 * da conexão ou invalidar as referências mantidas pelos contêineres.
 */
class BancoDados {
private:
    sqlite3* conexao = nullptr; /**< Conexão pertencente exclusivamente ao gerenciador. */

    /**
     * @brief Executa comandos internos de configuração e criação do esquema.
     * @param[in] sql Comando SQL interno, sem concatenação de dados de usuários.
     * @throws std::runtime_error Se o SQLite não conseguir executar o comando.
     */
    void executarSQL(const char* sql);

    /**
     * @brief Cria as tabelas e os índices necessários, preservando dados existentes.
     *
     * Define as chaves primárias e estrangeiras esperadas pelos repositórios,
     * com exclusão restrita dos registros referenciados. Mantém o rowid das
     * tabelas e permite NULL em inicio e termino dos cartões ainda não iniciados
     * ou concluídos, respectivamente.
     *
     * @throws std::runtime_error Se a criação do esquema falhar.
     */
    void criarTabelas();

public:
    /**
     * @brief Abre o banco de dados e prepara sua estrutura para os contêineres.
     * @param[in] caminhoArquivo Caminho do arquivo SQLite. O padrão é kanban.db,
     * relativo ao diretório de execução. Use ":memory:" para um banco temporário
     * e isolado durante os testes.
     * @throws std::runtime_error Se a abertura, configuração ou criação do
     * esquema falhar. Nesse caso, a conexão aberta é liberada.
     */
    explicit BancoDados(const std::string& caminhoArquivo = "kanban.db");

    /**
     * @brief Libera a conexão sem apagar o arquivo nem os dados persistidos.
     * @note Os contêineres e seus comandos SQL devem ter sido destruídos antes
     * do gerenciador. Este destrutor não lança exceções.
     */
    ~BancoDados() noexcept;

    /** @brief Impede copiar a propriedade da conexão. */
    BancoDados(const BancoDados&) = delete;

    /** @brief Impede atribuir a propriedade de outra conexão por cópia. */
    BancoDados& operator=(const BancoDados&) = delete;

    /** @brief Impede mover um gerenciador referenciado pelos contêineres. */
    BancoDados(BancoDados&&) = delete;

    /** @brief Impede substituir o gerenciador por atribuição de movimento. */
    BancoDados& operator=(BancoDados&&) = delete;

    /**
     * @brief Fornece acesso à conexão compartilhada pelos repositórios.
     * @return Ponteiro para a conexão SQLite aberta pelo gerenciador.
     * @note O ponteiro é emprestado: quem o recebe não deve fechar a conexão.
     * Ele permanece válido durante a vida deste objeto.
     */
    sqlite3* getConexao() const noexcept {
        return conexao;
    }
};

#endif // BANCO_DADOS_HPP_INCLUDED
