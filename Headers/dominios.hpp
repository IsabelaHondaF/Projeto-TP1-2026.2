#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED

class Limite {
private:
    static const int MINIMO = 1;
    static const int MAXIMO = 25;

    int valor;
    bool validar(int);

public:
    bool setValor(int);
    int getValor();
};

inline int Limite::getValor() {
    return valor;
}

/*
class Estado{
private:
    static const string "A FAZER";
    static const string "FAZENDO";
    static const string "FEITO";

public:

};
*/

class Senha{
private:
     string senha;
     void validar(string, int);
     static const int caracteres = 5;
public:
    bool setSenha(string);
    string  getSenha();
};

inline string Senha::getSenha(){
    return senha;
}

#endif // DOMINIOS_HPP_INCLUDED
