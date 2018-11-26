#include <stdio.h>

//
// Created by Jalr on 2018/11/26.
//
void main(){
    int t = 0;
    int choice = 0;
    int a = 0;
    while (a < 2 ){
        scanf("%d", &t);
//        printf("You input :  %d\n",t);
        printf("Choose a operation:  (1 or 2) \n1 is Create new file\n2 is Delete a file\n");
        scanf("%d", &choice);
        switch (choice){
            case 1 :
                printf("You input 1 :  %d\n",t+1);
                break;
            case 2 :
                printf("You input 2 :  %d\n",t+2);
                break;
            default :
                printf("Invalid\n");
                break;
        }
        a++;
    }
}
