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
     * @param[in] pessoa Endereço eletrônico da conta existente e novos dados editáveis.
     * @return true se os dados forem atualizados; false se a conta não existir
     * ou a atualização não puder ser realizada.
     */
    virtual bool atualizar(
        const Email& usuario,
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
     * @param[in] projeto Código do registro existente e novos valores dos dados editáveis.
     * @return true se os dados forem atualizados; false se o registro não existir
     * ou a atualização não puder ser realizada.
     */
    virtual bool atualizar(
        const Email& usuario,
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
 * @brief Define operações para cadastrar e manter quadros Kanban vinculados a um projeto.
 *
 * Cada registro reúne código, nome e limite de work in progress (WIP) da
 * coluna FAZENDO. Um quadro pertence a exatamente um projeto. A criação, a
 * atualização e a exclusão exigem papel GESTOR; a leitura e a listagem
 * admitem também DESENVOLVEDOR. Todas as operações exigem autenticação.
 * As implementações devem preservar a chave primária nas atualizações e a
 * consistência dos vínculos nas exclusões.
 * @note Nos métodos com saída por referência, o resultado deve ser utilizado
 * somente quando o retorno for true.
 */
class IServicoQuadro {
public:

    /**
     * @brief Permite destruir a implementação por meio de um ponteiro para esta interface.
     */
    virtual ~IServicoQuadro() = default;

    /**
     * @brief Cadastra um quadro e o vincula ao projeto informado.
     *
     * O código fornecido em quadro identifica o novo registro e não pode
     * duplicar um existente.
     * @pre O solicitante deve estar autenticado com papel GESTOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[in] projeto Código do projeto ao qual o quadro pertencerá.
     * @param[in] quadro Código, nome e limite de WIP a serem cadastrados.
     * @return true se o cadastro e o vínculo com o projeto forem concluídos;
     * false se a criação não puder ser realizada.
     */
    virtual bool criar(
        const Email& usuario,
        const Identificador& projeto,
        const Quadro& quadro
    ) = 0;

    /**
     * @brief Obtém os dados do quadro selecionado pelo código.
     *
     * @pre O solicitante deve estar autenticado como GESTOR ou DESENVOLVEDOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[in] identificador Código que localiza o registro a ser consultado.
     * @param[out] quadro Recebe os dados do registro consultado em caso de sucesso.
     * @return true se os dados forem obtidos; false se o registro não existir
     * ou a consulta não puder ser realizada.
     */
    virtual bool ler(
        const Email& usuario,
        const Identificador& identificador,
        Quadro& quadro
    ) = 0;

    /**
     * @brief Substitui nome e limite de WIP de um quadro cadastrado.
     *
     * O identificador presente em quadro seleciona o registro existente e
     * deve ser preservado, pois a chave primária não pode ser editada.
     * @pre O solicitante deve estar autenticado com papel GESTOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[in] quadro Código do registro existente e novos valores dos dados editáveis.
     * @return true se os dados forem atualizados; false se o registro não existir
     * ou a atualização não puder ser realizada.
     */
    virtual bool atualizar(
        const Email& usuario,
        const Quadro& quadro
    ) = 0;

    /**
     * @brief Remove um quadro cadastrado, preservando a consistência dos vínculos do sistema.
     *
     * A implementação deve impedir que a remoção deixe relacionamentos inconsistentes,
     * inclusive em relação aos cartões de atividade vinculados ao quadro.
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
     * @brief Obtém os códigos que identificam os quadros cadastrados.
     *
     * @pre O solicitante deve estar autenticado como GESTOR ou DESENVOLVEDOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[out] identificadores Recebe as chaves primárias dos quadros em caso de sucesso.
     * @return true se a consulta for concluída, inclusive quando não houver quadros
     * a listar; false se a consulta não puder ser realizada.
     */
    virtual bool listar(
        const Email& usuario,
        std::vector<Identificador>& identificadores
    ) = 0;
};


/**
 * @brief Define operações para cadastrar, mover e medir cartões de atividade de um quadro.
 *
 * Cada registro reúne código, nome, descrição, prioridade, estado, tamanho e
 * os instantes de entrada, início e término. Um cartão pertence a exatamente
 * um quadro. A criação, a atualização e a exclusão exigem papel GESTOR; as
 * demais operações admitem também DESENVOLVEDOR. Todas as operações exigem
 * autenticação. As implementações devem preservar a chave primária nas
 * atualizações, a consistência dos vínculos nas exclusões, e respeitar o
 * limite de WIP do quadro ao mover um cartão para a coluna FAZENDO.
 * @note Nos métodos com saída por referência, o resultado deve ser utilizado
 * somente quando o retorno for true.
 */
class IServicoCartaoAtividade {
public:

    /**
     * @brief Permite destruir a implementação por meio de um ponteiro para esta interface.
     */
    virtual ~IServicoCartaoAtividade() = default;

    /**
     * @brief Cadastra um cartão de atividade e o vincula ao quadro informado.
     *
     * O cartão é cadastrado no estado A FAZER, com o instante de entrada
     * registrado no momento da criação. O código fornecido em cartao
     * identifica o novo registro e não pode duplicar um existente.
     * @pre O solicitante deve estar autenticado com papel GESTOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[in] quadro Código do quadro ao qual o cartão pertencerá.
     * @param[in] cartao Código, nome, descrição, prioridade e tamanho a serem cadastrados.
     * @return true se o cadastro e o vínculo com o quadro forem concluídos;
     * false se a criação não puder ser realizada.
     */
    virtual bool criar(
        const Email& usuario,
        const Identificador& quadro,
        const CartaoDeAtividade& cartao
    ) = 0;

    /**
     * @brief Obtém os dados do cartão de atividade selecionado pelo código.
     *
     * @pre O solicitante deve estar autenticado como GESTOR ou DESENVOLVEDOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[in] identificador Código que localiza o registro a ser consultado.
     * @param[out] cartao Recebe os dados do registro consultado em caso de sucesso.
     * @return true se os dados forem obtidos; false se o registro não existir
     * ou a consulta não puder ser realizada.
     */
    virtual bool ler(
        const Email& usuario,
        const Identificador& identificador,
        CartaoDeAtividade& cartao
    ) = 0;

    /**
     * @brief Substitui nome, descrição, prioridade e tamanho de um cartão cadastrado.
     *
     * O identificador presente em cartao seleciona o registro existente e
     * deve ser preservado, pois a chave primária não pode ser editada. O
     * estado e os instantes de entrada, início e término não são alterados
     * por este método; a mudança de estado é feita pelo método mover.
     * @pre O solicitante deve estar autenticado com papel GESTOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[in] cartao Código do registro existente e novos valores dos dados editáveis.
     * @return true se os dados forem atualizados; false se o registro não existir
     * ou a atualização não puder ser realizada.
     */
    virtual bool atualizar(
        const Email& usuario,
        const CartaoDeAtividade& cartao
    ) = 0;

    /**
     * @brief Remove um cartão de atividade cadastrado, preservando a consistência do sistema.
     *
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
     * @brief Obtém os códigos que identificam os cartões de atividade cadastrados.
     *
     * @pre O solicitante deve estar autenticado como GESTOR ou DESENVOLVEDOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[out] identificadores Recebe as chaves primárias dos cartões em caso de sucesso.
     * @return true se a consulta for concluída, inclusive quando não houver cartões
     * a listar; false se a consulta não puder ser realizada.
     */
    virtual bool listar(
        const Email& usuario,
        std::vector<Identificador>& identificadores
    ) = 0;

    /**
     * @brief Move um cartão de atividade para uma coluna adjacente do quadro.
     *
     * As movimentações permitidas são A FAZER para FAZENDO, e FAZENDO para
     * FEITO. Ao entrar em FAZENDO, o instante de início é registrado; ao
     * entrar em FEITO, o instante de término é registrado. A implementação
     * deve recusar a movimentação para FAZENDO se o limite de WIP do quadro
     * já tiver sido atingido.
     * @pre O solicitante deve estar autenticado como GESTOR ou DESENVOLVEDOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[in] identificador Código do cartão a ser movido.
     * @param[in] estadoDestino Estado para o qual o cartão deve ser movido.
     * @return true se a movimentação for realizada; false se o cartão não existir,
     * a movimentação não for permitida, ou o limite de WIP impedir a movimentação.
     */
    virtual bool mover(
        const Email& usuario,
        const Identificador& identificador,
        const Estado& estadoDestino
    ) = 0;

    /**
     * @brief Obtém o tempo de ciclo de um cartão de atividade já concluído.
     *
     * O tempo de ciclo é medido do instante em que o cartão entra em FAZENDO
     * até o instante em que entra em FEITO.
     * @pre O solicitante deve estar autenticado como GESTOR ou DESENVOLVEDOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[in] identificador Código do cartão a ser consultado.
     * @param[out] minutos Recebe o tempo de ciclo em minutos em caso de sucesso.
     * @return true se o tempo de ciclo for obtido; false se o cartão não existir
     * ou ainda não tiver sido concluído.
     */
    virtual bool lerTempoDeCiclo(
        const Email& usuario,
        const Identificador& identificador,
        int& minutos
    ) = 0;

    /**
     * @brief Obtém a média dos tempos de ciclo das atividades concluídas de um quadro.
     *
     * @pre O solicitante deve estar autenticado como GESTOR ou DESENVOLVEDOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[in] quadro Código do quadro a ser consultado.
     * @param[out] mediaEmMinutos Recebe a média dos tempos de ciclo em minutos em caso de sucesso.
     * @return true se a média for obtida, inclusive quando for zero por não haver
     * atividades concluídas; false se o quadro não existir.
     */
    virtual bool lerTempoDeCicloMedio(
        const Email& usuario,
        const Identificador& quadro,
        double& mediaEmMinutos
    ) = 0;

    /**
     * @brief Obtém o lead time de um cartão de atividade já concluído.
     *
     * O lead time é medido do instante em que o cartão entra em A FAZER até
     * o instante em que entra em FEITO.
     * @pre O solicitante deve estar autenticado como GESTOR ou DESENVOLVEDOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[in] identificador Código do cartão a ser consultado.
     * @param[out] minutos Recebe o lead time em minutos em caso de sucesso.
     * @return true se o lead time for obtido; false se o cartão não existir
     * ou ainda não tiver sido concluído.
     */
    virtual bool lerLeadTime(
        const Email& usuario,
        const Identificador& identificador,
        int& minutos
    ) = 0;

    /**
     * @brief Obtém a média dos lead times das atividades concluídas de um quadro.
     *
     * @pre O solicitante deve estar autenticado como GESTOR ou DESENVOLVEDOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[in] quadro Código do quadro a ser consultado.
     * @param[out] mediaEmMinutos Recebe a média dos lead times em minutos em caso de sucesso.
     * @return true se a média for obtida, inclusive quando for zero por não haver
     * atividades concluídas; false se o quadro não existir.
     */
    virtual bool lerLeadTimeMedio(
        const Email& usuario,
        const Identificador& quadro,
        double& mediaEmMinutos
    ) = 0;

    /**
     * @brief Obtém o work in progress (WIP) atual de um quadro.
     *
     * O WIP é a quantidade de cartões de atividade atualmente no estado FAZENDO.
     * @pre O solicitante deve estar autenticado como GESTOR ou DESENVOLVEDOR.
     * @param[in] usuario Endereço eletrônico do solicitante autenticado.
     * @param[in] quadro Código do quadro a ser consultado.
     * @param[out] wip Recebe a quantidade de cartões em FAZENDO em caso de sucesso.
     * @return true se o WIP for obtido; false se o quadro não existir.
     */
    virtual bool lerWIP(
        const Email& usuario,
        const Identificador& quadro,
        int& wip
    ) = 0;
};

#endif // INTERFACES_HPP_INCLUDED