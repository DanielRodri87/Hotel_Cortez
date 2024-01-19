// main.c
#include <stdio.h>
#include "scripts/functor.h"

int main(void) {
    int op;
    oimundo();
    while(1) {
        printf("Menu: 1 - Daniel 2- Rita");
        scanf("%d", &op);
        if (op == 1)
        {
            printf("Escolheu o boy");
        }else if(op == 2)
        {
           printf("Escolheu a gata");

        }
        
        
    }

    return 0;

}
