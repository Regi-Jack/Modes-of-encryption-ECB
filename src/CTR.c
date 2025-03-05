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

// Function to encrypt data in CTR mode
char aes_ctr_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size, size_t *inputSize, unsigned char *iv) {
    unsigned char expandedKey[240];  // Max size for key expansion
    unsigned char counter[AES_BLOCK_SIZE];
    unsigned char encryptedCounter[AES_BLOCK_SIZE];
    unsigned char xorBlock[AES_BLOCK_SIZE];
    size_t dataSize = *inputSize;
    
    // Apply padding to the input data if needed
    applyPadding(input, &dataSize);
    
    *inputSize = dataSize;
    
    // Expand the key for encryption
    expandKey(expandedKey, key, size, 240);
    
    // Copy the IV to the counter (the counter is usually the IV/nonce)
    memcpy(counter, iv, AES_BLOCK_SIZE);
    
    // Encrypt each block
    for (size_t i = 0; i < dataSize; i += AES_BLOCK_SIZE) {
        // Encrypt the counter (it will change after each block)
        aes_encrypt(counter, encryptedCounter, expandedKey, size);
        
        // XOR the encrypted counter with the current block of plaintext
        for (size_t j = 0; j < AES_BLOCK_SIZE && i + j < dataSize; j++) {
            xorBlock[j] = input[i + j] ^ encryptedCounter[j];
        }
        
        // Store the ciphertext block in the output buffer
        memcpy(output + i, xorBlock, AES_BLOCK_SIZE);
        
        // Increment the counter for the next block
        for (int k = AES_BLOCK_SIZE - 1; k >= 0; k--) {
            if (++counter[k] != 0) {
                break;  // Stop once the counter overflows (modular arithmetic)
            }
        }
    }

    return SUCCESS;
}

// Function to decrypt data in CTR mode (same as encryption)
char aes_ctr_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size, size_t inputSize, unsigned char *iv) {
    // CTR mode encryption and decryption are identical
    return aes_ctr_encrypt(input, output, key, size, &inputSize, iv);
}
