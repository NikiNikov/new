#include <stdio.h>
#define N 15
#define M 13

void transform(int *buf, int **matr, int n, int m);
void make_picture(int **picture, int n, int m);
void reset_picture(int **picture, int n, int m);
void print_picture(int **picture, int n, int m);
int main() {
  int picture_data[N][M];
  int *picture[N];
  transform(*picture_data, picture, N, M);

  make_picture(picture, N, M);
  print_picture(picture, N, M);
}

void make_picture(int **picture, int n, int m) {
  int frame_w[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  int frame_h[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
  int tree_trunk[] = {7, 7, 7, 7};
  int tree_foliage[] = {3, 3, 3, 3};
  int sun_data[6][5] = {{0, 6, 6, 6, 6}, {0, 0, 6, 6, 6}, {0, 0, 6, 6, 6},
                        {0, 6, 0, 0, 6}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};

  reset_picture(picture, n, m);

  int length_tree_tr = sizeof(tree_trunk) / sizeof(tree_trunk[0]);
  int length_tree_fol = sizeof(tree_foliage) / sizeof(tree_foliage[0]);
  for (int i = 0; i < length_tree_tr; i++) {
    picture[3][i + 2] = tree_foliage[i];
    picture[4][i + 2] = tree_foliage[i];
    picture[i + 2][3] = tree_foliage[i];
    picture[i + 2][4] = tree_foliage[i];
  }

  for (int i = 0; i < length_tree_fol; i++) {
    picture[6 + length_tree_tr][i + 2] = tree_trunk[i];
    picture[i + 2 + length_tree_tr][3] = tree_trunk[i];
    picture[i + 2 + length_tree_tr][4] = tree_trunk[i];
  }

  for (int i = 1; i < n / 2 - 1; i++) {
    for (int j = m / 2 + 1; j < n - 1; j++) {
      picture[i][j] = sun_data[i - 1][j - m / 2 - 1];
    }
  }

  int length_frame_w = sizeof(frame_w) / sizeof(frame_w[0]);
  int length_frame_h = sizeof(frame_h) / sizeof(frame_h[0]);

  for (int i = 0; i < length_frame_w; i++) {
    picture[0][i] = frame_w[i];
    picture[n / 2][i] = frame_w[i];
    picture[n - 1][i] = frame_w[i];
  }

  for (int i = 0; i < length_frame_h; i++) {
    picture[i][0] = frame_h[i];
    picture[i][m / 2] = frame_h[i];
    picture[i][m - 1] = frame_h[i];
  }
}

void print_picture(int **picture, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d ", picture[i][j]);
    }
    printf("\n");
  }
}

void reset_picture(int **picture, int n, int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      picture[i][j] = 0;
    }
  }
}

void transform(int *buf, int **matr, int n, int m) {
  for (int i = 0; i < n; i++) {
    matr[i] = buf + i * m;
  }
}
