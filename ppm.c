#include "ppm.h"
#include <stdlib.h>
#include <stdio.h>

ppm_image* make_image(int width, int height){
   int i = 0;
   ppm_image* image = malloc(sizeof(ppm_image));
   image->width = width;
   image->height = height;
   image->data = malloc(height*sizeof(ppm_pixel*));
   for (; i < height; i++){
      image->data[i] = malloc(width*sizeof(ppm_pixel));
   }
   return image;
}

void free_image(ppm_image* image){
   int i = 0;
   for (; i < image->height; i++){
      free(image->data[i]);
   }
   free(image->data);
   free(image);
}

ppm_pixel* get_pixel(ppm_image* image, int x, int y){
   return &(image->data[y][x]);
}

void set_pixel(ppm_image* image, int x, int y, int r, int g, int b){
   ppm_pixel* current = get_pixel(image, x, y);
   current->r = r;
   current->g = g;
   current->b = b;
}

void map_pixels(ppm_image* image, void (*fn)(ppm_pixel*)){
   int x, y;
   for (y = 0; y < image->height; y++){
      for (x = 0; x < image->width; x++){
         fn(get_pixel(image, x, y));
      }
   }
}

void map_indices(ppm_image* image, void (*fn)(ppm_image*, ppm_pixel*, int, int)){
   int x, y;
   for (y = 0; y < image->height; y++){
      for (x = 0; x < image->width; x++){
         fn(image, get_pixel(image, x, y), x, y);
      }
   }
}

ppm_image* read_image(char* filename){
   FILE* fp = fopen(filename, "r");
   ppm_image* image;
   ppm_pixel* current;
   int width, height, x, y;
   char r, g, b;
   if (fp == NULL){
      fprintf(stderr, "Couldn't read image from: %s\n", filename);
      exit(1);
   }
   fscanf(fp, "P6 %d %d 255 ", &width, &height);
   image = make_image(width, height);
   for (y = 0; y < image->height; y++){
      for (x = 0; x < image->width; x++){
         current = get_pixel(image, x, y);
         fscanf(fp, "%c%c%c", &r, &g, &b);
         current->r = (int)r;
         current->g = (int)g;
         current->b = (int)b;
      }
   }
   fclose(fp);
   return image;
}

void write_image(ppm_image* image, char* filename){
   int x, y;
   ppm_pixel current;
   FILE* fp = fopen(filename, "w");
   if (fp == NULL){
      fprintf(stderr, "Couldn't write image to: %s\n", filename);
      exit(1);
   }
   fprintf(fp, "P6 %d %d 255 ", image->width, image->height);
   for (y = 0; y < image->height; y++){
      for (x = 0; x < image->width; x++){
         current = image->data[y][x];
         fprintf(fp, "%c%c%c", (char)current.r, (char)current.g, (char)current.b);
      }
   }
   fclose(fp);
}
