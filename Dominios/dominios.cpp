#ifndef DOMINIOS_CPP_INCLUDED
#define DOMINIOS_CPP_INCLUDED
#include "../Headers/dominios.hpp"
#include <stdexcept>
#include <cstring>
using namespace std;

//Classe Limite
void Limite::validar(int valor){
    if(valor < MINIMO || valor > MAXIMO)
        throw invalid_argument("Limite Quebrado.");
}

void Limite::setValor(int valor){
        validar(valor);
        this->valor = valor;
}


//Classe Senha
void Senha::validar(const string& senha) {
    bool possuiLetra = false;
    bool possuiDigito = false;

    if (senha.length() != 5)
        throw invalid_argument("Senha invalida.");

    for (char caractere : senha) {

        if ((caractere >= 'a' && caractere <= 'z') ||
            (caractere >= 'A' && caractere <= 'Z')) {
            possuiLetra = true;
        }
        else if (caractere >= '0' && caractere <= '9') {
            possuiDigito = true;
        }
        else {
            throw invalid_argument("Senha invalida.");
        }
    }

    if (!possuiLetra || !possuiDigito)
        throw invalid_argument("Senha invalida.");
}

void Senha::setSenha(const string& senha) {
    validar(senha);
    this->senha = senha;
}


//Classe Estado
const string Estado::A_FAZER = "A FAZER";
const string Estado::FAZENDO = "FAZENDO";
const string Estado::FEITO = "FEITO";

void Estado::validar(const string& estado){
    if(estado != A_FAZER && estado != FAZENDO && estado != FEITO)
        throw invalid_argument("Estado invalido.");
}

void Estado::setEstado(const string& estado){
    validar(estado);
    this->estado = estado;
}


//Classe Prioridade
const string Prioridade::ALTA = "ALTA";
const string Prioridade::MEDIA = "MEDIA";
const string Prioridade::BAIXA = "BAIXA";

void Prioridade::validar(const string& prioridade){
    if(prioridade != ALTA && prioridade != MEDIA && prioridade != BAIXA)
        throw invalid_argument("Prioridade invalida.");
}

void Prioridade::setPrioridade(const string& prioridade){
    validar(prioridade);
    this->prioridade = prioridade;
}


//Classe Tamanho
const string Tamanho::GRANDE = "GRANDE";
const string Tamanho::MEDIO = "MEDIO";
const string Tamanho::PEQUENO = "PEQUENO";

void Tamanho::validar(const string& tamanho){
    if(tamanho != GRANDE && tamanho != MEDIO && tamanho != PEQUENO)
        throw invalid_argument("Tamanho invalido.");
}

void Tamanho::setTamanho(const string& tamanho){
    validar(tamanho);
    this->tamanho = tamanho;
}


//Classe Nome
void Nome::validar(const string& novoNome) {
    //valida tamanho
    if (novoNome.empty() || novoNome.length() > MAXIMO)
        throw invalid_argument("Nome invalido.");
    //valida espaços no início e fim
    if (novoNome.front() == ' ' || novoNome.back() == ' ')
        throw invalid_argument("Nome invalido.");

    for (unsigned int i = 0; i < novoNome.length(); i++) {

        bool Ehletra = (novoNome[i] >= 'A' && novoNome[i] <= 'Z') ||
                     (novoNome[i] >= 'a' && novoNome[i] <= 'z');
        //se não for letra e não for espaço, nome inválido
        if (!Ehletra && novoNome[i] != ' ')
            throw invalid_argument("Nome invalido.");
        //se for espaço e o próximo caractere não for o último
        if (novoNome[i] == ' ' && i + 1 < novoNome.length()) {
    
            bool proximoEhLetra =
                (novoNome[i + 1] >= 'A' && novoNome[i + 1] <= 'Z') ||
                (novoNome[i + 1] >= 'a' && novoNome[i + 1] <= 'z');
            //se o proximo caractere não for letra, nome inválido
            if (!proximoEhLetra)
                throw invalid_argument("Nome invalido.");
        }
    }
}

void Nome::setNome(const string& novoNome) {
    validar(novoNome);
    nome = novoNome;
}

#endif // DOMINIOS_CPP_INCLUDED
