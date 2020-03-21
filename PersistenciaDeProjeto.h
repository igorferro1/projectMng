#ifndef PERSISTENCIADEPROJETO_H
#define PERSISTENCIADEPROJETO_H

#include "Projeto.h"

class PersistenciaDeProjeto
{
public:
    PersistenciaDeProjeto();
    virtual ~PersistenciaDeProjeto();

    Projeto* carregar(string arquivo);
    void salvar(Projeto *p, string arquivo);

private:

};

#endif // PERSISTENCIADEPROJETO_H
