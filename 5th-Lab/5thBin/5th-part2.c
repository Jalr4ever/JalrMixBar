//
// Created by jalr on 18-10-28.
//

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_PAGE 10

int MAX_PAGE_NUM = 10;         //虚拟页的最大页数
#define P_LACK -222             //缺页（可用）
#define P_UNLACK -111           //不缺页（不可用）

//用户运行的内存块
typedef struct MemoryBlock{

    int virtualPID;             //用户内存的虚页编号
    int actualPID;              //预备的全部的实页编号
    struct MemoryBlock *next;   //执向虚页的指针

}MemoryBlock;


//关于页面地址流
int Page[320]={0};                           //虚拟存储区,存储320条指令
int Page_flu[320]={0};                       //内存访问区，存储转换过来的320个页地址流，并且分成32页
int count=0;                                 //随机产生的指令条数
int provide_page_num = MAX_PAGE;           //可用页面数量，针对用户虚页来说的，初始化为最大可用页数
int cycle_out_id=0;                            //要调出用户内存区的实页号
int lack_page=0;                             //缺页数

//形成随机的320条指令地址, 存放在虚拟区中
void Pro_Page(){

    int m=0;         //在[0,319]的指令地址之间随机选取一起点m
    m=rand()%320;

    Page[count]=m;
    count++;
    if(count==320){
        return;
    }
    int m_=0;        //在前地址[0,m+1]中随机选取一条指令并执行
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

    Pro_Page();
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

//生成访问序列
void mockSequency(){
    srand(time(0));//随机时间种子
    Pro_Page();
    Flu();
}

/*----------------------------------------------------------*/


//扫描内存块的队列，查看是否存在
int check_memory_block(MemoryBlock *head, int virPageVal){
    MemoryBlock *p;
    p=head->next;//指向第一个页面
    while(p!=NULL){
        if(p->virtualPID == virPageVal){//存在，表示不缺页
            return P_UNLACK;
        }
        p=p->next;
    }
    return P_LACK;//不存在，缺页
}

//将缺页的页面调入内存
void insert_page(MemoryBlock *head, int actPageVal, int command){
    if(provide_page_num >= 1){                  //存在可用页面
        MemoryBlock *p;
        p=head->next;
        while (p->actualPID != P_LACK){
            p=p->next;
        }
        p->actualPID=actPageVal;
        provide_page_num--;                     //可用页减一
    }
    else{                                       //缺少可用页面，先进的要先出
        MemoryBlock *p;
        p=head;
        while (p->virtualPID != cycle_out_id){  //检查虚页ID与要调出的页号是否相等
            p=p->next;
        }
        p->actualPID=actPageVal;                //调出该页其实就是替换了该页的地址
        cycle_out_id++;                         //指向下一个元素
        if(cycle_out_id == MAX_PAGE_NUM){
            cycle_out_id=1;
        }
    }
}

void FIFO(MemoryBlock *head){
    for(int i = 0; i <= 319; i++){
        if(check_memory_block(head, Page_flu[i]) == P_LACK){
            lack_page++;
            insert_page(head, Page_flu[i], Page[i]);    //第三个参数，Page里存的是指令，也可以不操作
        }
        else{   //不缺页
//            printf("内存页 %d 不缺",Page_flu[i]);
        }
    }
}



/**
 * 一开始设置为全部缺页
 * @param memory
 */
void initMemoryBlock(MemoryBlock *memory){
    lack_page=0;
    for(int i = 0; i <= MAX_PAGE_NUM; i++){
        memory[i].next=&memory[i+1];
        memory[i].actualPID=P_LACK;
        memory[i].virtualPID=i;
        if(i == MAX_PAGE_NUM){
            memory[i].actualPID=P_LACK;
            memory[i].next=NULL;
            memory[i].virtualPID=i;
            break;
        }
    }
}

void threeMock(MemoryBlock *head){
    initMemoryBlock(head);
    int temp_max;
//    for()

}

int main() {

    mockSequency();
//    printPro_Page();
//    printPage_Flu();
    MemoryBlock m1[MAX_PAGE_NUM+1];
    MemoryBlock *head;
    head=&m1[0];
    initMemoryBlock(head);
    FIFO(head);

    float lack_last=lack_page;
    printf("FIFO: %lf  \t",1-lack_last/320);

    return 0;

}