//
// Created by jalr on 18-10-28.
//

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define FIFO 0
#define OPT 1

#define P_LACK -222             //缺页（需要调入）
#define P_UNLACK -111           //不缺页（不需调入）

//用户运行的内存块
typedef struct MemoryBlock{

    int virtualPID;             //用户内存的虚页编号
    int actualPID;              //预备的全部的实页编号
    struct MemoryBlock *next;   //执向虚页的指针

}MemoryBlock;

int Page[320]={0};                           //虚拟存储区,存储320条指令
int Page_flu[320]={0};                       //内存访问区，存储转换过来的320个页地址流，并且分成32页
int count=0;                                 //随机产生的指令条数
int lack_page=0;                             //缺少的页数-指向FIFO的最后页数
int cycle_out_id=0;
int choice_out_id=0;                         //缺少页数-指向最久不使用的序列

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

//生成访问序列
void mockSequency(){
    srand(time(0));//随机时间种子
    Pro_Page();
    Flu();
}

//扫描内存块的队列，查看是否存在
int check_memory_block(MemoryBlock *head, int virPageVal){
    MemoryBlock *p;
    p=head->next;//指向第一个页面
//    p=head;
    while(p!=NULL){
        if(p->virtualPID == virPageVal){//存在，表示不缺页
            return P_UNLACK;
        }
        p=p->next;
    }
    return P_LACK;//不存在，缺页
}

//要调入内存的页面置换算法页面置换算法
void insert_page(MemoryBlock *head, int actPageVal, int *provide_page_num,int max_page_num, int choice){


    if(choice == FIFO){                              //FIFO策略置换页面
        if(*provide_page_num >= 1){                  //存在可用页面
            MemoryBlock *p;
            p=head->next;
            while (p->actualPID != P_LACK){
                p=p->next;
            }
            p->actualPID=actPageVal;
            (*provide_page_num)--;                  //可用页减一
        }
        else{                                       //缺少可用页面，先进的要先出
            MemoryBlock *p;
            p=head;
            while (p->virtualPID != cycle_out_id){  //检查虚页ID与要调出的页号是否相等
                p=p->next;
            }
            p->actualPID=actPageVal;                //调出该页其实就是替换了该页的地址
            cycle_out_id++;                         //指向下一个元素
            if(cycle_out_id == max_page_num){
                cycle_out_id=1;
            }
        }
        
    } else if (choice == OPT){                      //OPT策略置换页面
        if(*provide_page_num >= 1){                 //存在可用页面
            MemoryBlock *p;
            p=head->next;
            while (p->actualPID != P_LACK){
                p=p->next;
            }
            p->actualPID=actPageVal;
            (*provide_page_num)--;
        }
        else{
            //OPT选择算法
//
//            MemoryBlock *p;
//            p=head->next;
//
//            while( p->actualPID != choice_out_id){
//                p=p->next;
//            }
//            p->actualPID=actPageVal;


        }
    }
}

void _FIFO(MemoryBlock *head, int *provide_page_num,int max_page_num){
    for(int i = 0; i <= 319; i++){
        if(check_memory_block(head, Page_flu[i]) == P_LACK){ //若缺页，需要调入
            lack_page++;
            insert_page(head, Page_flu[i],provide_page_num,max_page_num, FIFO);    //第三个参数，Page里存的是指令，也可以不操作
        }
        else{   //不缺页
//            printf("在使用FIFO页面置换算法:  内存页 %d 不缺",Page_flu[i]);
        }
    }
}

void _OPT(MemoryBlock *head, int *provide_page_num,int max_page_num){
    for (int i = 0; i < 319; i++) {
        if (check_memory_block(head, Page_flu[i] == P_LACK)){
            lack_page++;
            insert_page(head,Page_flu[i],provide_page_num, max_page_num,OPT);
        } else{
//            printf("在使用OPT页面置换算法:  内存页 %d  不缺",Page_flu[i]");
        }
    }

}

void initMemory(MemoryBlock *memory, int max_page_num){
    lack_page=0;
    cycle_out_id=0;
    for(int i = 0; i <= max_page_num; i++){
        memory[i].next=&memory[i+1];
        memory[i].actualPID=P_LACK;
        memory[i].virtualPID=i;
        if(i == max_page_num){
            memory[i].actualPID=P_LACK;
            memory[i].next=NULL;
            memory[i].virtualPID=i;
            break;
        }
    }
}

void doLab(){

    mockSequency();//随机生成320条指令
    for (int MAX_PAGE_NUM = 4; MAX_PAGE_NUM <= 32; MAX_PAGE_NUM++) {
        int provide_page_num=MAX_PAGE_NUM;//可提供页初始化为最大
        MemoryBlock m1[MAX_PAGE_NUM+1];
        MemoryBlock *head;
        head=&m1[0];
        initMemory(head,MAX_PAGE_NUM);
        _FIFO(head,&provide_page_num,MAX_PAGE_NUM);
        float lack_last=lack_page;
        printf("MAX PAGE————%d FIFO: \t%lf\n",MAX_PAGE_NUM,1-lack_last/320);
    }
}

void main(){
    doLab();
}
