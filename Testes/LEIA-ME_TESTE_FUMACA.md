# Teste de fumaça (smoke test)

## 1. Sistema integrado (o que vai no vídeo)

Code::Blocks: alvo **Debug** (ou Release) → Build and run. O programa abre um menu.

Pela linha de comando, na pasta raiz:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic Dominios/dominios.cpp Entidades/entidades.cpp \
  Repositorios/repositorios.cpp Servicos/controladoras_servico.cpp \
  Apresentacao/apresentacao.cpp Main/main.cpp -o Projeto_TP1
./Projeto_TP1
```

Para repetir o teste sem digitar nada, use o roteiro de entradas:

```bash
./Projeto_TP1 < Testes/roteiro_teste_fumaca.txt
```

O roteiro percorre os 26 serviços em 4 sessões: gestor monta tudo, desenvolvedor move os cartões e lê as métricas, o gestor exclui e cada um exclui a própria conta.

Resultados esperados na saída: `WIP (cartoes em FAZENDO): 2`, depois `0`; `Tempo de ciclo: 150 minutos`; `Lead time: 210 minutos`; `Tempo de ciclo medio: 165.0 minutos`; `Lead time medio: 240.0 minutos`; nenhuma linha `[ERRO]`.

### Serviço do enunciado → opção de menu

| ID | Serviço | Como chegar |
|---|---|---|
| 1 | Criar pessoa | Tela inicial → 2 |
| 2–5 | Ler / atualizar / excluir / listar pessoa | Menu principal → 1 → opções 2, 3, 4, 5 |
| 6–10 | Criar / ler / atualizar / excluir / listar projeto | Menu principal → 2 → opções 1, 2, 3, 4, 5 |
| 11–15 | Criar / ler / atualizar / excluir / listar quadro | Menu principal → 3 → opções 1, 2, 3, 4, 5 |
| 16–20 | Criar / ler / atualizar / excluir / listar cartão | Menu principal → 4 → opções 1, 2, 3, 4, 5 |
| 21 | Mover cartão | Menu principal → 4 → 6 |
| 22 | Ler tempo de ciclo | Menu principal → 4 → 7 |
| 23 | Ler tempo de ciclo médio | Menu principal → 4 → 8 |
| 24 | Ler lead time | Menu principal → 4 → 9 |
| 25 | Ler lead time médio | Menu principal → 4 → 10 |
| 26 | Ler WIP | Menu principal → 4 → 11 |

Formatos úteis: identificador `PRJ001`; senha `abc12`; texto começa com maiúscula e termina com ponto (`Tarefa de teste.`); data `2-JAN-2026-09:00`; prioridade `ALTA`/`MEDIA`/`BAIXA`; tamanho `GRANDE`/`MEDIO`/`PEQUENO`.

## 2. Controladoras de serviço (automático, sem menu)

Code::Blocks: alvo **SmokeTest**. Ou:

```bash
g++ -std=c++11 -Wall -Wextra -pedantic Dominios/dominios.cpp Entidades/entidades.cpp \
  Repositorios/repositorios.cpp Servicos/controladoras_servico.cpp \
  Testes/smoke_test_controladoras.cpp -o teste_controladoras
./teste_controladoras
```

Cobre um caso de sucesso para cada um dos 26 serviços e também os casos em que o serviço deve recusar (permissão, WIP, consistência na exclusão). Esperado: `Resultado: 75 de 75 verificacoes passaram.`
