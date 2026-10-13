#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include "entidades.hpp"
#include <vector>

// Padrao de nomenclatura: IServico + nome da entidade

/**
 * @brief Define operações para cadastrar contas, verificar credenciais e consultar usuários.
 *
 * O endereço eletrônico identifica cada conta. A criação e a autenticação
 * precedem o acesso aos demais serviços, disponíveis a usuários autenticados
 * com papel GESTOR ou DESENVOLVEDOR. As implementações devem preservar a
 * chave primária nas atualizações e a consistência dos vínculos nas exclusões.
 * @note Nos métodos com saída por referência, o resultado deve ser utilizado
 * somente quando o retorno for true.
 */
class IServicoPessoa {
public:

    /**
     * @brief Permite destruir a implementação por meio de um ponteiro para esta interface.
     */
    virtual ~IServicoPessoa() = default;

    /**
     * @brief Cadastra uma conta para permitir o acesso do usuário ao sistema.
     *
     * Esta operação não exige autenticação prévia. O endereço eletrônico
     * fornecido identifica a nova conta e não pode duplicar uma conta existente.
     * @param[in] pessoa Dados de cadastro: endereço eletrônico, nome, senha e papel.
     * @return true se a conta for cadastrada; false se não for possível cadastrá-la.
     */
    virtual bool criar(
        const Pessoa& pessoa
    ) = 0;

    /**
     * @brief Verifica se as credenciais correspondem a uma conta cadastrada.
     *
     * @param[in] email Endereço eletrônico que identifica a conta a ser verificada.
     * @param[in] senha Credencial apresentada para comprovar o acesso à conta.
     * @return true se a conta existir e a senha corresponder à cadastrada;
     * false se as credenciais não forem reconhecidas.
     */
    virtual bool autenticar(
        const Email& email,
        const Senha& senha
    ) = 0;

    /**
     * @brief Obtém os dados da conta identificada pelo endereço eletrônico de destino.
     *
     * @pre O solicitante deve estar autenticado como GESTOR ou DESENVOLVEDOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[in] alvo Endereço eletrônico da conta cujos dados serão consultados.
     * @param[out] pessoa Recebe os dados da conta consultada em caso de sucesso.
     * @return true se os dados forem obtidos; false se a conta não existir
     * ou a consulta não puder ser realizada.
     */
    virtual bool ler(
        const Email& usuario,
        const Email& alvo,
        Pessoa& pessoa
    ) = 0;

    /**
     * @brief Substitui os dados editáveis de uma conta já cadastrada.
     *
     * O endereço eletrônico presente em pessoa seleciona o registro existente
     * e deve ser preservado. Nome, senha e papel compõem os dados atualizáveis.
     * @pre O solicitante deve estar autenticado como GESTOR ou DESENVOLVEDOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[in] alvo Endereço eletrônico da conta a ser alterada.
     * @param[in] pessoa Endereço eletrônico da conta existente e novos dados editáveis.
     * @return true se os dados forem atualizados; false se a conta não existir
     * ou a atualização não puder ser realizada.
     */
    virtual bool atualizar(
        const Email& usuario,
        const Email& alvo,
        const Pessoa& pessoa
    ) = 0;

    /**
     * @brief Remove uma conta cadastrada, preservando a consistência dos vínculos do sistema.
     *
     * A implementação deve impedir que a remoção deixe relacionamentos inconsistentes.
     * @pre O solicitante deve estar autenticado como GESTOR ou DESENVOLVEDOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[in] alvo Endereço eletrônico da conta a ser removida.
     * @return true se a conta for removida; false se ela não existir
     * ou a exclusão não puder ser realizada com consistência.
     */
    virtual bool excluir(
        const Email& usuario,
        const Email& alvo
    ) = 0;

    /**
     * @brief Obtém os endereços eletrônicos que identificam as contas cadastradas.
     *
     * @pre O solicitante deve estar autenticado como GESTOR ou DESENVOLVEDOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[out] emails Recebe as chaves primárias das contas em caso de sucesso.
     * @return true se a consulta for concluída, inclusive quando não houver contas
     * a listar; false se a consulta não puder ser realizada.
     */
    virtual bool listar(
        const Email& usuario,
        std::vector<Email>& emails
    ) = 0;
};


/**
 * @brief Define operações para cadastrar e manter conjuntos de atividades e seus períodos.
 *
 * Cada registro reúne código, nome, descrição, início e término. A criação,
 * a atualização e a exclusão exigem papel GESTOR; a leitura e a listagem
 * admitem também DESENVOLVEDOR. Todas as operações exigem autenticação.
 * Quem cria o projeto torna-se seu gestor. As implementações devem preservar
 * a chave primária nas atualizações e a consistência dos vínculos nas exclusões.
 * @note Nos métodos com saída por referência, o resultado deve ser utilizado
 * somente quando o retorno for true.
 */
class IServicoProjeto {
public:

    /**
     * @brief Permite destruir a implementação por meio de um ponteiro para esta interface.
     */
    virtual ~IServicoProjeto() = default;

    /**
     * @brief Cadastra um conjunto de atividades e vincula seu criador como gestor.
     *
     * O código fornecido identifica o novo registro e não pode duplicar um existente.
     * @pre O solicitante deve estar autenticado com papel GESTOR.
     * @param[in] gestor Endereço eletrônico do usuário que cria e passa a gerir o projeto.
     * @param[in] projeto Código, nome, descrição, início e término a serem cadastrados.
     * @return true se o cadastro e o vínculo com o gestor forem concluídos;
     * false se a criação não puder ser realizada.
     */
    virtual bool criar(
        const Email& gestor,
        const Projeto& projeto
    ) = 0;

    /**
     * @brief Obtém os dados do conjunto de atividades selecionado pelo código.
     *
     * @pre O solicitante deve estar autenticado como GESTOR ou DESENVOLVEDOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[in] identificador Código que localiza o registro a ser consultado.
     * @param[out] projeto Recebe os dados do registro consultado em caso de sucesso.
     * @return true se os dados forem obtidos; false se o registro não existir
     * ou a consulta não puder ser realizada.
     */
    virtual bool ler(
        const Email& usuario,
        const Identificador& identificador,
        Projeto& projeto
    ) = 0;

    /**
     * @brief Substitui nome, descrição, início e término de um projeto cadastrado.
     *
     * O identificador presente em projeto seleciona o registro existente e deve
     * ser preservado, pois a chave primária não pode ser editada.
     * @pre O solicitante deve estar autenticado com papel GESTOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[in] identifcador Código que identifica o projetoa ser alterado
     * @param[in] projeto Código do registro existente e novos valores dos dados editáveis.
     * @return true se os dados forem atualizados; false se o registro não existir
     * ou a atualização não puder ser realizada.
     */
    virtual bool atualizar(
        const Email& usuario,
        const Identificador& identificador,
        const Projeto& projeto
    ) = 0;

    /**
     * @brief Remove um projeto cadastrado, preservando a consistência dos vínculos do sistema.
     *
     * A implementação deve impedir que a remoção deixe relacionamentos inconsistentes.
     * @pre O solicitante deve estar autenticado com papel GESTOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[in] identificador Código do registro a ser removido.
     * @return true se o registro for removido; false se ele não existir
     * ou a exclusão não puder ser realizada com consistência.
     */
    virtual bool excluir(
        const Email& usuario,
        const Identificador& identificador
    ) = 0;

    /**
     * @brief Obtém os códigos que identificam os projetos cadastrados.
     *
     * @pre O solicitante deve estar autenticado como GESTOR ou DESENVOLVEDOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[out] identificadores Recebe as chaves primárias dos projetos em caso de sucesso.
     * @return true se a consulta for concluída, inclusive quando não houver projetos
     * a listar; false se a consulta não puder ser realizada.
     */
    virtual bool listar(
        const Email& usuario,
        std::vector<Identificador>& identificadores
    ) = 0;
};


/**
 * @brief Interface responsável pelos serviços relacionados à entidade Quadro.
 *
 * Define as operações disponibilizadas pela camada de serviço para
 * criação, leitura, atualização, exclusão e listagem de quadros.
 *
 * O vínculo entre um quadro e um projeto deve ser mantido pela camada
 * de serviço.
 */
class IServicoQuadro {
public:

    /**
     * @brief Destrutor virtual da interface.
     */
    virtual ~IServicoQuadro() = default;

    /**
     * @brief Cria um novo quadro associado a um projeto.
     *
     * A operação deve associar o quadro informado ao projeto identificado
     * pelo parâmetro projeto.
     *
     * @param[in] usuario Email do usuário que solicita a operação.
     * @param[in] projeto Identificador do projeto ao qual o quadro será associado.
     * @param[in] quadro Entidade Quadro que será cadastrada.
     *
     * @return true caso o quadro seja criado com sucesso.
     * @return false caso a operação não possa ser realizada.
     */
    virtual bool criar(
        const Email& usuario,
        const Identificador& projeto,
        const Quadro& quadro
    ) = 0;

    /**
     * @brief Recupera os dados de um quadro cadastrado.
     *
     * O quadro é localizado por meio de seu identificador.
     *
     * @param[in] usuario Email do usuário que solicita a operação.
     * @param[in] identificador Identificador do quadro que será pesquisado.
     * @param[out] quadro Referência utilizada para retornar os dados do quadro.
     *
     * @return true caso o quadro seja encontrado.
     * @return false caso a operação não possa ser realizada.
     */
    virtual bool ler(
        const Email& usuario,
        const Identificador& identificador,
        Quadro& quadro
    ) = 0;

    /**
     * @brief Atualiza os dados de um quadro cadastrado.
     *
     * O identificador do quadro deve ser utilizado para localizar a entidade
     * armazenada e não pode ser alterado durante a atualização.
     *
     * @param[in] usuario Email do usuário que solicita a operação.
     * @param[in] identificador Código identificador do quadro
     * @param[in] quadro Entidade contendo os novos dados do quadro.
     *
     * @return true caso a atualização seja realizada com sucesso.
     * @return false caso a operação não possa ser realizada.
     */
    virtual bool atualizar(
        const Email& usuario,
        const Identificador& identificador,
        const Quadro& quadro
    ) = 0;

    /**
     * @brief Exclui um quadro cadastrado.
     *
     * A exclusão deve preservar a consistência dos relacionamentos
     * existentes no sistema.
     *
     * @param[in] usuario Email do usuário que solicita a operação.
     * @param[in] identificador Identificador do quadro que será excluído.
     *
     * @return true caso o quadro seja excluído com sucesso.
     * @return false caso a operação não possa ser realizada.
     */
    virtual bool excluir(
        const Email& usuario,
        const Identificador& identificador
    ) = 0;

    /**
     * @brief Lista os identificadores dos quadros cadastrados.
     *
     * @param[in] usuario Email do usuário que solicita a operação.
     * @param[out] identificadores Vetor utilizado para retornar os identificadores
     * dos quadros cadastrados.
     *
     * @return true caso a listagem seja realizada com sucesso.
     * @return false caso a operação não possa ser realizada.
     */
    virtual bool listar(
        const Email& usuario,
        std::vector<Identificador>& identificadores
    ) = 0;
};


/**
 * @brief Interface responsável pelos serviços relacionados a cartões de atividade.
 *
 * Define as operações disponibilizadas pela camada de serviço para criação,
 * leitura, atualização, exclusão, listagem e movimentação de cartões,
 * além do cálculo das métricas de tempo do quadro Kanban.
 *
 * A implementação deve controlar as movimentações entre A FAZER, FAZENDO
 * e FEITO e respeitar o limite de WIP do quadro.
 */
class IServicoCartaoDeAtividade {
public:

    /**
     * @brief Destrutor virtual da interface.
     */
    virtual ~IServicoCartaoDeAtividade() = default;

    /**
     * @brief Cria um novo cartão de atividade.
     *
     * O cartão é associado a um quadro e a um desenvolvedor responsável.
     *
     * @param[in] usuario Email do usuário que solicita a operação.
     * @param[in] quadro Identificador do quadro ao qual o cartão pertence.
     * @param[in] desenvolvedor Email do desenvolvedor responsável pelo cartão.
     * @param[in] cartao Entidade CartaoDeAtividade que será cadastrada.
     *
     * @return true caso o cartão seja criado com sucesso.
     * @return false caso a operação não possa ser realizada.
     */
    virtual bool criar(
        const Email& usuario,
        const Identificador& quadro,
        const Email& desenvolvedor,
        const CartaoDeAtividade& cartao
    ) = 0;

    /**
     * @brief Recupera os dados de um cartão de atividade.
     *
     * O cartão é localizado por meio do seu identificador.
     *
     * @param[in] usuario Email do usuário que solicita a operação.
     * @param[in] identificador Identificador do cartão que será pesquisado.
     * @param[out] cartao Referência utilizada para retornar os dados do cartão.
     *
     * @return true caso o cartão seja encontrado.
     * @return false caso a operação não possa ser realizada.
     */
    virtual bool ler(
        const Email& usuario,
        const Identificador& identificador,
        CartaoDeAtividade& cartao
    ) = 0;

    /**
     * @brief Atualiza os dados editáveis de um cartão de atividade.
     *
     * O identificador contido no cartão é utilizado para localizar
     * a entidade armazenada e não deve ser alterado.
     *
     * A alteração do estado e dos instantes relacionados às movimentações
     * deve ser realizada pelo serviço mover.
     *
     * @param[in] usuario Email do usuário que solicita a operação.
     * @param[in] cartao Entidade contendo os novos dados do cartão.
     *
     * @return true caso a atualização seja realizada com sucesso.
     * @return false caso a operação não possa ser realizada.
     */
    virtual bool atualizar(
        const Email& usuario,
        const Identificador& identificador,
        const CartaoDeAtividade& cartao
    ) = 0;

    /**
     * @brief Exclui um cartão de atividade cadastrado.
     *
     * @param[in] usuario Email do usuário que solicita a operação.
     * @param[in] identificador Identificador do cartão que será excluído.
     *
     * @return true caso o cartão seja excluído com sucesso.
     * @return false caso a operação não possa ser realizada.
     */
    virtual bool excluir(
        const Email& usuario,
        const Identificador& identificador
    ) = 0;

    /**
     * @brief Lista os identificadores dos cartões pertencentes a um quadro.
     *
     * @param[in] usuario Email do usuário que solicita a operação.
     * @param[in] quadro Identificador do quadro cujos cartões serão listados.
     * @param[out] identificadores Vetor utilizado para retornar os identificadores
     * dos cartões.
     *
     * @return true caso a listagem seja realizada com sucesso.
     * @return false caso a operação não possa ser realizada.
     */
    virtual bool listar(
        const Email& usuario,
        const Identificador& quadro,
        std::vector<Identificador>& identificadores
    ) = 0;

    /**
     * @brief Move um cartão para a próxima coluna permitida do quadro.
     *
     * As únicas movimentações permitidas são:
     *
     * A FAZER -> FAZENDO
     * FAZENDO -> FEITO
     *
     * Ao entrar em FAZENDO, a implementação deve registrar o instante
     * de início e respeitar o limite de WIP do quadro.
     *
     * Ao entrar em FEITO, deve registrar o instante de término.
     *
     * @param[in] usuario Email do usuário que solicita a movimentação.
     * @param[in] identificador Identificador do cartão que será movido.
     * @param[in] instante Momento em que ocorre a movimentação.
     *
     * @return true caso a movimentação seja realizada.
     * @return false caso a movimentação não seja permitida.
     */
    virtual bool mover(
        const Email& usuario,
        const Identificador& identificador,
        const Timestamp& instante
    ) = 0;

    /**
     * @brief Obtém o tempo de ciclo de um cartão de atividade.
     *
     * O tempo de ciclo corresponde ao intervalo entre a entrada do cartão
     * em FAZENDO e sua chegada em FEITO.
     *
     * @param[in] usuario Email do usuário que solicita a operação.
     * @param[in] identificador Identificador do cartão.
     * @param[out] minutos Referência utilizada para retornar o tempo de ciclo,
     * em minutos.
     *
     * @return true caso o tempo de ciclo possa ser calculado.
     * @return false caso a operação não possa ser realizada.
     */
    virtual bool lerTempoCiclo(
        const Email& usuario,
        const Identificador& identificador,
        long long& minutos
    ) = 0;

    /**
     * @brief Obtém o tempo de ciclo médio dos cartões de um quadro.
     *
     * O valor corresponde à média dos tempos de ciclo das atividades
     * consideradas no quadro.
     *
     * @param[in] usuario Email do usuário que solicita a operação.
     * @param[in] quadro Identificador do quadro.
     * @param[out] minutos Referência utilizada para retornar o tempo médio,
     * em minutos.
     *
     * @return true caso a média possa ser calculada.
     * @return false caso a operação não possa ser realizada.
     */
    virtual bool lerTempoCicloMedio(
        const Email& usuario,
        const Identificador& quadro,
        double& minutos
    ) = 0;

    /**
     * @brief Obtém o lead time de um cartão de atividade.
     *
     * O lead time corresponde ao intervalo entre a entrada do cartão
     * em A FAZER e sua chegada em FEITO.
     *
     * @param[in] usuario Email do usuário que solicita a operação.
     * @param[in] identificador Identificador do cartão.
     * @param[out] minutos Referência utilizada para retornar o lead time,
     * em minutos.
     *
     * @return true caso o lead time possa ser calculado.
     * @return false caso a operação não possa ser realizada.
     */
    virtual bool lerLeadTime(
        const Email& usuario,
        const Identificador& identificador,
        long long& minutos
    ) = 0;

    /**
     * @brief Obtém o lead time médio dos cartões de um quadro.
     *
     * @param[in] usuario Email do usuário que solicita a operação.
     * @param[in] quadro Identificador do quadro.
     * @param[out] minutos Referência utilizada para retornar o lead time médio,
     * em minutos.
     *
     * @return true caso a média possa ser calculada.
     * @return false caso a operação não possa ser realizada.
     */
    virtual bool lerLeadTimeMedio(
        const Email& usuario,
        const Identificador& quadro,
        double& minutos
    ) = 0;

    /**
     * @brief Obtém o WIP atual de um quadro.
     *
     * O WIP corresponde à quantidade de cartões atualmente na coluna
     * FAZENDO.
     *
     * @param[in] usuario Email do usuário que solicita a operação.
     * @param[in] quadro Identificador do quadro.
     * @param[out] quantidade Referência utilizada para retornar o número
     * de cartões em andamento.
     *
     * @return true caso o WIP seja obtido com sucesso.
     * @return false caso a operação não possa ser realizada.
     */
    virtual bool lerWIP(
        const Email& usuario,
        const Identificador& quadro,
        int& quantidade
    ) = 0;
};

#endif // INTERFACES_HPP_INCLUDED