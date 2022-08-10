#include <stdio.h>
#include <stdlib.h>
#define NMAX 10

int inputNum(int *a);

int inputValues(int *a, int n);

void output(int *a, int n);

void sort(int *a, int n);

int main() {
  int n, flag = 0;
  int *data = 0;
  if (inputNum(&n))
    flag = 2;
  else
    data = (int *)calloc(n, sizeof(int));

  if (!flag && inputValues(data, n))
    flag = 1;

  if (!flag) {
    sort(data, n);
    output(data, n);
  }
  if (flag < 2)
    free(data);

  if (flag) {
    printf("n/a");
  }
  return flag;
}

int inputNum(int *n) {
  int flag = 0;
  if (scanf("%d", n) != 1 || *n > NMAX || *n < 1) {
    flag = 1;
  }
  return flag;
}

int inputValues(int *a, int n) {
  int flag = 0;
  for (int *p = a; p - a < n; p++) {
    if (!scanf("%d", p))
      flag = 1;
  }
  return flag;
}

void output(int *a, int n) {
  for (int *p = a; p - a < n - 1; p++) {
    printf("%d ", *p);
  }
  printf("%d", *(a + n - 1));
}

void sort(int *a, int n) {
  int tmp;
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < n - i - 1; ++j) {
      if (a[j] > a[j + 1]) {
        tmp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = tmp;
      }
    }
  }
}
