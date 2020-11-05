#define  numMaxHeap 30
int estadoHeap = 1;
int heap[numMaxHeap];
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "extras.h"
struct livres *espLivres = NULL;
struct enderecos *espAtivos = NULL;
struct variaveis *varAtivas = NULL;

#include "adiciona.h"
#include "deleta.h"
#include "atribui.h"

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    FILE *f;
    char nomeArq[256], aux[30],var1,var2,va;
    int start =1,op, id, tam;
    int heap[numMaxHeap];
    struct livres *ultAdd;
    for (int i = 0; i<numMaxHeap; i++)
    {
        heap[i]=0;
    };
    espLivres = (struct livres*) malloc(sizeof(struct livres));
    espLivres->posicao = 0;
    espLivres->tamanho = numMaxHeap;
    espLivres->prox = NULL;
    if(argv[1]==NULL)
    {
        printf("Digite o nome do arquivo .txt de instruções:\n");
        scanf("%s", &nomeArq);
    }
    else
        strcpy(nomeArq,argv[1]);
    if(!(f = fopen(nomeArq,"r")))
    {
        printf("Não foi possível abrir o arquivo.Deseja continuar pelo modo manual?\n1.Para continuar\n2.Para encerrar a exeução\n");
        scanf("%d",&op);
        if(op!=1)
            exit(42);
    }
    else
    {
        while(feof(f)==0)
        {


            fscanf(f,"%s",aux);
            if(strcmp(aux,"heap")==0)//SET HEAP
            {
                fscanf(f,"%s",aux);
                if(strcmp(aux,"first")==0)
                    estadoHeap=1;
                else if(strcmp(aux,"best")==0)
                    estadoHeap=2;
                else if(strcmp(aux,"worst")==0)
                    estadoHeap=3;
                else if(strcmp(aux,"next")==0)
                    estadoHeap=4;
                else
                {
                    printf("Instrução não reconhecida, encerrando execução!\nAperte qualquer tecla para encerrar.\n");
                    fflush(stdin);
                    getchar();
                    exit(-777);
                }



            }
            else if (strcmp(aux,"new")==0)//CRIAÇÃO DE VARIAVEL
            {
                fscanf(f," %s %d",&var1,&tam);
                ultAdd = addvar( estadoHeap,heap,ultAdd,var1,tam);

            }
            else if (strcmp(aux,"exibe")==0)//EXIBE SITUAÇÃO DO HEAP
            {
                exibe(numMaxHeap,heap);
            }
            else if (strcmp(aux,"del")==0)//DELETAR VARIAVEL
            {
                fscanf(f," %s",&var1);
                delvarAtiv(var1,heap);

            }
            else//Atribuição ou Inst Errada
            {
                var1 = aux[0];
                fscanf(f," %s",aux);
                if(strcmp(aux,"=")==0)//Atribuição
                {
                    fscanf(f," %s",&var2);
                    atribui(var1,var2, varAtivas);
                }
                else if(var1!=aux[0])//Inst Errada
                {
                    printf("\nInstrução não reconhecida, encerrando execução!\nAperte qualquer tecla para encerrar.\n");
                    fflush(stdin);
                    getchar();
                    exit(-777);
                }
            }
        }
        fclose(f);
        printf("\nA leitura do arquivo de instruções chegou ao fim!\nDigite:\n1. para iniciar o modo de alteração manual do heap\n2. para encerrar o programa\n");
        scanf("%d",&op);
        if(op!=1)
            exit(0);

    }

    while (start == 1)
    {
        imprimeativos(espAtivos);
        imprimeLivre(espLivres);
        exibe(numMaxHeap,heap);
        imprimeVar(varAtivas);//refazer
        printf("\n\n------------------------- MENU -------------------------");
        printf("\n1: adicionar | 2: deletar | 3: set heap | 4: atribuir | 5: encerrar | 6: limpar tela\n");

        scanf("%d",&op);
        switch(op)
        {
        case 1://add
            printf("\nDigite um caracter para ser o nome da variavel: \n");
            scanf(" %c", &va);
            printf("\nDigite o tamanho da variavel:\n");
            scanf(" %d", &tam);
            ultAdd = addvar( estadoHeap,heap,ultAdd,va,tam);
            break;

        case 2://delete
            printf("\nDigite o nome da var:\n");
            scanf(" %c",&va);
            delvarAtiv( va,heap);

            break;

        case 3://set heap
            printf("\n 1.first | 2.best | 3.worst | 4.next \n");
            scanf("%d",&id);
            if(id>=1 && id<=4)
                estadoHeap = id;

            break;
        case 4://assign
            printf("\n A recebe B (A=B), digite A,e depois,B\n");
            char var1, var2;
            scanf(" %c %c", &var1, &var2);
            atribui(var1,var2, varAtivas);//var1 recebe var2

            break;
        case 5://finish
            start = 0;
            break;
        case 6:
            system("cls");
            break;

        }
    }
    return 0;
}
