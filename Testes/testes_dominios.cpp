#include "../Headers/testes_dominios.hpp"
#include <iostream>

bool TULimite::executar() {
    Limite limite;
    // Casos válidos: limites 1, 25 e intermediário
    try {
        limite.setValor(1);
        if (limite.getValor() == 1) sucesso++; else falha++;
        limite.setValor(25);
        if (limite.getValor() == 25) sucesso++; else falha++;
        limite.setValor(10);
        if (limite.getValor() == 10) sucesso++; else falha++;
    } catch (...) {
        falha++;
    }

    // Casos inválidos: 0, 26, negativos
    try {
        limite.setValor(0);
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    try {
        limite.setValor(26);
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    try {
        limite.setValor(-5);
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    return falha == 0;
}

bool TUSenha::executar() {
    Senha senha;
    // Casos válidos: 5 caracteres com pelo menos 1 letra e 1 dígito
    try {
        senha.setSenha("abc12");
        if (senha.getSenha() == "abc12") sucesso++; else falha++;
        senha.setSenha("1234a");
        if (senha.getSenha() == "1234a") sucesso++; else falha++;
        senha.setSenha("A1b2C");
        if (senha.getSenha() == "A1b2C") sucesso++; else falha++;
    } catch (...) {
        falha++;
    }

    // Casos inválidos:
    // Menos de 5 caracteres
    try {
        senha.setSenha("ab12");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Mais de 5 caracteres
    try {
        senha.setSenha("abc123");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Apenas letras
    try {
        senha.setSenha("abcde");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Apenas dígitos
    try {
        senha.setSenha("12345");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Caracteres especiais
    try {
        senha.setSenha("ab12!");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    return falha == 0;
}

bool TUEstado::executar() {
    Estado estado;
    // Casos válidos
    try {
        estado.setEstado("A FAZER");
        if (estado.getEstado() == "A FAZER") sucesso++; else falha++;
        estado.setEstado("FAZENDO");
        if (estado.getEstado() == "FAZENDO") sucesso++; else falha++;
        estado.setEstado("FEITO");
        if (estado.getEstado() == "FEITO") sucesso++; else falha++;
    } catch (...) {
        falha++;
    }

    // Casos inválidos
    try {
        estado.setEstado("EM ANDAMENTO");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    try {
        estado.setEstado("a fazer");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    try {
        estado.setEstado("");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    return falha == 0;
}

bool TUPrioridade::executar() {
    Prioridade prioridade;
    // Casos válidos
    try {
        prioridade.setPrioridade("ALTA");
        if (prioridade.getPrioridade() == "ALTA") sucesso++; else falha++;
        prioridade.setPrioridade("MEDIA");
        if (prioridade.getPrioridade() == "MEDIA") sucesso++; else falha++;
        prioridade.setPrioridade("BAIXA");
        if (prioridade.getPrioridade() == "BAIXA") sucesso++; else falha++;
    } catch (...) {
        falha++;
    }

    // Casos inválidos
    try {
        prioridade.setPrioridade("URGENTE");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    try {
        prioridade.setPrioridade("alta");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    return falha == 0;
}

bool TUTamanho::executar() {
    Tamanho tamanho;
    // Casos válidos
    try {
        tamanho.setTamanho("GRANDE");
        if (tamanho.getTamanho() == "GRANDE") sucesso++; else falha++;
        tamanho.setTamanho("MEDIO");
        if (tamanho.getTamanho() == "MEDIO") sucesso++; else falha++;
        tamanho.setTamanho("MÉDIO");
        if (tamanho.getTamanho() == "MEDIO") sucesso++; else falha++;
        tamanho.setTamanho("PEQUENO");
        if (tamanho.getTamanho() == "PEQUENO") sucesso++; else falha++;
    } catch (...) {
        falha++;
    }

    // Casos inválidos
    try {
        tamanho.setTamanho("MINIMO");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    try {
        tamanho.setTamanho("grande");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    return falha == 0;
}

bool TUNome::executar() {
    Nome nome;
    // Casos válidos: até 15 caracteres, letras e espaços isolados
    try {
        nome.setNome("Ana");
        if (nome.getNome() == "Ana") sucesso++; else falha++;
        nome.setNome("Joao Pedro");
        if (nome.getNome() == "Joao Pedro") sucesso++; else falha++;
        nome.setNome("Abcdefghij Klmn"); // 15 chars
        if (nome.getNome() == "Abcdefghij Klmn") sucesso++; else falha++;
    } catch (...) {
        falha++;
    }

    // Casos inválidos:
    // Vazio
    try {
        nome.setNome("");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Mais de 15 caracteres
    try {
        nome.setNome("Nome Com Mais De Quinze");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Espaço no início
    try {
        nome.setNome(" Ana");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Espaço no fim
    try {
        nome.setNome("Ana ");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Espaços consecutivos
    try {
        nome.setNome("Ana  Silva");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Dígitos
    try {
        nome.setNome("Ana 123");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    return falha == 0;
}

bool TUPapel::executar() {
    Papel papel;
    // Casos válidos
    try {
        papel.setPapel("GESTOR");
        if (papel.getPapel() == "GESTOR") sucesso++; else falha++;
        papel.setPapel("DESENVOLVEDOR");
        if (papel.getPapel() == "DESENVOLVEDOR") sucesso++; else falha++;
    } catch (...) {
        falha++;
    }

    // Casos inválidos
    try {
        papel.setPapel("ADMIN");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    try {
        papel.setPapel("gestor");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    return falha == 0;
}

bool TUTexto::executar() {
    Texto texto;
    // Casos válidos: até 30 chars, inicia com maiúscula, termina com ponto
    try {
        texto.setTexto("Tarefa de teste.");
        if (texto.getTexto() == "Tarefa de teste.") sucesso++; else falha++;
        texto.setTexto("A.");
        if (texto.getTexto() == "A.") sucesso++; else falha++;
        texto.setTexto("Texto com: virgula, e ponto.");
        if (texto.getTexto() == "Texto com: virgula, e ponto.") sucesso++; else falha++;
    } catch (...) {
        falha++;
    }

    // Casos inválidos:
    // Não inicia com maiúscula
    try {
        texto.setTexto("tarefa teste.");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Não termina com ponto
    try {
        texto.setTexto("Tarefa teste");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Mais de 30 caracteres
    try {
        texto.setTexto("Este texto possui bem mais de trinta caracteres no total.");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Pontuações consecutivas
    try {
        texto.setTexto("Texto com.. ponto duplo.");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    return falha == 0;
}

bool TUIdentificador::executar() {
    Identificador id;
    // Casos válidos: 3 letras seguidas de 3 dígitos
    try {
        id.setIdentificador("PRJ001");
        if (id.getIdentificador() == "PRJ001") sucesso++; else falha++;
        id.setIdentificador("abc123");
        if (id.getIdentificador() == "abc123") sucesso++; else falha++;
        id.setIdentificador("XYZ999");
        if (id.getIdentificador() == "XYZ999") sucesso++; else falha++;
    } catch (...) {
        falha++;
    }

    // Casos inválidos:
    // Comprimento incorreto
    try {
        id.setIdentificador("PR001");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    try {
        id.setIdentificador("PRJ0001");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Dígito onde deveria ser letra
    try {
        id.setIdentificador("P1J001");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Letra onde deveria ser dígito
    try {
        id.setIdentificador("PRJ0A1");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    return falha == 0;
}

bool TUEmail::executar() {
    Email email;
    // Casos válidos
    try {
        email.setEmail("usuario@dominio.com");
        if (email.getEmail() == "usuario@dominio.com") sucesso++; else falha++;
        email.setEmail("nome.sobrenome@sub.dominio.org");
        if (email.getEmail() == "nome.sobrenome@sub.dominio.org") sucesso++; else falha++;
        email.setEmail("user-123@empresa.com.br");
        if (email.getEmail() == "user-123@empresa.com.br") sucesso++; else falha++;
    } catch (...) {
        falha++;
    }

    // Casos inválidos:
    // Sem @
    try {
        email.setEmail("usuariodominio.com");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Dois @
    try {
        email.setEmail("user@@dominio.com");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Início com ponto
    try {
        email.setEmail(".user@dominio.com");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Término da parte local com ponto
    try {
        email.setEmail("user.@dominio.com");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Ponto duplo
    try {
        email.setEmail("user..name@dominio.com");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Domínio terminando em hífen
    try {
        email.setEmail("user@dominio-.com");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    return falha == 0;
}

bool TUTimestamp::executar() {
    Timestamp ts;
    // Casos válidos
    try {
        ts.setTimestamp("1-JAN-2026-09:00");
        if (ts.getTimestamp() == "1-JAN-2026-09:00") sucesso++; else falha++;
        ts.setTimestamp("29-FEV-2024-23:59"); // Ano bissexto
        if (ts.getTimestamp() == "29-FEV-2024-23:59") sucesso++; else falha++;
        ts.setTimestamp("31-DEZ-2099-00:00");
        if (ts.getTimestamp() == "31-DEZ-2099-00:00") sucesso++; else falha++;
    } catch (...) {
        falha++;
    }

    // Casos inválidos:
    // 29 de fevereiro em ano não bissexto
    try {
        ts.setTimestamp("29-FEV-2026-10:00");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // 31 de abril (mês de 30 dias)
    try {
        ts.setTimestamp("31-ABR-2026-10:00");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Hora inválida
    try {
        ts.setTimestamp("15-MAR-2026-24:00");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Minuto inválido
    try {
        ts.setTimestamp("15-MAR-2026-12:60");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Ano fora da faixa (< 2000)
    try {
        ts.setTimestamp("15-MAR-1999-12:00");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    // Mês inexistente
    try {
        ts.setTimestamp("15-XYZ-2026-12:00");
        falha++;
    } catch (const std::invalid_argument&) {
        sucesso++;
    }

    return falha == 0;
}

