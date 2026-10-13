#ifndef REPOSITORIOS_HPP_INCLUDED
#define REPOSITORIOS_HPP_INCLUDED

#include "entidades.hpp"
#include <string>
#include <vector>

/**
 * @brief Armazenamento em memória das pessoas cadastradas.
 *
 * O repositório cuida somente da persistência em memória e da unicidade
 * da chave. Autenticação e permissões pertencem às controladoras de serviço.
 */
class ContainerPessoas {
private:
    std::vector<Pessoa> pessoas;

public:
    bool inserir(const Pessoa& pessoa);
    bool obter(const std::string& email, Pessoa& pessoa) const;
    bool substituir(const std::string& email, const Pessoa& pessoa);
    bool remover(const std::string& email);
    bool existe(const std::string& email) const;
    std::vector<std::string> listarEmails() const;
};

/** Registro de projeto e vínculo com a pessoa que o criou/gerencia. */
struct RegistroProjeto {
    Projeto projeto;
    std::string emailGestor;
};

/** @brief Armazenamento de projetos e de seus gestores. */
class ContainerProjetos {
private:
    std::vector<RegistroProjeto> projetos;

public:
    bool inserir(const Projeto& projeto, const std::string& emailGestor);
    bool obter(const std::string& id, Projeto& projeto,
               std::string* emailGestor = 0) const;
    bool substituir(const std::string& id, const Projeto& projeto);
    bool remover(const std::string& id);
    bool existe(const std::string& id) const;
    bool gestorDoProjeto(const std::string& id, std::string& emailGestor) const;
    bool temProjetoGerenciadoPor(const std::string& emailGestor) const;
    std::vector<std::string> listarIds() const;
};

/** Registro de quadro e vínculo com o projeto ao qual pertence. */
struct RegistroQuadro {
    Quadro quadro;
    std::string idProjeto;
};

/** @brief Armazenamento de quadros e de seus projetos associados. */
class ContainerQuadros {
private:
    std::vector<RegistroQuadro> quadros;

public:
    bool inserir(const Quadro& quadro, const std::string& idProjeto);
    bool obter(const std::string& id, Quadro& quadro,
               std::string* idProjeto = 0) const;
    bool substituir(const std::string& id, const Quadro& quadro);
    bool remover(const std::string& id);
    bool existe(const std::string& id) const;
    bool projetoDoQuadro(const std::string& id, std::string& idProjeto) const;
    bool temQuadroDoProjeto(const std::string& idProjeto) const;
    std::vector<std::string> listarIds() const;
};

/** Registro de cartão e seus vínculos com quadro e desenvolvedor responsável. */
struct RegistroCartao {
    CartaoDeAtividade cartao;
    std::string idQuadro;
    std::string emailDesenvolvedor;
};

/** @brief Armazenamento de cartões e dos respectivos vínculos. */
class ContainerCartoes {
private:
    std::vector<RegistroCartao> cartoes;

public:
    bool inserir(const CartaoDeAtividade& cartao, const std::string& idQuadro,
                 const std::string& emailDesenvolvedor);
    bool obter(const std::string& id, CartaoDeAtividade& cartao,
               std::string* idQuadro = 0,
               std::string* emailDesenvolvedor = 0) const;
    bool substituir(const std::string& id, const CartaoDeAtividade& cartao);
    bool remover(const std::string& id);
    bool existe(const std::string& id) const;
    bool temCartaoNoQuadro(const std::string& idQuadro) const;
    bool temCartaoDoDesenvolvedor(const std::string& emailDesenvolvedor) const;
    std::vector<std::string> listarIdsDoQuadro(const std::string& idQuadro) const;
    std::vector<CartaoDeAtividade> listarCartoesDoQuadro(const std::string& idQuadro) const;
};

#endif // REPOSITORIOS_HPP_INCLUDED
