# Controladoras — TP1 Kanban

## Estrutura

| Módulo | Arquivos | Papel |
|---|---|---|
| Domínios | `Headers/dominios.hpp`, `Dominios/dominios.cpp` | Validam formato; `set` lança exceção se inválido |
| Entidades | `Headers/entidades.hpp`, `Entidades/entidades.cpp` | Pessoa, Projeto, Quadro, Cartão (atributos são domínios) |
| Interfaces de serviço | `Headers/interfaces.hpp` | 4 classes abstratas com os 26 serviços |
| Serviço | `Headers/controladoras_servico.hpp`, `Servicos/controladoras_servico.cpp` | Controladoras `CntrServico...`: regras de negócio e permissões |
| Containers | `Headers/repositorios.hpp`, `Repositorios/repositorios.cpp` | Armazenamento em memória e vínculos entre entidades |
| Apresentação | `Headers/apresentacao.hpp`, `Apresentacao/apresentacao.cpp` | Controladoras `CntrApresentacao...`: menus (cin/cout) e validação da entrada |

A apresentação depende apenas das interfaces `IServico...`; `Main/main.cpp` liga as camadas.

## Como as camadas se comunicam

1. A apresentação lê e valida o dado digitado (usando as próprias classes de domínio) e chama um método da interface (por exemplo, `IServicoProjeto::criar`).
2. A controladora de serviço concreta (`CntrServicoProjeto`) verifica a conta, o papel e as regras de negócio.
3. O estado é lido ou alterado por meio de um container.
4. O método devolve `true` se a operação foi concluída e `false` se foi recusada.

As controladoras recebem os containers por referência, e todas compartilham o mesmo armazenamento.

## Regras implementadas (conforme tabela de serviços do enunciado)

- **Pessoa:** criar e autenticar não exigem sessão. Ler e listar: qualquer usuário cadastrado. **Atualizar e excluir: somente a própria conta.** A chave e-mail não muda. A exclusão é recusada se a pessoa gerencia projeto ou tem cartões. O papel não pode mudar se isso quebrar um vínculo existente.
- **Projeto:** só GESTOR cria; o criador é o gestor do projeto. Só esse gestor atualiza ou exclui. Exclusão recusada se houver quadros. Início deve ser menor ou igual ao término.
- **Quadro:** criar, atualizar e excluir exigem ser o gestor do projeto. Exclusão recusada se houver cartões. O limite de WIP não pode ficar abaixo da quantidade de cartões em FAZENDO.
- **Cartão:** **criar, atualizar e excluir: somente o gestor do projeto** (conforme o enunciado). O responsável deve ser um DESENVOLVEDOR. O cartão nasce em A FAZER com início e término vazios. Ler e listar: qualquer usuário cadastrado.
- **Mover:** gestor do projeto ou desenvolvedor responsável. Só A FAZER → FAZENDO → FEITO. Entrar em FAZENDO respeita o limite de WIP. O instante não pode ser anterior à entrada/início.
- **Métricas:** ciclo = término − início; lead time = término − entrada; WIP = cartões em FAZENDO. As médias consideram cartões FEITO; sem nenhum, retornam `false`.

## Decisões que o enunciado não especifica

- Atualizar/excluir pessoa restrito à própria conta (evita que alguém altere a conta de outro).
- O desenvolvedor responsável pelo cartão não pode atualizá-lo nem excluí-lo (a tabela do enunciado reserva essas operações ao GESTOR), mas pode movê-lo.
- As interfaces recebem o e-mail do solicitante, sem token de sessão. A apresentação só repassa o e-mail de quem foi autenticado.
- Armazenamento somente em memória: os dados somem ao encerrar o programa.

## Compilar e testar

Veja `Testes/LEIA-ME_TESTE_FUMACA.md`. No Code::Blocks há três alvos: `Debug` e `Release` (sistema) e `SmokeTest` (teste automático das controladoras de serviço).
