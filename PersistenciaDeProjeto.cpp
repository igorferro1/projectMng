#include "PersistenciaDeProjeto.h"
#include "Pessoa.h"
#include "Projeto.h"
#include "Atividade.h"
#include "AtividadeDeEsforcoFixo.h"
#include "AtividadeDePrazoFixo.h"
#include "Ferramenta.h"
#include "ErroDeArquivo.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
PersistenciaDeProjeto::PersistenciaDeProjeto()
{
    //ctor
}

PersistenciaDeProjeto::~PersistenciaDeProjeto()
{
    //dtor
}

Projeto* PersistenciaDeProjeto::carregar(string arquivo)
{
    ifstream carregado;
    carregado.open(arquivo);

    if (!carregado.good())
        throw new ErroDeArquivo ("Erro na abertura do arquivo");
    string nome;
    int numeroDeRecursos;

    carregado >> nome;
    if (!carregado.good())
        throw new ErroDeArquivo ("Erro na leitura");

    Projeto* projetoCarregado = new Projeto(nome);

    carregado >> numeroDeRecursos;
    if (!carregado.good())
        throw new ErroDeArquivo ("Erro na leitura");

    for (int i = 0; i < numeroDeRecursos; i++){
        char tipo;
        string nomeDoRecurso;

        carregado >> tipo;
        if (!carregado.good())
            throw new ErroDeArquivo ("Erro na leitura");

        carregado >> nomeDoRecurso;
        if (!carregado.good())
            throw new ErroDeArquivo ("Erro na leitura");

        if (tipo == 'P'){
            double valorPorHora;
            int horasDiarias;

            carregado >> valorPorHora;
            if (!carregado.good())
                throw new ErroDeArquivo ("Erro na leitura");

            carregado >> horasDiarias;
            if (!carregado.good())
                throw new ErroDeArquivo ("Erro na leitura");

            if(valorPorHora == -1){
                Pessoa* pTemp = new Pessoa(nomeDoRecurso, horasDiarias);
                projetoCarregado->adicionar(pTemp);
            }
            else{
                Pessoa* pTemp = new Pessoa(nomeDoRecurso, valorPorHora, horasDiarias);
                projetoCarregado->adicionar(pTemp);
            }
        }

        if (tipo == 'F'){
            double custoDiario;

            carregado >> custoDiario;
            if (!carregado.good())
                throw new ErroDeArquivo ("Erro na leitura");

            Ferramenta* fTemp = new Ferramenta(nomeDoRecurso, custoDiario);
            projetoCarregado->adicionar(fTemp);
        }
    }
    int numeroDeAtividades;

    carregado >> numeroDeAtividades;
    if (!carregado.good())
        throw new ErroDeArquivo ("Erro na leitura");

    for (unsigned int i = 0; i < numeroDeAtividades; i++){
        char tipo;
        string nomeDaAtividade;

        carregado >> tipo;
        if (!carregado.good())
            throw new ErroDeArquivo ("Erro na leitura");

        carregado >> nomeDaAtividade;
        if (!carregado.good())
            throw new ErroDeArquivo ("Erro na leitura");

        if (tipo == 'E'){
            int horasNecessarias;
            char terminada;

            carregado >> horasNecessarias;
            if (!carregado.good())
                throw new ErroDeArquivo ("Erro na leitura");


            AtividadeDeEsforcoFixo* ativiTemp = new AtividadeDeEsforcoFixo(nomeDaAtividade, horasNecessarias);

            carregado >> terminada;
            if (!carregado.good())
                throw new ErroDeArquivo ("Erro na leitura");

            if(terminada == 'T'){
                int diasTerminados;

                carregado >> diasTerminados;
                if (!carregado.good())
                    throw new ErroDeArquivo ("Erro na leitura");

                ativiTemp->terminar(diasTerminados);
            }

            projetoCarregado->adicionar(ativiTemp);
        }

        if (tipo == 'P'){
            int prazo;
            char terminada;

            carregado >> prazo;
            if (!carregado.good())
                throw new ErroDeArquivo ("Erro na leitura");


            AtividadeDePrazoFixo* ativiTemp = new AtividadeDePrazoFixo(nomeDaAtividade, prazo);

            carregado >> terminada;
            if (!carregado.good())
                throw new ErroDeArquivo ("Erro na leitura");

            if(terminada == 'T'){
                int diasTerminados;

                carregado >> diasTerminados;
                if (!carregado.good())
                    throw new ErroDeArquivo ("Erro na leitura");

                ativiTemp->terminar(diasTerminados);
            }

           projetoCarregado->adicionar(ativiTemp);
        }

        int numeroDeRecursosPorAtividade;
        vector<Atividade*>* atividades = projetoCarregado->getAtividades();

        carregado >> numeroDeRecursosPorAtividade;
        if (!carregado.good())
            throw new ErroDeArquivo ("Erro na leitura");

        for (int j = 0; j < numeroDeRecursosPorAtividade; j++){
            string nomeDoRecursoLido;
            carregado >> nomeDoRecursoLido;

            if (!carregado.good())
                throw new ErroDeArquivo ("Erro na leitura");

            list<Recurso*>::iterator k = projetoCarregado->getRecursos()->begin();

            while (k != projetoCarregado->getRecursos()->end()){
                if (nomeDoRecursoLido == (*k)->getNome())
                    atividades->at(i)->adicionar((*k));
                k++;
            }
        }
    }

    carregado.close();
    return projetoCarregado;
}

void PersistenciaDeProjeto::salvar(Projeto* p, string arquivo)
{
    ofstream salvo;
    salvo.open(arquivo, ios_base::trunc);
    if (!salvo.good())
            throw new ErroDeArquivo ("Erro na abertura");
    salvo << p->getNome() << endl;

    list<Recurso*>* recursos = p->getRecursos();

    salvo << recursos->size() << endl;

    list<Recurso*>::iterator j = recursos->begin();
    while (j != recursos->end()){
        Pessoa* p1 = dynamic_cast<Pessoa*>((*j));
        if (p1 != nullptr){
            salvo << "P ";
            salvo << p1->getNome() << " ";
            if(p1->getRecebeValor())
                salvo << p1->getValorPorHora() << " ";
            else
                salvo << "-1" << " ";
            salvo << p1->getHorasDiarias() << endl;
        } else{
            Ferramenta* f1 = dynamic_cast<Ferramenta*>((*j));
            salvo << "F " ;
            salvo << f1->getNome() << " ";
            salvo << f1->getCustoDiario() << endl;
        }
        j++;
    }

    vector<Atividade*>* atividades = p->getAtividades();

    salvo << atividades->size() << endl;
    int tamanho = atividades->size();

    for (int i = 0; i < tamanho; i++){
        AtividadeDeEsforcoFixo* esforco1 = dynamic_cast<AtividadeDeEsforcoFixo*>((*atividades)[i]);
        if (esforco1 != nullptr){
            salvo << "E ";
            salvo << esforco1->getNome() << " ";
            salvo << esforco1->getHorasNecessarias() << " ";

            if(esforco1->estaTerminada()){
                salvo << "T ";
                salvo << esforco1->getDuracao() << " " << endl;
            }else
                salvo << "N " << endl;
        } else{
            AtividadeDePrazoFixo* prazo1 = dynamic_cast<AtividadeDePrazoFixo*>((*atividades)[i]);
            salvo << "P ";
            salvo << prazo1->getNome() << " ";
            salvo << prazo1->getPrazo() << " ";

            if(prazo1->estaTerminada()){
                salvo << "T ";
                salvo << prazo1->getDuracao() << " " << endl;
            }else
                salvo << "N " << endl;
        }

        salvo << (*atividades)[i]->getQuantidadeDeRecursos() << endl;
        Recurso** recursosAtividades = (*atividades)[i]->getRecursos();

        for (int contaRecursos = 0; contaRecursos < (*atividades)[i]->getQuantidadeDeRecursos(); contaRecursos++){
            salvo << recursosAtividades[contaRecursos]->getNome() << " ";
        }

        salvo << endl;
    }

    salvo.close();
}
