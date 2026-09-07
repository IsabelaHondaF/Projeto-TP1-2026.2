#ifndef ENTIDADES_CPP_INCLUDED
#define ENTIDADES_CPP_INCLUDED
#include "../Headers/entidades.hpp"

//Classe Pessoa
void Pessoa::setEmail(const std::string& email){
    this->email.setEmail(email);
}

void Pessoa::setNome(const std::string& nome){
    this->nome.setNome(nome);
}

void Pessoa::setSenha(const std::string& senha){
    this->senha.setSenha(senha);
}

void Pessoa::setPapel(const std::string& papel){
    this->papel.setPapel(papel);
}


//Classe Projeto
void Projeto::setIdentificador(const std::string& identificador){
    this->identificador.setIdentificador(identificador);
}

void Projeto::setNome(const std::string& nome){
    this->nome.setNome(nome);
}

void Projeto::setDescricao(const std::string& descricao){
    this->descricao.setTexto(descricao);
}

void Projeto::setInicio(const std::string& inicio){
    this->inicio.setTimestamp(inicio);
}

void Projeto::setTermino(const std::string& termino){
    this->termino.setTimestamp(termino);
}


//Classe Quadro
void Quadro::setIdentificador(const std::string& identificador){
    this->identificador.setIdentificador(identificador);
}

void Quadro::setNome(const std::string& nome){
    this->nome.setNome(nome);
}

void Quadro::setLimite(int limite){
    this->limite.setValor(limite);
}


//Classe CartaoDeAtividade
void CartaoDeAtividade::setIdentificador(const std::string& identificador){
    this->identificador.setIdentificador(identificador);
}

void CartaoDeAtividade::setNome(const std::string& nome){
    this->nome.setNome(nome);
}

void CartaoDeAtividade::setDescricao(const std::string& descricao){
    this->descricao.setTexto(descricao);
}

void CartaoDeAtividade::setPrioridade(const std::string& prioridade){
    this->prioridade.setPrioridade(prioridade);
}

void CartaoDeAtividade::setEstado(const std::string& estado){
    this->estado.setEstado(estado);
}

void CartaoDeAtividade::setTamanho(const std::string& tamanho){
    this->tamanho.setTamanho(tamanho);
}

void CartaoDeAtividade::setEntrada(const std::string& entrada){
    this->entrada.setTimestamp(entrada);
}

void CartaoDeAtividade::setInicio(const std::string& inicio){
    this->inicio.setTimestamp(inicio);
}

void CartaoDeAtividade::setTermino(const std::string& termino){
    this->termino.setTimestamp(termino);
}

#endif // ENTIDADES_CPP_INCLUDED