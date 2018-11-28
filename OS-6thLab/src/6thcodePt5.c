//
// Created by Jalr on 2018/11/26.
//

#include <stdio.h>
#include <malloc.h>

#define BLOCK_SIZE 8 //定义一个盘块占 8 字节
#define FILE_NAME_LENGTH 10 //文件名最长 10 个字节

typedef struct {
    int **map;              //这里直接用整型来表示位示图的状态了
}*BitMap, _BitMap;

/**
 * 物理盘块（文件数据块），简化了一下，数据域没使用到
 */
typedef struct Block_Node{
    int block_id;
    int data;
    struct Block_Node* next;
}*Block_Node, _Block_Node;

/**
 * FCB，直接采用隐式链接分配方式，包含文件名
 */
typedef struct {
    char name[FILE_NAME_LENGTH];
    Block_Node first_block;
}*FCB,_FCB;

//返回第一个可用的盘块号
int checkBitMap(BitMap bitMap, int n, int m){
    int avail_block_id = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(bitMap -> map[i][j] == 0){
                avail_block_id = i * m + j; //这个公式应该根据 字号，位号，盘块号从 0 或 1开始判断的，这时都从0开始的情况
                return avail_block_id;
            }
        }
    }
    return avail_block_id;
}
void travelBitMap(BitMap bitMap,int n, int m){
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d  ", bitMap -> map[i][j]);
        }
        printf("\n");
    }
}
void updateMap(BitMap bitmap, int n, int m, int b){
    //获取字号和行号
    int i = b / m;
    int j = b % m;
//    printf("\n%d --- %d\n", i, j );
    if(bitmap -> map[i][j] == 0){
        bitmap -> map[i][j] = 1;            //原来的 0 为可用，1 代表占用，是不可用
    } else if(bitmap -> map[i][j] == 1){
        bitmap -> map[i][j] = 0;            //原来的 1 为不可用，0 代表空闲，是可用
    }
    printf("Bitmap status:   \n");
    travelBitMap(bitmap, n, m);
}

void createFile(BitMap bitMap, int n, int m,  FCB *file_fcb){

    int disk_size = n * m * BLOCK_SIZE;

    int file_size = -1;

    int file_block = -1;

    int avail_block = checkBitMap(bitMap, n, m);

    if(avail_block == -1){
        printf("Disk is full.Try delete a file first!");
    }

    else{ //磁盘有空间
        //1. 初始化该文件的 FCB 目录项，一个 FCB 对应一个文件，这里还初始化文件名
        (*file_fcb)= (FCB) malloc(sizeof(_FCB));
        printf("------\nStart to create a new file. Please input file name: \n");
        scanf("%s", (*file_fcb)->name);
        printf("\nPlease input file size (Size must less than %d bytes): \n", disk_size);
        scanf("%d",&file_size);
        if(file_size <= 0){
            printf("Wrong file size!");
        }

        else {
            file_block = file_size / BLOCK_SIZE;
            if (file_size % BLOCK_SIZE != 0){ //对应 0 与 不能整块分的情况
                file_block ++;
            }
        }

        //为文件分配指定数量的盘块，初始化 fcb 第一个盘块的首盘块指针及其指向的地址内容
        (*file_fcb) -> first_block = (Block_Node) malloc (sizeof(_Block_Node));
        (*file_fcb)-> first_block -> block_id = avail_block;
        (*file_fcb)-> first_block -> next = NULL;
        file_block--;//第一个盘块已经分配，那么需分配数减一
        //修改位示图

        //Todo 更新位示图的函数！！！-DONE 2018.11.27 15:00
        updateMap(bitMap, n, m, avail_block);

        //从文件的第一个文件块往后给文件新增节点
        while(file_block > 0){//插入下一个盘块节点
            Block_Node temp_node = ((*file_fcb) -> first_block); //第一个文件的指针
            while(temp_node->next !=NULL){
                temp_node = temp_node ->next;
            }
            //现在的 temp_node 和 最后一个不空的节点 指向同一片内存 !
            //需要新建一个节点插在后面 !
            int new_avail_block = checkBitMap(bitMap, n, m);
            Block_Node new_node = (Block_Node) malloc(sizeof(_Block_Node));
            new_node -> next = NULL;
            new_node -> block_id = new_avail_block; //得到可用的字位号

            //Todo 更新位示图的函数！！！-DONE 2018.11.27 15:00
            updateMap(bitMap, n, m, new_avail_block);

            temp_node -> next = new_node; //新的盘块节点插入到原来的尾节点
            file_block--;
        }

        printf("Create file successfully ! You file name is : %s !\n",(*file_fcb)->name);

    }
}

//释放位示图，但这里暂且不用
void freeMap(BitMap bitMap, int m){
    for(int i = 0; i < m; i++){
        free(bitMap -> map[i]);    //释放行指针
    }
    free(bitMap -> map);           //释放列指针
}

//为 bitmap分配  n 行，m 列的大小
void initMap(BitMap *bitmap, int n, int m){
    int block_num = n * m;
    *bitmap = (BitMap) malloc(sizeof(_BitMap));//首先为位示图分配内存
    (*bitmap) -> map = ( int** ) malloc ( sizeof( int* ) * n ); //分配一个 m 行的数组
    for(int i = 0; i < n; i++){
        (*bitmap) -> map[i] = ( int* ) malloc ( sizeof ( int ) * m);   //分配 n 个 m 列的数组
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            (*bitmap) -> map[i][j] = 0;
        }
    }
    printf("The disk size is %d bytes. Each blocks has %d bytes !\n", (block_num * BLOCK_SIZE) , BLOCK_SIZE);
    printf("Initialization of bitmap:\n");
    travelBitMap((*bitmap), n, m);
    printf("Memory Initialize successfully ! It has %d blocks.\n",block_num);
}

void travelFile(FCB fcb){
    Block_Node temp = fcb -> first_block;
    while (temp  != NULL){
        printf("%d   ",temp->block_id);
        temp = temp ->next;
    }
    printf("\n");
}
void deleteFile(BitMap bitMap, int n, int m, FCB fcb){

    Block_Node  temp = fcb -> first_block;
    int re_bitmap_id = temp -> block_id;
    updateMap(bitMap, n, m, re_bitmap_id);
    temp = temp ->next;
    while (temp != NULL ){
        re_bitmap_id = temp -> block_id;
        updateMap(bitMap, n, m, re_bitmap_id);
        temp = temp -> next;
    }

    //Todo 依次释放 fcb 指针指向的内存块节点 - DONE 2018.11.28 10:33
    Block_Node _temp = fcb ->first_block;
    free(_temp);
    while (_temp -> next != NULL){
        free(_temp);
        _temp = _temp ->next;
    }
    _temp = NULL;
}


void main(){

    //这个只是一次性的模拟！
    BitMap m1;
    FCB new_file;
    int n = 0 , m = 0;
    printf("Please input the size of bitmap which is rows and columns and separate with a space: \n");
    scanf("%d %d", &n, &m);
    initMap(&m1, n, m);
    createFile(m1, n, m, &new_file);
    printf("You new file block id is :  ");
    travelFile(new_file);

    printf("Chose to delete your file or no ? (Y / N )\n");
    char choice[2];
    scanf("%s", choice);
    if (choice[0] == 'Y'){
        //Todo 删除文件的函数-deletefile() - DONE 2018.11.28 10:33
        //Todo 这里的 choice 使用 scanf() 后，发生了 m 为 0 的错误！- DONE 2018.11.27 22:05
//        printf("Thing going well");
        deleteFile(m1, n, m, new_file);
        new_file ->first_block = NULL; // deleteFile() 中的 fcb 没有用二级指针，这里就用一级指针吧！
    }
}