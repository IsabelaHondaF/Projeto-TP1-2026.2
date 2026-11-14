#ifndef CONTROLADORAS_SERVICO_HPP_INCLUDED
#define CONTROLADORAS_SERVICO_HPP_INCLUDED

#include "interfaces.hpp"
#include "repositorios.hpp"

/**
 * @brief Implementação concreta dos serviços de negócio relacionados a Pessoa.
 *
 * Implementa IServicoPessoa utilizando os repositórios de pessoas, projetos e cartões.
 * Esses contêineres compartilham a conexão SQLite gerenciada por BancoDados.
 * Na execução normal, os dados são persistidos em kanban.db; nos testes,
 * o gerenciador pode utilizar um banco temporário em memória (:memory:).
 */
class CntrServicoPessoa : public IServicoPessoa {
private:
    ContainerPessoas& pessoas;
    ContainerProjetos& projetos;
    ContainerCartoes& cartoes;

public:
    /**
     * @brief Constrói a controladora de serviço de pessoa.
     * @param[in] pessoas Referência para o repositório de pessoas.
     * @param[in] projetos Referência para o repositório de projetos.
     * @param[in] cartoes Referência para o repositório de cartões.
     */
    CntrServicoPessoa(ContainerPessoas& pessoas,
                      ContainerProjetos& projetos,
                      ContainerCartoes& cartoes);

    /** @copydoc IServicoPessoa::criar */
    bool criar(const Pessoa& pessoa) override;

    /** @copydoc IServicoPessoa::autenticar */
    bool autenticar(const Email& email, const Senha& senha) override;

    /** @copydoc IServicoPessoa::ler */
    bool ler(const Email& usuario, const Email& alvo, Pessoa& pessoa) override;

    /** @copydoc IServicoPessoa::atualizar */
    bool atualizar(const Email& usuario, const Email& alvo, const Pessoa& pessoa) override;

    /** @copydoc IServicoPessoa::excluir */
    bool excluir(const Email& usuario, const Email& alvo) override;

    /** @copydoc IServicoPessoa::listar */
    bool listar(const Email& usuario, std::vector<Email>& emails) override;
};

/**
 * @brief Implementação concreta dos serviços de negócio relacionados a Projeto.
 *
 * Implementa a interface IServicoProjeto e aplica as regras de permissão (GESTOR).
 */
class CntrServicoProjeto : public IServicoProjeto {
private:
    ContainerPessoas& pessoas;
    ContainerProjetos& projetos;
    ContainerQuadros& quadros;

public:
    /**
     * @brief Constrói a controladora de serviço de projeto.
     * @param[in] pessoas Referência para o repositório de pessoas.
     * @param[in] projetos Referência para o repositório de projetos.
     * @param[in] quadros Referência para o repositório de quadros.
     */
    CntrServicoProjeto(ContainerPessoas& pessoas,
                       ContainerProjetos& projetos,
                       ContainerQuadros& quadros);

    /** @copydoc IServicoProjeto::criar */
    bool criar(const Email& gestor, const Projeto& projeto) override;

    /** @copydoc IServicoProjeto::ler */
    bool ler(const Email& usuario, const Identificador& identificador, Projeto& projeto) override;

    /** @copydoc IServicoProjeto::atualizar */
    bool atualizar(const Email& usuario, const Identificador& identificador,
                   const Projeto& projeto) override;

    /** @copydoc IServicoProjeto::excluir */
    bool excluir(const Email& usuario, const Identificador& identificador) override;

    /** @copydoc IServicoProjeto::listar */
    bool listar(const Email& usuario, std::vector<Identificador>& identificadores) override;
};

/**
 * @brief Implementação dos serviços de quadros e cartões do subsistema Quadro.
 *
 * Implementa IServicoQuadro, garantindo integridade, permissões, fluxo Kanban, WIP e métricas.
 */
class CntrServicoQuadro : public IServicoQuadro {
private:
    ContainerPessoas& pessoas;
    ContainerProjetos& projetos;
    ContainerQuadros& quadros;
    ContainerCartoes& cartoes;

public:
    /**
     * @brief Constrói a controladora de serviço de quadro.
     * @param[in] pessoas Referência para o repositório de pessoas.
     * @param[in] projetos Referência para o repositório de projetos.
     * @param[in] quadros Referência para o repositório de quadros.
     * @param[in] cartoes Referência para o repositório de cartões.
     */
    CntrServicoQuadro(ContainerPessoas& pessoas,
                      ContainerProjetos& projetos,
                      ContainerQuadros& quadros,
                      ContainerCartoes& cartoes);

    /** @copydoc IServicoQuadro::criar */
    bool criar(const Email& usuario, const Identificador& projeto, const Quadro& quadro) override;

    /** @copydoc IServicoQuadro::ler */
    bool ler(const Email& usuario, const Identificador& identificador, Quadro& quadro) override;

    /** @copydoc IServicoQuadro::atualizar */
    bool atualizar(const Email& usuario, const Identificador& identificador,
                   const Quadro& quadro) override;

    /** @copydoc IServicoQuadro::excluir */
    bool excluir(const Email& usuario, const Identificador& identificador) override;

    /** @copydoc IServicoQuadro::listar */
    bool listar(const Email& usuario, std::vector<Identificador>& identificadores) override;

    /** @copydoc IServicoQuadro::listarPorProjeto */
    bool listarPorProjeto(const Email& usuario, const Identificador& projeto,
                          std::vector<Identificador>& identificadores) override;

    /** @copydoc IServicoQuadro::criarCartao */
    bool criarCartao(const Email& usuario, const Identificador& quadro,
                     const Email& desenvolvedor, const CartaoDeAtividade& cartao) override;

    /** @copydoc IServicoQuadro::lerCartao */
    bool lerCartao(const Email& usuario, const Identificador& identificador,
                   CartaoDeAtividade& cartao) override;

    /** @copydoc IServicoQuadro::atualizarCartao */
    bool atualizarCartao(const Email& usuario, const Identificador& identificador,
                         const CartaoDeAtividade& cartao) override;

    /** @copydoc IServicoQuadro::excluirCartao */
    bool excluirCartao(const Email& usuario, const Identificador& identificador) override;

    /** @copydoc IServicoQuadro::listarCartoes */
    bool listarCartoes(const Email& usuario, const Identificador& quadro,
                       std::vector<Identificador>& identificadores) override;

    /** @copydoc IServicoQuadro::moverCartao */
    bool moverCartao(const Email& usuario, const Identificador& identificador,
                     const Timestamp& instante) override;

    /** @copydoc IServicoQuadro::lerTempoCiclo */
    bool lerTempoCiclo(const Email& usuario, const Identificador& identificador,
                       long long& minutos) override;

    /** @copydoc IServicoQuadro::lerTempoCicloMedio */
    bool lerTempoCicloMedio(const Email& usuario, const Identificador& quadro,
                            double& minutos) override;

    /** @copydoc IServicoQuadro::lerLeadTime */
    bool lerLeadTime(const Email& usuario, const Identificador& identificador,
                     long long& minutos) override;

    /** @copydoc IServicoQuadro::lerLeadTimeMedio */
    bool lerLeadTimeMedio(const Email& usuario, const Identificador& quadro,
                          double& minutos) override;

    /** @copydoc IServicoQuadro::lerWIP */
    bool lerWIP(const Email& usuario, const Identificador& quadro,
                int& quantidade) override;
};

#endif // CONTROLADORAS_SERVICO_HPP_INCLUDED
