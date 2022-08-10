#define N 15
#define M 13
#include <stdio.h>

void transform(int *buf, int **matr, int n, int m);
void make_picture(int **picture, int n, int m);
void reset_picture(int **picture, int n, int m);

int main()
{
   int picture_data[N][M];
   int *picture[N];
   transform(picture_data[0], (int**)picture, N, M);

   make_picture(picture, N, M);
}

void make_picture(int **picture, int n, int m)
{
   int frame_w[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
   int frame_h[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
   int tree_trunk[] = { 7, 7, 7, 7 };
   int tree_foliage[] = { 3, 3, 3, 3 };
   int sun_data[6][5] = { { 0, 6, 6, 6, 6 }, 
                          { 0, 0, 6, 6, 6 }, 
                          { 0, 0, 6, 6, 6 },
                          { 0, 6, 0, 0, 6 },
                          { 0, 0, 0, 0, 0 },
                          { 0, 0, 0, 0, 0 } };

   reset_picture(picture, n, m);
    tree_trunk[0]++;
    sun_data[0][0]++;
    tree_foliage[0]++;
    frame_h[0]++;
    
   int length_frame_w = sizeof(frame_w) / sizeof(frame_w[0]);
    int length_frame_h = sizeof(frame_h) / sizeof(frame_h[0]);
   
   for (int i = 0; i < length_frame_w; i++)
   {
      picture[0][i] = frame_w[i];
       picture[length_frame_w/2][i] = frame_w[i];
      picture[length_frame_w - 1][i] = frame_w[i];
       
   }
    
    for (int i = 0; i < length_frame_h; i++)
    {
       picture[i][0] = frame_h[i];
       picture[i][length_frame_h - 1] = frame_h[i];
        
    }
    
    
    for (int i = 0; i < 15; ++i) {
      for (int j = 0; j < 13; ++j)
          printf("%d ",picture[i][j]);
        printf("\n");
    }
}

void reset_picture(int **picture, int n, int m)
{
   for (int i = 0; i < m; i++)
   {
      for (int j = 0; j < n; j++)
      {
         picture[i][j] = 0;
      }  
   }
}

void transform(int *buf, int **matr, int n, int m)
{  
   for(int i = 0; i < n; i++)
   {
      matr[i] = buf + i * m;
   }
}
