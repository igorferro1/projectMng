/***************************************************************/
/**                                                           **/
/**   Igor Nunes Ferro e Thomaz Assaf Pougy                   **/
/**   NUSPS: 10774138 e 9795907                               **/
/**   Exercicio-Programa 01                                   **/
/**   Professor: Pedro Luiz Pizzigati Correa                  **/
/**   Turma: T6T                                              **/
/**                                                           **/
/***************************************************************/
#include <iostream>
#include <string>
#include "Pessoa.h"
#include "Atividade.h"
#include "Projeto.h"
#include "Recurso.h"
#include "Ferramenta.h"
#include "PersistenciaDeProjeto.h"
#include "ErroDeArquivo.h"

#include "AtividadeDeEsforcoFixo.h"
#include "AtividadeDePrazoFixo.h"

using namespace std;

int main() {
    try{
      Projeto* projeMain;
      PersistenciaDeProjeto* persistencia = new PersistenciaDeProjeto();

      //inicio: carregar projeto ou iniciar novo
      char carregarNovo;
      cout << "Deseja carregar um novo projeto (s/n)? ";
      cin >> carregarNovo;

      if (carregarNovo == 's'){
      string nomeArquivo;
      cout << "Digite o nome do arquivo: ";
      cin >> nomeArquivo;
      projeMain = persistencia->carregar(nomeArquivo);
      }

      else{
      string nomeProjeto;
      cout << "Digite o nome do projeto: ";
      cin >> nomeProjeto;
      projeMain = new Projeto(nomeProjeto);
      }


      while (1) {
        int opcao;
        cout << "1 - Adicionar recurso" << endl;
        cout << "2 - Adicionar atividade" << endl;
        cout << "3 - Terminar atividade" << endl;
        cout << "4 - Imprimir projeto" << endl;
        cout << "5 - Definir valor por hora padrao" << endl;
        cout << "6 - Salvar" << endl;
        cout << "0 - Sair" << endl;
        cout << "Escolha a opcao: ";
        cin >> opcao;


        //Opcao 1 escolhida - Adicionar recurso
        if (opcao == 1) {
            char tipoDeRecurso;             //ele confere qual tipo esta tentando adicionar
            cout << "Ferramenta (f) ou pessoa (p): ";
            cin >> tipoDeRecurso;

            if (tipoDeRecurso == 'f'){
                string nomeDaFerramenta;                    //se for ferramenta, pega nome, custo diario, cria e adiciona no projeto
                double custoDiario;
                cout << "Nome: ";
                cin >> nomeDaFerramenta;
                cout << "Custo diario: ";
                cin >> custoDiario;

                Ferramenta* f1 = new Ferramenta(nomeDaFerramenta, custoDiario);
                projeMain->adicionar(f1);
            } else {
                string nomeDaPessoa;            //caso seja pessoa, ira pegar nome e horas diarias, depois verifica se o usuario quer utilizar valor padrao ou nao
                int horasDiarias;
                cout << "Nome: ";
                cin >> nomeDaPessoa;
                cout << "Horas diarias: ";
                cin >> horasDiarias;

                char haValorPadrao;
                cout << "Valor por hora padrao (s/n)? ";
                cin >> haValorPadrao;

                if (haValorPadrao == 'n'){          //caso nao queira, pega um valor por hora inserido, cria a pessoa e adiciona no projeto
                    double valorPorHoraPessoa;
                    cout << "Valor por hora (em R$): ";
                    cin >> valorPorHoraPessoa;

                    Pessoa* p1 = new Pessoa(nomeDaPessoa, valorPorHoraPessoa, horasDiarias);
                    projeMain->adicionar(p1);
                } else {                                                  //caso queira, cria a pessoa com o padrao e adiciona no projeto
                    Pessoa* p1 = new Pessoa(nomeDaPessoa, horasDiarias);
                    projeMain->adicionar(p1);
                }
            }
        }

        //Opcao 2 escolhida - Adicionar atividade
        if (opcao == 2) {
            string nomeAtividade;       //pergunta o nome e o tipo da atividade
            char tipoAtividade;
          cout << "Nome: ";
          cin >> nomeAtividade;
          cout << "Prazo fixo (p) ou trabalho fixo (t)? ";
          cin >> tipoAtividade;

          //dependendo do tipo, ira pedir ou dias, ou horas necessarias e adicionara a atividade no projeto
          if (tipoAtividade == 'p'){
            int prazoFixo;
            cout << "Dias necessarios: ";
            cin >> prazoFixo;
            AtividadeDePrazoFixo* ativi1 = new AtividadeDePrazoFixo(nomeAtividade, prazoFixo);
            projeMain->adicionar(ativi1);
          } else {
            int horasNecessarias;
            cout << "Horas necessarias: ";
            cin >> horasNecessarias;

            AtividadeDeEsforcoFixo* ativi1 = new AtividadeDeEsforcoFixo(nomeAtividade, horasNecessarias);
            projeMain->adicionar(ativi1);
          }
            char novoRecurso;           //ele pergunta se quer adicionar algum recurso na atividade, caso sim,
            cout << "Deseja adicionar um recurso (s/n)? ";
            cin >> novoRecurso;

            while (novoRecurso != 'n') {

              if (novoRecurso == 's') {                      //aqui ele faz aquela verificacao se a pessoa quer adicionar um recurso novo e se nao tem lixo na variavel
                list<Recurso*>* listaRecursos = projeMain->getRecursos();   //o if foi necessario para caso a pessoa digitar outra letra alem de s ou n, ai nao roda caso seja diferente de s
                                                            //ele pega a lista e cria um iterador pra poder varrer a lista, printando os dados de cada elemento

                list<Recurso*>::iterator i = listaRecursos->begin();
                int contadorDeRecursos = 1;             //ele gera tmb um contador, para fazer o indice da lista e tmb servira mais a frente

                while (i != listaRecursos->end()){

                  cout << contadorDeRecursos << " - ";

                  Pessoa* p = dynamic_cast<Pessoa*>((*i));

                  if (p != nullptr){
                    cout << "Pessoa: " << p->getNome() << " - R$" << p->getCusto(1) << " - " << p->getHorasDiarias() << "h por dia" << endl;
                  }

                  else{
                    Ferramenta* f = dynamic_cast<Ferramenta*>((*i));
                    cout << "Ferramenta: " << f->getNome() << " - R$" << f->getCustoDiario() << endl;
                  }
                  contadorDeRecursos++;
                  i++;
                }

                cout << "Escolha uma pessoa ou 0 para cancelar: ";
                cin >> opcao; // reutilizando a variavel para ocupar menos memoria, em seguida ela sera lida novamente, entao nao ha problema

                if (opcao != 0){
                    i = listaRecursos->begin();
                    contadorDeRecursos = 1;                 //o contador vai servir para selecionar a opcao da lista, visto que ela nao tem um indice como o vetor
                    while (contadorDeRecursos != opcao){
                        i++;
                        contadorDeRecursos++;               //ele sera somado e o iterador sera passado ao proximo elemento, tudo enquanto o contador for diferente da opcao
                    }
                    projeMain->getAtividades()->back()->adicionar((*i));        //quando chegar na opcao, adicionara o recurso na atividade
                }
              }      //fim do if do novo recurso == 's'

              cout << "Deseja adicionar um novo recurso (s/n)?";
              cin >> novoRecurso;
            }         // fim do while != 'n'
            opcao = 2;                    //voltando a variavel ao estado original para nao dar pau nos proximos ifs
        } // fim do if 2

        if (opcao == 3) {       //caso a opcao seja 3, ele listara todas as atividades pelo for e pedira uma atividade para terminar
          for (unsigned int i = 0; i < projeMain->getAtividades()->size(); i++){
            cout << i+1 << projeMain->getAtividades()->at(i)->getNome() << endl;
          }
          int escolha;
          cout << "Escolha uma atividade ou 0 para cancelar: ";
          cin >> escolha;

          if (escolha != 0){        //caso ele entre com 0, ira voltar ao menu

            if (projeMain->getAtividades()->at(escolha - 1)->estaTerminada())           //caso a atividade escolhida esteja ja terminada, printara uma msg e voltara ao menu
                cout << "Atividade ja terminada" << endl;

            else {
                int duracaoReal;                //caso contrario, pedira a duracao real e entao terminara a atividade escolhida
                cout << "Duracao real: ";
                cin >> duracaoReal;
                projeMain->getAtividades()->at(escolha - 1)->terminar(duracaoReal);
            }
          }
        }

        if (opcao == 4){
            projeMain->imprimir();
        }

        if (opcao == 5){            //aqui ele printara o valor padrao atual e pedira por um novo
            double novoValorPadrao;
            cout << "Valor atual: R$" << Pessoa::getValorPorHoraPadrao() << endl;
            cout << "Novo valor: ";
            cin >> novoValorPadrao;

            Pessoa::setValorPorHoraPadrao(novoValorPadrao);
        }

        if (opcao == 6){            //caso escolhida a opcao, ele pedira o nome do arquivo em que se deseja salvar e salvara la
            string nomeDoArquivo;
            cout << "Nome do arquivo: ";
            cin >> nomeDoArquivo;

            persistencia->salvar(projeMain, nomeDoArquivo);
        }

        if (opcao == 0) {
          break;
        }                   //da break quando eh para parar

      }                    // fim do while 1
    }   //fim do try

    catch(ErroDeArquivo *e){
        cout << e->what();
        delete e;
    }

    catch(logic_error *e){
        cout << e->what();
        delete e;
    }

    catch(invalid_argument *e){
        cout << e->what();
        delete e;
    }

    catch(overflow_error *e){
        cout << e->what();
        delete e;
    }

    return 0;
}
