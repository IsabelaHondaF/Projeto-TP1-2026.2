#ifndef REPOSITORIOS_HPP_INCLUDED
#define REPOSITORIOS_HPP_INCLUDED

#include "entidades.hpp"
#include <string>
#include <vector>

/**
 * @brief Armazenamento em memória das pessoas cadastradas.
 *
 * O repositório cuida exclusivamente da persistência em memória e da garantia de unicidade
 * da chave primária (email). Autenticação e regras de permissão pertencem às controladoras de serviço.
 */
class ContainerPessoas {
private:
    std::vector<Pessoa> pessoas;

public:
    /**
     * @brief Insere uma nova pessoa no contêiner se o email não estiver cadastrado.
     * @param[in] pessoa Instância da entidade Pessoa a ser inserida.
     * @return true se a inserção for concluída; false se já existir registro com mesmo email.
     */
    bool inserir(const Pessoa& pessoa);

    /**
     * @brief Localiza e recupera uma pessoa cadastrada pelo email.
     * @param[in] email Chave primária da conta a ser consultada.
     * @param[out] pessoa Referência para retornar os dados encontrados.
     * @return true se encontrada; false caso contrário.
     */
    bool obter(const std::string& email, Pessoa& pessoa) const;

    /**
     * @brief Substitui os dados de uma pessoa existente mantendo a chave primária.
     * @param[in] email Chave primária da pessoa a ser atualizada.
     * @param[in] pessoa Novos dados da pessoa.
     * @return true se a substituição for realizada; false se não existir.
     */
    bool substituir(const std::string& email, const Pessoa& pessoa);

    /**
     * @brief Remove uma pessoa do contêiner a partir de seu email.
     * @param[in] email Chave primária da pessoa a ser excluída.
     * @return true se removida; false se não for encontrada.
     */
    bool remover(const std::string& email);

    /**
     * @brief Verifica se existe uma conta cadastrada com o email fornecido.
     * @param[in] email Chave a ser verificada.
     * @return true se existir; false caso contrário.
     */
    bool existe(const std::string& email) const;

    /**
     * @brief Retorna a lista contendo as chaves primárias (emails) de todas as pessoas.
     * @return Vetor com as strings dos emails cadastrados.
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
 * @brief Armazenamento em memória de projetos e seus respectivos gestores.
 */
class ContainerProjetos {
private:
    std::vector<RegistroProjeto> projetos;

public:
    /**
     * @brief Insere um novo projeto associado ao seu criador/gestor.
     * @param[in] projeto Dados da entidade Projeto.
     * @param[in] emailGestor Email da pessoa cadastrada como gestora.
     * @return true se inserido com sucesso; false se o identificador já existir.
     */
    bool inserir(const Projeto& projeto, const std::string& emailGestor);

    /**
     * @brief Recupera um projeto pelo identificador, opcionalmente retornando o gestor.
     * @param[in] id Identificador do projeto.
     * @param[out] projeto Recebe os dados do projeto.
     * @param[out] emailGestor Ponteiro opcional para receber o email do gestor.
     * @return true se o projeto for encontrado; false caso contrário.
     */
    bool obter(const std::string& id, Projeto& projeto,
               std::string* emailGestor = 0) const;

    /**
     * @brief Substitui os dados de um projeto existente.
     * @param[in] id Identificador do projeto a ser atualizado.
     * @param[in] projeto Novos dados do projeto.
     * @return true se atualizado; false se não existir.
     */
    bool substituir(const std::string& id, const Projeto& projeto);

    /**
     * @brief Remove um projeto do contêiner.
     * @param[in] id Identificador do projeto a ser removido.
     * @return true se removido; false se inexistente.
     */
    bool remover(const std::string& id);

    /**
     * @brief Verifica se um projeto existe.
     * @param[in] id Identificador do projeto.
     * @return true se existir; false caso contrário.
     */
    bool existe(const std::string& id) const;

    /**
     * @brief Consulta o email do gestor de determinado projeto.
     * @param[in] id Identificador do projeto.
     * @param[out] emailGestor Referência para retornar o email do gestor.
     * @return true se encontrado; false caso o projeto não exista.
     */
    bool gestorDoProjeto(const std::string& id, std::string& emailGestor) const;

    /**
     * @brief Verifica se determinado usuário gerencia pelo menos um projeto.
     * @param[in] emailGestor Email a ser verificado.
     * @return true se houver projeto gerenciado por esse email; false caso contrário.
     */
    bool temProjetoGerenciadoPor(const std::string& emailGestor) const;

    /**
     * @brief Lista todos os identificadores de projetos cadastrados.
     * @return Vetor contendo os identificadores dos projetos.
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
 * @brief Armazenamento em memória de quadros Kanban e seus vínculos com projetos.
 */
class ContainerQuadros {
private:
    std::vector<RegistroQuadro> quadros;

public:
    /**
     * @brief Insere um quadro vinculado a um projeto.
     * @param[in] quadro Dados da entidade Quadro.
     * @param[in] idProjeto Identificador do projeto proprietário.
     * @return true se inserido; false se o identificador já existir.
     */
    bool inserir(const Quadro& quadro, const std::string& idProjeto);

    /**
     * @brief Recupera um quadro pelo seu identificador.
     * @param[in] id Identificador do quadro.
     * @param[out] quadro Recebe os dados do quadro.
     * @param[out] idProjeto Ponteiro opcional para receber o identificador do projeto.
     * @return true se encontrado; false caso contrário.
     */
    bool obter(const std::string& id, Quadro& quadro,
               std::string* idProjeto = 0) const;

    /**
     * @brief Atualiza os dados de um quadro mantendo seus vínculos.
     * @param[in] id Identificador do quadro.
     * @param[in] quadro Novos dados do quadro.
     * @return true se substituído com sucesso; false se não existir.
     */
    bool substituir(const std::string& id, const Quadro& quadro);

    /**
     * @brief Remove um quadro pelo identificador.
     * @param[in] id Identificador do quadro.
     * @return true se removido; false se inexistente.
     */
    bool remover(const std::string& id);

    /**
     * @brief Verifica se um quadro existe no contêiner.
     * @param[in] id Identificador do quadro.
     * @return true se existir; false caso contrário.
     */
    bool existe(const std::string& id) const;

    /**
     * @brief Consulta o identificador do projeto proprietário do quadro.
     * @param[in] id Identificador do quadro.
     * @param[out] idProjeto Recebe o código do projeto.
     * @return true se o quadro existir; false caso contrário.
     */
    bool projetoDoQuadro(const std::string& id, std::string& idProjeto) const;

    /**
     * @brief Verifica se existem quadros vinculados a determinado projeto.
     * @param[in] idProjeto Identificador do projeto.
     * @return true se houver ao menos um quadro no projeto; false caso contrário.
     */
    bool temQuadroDoProjeto(const std::string& idProjeto) const;

    /**
     * @brief Lista todos os identificadores de quadros cadastrados.
     * @return Vetor de identificadores.
     */
    std::vector<std::string> listarIds() const;
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
 * @brief Armazenamento em memória de cartões de atividade e seus vínculos.
 */
class ContainerCartoes {
private:
    std::vector<RegistroCartao> cartoes;

public:
    /**
     * @brief Insere um cartão com seus relacionamentos de quadro e responsável.
     * @param[in] cartao Dados da entidade CartaoDeAtividade.
     * @param[in] idQuadro Identificador do quadro Kanban.
     * @param[in] emailDesenvolvedor Email do desenvolvedor atribuído.
     * @return true se inserido com sucesso; false se o identificador já existir.
     */
    bool inserir(const CartaoDeAtividade& cartao, const std::string& idQuadro,
                 const std::string& emailDesenvolvedor);

    /**
     * @brief Recupera um cartão de atividade e opcionalmente seus vínculos.
     * @param[in] id Identificador do cartão.
     * @param[out] cartao Recebe os dados do cartão.
     * @param[out] idQuadro Ponteiro opcional para receber o id do quadro.
     * @param[out] emailDesenvolvedor Ponteiro opcional para receber o email do desenvolvedor.
     * @return true se encontrado; false caso contrário.
     */
    bool obter(const std::string& id, CartaoDeAtividade& cartao,
               std::string* idQuadro = 0,
               std::string* emailDesenvolvedor = 0) const;

    /**
     * @brief Atualiza os dados de um cartão existente.
     * @param[in] id Identificador do cartão.
     * @param[in] cartao Novos dados do cartão.
     * @return true se atualizado; false se não encontrado.
     */
    bool substituir(const std::string& id, const CartaoDeAtividade& cartao);

    /**
     * @brief Remove um cartão de atividade.
     * @param[in] id Identificador do cartão a ser excluído.
     * @return true se removido; false se inexistente.
     */
    bool remover(const std::string& id);

    /**
     * @brief Verifica se um cartão existe no contêiner.
     * @param[in] id Identificador do cartão.
     * @return true se existir; false caso contrário.
     */
    bool existe(const std::string& id) const;

    /**
     * @brief Verifica se determinado quadro possui algum cartão cadastrado.
     * @param[in] idQuadro Identificador do quadro.
     * @return true se houver cartões; false caso o quadro esteja vazio.
     */
    bool temCartaoNoQuadro(const std::string& idQuadro) const;

    /**
     * @brief Verifica se determinado desenvolvedor possui algum cartão sob sua responsabilidade.
     * @param[in] emailDesenvolvedor Email do desenvolvedor.
     * @return true se houver ao menos um cartão; false caso contrário.
     */
    bool temCartaoDoDesenvolvedor(const std::string& emailDesenvolvedor) const;

    /**
     * @brief Lista os identificadores de todos os cartões vinculados a um quadro.
     * @param[in] idQuadro Identificador do quadro.
     * @return Vetor de identificadores dos cartões.
     */
    std::vector<std::string> listarIdsDoQuadro(const std::string& idQuadro) const;

    /**
     * @brief Retorna cópias de todas as entidades cartão de um determinado quadro.
     * @param[in] idQuadro Identificador do quadro.
     * @return Vetor contendo as instâncias de CartaoDeAtividade.
     */
    std::vector<CartaoDeAtividade> listarCartoesDoQuadro(const std::string& idQuadro) const;
};

#endif // REPOSITORIOS_HPP_INCLUDED
