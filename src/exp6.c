#include <stdio.h>
#include <string.h>

int main(){
    char message[100];
    printf("Enter a message to hash: ");
    fgets(message, 100, stdin);

    size_t n = strlen(message);
    int sum = 0;
    for(int i=0; i<n; i++){
        sum ^= message[i];
    }

    printf("Message hash is %d\n", sum);
}