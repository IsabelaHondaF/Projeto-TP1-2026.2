# Guia de Testes e Roteiro de Demonstração (Vídeo)

Este documento orienta a execução dos testes e fornece um roteiro detalhado para a gravação do vídeo de demonstração do teste de fumaça (*smoke test*) do sistema integrado, em estrita conformidade com os requisitos da disciplina.

---

## 1. Roteiro Narrado para Gravação do Vídeo de Demonstração

Para atender ao **Requisito 4.26, 4.27 e Critério 6** da avaliação (100% de pontuação), o vídeo deve demonstrar a execução com sucesso do código integrado do sistema cobrindo um cenário de sucesso para cada uma das 26 funcionalidades.

### Como gravar o vídeo (Duração recomendada: 3 a 7 minutos)
1. Abra o terminal (ou o Code::Blocks) e mostre a pasta raiz do projeto.
2. Apresente os membros da equipe: **Arthur Vieira, Gabriel Sales, Isabela Honda Ferreira e João Roberto**.
3. Execute o programa integrado via terminal:
   ```bash
   ./Projeto_TP1 < Testes/roteiro_teste_fumaca.txt
   ```
   *(Ou execute `./Projeto_TP1` digitando manualmente os passos descritos abaixo).*
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
| 16 | CRIAR | CARTÃO DE ATIVIDADE | GESTOR | Menu Principal → `4` → `1` |
| 17 | LER | CARTÃO DE ATIVIDADE | GESTOR, DESENVOLVEDOR | Menu Principal → `4` → `2` |
| 18 | ATUALIZAR | CARTÃO DE ATIVIDADE | GESTOR | Menu Principal → `4` → `3` |
| 19 | EXCLUIR | CARTÃO DE ATIVIDADE | GESTOR | Menu Principal → `4` → `4` |
| 20 | LISTAR | CARTÃO DE ATIVIDADE | GESTOR, DESENVOLVEDOR | Menu Principal → `4` → `5` |
| 21 | MOVER | CARTÃO DE ATIVIDADE | GESTOR, DESENVOLVEDOR | Menu Principal → `4` → `6` |
| 22 | LER TEMPO DE CICLO | CARTÃO DE ATIVIDADE | GESTOR, DESENVOLVEDOR | Menu Principal → `4` → `7` |
| 23 | LER TEMPO DE CICLO MÉDIO | CARTÃO DE ATIVIDADE | GESTOR, DESENVOLVEDOR | Menu Principal → `4` → `8` |
| 24 | LER LEAD TIME | CARTÃO DE ATIVIDADE | GESTOR, DESENVOLVEDOR | Menu Principal → `4` → `9` |
| 25 | LER LEAD TIME MÉDIO | CARTÃO DE ATIVIDADE | GESTOR, DESENVOLVEDOR | Menu Principal → `4` → `10` |
| 26 | LER WIP | CARTÃO DE ATIVIDADE | GESTOR, DESENVOLVEDOR | Menu Principal → `4` → `11` |

---

## 3. Bateria de Testes Automatizados

O projeto conta com três suítes de testes automatizados:

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
  Repositorios/repositorios.cpp Servicos/controladoras_servico.cpp \
  Testes/smoke_test_controladoras.cpp -o bin/smoke_test
./bin/smoke_test
```

### 3.3 Teste Integrado Completo
Executa o sistema integrado com o roteiro de entradas automatizado:
```bash
make test_integrated
```
Esperado: 100% de sucesso sem nenhuma ocorrência de `[ERRO]`.
