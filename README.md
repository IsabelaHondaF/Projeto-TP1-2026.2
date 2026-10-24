<div align="center">
  <img width="300" height="150" alt="Símbolo da UnB" src="https://github.com/user-attachments/assets/3b50c780-d1e4-4b11-ac10-0dcac62b435f" />

  # Projeto-TP1-2026.2
  ### Trabalho Prático de Técnicas de Programação 1 — Universidade de Brasília (UnB)
  **Semestre:** 2026.2 &nbsp;|&nbsp; **Linguagem:** C++11 &nbsp;|&nbsp; **IDE:** Code::Blocks
</div>

---

## 👥 Integrantes da Equipe

| Nome | Função Principal |
|---|---|
| **Arthur Vieira** | Domínios, Entidades e Configuração Code::Blocks |
| **Gabriel Sales** | Interfaces Abstratas, Testes de Unidade e Documentação Doxygen |
| **Isabela Honda Ferreira** | Repositório GitHub, Domínios e Entidades |
| **João Roberto** | Serviços de Negócio, Apresentação e Integração |

> Para o detalhamento completo dos artefatos construídos por cada autor, consulte [EQUIPE_E_ARTEFATOS.md](file:///home/gabriel/projeto.tp1/Projeto-TP1-2026.2/EQUIPE_E_ARTEFATOS.md).

---

##  Especificações do Sistema

O sistema provê suporte à gestão de projetos pelo método Kanban:
- **Quadros Kanban:** compostos estritamente pelas colunas `A FAZER`, `FAZENDO` e `FEITO`.
- **Papéis:** `GESTOR` (cria projetos, quadros e cartões) e `DESENVOLVEDOR` (executa e move atividades).
- **Controle de WIP:** a coluna `FAZENDO` possui um `Limite` de cartões simultâneos (1 a 25).
- **Métricas:** cálculo de tempo de ciclo (*cycle time*), *lead time*, tempo de ciclo médio, *lead time* médio e *Work in Progress* (WIP).
- **Integridade:** exclusão de entidades preserva consistência dos relacionamentos e multiplicidades.

---

##  Arquitetura do Software

O sistema adota o padrão de arquitetura em camadas (*layers*) composto por 5 módulos:

```
[ Camada de Apresentação ] (cin/cout, menus estruturados por papel)
           |
           v (depende de interfaces abstratas)
[ Interfaces de Serviço  ] (IServicoPessoa, IServicoProjeto, IServicoQuadro, IServicoCartaoDeAtividade)
           ^
           | (implementam as interfaces)
[ Camada de Serviço      ] (regras de negócio, permissões, WIP e métricas temporais)
           |
           v
[ Contêineres em Memória ] (persistência e vínculos relacionais compartilhados)
           |
   [ Entidades e Domínios ] (modelagem OO e validações estritas de tipos com exceções)
```

- **Modelo de Arquitetura em PDF:** [Modelo_Arquitetura.pdf](file:///home/gabriel/projeto.tp1/Projeto-TP1-2026.2/Modelo_Arquitetura.pdf)
- **Documentação Técnica em HTML (Doxygen):** `Documentacao/html/index.html`
- **Documentação de Regras das Controladoras:** [DOCUMENTACAO_CONTROLADORAS.md](file:///home/gabriel/projeto.tp1/Projeto-TP1-2026.2/DOCUMENTACAO_CONTROLADORAS.md)

---

##  Como Compilar e Executar

### 1. Compilação via Makefile

```bash
# Compila todos os alvos (executável raiz, Debug, Release, SmokeTest e TestesUnitarios):
make all

# Executa todos os testes (unidade, fumaça das controladoras e teste integrado):
make test

# Gera a documentação Doxygen (HTML) e o PDF de Arquitetura:
make doc

# Gera o pacote ZIP no padrão de entrega (T1-TP1-X-Y-Z.ZIP):
make zip
```

### 2. Executando o Sistema Integrado

```bash
# Modo interativo:
./Projeto_TP1

# Modo de teste automatizado (cobre todos os 26 serviços do enunciado):
./Projeto_TP1 < Testes/roteiro_teste_fumaca.txt
```

### 3. Ambiente Code::Blocks

O arquivo de projeto [`Projeto_TP1.cbp`](file:///home/gabriel/projeto.tp1/Projeto-TP1-2026.2/Projeto_TP1.cbp) está configurado com 4 alvos independentes:
- **`Debug`**: compilação do sistema completo com flags de depuração (`-g`).
- **`Release`**: compilação otimizada do sistema (`-O2 -s`).
- **`SmokeTest`**: executa a suíte de teste de fumaça das controladoras de serviço (75 asserções).
- **`TestesUnitarios`**: executa a bateria de testes de unidade de domínios e entidades (106 asserções).

---

##  Suítes de Testes

1. **Testes de Unidade (`make test_unit`):**
   Valida as 11 classes de domínio e as 4 entidades com casos válidos e limites inválidos (`std::invalid_argument`).
2. **Testes de Fumaça das Controladoras (`make test_smoke`):**
   Valida as 26 operações de serviço, regras de permissão (GESTOR vs. DESENVOLVEDOR), WIP e consistência de exclusão.
3. **Teste de Fumaça Integrado (`make test_integrated`):**
   Simula a interação com o usuário em 4 sessões consecutivas cobrindo todos os requisitos funcionais sem erros.

Para instruções completas sobre o vídeo de demonstração, consulte [Testes/LEIA-ME_TESTE_FUMACA.md](file:///home/gabriel/projeto.tp1/Projeto-TP1-2026.2/Testes/LEIA-ME_TESTE_FUMACA.md).
