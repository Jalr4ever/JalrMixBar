#include <stdio.h>
#include <malloc.h>

//
// Created by Jalr on 2018/11/26.
//

/**
 * 位示图结构，m 行 n列的数组来表示位示图
 */
typedef struct {
    int **map;              //这里直接用整型来表示位示图的状态了
}BitMap;

//为 bitmap分配 m行，n列的大小
void initMap(BitMap *bitmap, int m, int n){
    printf("2.In initMap() and before allocate memory ---  %d \n",bitmap);
    bitmap = (BitMap*) malloc (sizeof(BitMap));//首先为位示图分配内存
    printf("3.In initMap() and after allocate memory ---  %d \n",bitmap);
    (*bitmap) . map = ( int** ) malloc ( sizeof( int* ) * m ); //分配一个 m 行的数组
    for(int i = 0; i < m; i++){
        (*bitmap) . map[i] = ( int* ) malloc ( sizeof ( int ) * n);   //分配 m 个 n 列的数组
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            (*bitmap) . map[i][j] = 6;
        }
    }
}

//释放 bitmap 内存，需要行数即可，释放每一行的头指针
void freeMap(BitMap bitMap, int m){
    for(int i = 0; i < m; i++){
        free(bitMap . map[i]);    //释放行指针
    }
    free(bitMap . map);           //释放列指针
}

void travelBitMap(BitMap *bitMap,int m, int n){
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d   \t", (*bitMap) . map[i][j]);
        }
    }
}

void main(){
    BitMap m1;
    int n = 3, m = 4;
//    scanf("%d %d", &n, &m);
printf("1.Before go into initMap() --- %d \n", &m1);
    initMap(&m1, n, m);
//    travelBitMap(&m1, n, m);

}








