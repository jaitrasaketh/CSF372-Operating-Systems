#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>

void *compute_pair(void *param);

typedef struct {
    int x;
    int y;
    int index;  // To alternate addition and subtraction
} Pair;

int main() {
    int n;
    printf("Enter a positive integer n: ");
    scanf("%d", &n);

    int num_threads = n / 2;  // Number of pairs
    int is_odd = n % 2 != 0;  // Check if n is odd for handling the last term

    Pair pairs[num_threads];
    pthread_t tid[num_threads];

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    // Create threads to compute each pair
    for (int i = 0; i < num_threads; i++) {
        pairs[i].x = n - 2 * i;      // First term of the pair
        pairs[i].y = n - 2 * i - 1;  // Second term of the pair
        pairs[i].index = i;          // Index to alternate operation
        pthread_create(&tid[i], &attr, compute_pair, (void *)&pairs[i]); // last 2 argument types are void *

    int result = 0;
    void *sum;

    // Join threads and compute the final result
    for (int i = 0; i < num_threads; i++) {
        pthread_join(tid[i], &sum); /// send reference of void * in 2nd argument of pthread_join
        result += (intptr_t)sum;
    }

    // If n is odd, handle the last single term (subtract it)
    if (is_odd) {
        result -= n - 2 * num_threads;
    }

    printf("The result of the series is: %d\n", result);
    return 0;
}

void *compute_pair(void *param) {
    Pair *p = (Pair *)param;
    int sum = p->x + p->y;

    // Alternate between adding and subtracting pairs
    if (p->index % 2 == 1) {
        sum = -sum;  // Subtract odd-indexed pairs
    }

    pthread_exit((void *)(intptr_t)sum);   // argument is void *type
}
