#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED
#include <string>
#include <stdexcept>

/**
 * @brief Representa a quantidade máxima de atividades simultâneas na coluna FAZENDO.
 *
 * Aceita números inteiros de 1 a 25, inclusive. Esse valor corresponde ao
 * limite de trabalho em andamento de um quadro Kanban.
 * A verificação da quantidade de cartões durante uma movimentação cabe ao serviço.
 */
class Limite {
private:
    static const int MINIMO = 1;
    static const int MAXIMO = 25;
    int valor;
    void validar(int);

public:
    /**
     * @brief Valida e armazena a quantidade máxima de atividades em andamento.
     *
     * @par Parâmetro de entrada
     * Número inteiro entre 1 e 25, inclusive.
     *
     * @throws std::invalid_argument Se o número for menor que 1 ou maior que 25.
     */
    void setValor(int);
    /**
     * @brief Consulta a quantidade máxima de atividades em andamento armazenada.
     *
     * @return Número inteiro definido como limite.
     */
    int getValor() const;
};

inline int Limite::getValor() const{
    return valor;
}

/**
 * @brief Armazena a sequência de caracteres usada para comprovar o acesso a uma conta.
 *
 * A sequência deve conter exatamente cinco caracteres, formados por letras
 * de A a Z ou de a a z, e dígitos de 0 a 9. É obrigatória a presença de pelo
 * menos uma letra e um dígito. Espaços e sinais de pontuação não são aceitos.
 */
class Senha{
private:
    std::string senha;
    void validar(const std::string&);
    static const int caracteres = 5;

public:
    /**
     * @brief Valida e armazena a credencial que será utilizada na autenticação.
     *
     * @par Parâmetro de entrada
     * Sequência de cinco caracteres, com pelo menos uma letra
     * de A a Z ou de a a z, e um dígito de 0 a 9.
     *
     * @throws std::invalid_argument Se o comprimento não for cinco, houver
     * caractere não permitido ou faltar uma letra ou um dígito.
     */
    void setSenha(const std::string&);
    /**
     * @brief Consulta a sequência armazenada para autenticação da conta.
     *
     * @return Cópia da senha atualmente armazenada.
     */
    std::string getSenha() const;
};

inline std::string Senha::getSenha() const{
    return senha;
}


/**
 * @brief Identifica a etapa de execução de uma atividade no quadro Kanban.
 *
 * Aceita A FAZER para trabalho ainda não iniciado, FAZENDO para trabalho
 * em andamento e FEITO para trabalho concluído. Os valores devem ser
 * escritos exatamente dessa forma, com letras maiúsculas.
 * A validação verifica o valor informado.
 */
class Estado{
private:
    static const std::string A_FAZER;
    static const std::string FAZENDO;
    static const std::string FEITO;
    std::string estado;
    void validar(const std::string&);

public:
    /**
     * @brief Valida e armazena a etapa de execução associada à atividade.
     *
     * @par Parâmetro de entrada
     * Texto A FAZER, FAZENDO ou FEITO, escrito exatamente como indicado.
     *
     * @throws std::invalid_argument Se o texto não corresponder a uma das três etapas.
     */
    void setEstado(const std::string&);
    /**
     * @brief Consulta a etapa de execução registrada para a atividade.
     *
     * @return Cópia do texto armazenado que identifica o estado da atividade.
     */
    std::string getEstado() const;
};

inline std::string Estado::getEstado() const{
    return estado;
}


/**
 * @brief Classifica a preferência de atendimento de uma atividade.
 *
 * Aceita os níveis ALTA, MEDIA e BAIXA. Os valores devem ser escritos
 * exatamente dessa forma, com letras maiúsculas e sem acentuação.
 */
class Prioridade{
private:
    static const std::string ALTA;
    static const std::string MEDIA;
    static const std::string BAIXA;
    std::string prioridade;
    void validar(const std::string&);

public:
    /**
     * @brief Valida e armazena o nível de preferência atribuído à atividade.
     *
     * @par Parâmetro de entrada
     * Texto ALTA, MEDIA ou BAIXA, escrito exatamente como indicado.
     *
     * @throws std::invalid_argument Se o texto não corresponder a um dos níveis aceitos.
     */
    void setPrioridade(const std::string&);
    /**
     * @brief Consulta o nível de preferência atribuído à atividade.
     *
     * @return Cópia do texto armazenado que classifica a preferência da atividade.
     */
    std::string getPrioridade() const;
};

inline std::string Prioridade::getPrioridade() const{
    return prioridade;
}


/**
 * @brief Classifica a dimensão do trabalho de uma atividade.
 *
 * Aceita as categorias GRANDE, MEDIO e PEQUENO. Os valores devem ser
 * escritos exatamente dessa forma, com letras maiúsculas e sem acentuação.
 */
class Tamanho{
private:
    static const std::string GRANDE;
    static const std::string MEDIO;
    static const std::string PEQUENO;
    std::string tamanho;
    void validar(const std::string&);

public:
    /**
     * @brief Valida e armazena a categoria da dimensão estimada do trabalho.
     *
     * @par Parâmetro de entrada
     * Texto GRANDE, MEDIO ou PEQUENO, escrito exatamente como indicado.
     *
     * @throws std::invalid_argument Se o texto não corresponder a uma das categorias aceitas.
     */
    void setTamanho(const std::string&);
    /**
     * @brief Consulta a categoria atribuída à dimensão estimada do trabalho.
     *
     * @return Cópia do texto armazenado que classifica a dimensão da atividade.
     */
    std::string getTamanho() const;
};

inline std::string Tamanho::getTamanho() const{
    return tamanho;
}


/**
 * @brief Armazena o nome de uma pessoa, projeto, quadro ou atividade.
 *
 * Aceita de 1 a 15 caracteres, compostos por letras de A a Z ou de a a z
 * e espaços em branco. Cada espaço deve ser seguido por uma letra.
 * Não são aceitos espaços no início ou no fim, espaços consecutivos,
 * dígitos ou sinais de pontuação.
 */
class Nome {
private:
    static const int MAXIMO = 15;
    std::string nome;
    void validar(const std::string&);

public:
    /**
     * @brief Valida e armazena o nome utilizado para reconhecer uma entidade.
     *
     * @par Parâmetro de entrada
     * Texto de 1 a 15 caracteres, contendo apenas letras de A a Z ou de a a z
     * e espaços isolados entre letras, sem espaços nas extremidades.
     *
     * @throws std::invalid_argument Se o texto estiver vazio, exceder 15 caracteres
     * ou desrespeitar as regras de caracteres e espaços.
     */
    void setNome(const std::string&);
    /**
     * @brief Consultao nome atualmente armazenado.
     *
     * @return Cópia do texto utilizado para reconhecer a entidade pelo nome.
     */
    std::string getNome() const;
};

inline std::string Nome::getNome() const {
    return nome;
}


/**
 * @brief Identifica a função de um usuário para a definição de suas permissões no sistema.
 *
 * Aceita GESTOR ou DESENVOLVEDOR, escritos exatamente dessa forma.
 * Os serviços utilizam essa classificação para verificar quais operações
 * o usuário pode realizar.
 */
class Papel{
private:
    static const std::string GESTOR;
    static const std::string DESENVOLVEDOR;
    std::string papel;
    void validar(const std::string&);

public:
    /**
     * @brief Valida e armazena a função atribuída ao usuário.
     *
     * @par Parâmetro de entrada
     * Texto GESTOR ou DESENVOLVEDOR, escrito exatamente como indicado.
     *
     * @throws std::invalid_argument Se o texto não corresponder a uma das funções aceitas.
     */
    void setPapel(const std::string&);
    /**
     * @brief Consulta a função utilizada pelos serviços para verificar permissões.
     *
     * @return Cópia do texto armazenado que classifica a função do usuário.
     */
    std::string getPapel() const;
};

inline std::string Papel::getPapel() const{
    return papel;
}


/**
 * @brief Armazena uma descrição curta de um projeto ou de uma atividade.
 *
 * Aceita até 30 caracteres, com letra maiúscula de A a Z no início e ponto
 * no final. Os demais caracteres podem ser letras de A a Z ou de a a z,
 * dígitos de 0 a 9, espaços em branco e os sinais vírgula, ponto e vírgula,
 * ponto, dois-pontos, interrogação e exclamação.
 * Dois sinais de pontuação não podem aparecer consecutivamente.
 */
class Texto{
private:
    static const int MAXIMO = 30;
    std::string texto;
    void validar(const std::string&);

public:
    /**
     * @brief Valida e armazena a descrição de uma entidade.
     *
     * @par Parâmetro de entrada
     * Descrição com até 30 caracteres, iniciada por letra maiúscula de A a Z
     * e terminada por ponto. São permitidos letras de A a Z ou de a a z,
     * dígitos, espaços e os sinais vírgula, ponto e vírgula, ponto, dois-pontos,
     * interrogação e exclamação, sem sinais de pontuação consecutivos.
     *
     * @throws std::invalid_argument Se o texto estiver vazio, exceder 30 caracteres
     * ou desrespeitar as regras de caracteres, início, término ou pontuação.
     */
    void setTexto(const std::string&);
    /**
     * @brief Consulta o conteúdo descritivo atualmente armazenado.
     *
     * @return Cópia da descrição textual associada à entidade.
     */
    std::string getTexto() const;
};

inline std::string Texto::getTexto() const{
    return texto;
}


/**
 * @brief Armazena o código utilizado como chave primária de projetos, quadros e atividades.
 *
 * O código deve conter exatamente seis caracteres: três letras de A a Z
 * ou de a a z, seguidas por três dígitos de 0 a 9.
 * A classe valida o formato e a unicidade entre registros.
 */
class Identificador{
private:
    static const int TAMANHO = 6;
    std::string identificador;
    void validar(const std::string&);

public:
    /**
     * @brief Valida e armazena o código utilizado para localizar uma entidade.
     *
     * @par Parâmetro de entrada
     * Código de seis caracteres: três letras de A a Z ou de a a z, seguidas
     * por três dígitos de 0 a 9.
     *
     * @throws std::invalid_argument Se o comprimento não for seis ou se as posições
     * reservadas às letras e aos dígitos contiverem caracteres incorretos.
     */
    void setIdentificador(const std::string&);
    /**
     * @brief Consulta o código utilizado como chave primária de uma entidade.
     *
     * @return Cópia do código atualmente armazenado.
     */
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