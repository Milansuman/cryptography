#include <stdio.h>
#include <stdlib.h>

int is_prime(long long num) {
    if (num <= 1) return 0;
    for (long long i = 2; i * i <= num; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

long long power(long long base, long long exponent, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % mod;
        }
        exponent = exponent >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    long long p, g, a, b;

    printf("Enter a prime number (p): (It should be greater than 1): ");
    scanf("%lld", &p);
    
    if (!is_prime(p)) {
        printf("Error: The number %lld is not prime.\n", p);
        return 1;
    }
    
    printf("Enter a primitive root (g) for the prime number p (1 < g < %lld): ", p);
    scanf("%lld", &g);

    printf("Enter User 1's private key (a) (must be positive and less than p): ");
    scanf("%lld", &a);
    if (a <= 0 || a >= p) {
        printf("Error: User 1's private key must be in the range (0, %lld).\n", p);
        return 1;
    }

    printf("Enter User 2's private key (b) (must be positive and less than p): ");
    scanf("%lld", &b);
    if (b <= 0 || b >= p) {
        printf("Error: User 2's private key must be in the range (0, %lld).\n", p);
        return 1;
    }

    long long A = power(g, a, p);
    long long B = power(g, b, p);

    printf("User 1's Public Key: %lld\n", A);
    printf("User 2's Public Key: %lld\n", B);

    long long shared_secret_User1 = power(B, a, p);
    long long shared_secret_User2 = power(A, b, p);

    printf("User 1's Shared Secret: %lld\n", shared_secret_User1);
    printf("User 2's Shared Secret: %lld\n", shared_secret_User2);

    if (shared_secret_User1 == shared_secret_User2) {
        printf("Shared secret successfully established!\n");
    } else {
        printf("Error: Shared secret mismatch!\n");
    }

    return 0;
}