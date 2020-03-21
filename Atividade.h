/***************************************************************/
/**                                                           **/
/**   Igor Nunes Ferro e Thomaz Assaf Pougy                   **/
/**   NUSPS: 10774138 e 9795907                               **/
/**   Exercicio-Programa 01                                   **/
/**   Professor: Pedro Luiz Pizzigati Correa                  **/
/**   Turma: T6T                                              **/
/**                                                           **/
/***************************************************************/
#ifndef ATIVIDADE_H
#define ATIVIDADE_H

#include "Pessoa.h"
#include "Recurso.h"

using namespace std;


class Atividade{
public:
    Atividade(string nome);
    virtual ~Atividade();

    virtual string getNome();

    virtual void adicionar(Recurso* r);
    virtual Recurso** getRecursos();
    virtual int getQuantidadeDeRecursos();

    virtual int getDuracao() = 0;
    virtual double getCusto();

    virtual void terminar(int duracaoReal);
    virtual bool estaTerminada();

    virtual void imprimir();
    static const int MAX_RECURSOS = 10;
protected:
    string nome;
    int quantidadeDeRecursos;
    Recurso** recursos;
    bool terminou;
    int duracaoReal;
};
#endif
