// Teste de fumaça da camada de serviço: um caso de sucesso para cada um dos 26
// serviços do enunciado, seguido de casos em que o serviço deve RECUSAR a operação
// (permissão, multiplicidade, WIP e consistência na exclusão).
//
// Compilar sem Main/main.cpp e sem Apresentacao/ (este arquivo tem o próprio main).

#include "../Headers/controladoras_servico.hpp"
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

namespace {

int total = 0;
int falhas = 0;

void verificar(const std::string& rotulo, bool condicao) {
    ++total;
    if (!condicao) ++falhas;
    std::cout << (condicao ? "[OK]    " : "[FALHA] ") << rotulo << "\n";
}

Email email(const std::string& t) { Email e; e.setEmail(t); return e; }
Identificador id(const std::string& t) { Identificador i; i.setIdentificador(t); return i; }
Timestamp ts(const std::string& t) { Timestamp x; x.setTimestamp(t); return x; }

Pessoa pessoa(const std::string& e, const std::string& nome, const std::string& senha,
              const std::string& papel) {
    Pessoa p;
    p.setEmail(e); p.setNome(nome); p.setSenha(senha); p.setPapel(papel);
    return p;
}

Projeto projeto(const std::string& i, const std::string& nome, const std::string& desc) {
    Projeto p;
    p.setIdentificador(i); p.setNome(nome); p.setDescricao(desc);
    p.setInicio("1-JAN-2026-09:00"); p.setTermino("31-DEZ-2026-18:00");
    return p;
}

Quadro quadro(const std::string& i, const std::string& nome, int limite) {
    Quadro q;
    q.setIdentificador(i); q.setNome(nome); q.setLimite(limite);
    return q;
}

CartaoDeAtividade cartao(const std::string& i, const std::string& nome, const std::string& entrada) {
    CartaoDeAtividade c;
    c.setIdentificador(i); c.setNome(nome); c.setDescricao("Tarefa de teste.");
    c.setPrioridade("ALTA"); c.setTamanho("MEDIO"); c.setEstado("A FAZER");
    c.setEntrada(entrada);
    return c;
}

} // namespace

int main() {
    ContainerPessoas pessoas;
    ContainerProjetos projetos;
    ContainerQuadros quadros;
    ContainerCartoes cartoes;

    // As controladoras são usadas somente por meio das interfaces.
    CntrServicoPessoa cp(pessoas, projetos, cartoes);
    CntrServicoProjeto cj(pessoas, projetos, quadros);
    CntrServicoQuadro cq(pessoas, projetos, quadros, cartoes);
    CntrServicoCartaoDeAtividade cc(pessoas, projetos, quadros, cartoes);
    IServicoPessoa& sp = cp;
    IServicoProjeto& sj = cj;
    IServicoQuadro& sq = cq;
    IServicoCartaoDeAtividade& sc = cc;

    const Email gestor = email("gestor@example.com");
    const Email outroGestor = email("outro.gestor@example.com");
    const Email dev = email("dev@example.com");
    const Email dev2 = email("dev2@example.com");

    std::cout << "== Casos de sucesso (um por servico) ==\n";

    // --- Pessoa ---------------------------------------------------------------
    verificar("01 CRIAR PESSOA (gestor)", sp.criar(pessoa("gestor@example.com", "Ana Silva", "abc12", "GESTOR")));
    verificar("01 CRIAR PESSOA (outro gestor)", sp.criar(pessoa("outro.gestor@example.com", "Caio Souza", "ccc33", "GESTOR")));
    verificar("01 CRIAR PESSOA (desenvolvedor)", sp.criar(pessoa("dev@example.com", "Bia Lima", "def34", "DESENVOLVEDOR")));
    verificar("01 CRIAR PESSOA (desenvolvedor 2)", sp.criar(pessoa("dev2@example.com", "Davi Cruz", "ddd44", "DESENVOLVEDOR")));
    Senha senhaOk; senhaOk.setSenha("abc12");
    verificar("-- AUTENTICAR com senha correta", sp.autenticar(gestor, senhaOk));

    Pessoa lida;
    verificar("02 LER PESSOA", sp.ler(gestor, dev, lida) && lida.getNome() == "Bia Lima" && lida.getPapel() == "DESENVOLVEDOR");
    verificar("03 ATUALIZAR PESSOA (propria conta)", sp.atualizar(dev, dev, pessoa("dev@example.com", "Bia Souza", "def34", "DESENVOLVEDOR")));
    verificar("02 LER PESSOA (dado atualizado)", sp.ler(dev, dev, lida) && lida.getNome() == "Bia Souza");
    std::vector<Email> emails;
    verificar("05 LISTAR PESSOA", sp.listar(gestor, emails) && emails.size() == 4);

    // --- Projeto --------------------------------------------------------------
    verificar("06 CRIAR PROJETO", sj.criar(gestor, projeto("PRJ001", "Projeto Alfa", "Projeto de teste.")));
    Projeto pj;
    verificar("07 LER PROJETO", sj.ler(dev, id("PRJ001"), pj) && pj.getNome() == "Projeto Alfa");
    verificar("08 ATUALIZAR PROJETO", sj.atualizar(gestor, id("PRJ001"), projeto("PRJ001", "Projeto Beta", "Nova descricao.")));
    verificar("07 LER PROJETO (dado atualizado)", sj.ler(gestor, id("PRJ001"), pj) && pj.getNome() == "Projeto Beta");
    std::vector<Identificador> ids;
    verificar("10 LISTAR PROJETO", sj.listar(dev, ids) && ids.size() == 1 && ids[0].getIdentificador() == "PRJ001");

    // --- Quadro ---------------------------------------------------------------
    verificar("11 CRIAR QUADRO", sq.criar(gestor, id("PRJ001"), quadro("QUA001", "Desenvolvimento", 2)));
    Quadro qd;
    verificar("12 LER QUADRO", sq.ler(dev, id("QUA001"), qd) && qd.getLimite() == 2);
    verificar("13 ATUALIZAR QUADRO", sq.atualizar(gestor, id("QUA001"), quadro("QUA001", "Sprint Um", 2)));
    verificar("12 LER QUADRO (dado atualizado)", sq.ler(gestor, id("QUA001"), qd) && qd.getNome() == "Sprint Um");
    verificar("15 LISTAR QUADRO", sq.listar(dev, ids) && ids.size() == 1 && ids[0].getIdentificador() == "QUA001");

    // --- Cartão ---------------------------------------------------------------
    verificar("16 CRIAR CARTAO DE ATIVIDADE (CAR001)", sc.criar(gestor, id("QUA001"), dev, cartao("CAR001", "Tarefa Um", "2-JAN-2026-09:00")));
    verificar("16 CRIAR CARTAO DE ATIVIDADE (CAR002)", sc.criar(gestor, id("QUA001"), dev, cartao("CAR002", "Tarefa Dois", "2-JAN-2026-09:30")));
    verificar("16 CRIAR CARTAO DE ATIVIDADE (CAR003)", sc.criar(gestor, id("QUA001"), dev2, cartao("CAR003", "Tarefa Tres", "2-JAN-2026-10:00")));
    CartaoDeAtividade ct;
    verificar("17 LER CARTAO DE ATIVIDADE", sc.ler(dev, id("CAR001"), ct) && ct.getEstado() == "A FAZER" && ct.getNome() == "Tarefa Um");
    verificar("18 ATUALIZAR CARTAO DE ATIVIDADE", sc.atualizar(gestor, id("CAR001"), cartao("CAR001", "Tarefa Uma", "2-JAN-2026-09:00")));
    verificar("17 LER CARTAO DE ATIVIDADE (dado atualizado)", sc.ler(gestor, id("CAR001"), ct) && ct.getNome() == "Tarefa Uma");
    verificar("20 LISTAR CARTAO DE ATIVIDADE", sc.listar(dev, id("QUA001"), ids) && ids.size() == 3);

    int wip = -1;
    verificar("26 LER WIP (inicial = 0)", sc.lerWIP(gestor, id("QUA001"), wip) && wip == 0);
    verificar("21 MOVER CAR001 (A FAZER -> FAZENDO)", sc.mover(dev, id("CAR001"), ts("2-JAN-2026-10:00")));
    verificar("21 MOVER CAR002 (A FAZER -> FAZENDO)", sc.mover(dev, id("CAR002"), ts("2-JAN-2026-11:00")));
    verificar("26 LER WIP (dois em FAZENDO)", sc.lerWIP(dev, id("QUA001"), wip) && wip == 2);
    verificar("21 MOVER CAR001 (FAZENDO -> FEITO)", sc.mover(dev, id("CAR001"), ts("2-JAN-2026-12:30")));
    verificar("21 MOVER CAR002 (FAZENDO -> FEITO, gestor)", sc.mover(gestor, id("CAR002"), ts("2-JAN-2026-14:00")));
    verificar("26 LER WIP (final = 0)", sc.lerWIP(gestor, id("QUA001"), wip) && wip == 0);

    long long minutos = -1;
    double media = -1;
    verificar("22 LER TEMPO DE CICLO (CAR001 = 150 min)", sc.lerTempoCiclo(dev, id("CAR001"), minutos) && minutos == 150);
    verificar("24 LER LEAD TIME (CAR001 = 210 min)", sc.lerLeadTime(dev, id("CAR001"), minutos) && minutos == 210);
    verificar("23 LER TEMPO DE CICLO MEDIO (150 e 180 -> 165)", sc.lerTempoCicloMedio(gestor, id("QUA001"), media) && std::fabs(media - 165.0) < 1e-9);
    verificar("25 LER LEAD TIME MEDIO (210 e 270 -> 240)", sc.lerLeadTimeMedio(gestor, id("QUA001"), media) && std::fabs(media - 240.0) < 1e-9);

    std::cout << "\n== Casos em que o servico deve recusar ==\n";

    verificar("AUTENTICAR com senha errada e recusado", !sp.autenticar(gestor, [] { Senha s; s.setSenha("zzz99"); return s; }()));
    verificar("CRIAR PESSOA com email repetido e recusado", !sp.criar(pessoa("gestor@example.com", "Outra Ana", "xyz12", "GESTOR")));
    verificar("ATUALIZAR PESSOA de outro usuario e recusado", !sp.atualizar(dev, gestor, pessoa("gestor@example.com", "Invasor", "abc12", "GESTOR")));
    verificar("EXCLUIR PESSOA de outro usuario e recusado", !sp.excluir(dev, dev2));
    verificar("DESENVOLVEDOR nao cria projeto", !sj.criar(dev, projeto("PRJ002", "Projeto Gama", "Nao deve criar.")));
    verificar("PROJETO duplicado e recusado", !sj.criar(gestor, projeto("PRJ001", "Projeto Alfa", "Duplicado.")));
    verificar("Gestor que nao criou o projeto nao atualiza", !sj.atualizar(outroGestor, id("PRJ001"), projeto("PRJ001", "Invasao", "Nao deve.")));
    verificar("Gestor que nao criou o projeto nao cria quadro nele", !sq.criar(outroGestor, id("PRJ001"), quadro("QUA002", "Invasao", 3)));
    verificar("DESENVOLVEDOR nao cria cartao", !sc.criar(dev, id("QUA001"), dev, cartao("CAR004", "Tarefa Quatro", "2-JAN-2026-11:00")));
    verificar("DESENVOLVEDOR nao atualiza cartao", !sc.atualizar(dev, id("CAR001"), cartao("CAR001", "Alterado", "2-JAN-2026-09:00")));
    verificar("DESENVOLVEDOR nao exclui cartao", !sc.excluir(dev, id("CAR001")));
    verificar("Cartao de quadro inexistente e recusado", !sc.criar(gestor, id("QUA999"), dev, cartao("CAR004", "Tarefa Quatro", "2-JAN-2026-11:00")));
    verificar("Cartao so pode ser criado para um DESENVOLVEDOR", !sc.criar(gestor, id("QUA001"), outroGestor, cartao("CAR004", "Tarefa Quatro", "2-JAN-2026-11:00")));
    verificar("Cartao FEITO nao pode mais ser movido", !sc.mover(dev, id("CAR001"), ts("2-JAN-2026-18:00")));
    verificar("Mover cartao de outro desenvolvedor e recusado", !sc.mover(dev, id("CAR003"), ts("2-JAN-2026-10:30")));

    // Limite de WIP (quadro com limite 2): CAR003 só entra em FAZENDO se houver vaga.
    // Para testar o limite, cria CAR004 e CAR005 e ocupa as duas vagas.
    verificar("-- preparo: CAR004", sc.criar(gestor, id("QUA001"), dev, cartao("CAR004", "Tarefa Quatro", "3-JAN-2026-09:00")));
    verificar("-- preparo: CAR005", sc.criar(gestor, id("QUA001"), dev, cartao("CAR005", "Tarefa Cinco", "3-JAN-2026-09:10")));
    verificar("-- preparo: CAR006", sc.criar(gestor, id("QUA001"), dev, cartao("CAR006", "Tarefa Seis", "3-JAN-2026-09:20")));
    verificar("MOVER CAR004 para FAZENDO", sc.mover(dev, id("CAR004"), ts("3-JAN-2026-10:00")));
    verificar("MOVER CAR005 para FAZENDO", sc.mover(dev, id("CAR005"), ts("3-JAN-2026-10:05")));
    verificar("WIP acima do limite e recusado (limite 2)", !sc.mover(dev, id("CAR006"), ts("3-JAN-2026-10:10")));
    verificar("Reduzir limite abaixo do WIP atual e recusado", !sq.atualizar(gestor, id("QUA001"), quadro("QUA001", "Sprint Um", 1)));
    verificar("Mover com instante anterior ao inicio e recusado", !sc.mover(dev, id("CAR004"), ts("3-JAN-2026-09:00")));
    verificar("Conclui CAR004", sc.mover(dev, id("CAR004"), ts("3-JAN-2026-11:00")));
    verificar("Com vaga liberada, CAR006 entra em FAZENDO", sc.mover(dev, id("CAR006"), ts("3-JAN-2026-11:05")));
    verificar("Metrica de cartao que nao esta FEITO e recusada", !sc.lerTempoCiclo(dev, id("CAR006"), minutos));

    std::cout << "\n== Consistencia nas exclusoes ==\n";

    verificar("Excluir projeto com quadro e recusado", !sj.excluir(gestor, id("PRJ001")));
    verificar("Excluir quadro com cartoes e recusado", !sq.excluir(gestor, id("QUA001")));
    verificar("Excluir gestor que gerencia projeto e recusado", !sp.excluir(gestor, gestor));
    verificar("Excluir desenvolvedor com cartoes e recusado", !sp.excluir(dev, dev));

    std::cout << "\n== Exclusoes que devem funcionar (ordem inversa das dependencias) ==\n";

    const char* cartoesParaExcluir[] = {"CAR001", "CAR002", "CAR003", "CAR004", "CAR005", "CAR006"};
    bool todosExcluidos = true;
    for (int i = 0; i < 6; ++i)
        todosExcluidos = sc.excluir(gestor, id(cartoesParaExcluir[i])) && todosExcluidos;
    verificar("19 EXCLUIR CARTAO DE ATIVIDADE (seis cartoes)", todosExcluidos);
    verificar("17 LER CARTAO excluido e recusado", !sc.ler(gestor, id("CAR001"), ct));
    verificar("14 EXCLUIR QUADRO", sq.excluir(gestor, id("QUA001")));
    verificar("09 EXCLUIR PROJETO", sj.excluir(gestor, id("PRJ001")));
    verificar("04 EXCLUIR PESSOA (dev2, sem vinculos)", sp.excluir(dev2, dev2));
    verificar("04 EXCLUIR PESSOA (dev, agora sem cartoes)", sp.excluir(dev, dev));
    verificar("04 EXCLUIR PESSOA (gestor, agora sem projetos)", sp.excluir(gestor, gestor));
    verificar("05 LISTAR PESSOA (resta um usuario)", sp.listar(outroGestor, emails) && emails.size() == 1);

    std::cout << "\nResultado: " << (total - falhas) << " de " << total << " verificacoes passaram.\n";
    return falhas == 0 ? 0 : 1;
}
