//
//  string_collaction.c
//  
//
//  Created by 川上隼 on 2021/12/05.
//
//与えられた文字列の記述してあるファイルを読み込み文字列照合を行うコードです

#include "string_collaction.h"
#include <stdlib.h>
#include <stdbool.h>

//指定のファイルを読み込む関数
int readFile(char* path, char* str) {
  FILE* fp = NULL;

  fp = fopen(path, "r");
  if ((fp = fopen(path, "r")) == NULL) {
    perror("Cannot not open file");
    exit(1);
  }

  int len = 0;
  while (!feof(fp))
    str[len++] = (char)fgetc(fp);
  fclose(fp);
  str[--len] = '\0';
  return len;
}

//文字を比較する関数
bool cmp(char a, char b) {
  if (isVerbose)
    fprintf(stderr, "cmp(%c, %c)\n", a, b);
  Ncmp++;
  if (a == b)
    return true;
  else
    return false;
}

//文字列照合を行う関数
int naive(char* text, unsigned int textlen, char* pat, unsigned int patlen) {
    int i = 0;
    int j = 0;
    int n = textlen;
    int m = patlen;
    while (j < n) {
        if (cmp(pat[i], text[j]) == false) {
            j = j - i + 1;
            i = 0;
        } else {
            if (i == m - 1)
                return j - m + 1;
            else {
                i++;
                j++;
            }
        }
    }
    return -1;
}

//ここからは実際に文字列照合を動かしていく
#define PAT_MAX 256     // パターンの最大の長さ
#define TEXT_MAX 1024 * 1024 * 10 // テキストの最大の長さ（10 MB）

int main(int argc, char** argv) {
  char pat[PAT_MAX];    // 検索パターン
  char* text = (char *)malloc(TEXT_MAX * sizeof(char));
  int patlen = 0;
  int textlen = 0;

  // 引数処理・ファイル読み込み
  if (argc < 3 || 4 < argc) {
    fprintf(stderr, "Usage: ./main [-v] <text file> <pattern file>\n");
    return 1;
  }
  int i = 1;
  if (strcmp(argv[i], "-v") == 0) {
    isVerbose = true;
    i++;
  }
  textlen = readFile(argv[i++], text);
  patlen = readFile(argv[i], pat);

  // pat 末尾の改行コードを削除
  while (pat[patlen - 1] == '\r' || pat[patlen - 1] == '\n')
    pat[--patlen] = '\0';

  // 文字列照合・結果表示
  if (isVerbose) {
    printf("text size: %d\n", textlen);
    printf("pattern size: %d\n", patlen);
  }
  printf("Pattern found at %d.\n", naive(text, textlen, pat, patlen));
  if (isVerbose)
    printf("# of comparisons: %d.\n", Ncmp);

    free(text);

  return 0;
}
