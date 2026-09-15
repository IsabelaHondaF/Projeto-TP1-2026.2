#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include "entidades.hpp"
#include <vector>

// Padrao de nomenclatura: IServico + nome da entidade

class IServicoPessoa {
public:

    virtual ~IServicoPessoa() = default;

    virtual bool criar(
        const Pessoa& pessoa
    ) = 0;

    virtual bool autenticar(
        const Email& email,
        const Senha& senha
    ) = 0;

    virtual bool ler(
        const Email& usuario,
        const Email& alvo,
        Pessoa& pessoa
    ) = 0;

    virtual bool atualizar(
        const Email& usuario,
        const Pessoa& pessoa
    ) = 0;

    virtual bool excluir(
        const Email& usuario,
        const Email& alvo
    ) = 0;

    virtual bool listar(
        const Email& usuario,
        std::vector<Email>& emails
    ) = 0;
};


class IServicoProjeto {
public:

    virtual ~IServicoProjeto() = default;

    virtual bool criar(
        const Email& gestor,
        const Projeto& projeto
    ) = 0;

    virtual bool ler(
        const Email& usuario,
        const Identificador& identificador,
        Projeto& projeto
    ) = 0;

    virtual bool atualizar(
        const Email& usuario,
        const Projeto& projeto
    ) = 0;

    virtual bool excluir(
        const Email& usuario,
        const Identificador& identificador
    ) = 0;

    virtual bool listar(
        const Email& usuario,
        std::vector<Identificador>& identificadores
    ) = 0;
};

#endif // INTERFACES_HPP_INCLUDED