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
void Nome::validar(const string& nome) {
    //valida tamanho
    if (nome.empty() || nome.length() > MAXIMO)
        throw invalid_argument("Nome invalido.");
    //valida espaços no início e fim
    if (nome.front() == ' ' || nome.back() == ' ')
        throw invalid_argument("Nome invalido.");

    for (size_t i = 0; i < nome.length(); i++) {

        bool Ehletra = (nome[i] >= 'A' && nome[i] <= 'Z') ||
                     (nome[i] >= 'a' && nome[i] <= 'z');
        //se não for letra e não for espaço, nome inválido
        if (!Ehletra && nome[i] != ' ')
            throw invalid_argument("Nome invalido.");
        //se for espaço e o próximo caractere não for o último
        if (nome[i] == ' ' && i + 1 < nome.length()) {
    
            bool proximoEhLetra =
                (nome[i + 1] >= 'A' && nome[i + 1] <= 'Z') ||
                (nome[i + 1] >= 'a' && nome[i + 1] <= 'z');
            //se o proximo caractere não for letra, nome inválido
            if (!proximoEhLetra)
                throw invalid_argument("Nome invalido.");
        }
    }
}

void Nome::setNome(const string& nome) {
    validar(nome);
    this->nome = nome;
}


//CLasse Papel
const string Papel::GESTOR = "GESTOR";
const string Papel::DESENVOLVEDOR = "DESENVOLVEDOR";

void Papel::validar(const string& papel){
    if(papel != GESTOR && papel != DESENVOLVEDOR)
        throw invalid_argument("Papel invalido.");
}

void Papel::setPapel(const string& papel){
    validar(papel);
    this->papel = papel;
}


//Classe Texto
void Texto::validar(const string& texto){
    //texto vazio ou acima de 30 caracteres
    if(texto.empty() || texto.length()>MAXIMO)
        throw invalid_argument("Texto invalido");
    
    //primeiro caractere deve ser letra maiuscula, ultimo deve ser ponto
    if((texto.front() < 'A' || texto.front() > 'Z') || texto.back() != '.')
        throw invalid_argument("Texto invalido");

    for (size_t i = 0; i < texto.length(); i++) {

        char caractere = texto[i];

        bool letra =
            (caractere >= 'A' && caractere <= 'Z') ||
            (caractere >= 'a' && caractere <= 'z');

        bool digito =
            (caractere >= '0' && caractere <= '9');

        bool pontuacao =
            caractere == ',' ||
            caractere == ';' ||
            caractere == '.' ||
            caractere == ':' ||
            caractere == '?' ||
            caractere == '!';

        // Verifica se o caractere pertence ao conjunto permitido.
        if (!letra && !digito && caractere != ' ' && !pontuacao)
            throw invalid_argument("Texto invalido.");
        
        //se o caractere atual for pontuacao, verifica se o proximo tambem é
        if(pontuacao && i + 1 < texto.length()){

            char proxcaractere = texto[i + 1];

            bool proxpontuacao =
            proxcaractere == ',' ||
            proxcaractere == ';' ||
            proxcaractere == '.' ||
            proxcaractere == ':' ||
            proxcaractere == '?' ||
            proxcaractere == '!';

            //se o proximo tambem for pontuacao
            if(proxpontuacao)
                throw invalid_argument("Texto invalido.");

        }
    }
}

void Texto::setTexto(const string& texto){
    validar(texto);
    this->texto = texto;
}


//Classe Identificador
void Identificador::validar(const string& identificador){
    //deve conter 6 caracteres
    if(identificador.length() != TAMANHO)
        throw invalid_argument("Identificador invalido.");
    
    bool verifica = true;

    for(size_t i = 0; i < identificador.length(); i++){

        char caractere = identificador[i];

        if(i < 3)
            if((caractere <'A' || caractere > 'Z') &&
            (caractere < 'a' || caractere > 'z'))
                verifica = false;
        else    
            if(caractere < '0' || caractere > '9')
               verifica = false;
        
        if(!verifica)
            throw invalid_argument("Identificador invalido.");
    }

}

void Identificador::setIdentificador(const string& identificador){
    validar(identificador);
    this->identificador = identificador;
} 
#endif // DOMINIOS_CPP_INCLUDED
