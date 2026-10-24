#include "../Headers/testes_entidades.hpp"

bool TUPessoa::executar() {
    Pessoa pessoa;

    // Teste de integridade de setters e getters válidos
    try {
        pessoa.setEmail("usuario@teste.com");
        if (pessoa.getEmail() == "usuario@teste.com") sucesso++; else falha++;

        pessoa.setNome("Carlos Silva");
        if (pessoa.getNome() == "Carlos Silva") sucesso++; else falha++;

        pessoa.setSenha("seg12");
        if (pessoa.getSenha() == "seg12") sucesso++; else falha++;

        pessoa.setPapel("GESTOR");
        if (pessoa.getPapel() == "GESTOR") sucesso++; else falha++;
    } catch (...) {
        falha++;
    }

    // Teste de propagação de exceção de domínio inválido
    try {
        pessoa.setEmail("email_invalido");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    try {
        pessoa.setPapel("PAPEL_INEXISTENTE");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    return falha == 0;
}

bool TUProjeto::executar() {
    Projeto projeto;

    // Setters e getters válidos
    try {
        projeto.setIdentificador("PRJ123");
        if (projeto.getIdentificador() == "PRJ123") sucesso++; else falha++;

        projeto.setNome("Novo Modulo");
        if (projeto.getNome() == "Novo Modulo") sucesso++; else falha++;

        projeto.setDescricao("Descricao do projeto.");
        if (projeto.getDescricao() == "Descricao do projeto.") sucesso++; else falha++;

        projeto.setInicio("1-JAN-2026-08:00");
        if (projeto.getInicio() == "1-JAN-2026-08:00") sucesso++; else falha++;

        projeto.setTermino("30-JUN-2026-18:00");
        if (projeto.getTermino() == "30-JUN-2026-18:00") sucesso++; else falha++;
    } catch (...) {
        falha++;
    }

    // Teste de propagação de erro de domínio
    try {
        projeto.setIdentificador("INVALID");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    try {
        projeto.setDescricao("sem ponto no final");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    return falha == 0;
}

bool TUQuadro::executar() {
    Quadro quadro;

    // Setters e getters válidos
    try {
        quadro.setIdentificador("QUA001");
        if (quadro.getIdentificador() == "QUA001") sucesso++; else falha++;

        quadro.setNome("Quadro Geral");
        if (quadro.getNome() == "Quadro Geral") sucesso++; else falha++;

        quadro.setLimite(15);
        if (quadro.getLimite() == 15) sucesso++; else falha++;
    } catch (...) {
        falha++;
    }

    // Propagação de erro de limite inválido
    try {
        quadro.setLimite(30);
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    try {
        quadro.setIdentificador("123QUA");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    return falha == 0;
}

bool TUCartaoDeAtividade::executar() {
    CartaoDeAtividade cartao;

    // Setters e getters válidos
    try {
        cartao.setIdentificador("CAR001");
        if (cartao.getIdentificador() == "CAR001") sucesso++; else falha++;

        cartao.setNome("Criar Login");
        if (cartao.getNome() == "Criar Login") sucesso++; else falha++;

        cartao.setDescricao("Implementar tela.");
        if (cartao.getDescricao() == "Implementar tela.") sucesso++; else falha++;

        cartao.setPrioridade("ALTA");
        if (cartao.getPrioridade() == "ALTA") sucesso++; else falha++;

        cartao.setEstado("A FAZER");
        if (cartao.getEstado() == "A FAZER") sucesso++; else falha++;

        cartao.setTamanho("MEDIO");
        if (cartao.getTamanho() == "MEDIO") sucesso++; else falha++;

        cartao.setEntrada("10-JAN-2026-09:00");
        if (cartao.getEntrada() == "10-JAN-2026-09:00") sucesso++; else falha++;

        cartao.setInicio("11-JAN-2026-10:00");
        if (cartao.getInicio() == "11-JAN-2026-10:00") sucesso++; else falha++;

        cartao.setTermino("12-JAN-2026-18:00");
        if (cartao.getTermino() == "12-JAN-2026-18:00") sucesso++; else falha++;
    } catch (...) {
        falha++;
    }

    // Propagação de erros de domínio
    try {
        cartao.setPrioridade("MUITO ALTA");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    try {
        cartao.setEstado("PENDENTE");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    try {
        cartao.setTamanho("GIGANTE");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    return falha == 0;
}
