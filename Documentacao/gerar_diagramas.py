#!/usr/bin/env python3
import os
import shutil
os.environ['MPLCONFIGDIR'] = '/tmp/mpl_config'
import matplotlib.pyplot as plt
import matplotlib.patches as patches

def criar_diagrama_modulos(caminho_saida):
    pasta_documentacao = os.path.dirname(os.path.abspath(__file__))
    imagem_atual = os.path.join(
        pasta_documentacao,
        "Diagrama_Arquitetura.png"
    )

    shutil.copyfile(imagem_atual, caminho_saida)
    print(f"Diagrama de módulos atualizado em {caminho_saida}")


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
