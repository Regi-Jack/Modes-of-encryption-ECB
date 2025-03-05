#ifndef CBC_H
#define CBC_H

#include "AES.h"  // Include AES.h since it's referenced in the functions
#include <stddef.h>  // For size_t

// Define AES block size and message size
#define AES_BLOCK_SIZE 16  // AES block size in bytes (128 bits)
#define MSSG_SIZE 1000

// Function to apply padding to the input data (if necessary) for AES block size
static void applyPadding(unsigned char *data, size_t *dataSize);

// Encrypts data using AES in CBC mode
char aes_cbc_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size, size_t *inputSize, unsigned char *iv);

// Decrypts data using AES in CBC mode
char aes_cbc_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size, size_t inputSize, unsigned char *iv);

#endif // CBC_H
