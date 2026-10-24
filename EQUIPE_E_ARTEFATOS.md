# Identificação da Equipe e Artefatos Construídos

**Universidade de Brasília (UnB)**  
**Instituto de Ciências Exatas (IE) — Departamento de Ciência da Computação (CIC)**  
**Disciplina:** Técnicas de Programação 1 (TP1) — Semestre 2026.2  
**Trabalho Prático:** Sistema Kanban de Gestão de Projetos  

---

## 1. Membros da Equipe

| Nome Completo | Matrícula | Função Principal / Responsabilidade |
|---|---|---|
| **Arthur Vieira** | `[Inserir Matrícula Arthur]` | Modelagem de Domínios e Entidades |
| **Gabriel Sales** | `[Inserir Matrícula Gabriel]` | Interfaces entre Módulos e Testes de Unidade |
| **Isabela Honda Ferreira** | `[Inserir Matrícula Isabela]` | Repositório, Domínios e Entidades |
| **João Roberto** | `[Inserir Matrícula João]` | Camada de Serviço, Apresentação e Integração |

> **Nota:** Antes do empacotamento final de entrega (`T1-TP1-X-Y-Z-W.ZIP`), cada membro deve preencher seu respectivo número de matrícula nos campos acima e no nome do arquivo ZIP conforme a regra 33 e 34 do enunciado.

---

## 2. Mapeamento de Artefatos por Membro da Equipe

### Arthur Vieira
- Modelagem e especificação das classes de domínio: `Limite`, `Senha`, `Estado`, `Prioridade`, `Tamanho`.
- Estruturação inicial do projeto Code::Blocks (`Projeto_TP1.cbp`).
- Implementação inicial de classes de entidade e diagramas estruturais.

### Gabriel Sales
- Especificação e codificação das interfaces abstratas de serviço:
  - `IServicoQuadro` (operações de criação, leitura, atualização, exclusão e listagem de quadros).
  - `IServicoCartaoDeAtividade` (ciclo de vida de cartões, movimentações e métricas Kanban).
- Documentação técnica das interfaces com Doxygen.
- Elaboração e codificação dos testes de unidade exaustivos:
  - `Headers/testes_dominios.hpp` e `Testes/testes_dominios.cpp` (11 classes de domínio).
  - `Headers/testes_entidades.hpp` e `Testes/testes_entidades.cpp` (4 classes de entidade).
  - Ponto de entrada de testes de unidade: `Testes/testes_unitarios.cpp`.

### Isabela Honda Ferreira
- Criação e administração do repositório no GitHub.
- Implementação das classes de domínio: `Email`, `Timestamp` e validações de calendário/bissexto.
- Implementação das entidades `Pessoa` e `Projeto` em `Headers/entidades.hpp` e `Entidades/entidades.cpp`.
- Revisão ortográfica, conformidade com os padrões de codificação e diretrizes da especificação.

### João Roberto
- Implementação das interfaces abstratas `IServicoPessoa` e `IServicoProjeto`.
- Implementação dos contêineres de dados em memória:
  - `Headers/repositorios.hpp` e `Repositorios/repositorios.cpp` (`ContainerPessoas`, `ContainerProjetos`, `ContainerQuadros`, `ContainerCartoes`).
- Implementação completa da Camada de Serviço:
  - `Headers/controladoras_servico.hpp` e `Servicos/controladoras_servico.cpp` (regras de negócio, permissões Gestor vs. Desenvolvedor, cálculo de Lead Time, Cycle Time e WIP).
- Implementação da Camada de Apresentação interativa via terminal:
  - `Headers/apresentacao.hpp` e `Apresentacao/apresentacao.cpp` (`CntrApresentacaoPrincipal`, menus por papel, validação de entrada).
- Integração global das camadas em `Main/main.cpp`.
- Suíte de testes de fumaça das controladoras (`Testes/smoke_test_controladoras.cpp`).

---

## 3. Inventário Consolidado de Artefatos do Projeto

### Código-Fonte e Cabeçalhos
- **Domínios (11 classes):** `Headers/dominios.hpp`, `Dominios/dominios.cpp`
- **Entidades (4 classes):** `Headers/entidades.hpp`, `Entidades/entidades.cpp`
- **Interfaces Abstratas (4 interfaces, 26 serviços):** `Headers/interfaces.hpp`
- **Contêineres / Repositórios em Memória:** `Headers/repositorios.hpp`, `Repositorios/repositorios.cpp`
- **Controladoras de Serviço:** `Headers/controladoras_servico.hpp`, `Servicos/controladoras_servico.cpp`
- **Controladoras de Apresentação:** `Headers/apresentacao.hpp`, `Apresentacao/apresentacao.cpp`
- **Ponto de Entrada Integrado:** `Main/main.cpp`

### Testes e Verificação de Qualidade
- **Testes de Unidade de Domínios:** `Headers/testes_dominios.hpp`, `Testes/testes_dominios.cpp` (106 asserções)
- **Testes de Unidade de Entidades:** `Headers/testes_entidades.hpp`, `Testes/testes_entidades.cpp`
- **Driver de Execução de Unidade:** `Testes/testes_unitarios.cpp`
- **Teste de Fumaça das Controladoras:** `Testes/smoke_test_controladoras.cpp` (75 asserções)
- **Roteiro de Teste de Fumaça Integrado:** `Testes/roteiro_teste_fumaca.txt` (cobre todos os 26 serviços)
- **Guia do Teste de Fumaça e Roteiro de Vídeo:** `Testes/LEIA-ME_TESTE_FUMACA.md`

### Modelagem e Documentação
- **Modelo de Arquitetura de Software em PDF:** `Modelo_Arquitetura.pdf` (e `Documentacao/Modelo_Arquitetura.pdf`)
- **Documentação Técnica em HTML gerada pelo Doxygen:** pasta `Documentacao/html/index.html`
- **Configuração Doxygen:** `Doxyfile`
- **Projeto Code::Blocks:** `Projeto_TP1.cbp` (alvos: Debug, Release, SmokeTest, TestesUnitarios)
- **Automação de Build e Empacotamento:** `Makefile`
- **Documentação de Arquitetura e Regras:** `DOCUMENTACAO_CONTROLADORAS.md`, `README.md`
