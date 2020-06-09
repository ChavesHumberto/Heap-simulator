#include <stdio.h>
#include <stdlib.h>

 struct enderecos {
    char var;
    int posicao;
    int tamanho;
    int conRef;
   struct enderecos *prox;
};
struct variaveis{
    char id;
    struct enderecos *ancora;//ponteiro p lista de espacos ativos
    struct variaveis *prox;
};



void imprimeVar(struct variaveis *livres){
    while(livres != NULL){
        printf("\nVAR: %c  T: %d",livres->id,livres->ancora->tamanho);
        livres=livres->prox;
    };
};

void addVarAtv(char id,struct enderecos *espAtivos,struct variaveis **varAtivas){
    struct variaveis *aux;
    aux = (struct variaveis*) malloc(sizeof(struct variaveis));
    aux->id = id;
    aux->ancora = espAtivos;
    aux->prox = *varAtivas;
    *varAtivas = aux;
};

//cria uma celula na lista de variaveis ativas sempre na frente
struct enderecos *incluiVar(int mPos,int tam,struct enderecos *espLivres,struct enderecos *espAtivos){
    struct enderecos *aux;
        while(espLivres != NULL){
                if (espLivres->posicao==mPos){
                    aux = (struct enderecos*) malloc(sizeof(struct enderecos));//mudar o tipo do malloc e mudara as atribuiçoes
                    aux->posicao = mPos;
                    aux->tamanho = tam;
                    aux->conRef = 1;
                    aux->prox = espAtivos;
                    return aux;
                }
            espLivres=espLivres->prox;
        };
};

//adiciona os luares novos ocupados no heap
void addHeap(int Pos, int tam, int heap[]){
    for(int i = Pos ; i < Pos+tam ; i++){
        heap[i]=1;
    }
};

//encontra a melhor posicao no caso first
int acharFirst(int tam,struct enderecos *espLivres){
    struct enderecos *aux = espLivres;
    while( aux->tamanho - tam < -1){
        aux = aux->prox;
    };
    return aux->posicao;
};

//encontra a melhor posicao no caso best e worst
int acharPosicao(int estado, int tam,struct enderecos *livres){
    struct enderecos *aux = livres;
    int Dif, mDif, mPos;
    mDif=-99;
    while( aux != NULL ){
        Dif = aux->tamanho - tam;
        if(Dif > -1){
            if(mDif == -99){
                mDif=Dif;
                mPos=aux->posicao;
            }
            if(Dif==0){
                mDif=Dif;
                mPos=aux->posicao;
                break;
            }
            switch(estado){
                    case 2://best = menor diferenca
                if (Dif<mDif && Dif>0){
                    mDif=Dif;
                    mPos=aux->posicao;
                }
                break;
                    case 3://worst = maior diferenca
                if (Dif>mDif && Dif>0){
                    mDif=Dif;
                    mPos=aux->posicao;
                }
                break;
            };
        }
        aux = aux->prox;
    };
    return mPos;
};

//limpa uma lista de strurutas
void limpalista(struct enderecos **livres){
    struct enderecos *aux = *livres;
    while(*livres!=NULL){
        *livres = aux->prox;
        free(aux);
        aux=*livres;
    }
};

//gera uma lista encadeada com os espacos livres no heap a partir de uma posicao
void geraLivresProx(int *mPos,int pIni,int tam,int heap[],int numMaxHeap,struct enderecos **livres){
    int cont=1,indice=0;
    int aux=heap[pIni];
        int flag = 0 ,i = pIni+1;
        while( i < numMaxHeap+1 && flag == 0){
            if (heap[i]==aux){
                aux=heap[i];
                cont++;
            }
            else{
                    if(heap[i-1]==0 ){
                        if( cont - tam > -1 ){
                            struct enderecos *aux;
                            struct enderecos *fim = *livres;
                            aux =(struct enderecos*) malloc(sizeof(struct enderecos));
                            aux->posicao = indice;
                            *mPos = indice;
                            aux->tamanho = cont;
                            aux->prox = NULL;
                            if(*livres == NULL){
                                *livres = aux;
                            }
                            else{
                                 while(fim->prox != NULL){
                                    fim = fim->prox;
                                 }
                                fim->prox = aux;
                            }
                            flag = 1;
                        }
                    }
                    aux=heap[i];
                    cont=1;
                    indice =i;

                }
        i++;
        };
};

//gera uma lista encadeada com os espacos livres no heap a partir do inicio
void geraLivres (int heap[],int nummax,struct enderecos **livres){
    int cont=1,indice=0;
    int aux=heap[0];
        for(int i=1 ; i<nummax+1 ; i++){
            if (heap[i]==aux){
                aux=heap[i];
                cont++;
            }
            else{
                    if(heap[i-1]==0 ){
                        struct enderecos *aux;
                        struct enderecos *fim = *livres;
                            aux =(struct enderecos*) malloc(sizeof(struct enderecos));
                            aux->posicao = indice;
                            aux->tamanho = cont;
                            aux->prox = NULL;
                            if(*livres == NULL){
                              *livres = aux;
                            }
                            else{
                                 while(fim->prox != NULL){
                                    fim = fim->prox;
                                 }
                                fim->prox = aux;
                            }
                    }
                    aux=heap[i];
                    cont=1;
                    indice =i;
                }
        };
    }

void imprimeativos(struct enderecos *livres){
    while(livres != NULL){
        printf("\n ATIVOS NO HEAP: %d  T: %d",livres->posicao,livres->tamanho);
        livres=livres->prox;
    };
};

//função que imprime o heap
void exibe(int nmax,int heap[]){
    printf("\nHEAP:");
    for(int i=0; i<nmax; i++ ){
        printf(" %d,",heap[i]);
    };
};

struct enderecos *addvar(int estadoHeap,int heap[], int numMaxHeap,int *ultADD, struct enderecos *espAtivos,
                         struct enderecos **espLivres, struct variaveis **varAtivas ){//retorna um ponteiro de esp ativos
    int tam,mPos;
    char va;

    printf("\nDigite id \n");
    scanf(" %c", &va);
    //printf("\nchar digitado foi:%c ",va);
    printf("\nDigite o tamanho\n");
    scanf(" %d", &tam);
    //printf("\ninteiro digitado foi:%d ",tam);
    switch(estadoHeap){
            case 1://first
                geraLivresProx(&mPos,0,tam,heap,numMaxHeap,&*espLivres);
        break;
            case 2://best=menor diferenca
            case 3://worst=maior diferenca
                geraLivres(heap,numMaxHeap,&*espLivres);
                mPos = acharPosicao(estadoHeap,tam,*espLivres);
        break;
            case 4://next
                geraLivresProx(&mPos,*ultADD,tam,heap,numMaxHeap,&*espLivres);
        break;
    }

    addHeap(mPos,tam,heap);
    espAtivos = incluiVar(mPos,tam,*espLivres,espAtivos);
    addVarAtv(va,espAtivos,&*varAtivas);
    limpalista(&*espLivres);
    *ultADD = mPos;
return espAtivos;
};


struct enderecos *delEsp(int heap[], struct enderecos *kill, struct enderecos *espAtivos){

        int i;
        struct enderecos *aux = espAtivos;
        struct enderecos *anterior = espAtivos;
        if(espAtivos == kill){
                if( kill->conRef == 0 ){
                for( i = kill->posicao ; i < kill->posicao + kill->tamanho ; i++){
                    heap[i] = 0;
                };
                free(espAtivos);
                espAtivos = aux->prox;
                return espAtivos;
            }
        }else {                while( aux != kill ){
                    anterior = aux;
                    aux=aux->prox;
                };
                if(kill->conRef == 0){
                    for(int i = kill->posicao ; i < (kill->posicao + kill->tamanho) ; i++){
                            heap[i] = 0;
                    };
                anterior->prox = kill->prox;
                free(kill);
            }
        }

                return espAtivos;
};


//deleta uma celula de uma lista encadeada pela var;
struct enderecos * delvarAtiv(char id,int heap[],int numMaxHeap, struct variaveis **varAtivas,struct enderecos *espAtivo){
    if(*varAtivas == NULL){
        printf("NAO EXISTE VARIAVEIS ATIVAS");
        return espAtivo;
    }else{
    struct variaveis *aux = *varAtivas;
    struct variaveis *anterior = *varAtivas;
    struct variaveis *retorno;NULL;
    int i;
        if( id == aux->id ){
            aux->ancora->conRef -= 1;
            espAtivo = delEsp(heap,aux->ancora,espAtivo);
            aux = aux->prox;
            free(*varAtivas);
            *varAtivas = aux;
        }else{
        int flag = 0;
            while (aux != NULL && flag ==0){
                if( id == aux->id){
                    aux->ancora->conRef -= 1;
                    espAtivo = delEsp(heap, aux->ancora,espAtivo);
                    anterior->prox = aux->prox;
                    free(aux);
                    flag = 1;
                }
                anterior = aux;
                aux=aux->prox;
            };
        }
    return espAtivo;
    }
};

//atribui o conteudo de uma variavel a outro;
void atribui(char var1,char var2,struct variaveis *varAtivas){
    struct variaveis *aux1 = varAtivas;
    struct variaveis *aux2 = varAtivas;
    int f1 = 0, f2 = 0;//flags

    while (aux1 != NULL && f1 == 0){
            if(aux1 == NULL){
            }else if(aux1->id == var1){
            f1 = 1;
            }
    if ( f1 == 0 )aux1 = aux1->prox;
    };

    while (aux2 != NULL && f2 == 0){
        if(aux2 == NULL){
        }else if(aux2->id == var2){
            f2 = 1;
        }
    if ( f2 == 0 )aux2 = aux2->prox;    };
    if(f1 == 1 && f2 == 1 ){
        aux1->ancora->conRef --;
        aux2->ancora->conRef ++;
        aux1->ancora = aux2->ancora;

    }
};

int main(int argc, char **argv)
{
    FILE *f;
    int start =1, numMaxHeap=30;
    int heap[numMaxHeap];


    if(!(f = fopen(argv[1],"r"))){
        printf("NAO ABRIU ARQUIVO\n");
        for (int i = 0; i<numMaxHeap; i++){heap[i]=0;};
    }else{
        int cont = 0;
        char v;
            while ( !feof(f) && cont < numMaxHeap ){
                fscanf(f,"%c",&v);
                heap[cont] = v - '0';
                cont++;
            }
        fclose(f);
    }


    struct enderecos *espLivres = NULL;
    struct enderecos *espAtivos = NULL;
    struct variaveis *varAtivas = NULL;


    int estadoHeap = 1;

    int op,id,ultAdd;
    char va;

        while (start == 1){
            imprimeativos(espAtivos);
            exibe(numMaxHeap,heap);
            imprimeVar(varAtivas);//refazer

            printf("\n       1=ADD | 2=DEL | 3=SET HEAP | 4=ATRIBUI | 5=FIM\n");

            scanf("%d",&op);
            switch(op){

                case 1://add
                    espAtivos = addvar( estadoHeap, heap, numMaxHeap,&ultAdd, espAtivos, &espLivres, &varAtivas);
                break;

                case 2://del
                    printf("\ndigite id");
                    scanf(" %c",&va);
                    espAtivos = delvarAtiv( va,heap, numMaxHeap, &varAtivas, espAtivos);

                break;

                case 3://set heap
                    printf("\n 1.first | 2.best | 3.worst | 4.next \n");
                    scanf("%d",&id);
                    estadoHeap = id;

                break;
                case 4://ATRIBUIR
                    printf("\n A recebe B, digite A e B\n");
                    char var1,var2;
                    scanf(" %c %c", &var1, &var2);//var1 recebe var2
                    atribui(var1,var2, varAtivas);
                break;
                case 5://fim
                    start= 0;
                break;
            }
        }
    return 0;
}
