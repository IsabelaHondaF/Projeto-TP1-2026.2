#include "../Headers/apresentacao.hpp"
#include "../Headers/controladoras_servico.hpp"
#include "../Headers/banco_dados.hpp"
#include <iostream>
#include <stdexcept>

/**
 * @brief Inicializa o banco de dados, as controladoras e a apresentação.
 *
 * Os quatro contêineres compartilham a conexão SQLite. As controladoras de
 * serviço e a apresentação continuam ligadas por meio das interfaces.
 *
 * @return 0 ao encerrar normalmente; 1 em caso de falha de acesso ao banco.
 */
int main() {
    try {
        // O arquivo é relativo ao diretório de execução. O banco é criado antes
        // dos contêineres para que sua conexão seja fechada somente depois deles.
        BancoDados banco("kanban.db");
        ContainerPessoas pessoas(banco);
        ContainerProjetos projetos(banco);
        ContainerQuadros quadros(banco);
        ContainerCartoes cartoes(banco);

        CntrServicoPessoa servicoPessoa(pessoas, projetos, cartoes);
        CntrServicoProjeto servicoProjeto(pessoas, projetos, quadros);
        CntrServicoQuadro servicoQuadro(pessoas, projetos, quadros, cartoes);

        CntrApresentacaoPessoa apresentacaoPessoa(&servicoPessoa);
        CntrApresentacaoProjeto apresentacaoProjeto(&servicoProjeto);
        CntrApresentacaoQuadro apresentacaoQuadro(&servicoQuadro);

        CntrApresentacaoPrincipal apresentacao(
            &servicoPessoa,
            apresentacaoPessoa,
            apresentacaoProjeto,
            apresentacaoQuadro
        );

        apresentacao.executar();
        return 0;
    } catch (const std::runtime_error& erro) {
        std::cerr << "[ERRO] Falha no acesso ao banco de dados: " << erro.what() << '\n';
        return 1;
    }
}
