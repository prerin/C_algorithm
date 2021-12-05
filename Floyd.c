//
//  Floyd.c
//  
//
//  Created by 川上隼 on 2021/12/05.
//
//ワーシャルフロイド法というグラフ理論における辺の重みが非負のときの単一始点最短経路問題を解くための
//裁量優先探索によるアルゴリズムを実装しているコードです。

#include "Floyd.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

extern int w[N][N];
extern int d[N][N];
extern int p[N][N];

void Floyd() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            d[i][j] = w[i][j];
            p[i][j] = i;
        }
    }
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int can = d[i][k] + d[k][j];
                if (can < d[i][j] && can > 0) {
                    d[i][j] = can;
                    p[i][j] = p[k][j];
                }
            }
        }
    }
}


void display(char* name, int length, int k) {
  printf("%s: [", name);
  for (int i = 0; i < length; i++) {
    if (d[k][i] == M)
      printf(" M");
    else
      printf(" %d", d[k][i]);
  }
  printf(" ]\n");
}

void shortest_path(int k) {
    
    for (int x=0; x<N; x++) {
        int P[N];
        for (int x=0; x<N; x++) {
            P[x] = -1;
        }
        int l = 0;
        int i = x;
        printf("頂点%dの最短路は：", i);
        do {
            P[l] = p[k][i];
            i = p[k][i];
            l++;
        } while(i != k);
        for (int t = N-1; t>=0; t=t-1) {
            if(P[t] != -1) printf(" %d ", P[t]);
        }
        if (x != k) printf(" %d ", x);
        printf("\n");
    }
}
