#include "Recurso.h"

Recurso::Recurso(string nome) : nome(nome)
{
    //ctor
}

Recurso::~Recurso()
{
    //dtor
}

string Recurso::getNome()
{
    return nome;
}

