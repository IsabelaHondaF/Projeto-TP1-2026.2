#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED
#include <string>
#include <stdexcept>

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
    std::string senha;
    void validar(const std::string&);
    static const int caracteres = 5;

public:
    void setSenha(const std::string&);
    std::string getSenha() const;
};

inline std::string Senha::getSenha() const{
    return senha;
}


class Estado{
private:
    static const std::string A_FAZER;
    static const std::string FAZENDO;
    static const std::string FEITO;
    std::string estado;
    void validar(const std::string&);

public:
    void setEstado(const std::string&);
    std::string getEstado() const;
};

inline std::string Estado::getEstado() const{
    return estado;
}


class Prioridade{
private:
    static const std::string ALTA;
    static const std::string MEDIA;
    static const std::string BAIXA;
    std::string prioridade;
    void validar(const std::string&);

public:
    void setPrioridade(const std::string&);
    std::string getPrioridade() const;
};

inline std::string Prioridade::getPrioridade() const{
    return prioridade;
}


class Tamanho{
private:
    static const std::string GRANDE;
    static const std::string MEDIO;
    static const std::string PEQUENO;
    std::string tamanho;
    void validar(const std::string&);

public:
    void setTamanho(const std::string&);
    std::string getTamanho() const;
};

inline std::string Tamanho::getTamanho() const{
    return tamanho;
}


class Nome {
private:
    static const int MAXIMO = 15;
    std::string nome;
    void validar(const std::string&);

public:
    void setNome(const std::string&);
    std::string getNome() const;
};

inline std::string Nome::getNome() const {
    return nome;
}


class Papel{
private:
    static const std::string GESTOR;
    static const std::string DESENVOLVEDOR;
    std::string papel;
    void validar(const std::string&);

public:
    void setPapel(const std::string&);
    std::string getPapel() const;
};

inline std::string Papel::getPapel() const{
    return papel;
}


class Texto{
private:
    static const int MAXIMO = 30;
    std::string texto;
    void validar(const std::string&);

public:
    void setTexto(const std::string&);
    std::string getTexto() const;
};

inline std::string Texto::getTexto() const{
    return texto;
}


class Identificador{
private:
    static const int TAMANHO = 6;
    std::string identificador;
    void validar(const std::string&);

public:
    void setIdentificador(const std::string&);
    std::string getIdentificador() const;
};

inline std::string Identificador::getIdentificador() const{
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
    std::string email;
    void validar(const std::string&);

public:
    /** Define o email, validando o formato; lanca excecao se invalido. */
    void setEmail(const std::string&);
    /** Retorna o valor atual do email. */
    std::string getEmail() const;
};

inline std::string Email::getEmail() const{
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
    std::string timestamp;
    void validar(const std::string&);
    static bool ehBissexto(int ano);
    static int diasNoMes(int mes, int ano);
    static int indiceMes(const std::string& mes);

public:
    /** Define o timestamp, validando o formato; lanca excecao se invalido. */
    void setTimestamp(const std::string&);
    /** Retorna o valor atual do timestamp. */
    std::string getTimestamp() const;
};

inline std::string Timestamp::getTimestamp() const{
    return timestamp;
}

#endif // DOMINIOS_HPP_INCLUDED