#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "ArvoreBinariaDeBusca.h"
#include "MinhaListaEncadeada.h"

template <typename T>
class MinhaArvoreAVL final : public ArvoreBinariaDeBusca<T>
{
private:
    int alturaNo(Nodo<T>* no) const
    {
        if (no != nullptr)
        {
            return no->altura;
        }
        return -1;
    }

    void atualizarAltura(Nodo<T>* no)
    {
        int he = alturaNo(no->filhoEsquerda);
        int hd = alturaNo(no->filhoDireita);

        if (he > hd)
        {
            no->altura = 1 + he;
        }
        else
        {
            no->altura = 1 + hd;
        }
    }

    int fatorBalanceamento(Nodo<T>* no) const
    {
        return alturaNo(no->filhoEsquerda) - alturaNo(no->filhoDireita);
    }

    Nodo<T>* rotacaoDireita(Nodo<T>* y)
    {
        Nodo<T>* x        = y->filhoEsquerda;
        Nodo<T>* subArvore = x->filhoDireita;

        x->filhoDireita  = y;
        y->filhoEsquerda = subArvore;

        atualizarAltura(y);
        atualizarAltura(x);
        return x;
    }

    Nodo<T>* rotacaoEsquerda(Nodo<T>* x)
    {
        Nodo<T>* y        = x->filhoDireita;
        Nodo<T>* subArvore = y->filhoEsquerda;

        y->filhoEsquerda = x;
        x->filhoDireita  = subArvore;

        atualizarAltura(x);
        atualizarAltura(y);
        return y;
    }

    Nodo<T>* rebalancear(Nodo<T>* no)
    {
        atualizarAltura(no);
        int fb = fatorBalanceamento(no);

        if (fb > 1 && fatorBalanceamento(no->filhoEsquerda) >= 0)
        {
            return rotacaoDireita(no);
        }

        if (fb > 1 && fatorBalanceamento(no->filhoEsquerda) < 0)
        {
            no->filhoEsquerda = rotacaoEsquerda(no->filhoEsquerda);
            return rotacaoDireita(no);
        }

        if (fb < -1 && fatorBalanceamento(no->filhoDireita) <= 0)
        {
            return rotacaoEsquerda(no);
        }

        if (fb < -1 && fatorBalanceamento(no->filhoDireita) > 0)
        {
            no->filhoDireita = rotacaoDireita(no->filhoDireita);
            return rotacaoEsquerda(no);
        }

        return no;
    }

    Nodo<T>* inserirRec(Nodo<T>* no, T chave)
    {
        if (no == nullptr)
        {
            Nodo<T>* novo = new Nodo<T>();
            novo->chave         = chave;
            novo->altura        = 0;
            novo->filhoEsquerda = nullptr;
            novo->filhoDireita  = nullptr;
            return novo;
        }

        if (chave < no->chave)
        {
            no->filhoEsquerda = inserirRec(no->filhoEsquerda, chave);
        }
        else if (chave > no->chave)
        {
            no->filhoDireita = inserirRec(no->filhoDireita, chave);
        }
        else
        {
            return no;
        }

        return rebalancear(no);
    }

    Nodo<T>* minimo(Nodo<T>* no) const
    {
        while (no->filhoEsquerda != nullptr)
        {
            no = no->filhoEsquerda;
        }
        return no;
    }

    Nodo<T>* removerRec(Nodo<T>* no, T chave)
    {
        if (no == nullptr)
        {
            return nullptr;
        }

        if (chave < no->chave)
        {
            no->filhoEsquerda = removerRec(no->filhoEsquerda, chave);
        }
        else if (chave > no->chave)
        {
            no->filhoDireita = removerRec(no->filhoDireita, chave);
        }
        else
        {
            if (no->filhoEsquerda == nullptr || no->filhoDireita == nullptr)
            {
                Nodo<T>* filho = nullptr;

                if (no->filhoEsquerda != nullptr)
                {
                    filho = no->filhoEsquerda;
                }
                else
                {
                    filho = no->filhoDireita;
                }

                delete no;
                return filho;
            }
            else
            {
                Nodo<T>* suc = minimo(no->filhoDireita);
                no->chave = suc->chave;
                no->filhoDireita = removerRec(no->filhoDireita, suc->chave);
            }
        }

        return rebalancear(no);
    }

    void destruirRec(Nodo<T>* no)
    {
        if (no == nullptr)
        {
            return;
        }
        destruirRec(no->filhoEsquerda);
        destruirRec(no->filhoDireita);
        delete no;
    }

    Nodo<T>* buscar(Nodo<T>* no, T chave) const
    {
        if (no == nullptr)
        {
            return nullptr;
        }
        if (chave == no->chave)
        {
            return no;
        }
        if (chave < no->chave)
        {
            return buscar(no->filhoEsquerda, chave);
        }
        else
        {
            return buscar(no->filhoDireita, chave);
        }
    }

    int contarRec(Nodo<T>* no) const
    {
        if (no == nullptr)
        {
            return 0;
        }
        return 1 + contarRec(no->filhoEsquerda) + contarRec(no->filhoDireita);
    }

    void emOrdemRec(Nodo<T>* no, MinhaListaEncadeada<T>* lista) const
    {
        if (no == nullptr)
        {
            return;
        }
        emOrdemRec(no->filhoEsquerda, lista);
        lista->inserirNoFim(no->chave);
        emOrdemRec(no->filhoDireita, lista);
    }

    void preOrdemRec(Nodo<T>* no, MinhaListaEncadeada<T>* lista) const
    {
        if (no == nullptr)
        {
            return;
        }
        lista->inserirNoFim(no->chave);
        preOrdemRec(no->filhoEsquerda, lista);
        preOrdemRec(no->filhoDireita, lista);
    }

    void posOrdemRec(Nodo<T>* no, MinhaListaEncadeada<T>* lista) const
    {
        if (no == nullptr)
        {
            return;
        }
        posOrdemRec(no->filhoEsquerda, lista);
        posOrdemRec(no->filhoDireita, lista);
        lista->inserirNoFim(no->chave);
    }

public:
    virtual ~MinhaArvoreAVL()
    {
        destruirRec(this->raiz);
        this->raiz = nullptr;
    };

    virtual bool vazia() const
    {
        return this->raiz == nullptr;
    };

    virtual int quantidade() const
    {
        return contarRec(this->raiz);
    };

    virtual bool contem(T chave) const
    {
        Nodo<T>* no = buscar(this->raiz, chave);
        return no != nullptr;
    };

    virtual std::optional<int> altura(T chave) const
    {
        Nodo<T>* no = buscar(this->raiz, chave);
        if (no == nullptr)
        {
            return std::nullopt;
        }
        return no->altura;
    };

    virtual void inserir(T chave)
    {
        this->raiz = inserirRec(this->raiz, chave);
    };

    virtual void remover(T chave)
    {
        this->raiz = removerRec(this->raiz, chave);
    };

    virtual std::optional<T> filhoEsquerdaDe(T chave) const
    {
        Nodo<T>* no = buscar(this->raiz, chave);
        if (no == nullptr || no->filhoEsquerda == nullptr)
        {
            return std::nullopt;
        }
        return no->filhoEsquerda->chave;
    };

    virtual std::optional<T> filhoDireitaDe(T chave) const
    {
        Nodo<T>* no = buscar(this->raiz, chave);
        if (no == nullptr || no->filhoDireita == nullptr)
        {
            return std::nullopt;
        }
        return no->filhoDireita->chave;
    };

    virtual ListaEncadeadaAbstrata<T>* emOrdem() const
    {
        MinhaListaEncadeada<T>* lista = new MinhaListaEncadeada<T>();
        emOrdemRec(this->raiz, lista);
        return lista;
    };

    virtual ListaEncadeadaAbstrata<T>* preOrdem() const
    {
        MinhaListaEncadeada<T>* lista = new MinhaListaEncadeada<T>();
        preOrdemRec(this->raiz, lista);
        return lista;
    };

    virtual ListaEncadeadaAbstrata<T>* posOrdem() const
    {
        MinhaListaEncadeada<T>* lista = new MinhaListaEncadeada<T>();
        posOrdemRec(this->raiz, lista);
        return lista;
    };
};

#endif