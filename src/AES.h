#ifndef AES_H
#define AES_H

#include <stddef.h> // for size_t

// Enum for error codes
enum errorCode
{
    SUCCESS = 0,
    ERROR_AES_UNKNOWN_KEYSIZE,
    ERROR_MEMORY_ALLOCATION_FAILED,
};

// Enum for key sizes
enum keySize
{
    SIZE_16 = 16,
    SIZE_24 = 24,
    SIZE_32 = 32
};

// S-Box and Inverse S-Box
extern unsigned char sbox[256];
extern unsigned char rsbox[256];

// Rcon
extern unsigned char Rcon[255];

// Function prototypes

// S-Box and Inverse S-Box functions
unsigned char getSBoxValue(unsigned char num);
unsigned char getSBoxInvert(unsigned char num);

// AES helper functions
void rotate(unsigned char *word);
unsigned char getRconValue(unsigned char num);

// Key expansion functions
void expandKey(unsigned char *expandedKey, unsigned char *key, enum keySize size, size_t expandedKeySize);
void core(unsigned char *word, int iteration);

// AES encryption functions
void subBytes(unsigned char *state);
void shiftRows(unsigned char *state);
void shiftRow(unsigned char *state, unsigned char nbr);
void addRoundKey(unsigned char *state, unsigned char *roundKey);
unsigned char galois_multiplication(unsigned char a, unsigned char b);
void mixColumns(unsigned char *state);
void mixColumn(unsigned char *column);
void aes_round(unsigned char *state, unsigned char *roundKey);
void createRoundKey(unsigned char *expandedKey, unsigned char *roundKey);
void aes_main(unsigned char *state, unsigned char *expandedKey, int nbrRounds);
char aes_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size);

// AES decryption functions
void invSubBytes(unsigned char *state);
void invShiftRows(unsigned char *state);
void invShiftRow(unsigned char *state, unsigned char nbr);
void invMixColumns(unsigned char *state);
void invMixColumn(unsigned char *column);
void aes_invRound(unsigned char *state, unsigned char *roundKey);
void aes_invMain(unsigned char *state, unsigned char *expandedKey, int nbrRounds);
char aes_decrypt(unsigned char *input, unsigned char *output, unsigned char *key, enum keySize size);

#endif // AES_H
