#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "ECB.h"

void encrypt_pgm(const char *input_file, const char *output_file)
{
    FILE *file = fopen(input_file, "rb");
    if (!file)
    {
        perror("Error opening input file!!!");
        return;
    }

    // Read P5 Header
    char magic[3];
    int width, height, maxval;
    fscanf(file, "%2s", magic);
    if (strcmp(magic, "P5") != 0)
    {
        printf("Not a valid P5 PGM file!\n");
        fclose(file);
        return;
    }
    fscanf(file, "%d %d %d", &width, &height, &maxval);
    fgetc(file); // Consume the newline after maxval

    // Read pixel data
    size_t image_size = width * height;
    unsigned char *image_data = (unsigned char *)malloc(image_size);
    fread(image_data, 1, image_size, file);
    fclose(file);

    unsigned char *encrypted_data = (unsigned char *)malloc(image_size);

    unsigned char key[32] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x97, 0x75, 0x46, 0x5d, 0xa1, 0x24, 0x56, 0x09, 0x88, 0x8b, 0x22, 0x33, 0x3c, 0x98, 0x78, 0x35, 0x45, 0x23, 0x01, 0x72, 0xa2};

    aes_ecb_encrypt(image_data, encrypted_data, key, SIZE_32, &image_size);

    FILE *out_file = fopen(output_file, "wb");
    fprintf(out_file, "P5\n%d %d\n%d\n", width, height, maxval);
    fwrite(encrypted_data, 1, image_size, out_file);
    fclose(out_file);

    printf("Encrypted image saved to: %s\n", output_file);

    free(image_data);
    free(encrypted_data);
}

int main()
{

    char cwd[3000];
    char path_to_img[3000];
    char path_to_enc_image[3000];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        // printf("Current Working Directory: %s\n", cwd);
        snprintf(path_to_img, sizeof(path_to_img), "%s/image/pikachu.pgm", cwd);
        snprintf(path_to_enc_image, sizeof(path_to_enc_image), "%s/output/output.pgm", cwd);
        // printf("Image Directory: %s\n", path_to_img);
    }
    else
    {
        perror("getcwd() error");
        return 1;
    }

    encrypt_pgm(path_to_img, path_to_enc_image);
    return 0;
}