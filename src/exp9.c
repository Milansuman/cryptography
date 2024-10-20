#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int* keystream(const char *key, size_t n){
    size_t keysize = strlen(key);
    int s[255];
    char t[255];
    for(int i=0; i<255; i++){
        s[i] = i;
        t[i] = key[i%keysize];
    }

    int j = 0;
    for(int i=0; i<255; i++){
        j = (j + s[i] + t[i])%256;
        int temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }

    int *rc4key = malloc(sizeof(int)*n);
    int i=0;
    j=0;
    for(int a=0; a<n; a++){
        i = (i+1)%256;
        j = (j + s[i])%256;
        int temp = s[i];
        s[i] = s[j];
        s[j] = temp;

        int t = (s[i] + s[j])%256;
        rc4key[a] = s[t];
    }

    return rc4key;
}

char* rc4(const char *text, const char *key){
    size_t n = strlen(text);
    int *rc4KeyStream = keystream(key, n);

    char *procText = malloc(sizeof(char)*n);
    for(int i=0; i<n; i++){
        procText[i] = text[i]^rc4KeyStream[i];
    }

    free(rc4KeyStream);
    return procText;
}

int main(){
    char message[100];
    char key[100];
    printf("Enter some text to encrypt: ");
    fgets(message, 100, stdin);
    printf("Enter your key: ");
    fgets(key, 100, stdin);

    printf("Encrypted RC4 text is: %s\n", rc4(message, key));
    printf("Decrypted text is: %s\n", rc4(rc4(message, key), key));
    int *stream = keystream(key, strlen(message));

    printf("Key stream is: ");
    for(int i=0; i<strlen(message); i++){
        printf("%x ", stream[i]);
    }
    printf("\n");
    free(stream);
    return 0;
}