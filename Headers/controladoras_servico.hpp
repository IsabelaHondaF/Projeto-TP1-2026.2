#ifndef CONTROLADORAS_SERVICO_HPP_INCLUDED
#define CONTROLADORAS_SERVICO_HPP_INCLUDED

#include "interfaces.hpp"
#include "repositorios.hpp"

/**
 * @brief Implementação concreta dos serviços de negócio relacionados a Pessoa.
 *
 * Implementa a interface IServicoPessoa acessando os contêineres compartilhados em memória.
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
 * @brief Implementação concreta dos serviços de negócio relacionados a Quadro Kanban.
 *
 * Implementa a interface IServicoQuadro e garante integridade com os projetos pais e cartões filhos.
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
};

/**
 * @brief Implementação concreta dos serviços de negócio de Cartão de Atividade.
 *
 * Implementa a interface IServicoCartaoDeAtividade, gerenciando o fluxo Kanban,
 * limites de WIP e métricas de tempo de ciclo e lead time.
 */
class CntrServicoCartaoDeAtividade : public IServicoCartaoDeAtividade {
private:
    ContainerPessoas& pessoas;
    ContainerProjetos& projetos;
    ContainerQuadros& quadros;
    ContainerCartoes& cartoes;

public:
    /**
     * @brief Constrói a controladora de serviço de cartões de atividade.
     * @param[in] pessoas Referência para o repositório de pessoas.
     * @param[in] projetos Referência para o repositório de projetos.
     * @param[in] quadros Referência para o repositório de quadros.
     * @param[in] cartoes Referência para o repositório de cartões.
     */
    CntrServicoCartaoDeAtividade(ContainerPessoas& pessoas,
                                 ContainerProjetos& projetos,
                                 ContainerQuadros& quadros,
                                 ContainerCartoes& cartoes);

    /** @copydoc IServicoCartaoDeAtividade::criar */
    bool criar(const Email& usuario, const Identificador& quadro,
               const Email& desenvolvedor, const CartaoDeAtividade& cartao) override;

    /** @copydoc IServicoCartaoDeAtividade::ler */
    bool ler(const Email& usuario, const Identificador& identificador,
             CartaoDeAtividade& cartao) override;

    /** @copydoc IServicoCartaoDeAtividade::atualizar */
    bool atualizar(const Email& usuario, const Identificador& identificador,
                   const CartaoDeAtividade& cartao) override;

    /** @copydoc IServicoCartaoDeAtividade::excluir */
    bool excluir(const Email& usuario, const Identificador& identificador) override;

    /** @copydoc IServicoCartaoDeAtividade::listar */
    bool listar(const Email& usuario, const Identificador& quadro,
                std::vector<Identificador>& identificadores) override;

    /** @copydoc IServicoCartaoDeAtividade::mover */
    bool mover(const Email& usuario, const Identificador& identificador,
               const Timestamp& instante) override;

    /** @copydoc IServicoCartaoDeAtividade::lerTempoCiclo */
    bool lerTempoCiclo(const Email& usuario, const Identificador& identificador,
                       long long& minutos) override;

    /** @copydoc IServicoCartaoDeAtividade::lerTempoCicloMedio */
    bool lerTempoCicloMedio(const Email& usuario, const Identificador& quadro,
                            double& minutos) override;

    /** @copydoc IServicoCartaoDeAtividade::lerLeadTime */
    bool lerLeadTime(const Email& usuario, const Identificador& identificador,
                     long long& minutos) override;

    /** @copydoc IServicoCartaoDeAtividade::lerLeadTimeMedio */
    bool lerLeadTimeMedio(const Email& usuario, const Identificador& quadro,
                          double& minutos) override;

    /** @copydoc IServicoCartaoDeAtividade::lerWIP */
    bool lerWIP(const Email& usuario, const Identificador& quadro,
                int& quantidade) override;
};

#endif // CONTROLADORAS_SERVICO_HPP_INCLUDED
