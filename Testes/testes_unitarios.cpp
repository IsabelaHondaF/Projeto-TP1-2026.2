#include <iostream>
#include <vector>
#include <string>
#include "../Headers/testes_dominios.hpp"
#include "../Headers/testes_entidades.hpp"

int main() {
    std::cout << "====================================================\n";
    std::cout << " BATERIA DE TESTES DE UNIDADE: DOMINIOS E ENTIDADES \n";
    std::cout << "====================================================\n\n";

    int totalSucesso = 0;
    int totalFalha = 0;

    auto testar = [&](const std::string& nome, TesteUnitarioBase& teste, bool resultado) {
        std::cout << "[" << (resultado ? "OK" : "ERRO") << "] " << nome
                  << " (" << teste.getSucesso() << " verificacoes passaram";
        if (teste.getFalha() > 0) {
            std::cout << ", " << teste.getFalha() << " FALHARAM";
        }
        std::cout << ")\n";
        totalSucesso += teste.getSucesso();
        totalFalha += teste.getFalha();
    };

    std::cout << "-- Testes de Classes de Dominio --\n";
    TULimite tuLimite;
    testar("Dominio Limite", tuLimite, tuLimite.executar());

    TUSenha tuSenha;
    testar("Dominio Senha", tuSenha, tuSenha.executar());

    TUEstado tuEstado;
    testar("Dominio Estado", tuEstado, tuEstado.executar());

    TUPrioridade tuPrioridade;
    testar("Dominio Prioridade", tuPrioridade, tuPrioridade.executar());

    TUTamanho tuTamanho;
    testar("Dominio Tamanho", tuTamanho, tuTamanho.executar());

    TUNome tuNome;
    testar("Dominio Nome", tuNome, tuNome.executar());

    TUPapel tuPapel;
    testar("Dominio Papel", tuPapel, tuPapel.executar());

    TUTexto tuTexto;
    testar("Dominio Texto", tuTexto, tuTexto.executar());

    TUIdentificador tuIdentificador;
    testar("Dominio Identificador", tuIdentificador, tuIdentificador.executar());

    TUEmail tuEmail;
    testar("Dominio Email", tuEmail, tuEmail.executar());

    TUTimestamp tuTimestamp;
    testar("Dominio Timestamp", tuTimestamp, tuTimestamp.executar());

    std::cout << "\n-- Testes de Classes de Entidade --\n";
    TUPessoa tuPessoa;
    testar("Entidade Pessoa", tuPessoa, tuPessoa.executar());

    TUProjeto tuProjeto;
    testar("Entidade Projeto", tuProjeto, tuProjeto.executar());

    TUQuadro tuQuadro;
    testar("Entidade Quadro", tuQuadro, tuQuadro.executar());

    TUCartaoDeAtividade tuCartao;
    testar("Entidade CartaoDeAtividade", tuCartao, tuCartao.executar());

    std::cout << "\n====================================================\n";
    std::cout << "RESULTADO FINAL DOS TESTES DE UNIDADE:\n";
    std::cout << "Total de verificacoes bem-sucedidas: " << totalSucesso << "\n";
    std::cout << "Total de falhas: " << totalFalha << "\n";
    if (totalFalha == 0) {
        std::cout << "Status: 100% DOS TESTES PASSARAM COM SUCESSO!\n";
    } else {
        std::cout << "Status: HOUVE FALHAS NOS TESTES.\n";
    }
    std::cout << "====================================================\n";

    return totalFalha == 0 ? 0 : 1;
}
