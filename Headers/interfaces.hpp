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

#endif // INTERFACES_HPP_INCLUDED