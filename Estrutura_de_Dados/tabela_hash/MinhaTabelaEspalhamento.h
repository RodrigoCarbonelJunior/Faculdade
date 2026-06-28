#ifndef MINHA_TABELA_ESPALHAMENTO_H
#define MINHA_TABELA_ESPALHAMENTO_H

#include "MinhaListaEncadeada.h"
// MinhaListaEncadeada
#include "TabelaEspalhamentoAbstrata.h"
// TabelaEspalhamentoAbstrata
#include "excecoes.h"
// ExcecaoDadoInexistente

template<typename T, std::size_t capac>
class MinhaTabelaEspalhamento final:
    public TabelaEspalhamentoAbstrata<T, capac>
{
public:
    virtual std::size_t capacidade() const
    {
        return capac;
    }

    virtual std::size_t quantidade() const
    {
        std::size_t total = 0;

        for (std::size_t i = 0; i < capac; i++)
        {
            total += this->tabela[i].tamanho();
        }

        return total;
    }

    virtual bool contem(T dado) const
    {
        std::size_t pos = funcaoEspalhamento(dado);
        return this->tabela[pos].contem(dado);
    }

    virtual void inserir(T dado)
    {
        if (contem(dado))
        {
            return;
        }

        std::size_t pos = funcaoEspalhamento(dado);
        this->tabela[pos].inserirNoFim(dado);
    }

    virtual void remover(T dado)
    {
        std::size_t pos = funcaoEspalhamento(dado);

        if (!this->tabela[pos].contem(dado))
        {
            throw ExcecaoDadoInexistente();
        }

        this->tabela[pos].remover(dado);
    }

protected:
    virtual std::size_t funcaoEspalhamento(T dado) const
    {
        return codigoEspalhamento(dado) % capac;
    }

private:
    template<typename U>
    std::size_t codigoEspalhamento(U integral) const
    {
        static_assert(std::is_integral_v<U>);
        return static_cast<std::size_t>(integral);
    }

    std::size_t codigoEspalhamento(std::string const& s) const
    {
        std::size_t h = 0;

        for (char c : s)
        {
            h = h * 31 + static_cast<std::size_t>(c);
        }

        return h;
    }
};

#endif