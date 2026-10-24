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
    /**
     * @brief Define o endereço de email (chave primária) da pessoa.
     * @param[in] email String com o email no formato válido de domínio.
     * @throws std::invalid_argument Se o formato do email for inválido.
     */
    void setEmail(const std::string& email);

    /**
     * @brief Retorna o endereço de email da pessoa.
     * @return String com o email cadastrado.
     */
    std::string getEmail() const;

    /**
     * @brief Define o nome da pessoa.
     * @param[in] nome String com o nome (até 15 caracteres válidos).
     * @throws std::invalid_argument Se o nome não atender às regras de domínio.
     */
    void setNome(const std::string& nome);

    /**
     * @brief Retorna o nome da pessoa.
     * @return String com o nome da pessoa.
     */
    std::string getNome() const;

    /**
     * @brief Define a senha de acesso da conta da pessoa.
     * @param[in] senha String de 5 caracteres alfanuméricos com pelo menos 1 letra e 1 dígito.
     * @throws std::invalid_argument Se a senha for inválida.
     */
    void setSenha(const std::string& senha);

    /**
     * @brief Retorna a senha da pessoa.
     * @return String com a senha armazenada.
     */
    std::string getSenha() const;

    /**
     * @brief Define o papel de atuação da pessoa (GESTOR ou DESENVOLVEDOR).
     * @param[in] papel String com o papel a ser atribuído.
     * @throws std::invalid_argument Se o papel não for GESTOR ou DESENVOLVEDOR.
     */
    void setPapel(const std::string& papel);

    /**
     * @brief Retorna o papel da pessoa.
     * @return String com o papel da pessoa.
     */
    std::string getPapel() const;
};

inline std::string Pessoa::getEmail() const{
    return email.getEmail();
}

inline std::string Pessoa::getNome() const{
    return nome.getNome();
}

inline std::string Pessoa::getSenha() const{
    return senha.getSenha();
}

inline std::string Pessoa::getPapel() const{
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
    /**
     * @brief Define o código identificador (chave primária) do projeto.
     * @param[in] identificador String de 6 caracteres (3 letras seguidas de 3 dígitos).
     * @throws std::invalid_argument Se o formato do identificador for inválido.
     */
    void setIdentificador(const std::string& identificador);

    /**
     * @brief Retorna o código identificador do projeto.
     * @return String com o identificador do projeto.
     */
    std::string getIdentificador() const;

    /**
     * @brief Define o nome do projeto.
     * @param[in] nome String com o nome do projeto (até 15 caracteres válidos).
     * @throws std::invalid_argument Se o nome for inválido segundo o domínio.
     */
    void setNome(const std::string& nome);

    /**
     * @brief Retorna o nome do projeto.
     * @return String com o nome do projeto.
     */
    std::string getNome() const;

    /**
     * @brief Define a descrição textual do projeto.
     * @param[in] descricao String com o texto descritivo (até 30 caracteres válidos).
     * @throws std::invalid_argument Se a descrição for inválida.
     */
    void setDescricao(const std::string& descricao);

    /**
     * @brief Retorna a descrição do projeto.
     * @return String com a descrição do projeto.
     */
    std::string getDescricao() const;

    /**
     * @brief Define o instante de início do projeto.
     * @param[in] inicio String no formato DIA-MES-ANO-HORARIO válido.
     * @throws std::invalid_argument Se o timestamp de início for inválido.
     */
    void setInicio(const std::string& inicio);

    /**
     * @brief Retorna o instante de início do projeto.
     * @return String com o timestamp de início.
     */
    std::string getInicio() const;

    /**
     * @brief Define o instante de término estimado do projeto.
     * @param[in] termino String no formato DIA-MES-ANO-HORARIO válido.
     * @throws std::invalid_argument Se o timestamp de término for inválido.
     */
    void setTermino(const std::string& termino);

    /**
     * @brief Retorna o instante de término estimado do projeto.
     * @return String com o timestamp de término.
     */
    std::string getTermino() const;
};

inline std::string Projeto::getIdentificador() const{
    return identificador.getIdentificador();
}

inline std::string Projeto::getNome() const{
    return nome.getNome();
}

inline std::string Projeto::getDescricao() const{
    return descricao.getTexto();
}

inline std::string Projeto::getInicio() const{
    return inicio.getTimestamp();
}

inline std::string Projeto::getTermino() const{
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
    /**
     * @brief Define o código identificador (chave primária) do quadro.
     * @param[in] identificador String de 6 caracteres (3 letras seguidas de 3 dígitos).
     * @throws std::invalid_argument Se o formato do identificador for inválido.
     */
    void setIdentificador(const std::string& identificador);

    /**
     * @brief Retorna o código identificador do quadro.
     * @return String com o identificador do quadro.
     */
    std::string getIdentificador() const;

    /**
     * @brief Define o nome do quadro Kanban.
     * @param[in] nome String com o nome do quadro (até 15 caracteres válidos).
     * @throws std::invalid_argument Se o nome for inválido segundo o domínio.
     */
    void setNome(const std::string& nome);

    /**
     * @brief Retorna o nome do quadro.
     * @return String com o nome do quadro.
     */
    std::string getNome() const;

    /**
     * @brief Define o limite de cartões simultâneos na coluna FAZENDO (WIP).
     * @param[in] limite Valor inteiro entre 1 e 25.
     * @throws std::invalid_argument Se o limite estiver fora da faixa permitida.
     */
    void setLimite(int limite);

    /**
     * @brief Retorna o limite de WIP do quadro.
     * @return Inteiro com o limite de trabalho em andamento.
     */
    int getLimite() const;
};

inline std::string Quadro::getIdentificador() const{
    return identificador.getIdentificador();
}

inline std::string Quadro::getNome() const{
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
    /**
     * @brief Define o código identificador (chave primária) do cartão.
     * @param[in] identificador String de 6 caracteres (3 letras seguidas de 3 dígitos).
     * @throws std::invalid_argument Se o formato do identificador for inválido.
     */
    void setIdentificador(const std::string& identificador);

    /**
     * @brief Retorna o código identificador do cartão.
     * @return String com o identificador do cartão.
     */
    std::string getIdentificador() const;

    /**
     * @brief Define o nome do cartão de atividade.
     * @param[in] nome String com o nome da atividade (até 15 caracteres válidos).
     * @throws std::invalid_argument Se o nome for inválido.
     */
    void setNome(const std::string& nome);

    /**
     * @brief Retorna o nome do cartão de atividade.
     * @return String com o nome do cartão.
     */
    std::string getNome() const;

    /**
     * @brief Define a descrição textual do cartão.
     * @param[in] descricao String com o texto descritivo (até 30 caracteres válidos).
     * @throws std::invalid_argument Se a descrição for inválida.
     */
    void setDescricao(const std::string& descricao);

    /**
     * @brief Retorna a descrição do cartão.
     * @return String com o texto descritivo.
     */
    std::string getDescricao() const;

    /**
     * @brief Define o nível de prioridade da atividade (ALTA, MEDIA ou BAIXA).
     * @param[in] prioridade String com o nível de prioridade.
     * @throws std::invalid_argument Se o valor for inválido.
     */
    void setPrioridade(const std::string& prioridade);

    /**
     * @brief Retorna o nível de prioridade da atividade.
     * @return String com o nível de prioridade (ALTA, MEDIA ou BAIXA).
     */
    std::string getPrioridade() const;

    /**
     * @brief Define a etapa do fluxo Kanban (A FAZER, FAZENDO ou FEITO).
     * @param[in] estado String com o estado da atividade.
     * @throws std::invalid_argument Se o estado for inválido.
     */
    void setEstado(const std::string& estado);

    /**
     * @brief Retorna o estado atual da atividade no quadro Kanban.
     * @return String com o estado (A FAZER, FAZENDO ou FEITO).
     */
    std::string getEstado() const;

    /**
     * @brief Define a dimensão estimada do trabalho (GRANDE, MEDIO ou PEQUENO).
     * @param[in] tamanho String com a dimensão do trabalho.
     * @throws std::invalid_argument Se o tamanho for inválido.
     */
    void setTamanho(const std::string& tamanho);

    /**
     * @brief Retorna a dimensão estimada da atividade.
     * @return String com o tamanho (GRANDE, MEDIO ou PEQUENO).
     */
    std::string getTamanho() const;

    /**
     * @brief Define o timestamp de entrada do cartão no quadro (coluna A FAZER).
     * @param[in] entrada String no formato DIA-MES-ANO-HORARIO válido.
     * @throws std::invalid_argument Se o timestamp for inválido.
     */
    void setEntrada(const std::string& entrada);

    /**
     * @brief Retorna o instante de entrada da atividade no quadro.
     * @return String com o timestamp de entrada.
     */
    std::string getEntrada() const;

    /**
     * @brief Define o timestamp de início da execução (entrada em FAZENDO).
     * @param[in] inicio String no formato DIA-MES-ANO-HORARIO válido.
     * @throws std::invalid_argument Se o timestamp for inválido.
     */
    void setInicio(const std::string& inicio);

    /**
     * @brief Retorna o instante de início da execução da atividade.
     * @return String com o timestamp de início.
     */
    std::string getInicio() const;

    /**
     * @brief Define o timestamp de conclusão da atividade (entrada em FEITO).
     * @param[in] termino String no formato DIA-MES-ANO-HORARIO válido.
     * @throws std::invalid_argument Se o timestamp for inválido.
     */
    void setTermino(const std::string& termino);

    /**
     * @brief Retorna o instante de conclusão da atividade.
     * @return String com o timestamp de conclusão.
     */
    std::string getTermino() const;
};

inline std::string CartaoDeAtividade::getIdentificador() const{
    return identificador.getIdentificador();
}

inline std::string CartaoDeAtividade::getNome() const{
    return nome.getNome();
}

inline std::string CartaoDeAtividade::getDescricao() const{
    return descricao.getTexto();
}

inline std::string CartaoDeAtividade::getPrioridade() const{
    return prioridade.getPrioridade();
}

inline std::string CartaoDeAtividade::getEstado() const{
    return estado.getEstado();
}

inline std::string CartaoDeAtividade::getTamanho() const{
    return tamanho.getTamanho();
}

inline std::string CartaoDeAtividade::getEntrada() const{
    return entrada.getTimestamp();
}

inline std::string CartaoDeAtividade::getInicio() const{
    return inicio.getTimestamp();
}

inline std::string CartaoDeAtividade::getTermino() const{
    return termino.getTimestamp();
}

#endif // ENTIDADES_HPP_INCLUDED