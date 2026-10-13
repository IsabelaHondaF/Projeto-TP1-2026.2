#ifndef APRESENTACAO_HPP_INCLUDED
#define APRESENTACAO_HPP_INCLUDED

#include "interfaces.hpp"
#include <string>

/**
 * @file apresentacao.hpp
 * @brief Camada de apresentação: interface com o usuário (cin/cout) e validação dos dados de entrada.
 *
 * As classes desta camada dependem apenas das interfaces de serviço
 * (IServicoPessoa, IServicoProjeto, IServicoQuadro e IServicoCartaoDeAtividade),
 * nunca das classes concretas da camada de serviço.
 */

/**
 * @brief Exceção lançada quando a entrada padrão termina (fim de arquivo).
 *
 * É capturada por CntrApresentacaoPrincipal::executar, que encerra o programa com elegância.
 */
class FimDeEntrada {};

/**
 * @brief Controladora de apresentação dos serviços relacionados a Pessoa.
 *
 * Lê e valida os dados digitados (e-mail, nome, senha e papel) antes de chamar o serviço.
 */
class CntrApresentacaoPessoa {
private:
    IServicoPessoa* servico;
public:
    /**
     * @brief Constrói a controladora.
     * @param[in] servico Serviço de pessoa que será utilizado (não pode ser nulo).
     */
    explicit CntrApresentacaoPessoa(IServicoPessoa* servico);

    /**
     * @brief Solicita os dados de uma nova conta e a cadastra (serviço CRIAR PESSOA).
     * @return true se a conta foi criada.
     */
    bool cadastrar();

    /**
     * @brief Solicita e-mail e senha e verifica as credenciais.
     * @param[out] usuario Recebe o e-mail autenticado em caso de sucesso.
     * @return true se a autenticação foi bem-sucedida.
     */
    bool autenticar(Email& usuario);

    /**
     * @brief Apresenta o menu de pessoas (ler, atualizar, excluir e listar).
     * @param[in] usuario E-mail do usuário autenticado.
     * @return true se o usuário excluiu a própria conta (a sessão deve ser encerrada).
     */
    bool executar(const Email& usuario);

private:
    void ler(const Email& usuario);
    void atualizar(const Email& usuario);
    bool excluir(const Email& usuario);
    void listar(const Email& usuario);
};

/**
 * @brief Controladora de apresentação dos serviços relacionados a Projeto.
 */
class CntrApresentacaoProjeto {
private:
    IServicoProjeto* servico;
public:
    /**
     * @brief Constrói a controladora.
     * @param[in] servico Serviço de projeto que será utilizado (não pode ser nulo).
     */
    explicit CntrApresentacaoProjeto(IServicoProjeto* servico);

    /**
     * @brief Apresenta o menu de projetos conforme o papel do usuário.
     * @param[in] usuario E-mail do usuário autenticado.
     * @param[in] papel Papel do usuário (GESTOR ou DESENVOLVEDOR).
     */
    void executar(const Email& usuario, const std::string& papel);

private:
    void criar(const Email& usuario);
    void ler(const Email& usuario);
    void atualizar(const Email& usuario);
    void excluir(const Email& usuario);
    void listar(const Email& usuario);
};

/**
 * @brief Controladora de apresentação dos serviços relacionados a Quadro.
 */
class CntrApresentacaoQuadro {
private:
    IServicoQuadro* servico;
public:
    /**
     * @brief Constrói a controladora.
     * @param[in] servico Serviço de quadro que será utilizado (não pode ser nulo).
     */
    explicit CntrApresentacaoQuadro(IServicoQuadro* servico);

    /**
     * @brief Apresenta o menu de quadros conforme o papel do usuário.
     * @param[in] usuario E-mail do usuário autenticado.
     * @param[in] papel Papel do usuário (GESTOR ou DESENVOLVEDOR).
     */
    void executar(const Email& usuario, const std::string& papel);

private:
    void criar(const Email& usuario);
    void ler(const Email& usuario);
    void atualizar(const Email& usuario);
    void excluir(const Email& usuario);
    void listar(const Email& usuario);
};

/**
 * @brief Controladora de apresentação dos serviços relacionados a Cartão de atividade.
 *
 * Inclui mover cartão e a leitura de tempo de ciclo, lead time e WIP.
 */
class CntrApresentacaoCartao {
private:
    IServicoCartaoDeAtividade* servico;
public:
    /**
     * @brief Constrói a controladora.
     * @param[in] servico Serviço de cartão que será utilizado (não pode ser nulo).
     */
    explicit CntrApresentacaoCartao(IServicoCartaoDeAtividade* servico);

    /**
     * @brief Apresenta o menu de cartões conforme o papel do usuário.
     * @param[in] usuario E-mail do usuário autenticado.
     * @param[in] papel Papel do usuário (GESTOR ou DESENVOLVEDOR).
     */
    void executar(const Email& usuario, const std::string& papel);

private:
    void criar(const Email& usuario);
    void ler(const Email& usuario);
    void atualizar(const Email& usuario);
    void excluir(const Email& usuario);
    void listar(const Email& usuario);
    void mover(const Email& usuario);
    void lerTempoCiclo(const Email& usuario);
    void lerTempoCicloMedio(const Email& usuario);
    void lerLeadTime(const Email& usuario);
    void lerLeadTimeMedio(const Email& usuario);
    void lerWIP(const Email& usuario);
};

/**
 * @brief Controladora principal da apresentação: tela inicial, sessão e menu principal.
 *
 * Coordena as demais controladoras de apresentação. Só repassa aos serviços
 * o e-mail de um usuário que passou pela autenticação.
 */
class CntrApresentacaoPrincipal {
private:
    IServicoPessoa* servicoPessoa;
    CntrApresentacaoPessoa pessoa;
    CntrApresentacaoProjeto projeto;
    CntrApresentacaoQuadro quadro;
    CntrApresentacaoCartao cartao;
public:
    /**
     * @brief Constrói a controladora principal a partir das interfaces de serviço.
     * @param[in] servicoPessoa Serviço de pessoa.
     * @param[in] servicoProjeto Serviço de projeto.
     * @param[in] servicoQuadro Serviço de quadro.
     * @param[in] servicoCartao Serviço de cartão de atividade.
     */
    CntrApresentacaoPrincipal(IServicoPessoa* servicoPessoa,
                              IServicoProjeto* servicoProjeto,
                              IServicoQuadro* servicoQuadro,
                              IServicoCartaoDeAtividade* servicoCartao);

    /**
     * @brief Executa o sistema: tela inicial (entrar, criar conta, sair) e menu principal.
     */
    void executar();

private:
    void sessao(const Email& usuario);
};

#endif // APRESENTACAO_HPP_INCLUDED
