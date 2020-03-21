#include "AtividadeDeEsforcoFixo.h"
#include <iostream>
#include <cmath>

using namespace std;

AtividadeDeEsforcoFixo::AtividadeDeEsforcoFixo(string nome, int horasNecessarias) : Atividade(nome), horasNecessarias(horasNecessarias)
{

}

AtividadeDeEsforcoFixo::~AtividadeDeEsforcoFixo()
{
    //dtor
}

int AtividadeDeEsforcoFixo::getHorasNecessarias()
{
    return horasNecessarias;
}

int AtividadeDeEsforcoFixo::getDuracao()
{
    if (estaTerminada())
        return duracaoReal;
    int horasPorDia = 0;
    bool temPessoas = false;
    for (int i = 0; i < quantidadeDeRecursos; i++){
        Pessoa* p1 = dynamic_cast<Pessoa*>(recursos[i]);
        if (p1 != nullptr){
            temPessoas = true;
            horasPorDia += p1->getHorasDiarias();

        }
    }
    if (!temPessoas) throw new logic_error ("Sem pessoas na atividade");
    return ceil(1.0 * horasNecessarias/horasPorDia);
}
