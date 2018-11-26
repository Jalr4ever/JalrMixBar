//
// Created by Jalr on 2018/11/26.
//

#include <stdio.h>

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

//返回第一个可用的 行列，下表
int checkBitMap(BitMap bitMap, int n, int m){
    int avail_block_id = -1;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if(bitMap -> map[i][j] == 0)
                avail_block_id = i * n + j; //这个公式应该根据 字号，位号，盘块号从 0 或 1开始判断的，这时都从0开始的情况
        }
    }
    return avail_block_id;
}

void createFile(BitMap bitMap, int n, int m){

    int avail_block = checkBitMap(bitMap, n, m);

    if(avail_block == -1){
        printf("Disk is full.Try delete a file first!");
    }
    else{
        FCB b1 = (b1);

    }

}


void deleteFile(){

}

void main(){

}