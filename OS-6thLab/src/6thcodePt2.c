//
// Created by Jalr on 2018/11/26.
//

#include <stdio.h>
#include <malloc.h>

//
// Created by Jalr on 2018/11/26.
//

/**
 * 位示图:   m 行 n列的数组来表示位示图
 */
#define BLOCK_SIZE 8 //定义一个盘块占 8 字节
#define FILE_NAME_LENGTH 10 //文件名最长 10 个字节
typedef struct {
    int **map;              //这里直接用整型来表示位示图的状态了
}*BitMap, _BitMap;

/**
 * 物理盘块，简化到只有一个 size
 */
typedef struct {
    int size;
}Block_Node;

/**
 * FCB，直接采用隐式链接分配方式，包含文件名
 */
typedef struct {
    char name[FILE_NAME_LENGTH];
    Block_Node* next;
}*FCB;


void travelBitMap();

//为 bitmap分配 m行，n列的大小
void initMap(BitMap *bitmap, int m, int n){
    int block_num = m*n;
    *bitmap = (BitMap) malloc(sizeof(_BitMap));//首先为位示图分配内存
    (*bitmap) -> map = ( int** ) malloc ( sizeof( int* ) * m ); //分配一个 m 行的数组
    for(int i = 0; i < m; i++){
        (*bitmap) -> map[i] = ( int* ) malloc ( sizeof ( int ) * n);   //分配 m 个 n 列的数组
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            (*bitmap) -> map[i][j] = 0;
        }
    }
    printf("The disk size is %d bytes. Each blocks has %d bytes !\n", (block_num * BLOCK_SIZE) , BLOCK_SIZE);
    printf("Initialization of bitmap:   \n");
    travelBitMap((*bitmap), m, n);
    printf("Memory Initialize successfully ! It has %d blocks.\n",block_num);
}

void initFCB(){

}



//释放 bitmap 内存，需要行数即可，释放每一行的头指针
void freeMap(BitMap bitMap, int m){
    for(int i = 0; i < m; i++){
        free(bitMap -> map[i]);    //释放行指针
    }
    free(bitMap -> map);           //释放列指针
}

void travelBitMap(BitMap bitMap,int m, int n){
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d  ", bitMap -> map[i][j]);
        }
        printf("\n");
    }
}

void updateMap(BitMap bitmap, int m, int n){

    printf("Bitmap status:   \n");
    travelBitMap(bitmap, m, n);
}



void main(){

    BitMap m1;
    int n = 0 , m = 0;
    printf("Please input the size of bitmap which is rows and columns and separate with a space: \n");
    scanf("%d %d", &n, &m);
    initMap(&m1, n, m);
//    updateMap(m1, n, m);
}
