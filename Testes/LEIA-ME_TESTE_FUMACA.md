# Guia de Testes e Roteiro de Demonstração (Vídeo)

Este documento orienta a execução dos testes e fornece um roteiro detalhado para a gravação do vídeo de demonstração do teste de fumaça (*smoke test*) do sistema integrado, em estrita conformidade com os requisitos da disciplina.

---

## 1. Roteiro Narrado para Gravação do Vídeo de Demonstração

Para atender ao **Requisito 4.26, 4.27 e Critério 6** da avaliação (100% de pontuação), o vídeo deve demonstrar a execução com sucesso do código integrado do sistema cobrindo um cenário de sucesso para cada uma das 26 funcionalidades.

### Como gravar o vídeo (Duração recomendada: 3 a 7 minutos)
1. Abra o terminal (ou o Code::Blocks) e mostre a pasta raiz do projeto.
2. Apresente os membros da equipe: **Arthur Vieira, Gabriel Sales, Isabela Honda Ferreira e João Roberto**.
3. Execute o programa integrado via terminal, com um banco temporário exclusivo para a demonstração:
   ```bash
   make test_integrated
   ```
   Esse alvo utiliza o mesmo `Testes/roteiro_teste_fumaca.txt`, mas executa o programa em um diretório temporário para preservar o `kanban.db` de uso normal. O diretório de teste é removido ao terminar.
   *(Para digitar manualmente os passos descritos abaixo, prepare um diretório separado como indicado na seção 4 e execute o programa a partir dele.)*
4. Destaque durante a apresentação as 4 fases do teste:

#### Fase 1: Sessão do Gestor (Criação de Entidades e Contas)
- **Serviço 1 (Criar Pessoa):** Criação das contas `gestor@example.com` (Gestor) e `dev@example.com` (Desenvolvedor).
- **Autenticação:** Login com sucesso de `gestor@example.com`.
- **Serviços 2, 3, 5 (Ler, Atualizar e Listar Pessoa):** Consulta da conta do desenvolvedor, atualização do nome/senha da própria conta e listagem dos usuários.
- **Serviços 6, 7, 8, 10 (Criar, Ler, Atualizar e Listar Projeto):** Criação do projeto `PRJ001`, leitura dos dados, atualização de período e listagem.
- **Serviços 11, 12, 13, 15 (Criar, Ler, Atualizar e Listar Quadro):** Criação do quadro `QUA001` (com colunas A FAZER, FAZENDO, FEITO e limite de WIP = 2), leitura, atualização do limite e listagem.
- **Serviços 16, 17, 18, 20 (Criar, Ler, Atualizar e Listar Cartão):** Criação dos cartões `CAR001` e `CAR002` atribuídos a `dev@example.com`, leitura, atualização de dados e listagem.

#### Fase 2: Sessão do Desenvolvedor (Fluxo Kanban e Métricas)
- **Autenticação:** Login de `dev@example.com`.
- **Serviço 21 (Mover Cartão):**
  - Move `CAR001` de **A FAZER** para **FAZENDO**.
  - Move `CAR002` de **A FAZER** para **FAZENDO**.
  - Move `CAR001` de **FAZENDO** para **FEITO**.
  - Move `CAR002` de **FAZENDO** para **FEITO**.
- **Serviço 26 (Ler WIP):** Demonstração do WIP do quadro variando de 0 para 2 e retornando a 0.
- **Serviço 22 (Ler Tempo de Ciclo):** Leitura do tempo de ciclo do cartão concluído (150 minutos).
- **Serviço 23 (Ler Tempo de Ciclo Médio):** Leitura da média do quadro (165.0 minutos).
- **Serviço 24 (Ler Lead Time):** Leitura do lead time do cartão (210 minutos).
- **Serviço 25 (Ler Lead Time Médio):** Leitura da média de lead time do quadro (240.0 minutos).

#### Fase 3: Exclusões Consistentes
- **Serviço 19 (Excluir Cartão):** Gestor exclui os cartões concluídos.
- **Serviço 14 (Excluir Quadro):** Gestor exclui o quadro desocupado.
- **Serviço 9 (Excluir Projeto):** Gestor exclui o projeto.
- **Serviço 4 (Excluir Pessoa):** Cada usuário exclui com sucesso a sua própria conta sem deixar pendências.

---

## 2. Mapa dos 26 Serviços Funcionais do Enunciado

| ID | Serviço | Entidade | Papéis Permitidos | Como Acionar no Menu |
|---|---|---|---|---|
| 1 | CRIAR | PESSOA | GESTOR, DESENVOLVEDOR | Tela Inicial → `2` |
| 2 | LER | PESSOA | GESTOR, DESENVOLVEDOR | Menu Principal → `1` → `2` |
| 3 | ATUALIZAR | PESSOA | GESTOR, DESENVOLVEDOR | Menu Principal → `1` → `3` |
| 4 | EXCLUIR | PESSOA | GESTOR, DESENVOLVEDOR | Menu Principal → `1` → `4` |
| 5 | LISTAR | PESSOA | GESTOR, DESENVOLVEDOR | Menu Principal → `1` → `5` |
| 6 | CRIAR | PROJETO | GESTOR | Menu Principal → `2` → `1` |
| 7 | LER | PROJETO | GESTOR, DESENVOLVEDOR | Menu Principal → `2` → `2` |
| 8 | ATUALIZAR | PROJETO | GESTOR | Menu Principal → `2` → `3` |
| 9 | EXCLUIR | PROJETO | GESTOR | Menu Principal → `2` → `4` |
| 10 | LISTAR | PROJETO | GESTOR, DESENVOLVEDOR | Menu Principal → `2` → `5` |
| 11 | CRIAR | QUADRO | GESTOR | Menu Principal → `3` → `1` |
| 12 | LER | QUADRO | GESTOR, DESENVOLVEDOR | Menu Principal → `3` → `2` |
| 13 | ATUALIZAR | QUADRO | GESTOR | Menu Principal → `3` → `3` |
| 14 | EXCLUIR | QUADRO | GESTOR | Menu Principal → `3` → `4` |
| 15 | LISTAR | QUADRO | GESTOR, DESENVOLVEDOR | Menu Principal → `3` → `5` |
| 16 | CRIAR | CARTÃO DE ATIVIDADE | GESTOR | Menu Principal → `3` → `6` → `1` |
| 17 | LER | CARTÃO DE ATIVIDADE | GESTOR, DESENVOLVEDOR | Menu Principal → `3` → `6` → `2` |
| 18 | ATUALIZAR | CARTÃO DE ATIVIDADE | GESTOR | Menu Principal → `3` → `6` → `3` |
| 19 | EXCLUIR | CARTÃO DE ATIVIDADE | GESTOR | Menu Principal → `3` → `6` → `4` |
| 20 | LISTAR | CARTÃO DE ATIVIDADE | GESTOR, DESENVOLVEDOR | Menu Principal → `3` → `6` → `5` |
| 21 | MOVER | CARTÃO DE ATIVIDADE | GESTOR, DESENVOLVEDOR | Menu Principal → `3` → `6` → `6` |
| 22 | LER TEMPO DE CICLO | CARTÃO DE ATIVIDADE | GESTOR, DESENVOLVEDOR | Menu Principal → `3` → `6` → `7` |
| 23 | LER TEMPO DE CICLO MÉDIO | CARTÃO DE ATIVIDADE | GESTOR, DESENVOLVEDOR | Menu Principal → `3` → `6` → `8` |
| 24 | LER LEAD TIME | CARTÃO DE ATIVIDADE | GESTOR, DESENVOLVEDOR | Menu Principal → `3` → `6` → `9` |
| 25 | LER LEAD TIME MÉDIO | CARTÃO DE ATIVIDADE | GESTOR, DESENVOLVEDOR | Menu Principal → `3` → `6` → `10` |
| 26 | LER WIP | CARTÃO DE ATIVIDADE | GESTOR, DESENVOLVEDOR | Menu Principal → `3` → `6` → `11` |

---

## 3. Bateria de Testes Automatizados

O projeto conta com três suítes de testes automatizados:

Para compilar os alvos que acessam o banco, o ambiente precisa disponibilizar o cabeçalho `sqlite3.h` e a biblioteca SQLite para vinculação com `-lsqlite3`. O `Makefile` e o `Projeto_TP1.cbp` atualizados já incluem `BancoDados/banco_dados.cpp` e essa dependência nos alvos correspondentes.

| Execução | Banco utilizado | Dados após encerrar |
|---|---|---|
| `make test_unit` / `TestesUnitarios` | Não utiliza banco | Não se aplica |
| `make test_smoke` / `SmokeTest` | SQLite em memória (`:memory:`) | Descartados ao fechar a conexão |
| `make test_integrated` | `kanban.db` em um diretório temporário | Removidos com o diretório de teste |
| Programa executado normalmente | `kanban.db` no diretório de execução | Preservados para a próxima execução nesse diretório |

O banco em memória dos testes também executa SQL e utiliza o esquema definido por `BancoDados`. Seu conteúdo é temporário, conforme a [documentação oficial do SQLite](https://www.sqlite.org/inmemorydb.html).

### 3.1 Testes de Unidade (Domínios e Entidades)
Testa individualmente todas as 11 classes de domínio e as 4 entidades com casos válidos e inválidos (106 asserções):
```bash
make test_unit
# ou:
g++ -std=c++11 -Wall -Wextra -pedantic Dominios/dominios.cpp Entidades/entidades.cpp \
  Testes/testes_dominios.cpp Testes/testes_entidades.cpp Testes/testes_unitarios.cpp -o bin/testes_unitarios
./bin/testes_unitarios
```

### 3.2 Testes de Fumaça das Controladoras de Serviço
Testa as regras de negócio, permissões e restrições de integridade diretamente nas controladoras (75 asserções):
```bash
make test_smoke
# ou:
g++ -std=c++11 -Wall -Wextra -pedantic Dominios/dominios.cpp Entidades/entidades.cpp \
  Repositorios/repositorios.cpp BancoDados/banco_dados.cpp Servicos/controladoras_servico.cpp \
  Testes/smoke_test_controladoras.cpp -o bin/smoke_test -lsqlite3
./bin/smoke_test
```

Os quatro contêineres compartilham um `BancoDados(":memory:")`. Cada execução começa com um banco vazio, sem criar ou modificar o arquivo `kanban.db` do programa. As 75 asserções originais foram mantidas.

### 3.3 Teste Integrado Completo
Executa o sistema integrado com o roteiro de entradas automatizado:
```bash
make test_integrated
```
Esperado: 100% de sucesso sem nenhuma ocorrência de `[ERRO]`.

O alvo prepara um diretório temporário, inicia o programa com o roteiro e remove esse diretório ao terminar. Assim, os cadastros do teste não se misturam aos dados já persistidos pelo usuário. A execução direta de `./Projeto_TP1 < Testes/roteiro_teste_fumaca.txt` usaria o banco do diretório atual; para esta demonstração automatizada, utilize `make test_integrated`.

---

## 4. Verificação da Persistência entre Execuções

Este teste complementar verifica se uma conta continua disponível depois de encerrar e abrir novamente o executável. O banco deve ser um arquivo em disco; o `SmokeTest` em memória não verifica a conservação dos dados entre processos.

### 4.1 Preparar um diretório de teste separado

No terminal, a partir da raiz do projeto, execute:

```bash
make Projeto_TP1
diretorio_projeto="$PWD"
diretorio_persistencia="$(mktemp -d)" || exit 1
cd "$diretorio_persistencia" || exit 1
printf 'Banco de teste: %s/kanban.db\n' "$PWD"
"$diretorio_projeto/Projeto_TP1"
```

Mantenha o mesmo terminal e esse diretório durante as duas execuções. O arquivo `kanban.db` será criado ali; o banco existente na raiz do projeto permanecerá separado.

### 4.2 Criar a conta e encerrar o programa

1. Na tela inicial, escolha `2 - Criar conta`.
2. Informe os dados de exemplo abaixo, pressionando Enter ao final de cada campo:

   | Campo | Valor |
   |---|---|
   | Email | `persistencia@example.com` |
   | Nome | `Ana Banco` |
   | Senha | `abc12` |
   | Papel | `GESTOR` |

3. Confirme a mensagem `[OK] Conta criada.` e pressione Enter se solicitado.
4. Na tela inicial, escolha `0 - Sair` para encerrar o executável.

### 4.3 Reabrir e consultar os dados persistidos

Ainda no mesmo terminal e diretório, execute novamente:

```bash
"$diretorio_projeto/Projeto_TP1"
```

1. Escolha `1 - Entrar` e use `persistencia@example.com` com a senha `abc12`.
2. Confirme a mensagem `[OK] Autenticado como persistencia@example.com.`.
3. No menu principal, escolha `1 - Pessoas`, depois `2 - Ler`, e informe o mesmo email.
4. Confira o nome `Ana Banco` e o papel `GESTOR`.
5. Use `0 - Voltar`, `0 - Sair da sessao` e `0 - Sair` para encerrar.

**Resultado esperado:** a segunda execução autentica e consulta a conta cadastrada na primeira, sem recriá-la. O arquivo `kanban.db` permanece no diretório de teste para inspeção. Ao concluir, retorne à raiz do projeto com:

```bash
cd "$diretorio_projeto"
```

Para consultar esse mesmo banco posteriormente, volte ao diretório de teste antes de iniciar o executável. No Code::Blocks, o diretório de execução configurado para o alvo determina qual `kanban.db` será utilizado.
