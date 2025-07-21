#include <stdio.h>
#include <stdlib.h>


int compareIntergers(const void *a, const void *b);
int readIntergers(const char *prompt);
void printArray(const int *arr, int size);



int main() {
    int n = readIntergers("Enter number of elements: ");
    if (n <= 0) {
        printf("Array size must be positive.\n");
        return 1;
    }

    int *arr = malloc(n * sizeof(int));
    if (!arr) {
        perror("Failed to allocate memory");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        arr[i] = readIntergers("> ");
    }

    qsort(arr, n, sizeof(int), compareIntergers);
    printArray(arr, n);

    int target = readIntergers("Enter a number to search: ");
    int *found = bsearch(&target, arr, n, sizeof(int), compareIntergers);

    if (found) {
        printf("✅ Number %d found at index %ld.\n", target, found - arr);
    } else {
        printf("❌ Number %d not found.\n", target);
    }

    free(arr);
    return 0;
}

// Function to compare integers (for qsort and bsearch)
int compareIntergers(const void *a, const void *b) {
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;
    return (int_a > int_b) - (int_a < int_b);  // avoids overflow
}

// Function to safely read an integer from input
int readIntergers(const char *prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        printf("Invalid input. Try again: ");
        while (getchar() != '\n'); // flush stdin
    }
    return value;
}

// Function to print the array
void printArray(const int *arr, int size) {
    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
