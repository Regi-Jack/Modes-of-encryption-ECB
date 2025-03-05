#include "AES.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define AES_BLOCK_SIZE 16  // AES block size in bytes (128 bits)
#define MSSG_SIZE 1000

// Function to apply padding to plaintext if necessary
static void applyPadding(unsigned char *data, size_t *dataSize) {
    size_t len = *dataSize;
    if(len % AES_BLOCK_SIZE == 0) {
        printf("padding not req.\n");
        return;
    }
    size_t padding = AES_BLOCK_SIZE - (len % AES_BLOCK_SIZE);
    for (size_t i = len; i < len + padding; i++) {
        data[i] = '.';
        if(i+1 == len + padding)
            data[i+1] = '\0';  
    }
    *dataSize += padding;
}

// Function to encrypt data in CBC mode
char aes_cbc_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size, size_t *inputSize, unsigned char *iv) {
    unsigned char expandedKey[240];  // Max size for key expansion
    unsigned char plaintext[AES_BLOCK_SIZE];
    unsigned char ciphertext[AES_BLOCK_SIZE];
    size_t dataSize = *inputSize;
    unsigned char prevCiphertext[AES_BLOCK_SIZE];
    
    // Apply padding to the input data if needed
    applyPadding(input, &dataSize);
    *inputSize = dataSize;
    
    // Save the original IV for the first block
    memcpy(prevCiphertext, iv, AES_BLOCK_SIZE);

    // Expand the key for encryption
    expandKey(expandedKey, key, size, 240);

    // Encrypt each block
    for (size_t i = 0; i < dataSize; i += AES_BLOCK_SIZE) {
        // Copy the next block of plaintext
        memcpy(plaintext, input + i, AES_BLOCK_SIZE);

        // XOR the plaintext with the previous ciphertext (or IV for the first block)
        for (size_t j = 0; j < AES_BLOCK_SIZE; j++) {
            plaintext[j] ^= prevCiphertext[j];
        }

        // Encrypt the block
        aes_encrypt(plaintext, ciphertext, expandedKey, size);

        // Store the ciphertext
        memcpy(output + i, ciphertext, AES_BLOCK_SIZE);

        // Update the previous ciphertext to the current one
        memcpy(prevCiphertext, ciphertext, AES_BLOCK_SIZE);
    }

    return SUCCESS;
}

// Function to decrypt data in CBC mode
char aes_cbc_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size, size_t inputSize, unsigned char *iv) {
    unsigned char expandedKey[240];  // Max size for key expansion
    unsigned char plaintext[AES_BLOCK_SIZE];
    unsigned char ciphertext[AES_BLOCK_SIZE];
    size_t dataSize = inputSize;
    unsigned char prevCiphertext[AES_BLOCK_SIZE];
    
    // Save the original IV for the first block
    memcpy(prevCiphertext, iv, AES_BLOCK_SIZE);

    // Expand the key for decryption
    expandKey(expandedKey, key, size, 240);

    // Decrypt each block
    for (size_t i = 0; i < dataSize; i += AES_BLOCK_SIZE) {
        // Copy the next block of ciphertext
        memcpy(ciphertext, input + i, AES_BLOCK_SIZE);

        // Decrypt the block
        aes_decrypt(ciphertext, plaintext, expandedKey, size);

        // XOR the decrypted block with the previous ciphertext (or IV for the first block)
        for (size_t j = 0; j < AES_BLOCK_SIZE; j++) {
            plaintext[j] ^= prevCiphertext[j];
        }

        // Store the decrypted block
        memcpy(output + i, plaintext, AES_BLOCK_SIZE);

        // Update the previous ciphertext to the current one
        memcpy(prevCiphertext, ciphertext, AES_BLOCK_SIZE);
    }

    return SUCCESS;
}
