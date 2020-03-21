#include "Projeto.h"
#include <vector>
#include <list>
#include <stdexcept>

using namespace std;

Projeto::Projeto(string nome) : nome(nome)
{
    atividades = new vector<Atividade*>();
    recursos = new list<Recurso*>();
}

Projeto::~Projeto()
{

}

string Projeto::getNome()
{
    return nome;
}

void Projeto::adicionar(Atividade* a)
{
    atividades->push_back(a);
}

vector<Atividade*>* Projeto::getAtividades()
{
    return atividades;
}

void Projeto::adicionar(Recurso* r)
{

    list<Recurso*>::iterator i = recursos->begin();
    while (i != recursos->end()){
        if (r == (*i))
            throw new invalid_argument ("Recurso previamente adicionado");
        i++;
    }
    recursos->push_back(r);
}

list<Recurso*>* Projeto::getRecursos()
{
    return recursos;
}

int Projeto::getDuracao()
{
    int duracaoTotal = 0;
    for (unsigned int i = 0; i < atividades->size(); i++){
        duracaoTotal += atividades->at(i)->getDuracao();
    }
    return duracaoTotal;
}

int Projeto::getDuracao(bool terminadas)
{
    int duracaoTotal = 0;
    for (unsigned int i = 0; i < atividades->size(); i++){
        if (atividades->at(i)->estaTerminada() == terminadas){
            duracaoTotal += atividades->at(i)->getDuracao();
        }
    }
    return duracaoTotal;
}

double Projeto::getCusto()
{
  int custoTotal = 0;
    for (unsigned int i = 0; i < atividades->size(); i++){
        custoTotal += atividades->at(i)->getCusto();
    }
    return custoTotal;
}

void Projeto::imprimir()
{
    cout << getNome() << " - R$" << getCusto() << endl;
    cout << "Duracao:" << endl;
    cout << "- Feito " << getDuracao(true) << " dias" << endl;
    cout << "- Falta " << getDuracao(false) << " dias" << endl;
    cout << "- Total " << getDuracao() << " dias" << endl;
    cout << "----" << endl;
    for (unsigned int i = 0; i < atividades->size(); i++){
        atividades->at(i)->imprimir();
    }
    cout << endl;
}
