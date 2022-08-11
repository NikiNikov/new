#include <stdio.h>
#include <stdlib.h>
#define NMAX 100

int sum(int **matrix_first, int r_1, int c_1, int **matrix_second, int r_2,
        int c_2, int ***matrix_result, int *r_result, int *c_result);

int mul(int **matrix_first, int r_1, int c_1, int **matrix_second, int r_2,
        int c_2, int ***matrix_result, int *r_result, int *c_result);

int transpose(int **matrix, int r, int c, int ***matrix_result, int *r_result,
              int *c_result);

int inputNum(int *n);

int input(int ***matrix, int *c, int *r);

void output(int **matrix, int c, int r);

int main() {
  int n, out_n, flag = 0;
  int R[3], C[3];
  int ***bPtr = 0;
  //  int **bPtrN = 0;
  if (inputNum(&n) || n > 3)
    flag = 2;

  if (!flag) {
    bPtr = (int ***)malloc(3 * sizeof(int **));
    switch (n) {
    case 1:
      for (int i = 0; i < 2; i++)
        if ((!flag) && input(&bPtr[i], &C[i], &R[i]))
          flag = 1;
      if (R[0] != R[1] || C[0] != C[1])
        flag = 1;
      break;
    case 2:
      for (int i = 0; i < 2; i++)
        if ((!flag) && input(&bPtr[i], &C[i], &R[i]))
          flag = 1;

      break;
    case 3:
      if ((!flag) && input(&bPtr[0], &C[0], &R[0]))
        flag = 1;
      break;
    }
  }
  if (!flag) {
    switch (n) {
    case 1:
      if (sum(bPtr[0], R[0], C[0], bPtr[1], R[1], C[1], &bPtr[2], &R[2], &C[2]))
        flag = 1;
      out_n = 2;
      break;
    case 2:
      if (mul(bPtr[0], R[0], C[0], bPtr[1], R[1], C[1], &bPtr[2], &R[2], &C[2]))
        flag = 1;
      out_n = 2;
      break;
    case 3:
      transpose(bPtr[0], R[0], C[0], &bPtr[1], &R[1], &C[1]);
      out_n = 1;
      break;
    }
  }

  if (!flag)
    output(bPtr[out_n], C[out_n], R[out_n]);

  if (flag < 2) {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < R[i]; ++j)
        free(bPtr[i][j]);
      free(bPtr[i]);
    }
    free(bPtr);
  }
  if (flag) {
    printf("n/a");
  }
  return flag;
}

int mul(int **matrix_first, int r_1, int c_1, int **matrix_second, int r_2,
        int c_2, int ***matrix_result, int *r_result, int *c_result) {
  int flag = 0;
  if (c_1 != r_2)
    flag = 1;

  if (!flag) {
    *r_result = r_1;
    *c_result = c_2;

    (*matrix_result) = (int **)malloc(*r_result * sizeof(int *));
    for (int j = 0; j < *r_result; ++j)
      (*matrix_result)[j] = (int *)malloc(*c_result * sizeof(int));

    for (int row = 0; row < *r_result; row++) {
      for (int col = 0; col < *c_result; col++)
        for (int inner = 0; inner < c_1; inner++)
          (*matrix_result)[row][col] +=
              matrix_first[row][inner] * matrix_second[inner][col];
    }
  }
  return flag;
}

int transpose(int **matrix, int r, int c, int ***matrix_result, int *r_result,
              int *c_result) {
  *matrix_result = (int **)malloc(c * sizeof(int *));
  for (int j = 0; j < c; ++j)
    (*matrix_result)[j] = (int *)malloc(r * sizeof(int));

  *r_result = c;
  *c_result = r;

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++)
      (*matrix_result)[j][i] = matrix[i][j];
  }

  return 0;
}

int sum(int **matrix_first, int r_1, int c_1, int **matrix_second, int r_2,
        int c_2, int ***matrix_result, int *r_result, int *c_result) {
  int flag = 0;

  if (c_1 != c_2 || r_1 != r_2) {
    flag = 1;
  } else {
    *matrix_result = (int **)malloc(r_1 * sizeof(int *));
    for (int j = 0; j < r_1; ++j)
      (*matrix_result)[j] = (int *)malloc(c_1 * sizeof(int));

    *r_result = r_1;
    *c_result = c_1;
  }

  if (!flag) {
    for (int x = 0; x < r_1; x++) {
      for (int y = 0; y < c_1; y++) {
        (*matrix_result)[x][y] = matrix_first[x][y] + matrix_second[x][y];
      }
    }
  }
  return flag;
}

int inputNum(int *n) {
  int flag = 0;
  if (scanf("%d", n) != 1 || *n < 1) {
    flag = 2;
  }
  return flag;
}

int input(int ***matrix, int *c, int *r) {
  float s;
  int flag = inputNum(r);
  if (!flag)
    flag = inputNum(c);

  if (!flag) {
    *matrix = (int **)calloc(*r, sizeof(int *));
    for (int j = 0; j < *r; ++j)
      (*matrix)[j] = (int *)calloc(*c, sizeof(int));

    for (int i = 0; i < *r; ++i)
      for (int j = 0; j < *c; ++j) {
        if ((!flag && !scanf("%f", &s)) || (s != (int)s)) {
          flag = 1;
        } else {
          (*matrix)[i][j] = (int)s;
        }
      }
  }
  return flag;
}

void output(int **matrix, int c, int r) {
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j) {
      if ((i == r - 1) && (j == c - 1))
        printf("%d", matrix[i][j]);
      else
        printf("%d ", matrix[i][j]);
    }
      if (i < r - 1)
    printf("\n");
  }
}
