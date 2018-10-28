//
// Created by jalr on 18-10-28.
//

#include<stdio.h>
void get(int *num){
    (*num)--;
    printf("%d",*num);
}
main(){
    int s=9;
    get(&s);
//    printf("%d",s);
}