//
//  knapsack.c
//  
//
//  Created by 川上隼 on 2021/12/05.
//
// ナップサック問題というリュックの中身に入れられる量で中身の重みを最大にするという問題を動的計画法で解いていくコードです

#include "knapsack.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool* knapsack(int v[], int w[], int n, int C) {
    int G[n+1][C+1];
    bool S[n+1][C+1];
    bool* SS = (bool*)malloc(sizeof(bool) * (n + 1));
    if (n == 0) return 0;
    for (int x = 0; x <= n; x++) {
        SS[x] = false;
        for (int y = 0; y <= C; y++) {
            G[x][y] = 0;
            S[x][y] = false;
        }
    }
    int t;
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= C; y++){
            if (y < w[x]) {
                G[x][y] = G[x-1][y];
            } else {
                t = G[x-1][y-w[x]] + v[x];
                if (G[x-1][y] < t) {
                    G[x][y] = t;
                    S[x][y] = true;
                } else {
                    G[x][y] = G[x-1][y];
                }
            }
        }
    }
    int x = n;
    int y = C;

    while(x > 0) {
        if (S[x][y]) {
            SS[x] = true;
            y -= w[x];
            x -= 1;
        } else {
            x -= 1;
        }
    }
    return SS;
}

int main(int argc, char** argv) {
  int num = 10;
  int v[] = {0, 250, 380, 420, 520, 580, 700, 720, 980, 20, 2000};
  int w[] = {0, 1, 2, 4, 3, 4, 6, 5, 7, 1, 10};

    if (argc == 3) {
        int n = atoi(argv[1]);
        int C = atoi(argv[2]);
        bool* S = knapsack(v, w, n, C);
        int total = 0;
        for (int k = 1; k <= num; k++) {
            if (S[k]) {
                total = total + v[k];
                printf("重さ %d 価値 %d\n", w[k], v[k]);
            }
        }
      printf("合計価値 %d\n", total);
  } else {
    fprintf(stderr, "Usage: knapsackDP2 <k: no. of items> <i: capacity>\n");
    return 1;
  }
  return 0;
}
