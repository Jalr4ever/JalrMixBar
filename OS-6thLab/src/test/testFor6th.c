#include <stdio.h>
#include <malloc.h>

typedef struct {
    char name[10];
}*TTest,_TTest;
int main(void){
   TTest t = (TTest) malloc(sizeof(_TTest));
   scanf("%s",t->name);
   printf("What you have input: %s",t->name);
}