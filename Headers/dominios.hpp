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


class Papel{
private:
    static const string GESTOR;
    static const string DESENVOLVEDOR;
    string papel;
    void validar(const string&);

public:
    void setPapel(const string&);
    string getPapel() const;
};

inline string Papel::getPapel() const{
    return papel;
}


class Texto{
private:
    static const int MAXIMO = 30;
    string texto;
    void validar(const string&);

public:
    void setTexto(const string&);
    string getTexto() const;
};

inline string Texto::getTexto() const{
    return texto;
}


class Identificador{
private:
    static const int TAMANHO = 6;
    string identificador;
    void validar(const string&);

public:
    void setIdentificador(const string&);
    string getIdentificador() const;
};

inline string Identificador::getIdentificador() const{
    return identificador;
}


/**
 * Representa o dominio EMAIL, no formato parte-local@dominio.
 * Parte local: letras (a-z), digitos (0-9), ponto (.) ou hifen (-);
 * nao pode iniciar/terminar com ponto ou hifen; ponto/hifen deve ser
 * seguido por letra(s) ou digito(s); no maximo 64 caracteres.
 * Dominio: uma ou mais partes separadas por ponto, cada parte com
 * letras (a-z), digitos (0-9) ou hifen (-), sem iniciar/terminar com
 * hifen; no maximo 255 caracteres.
 */
class Email{
private:
    static const int MAXIMO_PARTE_LOCAL = 64;
    static const int MAXIMO_DOMINIO = 255;
    string email;
    void validar(const string&);

public:
    /** Define o email, validando o formato; lanca excecao se invalido. */
    void setEmail(const string&);
    /** Retorna o valor atual do email. */
    string getEmail() const;
};

inline string Email::getEmail() const{
    return email;
}


/**
 * Representa o dominio TIMESTAMP, no formato DIA-MES-ANO-HORARIO.
 * DIA: numero de 1 a 31 (validado conforme o mes e ano, incluindo
 * anos bissextos). MES: sigla de tres letras (JAN, FEV, ..., DEZ).
 * ANO: numero de 2000 a 2099. HORARIO: HH:MM de 00:00 a 23:59.
 */
class Timestamp{
private:
    static const int ANO_MINIMO = 2000;
    static const int ANO_MAXIMO = 2099;
    string timestamp;
    void validar(const string&);
    static bool ehBissexto(int ano);
    static int diasNoMes(int mes, int ano);
    static int indiceMes(const string& mes);

public:
    /** Define o timestamp, validando o formato; lanca excecao se invalido. */
    void setTimestamp(const string&);
    /** Retorna o valor atual do timestamp. */
    string getTimestamp() const;
};

inline string Timestamp::getTimestamp() const{
    return timestamp;
}

#endif // DOMINIOS_HPP_INCLUDED