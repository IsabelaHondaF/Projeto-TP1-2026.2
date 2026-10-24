#ifndef TESTES_DOMINIOS_HPP_INCLUDED
#define TESTES_DOMINIOS_HPP_INCLUDED

#include "dominios.hpp"

/**
 * @brief Classe base de suporte para testes unitários com contagem de asserções.
 */
class TesteUnitarioBase {
protected:
    int sucesso;
    int falha;

public:
    TesteUnitarioBase() : sucesso(0), falha(0) {}
    virtual ~TesteUnitarioBase() = default;

    int getSucesso() const { return sucesso; }
    int getFalha() const { return falha; }
};

/** @brief Teste de unidade para o domínio Limite. */
class TULimite : public TesteUnitarioBase {
public:
    bool executar();
};

/** @brief Teste de unidade para o domínio Senha. */
class TUSenha : public TesteUnitarioBase {
public:
    bool executar();
};

/** @brief Teste de unidade para o domínio Estado. */
class TUEstado : public TesteUnitarioBase {
public:
    bool executar();
};

/** @brief Teste de unidade para o domínio Prioridade. */
class TUPrioridade : public TesteUnitarioBase {
public:
    bool executar();
};

/** @brief Teste de unidade para o domínio Tamanho. */
class TUTamanho : public TesteUnitarioBase {
public:
    bool executar();
};

/** @brief Teste de unidade para o domínio Nome. */
class TUNome : public TesteUnitarioBase {
public:
    bool executar();
};

/** @brief Teste de unidade para o domínio Papel. */
class TUPapel : public TesteUnitarioBase {
public:
    bool executar();
};

/** @brief Teste de unidade para o domínio Texto. */
class TUTexto : public TesteUnitarioBase {
public:
    bool executar();
};

/** @brief Teste de unidade para o domínio Identificador. */
class TUIdentificador : public TesteUnitarioBase {
public:
    bool executar();
};

/** @brief Teste de unidade para o domínio Email. */
class TUEmail : public TesteUnitarioBase {
public:
    bool executar();
};

/** @brief Teste de unidade para o domínio Timestamp. */
class TUTimestamp : public TesteUnitarioBase {
public:
    bool executar();
};

#endif // TESTES_DOMINIOS_HPP_INCLUDED

