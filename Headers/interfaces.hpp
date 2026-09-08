#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED
#include "entidades.hpp"
#include <vector>

//Padrão de nomeclatura: IServicoclasse_entidade
class IServicoPessoa{
public:

    virtual ~IServicoPessoa() = default;

    virtual bool criar(const Pessoa& pessoa) = 0;

    virtual bool autenticar(const Email& email, const Senha& senha) = 0;

    virtual Pessoa ler(const Email& usuario, const Email& alvo, Pessoa& pessoa) = 0;

    virtual Pessoa atualizar(const Email& usuario, Pessoa& pessoa) = 0;

    virtual void excluir(const Email& usuario, const Email& email) = 0;

    virtual bool listar(const Email& usuario, std::vector<Email>& emails) = 0;
};



#endif // INTERFACES_HPP_INCLUDED