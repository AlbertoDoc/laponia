#include <iostream>
#include <iomanip>
#include <string>
#define TAM 12
#define QTD_G 8

using namespace std;

int somadorX(int posicaoX){
  // Essa função é responsavel por informar em que sentido será o ataque frontal,
  // Já que o ataque de um guerreiro na posição de x<5 (parte de cima do tabuleiro)
  // é diferente pra um guerreiro que esta na posição x>6 (parte de baixo do tabuleiro)

  // Se retornar 1 o ataque é de cima pra baixo
  // Se retornar -1 o ataque é de baixo pra cima
  if (posicaoX<5){
    return 1;
  }
  return -1;
}

int somadorY(int direcaoAtq,int posicaoX){
  // Essa função é responsavel por dizer em qual sentido sera feito o ataque
  // Caso direcaoAtq == 1 (esquerda) e posicaoX<5 (parte de cima do tabuleiro) eu tenho que incrementar
  // valores de y para realizar meu ataque. logica parecida se aplica a (direcaoAtq==2)&&(posicaoX>6)
  
  // Caso nenhum dos dois casos acima forem satisfeitos é retornado -1, então precisamos decrementar valores de y
  // para que o ataque obedeça ao que o jogador solicitou
  if (((direcaoAtq == 1) && (posicaoX<5)) || ((direcaoAtq==2)&&(posicaoX>6))){
    return 1;
  }
  return -1;
}

char numeroGuerreiro(string jogador,string nomeJogador1,string nomeJogador2){
  // Verifica se o nome do jogador enviado por parametro é igual ao jogador 1 e retorna as respectivas peças para cada nome
  if (jogador == nomeJogador1){
    return '1';
  }
  return '2';
}


char guerreirOposto(char guerreiro){
  // Verifica o tipo do guerreiro e retorna o oposto a ele
  if (guerreiro =='1'){
    return '2';
  }
  return '1';
}

void criarTabuleiro(char tabuleiro[][TAM]){
  //Função percorre a matriz de tabuleiro e coloca cada caracter no respectivo lugar
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

  // No cout \t eh a mesma coisa que um tab
  // A funcao setw seta o tamanho do campo, mais informacoes no link abaixo
  // http://www.c4learn.com/cplusplus/cpp-setw-setting-field-width/
  
  // No geral essa função percorre a matriz do tabuleiro e printa cada casa dela seguindo uma...
  // ... formatacao para melhor visualizacao do tabuleiro
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
  // Aumenta aleatoriedado da funcao rand
  // segue link com mais explicacoes dessa funcao:
  // https://www.cprogressivo.net/2013/03/Como-gerar-numeros-aleatorios-em-C-com-a-rand-srand-e-seed.html

  if ((rand()%2 +1)==2){
    return jogador2;
  }
  return jogador1;

}

string mudaVez(string jogador,string nomeJogador1,string nomeJogador2){
  // Envia o nome do jogador oposto ao recebido por parametro
  if (jogador == nomeJogador1){
    return nomeJogador2;
  }
  return nomeJogador1;
}

bool validarPosicao(int posicaoX,int posicaoY,char tabuleiro[][12],char guerreiro=' '){

  // Primeiro if verifica se a posicao digitada está dentro do tabuleiro
  // Segundo if verifica se na posicao do tabuleiro digitada tem um campo vazio
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

  // Enquanto a qtd de peças que estão sendo preenchidas(qtd), for diferente da QTD_G*2 (QTD_G= 8)
  // Ou seja enquanto as peças que estão sendo preenchidas forem diferente da quantidade total que deve ter no jogo
  // este loop ficara rodando

  // Atenção QTD_G está definido no inicio do codigo com #define QTD_G 8, ou seja QTD_G SEMPRE TERA VALOR 8 
  while(qtd!=QTD_G*2){
    cout<<"Rodada: "<<jogador<<endl;
    cout<<"Posição do seu guerreiro (X,Y): ";
    // Leitura da posição do guerreiro
    cin>>posicaoX>>virgula>>posicaoY;
    cout<<endl;
    // Este if chama uma funcao que retorna um booleano, esta funcao tem como objetivo validar se a posicao escolhida
    // é valida
    if (validarPosicao(posicaoX,posicaoY,tabuleiro)){
      // Coloca o numero 1 ou 2 dependendo do retorno da funcao numeroGuerreiro que leva em consideracao o turno do jogador
      tabuleiro[posicaoX][posicaoY] = numeroGuerreiro(jogador,nomeJogador1,nomeJogador2);
      // Troca o valor da variavel jogador (esta variavel guarda o nome do jogador que tem o turno)
      jogador = mudaVez(jogador,nomeJogador1,nomeJogador2);
      // Aumenta a quantidade de peças colocada no tabuleiro
      qtd++;
      // Printa o tabuleiro com a peça ja colocada
      printarTabuleiro(tabuleiro);
    }
    else {
      // Entra aqui caso for digitada uma posição invalida
      cout<<"--------------------------------------------------------------------------------------"<<endl;
      // Este if verifica se na posicao digitada no tabuleiro ja tem uma peça, independente de qual time ela seja
      if (tabuleiro[posicaoX][posicaoY]=='1' || tabuleiro[posicaoX][posicaoY] == '2'){
        cout<<"--> Posicao Ocupada"<<endl;
      }
      else{
        // Quando entrar aqui é porque foi digitada uma casa dentro do tabuleiro mas ela foi a borda ou o rio
        cout<<"--> Posicao Invalida"<<endl;
      }
    }
    cout<<endl;
  }

}

bool movimento(int origemX,int origemY,int destinoX,int destinoY,char tabuleiro[][12]){
  // Esse if verifica se as coordenadas de destino sao validas
  // (abs(origemX-destinoX) == 1 && abs(origemY-destinoY) == 1) impede que sejam feitas movimentações em diagonal
  // abs(origemX-destinoX)>1 || abs(origemY-destinoY)>1 impede que sejam feitas movimentações com mais de uma casa de distancia
  // tabuleiro[destinoX][destinoY]!=' ' verifica se na posicao escolhida é uma casa vazia
  if((abs(origemX-destinoX) == 1 && abs(origemY-destinoY) == 1) || (abs(origemX-destinoX)>1 || abs(origemY-destinoY)>1 || tabuleiro[destinoX][destinoY]!=' ')){
    return false;
  }
  return true;
}

bool ataqueDiagonal(int contY,int contX,int posicaoAtqX,int posicaoAtqY,char guerreiro,char tabuleiro[][12]){
  // Chama a função que retorna qual é o tipo do guerreiro do adversario
  char inimigo = guerreirOposto(guerreiro);
  bool interrompido = false;
  cout<<"--------------------------------------------------------------------------------------"<<endl;
  // Verificação parecida com a função de ataque frontal, com a diferença de que agr a coordenada
  // y deve ser levada em conta, já que o tabuleiro pode ser excedido lateralmente em um ataque diagonal
  while(posicaoAtqX<(TAM-1) && posicaoAtqX>0 && posicaoAtqY<(TAM-1) && !interrompido){
    // Verifica se na posição do tabuleiro com as coordenadas de ataque tem um guerreiro inimigo
    if(tabuleiro[posicaoAtqX][posicaoAtqY]==inimigo){
      // Caso tenha esse guerreiro é eliminado
      tabuleiro[posicaoAtqX][posicaoAtqY] = ' ';
      // É printado na tela a jogada realizada
      cout<<"--> Guerreiro Da Posicao "<<posicaoAtqX<<","<<posicaoAtqY<<" Morreu!"<<endl;
      // Retornado true pois o ataque foi bem sucedido
      return true;
    }
    // Verifica se na posição de ataque no tabuleiro tem um aliado
    if(tabuleiro[posicaoAtqX][posicaoAtqY]==guerreiro){
      // Caso tenha é informado o acontecido
      cout<<"--> Guerreiro Aliado No Caminho"<<endl;
      // A variavel interrompido é setada como true para que o while nao continue avançando
      interrompido = true;
    }

    // Incrementada as variaveis de ataque para que seja verificada para as posições seguintes
    posicaoAtqX+=contX;
    posicaoAtqY+=contY;
  }

  // Retornado falso caso o ataque nao seja bem sucedido
  return false;
}

bool ataqueFrontal(int contX,int posicaoAtqX,int posicaoY,char guerreiro,char tabuleiro[][12]){
  // Chama a função que retorna qual é o tipo do guerreiro oposto
  char inimigo = guerreirOposto(guerreiro);
  bool interrompido = false;
  cout<<"--------------------------------------------------------------------------------------"<<endl;
  // Enquanto a posição do ataque não exceder o tabuleiro com a coordenada x esse while esta rodando
  while (posicaoAtqX<(TAM-1) && posicaoAtqX>0 && !interrompido){
    // Esse if verifica se na posição de ataque no tabuleiro tem uma peça inimiga
    if (tabuleiro[posicaoAtqX][posicaoY]==inimigo){
      // Caso verdade remove a peça inimiga daquela posição
      tabuleiro[posicaoAtqX][posicaoY] = ' ';
      // Imprime na tela a jogada que foi realizada
      cout<<"--> Guerreiro Da Posicao "<<posicaoAtqX<<","<<posicaoY<<" Morreu!"<<endl;
      // Retorna verdade encerrando o ataque frontal
      return true;
    }
    if(tabuleiro[posicaoAtqX][posicaoY]==guerreiro){
      // Se na posição de ataque mp tabuleiro tiver um guerreiro (aliado)
      // É imprimido a frase informando que há um guerreiro aliado no caminho
      cout<<"--> Guerreiro Aliado No Caminho"<<endl;
      // A flag interrompido é alterado para true encerrando o ataque frontal
      // pois perceba que no while que faz essas verificações a variavel interrompido
      // é levada em consideração
      interrompido = true;
    }
    // Incrementação da posição de ataque para que continue sendo verificado para as casas seguintes
    posicaoAtqX+=contX;
  }

  // Caso o ataque não tenha sucesso é retornado false
  return false;
}

void ataque(int posicaoX,int posicaoY,char tabuleiro[][12],char guerreiro,int qtd_jogador[]){

  // Chama a função que lida em que sentido será feita o ataque
  int contX=somadorX(posicaoX);
  int posicaoAtqX;
  bool atq;

  // Coloca o valor da posição no tabuleiro + sentido do ataque na variavel posicaoAtqX
  posicaoAtqX = posicaoX+contX;
  // Verifica se o guerreiro é do jogador1 e chama a funcao que lida com o ataque frontal
  if (guerreiro == '1'){
    // É chamada a função que lida com o ataque frontal e é retornado para a variavel
    // atq true para ataque bem sucedido e false para ataque falho
    atq = ataqueFrontal(contX,posicaoAtqX,posicaoY,guerreiro,tabuleiro);
  }
  else{
    // Entra aqui caso o guerreiro for '2'
    // Variavel abaixo irá armazenar a direcao do atq | Esquerda: 1 | Direita: 2
    int direcaoAtq;
    cout<<"Ataque Diagonal (Esquerda: 1 | Direita: 2): ";
    // Le se o ataque a ser feito é pra esquerda ou direita
    cin>>direcaoAtq;

    // Guardada na variavel contY o sentido em que sera feito o ataque (agora em relação a coordenada y do tabuleiro)
    int contY = somadorY(direcaoAtq,posicaoX);
    // Coloca o valor da posição no tabuleiro + sentido do ataque na variavel posicaoAtqY
    int posicaoAtqY = posicaoY+contY;
    // Chama a função que lida com o ataque diagonal e retorna para atq true se foi bem sucedida e false para o contrario
    atq = ataqueDiagonal(contY,contX,posicaoAtqX,posicaoAtqY,guerreiro,tabuleiro);
  }
  if (atq){
    // Caso ataque seja bem sucedido é informado na tela
    cout<<"--> Ataque Realizado com Sucesso!"<<endl;
    // Calcula em que time foi retirado uma peça e tira 1 unidade no array que guarda
    // a quantidade de guerreiros em cada time
    qtd_jogador[(int)(guerreirOposto(guerreiro)) - '0' - 1]--;
  }
  else{
    // Caso ataque nao seja bem sucedido é informado na tela
    cout<<"--> Ataque Falhou!"<<endl;
  }

}


void realizarJogada(string &jogador,string nomeJogador1,string nomeJogador2,char tabuleiro[][12],int qtd_jogador[]){
  int posicaoX,posicaoY,jogada,destinoX,destinoY;
  // Pega qual é o guerreiro baseado no turno e no nome dos jogadores
  char guerreiro = numeroGuerreiro(jogador,nomeJogador1,nomeJogador2);
  char virgula;

  cout<<"Rodada: "<<jogador<<endl;
  cout<<"Escolha seu guerreiro (X,Y): ";
  // Leitura das casas onde esta o guerreiro que o jogador quer movimentar
  cin>>posicaoX>>virgula>>posicaoY;
  // Limpa o input buffer para nao ocorrer erros inesperados
  cin.ignore();
  // Esse if chama a função que valida se a posicao escolhida é valida, esta funcao retorna um booleano
  if (validarPosicao(posicaoX,posicaoY,tabuleiro,guerreiro)){
    cout<<"Escolher jogada (movimento: 1 | ataque: 2): ";
    // Le se o jogador quer atacar ou movimentar
    cin>>jogada;
    // Limpa o input buffer para nao ocorrer erros inesperados
    cin.ignore();
    // Verifica se o jogador escolheu movimentar
    if (jogada==1){
      cout<<"Posicao que deseja ir (X,Y): ";
      // Leitura da coordenadas da casa que o jogador quer colocar a peça
      cin>>destinoX>>virgula>>destinoY;
      // Limpa o input buffer para nao ocorrer erros inesperados
      cin.ignore();
      cout<<"--------------------------------------------------------------------------------------"<<endl;
      if (movimento(posicaoX,posicaoY,destinoX,destinoY,tabuleiro)){
        // Colocacao da peça na outra casa e limpa a casa antiga dela
        tabuleiro[destinoX][destinoY]=tabuleiro[posicaoX][posicaoY];
        tabuleiro[posicaoX][posicaoY]=' ';
        // Printa a movimentação feita
        cout<<"---> Guerreiro "<<guerreiro<<": ("<<posicaoX<<","<<posicaoY<<") ->"<<" ("<<destinoX<<","<<destinoY<<")\n"<<endl;
        // Troca o turno do jogador
        jogador = mudaVez(jogador,nomeJogador1,nomeJogador2);
      }
      else{
        // Caso a funcao movimento retorne false ele printa essa mensagem que a casa é invalida
        cout<<"---> Posicao Invalida - Tente Novamente"<<endl;
      }
    }
    else if (jogada==2){
      // Entra aqui caso a escolha do jogador for ataque
      // Chama a funcao que lida com o ataque
      ataque(posicaoX,posicaoY,tabuleiro,guerreiro,qtd_jogador);
      // Troca o turno do jogador
      jogador = mudaVez(jogador,nomeJogador1,nomeJogador2);
    }
  }
  else{
    // Caso nao seja selecionado um guerreiro valido ele printa essa mensagem na tela
    cout<<"--------------------------------------------------------------------------------------"<<endl;
    cout<<"---> Guerreiro Invalido - Tente Novamente"<<endl;
  }

}

void laponiaGame(char tabuleiro[][12],string nomeJogador1,string nomeJogador2,string jogador){
  // Esta variavel guarda a quantidade de peças dos dois time, lembrar que QTD_G é 8
  int qtd_jogador[]={QTD_G,QTD_G};
  // Variavel que guarda a posição digitada em cada rodada
  int posicaoX,posicaoY;
  // Variavel que serve somente para guardar a virgula que é digitada na entrada das posicoes
  char virgula;

  // Enquanto os dois times tiverem peças. Caso algum time atinja 0 peças esse while para de rodar, pois o array qtd_jogador guarda
  // a quantidade de peças dos dois times
  while (qtd_jogador[0]!=0 && qtd_jogador[1]!=0){
    // Imprime o nome dos jogadores em cada rodada (requerido pelo professor)
    cout<<"Jogadores: "<<nomeJogador1<<"/"<<nomeJogador2<<endl<<endl;

    // Mostra a situação do tabuleiro para o jogador decidir sua jogada
    printarTabuleiro(tabuleiro);
    // Chama a funcao responsavel por realizar a jogada
    realizarJogada(jogador,nomeJogador1,nomeJogador2,tabuleiro,qtd_jogador);
  }
  // Caso o while pare de rodar é porque um dos dois times nao tem mais guerreiros
  cout<<"--------------------------------------Fim de Jogo---------------------------------------"<<endl;
  // Nas linhas de baixo há uma verificação para printar o nome do jogador vencedor
  cout<<"GANHADOR: ";
  if (qtd_jogador[0]==0){
    cout<<nomeJogador2<<endl;
  }
  else{
    cout<<nomeJogador2<<endl;
  }

}



int main(){
  string nomeJogador1,nomeJogador2,jogador;
  int start;
  char tabuleiro[TAM][TAM];
  // Chama a função responsavel por criar o tabuleiro
  criarTabuleiro(tabuleiro);
  cout<<"---------------------------------Batalhas da Lapônia------------------------------------"<<endl<<endl;
  cout<<"Jogador 1: ";
  
  //Leitura dos nomes dos jogadores
  cin>>nomeJogador1;
  cout<<"Jogador 2: ";
  cin>>nomeJogador2;
  cout<<endl;
  
  // Chamada da funcao para sortear o jogador 
  jogador = sortearJogador(nomeJogador1,nomeJogador2);
  cout<<"Sorteio realizado: "<<jogador<<endl;
  cout<<"-------------------------------Preenchendo o Tabuleiro----------------------------------"<<endl<<endl;
  // Mostra o tabuleiro vazio antes do preenchimento
  printarTabuleiro(tabuleiro);
  preencherTabuleiro(jogador,nomeJogador1,nomeJogador2,tabuleiro);
  cout<<"----------------------------------------------------------------------------------------"<<endl<<endl;
  cout<<"Iniciar (start: 1 | exit: 0): ";
  // Lê se o jogadores querem iniciar o jogo ou sair dele
  cin>>start;
  // Esse cin.ignore limpa o input buffer para nao ocorrer erros inesperados
  cin.ignore();
  cout<<endl;
  // Se o jogador digitou 1 para inciar o jogo vai ser chamado o metodo que cuida da logica de movimentacao, ataque,
  // controle da quantidade de peças e etc.
  if (start){
    laponiaGame(tabuleiro,nomeJogador1,nomeJogador2,jogador);
  }
  // Caso start = 0 o programa é encerrado
  cout<<endl;
}
