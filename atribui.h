
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
        aux1->ancora->conRef-=1;
        if(aux1->ancora->conRef<1)
          delEsp(heap,aux1->ancora);
        aux2->ancora->conRef++;
        aux1->ancora = aux2->ancora;

    }
};
