#include <stdio.h>
#include <stdlib.h>
#define NMAX 100

int inputNum(int *a);

int inputValues(int **a, int c, int r, int n);

void output(int **a, int c, int r, int n);

int sum(int **a, int stc, int c, int n);

void margeArr(int **a, int str1, int str2, int c, int n);

void sort(int **a, int r, int c, int n);

int main() {
  int n, R, C, flag = 0;
  int *lPtr = 0;
  int **bPtr = 0;
  if (inputNum(&n) || n > 3)
    flag = 2;

  if (inputNum(&R) || inputNum(&C))
    flag = 2;

  if (!flag) {
    switch (n) {
    case 1:
      bPtr = malloc(R * C * sizeof(int) + R * sizeof(int *));
      lPtr = (int *)(bPtr + R);
      for (int i = 0; i < R; ++i)
        bPtr[i] = lPtr + C * i;
      break;
    case 2:
      bPtr = malloc(R * sizeof(int *));
      for (int i = 0; i < R; ++i)
        bPtr[i] = malloc(C * sizeof(int));
      break;
    case 3:
      bPtr = malloc(R * sizeof(int *));
      lPtr = malloc(R * C * sizeof(int));
      for (int i = 0; i < R; ++i)
        bPtr[i] = lPtr + C * i;
      break;

    default:
      flag = 2;
    }
  }

  if ((!flag) && inputValues(bPtr, C, R, n))
    flag = 1;
  if (!flag) {
    sort(bPtr, R, C, n);
    output(bPtr, C, R, n);
  }
  if (flag < 2) {
    switch (n) {
    case 1:
      free(bPtr);
      break;
    case 2:
      for (int i = 0; i < R; ++i)
        free(bPtr[i]);
      free(bPtr);
      break;
    case 3:
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
        if (n == 1 || n == 3)
          *((int *)a + i * c + j) = (int)s;
        if (n == 2)
          a[i][j] = (int)s;
      }
    }
  return flag;
}

void output(int **a, int c, int r, int n) {
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      if ((i == r - 1) && (j == c - 1))
        printf("%d", (n == 1 || n == 3) ? *((int *)a + i * c + j) : a[i][j]);
      else
        printf("%d ", (n == 1 || n == 3) ? *((int *)a + i * c + j) : a[i][j]);
    }
    if (i < r - 1)
      printf("\n");
  }
}

int sum(int **a, int str, int c, int n) {
  int sum = 0;
  for (int i = 0; i < c; ++i)
    sum += (n == 1 || n == 3) ? *((int *)a + c * str + i) : a[str][i];
  return sum;
}

void margeArr(int **a, int str1, int str2, int c, int n) {
  int *tmp1 = (int *)calloc(c, sizeof(int));
  int *tmp2 = (int *)calloc(c, sizeof(int));
  for (int i = 0; i < c; ++i) {
    tmp1[i] = (n == 1 || n == 3) ? *((int *)a + c * str1 + i) : a[str1][i];
    (tmp2[i] = (n == 1 || n == 3) ? *((int *)a + c * str2 + i) : a[str2][i]);
  }
  for (int i = 0; i < c; ++i)
    if (n == 1 || n == 3)
      *((int *)a + c * str1 + i) = tmp2[i];
    else
      a[str1][i] = tmp2[i];

  for (int i = 0; i < c; ++i)
    if (n == 1 || n == 3)
      *((int *)a + c * str2 + i) = tmp1[i];
    else
      a[str2][i] = tmp1[i];

  free(tmp2);
  free(tmp1);
}

void sort(int **a, int r, int c, int n) {
  for (int i = 0; i < r - 1; ++i) {
    for (int j = 0; j < r - i - 1; ++j) {
      if (sum(&a[0], j, c, n) > sum(&a[0], j + 1, c, n)) {
        margeArr(&a[0], j, j + 1, c, n);
      }
    }
  }
}
