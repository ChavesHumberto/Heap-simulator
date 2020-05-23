#include <stdio.h>
#include <stdlib.h>

 struct enderecos {
    char var;
    int  posicao;
    int  tamanho;
   struct enderecos *prox;
};

void imprimeVar(struct enderecos *livres){
    while(livres != NULL){
        printf("\nVAR: %c  T: %d",livres->var,livres->tamanho);
        livres=livres->prox;
    };
};




//cria uma celula na lista de variaveis ativas
struct enderecos *incluiVar(int mPos,char id,int tam,struct enderecos *espLivres,struct enderecos *varAtivas){
    struct enderecos *aux;
    
        while(espLivres != NULL){
                if (espLivres->posicao==mPos){
                        printf("\nposicao=%d\n",espLivres->posicao);
                    aux = (struct enderecos*) malloc(sizeof(struct enderecos));
                    aux->var = id;
                    aux->posicao = mPos;
                    aux->tamanho = tam;
                    aux->prox = varAtivas;
                    return aux;
                }    
            espLivres=espLivres->prox;
        };
    
};



//adiciona os luares novos ocupados no heap 
void addHeap(int Pos, int tam, int heap[]){
    for(int i = Pos ; i < Pos+tam-1 ; i++){
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
    mDif=-100;
    while( aux != NULL ){
        Dif = aux->tamanho - tam;  
        if(Dif > -1){
            
            if(mDif == -100){
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



void imprimelivres(struct enderecos *livres){
    while(livres != NULL){
        printf("\nP: %d  T: %d",livres->posicao,livres->tamanho);
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






struct enderecos *addvar(int estadoHeap,int heap[], int nunMaxHeap,int *ultADD, struct enderecos *varAtivas, struct enderecos **espLivres){
    int tam,mPos;
    char va;
    
    printf("\nDigite id \n");
    scanf(" %c", &va);
    //printf("\nchar digitado foi:%c ",va);
    printf("\nDigite o tamanho\n");
    scanf(" %d", &tam);
    //printf("\ninteiro digitado foi:%d ",tam);
    switch(estadoHeap){
            case 1://first  TRABALHANDO
                geraLivresProx(&mPos,0,tam,heap,nunMaxHeap,&*espLivres);
                //imprimelivres(*espLivres);
   
        break;
            case 2://best=menor diferenca
            case 3://worst=maior diferenca
                geraLivres(heap,nunMaxHeap,&*espLivres);
                //imprimelivres(*espLivres);
                mPos = acharPosicao(estadoHeap,tam,*espLivres);

        break;
            case 4://next  TRABALHANDO
                geraLivresProx(&mPos,*ultADD,tam,heap,nunMaxHeap,&*espLivres);
                //imprimelivres(*espLivres);
        break;
    }
    //printf("\nmPos:%d\n",mPos);
    for (int i = mPos ; i<mPos + tam ; i++){heap[i]=1;};
    exibe(nunMaxHeap,heap);
    varAtivas = incluiVar(mPos,va,tam,*espLivres,varAtivas);
    
    limpalista(&*espLivres);
    *ultADD = mPos;
return varAtivas;
};


//deleta uma celula de uma lista encadeada pela var;
void delvar(char id,struct enderecos **varAtivas,int heap[],int numMaxHeap){
    if(*varAtivas == NULL){
        printf("NAO EXISTE VARIAVEIS ATIVAS");
        return ;
    }
    
    struct enderecos *aux = *varAtivas;
    struct enderecos *anterior = *varAtivas;
    int i;
    if( id == aux->var ){
        for( i=aux->posicao ; i < aux->posicao + aux->tamanho ; i++ ){heap[i] = 0;};
        aux = aux->prox;
        free(*varAtivas);
        *varAtivas = aux;
    }else{
        
    int flag = 0;
        while (aux != NULL && flag ==0){
            if( id == aux->var){
                //TRABALHANDOOO####################################################################
                    
                    
                    for( i=aux->posicao ; i < aux->posicao + aux->tamanho ; i++ ){heap[i] = 0;};
                    
                    anterior->prox = aux->prox; 
                    free(aux);
                    flag = 1; 
            }
            anterior = aux;
            aux=aux->prox;    
        };
    }
    
    
};



int main()
{
     
    int start =1, nunMaxHeap=30;
    int heap[nunMaxHeap];

    for (int i = 0; i<nunMaxHeap; i++){heap[i]=0;};
    
    
    struct enderecos *varAtivas = NULL;
    struct enderecos *espLivres = NULL;
    
    
    int estadoHeap = 1;
    
    int op,id, mPos,tam,ultAdd;
    char va;
       
        while (start == 1){
            exibe(nunMaxHeap,heap);
            imprimeVar(varAtivas);
            
            printf("\nOP:\n       1=ADD | 2=DEL | 3=SET HEAP | 4=ATRIBUI | 5=FIM\n");
        
            scanf("%d",&op);
            switch(op){
                
                case 1://add
                    varAtivas = addvar(estadoHeap, heap, nunMaxHeap,&ultAdd, varAtivas, &espLivres);
                break;
                
                case 2://del
                    printf("\ndigite id");
                    scanf(" %c",&va); 
                    delvar(va,&varAtivas,heap, nunMaxHeap);
                break;
                
                    case 3://set heap
                    printf("\n 1.first | 2.best | 3.worst | 4.next \n");
                    scanf("%d",&id);
                    estadoHeap = id;
                    
                break;
                    case 4://
                    //
                break;
                    case 5://fim
                    start= 0;
                break;
            }
        }
    return 0;
}





