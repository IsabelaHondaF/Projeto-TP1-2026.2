#include "../Headers/apresentacao.hpp"

#include <functional>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace {

const char* const MSG_FALHA =
    "[ERRO] Operacao nao realizada (permissao, dado inexistente ou regra violada).";

/** Lê uma linha da entrada padrão; lança FimDeEntrada se não houver mais entrada. */
std::string lerLinha(const std::string& rotulo) {
    std::cout << rotulo;
    std::string linha;
    if (!std::getline(std::cin, linha)) throw FimDeEntrada();
    if (!linha.empty() && linha[linha.size() - 1] == '\r') linha.erase(linha.size() - 1);
    return linha;
}

/** Repete a leitura até que a classe de domínio aceite o valor digitado. */
std::string lerCampo(const std::string& rotulo,
                     const std::function<void(const std::string&)>& validar) {
    for (;;) {
        const std::string valor = lerLinha(rotulo);
        try {
            validar(valor);
            return valor;
        } catch (const std::exception& e) {
            std::cout << "  Valor invalido (" << e.what() << ") Tente novamente.\n";
        }
    }
}

std::string lerEmail(const std::string& r) {
    return lerCampo(r, [](const std::string& s) { Email d; d.setEmail(s); });
}
std::string lerSenha(const std::string& r) {
    return lerCampo(r, [](const std::string& s) { Senha d; d.setSenha(s); });
}
std::string lerNome(const std::string& r) {
    return lerCampo(r, [](const std::string& s) { Nome d; d.setNome(s); });
}
std::string lerPapel(const std::string& r) {
    return lerCampo(r, [](const std::string& s) { Papel d; d.setPapel(s); });
}
std::string lerIdentificador(const std::string& r) {
    return lerCampo(r, [](const std::string& s) { Identificador d; d.setIdentificador(s); });
}
std::string lerTexto(const std::string& r) {
    return lerCampo(r, [](const std::string& s) { Texto d; d.setTexto(s); });
}
std::string lerTimestamp(const std::string& r) {
    return lerCampo(r, [](const std::string& s) { Timestamp d; d.setTimestamp(s); });
}
std::string lerPrioridade(const std::string& r) {
    return lerCampo(r, [](const std::string& s) { Prioridade d; d.setPrioridade(s); });
}
std::string lerTamanho(const std::string& r) {
    return lerCampo(r, [](const std::string& s) { Tamanho d; d.setTamanho(s); });
}

int lerLimite(const std::string& rotulo) {
    for (;;) {
        const std::string texto = lerLinha(rotulo);
        try {
            std::size_t usados = 0;
            const int valor = std::stoi(texto, &usados);
            if (usados != texto.size()) throw std::invalid_argument("nao numerico");
            Limite limite;
            limite.setValor(valor);
            return valor;
        } catch (const std::exception&) {
            std::cout << "  Valor invalido (limite deve ser um inteiro de 1 a 25). Tente novamente.\n";
        }
    }
}

int lerOpcao() {
    const std::string texto = lerLinha("Opcao: ");
    try {
        std::size_t usados = 0;
        const int valor = std::stoi(texto, &usados);
        return usados == texto.size() ? valor : -1;
    } catch (const std::exception&) {
        return -1;
    }
}

void resultado(bool ok, const std::string& sucesso) {
    if (ok) std::cout << "[OK] " << sucesso << "\n";
    else std::cout << MSG_FALHA << "\n";
}

void opcaoInvalida() { std::cout << "Opcao invalida.\n"; }
void opcaoIndisponivel() { std::cout << "Opcao indisponivel para o seu papel.\n"; }

Email criarEmail(const std::string& texto) {
    Email email;
    email.setEmail(texto);
    return email;
}
Identificador criarId(const std::string& texto) {
    Identificador id;
    id.setIdentificador(texto);
    return id;
}

void mostrar(const Pessoa& p) {
    std::cout << "  Email: " << p.getEmail() << "\n  Nome: " << p.getNome()
              << "\n  Papel: " << p.getPapel() << "\n";
}
void mostrar(const Projeto& p) {
    std::cout << "  Identificador: " << p.getIdentificador() << "\n  Nome: " << p.getNome()
              << "\n  Descricao: " << p.getDescricao() << "\n  Inicio: " << p.getInicio()
              << "\n  Termino: " << p.getTermino() << "\n";
}
void mostrar(const Quadro& q) {
    std::cout << "  Identificador: " << q.getIdentificador() << "\n  Nome: " << q.getNome()
              << "\n  Limite WIP: " << q.getLimite() << "\n";
}
void mostrar(const CartaoDeAtividade& c) {
    std::cout << "  Identificador: " << c.getIdentificador() << "\n  Nome: " << c.getNome()
              << "\n  Descricao: " << c.getDescricao() << "\n  Prioridade: " << c.getPrioridade()
              << "\n  Tamanho: " << c.getTamanho() << "\n  Estado: " << c.getEstado()
              << "\n  Entrada: " << c.getEntrada() << "\n  Inicio: " << c.getInicio()
              << "\n  Termino: " << c.getTermino() << "\n";
}

void mostrarMinutos(const std::string& titulo, long long minutos) {
    std::cout << "  " << titulo << ": " << minutos << " minutos\n";
}
void mostrarMinutos(const std::string& titulo, double minutos) {
    std::ios::fmtflags flags = std::cout.flags();
    std::streamsize precisao = std::cout.precision();
    std::cout << "  " << titulo << ": " << std::fixed << std::setprecision(1) << minutos
              << " minutos\n";
    std::cout.flags(flags);
    std::cout.precision(precisao);
}

} // namespace

// -----------------------------------------------------------------------------
// Pessoa
// -----------------------------------------------------------------------------

CntrApresentacaoPessoa::CntrApresentacaoPessoa(IServicoPessoa* servico) : servico(servico) {}

bool CntrApresentacaoPessoa::cadastrar() {
    std::cout << "\n--- Criar conta ---\n";
    Pessoa pessoa;
    pessoa.setEmail(lerEmail("Email: "));
    pessoa.setNome(lerNome("Nome: "));
    pessoa.setSenha(lerSenha("Senha (5 caracteres, letras e digitos): "));
    pessoa.setPapel(lerPapel("Papel (GESTOR ou DESENVOLVEDOR): "));
    const bool ok = servico->criar(pessoa);
    resultado(ok, "Conta criada.");
    return ok;
}

bool CntrApresentacaoPessoa::autenticar(Email& usuario) {
    std::cout << "\n--- Entrar ---\n";
    Email email;
    Senha senha;
    email.setEmail(lerEmail("Email: "));
    senha.setSenha(lerSenha("Senha: "));
    if (!servico->autenticar(email, senha)) {
        std::cout << "[ERRO] Email ou senha incorretos.\n";
        return false;
    }
    usuario = email;
    std::cout << "[OK] Autenticado como " << email.getEmail() << ".\n";
    return true;
}

bool CntrApresentacaoPessoa::executar(const Email& usuario) {
    for (;;) {
        std::cout << "\n--- Pessoas ---\n"
                  << "2 - Ler\n3 - Atualizar (propria conta)\n4 - Excluir (propria conta)\n"
                  << "5 - Listar\n0 - Voltar\n";
        switch (lerOpcao()) {
            case 0: return false;
            case 2: ler(usuario); break;
            case 3: atualizar(usuario); break;
            case 4: if (excluir(usuario)) return true; break;
            case 5: listar(usuario); break;
            default: opcaoInvalida();
        }
    }
}

void CntrApresentacaoPessoa::ler(const Email& usuario) {
    const Email alvo = criarEmail(lerEmail("Email da pessoa: "));
    Pessoa pessoa;
    if (servico->ler(usuario, alvo, pessoa)) mostrar(pessoa);
    else std::cout << MSG_FALHA << "\n";
}

void CntrApresentacaoPessoa::atualizar(const Email& usuario) {
    std::cout << "Novos dados da sua conta (o email nao pode ser alterado).\n";
    Pessoa pessoa;
    pessoa.setEmail(usuario.getEmail());
    pessoa.setNome(lerNome("Nome: "));
    pessoa.setSenha(lerSenha("Senha (5 caracteres, letras e digitos): "));
    pessoa.setPapel(lerPapel("Papel (GESTOR ou DESENVOLVEDOR): "));
    resultado(servico->atualizar(usuario, usuario, pessoa), "Conta atualizada.");
}

bool CntrApresentacaoPessoa::excluir(const Email& usuario) {
    const bool ok = servico->excluir(usuario, usuario);
    resultado(ok, "Conta excluida. Sessao encerrada.");
    return ok;
}

void CntrApresentacaoPessoa::listar(const Email& usuario) {
    std::vector<Email> emails;
    if (!servico->listar(usuario, emails)) {
        std::cout << MSG_FALHA << "\n";
        return;
    }
    std::cout << "  Pessoas cadastradas (" << emails.size() << "):\n";
    for (std::size_t i = 0; i < emails.size(); ++i) std::cout << "  - " << emails[i].getEmail() << "\n";
}

// -----------------------------------------------------------------------------
// Projeto
// -----------------------------------------------------------------------------

CntrApresentacaoProjeto::CntrApresentacaoProjeto(IServicoProjeto* servico) : servico(servico) {}

void CntrApresentacaoProjeto::executar(const Email& usuario, const std::string& papel) {
    const bool gestor = (papel == "GESTOR");
    for (;;) {
        std::cout << "\n--- Projetos ---\n";
        if (gestor) std::cout << "1 - Criar\n";
        std::cout << "2 - Ler\n";
        if (gestor) std::cout << "3 - Atualizar\n4 - Excluir\n";
        std::cout << "5 - Listar\n0 - Voltar\n";
        const int opcao = lerOpcao();
        if (opcao == 0) return;
        if (!gestor && (opcao == 1 || opcao == 3 || opcao == 4)) { opcaoIndisponivel(); continue; }
        switch (opcao) {
            case 1: criar(usuario); break;
            case 2: ler(usuario); break;
            case 3: atualizar(usuario); break;
            case 4: excluir(usuario); break;
            case 5: listar(usuario); break;
            default: opcaoInvalida();
        }
    }
}

void CntrApresentacaoProjeto::criar(const Email& usuario) {
    Projeto projeto;
    projeto.setIdentificador(lerIdentificador("Identificador (3 letras + 3 digitos): "));
    projeto.setNome(lerNome("Nome: "));
    projeto.setDescricao(lerTexto("Descricao: "));
    projeto.setInicio(lerTimestamp("Inicio (DIA-MES-ANO-HH:MM): "));
    projeto.setTermino(lerTimestamp("Termino (DIA-MES-ANO-HH:MM): "));
    resultado(servico->criar(usuario, projeto), "Projeto criado. Voce e o gestor.");
}

void CntrApresentacaoProjeto::ler(const Email& usuario) {
    const Identificador id = criarId(lerIdentificador("Identificador do projeto: "));
    Projeto projeto;
    if (servico->ler(usuario, id, projeto)) mostrar(projeto);
    else std::cout << MSG_FALHA << "\n";
}

void CntrApresentacaoProjeto::atualizar(const Email& usuario) {
    const std::string idTexto = lerIdentificador("Identificador do projeto: ");
    Projeto projeto;
    projeto.setIdentificador(idTexto);
    projeto.setNome(lerNome("Novo nome: "));
    projeto.setDescricao(lerTexto("Nova descricao: "));
    projeto.setInicio(lerTimestamp("Novo inicio (DIA-MES-ANO-HH:MM): "));
    projeto.setTermino(lerTimestamp("Novo termino (DIA-MES-ANO-HH:MM): "));
    resultado(servico->atualizar(usuario, criarId(idTexto), projeto), "Projeto atualizado.");
}

void CntrApresentacaoProjeto::excluir(const Email& usuario) {
    const Identificador id = criarId(lerIdentificador("Identificador do projeto: "));
    resultado(servico->excluir(usuario, id), "Projeto excluido.");
}

void CntrApresentacaoProjeto::listar(const Email& usuario) {
    std::vector<Identificador> ids;
    if (!servico->listar(usuario, ids)) {
        std::cout << MSG_FALHA << "\n";
        return;
    }
    std::cout << "  Projetos (" << ids.size() << "):\n";
    for (std::size_t i = 0; i < ids.size(); ++i)
        std::cout << "  - " << ids[i].getIdentificador() << "\n";
}

// -----------------------------------------------------------------------------
// Quadro
// -----------------------------------------------------------------------------

CntrApresentacaoQuadro::CntrApresentacaoQuadro(IServicoQuadro* servico) : servico(servico) {}

void CntrApresentacaoQuadro::executar(const Email& usuario, const std::string& papel) {
    const bool gestor = (papel == "GESTOR");
    for (;;) {
        std::cout << "\n--- Quadros ---\n";
        if (gestor) std::cout << "1 - Criar\n";
        std::cout << "2 - Ler\n";
        if (gestor) std::cout << "3 - Atualizar\n4 - Excluir\n";
        std::cout << "5 - Listar\n0 - Voltar\n";
        const int opcao = lerOpcao();
        if (opcao == 0) return;
        if (!gestor && (opcao == 1 || opcao == 3 || opcao == 4)) { opcaoIndisponivel(); continue; }
        switch (opcao) {
            case 1: criar(usuario); break;
            case 2: ler(usuario); break;
            case 3: atualizar(usuario); break;
            case 4: excluir(usuario); break;
            case 5: listar(usuario); break;
            default: opcaoInvalida();
        }
    }
}

void CntrApresentacaoQuadro::criar(const Email& usuario) {
    const Identificador projeto = criarId(lerIdentificador("Identificador do projeto: "));
    Quadro quadro;
    quadro.setIdentificador(lerIdentificador("Identificador do quadro (3 letras + 3 digitos): "));
    quadro.setNome(lerNome("Nome: "));
    quadro.setLimite(lerLimite("Limite de WIP (1 a 25): "));
    resultado(servico->criar(usuario, projeto, quadro), "Quadro criado com as colunas A FAZER, FAZENDO e FEITO.");
}

void CntrApresentacaoQuadro::ler(const Email& usuario) {
    const Identificador id = criarId(lerIdentificador("Identificador do quadro: "));
    Quadro quadro;
    if (servico->ler(usuario, id, quadro)) mostrar(quadro);
    else std::cout << MSG_FALHA << "\n";
}

void CntrApresentacaoQuadro::atualizar(const Email& usuario) {
    const std::string idTexto = lerIdentificador("Identificador do quadro: ");
    Quadro quadro;
    quadro.setIdentificador(idTexto);
    quadro.setNome(lerNome("Novo nome: "));
    quadro.setLimite(lerLimite("Novo limite de WIP (1 a 25): "));
    resultado(servico->atualizar(usuario, criarId(idTexto), quadro), "Quadro atualizado.");
}

void CntrApresentacaoQuadro::excluir(const Email& usuario) {
    const Identificador id = criarId(lerIdentificador("Identificador do quadro: "));
    resultado(servico->excluir(usuario, id), "Quadro excluido.");
}

void CntrApresentacaoQuadro::listar(const Email& usuario) {
    std::vector<Identificador> ids;
    if (!servico->listar(usuario, ids)) {
        std::cout << MSG_FALHA << "\n";
        return;
    }
    std::cout << "  Quadros (" << ids.size() << "):\n";
    for (std::size_t i = 0; i < ids.size(); ++i)
        std::cout << "  - " << ids[i].getIdentificador() << "\n";
}

// -----------------------------------------------------------------------------
// Cartão de atividade
// -----------------------------------------------------------------------------

CntrApresentacaoCartao::CntrApresentacaoCartao(IServicoCartaoDeAtividade* servico)
    : servico(servico) {}

void CntrApresentacaoCartao::executar(const Email& usuario, const std::string& papel) {
    const bool gestor = (papel == "GESTOR");
    for (;;) {
        std::cout << "\n--- Cartoes de atividade ---\n";
        if (gestor) std::cout << "1 - Criar\n";
        std::cout << "2 - Ler\n";
        if (gestor) std::cout << "3 - Atualizar\n4 - Excluir\n";
        std::cout << "5 - Listar (por quadro)\n6 - Mover\n7 - Ler tempo de ciclo\n"
                  << "8 - Ler tempo de ciclo medio\n9 - Ler lead time\n"
                  << "10 - Ler lead time medio\n11 - Ler WIP\n0 - Voltar\n";
        const int opcao = lerOpcao();
        if (opcao == 0) return;
        if (!gestor && (opcao == 1 || opcao == 3 || opcao == 4)) { opcaoIndisponivel(); continue; }
        switch (opcao) {
            case 1: criar(usuario); break;
            case 2: ler(usuario); break;
            case 3: atualizar(usuario); break;
            case 4: excluir(usuario); break;
            case 5: listar(usuario); break;
            case 6: mover(usuario); break;
            case 7: lerTempoCiclo(usuario); break;
            case 8: lerTempoCicloMedio(usuario); break;
            case 9: lerLeadTime(usuario); break;
            case 10: lerLeadTimeMedio(usuario); break;
            case 11: lerWIP(usuario); break;
            default: opcaoInvalida();
        }
    }
}

void CntrApresentacaoCartao::criar(const Email& usuario) {
    const Identificador quadro = criarId(lerIdentificador("Identificador do quadro: "));
    const Email desenvolvedor = criarEmail(lerEmail("Email do desenvolvedor responsavel: "));
    CartaoDeAtividade cartao;
    cartao.setIdentificador(lerIdentificador("Identificador do cartao (3 letras + 3 digitos): "));
    cartao.setNome(lerNome("Nome: "));
    cartao.setDescricao(lerTexto("Descricao: "));
    cartao.setPrioridade(lerPrioridade("Prioridade (ALTA, MEDIA ou BAIXA): "));
    cartao.setTamanho(lerTamanho("Tamanho (GRANDE, MEDIO ou PEQUENO): "));
    cartao.setEstado("A FAZER"); // todo cartão novo entra na coluna A FAZER
    cartao.setEntrada(lerTimestamp("Entrada na coluna A FAZER (DIA-MES-ANO-HH:MM): "));
    resultado(servico->criar(usuario, quadro, desenvolvedor, cartao), "Cartao criado na coluna A FAZER.");
}

void CntrApresentacaoCartao::ler(const Email& usuario) {
    const Identificador id = criarId(lerIdentificador("Identificador do cartao: "));
    CartaoDeAtividade cartao;
    if (servico->ler(usuario, id, cartao)) mostrar(cartao);
    else std::cout << MSG_FALHA << "\n";
}

void CntrApresentacaoCartao::atualizar(const Email& usuario) {
    std::cout << "Estado e datas so mudam pela opcao Mover.\n";
    const std::string idTexto = lerIdentificador("Identificador do cartao: ");
    CartaoDeAtividade cartao;
    cartao.setIdentificador(idTexto);
    cartao.setNome(lerNome("Novo nome: "));
    cartao.setDescricao(lerTexto("Nova descricao: "));
    cartao.setPrioridade(lerPrioridade("Nova prioridade (ALTA, MEDIA ou BAIXA): "));
    cartao.setTamanho(lerTamanho("Novo tamanho (GRANDE, MEDIO ou PEQUENO): "));
    resultado(servico->atualizar(usuario, criarId(idTexto), cartao), "Cartao atualizado.");
}

void CntrApresentacaoCartao::excluir(const Email& usuario) {
    const Identificador id = criarId(lerIdentificador("Identificador do cartao: "));
    resultado(servico->excluir(usuario, id), "Cartao excluido.");
}

void CntrApresentacaoCartao::listar(const Email& usuario) {
    const Identificador quadro = criarId(lerIdentificador("Identificador do quadro: "));
    std::vector<Identificador> ids;
    if (!servico->listar(usuario, quadro, ids)) {
        std::cout << MSG_FALHA << "\n";
        return;
    }
    std::cout << "  Cartoes do quadro (" << ids.size() << "):\n";
    for (std::size_t i = 0; i < ids.size(); ++i)
        std::cout << "  - " << ids[i].getIdentificador() << "\n";
}

void CntrApresentacaoCartao::mover(const Email& usuario) {
    std::cout << "Movimentos possiveis: A FAZER -> FAZENDO e FAZENDO -> FEITO.\n";
    const Identificador id = criarId(lerIdentificador("Identificador do cartao: "));
    Timestamp instante;
    instante.setTimestamp(lerTimestamp("Instante da movimentacao (DIA-MES-ANO-HH:MM): "));
    resultado(servico->mover(usuario, id, instante), "Cartao movido para a proxima coluna.");
}

void CntrApresentacaoCartao::lerTempoCiclo(const Email& usuario) {
    const Identificador id = criarId(lerIdentificador("Identificador do cartao: "));
    long long minutos = 0;
    if (servico->lerTempoCiclo(usuario, id, minutos)) mostrarMinutos("Tempo de ciclo", minutos);
    else std::cout << "[ERRO] Indisponivel (o cartao precisa estar FEITO) ou sem permissao.\n";
}

void CntrApresentacaoCartao::lerTempoCicloMedio(const Email& usuario) {
    const Identificador quadro = criarId(lerIdentificador("Identificador do quadro: "));
    double minutos = 0;
    if (servico->lerTempoCicloMedio(usuario, quadro, minutos)) mostrarMinutos("Tempo de ciclo medio", minutos);
    else std::cout << "[ERRO] Indisponivel (nenhum cartao FEITO no quadro) ou sem permissao.\n";
}

void CntrApresentacaoCartao::lerLeadTime(const Email& usuario) {
    const Identificador id = criarId(lerIdentificador("Identificador do cartao: "));
    long long minutos = 0;
    if (servico->lerLeadTime(usuario, id, minutos)) mostrarMinutos("Lead time", minutos);
    else std::cout << "[ERRO] Indisponivel (o cartao precisa estar FEITO) ou sem permissao.\n";
}

void CntrApresentacaoCartao::lerLeadTimeMedio(const Email& usuario) {
    const Identificador quadro = criarId(lerIdentificador("Identificador do quadro: "));
    double minutos = 0;
    if (servico->lerLeadTimeMedio(usuario, quadro, minutos)) mostrarMinutos("Lead time medio", minutos);
    else std::cout << "[ERRO] Indisponivel (nenhum cartao FEITO no quadro) ou sem permissao.\n";
}

void CntrApresentacaoCartao::lerWIP(const Email& usuario) {
    const Identificador quadro = criarId(lerIdentificador("Identificador do quadro: "));
    int wip = 0;
    if (servico->lerWIP(usuario, quadro, wip)) std::cout << "  WIP (cartoes em FAZENDO): " << wip << "\n";
    else std::cout << MSG_FALHA << "\n";
}

// -----------------------------------------------------------------------------
// Principal
// -----------------------------------------------------------------------------

CntrApresentacaoPrincipal::CntrApresentacaoPrincipal(IServicoPessoa* servicoPessoa,
                                                     IServicoProjeto* servicoProjeto,
                                                     IServicoQuadro* servicoQuadro,
                                                     IServicoCartaoDeAtividade* servicoCartao)
    : servicoPessoa(servicoPessoa),
      pessoa(servicoPessoa),
      projeto(servicoProjeto),
      quadro(servicoQuadro),
      cartao(servicoCartao) {}

void CntrApresentacaoPrincipal::executar() {
    try {
        for (;;) {
            std::cout << "\n=== Sistema Kanban ===\n1 - Entrar\n2 - Criar conta\n0 - Sair\n";
            const int opcao = lerOpcao();
            if (opcao == 0) {
                std::cout << "Ate logo.\n";
                return;
            }
            if (opcao == 1) {
                Email usuario;
                if (pessoa.autenticar(usuario)) sessao(usuario);
            } else if (opcao == 2) {
                pessoa.cadastrar();
            } else {
                opcaoInvalida();
            }
        }
    } catch (const FimDeEntrada&) {
        std::cout << "\nEntrada encerrada.\n";
    }
}

void CntrApresentacaoPrincipal::sessao(const Email& usuario) {
    for (;;) {
        Pessoa atual;
        if (!servicoPessoa->ler(usuario, usuario, atual)) return;
        const std::string papel = atual.getPapel();

        std::cout << "\n=== Menu principal (" << usuario.getEmail() << " - " << papel << ") ===\n"
                  << "1 - Pessoas\n2 - Projetos\n3 - Quadros\n4 - Cartoes de atividade\n"
                  << "0 - Sair da sessao\n";
        switch (lerOpcao()) {
            case 0: std::cout << "Sessao encerrada.\n"; return;
            case 1: if (pessoa.executar(usuario)) return; break;
            case 2: projeto.executar(usuario, papel); break;
            case 3: quadro.executar(usuario, papel); break;
            case 4: cartao.executar(usuario, papel); break;
            default: opcaoInvalida();
        }
    }
}
