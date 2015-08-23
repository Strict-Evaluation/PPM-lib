#ifndef PPM_H
#define PPM_H

typedef struct {
   int r, g, b;
} ppm_pixel;

typedef struct {
   int width, height;
   ppm_pixel **data;
} ppm_image;

ppm_image* make_image(int width, int height);
void free_image(ppm_image* image);

ppm_pixel* get_pixel(ppm_image* image, int x, int y);
void set_pixel(ppm_image* image, int x, int y, int r, int g, int b);
void map_pixels(ppm_image* image, void (*fn)(ppm_pixel*));
void map_indices(ppm_image* image, void (*fn)(ppm_image*, ppm_pixel*, int, int));

ppm_image* read_image(char* filename);
void write_image(ppm_image* image, char* filename);

#endif
