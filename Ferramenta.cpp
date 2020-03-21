#include "Ferramenta.h"
#include <iostream>

using namespace std;

Ferramenta::Ferramenta(string nome, double custoDiario) : Recurso(nome), custoDiario(custoDiario)
{
    //ctor
}

Ferramenta::~Ferramenta()
{
    //dtor
}
double Ferramenta::getCustoDiario()
{
    return custoDiario;
}

void Ferramenta::imprimir()
{
    cout << "Ferramenta: " << nome << " - R$" << custoDiario << " por dia" << endl;
}

double Ferramenta::getCusto(int dias)
{
    return dias*custoDiario;
}
