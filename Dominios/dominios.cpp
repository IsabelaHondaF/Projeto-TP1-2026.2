#ifndef DOMINIOS_CPP_INCLUDED
#define DOMINIOS_CPP_INCLUDED
#include "Headers/dominios.cpp"
#include <cstring>

//Classe LIMITE
bool Limite::validar(int valor){
    if(valor >= MINIMO && valor <= MAXIMO)
        return true;
    else
        return false;
}

bool Limite::setValor(int valor){
    if(validar(valor)){
        this->valor = valor;
        return true;
    }
    else
        return false;
}

#endif // DOMINIOS_CPP_INCLUDED
