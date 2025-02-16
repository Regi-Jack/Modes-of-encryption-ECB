#include "AES.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define AES_BLOCK_SIZE 16  // AES block size in bytes (128 bits)
#define MSSG_SIZE 1000

// Function to apply padding to plaintext if necessary
void applyPadding(unsigned char *data, size_t *dataSize) {
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

// // Function to remove padding after decryption
// void removePadding(unsigned char *data, size_t *dataSize) {
//     size_t len = *dataSize;
//     size_t padding = data[len - 1];
//     *dataSize -= padding;
    
//     // Null-terminate the decrypted string
//     data[*dataSize] = '\0';
// }

// Function to encrypt data in ECB mode
char aes_ecb_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size, size_t *inputSize) {
    unsigned char expandedKey[240];  // Max size for key expansion
    unsigned char plaintext[AES_BLOCK_SIZE];
    unsigned char ciphertext[AES_BLOCK_SIZE];
    size_t dataSize = *inputSize;
    
    // Apply padding to the input data if needed
    applyPadding(input, &dataSize);

    // printf("New data size: %ld\n", dataSize);
    *inputSize = dataSize;

    // printf("New data: %s\n", input);
 
    // Expand the key for encryption
    expandKey(expandedKey, key, size, 240);

    // Encrypt each block
    for (size_t i = 0; i < dataSize; i += AES_BLOCK_SIZE) {
        memcpy(plaintext, input + i, AES_BLOCK_SIZE);  // Copy one block of input into the variable plaintext
        aes_encrypt(plaintext, ciphertext, expandedKey, size);  // Encrypt the plaintext block into ciphertext
        memcpy(output + i, ciphertext, AES_BLOCK_SIZE);   // Store the ciphertext block to output
    }


    return SUCCESS;
}

// Function to decrypt data in ECB mode
char aes_ecb_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size, size_t inputSize) {
    unsigned char expandedKey[240];  // Max size for key expansion
    unsigned char plaintext[AES_BLOCK_SIZE];
    unsigned char ciphertext[AES_BLOCK_SIZE];
    size_t dataSize = inputSize;

    // Expand the key for decryption
    expandKey(expandedKey, key, size, 240);

    // Decrypt each block
    for (size_t i = 0; i < dataSize; i += AES_BLOCK_SIZE) {
        memcpy(ciphertext, input + i, AES_BLOCK_SIZE);  // Copy one block of ciphertext into the state
        aes_decrypt(ciphertext, plaintext, expandedKey, size);  // Decrypt the block
        memcpy(output + i, plaintext, AES_BLOCK_SIZE);   // Store the decrypted block
    }

    // Remove padding if present
    // removePadding(output, &dataSize);
    
    return SUCCESS;
}







// int main() {
//     // Test data and key
    
//     unsigned char key[32] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x97, 0x75, 0x46, 0x5d, 0xa1, 0x24, 0x56, 0x09, 0x88, 0x8b, 0x22, 0x33, 0x3c, 0x98, 0x78, 0x35, 0x45, 0x23, 0x01, 0x72, 0xa2};
    
//     // Allocate a buffer for input, encrypted, and decrypted data (e.g., 1000 bytes)
//     unsigned char input[MSSG_SIZE];
//     unsigned char encrypted[MSSG_SIZE];  // Extra space for padding
//     unsigned char decrypted[MSSG_SIZE];  // Output for decrypted data
    
//     // Prompt the user for input (up to MSSG_SIZE bytes)
//     printf("Enter the message: ");
//     scanf("%s", input);
//     // fgets((char *)input, sizeof(input), stdin);  // Read input from user
    
//     // Calculate input size
//     size_t inputSize = strlen((char *)input);
    
//     // // Make sure to remove the newline character at the end if present
//     // if (inputSize > 0 && input[inputSize - 1] == '\n') {
//     //     input[inputSize - 1] = '\0';
//     //     inputSize--;
//     // }

//     printf("Size of input: %ld\n", inputSize);
    
//     printf("Original Input: %s\n", input);

//     // Encrypt the data
//     aes_ecb_encrypt(input, encrypted, key, SIZE_32, &inputSize);

//     printf("New input size : %ld\n", inputSize);

//     printf("New input: %s\n", input);

//     printf("Encrypted Output:\n");
//     for (size_t i = 0; i < inputSize; i++) {
//             printf("%02x ", encrypted[i]); 
//     }
    
//     printf("\n");

//     // Decrypt the data
//     aes_ecb_decrypt(encrypted, decrypted, key, SIZE_32, inputSize);
//     printf("Decrypted Output: %s\n", decrypted);

//     return 0;
// }
