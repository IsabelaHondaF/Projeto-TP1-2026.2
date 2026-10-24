#ifndef TESTES_ENTIDADES_HPP_INCLUDED
#define TESTES_ENTIDADES_HPP_INCLUDED

#include "entidades.hpp"
#include "testes_dominios.hpp"

/** @brief Teste de unidade para a entidade Pessoa. */
class TUPessoa : public TesteUnitarioBase {
public:
    bool executar();
};

/** @brief Teste de unidade para a entidade Projeto. */
class TUProjeto : public TesteUnitarioBase {
public:
    bool executar();
};

/** @brief Teste de unidade para a entidade Quadro. */
class TUQuadro : public TesteUnitarioBase {
public:
    bool executar();
};

/** @brief Teste de unidade para a entidade CartaoDeAtividade. */
class TUCartaoDeAtividade : public TesteUnitarioBase {
public:
    bool executar();
};

#endif // TESTES_ENTIDADES_HPP_INCLUDED
