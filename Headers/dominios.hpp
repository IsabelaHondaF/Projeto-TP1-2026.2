
#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED
#include <string>
#include <stdexcept>
using namespace std;

class Limite {
private:
    static const int MINIMO = 1;
    static const int MAXIMO = 25;
    int valor;
    void validar(int);

public:
    void setValor(int);
    int getValor() const;
};

inline int Limite::getValor() const{
    return valor;
}

class Senha{
private:
     string senha;
     void validar(const string&);
     static const int caracteres = 5;

public:
    void setSenha(const string&);
    string getSenha() const;
};

inline string Senha::getSenha() const{
    return senha;
}


class Estado{
private:
    static const string A_FAZER;
    static const string FAZENDO;
    static const string FEITO;
    string estado;
    void validar(const string&);

public:
    void setEstado(const string&);
    string getEstado() const;
};

inline string Estado::getEstado() const{
    return estado;
}


class Prioridade{
private:
    static const string ALTA;
    static const string MEDIA;
    static const string BAIXA;
    string prioridade;
    void validar(const string&);

public:
    void setPrioridade(const string&);
    string getPrioridade() const;
};

inline string Prioridade::getPrioridade() const{
    return prioridade;
}


class Tamanho{
private:
    static const string GRANDE;
    static const string MEDIO;
    static const string PEQUENO;
    string tamanho;
    void validar(const string&);

public:
    void setTamanho(const string&);
    string getTamanho() const;
};

inline string Tamanho::getTamanho() const{
    return tamanho;
}


class Nome {
private:
    static const int MAXIMO = 15;
    string nome;
    void validar(const string&);

public:
    void setNome(const string&);
    string getNome() const;
};

inline string Nome::getNome() const {
    return nome;
}

#endif; // DOMINIOS_HPP_INCLUDED;
