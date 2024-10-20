#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* strupper(char *text){
    char *upper = malloc(sizeof(char) * strlen(text));
    for(int i=0; i<strlen(text); i++){
        upper[i] = toupper(text[i]);
    }
    return upper;
}

char* encrypt(char *plainText, int key){
    char *upperText = strupper(plainText);

    for(int i=0; i<strlen(upperText); i++){
        if(!isalpha(upperText[i])) continue;

        int offset = (upperText[i] - 'A' + key) % 25;
        upperText[i] = 'A' + offset;
    }
    return upperText;
}

char* decrypt(char *cipherText, int key){
    char *upperText = strupper(cipherText);

    for(int i=0; i<strlen(upperText); i++){
        if(!isalpha(upperText[i])) continue;

        int offset = (upperText[i] - 'A' - key) % 25;
        if(offset < 0) offset += 25;
        upperText[i] = 'A' + offset;
    }
    return upperText;
}

int main(){
    char message[100];
    int key = 0;
    printf("Enter a message to encrypt: ");
    fgets(message, 100, stdin);
    printf("Enter the key: ");
    scanf("%d", &key);

    printf("Encrypted message using substitution cipher: %s", encrypt(message, key));
    printf("Decrypted message using substitution cipher: %s", decrypt(encrypt(message, key), key));
    return 0;
}