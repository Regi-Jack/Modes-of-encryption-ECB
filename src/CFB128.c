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

// Function to encrypt data in CFB-128 mode
char aes_cfb128_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size, size_t *inputSize, unsigned char *iv) {
    unsigned char expandedKey[240];  // Max size for key expansion
    unsigned char ivCopy[AES_BLOCK_SIZE];
    unsigned char ciphertext[AES_BLOCK_SIZE];
    unsigned char xorBlock[AES_BLOCK_SIZE];
    size_t dataSize = *inputSize;
    
    // Apply padding to the input data if needed
    applyPadding(input, &dataSize);
    
    *inputSize = dataSize;
    
    // Expand the key for encryption
    expandKey(expandedKey, key, size, 240);
    
    // Encrypt each block
    for (size_t i = 0; i < dataSize; i += AES_BLOCK_SIZE) {
        // Copy the IV before modifying it for feedback
        memcpy(ivCopy, iv, AES_BLOCK_SIZE);
        
        // Encrypt the IV (Feedback block)
        aes_encrypt(ivCopy, ciphertext, expandedKey, size);
        
        // XOR the plaintext block with the encrypted IV to produce the ciphertext
        for (size_t j = 0; j < AES_BLOCK_SIZE; j++) {
            xorBlock[j] = input[i + j] ^ ciphertext[j];
        }
        
        // Store the ciphertext block in the output buffer
        memcpy(output + i, xorBlock, AES_BLOCK_SIZE);
        
        // Update the IV for the next block (feedback mechanism) — FIXED LINE
        memcpy(iv, xorBlock, AES_BLOCK_SIZE);  // Correct feedback is the XORed block, not the ciphertext
    }

    return SUCCESS;
}

// Function to decrypt data in CFB-128 mode
char aes_cfb128_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size, size_t inputSize, unsigned char *iv) {
    unsigned char expandedKey[240];  // Max size for key expansion
    unsigned char ivCopy[AES_BLOCK_SIZE];
    unsigned char ciphertext[AES_BLOCK_SIZE];
    unsigned char xorBlock[AES_BLOCK_SIZE];
    
    // Expand the key for decryption
    expandKey(expandedKey, key, size, 240);
    
    // Decrypt each block
    for (size_t i = 0; i < inputSize; i += AES_BLOCK_SIZE) {
        // Copy the IV before modifying it for feedback
        memcpy(ivCopy, iv, AES_BLOCK_SIZE);
        
        // Encrypt the IV (Feedback block)
        aes_encrypt(ivCopy, ciphertext, expandedKey, size);
        
        // XOR the ciphertext block with the encrypted IV to produce the plaintext
        for (size_t j = 0; j < AES_BLOCK_SIZE; j++) {
            xorBlock[j] = input[i + j] ^ ciphertext[j];
        }
        
        // Store the plaintext block in the output buffer
        memcpy(output + i, xorBlock, AES_BLOCK_SIZE);
        
        // Update the IV for the next block (feedback mechanism) — FIXED LINE
        memcpy(iv, xorBlock, AES_BLOCK_SIZE);  // Correct feedback is the XORed block, not the ciphertext
    }

    return SUCCESS;
}
