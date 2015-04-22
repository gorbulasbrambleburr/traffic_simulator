// Copyright (c) <2015>, <Makhles Reuter Lange>
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// The views and conclusions contained in the software and documentation are
// those of the authors and should not be interpreted as representing official
// policies, either expressed or implied, of the FreeBSD Project.

/// \author Makhles R. Lange
/// \since 5/4/2015
/// \version 1.0

#ifndef LISTAENC_H
#define LISTAENC_H

#include "Elemento.hpp"

const int ERRO_LISTA_CHEIA = 10;
const int ERRO_LISTA_VAZIA = 20;
const int ERRO_LISTA_POSICAO = 30;
const int ERRO_LISTA_DADO_INEXISTENTE = 40;

template<typename T>
class ListaEnc {
 public:
    ////////////////////////////////////////////////////////////////////////////
	/// Construtor da classe ListaEnc.
	/// Ao ser criada, possui tamanho 0 e aponta para lugar nenhum.
	////////////////////////////////////////////////////////////////////////////
	ListaEnc<T>() : _head(NULL) , _size(0) {}



    ////////////////////////////////////////////////////////////////////////////
	/// Destrutor da classe. Utiliza o método destroiLista() para isso.
	////////////////////////////////////////////////////////////////////////////
	~ListaEnc() {
	    destroiLista();
    }


    ////////////////////////////////////////////////////////////////////////////
	/// Adiciona o dado fornecido no início da lista. Se o novo elemento não
	/// puder ser criado, lança a exceção ERRO_LISTA_CHEIA.
	///
	/// \param dado T& - o dado a ser inserido.
	////////////////////////////////////////////////////////////////////////////
	void adicionaNoInicio(const T& dado) {
	    Elemento<T> *novo;
	    if (!(novo = new Elemento<T>(dado, _head))) {
	        throw ERRO_LISTA_CHEIA;
	    }
	    _head = novo;
	    _size++;
	}


    ////////////////////////////////////////////////////////////////////////////
	/// Retira o dado que estiver no início da lista. Se a lista estiver vazia,
	/// lança a exceção ERRO_LISTA_VAZIA.
	///
	/// \return T - o dado do início da lista.
	////////////////////////////////////////////////////////////////////////////
	T retiraDoInicio() {
	    if (listaVazia()) {
	        throw ERRO_LISTA_VAZIA;
	    } else {
			Elemento<T> *elemento = _head;
			T dado = _head->getInfo();
			_head = _head->getProximo();
			delete elemento;
			_size--;
			return dado;
		}
	}


    ////////////////////////////////////////////////////////////////////////////
    /// Elimina o dado que estiver no início da lista. Se a lista estiver vazia,
	/// lança a exceção ERRO_LISTA_VAZIA.
	////////////////////////////////////////////////////////////////////////////
	void eliminaDoInicio() {
		if (listaVazia()) {
	        throw ERRO_LISTA_VAZIA;
	    } else {
			Elemento<T> *elemento = _head;
			_head = _head->getProximo();
			delete elemento;
			_size--;
		}
	}



    ////////////////////////////////////////////////////////////////////////////
	/// Adiciona o dado fornecido na posição indicada. Se o novo elemento não
	/// puder ser criado, lança a exceção ERRO_LISTA_CHEIA. Se a posição na qual
	/// o dado deve ser inserido for igual a 0, delega o trabalho para o método
	/// adicionaNaPosicao.
	///
	/// \param dado T& - o dado a ser inserido.
	/// \param pos int - a posição na qual o dado deve ser inserido.
	////////////////////////////////////////////////////////////////////////////
	void adicionaNaPosicao(const T& dado, int pos) {
	    if (pos > _size || pos < 0) {
	        throw ERRO_LISTA_POSICAO;
	    } else if (pos == 0) {
			try {
				adicionaNoInicio(dado);
			}
			catch (int& e) {
				throw;  // ERRO_LISTA_CHEIA
			}
		} else {
			int i;
			Elemento<T> *novo, *anterior = _head;

			for (i = 1; i < pos; i++) {
				anterior = anterior->getProximo();
			}

			if (!(novo = new Elemento<T>(dado, anterior->getProximo()))) {
				throw ERRO_LISTA_CHEIA;
			} else {
				anterior->setProximo(novo);
				_size++;
			}
	    }
	}

    ////////////////////////////////////////////////////////////////////////////
	/// Retorna a posição que o dado fornecido ocupa na lista. Se a lista esti-
	/// ver vazia, lança a exceção ERRO_LISTA_VAZIA. Se o dado não estiver na
	/// lista, lança a exceção ERRO_LISTA_DADO_INEXISTENTE.
	///
	/// \param dado T& - o dado a ser procurado.
	/// \return int    - a posição do dado.
	////////////////////////////////////////////////////////////////////////////
	int posicao(const T& dado) const {
	    if (listaVazia()) {
	        throw ERRO_LISTA_VAZIA;
        } else {
	        int pos;
	        Elemento<T> *atual = _head;

			for (pos = 0; pos < _size; pos++) {
				if (igual(dado, atual->getInfo())) {
					return pos;
				} else {
					atual = atual->getProximo();
				}
			}
			throw ERRO_LISTA_DADO_INEXISTENTE;
	    }
	}


    ////////////////////////////////////////////////////////////////////////////
	/// Retorna um ponteiro para o endereço do dado fornecido. Se a lista esti-
	/// ver vazia, lança a exceção ERRO_LISTA_VAZIA. Se o dado não estiver na
	/// lista, lança a exceção ERRO_LISTA_DADO_INEXISTENTE.
	///
	/// \param dado T& - o dado a ser procurado.
	/// \return T*     - o ponteiro para o dado fornecido.
	////////////////////////////////////////////////////////////////////////////
	T* posicaoMem(const T& dado) const {
		if (listaVazia()) {
	        throw ERRO_LISTA_VAZIA;
        } else {
	        int pos;
	        Elemento<T> *atual = _head;

			for (pos = 0; pos < _size; pos++) {
				if (igual(dado, atual->getInfo())) {
					return &(atual->getInfo());
				} else {
					atual = atual->getProximo();
				}
			}
			throw ERRO_LISTA_DADO_INEXISTENTE;
	    }
	}


    ////////////////////////////////////////////////////////////////////////////
	/// Verifica se a lista contém o dado fornecido.
	///
	/// \return bool - true se o dado estiver presente.
	////////////////////////////////////////////////////////////////////////////
	bool contem(const T& dado) {
		try {
			posicao(dado);
			return true;
		}
		catch(int &ex) {
			return false;
		}
	}


    ////////////////////////////////////////////////////////////////////////////
	/// Retira o dado da posição fornecida. Se a lista estiver vazia, lança a
	/// exceção ERRO_LISTA_VAZIA. Se a posição estiver incorreta, lança a exce-
	/// ção ERRO_LISTA_POSICAO.
	///
	/// \return T - o dado da posição fornecida.
	////////////////////////////////////////////////////////////////////////////
	T retiraDaPosicao(int pos) {
	    if (listaVazia()) {
			throw ERRO_LISTA_VAZIA;
		} else if (pos >= _size || pos < 0) {
            throw ERRO_LISTA_POSICAO;
	    } else {
	        int i;
	        Elemento<T> *retirado, *anterior = _head;
	        T dado;

            for (i = 1; i < pos; i++) {
                anterior = anterior->getProximo();
            }

            retirado = anterior->getProximo();
            dado = retirado->getInfo();

            anterior->setProximo(retirado->getProximo());

            _size--;
            delete retirado;
            return dado;
	    }
	}




    ////////////////////////////////////////////////////////////////////////////
	/// Insere o dado fornecido ao final da lista.
	///
	/// \param T& - o dado a ser inserido.
	////////////////////////////////////////////////////////////////////////////
	void adiciona(const T& dado) {
	    adicionaNaPosicao(dado, _size);
	}



    ////////////////////////////////////////////////////////////////////////////
	/// Retira o dado que estiver no final da lista. Se a lista estiver vazia,
	/// lança a exceção ERRO_LISTA_VAZIA.
	///
	/// \return T - o dado no final da lista.
	////////////////////////////////////////////////////////////////////////////
	T retira() {
	    try {
	        return retiraDaPosicao(_size-1);
        }
        catch (int e) {
            throw;
        }
	}



    ////////////////////////////////////////////////////////////////////////////
	/// Retira da lista o dado fornecido. Se a lista estiver vazia, lança a
	/// exceção ERRO_LISTA_VAZIA. Se o dado não estiver na lista, lança a exce-
	/// ção ERRO_LISTA_DADO_INEXISTENTE.
	///
	/// \param dado T& - o dado a ser retirado.
	/// \return T      - o dado retirado.
	////////////////////////////////////////////////////////////////////////////
	T retiraEspecifico(const T& dado) {
		if (listaVazia()) {
	        throw ERRO_LISTA_VAZIA;
        } else {
	        int pos;
			Elemento<T> *anterior, *atual;
			anterior = atual = _head;

			for (pos = 0; pos < _size; pos++) {
				if (igual(dado, atual->getInfo())) {
					anterior->setProximo(atual->getProximo());
					T tmp_dado = atual->getInfo();
					delete atual;
					_size--;
					return tmp_dado;
				} else {
					anterior = atual;
					atual = atual->getProximo();
				}
			}
			throw ERRO_LISTA_DADO_INEXISTENTE;
	    }
	}


    ////////////////////////////////////////////////////////////////////////////
	/// Adiciona o dado segundo uma ordem pré-estabelecida: crescente. Se a
	/// lista estiver cheia, lança a exceção ERRO_LISTA_CHEIA.
	///
	/// \param dado T& - o dado a ser inserido.
	////////////////////////////////////////////////////////////////////////////
	void adicionaEmOrdem(const T& dado) {
		if (listaVazia()) {
			adicionaNoInicio(dado);
		} else {
			try {
				int pos = 0;
				Elemento<T> *elemento = _head;
				while ((elemento->getProximo())
				         && maior(dado, elemento->getInfo())) {
					pos++;
					elemento = elemento->getProximo();
				}
				if (maior(dado, elemento->getInfo())) {
					adicionaNaPosicao(dado, ++pos);
				} else {
					adicionaNaPosicao(dado, pos);
				}
			}
			catch (int &ex) {
				throw;  // ERRO_LISTA_CHEIA
			}
		}
	}


    ////////////////////////////////////////////////////////////////////////////
	/// Verifica se a lista está vazia.
	///
	/// \return bool - true se estiver vazia.
	////////////////////////////////////////////////////////////////////////////
	bool listaVazia() const {
	    return !_size;
	}


    ////////////////////////////////////////////////////////////////////////////
	/// Verifica se os dois dados fornecidos são iguais. Considera-se que o tipo
	/// de dado T implemente o operador ==.
	///
	/// \param dado1 T - o primeiro dado a ser comparado.
	/// \param dado2 T - o segundo dado a ser comparado.
	/// \return bool -  true se forem iguais.
	////////////////////////////////////////////////////////////////////////////
	bool igual(T dado1, T dado2) const {
	    return (dado1 == dado2);
	}


    ////////////////////////////////////////////////////////////////////////////
	/// Verifica a desigualdade entre os dados fornecidos. Considera-se que o
	/// tipo de dado T implemente o operador >.
	///
	/// \param dado1 T - o primeiro dado a ser comparado.
	/// \param dado2 T - o segundo dado a ser comparado.
	/// \return bool   -  true se o dado1 for maior que o dado2.
	////////////////////////////////////////////////////////////////////////////
	bool maior(T dado1, T dado2) const {
	    return (dado1 > dado2);
	}


    ////////////////////////////////////////////////////////////////////////////
	/// Verifica a desigualdade entre os dados fornecidos. Considera-se que o
	/// tipo de dado T implemente o operador <.
	///
	/// \param dado1 T - o primeiro dado a ser comparado.
	/// \param dado2 T - o segundo dado a ser comparado.
	/// \return bool   -  true se o dado1 for menor que o dado2.
	////////////////////////////////////////////////////////////////////////////
	bool menor(T dado1, T dado2) const {
	    return (dado1 < dado2);
	}


    ////////////////////////////////////////////////////////////////////////////
	/// Limpa a lista, removendo a memória alocada correspondente a cada elemen-
	/// to da lista.
	////////////////////////////////////////////////////////////////////////////
	void destroiLista() {
	    Elemento<T> *anterior, *atual = _head;

	    while (atual != NULL) {
	        anterior = atual;
	        atual = atual->getProximo();
	        delete anterior;
	    }
	    _size = 0;
	    _head = NULL;
	}

 protected:
	Elemento<T>* _head;
	int _size;
};
#endif

