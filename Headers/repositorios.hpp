#ifndef REPOSITORIOS_HPP_INCLUDED
#define REPOSITORIOS_HPP_INCLUDED

#include "entidades.hpp"
#include <string>
#include <vector>

// Declaração antecipada do gerenciador da conexão SQLite.
class BancoDados;

/**
 * @brief Persistência em banco de dados relacional SQLite das pessoas cadastradas.
 *
 * O repositório cuida exclusivamente da persistência dos dados e da garantia de unicidade
 * da chave primária (email). Autenticação e regras de permissão pertencem às controladoras de serviço.
 */
class ContainerPessoas {
private:
    BancoDados& banco; /**< Referência ao gerenciador da conexão SQLite compartilhada. */

public:
    /**
     * @brief Inicializa o contêiner de pessoas com o banco de dados compartilhado.
     * @param[in] bancoDados Gerenciador da conexão SQLite utilizada pelo contêiner.
     * @note O banco deve permanecer válido durante toda a vida do contêiner.
     * O contêiner não abre nem fecha a conexão.
     */
    explicit ContainerPessoas(BancoDados& bancoDados) : banco(bancoDados) {}

    /**
     * @brief Insere uma nova pessoa no contêiner se o email não estiver cadastrado.
     * @param[in] pessoa Instância da entidade Pessoa a ser inserida.
     * @return true se a pessoa for inserida; false se o email já existir
     * ou se os dados violarem uma restrição de integridade do banco.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    bool inserir(const Pessoa& pessoa);

    /**
     * @brief Localiza e recupera uma pessoa cadastrada pelo email.
     * @param[in] email Chave primária da conta a ser consultada.
     * @param[out] pessoa Referência para retornar os dados encontrados.
     * @return true se o registro for encontrado; false se não existir.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     * @throws std::invalid_argument Se um valor armazenado não atender ao
     * formato exigido pelo domínio ao reconstruir a entidade.
     * @note Se o retorno for false, os parâmetros de saída permanecem inalterados.
     */
    bool obter(const std::string& email, Pessoa& pessoa) const;

    /**
     * @brief Substitui os dados de uma pessoa existente mantendo a chave primária.
     * @param[in] email Chave primária da pessoa a ser atualizada.
     * @param[in] pessoa Novos dados da pessoa.
     * @return true se os dados forem atualizados; false se a pessoa não existir,
     * se pessoa.getEmail() diferir de email ou se uma restrição de integridade
     * do banco impedir a atualização.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     * @note O email não é alterado. As permissões e as regras para mudança de papel
     * são verificadas pela controladora de serviço.
     */
    bool substituir(const std::string& email, const Pessoa& pessoa);

    /**
     * @brief Remove uma pessoa do contêiner a partir de seu email.
     * @param[in] email Chave primária da pessoa a ser excluída.
     * @return true se a pessoa for removida; false se ela não existir ou se uma
     * restrição de integridade impedir a remoção, inclusive quando a pessoa
     * for referenciada como gestora de projeto ou desenvolvedora de cartão.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    bool remover(const std::string& email);

    /**
     * @brief Verifica se existe uma conta cadastrada com o email fornecido.
     * @param[in] email Chave a ser verificada.
     * @return true se existir; false caso contrário.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    bool existe(const std::string& email) const;

    /**
     * @brief Retorna a lista contendo as chaves primárias (emails) de todas as pessoas.
     * @return Vetor com as strings dos emails cadastrados.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    std::vector<std::string> listarEmails() const;
};

/**
 * @brief Registro interno que vincula um projeto ao gestor responsável.
 */
struct RegistroProjeto {
    Projeto projeto;          /**< Dados da entidade Projeto */
    std::string emailGestor;  /**< Email do gestor que criou e administra o projeto */
};

/**
 * @brief Persistência em banco de dados relacional SQLite de projetos e seus respectivos gestores.
 */
class ContainerProjetos {
private:
    BancoDados& banco; /**< Referência ao gerenciador da conexão SQLite compartilhada. */

public:
    /**
     * @brief Inicializa o contêiner de projetos com o banco de dados compartilhado.
     * @param[in] bancoDados Gerenciador da conexão SQLite utilizada pelo contêiner.
     * @note O banco deve permanecer válido durante toda a vida do contêiner.
     * O contêiner não abre nem fecha a conexão.
     */
    explicit ContainerProjetos(BancoDados& bancoDados) : banco(bancoDados) {}

    /**
     * @brief Insere um novo projeto associado ao seu criador/gestor.
     * @param[in] projeto Dados da entidade Projeto.
     * @param[in] emailGestor Email da pessoa cadastrada como gestora.
     * @return true se o projeto for inserido; false se o identificador já existir,
     * se emailGestor não identificar uma pessoa cadastrada ou se outra
     * restrição de integridade do banco impedir a inserção.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     * @note A existência da pessoa é assegurada pela chave estrangeira. A verificação
     * de seu papel GESTOR e das permissões cabe à controladora de serviço.
     */
    bool inserir(const Projeto& projeto, const std::string& emailGestor);

    /**
     * @brief Recupera um projeto pelo identificador, opcionalmente retornando o gestor.
     * @param[in] id Identificador do projeto.
     * @param[out] projeto Recebe os dados do projeto.
     * @param[out] emailGestor Ponteiro opcional para receber o email do gestor.
     * @return true se o registro for encontrado; false se não existir.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     * @throws std::invalid_argument Se um valor armazenado não atender ao
     * formato exigido pelo domínio ao reconstruir a entidade.
     * @note Se o retorno for false, os parâmetros de saída permanecem inalterados.
     */
    bool obter(const std::string& id, Projeto& projeto,
               std::string* emailGestor = 0) const;

    /**
     * @brief Substitui os dados de um projeto existente.
     * @param[in] id Identificador do projeto a ser atualizado.
     * @param[in] projeto Novos dados do projeto.
     * @return true se os dados forem atualizados; false se o projeto não existir,
     * se projeto.getIdentificador() diferir de id ou se uma restrição de
     * integridade do banco impedir a atualização.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     * @note A chave primária e o vínculo com o gestor são preservados.
     */
    bool substituir(const std::string& id, const Projeto& projeto);

    /**
     * @brief Remove um projeto do contêiner.
     * @param[in] id Identificador do projeto a ser removido.
     * @return true se o projeto for removido; false se ele não existir ou se uma
     * restrição de integridade impedir a remoção, inclusive quando houver
     * quadros vinculados ao projeto.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    bool remover(const std::string& id);

    /**
     * @brief Verifica se um projeto existe.
     * @param[in] id Identificador do projeto.
     * @return true se existir; false caso contrário.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    bool existe(const std::string& id) const;

    /**
     * @brief Consulta o email do gestor de determinado projeto.
     * @param[in] id Identificador do projeto.
     * @param[out] emailGestor Referência para retornar o email do gestor.
     * @return true se encontrado; false caso o projeto não exista.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    bool gestorDoProjeto(const std::string& id, std::string& emailGestor) const;

    /**
     * @brief Verifica se determinado usuário gerencia pelo menos um projeto.
     * @param[in] emailGestor Email a ser verificado.
     * @return true se houver projeto gerenciado por esse email; false caso contrário.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    bool temProjetoGerenciadoPor(const std::string& emailGestor) const;

    /**
     * @brief Lista todos os identificadores de projetos cadastrados.
     * @return Vetor contendo os identificadores dos projetos.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    std::vector<std::string> listarIds() const;
};

/**
 * @brief Registro interno que vincula um quadro ao projeto pai.
 */
struct RegistroQuadro {
    Quadro quadro;          /**< Dados da entidade Quadro */
    std::string idProjeto;  /**< Identificador do projeto ao qual o quadro pertence */
};

/**
 * @brief Persistência em banco de dados relacional SQLite de quadros Kanban e seus vínculos com projetos.
 */
class ContainerQuadros {
private:
    BancoDados& banco; /**< Referência ao gerenciador da conexão SQLite compartilhada. */

public:
    /**
     * @brief Inicializa o contêiner de quadros com o banco de dados compartilhado.
     * @param[in] bancoDados Gerenciador da conexão SQLite utilizada pelo contêiner.
     * @note O banco deve permanecer válido durante toda a vida do contêiner.
     * O contêiner não abre nem fecha a conexão.
     */
    explicit ContainerQuadros(BancoDados& bancoDados) : banco(bancoDados) {}

    /**
     * @brief Insere um quadro vinculado a um projeto.
     * @param[in] quadro Dados da entidade Quadro.
     * @param[in] idProjeto Identificador do projeto proprietário.
     * @return true se o quadro for inserido; false se o identificador já existir,
     * se idProjeto não identificar um projeto cadastrado ou se outra
     * restrição de integridade do banco impedir a inserção.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    bool inserir(const Quadro& quadro, const std::string& idProjeto);

    /**
     * @brief Recupera um quadro pelo seu identificador.
     * @param[in] id Identificador do quadro.
     * @param[out] quadro Recebe os dados do quadro.
     * @param[out] idProjeto Ponteiro opcional para receber o identificador do projeto.
     * @return true se o registro for encontrado; false se não existir.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     * @throws std::invalid_argument Se um valor armazenado não atender ao
     * formato exigido pelo domínio ao reconstruir a entidade.
     * @note Se o retorno for false, os parâmetros de saída permanecem inalterados.
     */
    bool obter(const std::string& id, Quadro& quadro,
               std::string* idProjeto = 0) const;

    /**
     * @brief Atualiza os dados de um quadro mantendo seus vínculos.
     * @param[in] id Identificador do quadro.
     * @param[in] quadro Novos dados do quadro.
     * @return true se os dados forem atualizados; false se o quadro não existir,
     * se quadro.getIdentificador() diferir de id ou se uma restrição de
     * integridade do banco impedir a atualização.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     * @note A chave primária e o vínculo com o projeto são preservados. A comparação
     * do limite com o WIP atual cabe à controladora de serviço.
     */
    bool substituir(const std::string& id, const Quadro& quadro);

    /**
     * @brief Remove um quadro pelo identificador.
     * @param[in] id Identificador do quadro.
     * @return true se o quadro for removido; false se ele não existir ou se uma
     * restrição de integridade impedir a remoção, inclusive quando houver
     * cartões vinculados ao quadro.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    bool remover(const std::string& id);

    /**
     * @brief Verifica se um quadro existe no contêiner.
     * @param[in] id Identificador do quadro.
     * @return true se existir; false caso contrário.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    bool existe(const std::string& id) const;

    /**
     * @brief Consulta o identificador do projeto proprietário do quadro.
     * @param[in] id Identificador do quadro.
     * @param[out] idProjeto Recebe o código do projeto.
     * @return true se o quadro existir; false caso contrário.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    bool projetoDoQuadro(const std::string& id, std::string& idProjeto) const;

    /**
     * @brief Verifica se existem quadros vinculados a determinado projeto.
     * @param[in] idProjeto Identificador do projeto.
     * @return true se houver ao menos um quadro no projeto; false caso contrário.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    bool temQuadroDoProjeto(const std::string& idProjeto) const;

    /**
     * @brief Lista todos os identificadores de quadros cadastrados.
     * @return Vetor de identificadores.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    std::vector<std::string> listarIds() const;

    /**
     * @brief Lista os identificadores dos quadros vinculados a um projeto.
     * @param[in] idProjeto Identificador do projeto a consultar.
     * @return Vetor com os identificadores encontrados; vazio se não houver vínculos.
     * @note A existência do projeto é verificada pela controladora de serviço.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    std::vector<std::string> listarIdsDoProjeto(const std::string& idProjeto) const;
};

/**
 * @brief Registro interno que vincula um cartão ao quadro e ao desenvolvedor responsável.
 */
struct RegistroCartao {
    CartaoDeAtividade cartao;          /**< Dados da entidade CartaoDeAtividade */
    std::string idQuadro;              /**< Identificador do quadro ao qual pertence */
    std::string emailDesenvolvedor;    /**< Email do desenvolvedor responsável */
};

/**
 * @brief Persistência em banco de dados relacional SQLite de cartões de atividade e seus vínculos.
 */
class ContainerCartoes {
private:
    BancoDados& banco; /**< Referência ao gerenciador da conexão SQLite compartilhada. */

public:
    /**
     * @brief Inicializa o contêiner de cartões com o banco de dados compartilhado.
     * @param[in] bancoDados Gerenciador da conexão SQLite utilizada pelo contêiner.
     * @note O banco deve permanecer válido durante toda a vida do contêiner.
     * O contêiner não abre nem fecha a conexão.
     */
    explicit ContainerCartoes(BancoDados& bancoDados) : banco(bancoDados) {}

    /**
     * @brief Insere um cartão com seus relacionamentos de quadro e responsável.
     * @param[in] cartao Dados da entidade CartaoDeAtividade.
     * @param[in] idQuadro Identificador do quadro Kanban.
     * @param[in] emailDesenvolvedor Email do desenvolvedor atribuído.
     * @return true se o cartão for inserido; false se o identificador já existir,
     * se o quadro ou a pessoa responsável não estiverem cadastrados ou se
     * outra restrição de integridade do banco impedir a inserção.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     * @note A verificação do papel DESENVOLVEDOR, das permissões e do estado inicial
     * do cartão cabe à controladora de serviço.
     */
    bool inserir(const CartaoDeAtividade& cartao, const std::string& idQuadro,
                 const std::string& emailDesenvolvedor);

    /**
     * @brief Recupera um cartão de atividade e opcionalmente seus vínculos.
     * @param[in] id Identificador do cartão.
     * @param[out] cartao Recebe os dados do cartão.
     * @param[out] idQuadro Ponteiro opcional para receber o id do quadro.
     * @param[out] emailDesenvolvedor Ponteiro opcional para receber o email do desenvolvedor.
     * @return true se o registro for encontrado; false se não existir.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     * @throws std::invalid_argument Se um valor armazenado não atender ao
     * formato exigido pelo domínio ao reconstruir a entidade.
     * @note Se o retorno for false, os parâmetros de saída permanecem inalterados.
     */
    bool obter(const std::string& id, CartaoDeAtividade& cartao,
               std::string* idQuadro = 0,
               std::string* emailDesenvolvedor = 0) const;

    /**
     * @brief Atualiza os dados de um cartão existente.
     * @param[in] id Identificador do cartão.
     * @param[in] cartao Novos dados do cartão.
     * @return true se os dados forem atualizados; false se o cartão não existir,
     * se cartao.getIdentificador() diferir de id ou se uma restrição de
     * integridade do banco impedir a atualização.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     * @note A chave primária e os vínculos com quadro e desenvolvedor são preservados.
     * As regras de movimentação, timestamps e WIP cabem à controladora de serviço.
     */
    bool substituir(const std::string& id, const CartaoDeAtividade& cartao);

    /**
     * @brief Remove um cartão de atividade.
     * @param[in] id Identificador do cartão a ser excluído.
     * @return true se o cartão for removido; false se ele não existir ou se uma
     * restrição de integridade do banco impedir a remoção.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    bool remover(const std::string& id);

    /**
     * @brief Verifica se um cartão existe no contêiner.
     * @param[in] id Identificador do cartão.
     * @return true se existir; false caso contrário.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    bool existe(const std::string& id) const;

    /**
     * @brief Verifica se determinado quadro possui algum cartão cadastrado.
     * @param[in] idQuadro Identificador do quadro.
     * @return true se houver cartões; false caso o quadro esteja vazio.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    bool temCartaoNoQuadro(const std::string& idQuadro) const;

    /**
     * @brief Verifica se determinado desenvolvedor possui algum cartão sob sua responsabilidade.
     * @param[in] emailDesenvolvedor Email do desenvolvedor.
     * @return true se houver ao menos um cartão; false caso contrário.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    bool temCartaoDoDesenvolvedor(const std::string& emailDesenvolvedor) const;

    /**
     * @brief Lista os identificadores de todos os cartões vinculados a um quadro.
     * @param[in] idQuadro Identificador do quadro.
     * @return Vetor de identificadores dos cartões.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     */
    std::vector<std::string> listarIdsDoQuadro(const std::string& idQuadro) const;

    /**
     * @brief Retorna cópias de todas as entidades cartão de um determinado quadro.
     * @param[in] idQuadro Identificador do quadro.
     * @return Vetor contendo as instâncias de CartaoDeAtividade.
     * @throws std::runtime_error Se ocorrer falha ao acessar o banco ou
     * preparar, vincular parâmetros, executar ou ler o comando SQL.
     * @throws std::invalid_argument Se um valor armazenado não atender ao
     * formato exigido pelo domínio ao reconstruir a entidade.
     */
    std::vector<CartaoDeAtividade> listarCartoesDoQuadro(const std::string& idQuadro) const;
};

#endif // REPOSITORIOS_HPP_INCLUDED
