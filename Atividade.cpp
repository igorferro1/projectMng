/***************************************************************/
/**                                                           **/
/**   Igor Nunes Ferro e Thomaz Assaf Pougy                   **/
/**   NUSPS: 10774138 e 9795907                               **/
/**   Exercicio-Programa 01                                   **/
/**   Professor: Pedro Luiz Pizzigati Correa                  **/
/**   Turma: T6T                                              **/
/**                                                           **/
/***************************************************************/
#include "Atividade.h"
#include <cmath>
#include <string>

using namespace std;

Atividade::Atividade(string nome) : nome(nome){
  quantidadeDeRecursos = 0;
  recursos = new Recurso*[MAX_RECURSOS];
  terminou = false;
}

Atividade::~Atividade() {

}

string Atividade::getNome() {
  return nome;
}

Recurso** Atividade::getRecursos() {
  return recursos;
}

int Atividade::getQuantidadeDeRecursos() {
  return quantidadeDeRecursos;
}

double Atividade::getCusto() {
    double custo = 0;
    for (int i = 0; i < quantidadeDeRecursos; i++) {
        custo += (recursos[i]->getCusto(getDuracao()));
    }
    return custo;
}

void Atividade::adicionar(Recurso* r) {
    try{
      if (quantidadeDeRecursos >= MAX_RECURSOS) {
        throw new overflow_error ("Recursos ja esta cheio");
      } else if (quantidadeDeRecursos != 0 ) {
        for(int i = 0; i < quantidadeDeRecursos; i++) {
          if (r == recursos[i]) {
            throw new invalid_argument ("Nao foi possivel adicionar recurso");
          }
        }
      }
      recursos[quantidadeDeRecursos] = r;
      quantidadeDeRecursos++;
    }
    catch(invalid_argument *e){
        cout << e->what() << endl;
        delete e;
    }
}

void Atividade::terminar(int duracaoReal)
{

    if (duracaoReal <= 0){
        throw new invalid_argument ("Duracao Real menor ou igual a 0");
    }
    terminou = true;
    this->duracaoReal = duracaoReal;
}

bool Atividade::estaTerminada()
{
    return terminou;
}


void Atividade::imprimir() {
  cout << nome << " - " << getDuracao();
  if (getDuracao() == 1) {
    cout << " dia - R$" << getCusto() << endl;
  } else {
    cout << " dias - R$" << getCusto() << endl;
  }
}


