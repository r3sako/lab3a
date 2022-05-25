#include <stdio.h>
#include <stdlib.h>

#include "func.h"

int main(){
    Table *table = NULL;
    table = (Table*) calloc(1,sizeof(Table));
    int rc;
    int (*fptr[])(Table *) = {NULL, D_Add, D_Find, D_Del, D_Show};

    while(rc = dialog(msgs, NMsgs)){
        if(!fptr[rc](table)){
            break;
        }
    }
    printf("That's all. Bye!\n");
    del(table);
    return 0;
}


