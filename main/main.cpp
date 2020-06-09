#include <iostream>
#include <iomanip>
#include <string>
#define TAM 12
#define QTD_G 8

using namespace std;

int somadorX(int posicaoX){
  if (posicaoX<5){
    return 1;
  }
  return -1;
}

int somadorY(int direcaoAtq,int posicaoX){
  if (((direcaoAtq == 1) && (posicaoX<5)) || ((direcaoAtq==2)&&(posicaoX>6))){
    return 1;
  }
  return -1;
}

char numeroGuerreiro(string jogador,string nomeJogador1,string nomeJogador2){
  if (jogador == nomeJogador1){
    return '1';
  }
  return '2';
}


char guerreirOposto(char guerreiro){
  if (guerreiro =='1'){
    return '2';
  }
  return '1';
}

void criarTabuleiro(char tabuleiro[][TAM]){
  for (int i=0;i<TAM;i++){
    for (int j=0;j<TAM;j++){
      if (i==0 || j==0 || i==(TAM-1) || j==(TAM-1)){
        tabuleiro[i][j] = '*';
      }
      else if (i==5 || i==6){
        tabuleiro[i][j] = '~';
      }
      else{
        tabuleiro[i][j] = ' ';
      }
    }
  }
}


void printarTabuleiro(char tabuleiro[][12]){

  for (int i=0;i<TAM;i++){
    cout<<"\t\t"<<setw(2)<<i<<"  ";
    for (int j=0;j<TAM;j++){
      cout<<setw(3)<<tabuleiro[i][j]<<' ';
    }
    cout<<endl<<endl;
  }
  cout<<"\t\t   ";
  for (int i=0;i<TAM;i++){
    cout<<setw(4)<<i;
  }
  cout<<endl;
}

string sortearJogador(string jogador1,string jogador2){
  srand(time(NULL));

  if ((rand()%2 +1)==2){
    return jogador2;
  }
  return jogador1;

}



string mudaVez(string jogador,string nomeJogador1,string nomeJogador2){
  if (jogador == nomeJogador1){
    return nomeJogador2;
  }
  return nomeJogador1;
}

bool validarPosicao(int posicaoX,int posicaoY,char tabuleiro[][12],char guerreiro=' '){

  if (posicaoX>0 && posicaoX<TAM && posicaoY>0 && posicaoY<TAM){
    if (tabuleiro[posicaoX][posicaoY]==guerreiro){
      return true;
    }
  }
  return false;

}



void preencherTabuleiro(string jogador,string nomeJogador1,string nomeJogador2,char tabuleiro[][12]){
  int qtd = 0;
  int posicaoX,posicaoY;
  char virgula;

  while(qtd!=QTD_G*2){
    cout<<"Rodada: "<<jogador<<endl;
    cout<<"Posição do seu guerreiro (X,Y): ";
    cin>>posicaoX>>virgula>>posicaoY;
    cout<<endl;
    if (validarPosicao(posicaoX,posicaoY,tabuleiro)){
      tabuleiro[posicaoX][posicaoY] = numeroGuerreiro(jogador,nomeJogador1,nomeJogador2);
      jogador = mudaVez(jogador,nomeJogador1,nomeJogador2);
      qtd++;
      printarTabuleiro(tabuleiro);
    }
    else {
      cout<<"--------------------------------------------------------------------------------------"<<endl;
      if (tabuleiro[posicaoX][posicaoY]=='1' || tabuleiro[posicaoX][posicaoY] == '2'){
        cout<<"--> Posicao Ocupada"<<endl;
      }
      else{
        cout<<"--> Posicao Invalida"<<endl;
      }
    }
    cout<<endl;

  }


}

bool movimento(int origemX,int origemY,int destinoX,int destinoY,char tabuleiro[][12]){
  //if ((abs(origemX-destinoX)>=1 && abs(origemY-destinoY)>=1) || tabuleiro[destinoX][destinoY]!=' '){
    //return false;
  //}
  if((abs(origemX-destinoX) == 1 && abs(origemY-destinoY) == 1) || (abs(origemX-destinoX)>1 || abs(origemY-destinoY)>1 || tabuleiro[destinoX][destinoY]!=' ')){
    return false;
  }
  return true;
}

bool ataqueDiagonal(int contY,int contX,int posicaoAtqX,int posicaoAtqY,char guerreiro,char tabuleiro[][12]){
  char inimigo = guerreirOposto(guerreiro);
  bool interrompido = false;
  cout<<"--------------------------------------------------------------------------------------"<<endl;
  while(posicaoAtqX<(TAM-1) && posicaoAtqX>0 && posicaoAtqY<(TAM-1) && !interrompido){
    if(tabuleiro[posicaoAtqX][posicaoAtqY]==inimigo){
      tabuleiro[posicaoAtqX][posicaoAtqY] = ' ';
      cout<<"--> Guerreiro Da Posicao "<<posicaoAtqX<<","<<posicaoAtqY<<" Morreu!"<<endl;
      return true;
    }
    if(tabuleiro[posicaoAtqX][posicaoAtqY]==guerreiro){
      cout<<"--> Guerreiro Aliado No Caminho"<<endl;
      interrompido = true;
    }
    posicaoAtqX+=contX;
    posicaoAtqY+=contY;
  }

  return false;
}

bool ataqueFrontal(int contX,int posicaoAtqX,int posicaoY,char guerreiro,char tabuleiro[][12]){
  char inimigo = guerreirOposto(guerreiro);
  bool interrompido = false;
  cout<<"--------------------------------------------------------------------------------------"<<endl;
  while (posicaoAtqX<(TAM-1) && posicaoAtqX>0 && !interrompido){
    if (tabuleiro[posicaoAtqX][posicaoY]==inimigo){
      tabuleiro[posicaoAtqX][posicaoY] = ' ';
      cout<<"--> Guerreiro Da Posicao "<<posicaoAtqX<<","<<posicaoY<<" Morreu!"<<endl;
      return true;

    }
    if(tabuleiro[posicaoAtqX][posicaoY]==guerreiro){
      cout<<"--> Guerreiro Aliado No Caminho"<<endl;
      interrompido = true;
    }
    posicaoAtqX+=contX;
  }

  return false;
}

void ataque(int posicaoX,int posicaoY,char tabuleiro[][12],char guerreiro,int qtd_jogador[]){

  int contX=somadorX(posicaoX);
  int posicaoAtqX;
  bool atq;

  posicaoAtqX = posicaoX+contX;
  if (guerreiro == '1'){
    atq = ataqueFrontal(contX,posicaoAtqX,posicaoY,guerreiro,tabuleiro);
  }
  else{
    int direcaoAtq;
    cout<<"Ataque Diagonal (Esquerda: 1 | Direita: 2): ";
    cin>>direcaoAtq;
    int contY = somadorY(direcaoAtq,posicaoX);
    int posicaoAtqY = posicaoY+contY;
    atq = ataqueDiagonal(contY,contX,posicaoAtqX,posicaoAtqY,guerreiro,tabuleiro);
  }
  if (atq){
    cout<<"--> Ataque Realizado com Sucesso!"<<endl;
    qtd_jogador[(int)(guerreirOposto(guerreiro)) - '0' - 1]--;
  }
  else{
    cout<<"--> Ataque Falhou!"<<endl;
  }

}


void realizarJogada(string &jogador,string nomeJogador1,string nomeJogador2,char tabuleiro[][12],int qtd_jogador[]){
  int posicaoX,posicaoY,jogada,destinoX,destinoY;
  char guerreiro = numeroGuerreiro(jogador,nomeJogador1,nomeJogador2);
  char virgula;

  cout<<"Rodada: "<<jogador<<endl;
  cout<<"Escolha seu guerreiro (X,Y): ";
  cin>>posicaoX>>virgula>>posicaoY;
  cin.ignore();
  if (validarPosicao(posicaoX,posicaoY,tabuleiro,guerreiro)){
    cout<<"Escolher jogada (movimento: 1 | ataque: 2): ";
    cin>>jogada;
    cin.ignore();
    if (jogada==1){
      cout<<"Posicao que deseja ir (X,Y): ";
      cin>>destinoX>>virgula>>destinoY;
      cin.ignore();
      cout<<"--------------------------------------------------------------------------------------"<<endl;
      if (movimento(posicaoX,posicaoY,destinoX,destinoY,tabuleiro)){
        tabuleiro[destinoX][destinoY]=tabuleiro[posicaoX][posicaoY];
        tabuleiro[posicaoX][posicaoY]=' ';
        cout<<"---> Guerreiro "<<guerreiro<<": ("<<posicaoX<<","<<posicaoY<<") ->"<<" ("<<destinoX<<","<<destinoY<<")\n"<<endl;
        jogador = mudaVez(jogador,nomeJogador1,nomeJogador2);
      }
      else{
        cout<<"---> Posicao Invalida - Tente Novamente"<<endl;
      }
    }
    else if (jogada==2){
      ataque(posicaoX,posicaoY,tabuleiro,guerreiro,qtd_jogador);
      jogador = mudaVez(jogador,nomeJogador1,nomeJogador2);
    }
  }
  else{
    cout<<"--------------------------------------------------------------------------------------"<<endl;
    cout<<"---> Guerreiro Invalido - Tente Novamente"<<endl;
  }

}

void laponiaGame(char tabuleiro[][12],string nomeJogador1,string nomeJogador2,string jogador){
  int qtd_jogador[]={QTD_G,QTD_G};
  int posicaoX,posicaoY;
  char virgula;
  while (qtd_jogador[0]!=0 && qtd_jogador[1]!=0){

    printarTabuleiro(tabuleiro);
    realizarJogada(jogador,nomeJogador1,nomeJogador2,tabuleiro,qtd_jogador);
  }
  cout<<"--------------------------------------Fim de Jogo---------------------------------------"<<endl;
  cout<<"GANHADOR: ";
  if (qtd_jogador[0]==0){
    cout<<nomeJogador2<<endl;
  }
  else{
    cout<<nomeJogador2<<endl;
  }


}
//
// bool sortearJogador(int numeros[], int qtdNumeros, int limite){
//     int qtd0 = 0;
//     int qtd1 = 0;
//
//     srand(time(NULL));
//
//     for(int i=0;i<qtdNumeros;i++){
//         numeros[i] = rand() % limite;
//     }
//
//     for(int i=0;i<qtdNumeros;i++){
//         if(numeros[i] == 0){
//             qtd0++;
//         } else {
//             qtd1++;
//         }
//     }
//
//     if(qtd0 > qtd1){
//         return true; //Jogador 1 começa
//     } else {
//         return false; //Jogador 2 começa
//     }
// }





int main(){
  string nomeJogador1,nomeJogador2,jogador;
  int start;
  char tabuleiro[TAM][TAM];
  criarTabuleiro(tabuleiro);
  cout<<"---------------------------------Batalhas da Lapônia------------------------------------"<<endl<<endl;
  cout<<"Jogador 1: ";
  cin>>nomeJogador1;
  cout<<"Jogador 2: ";
  cin>>nomeJogador2;
  cout<<endl;
  jogador = sortearJogador(nomeJogador1,nomeJogador2);
  cout<<"Sorteio realizado: "<<jogador<<endl;
  cout<<"-------------------------------Preenchendo o Tabuleiro----------------------------------"<<endl<<endl;
  printarTabuleiro(tabuleiro);
  preencherTabuleiro(jogador,nomeJogador1,nomeJogador2,tabuleiro);
  cout<<"----------------------------------------------------------------------------------------"<<endl<<endl;
  cout<<"Iniciar (start: 1 | exit: 0): ";
  cin>>start;
  cin.ignore();
  cout<<endl;
  if (start){
    laponiaGame(tabuleiro,nomeJogador1,nomeJogador2,jogador);
  }
  cout<<endl;



}
