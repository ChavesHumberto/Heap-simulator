void addEspLivre (int pos, int tam){
    struct livres * aux = espLivres;
    struct livres * ant = NULL;
    if(espLivres == NULL){
        espLivres = (struct livres*)malloc(sizeof(struct livres));
        espLivres->posicao=pos;
        espLivres->tamanho=tam;
        espLivres->prox=NULL;
    }else{
    while (pos > aux->posicao){
        ant=aux;
        aux=aux->prox;
    }
    if(ant == NULL){
        if(pos+tam == aux->posicao){
            aux->posicao = pos;
            aux->tamanho += tam;
        }else{
            espLivres = (struct livres*)malloc(sizeof(struct livres));
            espLivres->posicao=pos;
            espLivres->tamanho=tam;
            espLivres->prox=aux;
        }
    }else if(ant->posicao + ant->tamanho == pos){
            ant->tamanho += tam;
            if(pos+tam == aux->posicao || pos+tam == numMaxHeap){
                ant->tamanho += ant->prox->tamanho;
                struct livres *kill= ant->prox;
                ant->prox = ant->prox->prox;
                free(kill);
            }
        }else if(pos+tam == aux->posicao){
            aux->posicao = pos;
            aux->tamanho += tam;
        }else{
            ant->prox = (struct livres *)malloc(sizeof(struct livres));
            ant->prox->posicao = pos;
            ant->prox->tamanho = tam;
            ant->prox->prox = aux;
        }
    }
};

void delEsp(int heap[], struct enderecos *kill){

        int i;
        struct enderecos *aux = espAtivos;
        struct enderecos *anterior = espAtivos;
        if(espAtivos == kill){
                if( kill->conRef < 1 ){
                for( i = kill->posicao ; i < kill->posicao + kill->tamanho ; i++){
                    heap[i] = 0;
                };
                addEspLivre(espAtivos->posicao, espAtivos->tamanho);
                free(espAtivos);
                espAtivos = aux->prox;
            }
        }else {                while( aux != kill ){
                    anterior = aux;
                    aux=aux->prox;
                };
                if(kill->conRef < 1){
                    for(int i = kill->posicao ; i < (kill->posicao + kill->tamanho) ; i++){
                            heap[i] = 0;
                    };
                anterior->prox = kill->prox;
                addEspLivre(kill->posicao, kill->tamanho);
                free(kill);
            }
        }

};


//deleta uma celula de uma lista encadeada pela var;
void delvarAtiv(char id,int heap[]){
    if(varAtivas == NULL){
        printf("NAO EXISTE VARIAVEIS ATIVAS");

    }else{
    struct variaveis *aux = varAtivas;
    struct variaveis *anterior = varAtivas;
    struct variaveis *retornoNULL;
    int i;
        if( id == aux->id ){
            aux->ancora->conRef -= 1;
            delEsp(heap,aux->ancora);
            aux = aux->prox;
            free(varAtivas);
            varAtivas = aux;
        }else{
        int flag = 0;
            while (aux != NULL && flag ==0){
                if( id == aux->id){
                    aux->ancora->conRef -= 1;
                    delEsp(heap, aux->ancora);
                    anterior->prox = aux->prox;
                    free(aux);
                    flag = 1;
                }
                anterior = aux;
                aux=aux->prox;
            };
        }
    }
};

