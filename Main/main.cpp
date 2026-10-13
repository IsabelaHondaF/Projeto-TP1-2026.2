#include "../Headers/apresentacao.hpp"
#include "../Headers/controladoras_servico.hpp"

/**
 * Ponto de entrada: instancia o armazenamento em memória, as controladoras de
 * serviço e a camada de apresentação, ligando-as por meio das interfaces.
 */
int main() {
    ContainerPessoas pessoas;
    ContainerProjetos projetos;
    ContainerQuadros quadros;
    ContainerCartoes cartoes;

    CntrServicoPessoa servicoPessoa(pessoas, projetos, cartoes);
    CntrServicoProjeto servicoProjeto(pessoas, projetos, quadros);
    CntrServicoQuadro servicoQuadro(pessoas, projetos, quadros, cartoes);
    CntrServicoCartaoDeAtividade servicoCartao(pessoas, projetos, quadros, cartoes);

    CntrApresentacaoPrincipal apresentacao(&servicoPessoa, &servicoProjeto,
                                           &servicoQuadro, &servicoCartao);
    apresentacao.executar();
    return 0;
}
