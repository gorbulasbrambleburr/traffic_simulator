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
/// \since 12/4/2015
/// \version 1.0

#ifndef FILAENC_H
#define FILAENC_H

#include "ListaEnc.hpp"

const int ERRO_FILA_VAZIA = 10;
const int ERRO_FILA_CHEIA = 20;

template<typename T>
class FilaEnc : private ListaEnc<T> {
 public:
	////////////////////////////////////////////////////////////////////////////
	/// Construtor da classe FilaEnc.
	/// Usa o construtor da class base, o qual inicializa o tamanho em 0 e
	/// e _head = NULL.
	////////////////////////////////////////////////////////////////////////////
	FilaEnc<T>() :
		ListaEnc<T>(),      // Construtor da classe base
		_tail(NULL) {}      // Atributo desta classe




	////////////////////////////////////////////////////////////////////////////
	/// Destrutor da classe. Utiliza o método limparFila() para isso.
	////////////////////////////////////////////////////////////////////////////
	~FilaEnc() {
		limparFila();
    }




	////////////////////////////////////////////////////////////////////////////
	/// Retira o dado que estiver no início da fila. Usa o método retiraDoInicio
	/// da classe base se o tamanho da fila for superior a 1.
	///
	/// \return T - o dado do início.
	////////////////////////////////////////////////////////////////////////////
	T retira() {
		if(ListaEnc<T>::_size > 1) {
			return ListaEnc<T>::retiraDoInicio();
		} else {
			if (filaVazia()) {
				throw ERRO_FILA_VAZIA;
			} else {
				// _size == 1
				T dado = ListaEnc<T>::_head->getInfo();
				limparFila();
				return dado;
			}
		}
	}




	////////////////////////////////////////////////////////////////////////////
	/// Insere o dado fornecido no final da fila.
	///
	/// \param T& - o dado a ser inserido.
	////////////////////////////////////////////////////////////////////////////
	void inclui(const T& dado) {
		Elemento<T> *novo;
		if ((novo = new Elemento<T>(dado, NULL))) {
			if(filaVazia()) {
				ListaEnc<T>::_head = novo;
			} else {
				_tail->setProximo(novo);
			}
			_tail = novo;
			ListaEnc<T>::_size++;
		} else {
			throw ERRO_FILA_CHEIA;
		}
	}




	////////////////////////////////////////////////////////////////////////////
	/// Retorna o último elemento da fila sem removê-lo.
	///
	/// \return T - o último elemento da fila.
	////////////////////////////////////////////////////////////////////////////
	T ultimo() const {
		if (filaVazia()) {
			throw ERRO_FILA_VAZIA;
		} else {
			return _tail->getInfo();
		}
	}




	////////////////////////////////////////////////////////////////////////////
	/// Retorna o primeiro elemento da fila sem removê-lo.
	///
	/// \return T - o primeiro elemento da fila.
	////////////////////////////////////////////////////////////////////////////
	T primeiro() const {
		if (filaVazia()) {
			throw ERRO_FILA_VAZIA;
		} else {
			return ListaEnc<T>::_head->getInfo();
		}
	}




    ////////////////////////////////////////////////////////////////////////////
	/// Verifica se a fila está vazia.
	///
	/// \return bool - true se estiver vazia.
	////////////////////////////////////////////////////////////////////////////
	bool filaVazia() const {
		return ListaEnc<T>::listaVazia();
	}




	////////////////////////////////////////////////////////////////////////////
	/// Limpa a fila, removendo a memória alocada correspondente a cada elemen-
	/// to desta.
	////////////////////////////////////////////////////////////////////////////
	void limparFila() {
		ListaEnc<T>::destroiLista();
		_tail = NULL;
	}




 private:
	Elemento<T> *_tail;  //< Ponteiro para o último elemento da fila.
};
#endif
