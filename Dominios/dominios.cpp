#ifndef DOMINIOS_CPP_INCLUDED
#define DOMINIOS_CPP_INCLUDED
#include "../Headers/dominios.hpp"
#include <stdexcept>
#include <cstring>

//Classe Limite
void Limite::validar(int valor){
    if(valor < MINIMO || valor > MAXIMO)
        throw std::invalid_argument("Limite Quebrado.");
}

void Limite::setValor(int valor){
        validar(valor);
        this->valor = valor;
}


//Classe Senha
void Senha::validar(const std::string& senha) {
    bool possuiLetra = false;
    bool possuiDigito = false;

    if (senha.length() != 5)
        throw std::invalid_argument("Senha invalida.");

    for (char caractere : senha) {

        if ((caractere >= 'a' && caractere <= 'z') ||
            (caractere >= 'A' && caractere <= 'Z')) {
            possuiLetra = true;
        }
        else if (caractere >= '0' && caractere <= '9') {
            possuiDigito = true;
        }
        else {
            throw std::invalid_argument("Senha invalida.");
        }
    }

    if (!possuiLetra || !possuiDigito)
        throw std::invalid_argument("Senha invalida.");
}

void Senha::setSenha(const std::string& senha) {
    validar(senha);
    this->senha = senha;
}


//Classe Estado
const std::string Estado::A_FAZER = "A FAZER";
const std::string Estado::FAZENDO = "FAZENDO";
const std::string Estado::FEITO = "FEITO";

void Estado::validar(const std::string& estado){
    if(estado != A_FAZER && estado != FAZENDO && estado != FEITO)
        throw std::invalid_argument("Estado invalido.");
}

void Estado::setEstado(const std::string& estado){
    validar(estado);
    this->estado = estado;
}


//Classe Prioridade
const std::string Prioridade::ALTA = "ALTA";
const std::string Prioridade::MEDIA = "MEDIA";
const std::string Prioridade::BAIXA = "BAIXA";

void Prioridade::validar(const std::string& prioridade){
    if(prioridade != ALTA && prioridade != MEDIA && prioridade != BAIXA)
        throw std::invalid_argument("Prioridade invalida.");
}

void Prioridade::setPrioridade(const std::string& prioridade){
    validar(prioridade);
    this->prioridade = prioridade;
}


//Classe Tamanho
const std::string Tamanho::GRANDE = "GRANDE";
const std::string Tamanho::MEDIO = "MEDIO";
const std::string Tamanho::PEQUENO = "PEQUENO";

void Tamanho::validar(const std::string& tamanho){
    if(tamanho != GRANDE && tamanho != MEDIO && tamanho != PEQUENO)
        throw std::invalid_argument("Tamanho invalido.");
}

void Tamanho::setTamanho(const std::string& tamanho){
    validar(tamanho);
    this->tamanho = tamanho;
}


//Classe Nome
void Nome::validar(const std::string& nome) {
    //valida tamanho
    if (nome.empty() || nome.length() > MAXIMO)
        throw std::invalid_argument("Nome invalido.");
    //valida espaços no início e fim
    if (nome.front() == ' ' || nome.back() == ' ')
        throw std::invalid_argument("Nome invalido.");

    for (std::size_t i = 0; i < nome.length(); i++) {

        bool Ehletra = (nome[i] >= 'A' && nome[i] <= 'Z') ||
                     (nome[i] >= 'a' && nome[i] <= 'z');
        //se não for letra e não for espaço, nome inválido
        if (!Ehletra && nome[i] != ' ')
            throw std::invalid_argument("Nome invalido.");
        //se for espaço e o próximo caractere não for o último
        if (nome[i] == ' ' && i + 1 < nome.length()) {
    
            bool proximoEhLetra =
                (nome[i + 1] >= 'A' && nome[i + 1] <= 'Z') ||
                (nome[i + 1] >= 'a' && nome[i + 1] <= 'z');
            //se o proximo caractere não for letra, nome inválido
            if (!proximoEhLetra)
                throw std::invalid_argument("Nome invalido.");
        }
    }
}

void Nome::setNome(const std::string& nome) {
    validar(nome);
    this->nome = nome;
}


//CLasse Papel
const std::string Papel::GESTOR = "GESTOR";
const std::string Papel::DESENVOLVEDOR = "DESENVOLVEDOR";

void Papel::validar(const std::string& papel){
    if(papel != GESTOR && papel != DESENVOLVEDOR)
        throw std::invalid_argument("Papel invalido.");
}

void Papel::setPapel(const std::string& papel){
    validar(papel);
    this->papel = papel;
}


//Classe Texto
void Texto::validar(const std::string& texto){
    //texto vazio ou acima de 30 caracteres
    if(texto.empty() || texto.length()>MAXIMO)
        throw std::invalid_argument("Texto invalido");
    
    //primeiro caractere deve ser letra maiuscula, ultimo deve ser ponto
    if((texto.front() < 'A' || texto.front() > 'Z') || texto.back() != '.')
        throw std::invalid_argument("Texto invalido");

    for (std::size_t i = 0; i < texto.length(); i++) {

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
            throw std::invalid_argument("Texto invalido.");
        
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
                throw std::invalid_argument("Texto invalido.");

        }
    }
}

void Texto::setTexto(const std::string& texto){
    validar(texto);
    this->texto = texto;
}


//Classe Identificador
void Identificador::validar(const std::string& identificador){
    //deve conter 6 caracteres
    if(identificador.length() != TAMANHO)
        throw std::invalid_argument("Identificador invalido.");
    
    bool verifica = true;

    for(std::size_t i = 0; i < identificador.length(); i++){

        char caractere = identificador[i];

        if(i < 3){
            if((caractere <'A' || caractere > 'Z') &&
            (caractere < 'a' || caractere > 'z'))
                verifica = false;
        }
        else{
            if(caractere < '0' || caractere > '9')
               verifica = false;
        }

        if(!verifica)
            throw std::invalid_argument("Identificador invalido.");
    }

}

void Identificador::setIdentificador(const std::string& identificador){
    validar(identificador);
    this->identificador = identificador;
}


//Classe Email
void Email::validar(const std::string& email){
    //localiza o @ (deve existir exatamente um)
    std::size_t posArroba = email.find('@');
    if(posArroba == std::string::npos || email.find('@', posArroba + 1) != std::string::npos)
        throw std::invalid_argument("Email invalido.");

    std::string parteLocal = email.substr(0, posArroba);
    std::string dominio = email.substr(posArroba + 1);

    //valida parte local
    if(parteLocal.empty() || parteLocal.length() > MAXIMO_PARTE_LOCAL)
        throw std::invalid_argument("Email invalido.");

    if(parteLocal.front() == '.' || parteLocal.front() == '-' ||
       parteLocal.back() == '.' || parteLocal.back() == '-')
        throw std::invalid_argument("Email invalido.");

    for(std::size_t i = 0; i < parteLocal.length(); i++){
        char caractere = parteLocal[i];

        bool letra = (caractere >= 'a' && caractere <= 'z');
        bool digito = (caractere >= '0' && caractere <= '9');
        bool pontoOuHifen = (caractere == '.' || caractere == '-');

        if(!letra && !digito && !pontoOuHifen)
            throw std::invalid_argument("Email invalido.");

        //ponto ou hifen deve ser seguido por letra(s) ou digito(s)
        if(pontoOuHifen && i + 1 < parteLocal.length()){
            char proximo = parteLocal[i + 1];
            bool proximoValido = (proximo >= 'a' && proximo <= 'z') ||
                                  (proximo >= '0' && proximo <= '9');
            if(!proximoValido)
                throw std::invalid_argument("Email invalido.");
        }
    }

    //valida dominio
    if(dominio.empty() || dominio.length() > MAXIMO_DOMINIO)
        throw std::invalid_argument("Email invalido.");

    std::size_t inicio = 0;
    while(inicio <= dominio.length()){
        std::size_t fim = dominio.find('.', inicio);
        std::string parte = (fim == std::string::npos) ? dominio.substr(inicio)
                                              : dominio.substr(inicio, fim - inicio);

        //parte vazia significa ponto duplicado ou ponto no inicio/fim
        if(parte.empty())
            throw std::invalid_argument("Email invalido.");

        if(parte.front() == '-' || parte.back() == '-')
            throw std::invalid_argument("Email invalido.");

        for(char caractere : parte){
            bool letra = (caractere >= 'a' && caractere <= 'z');
            bool digito = (caractere >= '0' && caractere <= '9');
            bool hifen = (caractere == '-');

            if(!letra && !digito && !hifen)
                throw std::invalid_argument("Email invalido.");
        }

        if(fim == std::string::npos)
            break;
        inicio = fim + 1;
    }
}

void Email::setEmail(const std::string& email){
    validar(email);
    this->email = email;
}


//Classe Timestamp
bool Timestamp::ehBissexto(int ano){
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int Timestamp::indiceMes(const std::string& mes){
    static const std::string meses[12] = {
        "JAN", "FEV", "MAR", "ABR", "MAI", "JUN",
        "JUL", "AGO", "SET", "OUT", "NOV", "DEZ"
    };

    for(int i = 0; i < 12; i++)
        if(mes == meses[i])
            return i + 1;

    return -1;
}

int Timestamp::diasNoMes(int mes, int ano){
    static const int dias[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(mes == 2 && ehBissexto(ano))
        return 29;

    return dias[mes - 1];
}

void Timestamp::validar(const std::string& timestamp){
    //separa DIA-MES-ANO-HORARIO
    std::size_t p1 = timestamp.find('-');
    std::size_t p2 = (p1 == std::string::npos) ? std::string::npos : timestamp.find('-', p1 + 1);
    std::size_t p3 = (p2 == std::string::npos) ? std::string::npos : timestamp.find('-', p2 + 1);

    if(p1 == std::string::npos || p2 == std::string::npos || p3 == std::string::npos)
        throw std::invalid_argument("Timestamp invalido.");

    std::string diaStr = timestamp.substr(0, p1);
    std::string mesStr = timestamp.substr(p1 + 1, p2 - p1 - 1);
    std::string anoStr = timestamp.substr(p2 + 1, p3 - p2 - 1);
    std::string horaStr = timestamp.substr(p3 + 1);

    //valida dia (somente digitos, 1 ou 2 caracteres)
    if(diaStr.empty() || diaStr.length() > 2)
        throw std::invalid_argument("Timestamp invalido.");

    for(char caractere : diaStr)
        if(caractere < '0' || caractere > '9')
            throw std::invalid_argument("Timestamp invalido.");

    int dia = std::stoi(diaStr);

    //valida mes
    int mes = indiceMes(mesStr);
    if(mes == -1)
        throw std::invalid_argument("Timestamp invalido.");

    //valida ano (4 digitos, entre 2000 e 2099)
    if(anoStr.length() != 4)
        throw std::invalid_argument("Timestamp invalido.");

    for(char caractere : anoStr)
        if(caractere < '0' || caractere > '9')
            throw std::invalid_argument("Timestamp invalido.");

    int ano = std::stoi(anoStr);
    if(ano < ANO_MINIMO || ano > ANO_MAXIMO)
        throw std::invalid_argument("Timestamp invalido.");

    //valida dia dentro do mes/ano (considerando anos bissextos)
    if(dia < 1 || dia > diasNoMes(mes, ano))
        throw std::invalid_argument("Timestamp invalido.");

    //valida horario HH:MM
    if(horaStr.length() != 5 || horaStr[2] != ':')
        throw std::invalid_argument("Timestamp invalido.");

    std::string horaP = horaStr.substr(0, 2);
    std::string minutoP = horaStr.substr(3, 2);

    for(char caractere : horaP)
        if(caractere < '0' || caractere > '9')
            throw std::invalid_argument("Timestamp invalido.");

    for(char caractere : minutoP)
        if(caractere < '0' || caractere > '9')
            throw std::invalid_argument("Timestamp invalido.");

    int hora = std::stoi(horaP);
    int minuto = std::stoi(minutoP);

    if(hora < 0 || hora > 23 || minuto < 0 || minuto > 59)
        throw std::invalid_argument("Timestamp invalido.");
}

void Timestamp::setTimestamp(const std::string& timestamp){
    validar(timestamp);
    this->timestamp = timestamp;
}

#endif // DOMINIOS_CPP_INCLUDED