#ifndef ENTIDADES_CPP_INCLUDED
#define ENTIDADES_CPP_INCLUDED
#include "../Headers/entidades.hpp"

//Classe Pessoa
void Pessoa::setEmail(const string& email){
    this->email.setEmail(email);
}

void Pessoa::setNome(const string& nome){
    this->nome.setNome(nome);
}

void Pessoa::setSenha(const string& senha){
    this->senha.setSenha(senha);
}

void Pessoa::setPapel(const string& papel){
    this->papel.setPapel(papel);
}


//Classe Projeto
void Projeto::setIdentificador(const string& identificador){
    this->identificador.setIdentificador(identificador);
}

void Projeto::setNome(const string& nome){
    this->nome.setNome(nome);
}

void Projeto::setDescricao(const string& descricao){
    this->descricao.setTexto(descricao);
}

void Projeto::setInicio(const string& inicio){
    this->inicio.setTimestamp(inicio);
}

void Projeto::setTermino(const string& termino){
    this->termino.setTimestamp(termino);
}


//Classe Quadro
void Quadro::setIdentificador(const string& identificador){
    this->identificador.setIdentificador(identificador);
}

void Quadro::setNome(const string& nome){
    this->nome.setNome(nome);
}

void Quadro::setLimite(int limite){
    this->limite.setValor(limite);
}


//Classe CartaoDeAtividade
void CartaoDeAtividade::setIdentificador(const string& identificador){
    this->identificador.setIdentificador(identificador);
}

void CartaoDeAtividade::setNome(const string& nome){
    this->nome.setNome(nome);
}

void CartaoDeAtividade::setDescricao(const string& descricao){
    this->descricao.setTexto(descricao);
}

void CartaoDeAtividade::setPrioridade(const string& prioridade){
    this->prioridade.setPrioridade(prioridade);
}

void CartaoDeAtividade::setEstado(const string& estado){
    this->estado.setEstado(estado);
}

void CartaoDeAtividade::setTamanho(const string& tamanho){
    this->tamanho.setTamanho(tamanho);
}

void CartaoDeAtividade::setEntrada(const string& entrada){
    this->entrada.setTimestamp(entrada);
}

void CartaoDeAtividade::setInicio(const string& inicio){
    this->inicio.setTimestamp(inicio);
}

void CartaoDeAtividade::setTermino(const string& termino){
    this->termino.setTimestamp(termino);
}

#endif // ENTIDADES_CPP_INCLUDED