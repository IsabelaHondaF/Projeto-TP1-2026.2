#ifndef CONTROLADORAS_SERVICO_HPP_INCLUDED
#define CONTROLADORAS_SERVICO_HPP_INCLUDED

#include "interfaces.hpp"
#include "repositorios.hpp"

/**
 * @brief Implementação concreta dos serviços de pessoa.
 *
 * Recebe o container por referência: não cria outra cópia do armazenamento.
 */
class CntrServicoPessoa : public IServicoPessoa {
private:
    ContainerPessoas& pessoas;
    ContainerProjetos& projetos;
    ContainerCartoes& cartoes;

public:
    CntrServicoPessoa(ContainerPessoas& pessoas,
                      ContainerProjetos& projetos,
                      ContainerCartoes& cartoes);

    bool criar(const Pessoa& pessoa) override;
    bool autenticar(const Email& email, const Senha& senha) override;
    bool ler(const Email& usuario, const Email& alvo, Pessoa& pessoa) override;
    bool atualizar(const Email& usuario, const Email& alvo, const Pessoa& pessoa) override;
    bool excluir(const Email& usuario, const Email& alvo) override;
    bool listar(const Email& usuario, std::vector<Email>& emails) override;
};

/** @brief Implementação concreta das operações de projeto. */
class CntrServicoProjeto : public IServicoProjeto {
private:
    ContainerPessoas& pessoas;
    ContainerProjetos& projetos;
    ContainerQuadros& quadros;

public:
    CntrServicoProjeto(ContainerPessoas& pessoas,
                       ContainerProjetos& projetos,
                       ContainerQuadros& quadros);

    bool criar(const Email& gestor, const Projeto& projeto) override;
    bool ler(const Email& usuario, const Identificador& identificador, Projeto& projeto) override;
    bool atualizar(const Email& usuario, const Identificador& identificador,
                   const Projeto& projeto) override;
    bool excluir(const Email& usuario, const Identificador& identificador) override;
    bool listar(const Email& usuario, std::vector<Identificador>& identificadores) override;
};

/** @brief Implementação concreta das operações de quadro Kanban. */
class CntrServicoQuadro : public IServicoQuadro {
private:
    ContainerPessoas& pessoas;
    ContainerProjetos& projetos;
    ContainerQuadros& quadros;
    ContainerCartoes& cartoes;

public:
    CntrServicoQuadro(ContainerPessoas& pessoas,
                      ContainerProjetos& projetos,
                      ContainerQuadros& quadros,
                      ContainerCartoes& cartoes);

    bool criar(const Email& usuario, const Identificador& projeto, const Quadro& quadro) override;
    bool ler(const Email& usuario, const Identificador& identificador, Quadro& quadro) override;
    bool atualizar(const Email& usuario, const Identificador& identificador,
                   const Quadro& quadro) override;
    bool excluir(const Email& usuario, const Identificador& identificador) override;
    bool listar(const Email& usuario, std::vector<Identificador>& identificadores) override;
};

/**
 * @brief Implementação concreta dos serviços de cartão de atividade.
 *
 * As movimentações válidas são A FAZER -> FAZENDO -> FEITO. Os instantes
 * de início e término são definidos exclusivamente por mover().
 */
class CntrServicoCartaoDeAtividade : public IServicoCartaoDeAtividade {
private:
    ContainerPessoas& pessoas;
    ContainerProjetos& projetos;
    ContainerQuadros& quadros;
    ContainerCartoes& cartoes;

public:
    CntrServicoCartaoDeAtividade(ContainerPessoas& pessoas,
                                 ContainerProjetos& projetos,
                                 ContainerQuadros& quadros,
                                 ContainerCartoes& cartoes);

    bool criar(const Email& usuario, const Identificador& quadro,
               const Email& desenvolvedor, const CartaoDeAtividade& cartao) override;
    bool ler(const Email& usuario, const Identificador& identificador,
             CartaoDeAtividade& cartao) override;
    bool atualizar(const Email& usuario, const Identificador& identificador,
                   const CartaoDeAtividade& cartao) override;
    bool excluir(const Email& usuario, const Identificador& identificador) override;
    bool listar(const Email& usuario, const Identificador& quadro,
                std::vector<Identificador>& identificadores) override;
    bool mover(const Email& usuario, const Identificador& identificador,
               const Timestamp& instante) override;
    bool lerTempoCiclo(const Email& usuario, const Identificador& identificador,
                       long long& minutos) override;
    bool lerTempoCicloMedio(const Email& usuario, const Identificador& quadro,
                            double& minutos) override;
    bool lerLeadTime(const Email& usuario, const Identificador& identificador,
                     long long& minutos) override;
    bool lerLeadTimeMedio(const Email& usuario, const Identificador& quadro,
                          double& minutos) override;
    bool lerWIP(const Email& usuario, const Identificador& quadro,
                int& quantidade) override;
};

#endif // CONTROLADORAS_SERVICO_HPP_INCLUDED
