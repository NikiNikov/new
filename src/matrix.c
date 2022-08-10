#include <stdio.h>
#include <stdlib.h>
#define NMAX 100

int inputNum(int *a);

int inputValues(int **a, int c, int r, int n);

void output(int **a, int c, int r, int n);

int main() {
  int data[NMAX][NMAX];
  int n, R, C, flag = 0;
  int *lPtr = 0;
  int **bPtr = 0;
  if (inputNum(&n) || n > 4)
    flag = 2;

  if (inputNum(&R) || inputNum(&C) || (n == 1 && (R > 100 || C > 100)))
    flag = 2;

  if (!flag) {
    switch (n) {
    case 1:
      bPtr = (int **)data;
      break;
    case 2:
      bPtr = malloc(R * C * sizeof(int) + R * sizeof(int *));
      lPtr = (int *)(bPtr + R);
      for (int i = 0; i < C; ++i)
        bPtr[i] = lPtr + C * i;
      break;
    case 3:
      bPtr = malloc(R * sizeof(int *));
      for (int i = 0; i < C; ++i)
        bPtr[i] = malloc(C * sizeof(int));
      break;
    case 4:
      bPtr = malloc(R * sizeof(int *));
      lPtr = malloc(R * C * sizeof(int));
      for (int i = 0; i < C; ++i)
        bPtr[i] = lPtr + C * i;
      break;

    default:
      flag = 2;
    }
  }

  if ((!flag) && inputValues(bPtr, C, R, n))
    flag = 1;
  if (!flag) {
    output(bPtr, C, R, n);
  }
  if (flag < 2) {
    switch (n) {
    case 2:
      free(bPtr);
      break;
    case 3:
      for (int i = 0; i < C; ++i)
        free(bPtr[i]);
      free(bPtr);
      break;
    case 4:
      free(lPtr);
      free(bPtr);
      break;
    }
  }

  if (flag) {
    printf("n/a");
  }
  return flag;
}

int inputNum(int *n) {
  int flag = 0;
  if (scanf("%d", n) != 1 || *n < 1) {
    flag = 1;
  }
  return flag;
}

int inputValues(int **a, int c, int r, int n) {
  int flag = 0;
  float s;
  for (int i = 0; i < r; ++i)
    for (int j = 0; j < c; ++j) {
      if ((!flag && !scanf("%f", &s)) || (s != (int)s)) {
        flag = 1;
      } else {
        if (n == 1 || n == 2)
          *((int *)a + i * c + j) = (int)s;
        if (n == 3 || n == 4)
          a[i][j] = (int)s;
      }
    }
  return flag;
}

void output(int **a, int c, int r, int n) {
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      if ((i == r - 1) && (j == c - 1))
        printf("%d", n < 3 ? *((int *)a + i * c + j) : a[i][j]);
      else
        printf("%d ", n < 3 ? *((int *)a + i * c + j) : a[i][j]);
    }
    if (i < r - 1)
      printf("\n");
  }
}
