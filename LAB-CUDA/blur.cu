#include "lodepng.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>

#define BLUR_SIZE 7
#define R 0
#define G 1
#define B 2
#define A 3

__global__ void blurKernel(unsigned char* in, unsigned char* out, int width, int height, int num_channel, int channel, int copy_A) {

  int col = blockIdx.x * blockDim.x + threadIdx.x;
  int row = blockIdx.y * blockDim.y + threadIdx.y;

  if(col < width && row < height) {
    int pixVal = 0;
    int pixels = 0;
    if (copy_A)
      out[row*width*num_channel+col*num_channel+A] = in[row*width*num_channel+col*num_channel+A];
    for(int blurRow = -BLUR_SIZE; blurRow < BLUR_SIZE + 1; ++blurRow) {
      for(int blurCol = -BLUR_SIZE; blurCol < BLUR_SIZE + 1; ++blurCol) {
        int curRow = row + blurRow;
        int curCol = col + blurCol;
        if(curRow > -1 && curRow < height && curCol > -1 && curCol < width) {
          pixVal += in[curRow * width * num_channel + curCol * num_channel + channel];
          pixels++;
        }
      }
    }
    out[row * width * num_channel + col * num_channel + channel] = (unsigned char)(pixVal/pixels);
  }
}

int main() {

  int width, height,n;
  unsigned char *image = stbi_load("image4.png",&width,&height,&n,0);
  unsigned char *output = (unsigned char*)malloc(width * height * n *sizeof(unsigned char));
  unsigned char* Dev_Input_Image = NULL;
  unsigned char* Dev_Output_Image = NULL;
  cudaMalloc((void**)&Dev_Input_Image, sizeof(unsigned char)* height * width * n);
  cudaMalloc((void**)&Dev_Output_Image, sizeof(unsigned char)* height * width * n);

  cudaMemcpy(Dev_Input_Image, image, sizeof(unsigned char) * height * width * n, cudaMemcpyHostToDevice);

  //kernel call
  dim3 blockSize(16, 16, 1);
  dim3 gridSize(width/blockSize.x, height/blockSize.y,1);
  blurKernel <<<gridSize, blockSize>>>(Dev_Input_Image, Dev_Output_Image, width, height,n,R,0);
  blurKernel <<<gridSize, blockSize>>>(Dev_Input_Image, Dev_Output_Image, width, height,n,G,0);
  blurKernel <<<gridSize, blockSize>>>(Dev_Input_Image, Dev_Output_Image, width, height,n,B,1);
  
  cudaDeviceSynchronize();

    cudaMemcpy(image, Dev_Output_Image, sizeof(unsigned char) * height * width * n, cudaMemcpyDeviceToHost);
  cudaFree(Dev_Input_Image);
  cudaFree(Dev_Output_Image);
  stbi_write_png("output_stbimage.png", width, height, n, image, width * n);


  return 0;
}