/* Compiles corectly; need to test. */

typedef struct Matrix {
  double mat[2][2];
} Matrix;

typedef struct Vector {
  double mat[2][1];
} Vector;

/* Change back to 4x4 after tests. */
Matrix multiply(Matrix A, Matrix B) {
  /* Initialize product matrix. */
  Matrix C;

  for(int i=0; i<2; i++){
    for(int j=0; j<2; j++){
      C.mat[i][j] = 0;
        for(int k=0; k<2; k++){
          C.mat[i][j] += A.mat[i][k] * B.mat[k][j];
        }
    }
  }
}

Matrix add(Matrix A, Matrix B) {
  /* Initialize sum matrix. */
  Matrix C;

  for(int i=0; i<2; i++){
    for(int j=0; j<2; j++){
      C.mat[i][j] = A.mat[i][j] + B.mat[i][j];
    }
  }
}
