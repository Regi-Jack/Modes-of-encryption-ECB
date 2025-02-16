#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

int extract_pixel_values(const char* path_to_img, const char* path_to_enc_file) {
    // Open the JPEG file
    FILE *infile = fopen(path_to_img, "rb");
    if (infile == NULL) {
        printf("Error opening JPEG file\n");
        return 1;
    }

    // Set up the decompression structure for libjpeg
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    // Specify the source of the JPEG file
    jpeg_stdio_src(&cinfo, infile);

    // Read the JPEG header
    jpeg_read_header(&cinfo, TRUE);

    // Start the decompression
    jpeg_start_decompress(&cinfo);

    // Get image width, height, and number of channels (color components)
    int width = cinfo.output_width;
    // int height = cinfo.output_height;
    int num_channels = cinfo.output_components; // 3 for RGB, 1 for grayscale

    // Allocate memory for one row of pixel data (RGB format)
    unsigned char *row = (unsigned char *)malloc(width * num_channels);

    // Open file to write grayscale values
    FILE *file = fopen(path_to_enc_file, "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Iterate over each row and each pixel to extract grayscale values
    while (cinfo.output_scanline < cinfo.output_height) {
        jpeg_read_scanlines(&cinfo, &row, 1);

        // Convert RGB to grayscale and write to file
        for (int x = 0; x < width; x++) {
            unsigned char r = row[x * num_channels];     // Red channel
            unsigned char g = row[x * num_channels + 1]; // Green channel
            unsigned char b = row[x * num_channels + 2]; // Blue channel
            // Grayscale conversion: average of R, G, and B channels
            unsigned char gray = (r + g + b) / 3;
            fprintf(file, "%d ", gray);
        }
        fprintf(file, "\n");
    }

    // Clean up memory and file
    free(row);
    fclose(file);

    // Finish decompression
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);

    printf("Grayscale values have been written to encrypted_image.txt\n");
    return 0;
}


// int main() {
//     const char *path_to_img = "/home/rajdeep/Desktop/AES/aes-in-c-main/image/boy.jpg";
//     const char *path_to_enc_file = "/home/rajdeep/Desktop/AES/aes-in-c-main/file/encrypted_image.txt";
//     extract_pixel_values(path_to_img, path_to_enc_file);
//     return 0;
// }
