# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -pedantic -g -std=c++11

# ****************************************************
# Targets needed to bring the executable up to date

main: main.o Recurso.o Pessoa.o Ferramenta.o Atividade.o AtividadeDeEsforcoFixo.o AtividadeDePrazoFixo.o ErroDeArquivo.o Projeto.o PersistenciaDeProjeto.o
	$(CXX) $(CXXFLAGS) -o main main.o Recurso.o Pessoa.o Ferramenta.o Atividade.o AtividadeDeEsforcoFixo.o AtividadeDePrazoFixo.o ErroDeArquivo.o Projeto.o PersistenciaDeProjeto.o

# The main.o target can be written more simply

main.o: main.cpp Recurso.h Pessoa.h Ferramenta.h Atividade.h AtividadeDeEsforcoFixo.h AtividadeDePrazoFixo.h ErroDeArquivo.h Projeto.h PersistenciaDeProjeto.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Recurso.o: Recurso.h

Pessoa.o: Pessoa.h Recurso.h

Ferramenta.o: Ferramenta.h Recurso.h

Atividade.o: Atividade.h Pessoa.h Recurso.h

AtividadeDeEsforcoFixo.o: AtividadeDeEsforcoFixo.h Atividade.h 
 
AtividadeDePrazoFixo.o: AtividadeDePrazoFixo.h Atividade.h 

ErroDeArquivo.o: ErroDeArquivo.h

Projeto.o: Projeto.h Atividade.h Recurso.h

PersistenciaDeProjeto.o: PersistenciaDeProjeto.h Projeto.h AtividadeDeEsforcoFixo.h AtividadeDePrazoFixo.h Atividade.h Pessoa.h Ferramenta.h Recurso.h ErroDeArquivo.h