#ifndef ENTIDADES_HPP_INCLUDED
#define ENTIDADES_HPP_INCLUDED
#include "dominios.hpp"

/**
 * @brief Representa uma pessoa cadastrada no sistema.
 *
 * Uma pessoa pode atuar como gestor ou desenvolvedor de projetos.
 * O atributo email funciona como identificador (chave primaria) da
 * entidade.
 */
class Pessoa{
private:
    Email email;
    Nome nome;
    Senha senha;
    Papel papel;

public:
    /** Define o email (chave primaria) da pessoa; lanca excecao se invalido. */
    void setEmail(const string&);
    /** Retorna o email da pessoa. */
    string getEmail() const;

    /** Define o nome da pessoa; lanca excecao se invalido. */
    void setNome(const string&);
    /** Retorna o nome da pessoa. */
    string getNome() const;

    /** Define a senha da pessoa; lanca excecao se invalido. */
    void setSenha(const string&);
    /** Retorna a senha da pessoa. */
    string getSenha() const;

    /** Define o papel (GESTOR ou DESENVOLVEDOR) da pessoa; lanca excecao se invalido. */
    void setPapel(const string&);
    /** Retorna o papel da pessoa. */
    string getPapel() const;
};

inline string Pessoa::getEmail() const{
    return email.getEmail();
}

inline string Pessoa::getNome() const{
    return nome.getNome();
}

inline string Pessoa::getSenha() const{
    return senha.getSenha();
}

inline string Pessoa::getPapel() const{
    return papel.getPapel();
}


/**
 * @brief Representa um projeto cadastrado no sistema.
 *
 * Um projeto e criado e gerenciado por uma Pessoa que atua como
 * gestor. O atributo identificador funciona como chave primaria da
 * entidade.
 */
class Projeto{
private:
    Identificador identificador;
    Nome nome;
    Texto descricao;
    Timestamp inicio;
    Timestamp termino;

public:
    /** Define o identificador (chave primaria) do projeto; lanca excecao se invalido. */
    void setIdentificador(const string&);
    /** Retorna o identificador do projeto. */
    string getIdentificador() const;

    /** Define o nome do projeto; lanca excecao se invalido. */
    void setNome(const string&);
    /** Retorna o nome do projeto. */
    string getNome() const;

    /** Define a descricao do projeto; lanca excecao se invalido. */
    void setDescricao(const string&);
    /** Retorna a descricao do projeto. */
    string getDescricao() const;

    /** Define o timestamp de inicio do projeto; lanca excecao se invalido. */
    void setInicio(const string&);
    /** Retorna o timestamp de inicio do projeto. */
    string getInicio() const;

    /** Define o timestamp de termino do projeto; lanca excecao se invalido. */
    void setTermino(const string&);
    /** Retorna o timestamp de termino do projeto. */
    string getTermino() const;
};

inline string Projeto::getIdentificador() const{
    return identificador.getIdentificador();
}

inline string Projeto::getNome() const{
    return nome.getNome();
}

inline string Projeto::getDescricao() const{
    return descricao.getTexto();
}

inline string Projeto::getInicio() const{
    return inicio.getTimestamp();
}

inline string Projeto::getTermino() const{
    return termino.getTimestamp();
}


/**
 * @brief Representa um quadro Kanban.
 *
 * Um quadro pertence a um projeto e possui um limite de work in
 * progress (WIP) para a coluna FAZENDO. O atributo identificador
 * funciona como chave primaria da entidade.
 */
class Quadro{
private:
    Identificador identificador;
    Nome nome;
    Limite limite;

public:
    /** Define o identificador (chave primaria) do quadro; lanca excecao se invalido. */
    void setIdentificador(const string&);
    /** Retorna o identificador do quadro. */
    string getIdentificador() const;

    /** Define o nome do quadro; lanca excecao se invalido. */
    void setNome(const string&);
    /** Retorna o nome do quadro. */
    string getNome() const;

    /** Define o limite de WIP do quadro (1 a 25); lanca excecao se invalido. */
    void setLimite(int);
    /** Retorna o limite de WIP do quadro. */
    int getLimite() const;
};

inline string Quadro::getIdentificador() const{
    return identificador.getIdentificador();
}

inline string Quadro::getNome() const{
    return nome.getNome();
}

inline int Quadro::getLimite() const{
    return limite.getValor();
}


/**
 * @brief Representa um cartao de atividade de um quadro Kanban.
 *
 * O atributo identificador funciona como chave primaria da entidade.
 * Os atributos entrada, inicio e termino sao usados para calcular
 * tempo de ciclo, lead time e work in progress (WIP) do quadro.
 */
class CartaoDeAtividade{
private:
    Identificador identificador;
    Nome nome;
    Texto descricao;
    Prioridade prioridade;
    Estado estado;
    Tamanho tamanho;
    Timestamp entrada;
    Timestamp inicio;
    Timestamp termino;

public:
    /** Define o identificador (chave primaria) do cartao; lanca excecao se invalido. */
    void setIdentificador(const string&);
    /** Retorna o identificador do cartao. */
    string getIdentificador() const;

    /** Define o nome do cartao; lanca excecao se invalido. */
    void setNome(const string&);
    /** Retorna o nome do cartao. */
    string getNome() const;

    /** Define a descricao do cartao; lanca excecao se invalido. */
    void setDescricao(const string&);
    /** Retorna a descricao do cartao. */
    string getDescricao() const;

    /** Define a prioridade do cartao (ALTA, MEDIA ou BAIXA); lanca excecao se invalido. */
    void setPrioridade(const string&);
    /** Retorna a prioridade do cartao. */
    string getPrioridade() const;

    /** Define o estado do cartao (A FAZER, FAZENDO ou FEITO); lanca excecao se invalido. */
    void setEstado(const string&);
    /** Retorna o estado do cartao. */
    string getEstado() const;

    /** Define o tamanho do cartao (GRANDE, MEDIO ou PEQUENO); lanca excecao se invalido. */
    void setTamanho(const string&);
    /** Retorna o tamanho do cartao. */
    string getTamanho() const;

    /** Define o timestamp de entrada do cartao no quadro; lanca excecao se invalido. */
    void setEntrada(const string&);
    /** Retorna o timestamp de entrada do cartao no quadro. */
    string getEntrada() const;

    /** Define o timestamp de inicio (entrada na coluna FAZENDO) do cartao; lanca excecao se invalido. */
    void setInicio(const string&);
    /** Retorna o timestamp de inicio do cartao. */
    string getInicio() const;

    /** Define o timestamp de termino (entrada na coluna FEITO) do cartao; lanca excecao se invalido. */
    void setTermino(const string&);
    /** Retorna o timestamp de termino do cartao. */
    string getTermino() const;
};

inline string CartaoDeAtividade::getIdentificador() const{
    return identificador.getIdentificador();
}

inline string CartaoDeAtividade::getNome() const{
    return nome.getNome();
}

inline string CartaoDeAtividade::getDescricao() const{
    return descricao.getTexto();
}

inline string CartaoDeAtividade::getPrioridade() const{
    return prioridade.getPrioridade();
}

inline string CartaoDeAtividade::getEstado() const{
    return estado.getEstado();
}

inline string CartaoDeAtividade::getTamanho() const{
    return tamanho.getTamanho();
}

inline string CartaoDeAtividade::getEntrada() const{
    return entrada.getTimestamp();
}

inline string CartaoDeAtividade::getInicio() const{
    return inicio.getTimestamp();
}

inline string CartaoDeAtividade::getTermino() const{
    return termino.getTimestamp();
}

#endif // ENTIDADES_HPP_INCLUDED