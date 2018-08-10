/*************************************************************************
	> File Name: hash.c
	> Author: keaidema
	> Mail: 541609206@qq.com
	> Created Time: 2018年07月28日 星期六 16时20分40秒
 ************************************************************************/


#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int ApHash(const char *str) {
    int hash = 0;
    for (int i = 0; str[i]; i++) {
        if (i & 1) {
            hash ^= (hash << 7) ^ str[i] ^ (hash >> 3);
        } else {
            hash ^= (~((hash<< 11) ^ str[i] ^ (hash >> 5)));
        }
    }
    return (hash & 0x7fffffff);
}

int BKDRHash(const char *str) {
    int hash = 0, seed = 131;
    for (int i = 0; str[i]; i++) {
        hash = hash * seed + str[i];
    }
    return hash & 0x7fffffff;
}

int zobrist_table[50][256] = {0};

void init_zobrist_table() {
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 256; j++) {
            zobrist_table[i][j] = rand();
        }
    }
    return ;
}

int ZobristHash(const char *str) {
    static int flag = 1;
    if (flag) {
        flag = 0;
        init_zobrist_table();
    }
    int hash = 0;
    for (int i = 0; str[i]; i++) {
        hash ^= zobrist_table[i][str[i]];
    }
    return hash & 0x7fffffff;
}

int main() {
    char str1[50] = {0}, str2[50] = {0};
    for (int i = 0; i < 16; i++) {
        str1[i] = (i & 1) ? 'a' : 'b';
    }
    for (int i = 0; i < 32; i++) {
        str2[i] = (i & 1) ? 'a' : 'b';
    }
    printf("Aphash=(%s) = %d\n", str1, ApHash(str1));
    printf("Aphash=(%s) = %d\n", str2, ApHash(str2));
    printf("BKDhash=(%s) = %d\n", str1, BKDRHash(str1));
    printf("BKDhash=(%s) = %d\n", str2, BKDRHash(str2));
    printf("ZobristHash=(%s) = %d\n", str1, ZobristHash(str1));
    printf("ZobristHash=(%s) = %d\n", str2, ZobristHash(str2));
    return 0;
}
