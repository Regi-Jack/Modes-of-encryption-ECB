#ifndef IMG_H
#define IMG_H

#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

// Function to extract pixel values from a grayscale image and write to a file
// Takes in paths for input image and output encrypted file
int extract_pixel_values(char* path_to_img, char* path_to_enc_file);

#endif // IMG_H
