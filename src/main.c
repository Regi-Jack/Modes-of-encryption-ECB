#include "IMG.h"

int main() {
    char path_to_img[1000] = "/home/rajdeep/Desktop/AES/aes-in-c-main/image/boy.jpg";
    char path_to_enc_file[1000] = "/home/rajdeep/Desktop/AES/aes-in-c-main/file/plain_image.txt";
    extract_pixel_values(path_to_img, path_to_enc_file);
    return 0;
}