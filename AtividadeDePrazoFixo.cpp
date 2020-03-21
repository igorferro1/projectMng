#include "AtividadeDePrazoFixo.h"
#include <stdexcept>

AtividadeDePrazoFixo::AtividadeDePrazoFixo(string nome, int dias) : Atividade(nome), dias(dias)
{
    if (dias <= 0)
        throw new invalid_argument ("dias menores ou iguais a 0");
}

AtividadeDePrazoFixo::~AtividadeDePrazoFixo()
{

}

int AtividadeDePrazoFixo::getPrazo()
{
    return dias;
}

int AtividadeDePrazoFixo::getDuracao()
{
    if (estaTerminada())
        return duracaoReal;
    return dias;
}
