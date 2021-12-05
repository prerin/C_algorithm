//
//  sort_collection.c
//  
//
//  Created by 川上隼 on 2021/12/05.
//

#include "sort_collection.h"
#include "sort_collection.h"
#include <stdio.h>
#include <stdlib.h>

unsigned long compare_count = 0;

void cmp_cnt_rest(void) {
  compare_count = 0;
}

int compare(int ldata, int rdata) {
  compare_count++;
  if      (ldata  < rdata) return -1;
  else if (ldata == rdata) return  0;
  else                     return  1;
}

void swap(int a[], int lidx, int ridx) {
  int temp = a[lidx];
  a[lidx] = a[ridx];
  a[ridx] = temp;
}

void display(int a[], int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

void selection_sort(int a[], int n) {
  int i, j;
  for (i = 0; i < n - 1; i++) {
    int min = i;
    for (j = i + 1; j < n; j++) {
      if (compare(a[j], a[min]) == -1) {
        min = j;
      }
    }
    swap(a, i, min);
  }
}

// Insertion sort
/**************************************/
void insertion_sort(int a[], int n) {
    for (int i=1; i<n; i=i+1) {
        int k = a[i];
        int j = i-1;
        while(j >= 0 && compare(k, a[j]) == -1) {
            a[j+1] = a[j];
            j = j - 1;
        }
        a[j+1] = k;
    }
}

// Functions for Heap sort
/**************************************/
void sift_down(int a[], int i, int n) {
    int snode;
    int svalue;
    while(i < n/2-1) {
        if (2*i+1 == n-1) {
            snode = 2*i+1;
            svalue = a[2*i+1];
        } else {
            if (compare(a[2*i+1], a[2*i+2]) == -1) {
                snode = 2*i+2;
                svalue = a[2*i+2];
            } else {
                snode = 2*i+1;
                svalue = a[2*i+1];
            }
        }
        if (compare(a[i], svalue) == -1) {
            a[snode] = a[i];
            a[i] = svalue;
            i = snode;
        } else return;
        return;
    }
}

void build_heap (int a[], int n) {
    for (int x = n/2-1; x >= 0; x = x-1){
        sift_down(a, x, n);
    }
}

void heap_sort (int a[], int n) {
    build_heap(a, n);
    for (int m = n-1; m > 0; m = m-1) {
        swap(a, 0, m);
        sift_down(a, 0, m);
    }
}

// Functions for Quick sort
/**************************************/
int partition(int a[], int pivot, int left, int right) {
    swap(a, right, pivot);
    int l = left;
    int r = right - 1;
    while(1) {
        while (compare(a[l] , a[right]) == -1) l = l + 1;
        while (l <= r && compare(a[r] , a[right]) != -1) r = r - 1;
        if(l < r) swap(a, l, r);
        else break;
    }
    swap(a, l, right);
    return l;
}
 
void quick_sort(int a[], int left, int right) {
    if (left < right) {
        int pivot = (left + right) / 2;
        int p = partition(a, pivot, left, right);
        quick_sort(a, left, p-1);
        quick_sort(a, p+1, right);
    }
}

void q_sort(int a[], int n) {
  quick_sort(a, 0, n-1);
}

//Functions for radix_sort
//************************
void buket_sort(A) {
    int len = sizeof(A) / sizeof(int);
    int Q[9];
    for (int i = 0; i < len; i = i + 1) {
        for (int j; j < len; j = j + 1) {
            if (A[i] == j)
        }
    }
}

int GetRandom(int min, int max) {
  return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

int main(int argc, char *argv[]) {
  if (argc != 1) {
      long cpu_time;
      double sec;
      int numdata = atoi(argv[1]);  // set numdata with cmd. argument
      int *array = (int*)malloc(sizeof(int) * numdata);
      int i;
      printf("Enter %d integers\n", numdata);
      for (i = 0; i < numdata; i++) {
        scanf("%d", &array[i]);  // enter integers
      }
      insertion_sort(array, numdata);
      printf("sorting result\n");
      printf("insertion_sort:");
      display(array, numdata);
      printf("# of comparisons: %lu\n", compare_count);
      free(array);
      cpu_time = clock();
      sec = (double)cpu_time / CLOCKS_PER_SEC;
      printf("%f秒\n", sec);
  } else {
//      基本課題5-2-1用
//      int numdata;
//      for (numdata = 1000; numdata <= 10000; numdata += 1000) {  // numdata is 1000, 2000, ..., 10,000
//
//      int *array = (int*)malloc(sizeof(int) * numdata);
//      int i;
//      for (i = 0; i < numdata; i++) {
//        array[i] = GetRandom(0, (numdata * 10 - 1));  // random number from 0 to numdata * 10 - 1
//      }
//      q_sort(array, numdata);
//      printf("%d %lu\n", numdata, compare_count);
//      cmp_cnt_rest();
//      free(array);
//  }
//      -----------------------------------------------------
//      基本課題5-2-2用
      int numdata = 10;
      int i;
      long cpu_time;
      double sec;
      
      int *array = (int*)malloc(sizeof(int) * numdata);
      for (i = 0; i < numdata; i++) {
        array[i] = GetRandom(0, (numdata * 10 - 1));
      }
      q_sort(array, numdata);
      cmp_cnt_rest();
      free(array);
      cpu_time = clock();
      sec = (double)cpu_time / CLOCKS_PER_SEC;
      printf("%f秒\n", sec);
  }

  return EXIT_SUCCESS;
}
