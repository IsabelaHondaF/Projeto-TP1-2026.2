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
| **Gabriel Sales** | Entidades, Interfaces Abstratas, Testes de Unidade e Documentação Doxygen |
| **Isabela Honda Ferreira** | Repositório GitHub |
| **João Roberto Machado** | Serviços de Negócio, Apresentação, Integração e Domínios |

> Para o detalhamento completo dos artefatos construídos por cada autor, consulte `EQUIPE_E_ARTEFATOS.md`.

---

##  Especificações do Sistema

O sistema provê suporte à gestão de projetos pelo método Kanban:
- **Quadros Kanban:** compostos estritamente pelas colunas `A FAZER`, `FAZENDO` e `FEITO`.
- **Papéis:** `GESTOR` (cria projetos, quadros e cartões) e `DESENVOLVEDOR` (executa e move atividades).
- **Controle de WIP:** a coluna `FAZENDO` possui um `Limite` de cartões simultâneos (1 a 25).
- **Métricas:** cálculo de tempo de ciclo (*cycle time*), *lead time*, tempo de ciclo médio, *lead time* médio e *Work in Progress* (WIP).
- **Integridade:** exclusão de entidades preserva consistência dos relacionamentos e multiplicidades.
- **Persistência:** pessoas, projetos, quadros e cartões são armazenados em um banco de dados relacional SQLite e permanecem disponíveis entre execuções.

---

##  Arquitetura do Software


O sistema adota o estilo de arquitetura em duas camadas,
organizadas em três subsistemas: Pessoa, Projeto e Quadro.

- **Apresentação:** módulos MAC, MAA, MAP e MAQ, responsáveis
  pela navegação, interação com o usuário e validação das entradas.
- **Serviço:** módulos MSA, MSP e MSQ, responsáveis pelas regras
  de negócio, permissões e integridade dos relacionamentos,
  com acesso aos dados por meio dos repositórios.

O subsistema Quadro incorpora o gerenciamento dos cartões de
atividade, sua movimentação, o controle de WIP e a consulta de
métricas. Essas funcionalidades são implementadas por MAQ e MSQ.

A comunicação entre os módulos ocorre por seis interfaces abstratas:

- **Apresentação:** IAA (`IApresentacaoPessoa`),
  IAP (`IApresentacaoProjeto`) e IAQ (`IApresentacaoQuadro`).
- **Serviço:** ISA (`IServicoPessoa`),
  ISP (`IServicoProjeto`) e ISQ (`IServicoQuadro`).

MAC depende de IAA, IAP e IAQ para acessar os subsistemas.
Também depende de ISA para consultar os dados e o papel do
usuário autenticado.

MAA solicita operações por meio de ISA, MAP utiliza ISP e
MAQ utiliza ISQ para as operações de quadros e cartões.

Os contêineres implementam os repositórios SQL utilizados
pela camada de serviço. Um objeto `BancoDados` gerencia a conexão
SQLite compartilhada pelos quatro contêineres e a criação das tabelas.
As classes de domínio e entidade
representam os dados utilizados pelas duas camadas.

- **Modelo de Arquitetura em PDF:** `Documentacao/Modelo_Arquitetura.pdf`
- **Documentação Técnica em HTML (Doxygen):** `Documentacao/html/index.html`
- **Documentação de Regras das Controladoras:** `DOCUMENTACAO_CONTROLADORAS.md`

---

##  Como Compilar e Executar

### Dependência SQLite

Além do compilador com suporte a C++11 e do Make, a compilação dos alvos que acessam o banco requer o cabeçalho `sqlite3.h` e a biblioteca SQLite disponível para vinculação com `-lsqlite3`.

Em Debian/Ubuntu, instale os arquivos de desenvolvimento:

```bash
sudo apt update
sudo apt install libsqlite3-dev
```

O pacote `libsqlite3-dev` está disponível nos repositórios oficiais do [Debian](https://packages.debian.org/stable/libsqlite3-dev) e do [Ubuntu](https://packages.ubuntu.com/noble/libsqlite3-dev). Em outros ambientes, disponibilize o cabeçalho e a biblioteca SQLite para o compilador utilizado.

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
make test_integrated
```

Na execução interativa, o programa cria ou abre `kanban.db` no diretório de execução. Para recuperar os mesmos dados, execute novamente a partir desse diretório.

O alvo `make test_integrated` utiliza `Testes/roteiro_teste_fumaca.txt` em um diretório temporário, preservando o banco de uso normal. O diretório e o banco de teste são removidos ao terminar.

### 3. Ambiente Code::Blocks

O arquivo de projeto `Projeto_TP1.cbp` está configurado com 4 alvos independentes:
- **`Debug`**: compilação do sistema completo com flags de depuração (`-g`).
- **`Release`**: compilação otimizada do sistema (`-O2 -s`).
- **`SmokeTest`**: executa a suíte de teste de fumaça das controladoras de serviço (75 asserções).
- **`TestesUnitarios`**: executa a bateria de testes de unidade de domínios e entidades (106 asserções).

Os alvos `Debug`, `Release` e `SmokeTest` incluem `BancoDados/banco_dados.cpp` e vinculam a biblioteca `sqlite3`. O cabeçalho `Headers/banco_dados.hpp` também está incluído no projeto. O alvo `TestesUnitarios` permanece independente do banco.

Abra o `Projeto_TP1.cbp` atualizado após instalar a dependência SQLite. Nos alvos `Debug` e `Release`, o diretório de execução determina a localização de `kanban.db`; utilize o mesmo diretório para acessar os mesmos dados nos dois alvos.

---

##  Persistência com SQLite

O banco contém as tabelas `pessoas`, `projetos`, `quadros` e `cartoes`. As chaves estrangeiras associam projetos aos seus gestores, quadros aos projetos e cartões aos quadros e desenvolvedores. A exclusão de registros ainda referenciados é restringida pelo banco, em conjunto com as verificações existentes nas controladoras.

| Arquivos | Responsabilidade |
|---|---|
| `Headers/banco_dados.hpp` e `BancoDados/banco_dados.cpp` | Abrir e fechar a conexão, habilitar as chaves estrangeiras e criar as tabelas e os índices ausentes. |
| `Headers/repositorios.hpp` e `Repositorios/repositorios.cpp` | Executar as operações SQL de pessoas, projetos, quadros e cartões por meio dos quatro contêineres. |

Ao iniciar, o programa prepara a estrutura do banco preservando os registros existentes. Ao encerrar, fecha a conexão e mantém o arquivo `kanban.db`, permitindo consultar os dados em uma nova execução. As regras de domínio, permissões, movimentação dos cartões e cálculo das métricas continuam nas classes correspondentes.

---

##  Suítes de Testes

1. **Testes de Unidade (`make test_unit`):**
   Valida as 11 classes de domínio e as 4 entidades com casos válidos e limites inválidos (`std::invalid_argument`).
2. **Testes de Fumaça das Controladoras (`make test_smoke`):**
   Valida as 26 operações de serviço, regras de permissão (GESTOR vs. DESENVOLVEDOR), WIP e consistência de exclusão.
   Utiliza SQLite em memória (`:memory:`), com um banco vazio em cada execução, sem criar ou alterar `kanban.db`.
3. **Teste de Fumaça Integrado (`make test_integrated`):**
   Simula a interação com o usuário em 4 sessões consecutivas cobrindo todos os requisitos funcionais sem erros.
   Utiliza um arquivo de banco exclusivo em um diretório temporário, removido ao final do teste.

Para instruções completas sobre o vídeo de demonstração, consulte `Testes/LEIA-ME_TESTE_FUMACA.md`.

O mesmo guia inclui, na seção 4, um roteiro complementar para verificar a persistência em disco: cadastrar uma conta, encerrar o executável e confirmar que a conta pode ser autenticada e consultada ao reabrir o programa no mesmo diretório. O `SmokeTest` em memória verifica os serviços, mas não a conservação dos dados entre processos.
