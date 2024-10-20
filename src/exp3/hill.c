#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define INCOMPATIBLE_MATRICES -3
#define INVALID_SIZE -4

typedef struct Matrix{
    float **elements;
    int rows, cols;
} Matrix;

Matrix* initializeMatrix(int rows, int cols){
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;

    matrix->elements = malloc(sizeof(float*) * matrix->rows);
    for(int i=0; i<matrix->rows; i++){
        matrix->elements[i] = malloc(sizeof(float) * matrix->cols);
        for(int j=0; j<matrix->cols; j++){
            matrix->elements[i][j] = 0.0;
        }
    }
    return matrix;
}

void freeMatrix(Matrix *matrix){
    for(int i=0; i<matrix->rows; i++){
        free(matrix->elements[i]);
    }
    free(matrix->elements);
    free(matrix);
}

int product(Matrix *m1, Matrix *m2, Matrix *res){
    if(m1->cols != m2->rows){
        return INCOMPATIBLE_MATRICES;
    }

    if(res) freeMatrix(res);
    res = initializeMatrix(m1->rows, m2->cols);

    for(int i=0; i<res->rows; i++){
        for(int j=0; j<m1->cols; j++){
            for(int k=0; k<m1->cols; k++){
                res->elements[i][j] = res->elements[i][j] + m1->elements[i][k] * m2->elements[k][j];
            }
        }
    }

    return 0;
}

int determinant(Matrix *matrix){
    return (matrix->elements[0][0] * matrix->elements[1][1]) - (matrix->elements[0][1] * matrix->elements[1][0]);
}

int inverse(Matrix *matrix, Matrix *inverse){
    if(matrix->rows != 2 && matrix->cols != 2){
        return INVALID_SIZE;
    }

    if(inverse == NULL) inverse = initializeMatrix(matrix->rows, matrix->cols);
    
    //find minor
    inverse->elements[0][0] = matrix->elements[1][1];
    inverse->elements[0][1] = matrix->elements[0][1];
    inverse->elements[1][0] = matrix->elements[1][0];
    inverse->elements[1][1] = matrix->elements[0][0];

    int det = determinant(matrix);

    //find inverse
    for(int i=0; i<inverse->rows; i++){
        for(int j=0; j<inverse->cols; j++){
            inverse->elements[i][j] *= pow(-1, i+j) * (1.0/det);
        }
    }

    return 0;
}

void printMatrix(Matrix* matr) {
    for (int i = 0; i < matr -> rows; i++) {
        for (int j = 0; j < matr -> cols; j++) {
            printf("%.2f ", matr -> elements[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

char* encrypt(char *plainText, Matrix *key){
    if(strlen(plainText)%2 != 0){
        plainText = strcat(plainText, " ");
    }

    size_t n = strlen(plainText);
    char *cipherText = malloc(sizeof(char)*n);
    for(int i=0; i<n; i+=2){
        Matrix *block = initializeMatrix(2, 1);
        block->elements[0][0] = (float) *(plainText+i);
        block->elements[1][0] = (float) *(plainText+i+1);

        Matrix *encryptedBlock = initializeMatrix(2, 1);
        int err = product(key, block, encryptedBlock);

        cipherText[i] = (int) encryptedBlock->elements[0][0];
        cipherText[i+1] = (int) encryptedBlock->elements[1][0];

        freeMatrix(block);
        freeMatrix(encryptedBlock);
    }
    return cipherText;
}

char* decrypt(char *cipherText, Matrix *invKey){
    size_t n = strlen(cipherText);
    char *plainText = malloc(sizeof(char) * n);
    for(int i=0; i<n; i+=2){
        Matrix *block = initializeMatrix(2, 1);
        block->elements[0][0] = (float) *(cipherText+i);
        block->elements[1][0] = (float) *(cipherText+i+1);

        Matrix *decryptedBlock = initializeMatrix(2, 1);
        int err = product(invKey, block, decryptedBlock);

        plainText[i] = (int) decryptedBlock->elements[0][0];
        plainText[i+1] = (int) decryptedBlock->elements[1][0];

        freeMatrix(block);
        freeMatrix(decryptedBlock);
    }
    return plainText;
}

int main(){
    Matrix *key = initializeMatrix(2, 2);
    key->elements[0][0] = 4.0;
    key->elements[0][1] = 3.0;
    key->elements[1][0] = 1.0;
    key->elements[1][1] = 1.0;
    printf("KEY:\n");
    printMatrix(key);

    Matrix *invKey = initializeMatrix(2, 2);
    inverse(key, invKey);
    printf("INVERSE KEY:\n");
    printMatrix(invKey);

    char text[] = "hello world";
    printf("ENCRYPTED: %s\n", encrypt(text, key));
    printf("DECRYPTED: %s\n", decrypt(encrypt(text, key), invKey));
    return 0;
}