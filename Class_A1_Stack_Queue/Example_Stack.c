#include <stdio.h>
#include <stdlib.h>

#define STACKSIZE 100
struct stack {
    int top;
    int items[STACKSIZE];
};

int empty(struct stack *ps){
    if (ps->top == -1)
        return(1);
    else
        return (0);
}

void push(struct stack *ps, int x){
    if (ps->top == STACKSIZE - 1){
        printf("%s", "stack overflow");
        exit(1);
    }else{
        ps->items[++(ps->top)] = x;
    }
}

int pop(struct stack *ps){
    if(empty(ps)){
        printf("%s", "sctack underflow");
        exit(1);
    }
    return (ps->items[ps->top--]);
}

int main (){

    struct stack s;
    s.top = -1;
    if (empty(&s)){
        printf("\n");
        printf("Pilha vazia!\n");
    }
    push(&s,1);
    push(&s,2);
    push(&s,3);
    push(&s,4);
    printf("\n");
    printf("%d ", pop(&s));
    printf("%d ", pop(&s));
    printf("%d ", pop(&s));
    printf("%d ", pop(&s));
    printf("%d ", pop(&s));
    
    printf("\n");
    system("pause");
    return 0;
}