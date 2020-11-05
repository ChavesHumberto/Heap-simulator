struct enderecos
{
    char var;
    int posicao;
    int tamanho;
    int conRef;
    struct enderecos *prox;
};

struct livres
{
    int posicao;
    int tamanho;
    struct livres *prox;
};


struct variaveis
{
    char id;
    struct enderecos *ancora;//ponteiro p um elemento especifico da lista de espacos ativos
    struct enderecos *filhos;
    struct variaveis *prox;
};


//função que imprime o heap
void exibe(int nmax,int heap[])
{
    switch(estadoHeap)
    {
    case 1:
        printf("\nMÉTODO DE INSERÇÃO NO HEAP: First\n");
        break;
    case 2:
        printf("\nMÉTODO DE INSERÇÃO NO HEAP: Best\n");
        break;
    case 3:
        printf("\nMÉTODO DE INSERÇÃO NO HEAP: Worst\n");
        break;
    case 4:
        printf("\nMÉTODO DE INSERÇÃO NO HEAP: Next\n");
        break;
    }
    printf("\nINDC:");
    for(int i=0; i<nmax; i++ )
        printf(" %d ",i);
    printf("\nHEAP:");
    for(int i=0; i<nmax; i++ )
    {
        if(i>=10)
            printf(" ");
        printf(" %d,",heap[i]);
    }
    printf("\n");

};


void imprimeVar(struct variaveis *livres)
{
    while(livres != NULL)
    {
        printf("\nVAR: %c  TAMANHO: %d",livres->id,livres->ancora->tamanho);
        livres=livres->prox;
    };
};


void imprimeativos(struct enderecos *livres)
{
    while(livres != NULL)
    {
        printf("\nATIVOS NO HEAP-> POS.INICAL:%d  TAMANHO: %d",livres->posicao,livres->tamanho);
        livres=livres->prox;
    };
};

void imprimeLivre(struct livres *livres)
{
    while(livres != NULL)
    {
        printf("\nESP LIVRES NO HEAP-> POS.INICAL:%d  TAMANHO: %d",livres->posicao,livres->tamanho);
        livres=livres->prox;
    };
};

