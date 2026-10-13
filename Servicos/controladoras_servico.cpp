#include "../Headers/controladoras_servico.hpp"

#include <exception>
#include <string>
#include <vector>

namespace {

bool usuarioCadastrado(const ContainerPessoas& pessoas, const std::string& email) {
    Pessoa pessoa;
    return pessoas.obter(email, pessoa);
}

bool usuarioTemPapel(const ContainerPessoas& pessoas, const std::string& email,
                     const std::string& papel) {
    Pessoa pessoa;
    return pessoas.obter(email, pessoa) && pessoa.getPapel() == papel;
}

bool ehGestorDoProjeto(const ContainerPessoas& pessoas,
                       const ContainerProjetos& projetos,
                       const std::string& email,
                       const std::string& idProjeto) {
    std::string gestor;
    return usuarioTemPapel(pessoas, email, "GESTOR") &&
           projetos.gestorDoProjeto(idProjeto, gestor) && gestor == email;
}

bool ehGestorDoQuadro(const ContainerPessoas& pessoas,
                      const ContainerProjetos& projetos,
                      const ContainerQuadros& quadros,
                      const std::string& email,
                      const std::string& idQuadro) {
    std::string idProjeto;
    return quadros.projetoDoQuadro(idQuadro, idProjeto) &&
           ehGestorDoProjeto(pessoas, projetos, email, idProjeto);
}

bool podeOperarCartao(const ContainerPessoas& pessoas,
                      const ContainerProjetos& projetos,
                      const ContainerQuadros& quadros,
                      const ContainerCartoes& cartoes,
                      const std::string& email,
                      const std::string& idCartao) {
    CartaoDeAtividade cartao;
    std::string idQuadro;
    std::string desenvolvedor;
    if (!usuarioCadastrado(pessoas, email) ||
        !cartoes.obter(idCartao, cartao, &idQuadro, &desenvolvedor)) {
        return false;
    }

    if (ehGestorDoQuadro(pessoas, projetos, quadros, email, idQuadro))
        return true;

    return email == desenvolvedor &&
           usuarioTemPapel(pessoas, email, "DESENVOLVEDOR");
}

bool ehGestorDoCartao(const ContainerPessoas& pessoas,
                      const ContainerProjetos& projetos,
                      const ContainerQuadros& quadros,
                      const ContainerCartoes& cartoes,
                      const std::string& email,
                      const std::string& idCartao) {
    CartaoDeAtividade cartao;
    std::string idQuadro;
    return cartoes.obter(idCartao, cartao, &idQuadro) &&
           ehGestorDoQuadro(pessoas, projetos, quadros, email, idQuadro);
}

int contarWip(const ContainerCartoes& cartoes, const std::string& idQuadro) {
    const std::vector<CartaoDeAtividade> itens = cartoes.listarCartoesDoQuadro(idQuadro);
    int wip = 0;
    for (std::size_t i = 0; i < itens.size(); ++i)
        if (itens[i].getEstado() == "FAZENDO") ++wip;
    return wip;
}

bool ehAnoBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int diasNoMes(int mes, int ano) {
    static const int dias[12] = {31, 28, 31, 30, 31, 30,
                                  31, 31, 30, 31, 30, 31};
    if (mes == 2 && ehAnoBissexto(ano)) return 29;
    if (mes < 1 || mes > 12) return 0;
    return dias[mes - 1];
}

/**
 * Converte DIA-MES-ANO-HH:MM para minutos contados desde 01-JAN-2000 00:00.
 * Retorna false para texto vazio ou malformado. A validação principal do
 * formato continua sendo responsabilidade da classe de domínio Timestamp.
 */
bool timestampEmMinutos(const std::string& texto, long long& resultado) {
    const std::size_t p1 = texto.find('-');
    const std::size_t p2 = p1 == std::string::npos ? std::string::npos : texto.find('-', p1 + 1);
    const std::size_t p3 = p2 == std::string::npos ? std::string::npos : texto.find('-', p2 + 1);
    if (p1 == std::string::npos || p2 == std::string::npos || p3 == std::string::npos)
        return false;

    const std::string diaTexto = texto.substr(0, p1);
    const std::string mesTexto = texto.substr(p1 + 1, p2 - p1 - 1);
    const std::string anoTexto = texto.substr(p2 + 1, p3 - p2 - 1);
    const std::string horaTexto = texto.substr(p3 + 1);

    if (diaTexto.empty() || anoTexto.size() != 4 || horaTexto.size() != 5 ||
        horaTexto[2] != ':' || mesTexto.size() != 3) return false;

    int dia = 0, mes = 0, ano = 0, hora = 0, minuto = 0;
    try {
        std::size_t usados = 0;
        dia = std::stoi(diaTexto, &usados);
        if (usados != diaTexto.size()) return false;
        ano = std::stoi(anoTexto, &usados);
        if (usados != anoTexto.size()) return false;
        hora = std::stoi(horaTexto.substr(0, 2), &usados);
        if (usados != 2) return false;
        minuto = std::stoi(horaTexto.substr(3, 2), &usados);
        if (usados != 2) return false;
    } catch (const std::exception&) {
        return false;
    }

    static const char* meses[12] = {"JAN", "FEV", "MAR", "ABR", "MAI", "JUN",
                                    "JUL", "AGO", "SET", "OUT", "NOV", "DEZ"};
    for (int i = 0; i < 12; ++i)
        if (mesTexto == meses[i]) mes = i + 1;

    if (ano < 2000 || ano > 2099 || mes == 0 || dia < 1 ||
        dia > diasNoMes(mes, ano) || hora < 0 || hora > 23 ||
        minuto < 0 || minuto > 59) return false;

    long long dias = 0;
    for (int a = 2000; a < ano; ++a)
        dias += ehAnoBissexto(a) ? 366 : 365;
    for (int m = 1; m < mes; ++m)
        dias += diasNoMes(m, ano);
    dias += dia - 1;

    resultado = dias * 24LL * 60LL + hora * 60LL + minuto;
    return true;
}

bool periodoProjetoValido(const Projeto& projeto) {
    long long inicio = 0, termino = 0;
    return timestampEmMinutos(projeto.getInicio(), inicio) &&
           timestampEmMinutos(projeto.getTermino(), termino) && inicio <= termino;
}

bool intervaloValido(const std::string& inicioTexto, const std::string& fimTexto,
                     long long& duracao) {
    long long inicio = 0, fim = 0;
    if (!timestampEmMinutos(inicioTexto, inicio) ||
        !timestampEmMinutos(fimTexto, fim) || fim < inicio) return false;
    duracao = fim - inicio;
    return true;
}

bool calcularTempoCiclo(const CartaoDeAtividade& cartao, long long& minutos) {
    if (cartao.getEstado() != "FEITO") return false;
    return intervaloValido(cartao.getInicio(), cartao.getTermino(), minutos);
}

bool calcularLeadTime(const CartaoDeAtividade& cartao, long long& minutos) {
    if (cartao.getEstado() != "FEITO") return false;
    return intervaloValido(cartao.getEntrada(), cartao.getTermino(), minutos);
}

bool criarIdentificador(const std::string& texto, Identificador& identificador) {
    try {
        identificador.setIdentificador(texto);
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

bool criarEmail(const std::string& texto, Email& email) {
    try {
        email.setEmail(texto);
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

} // namespace

// -----------------------------------------------------------------------------
// Pessoa
// -----------------------------------------------------------------------------

CntrServicoPessoa::CntrServicoPessoa(ContainerPessoas& pessoas,
                                     ContainerProjetos& projetos,
                                     ContainerCartoes& cartoes)
    : pessoas(pessoas), projetos(projetos), cartoes(cartoes) {}

bool CntrServicoPessoa::criar(const Pessoa& pessoa) {
    // Cadastro é a única operação que não exige uma sessão já autenticada.
    if (pessoa.getEmail().empty() || pessoa.getNome().empty() ||
        pessoa.getSenha().empty() || pessoa.getPapel().empty()) return false;
    return pessoas.inserir(pessoa);
}

bool CntrServicoPessoa::autenticar(const Email& email, const Senha& senha) {
    Pessoa cadastrada;
    return pessoas.obter(email.getEmail(), cadastrada) &&
           cadastrada.getSenha() == senha.getSenha();
}

bool CntrServicoPessoa::ler(const Email& usuario, const Email& alvo, Pessoa& pessoa) {
    if (!usuarioCadastrado(pessoas, usuario.getEmail())) return false;
    return pessoas.obter(alvo.getEmail(), pessoa);
}

bool CntrServicoPessoa::atualizar(const Email& usuario, const Email& alvo,
                                  const Pessoa& pessoa) {
    const std::string emailAlvo = alvo.getEmail();
    // Cada usuário só pode alterar a própria conta.
    if (usuario.getEmail() != emailAlvo ||
        !usuarioCadastrado(pessoas, usuario.getEmail()) ||
        pessoa.getEmail() != emailAlvo || !pessoas.existe(emailAlvo)) return false;

    // Não permite tornar inválidos vínculos já existentes.
    if (projetos.temProjetoGerenciadoPor(emailAlvo) && pessoa.getPapel() != "GESTOR")
        return false;
    if (cartoes.temCartaoDoDesenvolvedor(emailAlvo) && pessoa.getPapel() != "DESENVOLVEDOR")
        return false;

    return pessoas.substituir(emailAlvo, pessoa);
}

bool CntrServicoPessoa::excluir(const Email& usuario, const Email& alvo) {
    const std::string emailAlvo = alvo.getEmail();
    // Cada usuário só pode excluir a própria conta.
    if (usuario.getEmail() != emailAlvo ||
        !usuarioCadastrado(pessoas, usuario.getEmail()) || !pessoas.existe(emailAlvo))
        return false;

    // Impede referências pendentes a gestores ou desenvolvedores removidos.
    if (projetos.temProjetoGerenciadoPor(emailAlvo) ||
        cartoes.temCartaoDoDesenvolvedor(emailAlvo)) return false;
    return pessoas.remover(emailAlvo);
}

bool CntrServicoPessoa::listar(const Email& usuario, std::vector<Email>& emails) {
    if (!usuarioCadastrado(pessoas, usuario.getEmail())) return false;
    const std::vector<std::string> valores = pessoas.listarEmails();
    std::vector<Email> resultado;
    for (std::size_t i = 0; i < valores.size(); ++i) {
        Email email;
        if (!criarEmail(valores[i], email)) return false;
        resultado.push_back(email);
    }
    emails.swap(resultado); // Saída só é alterada depois de uma operação bem-sucedida.
    return true;
}

// -----------------------------------------------------------------------------
// Projeto
// -----------------------------------------------------------------------------

CntrServicoProjeto::CntrServicoProjeto(ContainerPessoas& pessoas,
                                       ContainerProjetos& projetos,
                                       ContainerQuadros& quadros)
    : pessoas(pessoas), projetos(projetos), quadros(quadros) {}

bool CntrServicoProjeto::criar(const Email& gestor, const Projeto& projeto) {
    const std::string email = gestor.getEmail();
    // O projeto ainda não existe; basta confirmar que o criador é um GESTOR.
    if (!usuarioTemPapel(pessoas, email, "GESTOR")) return false;
    if (!periodoProjetoValido(projeto)) return false;
    return projetos.inserir(projeto, email);
}

bool CntrServicoProjeto::ler(const Email& usuario, const Identificador& identificador,
                             Projeto& projeto) {
    if (!usuarioCadastrado(pessoas, usuario.getEmail())) return false;
    return projetos.obter(identificador.getIdentificador(), projeto);
}

bool CntrServicoProjeto::atualizar(const Email& usuario,
                                   const Identificador& identificador,
                                   const Projeto& projeto) {
    const std::string id = identificador.getIdentificador();
    if (!ehGestorDoProjeto(pessoas, projetos, usuario.getEmail(), id) ||
        projeto.getIdentificador() != id || !periodoProjetoValido(projeto)) return false;
    return projetos.substituir(id, projeto);
}

bool CntrServicoProjeto::excluir(const Email& usuario, const Identificador& identificador) {
    const std::string id = identificador.getIdentificador();
    if (!ehGestorDoProjeto(pessoas, projetos, usuario.getEmail(), id) ||
        quadros.temQuadroDoProjeto(id)) return false;
    return projetos.remover(id);
}

bool CntrServicoProjeto::listar(const Email& usuario,
                                std::vector<Identificador>& identificadores) {
    if (!usuarioCadastrado(pessoas, usuario.getEmail())) return false;
    const std::vector<std::string> valores = projetos.listarIds();
    std::vector<Identificador> resultado;
    for (std::size_t i = 0; i < valores.size(); ++i) {
        Identificador id;
        if (!criarIdentificador(valores[i], id)) return false;
        resultado.push_back(id);
    }
    identificadores.swap(resultado);
    return true;
}

// -----------------------------------------------------------------------------
// Quadro
// -----------------------------------------------------------------------------

CntrServicoQuadro::CntrServicoQuadro(ContainerPessoas& pessoas,
                                     ContainerProjetos& projetos,
                                     ContainerQuadros& quadros,
                                     ContainerCartoes& cartoes)
    : pessoas(pessoas), projetos(projetos), quadros(quadros), cartoes(cartoes) {}

bool CntrServicoQuadro::criar(const Email& usuario, const Identificador& projeto,
                              const Quadro& quadro) {
    const std::string idProjeto = projeto.getIdentificador();
    if (!ehGestorDoProjeto(pessoas, projetos, usuario.getEmail(), idProjeto)) return false;
    Projeto projetoExistente;
    if (!projetos.obter(idProjeto, projetoExistente)) return false;
    if (quadro.getIdentificador().empty() || quadro.getNome().empty() || quadro.getLimite() < 1)
        return false;
    return quadros.inserir(quadro, idProjeto);
}

bool CntrServicoQuadro::ler(const Email& usuario, const Identificador& identificador,
                            Quadro& quadro) {
    if (!usuarioCadastrado(pessoas, usuario.getEmail())) return false;
    return quadros.obter(identificador.getIdentificador(), quadro);
}

bool CntrServicoQuadro::atualizar(const Email& usuario,
                                  const Identificador& identificador,
                                  const Quadro& quadro) {
    const std::string id = identificador.getIdentificador();
    if (!ehGestorDoQuadro(pessoas, projetos, quadros, usuario.getEmail(), id) ||
        quadro.getIdentificador() != id || quadro.getNome().empty() || quadro.getLimite() < 1 ||
        quadro.getLimite() < contarWip(cartoes, id))
        return false;
    return quadros.substituir(id, quadro);
}

bool CntrServicoQuadro::excluir(const Email& usuario, const Identificador& identificador) {
    const std::string id = identificador.getIdentificador();
    if (!ehGestorDoQuadro(pessoas, projetos, quadros, usuario.getEmail(), id) ||
        cartoes.temCartaoNoQuadro(id)) return false;
    return quadros.remover(id);
}

bool CntrServicoQuadro::listar(const Email& usuario,
                               std::vector<Identificador>& identificadores) {
    if (!usuarioCadastrado(pessoas, usuario.getEmail())) return false;
    const std::vector<std::string> valores = quadros.listarIds();
    std::vector<Identificador> resultado;
    for (std::size_t i = 0; i < valores.size(); ++i) {
        Identificador id;
        if (!criarIdentificador(valores[i], id)) return false;
        resultado.push_back(id);
    }
    identificadores.swap(resultado);
    return true;
}

// -----------------------------------------------------------------------------
// Cartão de atividade
// -----------------------------------------------------------------------------

CntrServicoCartaoDeAtividade::CntrServicoCartaoDeAtividade(
    ContainerPessoas& pessoas, ContainerProjetos& projetos,
    ContainerQuadros& quadros, ContainerCartoes& cartoes)
    : pessoas(pessoas), projetos(projetos), quadros(quadros), cartoes(cartoes) {}

bool CntrServicoCartaoDeAtividade::criar(const Email& usuario,
                                         const Identificador& quadro,
                                         const Email& desenvolvedor,
                                         const CartaoDeAtividade& cartao) {
    const std::string idQuadro = quadro.getIdentificador();
    const std::string emailDev = desenvolvedor.getEmail();
    Quadro quadroExistente;
    long long entrada = 0;
    if (!ehGestorDoQuadro(pessoas, projetos, quadros, usuario.getEmail(), idQuadro) ||
        !quadros.obter(idQuadro, quadroExistente) ||
        !usuarioTemPapel(pessoas, emailDev, "DESENVOLVEDOR") ||
        cartao.getIdentificador().empty() || cartao.getNome().empty() ||
        cartao.getEstado() != "A FAZER" ||
        !timestampEmMinutos(cartao.getEntrada(), entrada) ||
        !cartao.getInicio().empty() || !cartao.getTermino().empty()) return false;

    return cartoes.inserir(cartao, idQuadro, emailDev);
}

bool CntrServicoCartaoDeAtividade::ler(const Email& usuario,
                                       const Identificador& identificador,
                                       CartaoDeAtividade& cartao) {
    if (!usuarioCadastrado(pessoas, usuario.getEmail())) return false;
    return cartoes.obter(identificador.getIdentificador(), cartao);
}

bool CntrServicoCartaoDeAtividade::atualizar(const Email& usuario,
                                             const Identificador& identificador,
                                             const CartaoDeAtividade& cartao) {
    const std::string id = identificador.getIdentificador();
    if (cartao.getIdentificador() != id ||
        !ehGestorDoCartao(pessoas, projetos, quadros, cartoes, usuario.getEmail(), id))
        return false;

    // Campos de fluxo (estado e timestamps) não são editáveis por atualizar().
    CartaoDeAtividade atual;
    if (!cartoes.obter(id, atual)) return false;
    try {
        atual.setNome(cartao.getNome());
        atual.setDescricao(cartao.getDescricao());
        atual.setPrioridade(cartao.getPrioridade());
        atual.setTamanho(cartao.getTamanho());
    } catch (const std::exception&) {
        return false;
    }
    return cartoes.substituir(id, atual);
}

bool CntrServicoCartaoDeAtividade::excluir(const Email& usuario,
                                          const Identificador& identificador) {
    const std::string id = identificador.getIdentificador();
    if (!ehGestorDoCartao(pessoas, projetos, quadros, cartoes, usuario.getEmail(), id))
        return false;
    return cartoes.remover(id);
}

bool CntrServicoCartaoDeAtividade::listar(const Email& usuario,
                                          const Identificador& quadro,
                                          std::vector<Identificador>& identificadores) {
    if (!usuarioCadastrado(pessoas, usuario.getEmail()) ||
        !quadros.existe(quadro.getIdentificador())) return false;
    const std::vector<std::string> valores =
        cartoes.listarIdsDoQuadro(quadro.getIdentificador());
    std::vector<Identificador> resultado;
    for (std::size_t i = 0; i < valores.size(); ++i) {
        Identificador id;
        if (!criarIdentificador(valores[i], id)) return false;
        resultado.push_back(id);
    }
    identificadores.swap(resultado);
    return true;
}

bool CntrServicoCartaoDeAtividade::mover(const Email& usuario,
                                         const Identificador& identificador,
                                         const Timestamp& instante) {
    const std::string id = identificador.getIdentificador();
    if (!podeOperarCartao(pessoas, projetos, quadros, cartoes, usuario.getEmail(), id))
        return false;

    CartaoDeAtividade cartao;
    std::string idQuadro;
    if (!cartoes.obter(id, cartao, &idQuadro)) return false;

    long long instanteMovimento = 0;
    if (!timestampEmMinutos(instante.getTimestamp(), instanteMovimento)) return false;

    if (cartao.getEstado() == "A FAZER") {
        Quadro quadro;
        long long entrada = 0;
        if (!quadros.obter(idQuadro, quadro) ||
            !timestampEmMinutos(cartao.getEntrada(), entrada) ||
            instanteMovimento < entrada) return false;

        if (contarWip(cartoes, idQuadro) >= quadro.getLimite()) return false;

        try {
            cartao.setEstado("FAZENDO");
            cartao.setInicio(instante.getTimestamp());
        } catch (const std::exception&) {
            return false;
        }
    } else if (cartao.getEstado() == "FAZENDO") {
        long long inicio = 0;
        if (!timestampEmMinutos(cartao.getInicio(), inicio) || instanteMovimento < inicio)
            return false;
        try {
            cartao.setEstado("FEITO");
            cartao.setTermino(instante.getTimestamp());
        } catch (const std::exception&) {
            return false;
        }
    } else {
        // Não há transições de saída de FEITO.
        return false;
    }

    return cartoes.substituir(id, cartao);
}

bool CntrServicoCartaoDeAtividade::lerTempoCiclo(const Email& usuario,
                                                 const Identificador& identificador,
                                                 long long& minutos) {
    if (!usuarioCadastrado(pessoas, usuario.getEmail())) return false;
    CartaoDeAtividade cartao;
    long long resultado = 0;
    if (!cartoes.obter(identificador.getIdentificador(), cartao) ||
        !calcularTempoCiclo(cartao, resultado)) return false;
    minutos = resultado;
    return true;
}

bool CntrServicoCartaoDeAtividade::lerTempoCicloMedio(const Email& usuario,
                                                      const Identificador& quadro,
                                                      double& minutos) {
    const std::string idQuadro = quadro.getIdentificador();
    if (!usuarioCadastrado(pessoas, usuario.getEmail()) || !quadros.existe(idQuadro))
        return false;

    const std::vector<CartaoDeAtividade> itens = cartoes.listarCartoesDoQuadro(idQuadro);
    long long soma = 0;
    std::size_t quantidade = 0;
    for (std::size_t i = 0; i < itens.size(); ++i) {
        long long valor = 0;
        if (calcularTempoCiclo(itens[i], valor)) {
            soma += valor;
            ++quantidade;
        }
    }
    if (quantidade == 0) return false;
    minutos = static_cast<double>(soma) / static_cast<double>(quantidade);
    return true;
}

bool CntrServicoCartaoDeAtividade::lerLeadTime(const Email& usuario,
                                               const Identificador& identificador,
                                               long long& minutos) {
    if (!usuarioCadastrado(pessoas, usuario.getEmail())) return false;
    CartaoDeAtividade cartao;
    long long resultado = 0;
    if (!cartoes.obter(identificador.getIdentificador(), cartao) ||
        !calcularLeadTime(cartao, resultado)) return false;
    minutos = resultado;
    return true;
}

bool CntrServicoCartaoDeAtividade::lerLeadTimeMedio(const Email& usuario,
                                                    const Identificador& quadro,
                                                    double& minutos) {
    const std::string idQuadro = quadro.getIdentificador();
    if (!usuarioCadastrado(pessoas, usuario.getEmail()) || !quadros.existe(idQuadro))
        return false;

    const std::vector<CartaoDeAtividade> itens = cartoes.listarCartoesDoQuadro(idQuadro);
    long long soma = 0;
    std::size_t quantidade = 0;
    for (std::size_t i = 0; i < itens.size(); ++i) {
        long long valor = 0;
        if (calcularLeadTime(itens[i], valor)) {
            soma += valor;
            ++quantidade;
        }
    }
    if (quantidade == 0) return false;
    minutos = static_cast<double>(soma) / static_cast<double>(quantidade);
    return true;
}

bool CntrServicoCartaoDeAtividade::lerWIP(const Email& usuario,
                                          const Identificador& quadro,
                                          int& quantidade) {
    const std::string idQuadro = quadro.getIdentificador();
    if (!usuarioCadastrado(pessoas, usuario.getEmail()) || !quadros.existe(idQuadro))
        return false;

    quantidade = contarWip(cartoes, idQuadro);
    return true;
}
