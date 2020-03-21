#include "Pessoa.h"
#include <iostream>

using namespace std;

Pessoa::Pessoa(string nome, double valorPorHora, int horasDiarias) : Recurso(nome), valorPorHora(valorPorHora), horasDiarias(horasDiarias)
{
    if (valorPorHora <= 0) throw new invalid_argument ("Valor por hora menor que zero");
    if (horasDiarias <= 0) throw new invalid_argument ("Horas diarias menores que zero");
    recebeValor = true;
}

Pessoa::Pessoa(string nome, int horasDiarias) : Recurso(nome), horasDiarias(horasDiarias)
{
    if (horasDiarias <= 0) throw new invalid_argument ("Horas diarias menores que zero");
    recebeValor = false;
}

Pessoa::~Pessoa()
{

}

double Pessoa::valorPorHoraPadrao = 10;
bool Pessoa::recebeuPadrao = false;

bool Pessoa::getRecebeValor(){
    return recebeValor;
}

double Pessoa::getValorPorHora()
{
    if (recebeValor)
        return valorPorHora;

    return Pessoa::valorPorHoraPadrao;
}

int Pessoa::getHorasDiarias()
{
    return horasDiarias;
}

bool Pessoa::recebeValorPadrao()
{
    return Pessoa::recebeuPadrao;
}

void Pessoa::setValorPorHoraPadrao(double valor)
{
    Pessoa::valorPorHoraPadrao = valor;
    Pessoa::recebeuPadrao = true;
}

double Pessoa::getValorPorHoraPadrao()
{
    return Pessoa::valorPorHoraPadrao;
}

void Pessoa::imprimir()
{
    cout << nome << " - R$";
    if (recebeValor)
       cout << valorPorHora;
    else
        cout << Pessoa::valorPorHoraPadrao;

    cout << " - " << horasDiarias << "h por dia" << endl;
}

double Pessoa::getCusto(int dias)
{
    if (recebeValor){
        return dias*horasDiarias*valorPorHora;
    }
    return dias*horasDiarias*Pessoa::valorPorHoraPadrao;
}
