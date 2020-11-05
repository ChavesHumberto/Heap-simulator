
void attEspLivres(struct livres *Pos,int tam){
    struct livres *aux = espLivres;
    if(Pos == espLivres){
        if(Pos->tamanho == tam){
            espLivres = espLivres->prox;
            free(aux);
        }else{
            espLivres->posicao += tam;
            espLivres->tamanho -= tam;
        }
    }else{
        if(Pos->tamanho == tam){
            while(aux->prox != Pos){
                aux=aux->prox;
            };
            aux->prox = Pos->prox;
            free(Pos);
        }else{
            Pos->posicao += tam;
            Pos->tamanho -= tam;
        }
    }
    };

void addVarAtv(char id,struct enderecos *adicionado,struct variaveis **varAtivas){
    struct variaveis *aux;
    aux = (struct variaveis*) malloc(sizeof(struct variaveis));
    aux->id = id;
    aux->ancora = adicionado;
    aux->prox = *varAtivas;
    *varAtivas = aux;
};

//cria uma celula na lista de espacos ativos em ordem
struct enderecos *incluiEsp(struct livres *mPos,int tam){
    struct enderecos *ant=NULL;
    struct enderecos *ativos = espAtivos;
    struct enderecos *aux;
                    aux = (struct enderecos*) malloc(sizeof(struct enderecos));
                    aux->posicao = mPos->posicao;
                    aux->tamanho = tam;
                    aux->conRef = 1;

        aux->prox = espAtivos;
        espAtivos = aux;
        return aux;
};

//adiciona os lugares novos ocupados no heap
void addHeap(int Pos, int tam, int heap[]){
    for(int i = Pos ; i < Pos+tam ; i++){
        heap[i]=1;
    }
};


//encontra a melhor posicao no caso first
struct livres *acharFirst(int tam,struct livres *aux){
    while(aux != NULL ){
        if(aux->tamanho - tam > -1) return aux;
        aux = aux->prox;
    }
    return aux;
};


//encontra a melhor posicao no caso best e worst
struct livres *acharPosicao(int estado, int tam){
    struct livres *aux = espLivres, *mPos;
    int f=0,Dif, mDif;
    mDif=-99;
    while( aux != NULL && f==0 ){
        Dif = aux->tamanho - tam;
        if(Dif > -1){
            if(mDif == -99){
                mDif=Dif;
                mPos=aux;
            }
            if(Dif==0){
                aux = aux->prox;
                mDif=Dif;
                mPos=aux;
                f=1;
            }
            switch(estado){
                    case 2://best = menor diferenca
                if (Dif<mDif && Dif>0){
                    mDif=Dif;
                    mPos=aux;
                }
                break;
                    case 3://worst = maior diferenca
                if (Dif>mDif && Dif>0){
                    mDif=Dif;
                    mPos=aux;
                }
                break;
            };
        }
        aux = aux->prox;
    };
    if(mDif<0)
        return NULL;
    else
    return mPos;
};



//adiciona uma variavel no Heap
struct livres *addvar(int estadoHeap,int heap[],struct livres *ultAdd, char va, int tam ){
    struct livres *mPos;
    if(espLivres == NULL){
        printf("\nHeap Cheio!\n");
        return;
    }
    switch(estadoHeap){
            case 1://first
                mPos = acharFirst(tam,espLivres);
        break;
            case 2://best=menor diferenca
            case 3://worst=maior diferenca
                mPos = acharPosicao(estadoHeap,tam);
        break;
            case 4://next
                mPos = acharFirst(tam,ultAdd);
    }
    if(mPos == NULL){
        printf("\nNAO TEM ESPAÇO NO HEAP!\n");
        return;
    }
    addHeap(mPos->posicao,tam,heap);
    struct enderecos *adicionado = incluiEsp(mPos,tam);
    addVarAtv(va,adicionado,&varAtivas);
    attEspLivres(mPos,tam);
    return mPos;
};
