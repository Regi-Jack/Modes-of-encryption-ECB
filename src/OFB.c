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
        printf("Padding not required.\n");
        return;
    }
    size_t padding = AES_BLOCK_SIZE - (len % AES_BLOCK_SIZE);
    for (size_t i = len; i < len + padding; i++) {
        data[i] = '.';
    }
    *dataSize += padding;
}

// Function to encrypt data in OFB mode
char aes_ofb_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size, size_t *inputSize, unsigned char *iv) {
    unsigned char expandedKey[240];  // Max size for key expansion
    unsigned char feedback[AES_BLOCK_SIZE];  // Holds feedback block
    unsigned char encryptedFeedback[AES_BLOCK_SIZE];  // Holds encrypted feedback
    unsigned char xorBlock[AES_BLOCK_SIZE];  // Holds XORed result
    size_t dataSize = *inputSize;
    
    // Apply padding to the input data if needed
    applyPadding(input, &dataSize);
    
    *inputSize = dataSize;
    
    // Expand the key for encryption
    expandKey(expandedKey, key, size, 240);
    
    // Copy the IV to the feedback block (the feedback block starts with the IV)
    memcpy(feedback, iv, AES_BLOCK_SIZE);
    
    // Encrypt each block of data
    for (size_t i = 0; i < dataSize; i += AES_BLOCK_SIZE) {
        // Encrypt the feedback block using AES
        aes_encrypt(feedback, encryptedFeedback, expandedKey, size);
        
        // XOR the encrypted feedback with the current block of plaintext
        for (size_t j = 0; j < AES_BLOCK_SIZE && i + j < dataSize; j++) {
            xorBlock[j] = input[i + j] ^ encryptedFeedback[j];
        }
        
        // Store the ciphertext block in the output buffer
        memcpy(output + i, xorBlock, AES_BLOCK_SIZE);
        
        // Copy the current encrypted feedback to the feedback block (feedback loop)
        memcpy(feedback, encryptedFeedback, AES_BLOCK_SIZE);
    }

    return SUCCESS;
}

// Function to decrypt data in OFB mode (same as encryption)
char aes_ofb_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size, size_t inputSize, unsigned char *iv) {
    // OFB mode encryption and decryption are identical
    return aes_ofb_encrypt(input, output, key, size, &inputSize, iv);
}
