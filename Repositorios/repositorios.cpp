#include "../Headers/repositorios.hpp"

// -----------------------------------------------------------------------------
// Pessoas
// -----------------------------------------------------------------------------

bool ContainerPessoas::inserir(const Pessoa& pessoa) {
    if (existe(pessoa.getEmail())) return false;
    pessoas.push_back(pessoa);
    return true;
}

bool ContainerPessoas::obter(const std::string& email, Pessoa& pessoa) const {
    for (std::size_t i = 0; i < pessoas.size(); ++i) {
        if (pessoas[i].getEmail() == email) {
            pessoa = pessoas[i];
            return true;
        }
    }
    return false;
}

bool ContainerPessoas::substituir(const std::string& email, const Pessoa& pessoa) {
    if (email != pessoa.getEmail()) return false; // preserva a chave primária
    for (std::size_t i = 0; i < pessoas.size(); ++i) {
        if (pessoas[i].getEmail() == email) {
            pessoas[i] = pessoa;
            return true;
        }
    }
    return false;
}

bool ContainerPessoas::remover(const std::string& email) {
    for (std::vector<Pessoa>::iterator it = pessoas.begin(); it != pessoas.end(); ++it) {
        if (it->getEmail() == email) {
            pessoas.erase(it);
            return true;
        }
    }
    return false;
}

bool ContainerPessoas::existe(const std::string& email) const {
    for (std::size_t i = 0; i < pessoas.size(); ++i)
        if (pessoas[i].getEmail() == email) return true;
    return false;
}

std::vector<std::string> ContainerPessoas::listarEmails() const {
    std::vector<std::string> resultado;
    for (std::size_t i = 0; i < pessoas.size(); ++i)
        resultado.push_back(pessoas[i].getEmail());
    return resultado;
}

// -----------------------------------------------------------------------------
// Projetos
// -----------------------------------------------------------------------------

bool ContainerProjetos::inserir(const Projeto& projeto, const std::string& emailGestor) {
    if (existe(projeto.getIdentificador())) return false;
    RegistroProjeto registro;
    registro.projeto = projeto;
    registro.emailGestor = emailGestor;
    projetos.push_back(registro);
    return true;
}

bool ContainerProjetos::obter(const std::string& id, Projeto& projeto,
                               std::string* emailGestor) const {
    for (std::size_t i = 0; i < projetos.size(); ++i) {
        if (projetos[i].projeto.getIdentificador() == id) {
            projeto = projetos[i].projeto;
            if (emailGestor != 0) *emailGestor = projetos[i].emailGestor;
            return true;
        }
    }
    return false;
}

bool ContainerProjetos::substituir(const std::string& id, const Projeto& projeto) {
    if (id != projeto.getIdentificador()) return false;
    for (std::size_t i = 0; i < projetos.size(); ++i) {
        if (projetos[i].projeto.getIdentificador() == id) {
            projetos[i].projeto = projeto;
            return true;
        }
    }
    return false;
}

bool ContainerProjetos::remover(const std::string& id) {
    for (std::vector<RegistroProjeto>::iterator it = projetos.begin(); it != projetos.end(); ++it) {
        if (it->projeto.getIdentificador() == id) {
            projetos.erase(it);
            return true;
        }
    }
    return false;
}

bool ContainerProjetos::existe(const std::string& id) const {
    for (std::size_t i = 0; i < projetos.size(); ++i)
        if (projetos[i].projeto.getIdentificador() == id) return true;
    return false;
}

bool ContainerProjetos::gestorDoProjeto(const std::string& id, std::string& emailGestor) const {
    Projeto ignorado;
    return obter(id, ignorado, &emailGestor);
}

bool ContainerProjetos::temProjetoGerenciadoPor(const std::string& emailGestor) const {
    for (std::size_t i = 0; i < projetos.size(); ++i)
        if (projetos[i].emailGestor == emailGestor) return true;
    return false;
}

std::vector<std::string> ContainerProjetos::listarIds() const {
    std::vector<std::string> resultado;
    for (std::size_t i = 0; i < projetos.size(); ++i)
        resultado.push_back(projetos[i].projeto.getIdentificador());
    return resultado;
}

// -----------------------------------------------------------------------------
// Quadros
// -----------------------------------------------------------------------------

bool ContainerQuadros::inserir(const Quadro& quadro, const std::string& idProjeto) {
    if (existe(quadro.getIdentificador())) return false;
    RegistroQuadro registro;
    registro.quadro = quadro;
    registro.idProjeto = idProjeto;
    quadros.push_back(registro);
    return true;
}

bool ContainerQuadros::obter(const std::string& id, Quadro& quadro,
                              std::string* idProjeto) const {
    for (std::size_t i = 0; i < quadros.size(); ++i) {
        if (quadros[i].quadro.getIdentificador() == id) {
            quadro = quadros[i].quadro;
            if (idProjeto != 0) *idProjeto = quadros[i].idProjeto;
            return true;
        }
    }
    return false;
}

bool ContainerQuadros::substituir(const std::string& id, const Quadro& quadro) {
    if (id != quadro.getIdentificador()) return false;
    for (std::size_t i = 0; i < quadros.size(); ++i) {
        if (quadros[i].quadro.getIdentificador() == id) {
            // Somente os dados do quadro são alterados; o vínculo com o projeto permanece.
            quadros[i].quadro = quadro;
            return true;
        }
    }
    return false;
}

bool ContainerQuadros::remover(const std::string& id) {
    for (std::vector<RegistroQuadro>::iterator it = quadros.begin(); it != quadros.end(); ++it) {
        if (it->quadro.getIdentificador() == id) {
            quadros.erase(it);
            return true;
        }
    }
    return false;
}

bool ContainerQuadros::existe(const std::string& id) const {
    for (std::size_t i = 0; i < quadros.size(); ++i)
        if (quadros[i].quadro.getIdentificador() == id) return true;
    return false;
}

bool ContainerQuadros::projetoDoQuadro(const std::string& id, std::string& idProjeto) const {
    Quadro ignorado;
    return obter(id, ignorado, &idProjeto);
}

bool ContainerQuadros::temQuadroDoProjeto(const std::string& idProjeto) const {
    for (std::size_t i = 0; i < quadros.size(); ++i)
        if (quadros[i].idProjeto == idProjeto) return true;
    return false;
}

std::vector<std::string> ContainerQuadros::listarIds() const {
    std::vector<std::string> resultado;
    for (std::size_t i = 0; i < quadros.size(); ++i)
        resultado.push_back(quadros[i].quadro.getIdentificador());
    return resultado;
}

// -----------------------------------------------------------------------------
// Cartões
// -----------------------------------------------------------------------------

bool ContainerCartoes::inserir(const CartaoDeAtividade& cartao,
                               const std::string& idQuadro,
                               const std::string& emailDesenvolvedor) {
    if (existe(cartao.getIdentificador())) return false;
    RegistroCartao registro;
    registro.cartao = cartao;
    registro.idQuadro = idQuadro;
    registro.emailDesenvolvedor = emailDesenvolvedor;
    cartoes.push_back(registro);
    return true;
}

bool ContainerCartoes::obter(const std::string& id, CartaoDeAtividade& cartao,
                              std::string* idQuadro,
                              std::string* emailDesenvolvedor) const {
    for (std::size_t i = 0; i < cartoes.size(); ++i) {
        if (cartoes[i].cartao.getIdentificador() == id) {
            cartao = cartoes[i].cartao;
            if (idQuadro != 0) *idQuadro = cartoes[i].idQuadro;
            if (emailDesenvolvedor != 0) *emailDesenvolvedor = cartoes[i].emailDesenvolvedor;
            return true;
        }
    }
    return false;
}

bool ContainerCartoes::substituir(const std::string& id, const CartaoDeAtividade& cartao) {
    if (id != cartao.getIdentificador()) return false;
    for (std::size_t i = 0; i < cartoes.size(); ++i) {
        if (cartoes[i].cartao.getIdentificador() == id) {
            // Os vínculos quadro/desenvolvedor não são alterados nesta operação.
            cartoes[i].cartao = cartao;
            return true;
        }
    }
    return false;
}

bool ContainerCartoes::remover(const std::string& id) {
    for (std::vector<RegistroCartao>::iterator it = cartoes.begin(); it != cartoes.end(); ++it) {
        if (it->cartao.getIdentificador() == id) {
            cartoes.erase(it);
            return true;
        }
    }
    return false;
}

bool ContainerCartoes::existe(const std::string& id) const {
    for (std::size_t i = 0; i < cartoes.size(); ++i)
        if (cartoes[i].cartao.getIdentificador() == id) return true;
    return false;
}

bool ContainerCartoes::temCartaoNoQuadro(const std::string& idQuadro) const {
    for (std::size_t i = 0; i < cartoes.size(); ++i)
        if (cartoes[i].idQuadro == idQuadro) return true;
    return false;
}

bool ContainerCartoes::temCartaoDoDesenvolvedor(const std::string& emailDesenvolvedor) const {
    for (std::size_t i = 0; i < cartoes.size(); ++i)
        if (cartoes[i].emailDesenvolvedor == emailDesenvolvedor) return true;
    return false;
}

std::vector<std::string> ContainerCartoes::listarIdsDoQuadro(const std::string& idQuadro) const {
    std::vector<std::string> resultado;
    for (std::size_t i = 0; i < cartoes.size(); ++i)
        if (cartoes[i].idQuadro == idQuadro)
            resultado.push_back(cartoes[i].cartao.getIdentificador());
    return resultado;
}

std::vector<CartaoDeAtividade> ContainerCartoes::listarCartoesDoQuadro(const std::string& idQuadro) const {
    std::vector<CartaoDeAtividade> resultado;
    for (std::size_t i = 0; i < cartoes.size(); ++i)
        if (cartoes[i].idQuadro == idQuadro)
            resultado.push_back(cartoes[i].cartao);
    return resultado;
}
