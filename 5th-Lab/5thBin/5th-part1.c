//
// Created by jalr on 18-10-28.
//

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * 1.虚拟存储区中指令生成320条，320条的指令的值放在Page[320]中，指令的值为0-319
 * 2.内存访问区中访问页生成32页，320条指令的访问页号放在Page_flu[320]中，值为0-31，
 */


//关于页面地址流
int Page[320]={0};//虚拟存储区,存储320条指令
int Page_flu[320]={0};//内存访问区，存储转换过来的320个页地址流，并且分成32页
int count=0;

//形成随机的320条指令, 存放在虚拟区中
void Pro_Page(){
    int m=0;    //在[0,319]的指令地址之间随机选取一起点m
    m=rand()%320;

    Page[count]=m;
    count++;
    if(count==320){
        return;
    }
    int m_=0;    //在前地址[0,m+1]中随机选取一条指令并执行
    m_=rand()%(m+1);

    Page[count]=m_;
    count++;
    if(count==320){
        return;
    }
    Page[count]=m_+1;
    count++;
    if(count==320){
        return;
    }
    int m__=0;
    m__=(m_+2)+rand()%( 319-(m_+2)+1 );    //在后地址[m_+2,319]的指令地址之间随机选取一条指令并执行
    Page[count]=m__;
    count++;
    if(count==320){
        return;
    }

    Pro_Page();//递归循环
}

//虚拟区的地址 -----> 对应要访问的的内存的地址序列号
int Judge_Page(int value){    //输入指令,返回指令对面的页面号
    return value/10;
}

//随机的指令地址序列 -----> 随机的内存地址页面访问序列
void Flu(){
    int i=0;
    for(i=0;i<=319;i++){
        Page_flu[i]=Judge_Page( Page[i] );
    }
}

//打印虚拟区的地址，3个一组
void printPro_Page(){
    int i,j=0;
    printf("Page address stream : \n");
    for(i=0;i<=319;i++){    //输出页地址流
        printf("%d   \t",Page[i]);
        j++;
        if(j == 3){
            printf("\n");
            j=0;
        }
    }
    printf("\n\n");
}

//打印内存访问序列的地址流，10个一组
void printPage_Flu(){
    printf("Command sequence in the memory:   \n");
    int i, j=0;
    j=0;
    for(i = 0; i <= 319; i++){
        printf("%d   \t", Page_flu[i]);
        j++;
        if( j == 10 ){
            printf(" \n");
            j=0;
        }
    }
    printf("\n\n");
}

int main() {

    srand(time(0));//随机时间种子
    Pro_Page();
    Flu();
    printPro_Page();
    printPage_Flu();

    return 0;
}