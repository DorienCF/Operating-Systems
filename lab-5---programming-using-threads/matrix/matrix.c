#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define MAX 4 
//  couldn't rectify errors without defineing max 

  int matA[MAX][MAX]; 
  int matB[MAX][MAX]; 
  
  int matSumResult[MAX][MAX];
  int matDiffResult[MAX][MAX]; 
  int matProductResult[MAX][MAX]; 



  void fillMatrix(int matrix[MAX][MAX])
{
    for(int i = 0; i<MAX; i++) {
        for(int j = 0; j<MAX; j++) {
            matrix[i][j] = rand()%10+1;
        }
    }
}

void printMatrix(int matrix[MAX][MAX])
{
    for(int i = 0; i<MAX; i++) {
        for(int j = 0; j<MAX; j++) {
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the sum of the
// values at the coordinates of matA and matB.
void* computeSum(void* args)
{ // pass in the number of the ith thread
  int *x = (int*)args;
  int row = (*x)/MAX;
  int colum = (*x)%MAX;
  matSumResult[row][colum] = matA[row][colum] + matB[row][colum]; // Adds the two together by row and colum. 
}

// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the difference of the
// values at the coordinates of matA and matB.
void* computeDiff(void* args)
{ // pass in the number of the ith thread
    int *x = (int*) args;
    int row = (*x)/MAX;
    int col = (*x)%MAX;
    matDiffResult[row][col] = matA[row][col] - matB[row][col]; // results in the difference from A and B in MatDiffResult. 
}

// Fetches the appropriate coordinates from the argument, and sets
// the cell of matSumResult at the coordinates to the inner product
// of matA and matB.
void* computeProduct(void* args) 
{ // pass in the number of the ith thread
    int *x = (int*) args;
    int row = (*x)/MAX;
    int col = (*x)%MAX;
    matProductResult[row][col] = matA[row][col] * matB[row][col];// results in the product from A and B in MatProductResult
}

int main() 
{
typedef void*(*Operations)(void*);
// Spawn a thread to fill each cell in each result matrix.
// How many threads will you spawn?
  
    srand(time(0));  // Do Not Remove. Just ignore and continue below.
    
    // 0. Get the matrix size from the command line and assign it to MAX
      //####### matrix size is contraied in 4 see in ln:5.
    
    // 1. Fill the matrices (matA and matB) with random values.
      fillMatrix(matA); fillMatrix(matB);
    // 2. Print the initial matrices.
      printf("Matrix A:\n");
      printMatrix(matA);
      printf("Matrix B:\n");
      printMatrix(matB);
      
    // 3. Create pthread_t objects for our threads.
    pthread_t threads[MAX];
    
    // 4. Create a thread for each cell of each matrix operation.
    Operations MatrixOperations[3]; // three for each matrix operation.
        MatrixOperations[0] = &computeSum;
        MatrixOperations[1] = &computeDiff;
        MatrixOperations[2] = &computeProduct;
  
      
    // ###################
    // You'll need to pass in the coordinates of the cell you want the thread
    // to compute.
    // 
    // One way to do this is to malloc memory for the thread number i, populate the coordinates
    // into that space, and pass that address to the thread. The thread will use that number to calcuate 
    // its portion of the matrix. The thread will then have to free that space when it's done with what's in that memory.
    // ###################



  for(int i = 0; i<3; i++) // iterating through the MatrixOperations[0-2]
  {
      for (int k = 0; k< MAX*MAX; k++)
      {
       int *index = (int*)malloc(sizeof(int));
       *index = k;
        
        pthread_create(&threads[*index], NULL, MatrixOperations[i], (void*)index);
      }
    }
    
    // 5. Wait for all threads to finish.
    for (int i=0; i<MAX; i++)
    {
    pthread_join(threads[i], NULL);
    }
  
    // 6. Print the results.
    printf("Results:\n");
    printf("Sum:\n");
    printMatrix(matSumResult);
    printf("Difference:\n");
    printMatrix(matDiffResult);
    printf("Product:\n");
    printMatrix(matProductResult);
    printf("There seems to be a Segmentation Fault... there is a possablilty to exploit this code...Hacking the art of exploitation goes into this\n
  ");
    return 0;
            // There seems to be a Segmentation Fault... there is a possablilty to exploit this code... "Hacking the art of exploitation goes into this"
  
}
