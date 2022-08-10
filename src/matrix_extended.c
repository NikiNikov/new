#include <stdio.h>
#include <stdlib.h>
#define NMAX 100

int inputNum(int *a);

int inputValues(int **a, int c, int r, int n);

void output(int **a, int c, int r, int n, int *max, int *min);

void maxmin(int **a, int c, int r, int n, int *max, int *min);

int main() {
  int data[NMAX][NMAX];
  int n, R, C, flag = 0;
  int *lPtr = 0;
  int *max = 0;
  int *min = 0;
  int **bPtr = 0;
  if (inputNum(&n) || n > 4)
    flag = 2;

  if (inputNum(&R) || inputNum(&C) || (n == 1 && (R > 100 || C > 100)))
    flag = 2;

  if (!flag) {
    max = (int *)calloc(R, sizeof(int));
    min = (int *)calloc(C, sizeof(int));
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
    maxmin(bPtr, C, R, n, max, min);
    output(bPtr, C, R, n, max, min);
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

void output(int **a, int c, int r, int n, int *max, int *min) {
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      if ((i == r - 1) && (j == c - 1))
        printf("%d", n < 3 ? *((int *)a + i * c + j) : a[i][j]);
      else
        printf("%d ", n < 3 ? *((int *)a + i * c + j) : a[i][j]);
    }
    printf("\n");
  }

  for (int i = 0; i < r - 1; ++i)
    printf("%d ", max[i]);
  printf("%d\n", max[r - 1]);
  for (int i = 0; i < c - 1; ++i)
    printf("%d ", min[i]);
  printf("%d", min[c - 1]);
}

void maxmin(int **a, int c, int r, int n, int *max, int *min) {
  for (int i = 0; i < r; ++i)
    max[i] = n < 3 ? *((int *)a + i * c) : a[i][0];

  for (int i = 0; i < c; ++i)
    min[i] = n < 3 ? *((int *)a + 1 * c + i) : a[0][i];

  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      int p = n < 3 ? *((int *)a + i * c + j) : a[i][j];
      if (p > max[i])
        max[i] = p;
    }
  }

  for (int i = 0; i < c; ++i) {
    for (int j = 0; j < r; ++j) {
      int p = n < 3 ? *((int *)a + j * r + i) : a[j][i];
      if (p < min[i])
        min[i] = p;
    }
  }
}
