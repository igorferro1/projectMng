#ifndef ATIVIDADEDEESFORCOFIXO_H
#define ATIVIDADEDEESFORCOFIXO_H

#include "Atividade.h"


class AtividadeDeEsforcoFixo : public Atividade
{
public:
    AtividadeDeEsforcoFixo(string nome, int horasNecessarias);
    virtual ~AtividadeDeEsforcoFixo();

    virtual int getHorasNecessarias();
    int getDuracao();
private:
    string nome;
    int horasNecessarias;
};

#endif // ATIVIDADEDEESFORCOFIXO_H
