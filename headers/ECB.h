#ifndef ECB_H
#define ECB_H

#include "AES.h"  // Include AES.h since it's referenced in the functions
#include <stddef.h>  // For size_t

// Define the size of the message and AES block size
#define AES_BLOCK_SIZE 16  // AES block size in bytes (128 bits)
#define MSSG_SIZE 1000    // Max message size

// Function to apply padding to plaintext if necessary
void applyPadding(unsigned char *data, size_t *dataSize);

// Function to encrypt data in ECB mode
char aes_ecb_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size, size_t *inputSize);

// Function to decrypt data in ECB mode
char aes_ecb_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size, size_t inputSize);

#endif // ECB_H
