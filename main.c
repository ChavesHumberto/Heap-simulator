
#include <stdio.h>
 struct enderecos {
   int  posicao;
   int  tamanho;
   struct enderecos *prox;
};

void new(int id,int tam){};

void exibe(int nmax,int heap[]){
    printf("\nHEAP:");
    for(int i=0; i<nmax; i++ ){
        printf(" %d,",heap[i]);
    };  
};

int menu(int heap[],struct enderecos *esp){
    printf("\nOP:\n       1=ADD|2=DEL|3=FIM");
    int op, id,tam;
    scanf("%d",&op);
        switch(op){
            
                case 1:
                printf("\nDigite id e tam\n");
                scanf("%d,%d",&id,&tam);
                new(id,tam);
                for(int i = id; i<id+tam-1; i++){
                    heap[i]=1;
                }
            break;
            
                case 2:
                printf("\ndigite id");
                scanf("%d",&id);
            break;
            
                case 3:
                return 0;
            break;
        }
        
        return 1;
}


int main()
{
    int start =1, nunMaxHeap=10;
    int heap[nunMaxHeap];
    for (int i = 0; i<nunMaxHeap; i++){heap[i]=0;};
    
   struct enderecos *espLivres;
    
    while (start == 1){
    exibe(nunMaxHeap,heap);
    
    start = menu(heap,espLivres);
    }
    return 0;
}

