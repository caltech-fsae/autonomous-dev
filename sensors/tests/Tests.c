# include <stdio.h>
# include "matrix_ops.c"

int main() {
  /* Test for multiplication. */
  Matrix A;
  Matrix B;
  A.mat[0][0] = 1;
  A.mat[0][1] = 2;
  A.mat[1][0] = 1;
  A.mat[1][1] = 2;
  B.mat[0][0] = 1;
  B.mat[0][1] = 2;
  B.mat[1][0] = 1;
  B.mat[1][1] = 2;

  Matrix C = multiply(A, B);

  for(int i = 0; i < 2; i++) {
    for(int j = 0; j < 2; j++) {
        printf("%d ", C.mat[i][j]);
    }
    printf("\n");
}
}
