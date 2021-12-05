//
//  dijstra.c
//  
//
//  Created by 川上隼 on 2021/12/05.
//
//ダイクストラ法というグラフ理論における辺の重みが非負のときの単一始点最短経路問題を解くための
//裁量優先探索によるアルゴリズムを実装しているコードです。

#include <stdio.h>
#include "dijkstra.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

extern int w[N][N];
extern bool S[N];
extern int Scount;
extern int d[N];
extern int parent[N];


void add(int u, bool S[]) {．
    S[u] = true;
}


static bool remain() {
    for (int x = 0; x < N; x++) {
        if (S[x] == false) return true;
    }
    return false;
}


int select_min(int p) {
    int k;
    int i;
    for (i=0; i<N; i++) {
        if (S[i] == false) {
            k = i;
            break;
        }
    }
    for (i=0; i<N; i++) {
        if (d[k] > d[i] && S[i] == false) k = i;
    }
    if (k != p) return k;
    for (i=0; i<N; i++) {
        if (d[i] == M && S[i] == false) return i;
    }
    return -1;
}

bool member(int u, int x) {
    if (w[u][x] != M) return true;
    return false;
}


void dijkstra(int p) {
    add(p, S);

    for (int i = 0; i < N; i++) {
        d[i] = w[p][i];
        parent[i] = p;
    }

    while (remain()) {
        int u = select_min(p);
        if (u == -1) break;
        else add(u, S);

        for (int x = 0; x < N; x++) {
            if (member(u, x)) {
                int k = d[u] + w[u][x];
                if (k < d[x] && d[x] > 0 && k > 0) {
                    d[x] = k;
                    parent[x] = u;
                }
            }
        }
    }
}

void display(char* name, int* ary, int length) {
  printf("%s: [", name);
  for (int i = 0; i < length; i++) {
    if (ary[i] == M)
      printf(" M");
    else
      printf(" %d", ary[i]);
  }
  printf(" ]\n");
}

void shortest_path(int p) {
    
    for (int x=0; x<N; x++) {
        int P[N];
        for (int x=0; x<N; x++) {
            P[x] = -1;
        }
        int l = 0;
        int i = x;
        printf("頂点%dの最短路は：", i);
        do {
            P[l] = parent[i];
            i = parent[i];
            l++;
        } while(i != p);
        for (int t = N-1; t>=0; t=t-1) {
            if(P[t] != -1) printf(" %d ", P[t]);
        }
        if (x != p) printf(" %d ", x);
        printf("\n");
    }
}

#実際にグラフを作って、プログラムを動かしてみる
int w[N][N] = {
   { 0,  M, 10,  M,  M, 30},
   {10,  0, 50,  M,  M,  M},
   { M,  M,  0,  M,  M, 10},
   {70,  M, 40,  0, 40,  M},
   { M,  M,  M, 20,  0,  M},
   { M, 60,  M,  M, 10,  0},
};

bool S[N];
int Scount = 0;                      // 頂点集合Sの要素数
int d[N];
int parent[N];

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: ./main <node ID>\n");
    return 1;
  }

  int p = atoi(argv[1]);
  if (p < 0 || N <= p) {
    fprintf(stderr, "Node ID %d is out of range: [0, %d].\n", p, N);
    return 1;
  }

  for (int i = 0; i < N; i++)
    S[i] = false;


  dijkstra(p);              // ダイクストラ法による最短路の計算
  display("Result", d, N);  // 結果表示
    shortest_path(p);
    

  return 0;
}
