#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct No{
 int dado;
 struct No *prox;
};

struct pedido{
    char nomeprod [50];
    char qtdprod [50];
    char valorprod [50] ;
    int vazio, cod;
}log[200];

typedef struct No no;

int tam;
char confere[1];


int verifica_pos( void );
void inicia(no *LISTA);
int menu(void);
void opcao(no *LISTA, int op);
no *criaNo();
void insereFim(no *LISTA);
void insereInicio(no *LISTA);
void exibe(no *LISTA);
void libera(no *LISTA);
void insere (no *LISTA);
no *retiraInicio(no *LISTA);
no *retiraFim(no *LISTA);
no *retira(no *LISTA);
void cadastropedido ( int cod, int pos);
void list();




int main(void)
{
 no *LISTA = (no *) malloc(sizeof(no));
 if(!LISTA){
  printf("Sem memoria disponivel!\n");
  exit(1);
 }else{
 inicia(LISTA);
 int opt;

 do{
  opt=menu();
  opcao(LISTA,opt);
 }while(opt);

 free(LISTA);
 return 0;
 }
}

void inicia(no *LISTA)
{
 LISTA->prox = NULL;
 tam=0;
}

int menu(void)
{
 setlocale(LC_ALL, "Portuguese");
 int opt;

 printf("\n---Escolha a opcao---\n");
 printf("\n1.Cadastrar pedido \n");
 printf("2. Adicionar codigo do pedido no inicio\n");
 printf("3. Escolher onde adicionar\n");
 printf("4. Exibe Lista\n");
 printf("5. Exibir elementos do codigo\n");
 printf("6. Retirar do inicio\n");
 printf("7. Escolher de onde tirar\n");
 printf("8. Zerar Lista\n");
 printf("0. Encerrar programa\n");
 printf("Opcao: ");
 scanf("%d", &opt);
 system("cls");

 return opt;
}

void opcao(no *LISTA, int op)
{
    int codaux,retorno,posicao;

 no *tmp;
 switch(op){
  case 0:
   libera(LISTA);
   break;

  case 1:
  printf("Você selecionou a opção 1 - Cadastrar Pedido");

    posicao=verifica_pos();

 if ( posicao != -1 )
    {
    printf("\nEntre com um codigo para seu cadastro: \n");
    scanf("%d",&codaux);fflush(stdin);

    retorno = verifica_cod( codaux );

    if ( retorno == 1 )
    {
    cadastropedido( codaux, posicao);
    }
    else{
            printf("\nCodigo ja existente ou invalido pressione enter para voltar ao menu principal\n");
            getchar();
            system("cls");
            main();
          }

    }


   break;

  case 2:
   printf("Você selecionou a opção 2 - Por favor, Digite o código do pedido");
   insereInicio(LISTA);
   break;

  case 3:
    printf("Você selecionou a opção 3 - Por favor, Digite o código do pedido e onde ele deve ser inserido ");
    insere(LISTA);
   break;

  case 4:
   printf("Você selecionou a opção 4 - Essa é sua lista de pedidos");
   exibe(LISTA);
   break;

  case 5:
  printf("Você selecionou a opção 5 - Esse é o detalhamento de cada codigo");
  list();
   break;

  case 6:
  printf("Você selecionou a opção 6 - Retiramos o primeiro codigo que vc digitou");
   tmp= retiraInicio(LISTA);
   printf("Retirado: %3d\n\n", tmp->dado);
   system("cls");
   break;

  case 7:
   printf("Você selecionou a opção 7 - ,Você escolhe de onde retirar ");
   tmp= retira(LISTA);
   printf("Retirado: %3d\n\n", tmp->dado);
   system("cls");
   break;

  case 8:
   printf("Fim de expediente? finalmente, limpamos a lista pra você");
   libera(LISTA);
   inicia(LISTA);
   system("cls");
   break;

  default:
   printf("Comando invalido\n\n");
 }
}


int vazia(no *LISTA)
{
 if(LISTA->prox == NULL)
  return 1;
 else
  return 0;
}

no *aloca()
{
 no *novo=(no *) malloc(sizeof(no));
 if(!novo){
  printf("Sem memoria disponivel!\n");
  exit(1);
 }else{
  printf("\nNovo Codigo: ");
  scanf("%d", &novo->dado);
  return novo;
 }
}

void insereInicio(no *LISTA)
{

 no *novo=aloca();
 no *cabeca = LISTA->prox;

 LISTA->prox = novo;
 novo->prox = cabeca;

 tam++;
}
void insereFim(no *LISTA)
{
 no *novo=aloca();
 novo->prox = NULL;

 if(vazia(LISTA))
  LISTA->prox=novo;
 else{
  no *tmp = LISTA->prox;

  while(tmp->prox != NULL)
   tmp = tmp->prox;

  tmp->prox = novo;
 }
 tam++;
}
void insere(no *LISTA)
{
 int pos,
  count;
 printf("Em que posicao, [de 1 ate %d] voce deseja inserir: ", tam);
 scanf("%d", &pos);

 if(pos>0 && pos <= tam){
  if(pos==1)
   insereInicio(LISTA);
  else{
   no *atual = LISTA->prox,
     *anterior=LISTA;
   no *novo=aloca();

   for(count=1 ; count < pos ; count++){
     anterior=atual;
     atual=atual->prox;
   }
   anterior->prox=novo;
   novo->prox = atual;
   tam++;
  }

 }else
  printf("Elemento invalido\n\n");
}



void exibe(no *LISTA)
{
 system("cls");
 if(vazia(LISTA)){
  printf("Lista vazia!\n\n");
  return ;
 }

 no *tmp;
 tmp = LISTA->prox;
 printf("Lista:");
 while( tmp != NULL){
  printf("%5d", tmp->dado);
  tmp = tmp->prox;
 }
 printf("\n        ");
 int count;
 for(count=0 ; count < tam ; count++)
  printf("  ^  ");
 printf("\nOrdem:");
 for(count=0 ; count < tam ; count++)
  printf("%5d", count+1);


 printf("\n\n");
}

void libera(no *LISTA)
{
 if(!vazia(LISTA)){
  no *proxNode,
     *atual;

  atual = LISTA->prox;
  while(atual != NULL){
   proxNode = atual->prox;
   free(atual);
   atual = proxNode;
  }
 }
}


no *retiraInicio(no *LISTA)
{
 if(LISTA->prox == NULL){
  printf("Lista ja esta vazia\n");
  return NULL;
 }else{
  no *tmp = LISTA->prox;
  LISTA->prox = tmp->prox;
  tam--;
  return tmp;
 }

}

no *retiraFim(no *LISTA)
{
 if(LISTA->prox == NULL){
  printf("Lista ja vazia\n\n");
  return NULL;
 }else{
  no *ultimo = LISTA->prox,
    *penultimo = LISTA;

  while(ultimo->prox != NULL){
   penultimo = ultimo;
   ultimo = ultimo->prox;
  }

  penultimo->prox = NULL;
  tam--;
  return ultimo;
 }
}

no *retira(no *LISTA)
{
 int opt,
  count;
 printf("Que posicao, [de 1 ate %d] voce deseja retirar: ", tam);
 scanf("%d", &opt);

 if(opt>0 && opt <= tam){
  if(opt==1)
   return retiraInicio(LISTA);
  else{
   no *atual = LISTA->prox,
     *anterior=LISTA;

   for(count=1 ; count < opt ; count++){
    anterior=atual;
    atual=atual->prox;
   }

  anterior->prox=atual->prox;
  tam--;
  return atual;
  }

 }else{
  printf("Elemento invalido\n\n");
  return NULL;
 }
}
void cadastropedido(int cod,int pos){
    do{
    pos = verifica_pos();
    log[pos].cod = cod;

        printf("Digite os componentes do pedido: ");
        gets(log[pos].nomeprod);
        printf("Digite a quantidade: ");
        gets(log[pos].qtdprod);
        printf(" Digite o valor total do pedido: ");
        gets(log[pos].valorprod);
        log[pos].vazio = 1;
        //printf("\n Pressione enter  2 vezes para voltar ao menu principal");
        //scanf("%c", &confere);
        confere == 1;
        getchar();
    }while(confere==1);
    system("cls");


    }

int verifica_pos( void ){
    int cont = 0;

    while ( cont <= 200 )
    {

        if ( log[cont].vazio == 0 )
            return(cont);

        cont++;

    }

    return(-1);



    return(1);
    }


int verifica_cod( int cod ) // VERIFICADOR DE CÓDIGO
{
      int cont = 0;

    while ( cont <= 200 )
    {
        if ( log[cont].cod == cod )
            return(0);

        cont++;
    }

    return(1);
}
void list(){ // Lista os usuarios cadastrados.
    int i,j;
    for(i=0;i<200;i++){
        if(log[i].cod!=NULL){
            printf("\nCodigo: %d",log[i].cod);
            printf("\nNome Produto: %s",log[i].nomeprod);
            printf("\nQauntos Produtos: %s",log[i].qtdprod);
            printf("\nValor: %s\n\n",log[i].valorprod);
        }

    }
    //printf("\nPressione enter para volta ao menu principal\n\n\n\n");
    //getchar();


}




