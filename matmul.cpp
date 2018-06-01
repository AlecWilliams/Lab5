#include <stdlib.h>
#include <stdio.h>
#include "matmul.h"

Matrix Allocate2ndMatrix(int height, int width, int init);

void matmul( float*, const float*, const float*, unsigned int, unsigned int, unsigned int);

////////////////////////////////////////////////////////////////////////////////
//! C = A * B
//! @param C          result matrix
//! @param A          matrix A 
//! @param B          matrix B
//! @param hA         height of matrix A
//! @param wB         width of matrix B
////////////////////////////////////////////////////////////////////////////////

/* You'll need to modify this function such that matrix B is accessed
 * correctly once you change the memory layout to column-major. */
void matmul(float* C, const float* A, const float* B, unsigned int hA, 
    unsigned int wA, unsigned int wB)
{
//====================Colum Major=========================
  /**
    for (unsigned int i = 0; i < hA; ++i)           // i == row A
      for (unsigned int j = 0; j < wB; ++j) {       // j == col
        double sum = 0;
        for (unsigned int k = 0; k < wA; ++k) {     //a = A[0 * 1024 + 0]  A[0 * 1024 +1]
          double a = A[i * wA + k];                 //b = B[0 * 1024 + 0]  B[1 * 1024 +0]
          //double b = B[k * wB + j];
          double b = B[j * wA + k];
          sum += a * b;
        }
       
        C[i * wB + j] = (float)sum;
    }
    
**/   
//============Tiling====================================
  
    //int tilingWidth = 16;
    float sumArr[1024*1024];
    unsigned int i,j,k,x,y,z;
    unsigned int max = 1024*1024;
    int blockSize = 16;
    float sum = 0;
    //int Q=1;
    for(i=0; i < hA; i+=blockSize) {
      for(j=0; j < wB; j+=blockSize) {
        for(k=0; k < hA; k+=blockSize) {
         
          for (x = i; x < hA && x<i+blockSize; x++) {
            
            for (y = j; y < wB && y<j+blockSize; y++) {
             sum = 0;
              for (z = k; z < hA && z<k+blockSize; z++) {
                double a = A[x * wB + z];
                double b = B[y * wB + z];
    
                sum+= a*b;
              }
              C[x*wB + y] += sum;
             
            }
          }
        }
      }
  
    }
 
}



// Allocate a matrix of dimensions height*width
Matrix Allocate2ndMatrix(int height, int width)
{
  Matrix M;
  M.width = M.pitch = width;
  M.height = height;
  int size = M.width * M.height;
  M.elements = NULL;
  //int colCounter = 0;
  M.elements = (float*) malloc(size*sizeof(float));

  /* This is a row-major allocation and initialization.
   * You need to modify this function which is only called
   * for Matrix B such that a column-major ordering is
   * performed. **/

  

  //===============Original==========================
  /**
  for(unsigned int i = 0; i < M.height * M.width; i++)
  {
    M.elements[i] = (rand() / (float)RAND_MAX);
  }
  return M;
**/
    

  //===============Colum Major=====================
  
  for(unsigned int k = 0; k < M.width; k++){

    for(unsigned int i= 0; i <M.height; i++){
     
      //colCounter = (float)(i / M.pitch);
      M.elements[(i * M.pitch) + k] = (rand() / (float)RAND_MAX);
        
    }
  }
  return M;
  
}	

