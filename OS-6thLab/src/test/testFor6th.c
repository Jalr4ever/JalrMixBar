#include <stdio.h>
#include <malloc.h>

int main(void){
   int n = 0 , m = 0;
   scanf("%d %d", &n, &m);
   printf("\n1st --- and m is : %d\n",m);
   char choice;
   scanf("%s",&choice);
   printf("\n2rd --- and m is : %d   and choice is %c \n", m, choice);
}