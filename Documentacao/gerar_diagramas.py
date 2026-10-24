#!/usr/bin/env python3
import os
os.environ['MPLCONFIGDIR'] = '/tmp/mpl_config'
import matplotlib.pyplot as plt
import matplotlib.patches as patches

def criar_diagrama_modulos(caminho_saida):
    fig, ax = plt.subplots(figsize=(13, 9), dpi=300)
    ax.set_xlim(0, 130)
    ax.set_ylim(0, 90)
    ax.axis('off')

    # Paleta de cores formal e profissional
    c_apresentacao_bg = '#E8F1F5'
    c_apresentacao_border = '#005691'
    c_interface_bg = '#FFFFFF'
    c_interface_border = '#0B3C5D'
    c_servico_bg = '#EAF5EA'
    c_servico_border = '#1B5E20'
    c_dados_bg = '#FFF8E7'
    c_dados_border = '#C67D00'
    c_entidades_bg = '#FDE8E8'
    c_entidades_border = '#B71C1C'
    c_dominios_bg = '#F3E8FD'
    c_dominios_border = '#6A1B9A'

    # 1. Módulo Apresentação
    rect_apres = patches.FancyBboxPatch((10, 72), 110, 14, boxstyle="round,pad=0.8,rounding_size=1.5",
                                        facecolor=c_apresentacao_bg, edgecolor=c_apresentacao_border, linewidth=2)
    ax.add_patch(rect_apres)
    # Tab do pacote
    tab_apres = patches.FancyBboxPatch((10, 84), 36, 4, boxstyle="round,pad=0.4,rounding_size=0.8",
                                       facecolor=c_apresentacao_border, edgecolor=c_apresentacao_border)
    ax.add_patch(tab_apres)
    ax.text(28, 86, "«módulo» Apresentação", ha='center', va='center', color='white', fontsize=9, fontweight='bold')
    ax.text(65, 80.5, "Camada de Apresentação (Interface com Usuário - cin / cout)", ha='center', va='center',
            color='#0B3C5D', fontsize=11, fontweight='bold')
    ax.text(65, 76, "Controladoras: CntrApresentacaoPrincipal  |  CntrApresentacaoPessoa  |  CntrApresentacaoProjeto\n"
                      "CntrApresentacaoQuadro  |  CntrApresentacaoCartao   •   (Validação de entrada via Domínios)",
            ha='center', va='center', color='#333333', fontsize=9)

    # 2. Interfaces de Serviço (Abstração / Contrato)
    interfaces = [
        ("IServicoPessoa", 22),
        ("IServicoProjeto", 51),
        ("IServicoQuadro", 79),
        ("IServicoCartaoDeAtividade", 108)
    ]

    for nome, x in interfaces:
        w = 24 if nome != "IServicoCartaoDeAtividade" else 26
        rect_if = patches.FancyBboxPatch((x - w/2, 54), w, 8.5, boxstyle="round,pad=0.5,rounding_size=1.0",
                                         facecolor=c_interface_bg, edgecolor=c_interface_border, linewidth=1.8)
        ax.add_patch(rect_if)
        ax.text(x, 59.8, "«interface»", ha='center', va='center', color='#555555', fontsize=8, fontstyle='italic')
        ax.text(x, 56.5, nome, ha='center', va='center', color='#0B3C5D', fontsize=9, fontweight='bold')

        # Flecha de Dependência (Apresentação ..> Interface)
        ax.annotate('', xy=(x, 62.5), xytext=(x, 72),
                    arrowprops=dict(arrowstyle="->", linestyle="dashed", color="#005691", lw=1.5))
        # Flecha de Realização (Serviço --|> Interface)
        ax.annotate('', xy=(x, 54), xytext=(x, 44),
                    arrowprops=dict(arrowstyle="-|>", linestyle="dashed", color="#1B5E20", lw=1.5,
                                    mutation_scale=12, facecolor='white'))

    # Legenda das flechas no meio
    ax.text(5, 67, "«use» (dependência)", ha='left', va='center', color='#005691', fontsize=8, fontstyle='italic')
    ax.text(5, 48, "«realize» (implementação)", ha='left', va='center', color='#1B5E20', fontsize=8, fontstyle='italic')

    # 3. Módulo Serviço
    rect_serv = patches.FancyBboxPatch((10, 30), 110, 14, boxstyle="round,pad=0.8,rounding_size=1.5",
                                       facecolor=c_servico_bg, edgecolor=c_servico_border, linewidth=2)
    ax.add_patch(rect_serv)
    tab_serv = patches.FancyBboxPatch((10, 42), 30, 4, boxstyle="round,pad=0.4,rounding_size=0.8",
                                      facecolor=c_servico_border, edgecolor=c_servico_border)
    ax.add_patch(tab_serv)
    ax.text(25, 44, "«módulo» Serviço", ha='center', va='center', color='white', fontsize=9, fontweight='bold')
    ax.text(65, 38.5, "Camada de Negócio (Regras, Permissões e Métricas Kanban)", ha='center', va='center',
            color='#1B5E20', fontsize=11, fontweight='bold')
    ax.text(65, 34, "Controladoras: CntrServicoPessoa  |  CntrServicoProjeto  |  CntrServicoQuadro  |  CntrServicoCartaoDeAtividade\n"
                      "Regras: Permissões Gestor vs. Dev  •  Transições A FAZER → FAZENDO → FEITO  •  WIP  •  Tempo Ciclo / Lead Time",
            ha='center', va='center', color='#222222', fontsize=9)

    # 4. Módulo Repositórios / Contêineres
    rect_cont = patches.FancyBboxPatch((10, 7), 38, 14, boxstyle="round,pad=0.8,rounding_size=1.5",
                                       facecolor=c_dados_bg, edgecolor=c_dados_border, linewidth=1.8)
    ax.add_patch(rect_cont)
    ax.text(29, 18, "«módulo» Repositórios", ha='center', va='center', color='#C67D00', fontsize=9.5, fontweight='bold')
    ax.text(29, 13, "ContainerPessoas\nContainerProjetos\nContainerQuadros\nContainerCartoes",
            ha='center', va='center', color='#333333', fontsize=8.5)

    # 5. Módulo Entidades
    rect_ent = patches.FancyBboxPatch((53, 7), 35, 14, boxstyle="round,pad=0.8,rounding_size=1.5",
                                      facecolor=c_entidades_bg, edgecolor=c_entidades_border, linewidth=1.8)
    ax.add_patch(rect_ent)
    ax.text(70.5, 18, "«módulo» Entidades", ha='center', va='center', color='#B71C1C', fontsize=9.5, fontweight='bold')
    ax.text(70.5, 13, "Pessoa\nProjeto\nQuadro\nCartaoDeAtividade",
            ha='center', va='center', color='#333333', fontsize=8.5)

    # 6. Módulo Domínios
    rect_dom = patches.FancyBboxPatch((93, 7), 27, 14, boxstyle="round,pad=0.8,rounding_size=1.5",
                                      facecolor=c_dominios_bg, edgecolor=c_dominios_border, linewidth=1.8)
    ax.add_patch(rect_dom)
    ax.text(106.5, 18, "«módulo» Domínios", ha='center', va='center', color='#6A1B9A', fontsize=9.5, fontweight='bold')
    ax.text(106.5, 12.5, "Email, Identificador,\nNome, Senha, Papel,\nTexto, Limite, Prioridade,\nEstado, Tamanho, Timestamp",
            ha='center', va='center', color='#333333', fontsize=7.5)

    # Conexões Serviço -> Contêineres, Entidades, Domínios
    ax.annotate('', xy=(29, 21), xytext=(29, 30),
                arrowprops=dict(arrowstyle="->", color="#C67D00", lw=1.5))
    ax.annotate('', xy=(70.5, 21), xytext=(70.5, 30),
                arrowprops=dict(arrowstyle="->", color="#B71C1C", lw=1.5))
    ax.annotate('', xy=(106.5, 21), xytext=(106.5, 30),
                arrowprops=dict(arrowstyle="->", color="#6A1B9A", lw=1.5))

    # Título do Diagrama
    ax.text(65, 2, "Figura 1 — Diagrama UML de Módulos, Componentes e Interfaces da Arquitetura em Camadas",
            ha='center', va='center', color='#444444', fontsize=9.5, fontstyle='italic')

    plt.tight_layout()
    fig.savefig(caminho_saida, bbox_inches='tight', dpi=300)
    plt.close(fig)
    print(f"Diagrama de módulos gerado em {caminho_saida}")


def criar_diagrama_entidades(caminho_saida):
    fig, ax = plt.subplots(figsize=(13, 9), dpi=300)
    ax.set_xlim(0, 130)
    ax.set_ylim(0, 95)
    ax.axis('off')

    c_box_bg = '#FFFFFF'
    c_box_header = '#0B3C5D'
    c_box_border = '#0B3C5D'

    def desenhar_entidade(x, y, w, h, titulo, atributos):
        # Caixa principal
        rect = patches.FancyBboxPatch((x, y), w, h, boxstyle="round,pad=0.5,rounding_size=1.0",
                                      facecolor=c_box_bg, edgecolor=c_box_border, linewidth=1.8)
        ax.add_patch(rect)
        # Cabeçalho
        h_head = 6.0
        rect_head = patches.FancyBboxPatch((x, y + h - h_head), w, h_head, boxstyle="round,pad=0.5,rounding_size=1.0",
                                          facecolor=c_box_header, edgecolor=c_box_border, linewidth=1.8)
        ax.add_patch(rect_head)
        ax.text(x + w/2, y + h - h_head/2, titulo, ha='center', va='center',
                color='white', fontsize=11, fontweight='bold')

        # Linha separadora do cabeçalho
        ax.plot([x, x + w], [y + h - h_head, y + h - h_head], color=c_box_border, lw=1.8)

        # Atributos
        curr_y = y + h - h_head - 3.2
        for at in atributos:
            peso = 'bold' if '«PK»' in at else 'normal'
            cor = '#0B3C5D' if '«PK»' in at else '#222222'
            ax.text(x + 2.0, curr_y, at, ha='left', va='center', color=cor, fontsize=9.2, fontweight=peso)
            curr_y -= 3.2

    # 1. Classe Pessoa
    desenhar_entidade(
        10, 52, 34, 25, "Pessoa",
        [
            "- «PK» email : Email",
            "- nome : Nome",
            "- senha : Senha",
            "- papel : Papel"
        ]
    )

    # 2. Classe Projeto
    desenhar_entidade(
        10, 12, 34, 28, "Projeto",
        [
            "- «PK» identificador : Identificador",
            "- nome : Nome",
            "- descrição : Texto",
            "- início : Timestamp",
            "- término : Timestamp"
        ]
    )

    # 3. Classe Quadro
    desenhar_entidade(
        52, 12, 32, 22, "Quadro",
        [
            "- «PK» identificador : Identificador",
            "- nome : Nome",
            "- limite : Limite"
        ]
    )

    # 4. Classe CartaoDeAtividade
    desenhar_entidade(
        92, 12, 34, 38, "Cartão de Atividade",
        [
            "- «PK» identificador : Identificador",
            "- nome : Nome",
            "- descrição : Texto",
            "- prioridade : Prioridade",
            "- estado : Estado",
            "- tamanho : Tamanho",
            "- entrada : Timestamp",
            "- início : Timestamp",
            "- término : Timestamp"
        ]
    )

    # Linha e Multiplicidade 1: Pessoa (1 - Gestor) ---- (0..*) Projeto
    ax.plot([27, 27], [52, 40], color='#222222', lw=1.8)
    ax.text(28.5, 49, "1  (Gestor)", fontsize=8.5, fontweight='bold', color='#0B3C5D')
    ax.text(28.5, 42, "0..*", fontsize=8.5, fontweight='bold', color='#0B3C5D')

    # Linha e Multiplicidade 2: Projeto (1) ---- (0..*) Quadro
    ax.plot([44, 52], [23, 23], color='#222222', lw=1.8)
    ax.text(45, 24.5, "1", fontsize=8.5, fontweight='bold', color='#0B3C5D')
    ax.text(49.5, 24.5, "0..*", fontsize=8.5, fontweight='bold', color='#0B3C5D')

    # Linha e Multiplicidade 3: Quadro (1) ---- (0..*) Cartão de Atividade
    ax.plot([84, 92], [23, 23], color='#222222', lw=1.8)
    ax.text(85, 24.5, "1", fontsize=8.5, fontweight='bold', color='#0B3C5D')
    ax.text(89.5, 24.5, "0..*", fontsize=8.5, fontweight='bold', color='#0B3C5D')

    # Linha e Multiplicidade 4: Pessoa (1 - Desenvolvedor) ---- (0..*) Cartão de Atividade
    ax.plot([44, 109], [64, 64], color='#222222', lw=1.8)
    ax.plot([109, 109], [64, 50], color='#222222', lw=1.8)
    ax.text(46, 65.5, "1  (Desenvolvedor)", fontsize=8.5, fontweight='bold', color='#0B3C5D')
    ax.text(110.5, 52, "0..*", fontsize=8.5, fontweight='bold', color='#0B3C5D')

    # Título do Diagrama
    ax.text(65, 87, "Figura 2 — Diagrama de Classes Entidade, Tipagem por Domínios e Multiplicidades (UML)",
            ha='center', va='center', color='#333333', fontsize=11, fontweight='bold')

    plt.tight_layout()
    fig.savefig(caminho_saida, bbox_inches='tight', dpi=300)
    plt.close(fig)
    print(f"Diagrama de entidades gerado em {caminho_saida}")


if __name__ == '__main__':
    os.makedirs('Documentacao', exist_ok=True)
    criar_diagrama_modulos('Documentacao/diagrama_modulos.png')
    criar_diagrama_entidades('Documentacao/diagrama_entidades.png')
