#ifndef PESSOA_H
#define PESSOA_H

#include "Recurso.h"
#include <stdexcept>

class Pessoa : public Recurso
{
public:
    Pessoa(string nome, double valorPorHora, int horasDiarias);
    Pessoa(string nome,int horasDiarias);
    virtual ~Pessoa();

    virtual double getValorPorHora();
    virtual int getHorasDiarias();
    virtual bool recebeValorPadrao();

    static void setValorPorHoraPadrao(double valor);
    static double getValorPorHoraPadrao();

    virtual void imprimir();
    virtual double getCusto(int dias);

    virtual bool getRecebeValor();
private:
    double valorPorHora;
    int horasDiarias;
    bool recebeValor;
    static double valorPorHoraPadrao;
    static bool recebeuPadrao;

};

#endif // PESSOA_H
