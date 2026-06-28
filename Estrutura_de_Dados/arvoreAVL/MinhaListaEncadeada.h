#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
#include "Elemento.h"
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
using namespace std;

template<typename T>
class MinhaListaEncadeada : public ListaEncadeadaAbstrata<T>
{
private:
    Elemento<T>* primeiro;
    size_t qtd;

public:
    MinhaListaEncadeada() : primeiro(nullptr), qtd(0) {}

    virtual ~MinhaListaEncadeada() {
        while (!vazia()) {
            removerDoInicio();
        }
    }

    virtual size_t tamanho() const {
        return qtd;
    }

    virtual bool vazia() const {
        return qtd == 0;
    }

    virtual bool contem(T dado) const {
        Elemento<T>* atual = primeiro;

        while (atual != nullptr) {
            if (atual->dado == dado) {
                return true;
            }
            atual = atual->proximo;
        }

        return false;
    }

    virtual  size_t posicao(T dado) const {
        if (vazia()){
            throw ExcecaoListaEncadeadaVazia();
        }

        Elemento<T>* atual = primeiro;
        size_t i = 0;

        while (atual != nullptr) {
            if (atual->dado == dado) {
                return i;
            }
            atual = atual->proximo;
            i++;
        }

        throw ExcecaoDadoInexistente();
    }

    virtual void inserirNoInicio(T dado) {
        primeiro = new Elemento<T>(dado, primeiro);
        qtd++;
    }

    virtual void inserirNoFim(T dado) {
        if (vazia()) {
            inserirNoInicio(dado);
            return;
        }

        Elemento<T>* atual = primeiro;

        while (atual->proximo != nullptr) {
            atual = atual->proximo;
        }

        atual->proximo = new Elemento<T>(dado);
        qtd++;
    }

    virtual void inserir(size_t posicao, T dado) {
        if (posicao > qtd) {
            throw ExcecaoPosicaoInvalida();
        }

        if (posicao == 0) {
            inserirNoInicio(dado);
            return;
        }

        Elemento<T>* atual = primeiro;

        for (size_t i = 0; i < posicao - 1; i++) {
            atual = atual->proximo;
        }

        atual->proximo = new Elemento<T>(dado, atual->proximo);
        qtd++;
    }

    virtual T removerDoInicio() {
        if (vazia()){
            throw ExcecaoListaEncadeadaVazia();
        }

        Elemento<T>* removido = primeiro;
        T valor = removido->dado;

        primeiro = primeiro->proximo;
        delete removido;

        qtd--;
        return valor;
    }

    virtual T removerDoFim() {
        if (vazia()) {
            throw ExcecaoListaEncadeadaVazia();
        }

        if (qtd == 1) {
            return removerDoInicio();
        }

        Elemento<T>* atual = primeiro;

        while (atual->proximo->proximo != nullptr) {
            atual = atual->proximo;
        }

        Elemento<T>* removido = atual->proximo;
        T valor = removido->dado;

        atual->proximo = nullptr;
        delete removido;

        qtd--;
        return valor;
    }

    virtual T removerDe(size_t posicao) {
        if (posicao >= qtd) {
            throw ExcecaoPosicaoInvalida();
        }

        if (posicao == 0) {
            return removerDoInicio();
        }

        Elemento<T>* atual = primeiro;

        for (size_t i = 0; i < posicao - 1; i++) {
            atual = atual->proximo;
        }

        Elemento<T>* removido = atual->proximo;
        T valor = removido->dado;

        atual->proximo = removido->proximo;
        delete removido;

        qtd--;
        return valor;
    }

    virtual void remover(T dado) {
        if (vazia()) {
            throw ExcecaoListaEncadeadaVazia();
        }

        if (primeiro->dado == dado) {
            removerDoInicio();
            return;
        }

        Elemento<T>* atual = primeiro;

        while (atual->proximo != nullptr && atual->proximo->dado != dado) {
            atual = atual->proximo;
        }

        if (atual->proximo == nullptr) {
            throw ExcecaoDadoInexistente();
        }

        Elemento<T>* removido = atual->proximo;

        atual->proximo = removido->proximo;
        delete removido;

        qtd--;
    }
};

#endif