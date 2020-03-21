# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CXX = g++
CXXFLAGS = -Wall -pedantic -g -std=c++11

# ****************************************************
# Targets needed to bring the executable up to date

main: main.o Pessoa.o Atividade.o Projeto.o
	$(CXX) $(CXXFLAGS) -o main main.o Pessoa.o Atividade.o Projeto.o

# The main.o target can be written more simply

main.o: main.cpp Pessoa.h Atividade.h Projeto.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Pessoa.o: Pessoa.h

Atividade.o: Atividade.h Pessoa.h

Projeto.o: Projeto.h Atividade.h Pessoa.h
