#include <stdio.h>
#include <limits.h>

int main() {
    int n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if(n < 2) {
        printf("Array must contain at least two elements.\n");
        return 0;
    }

    int arr[n];
    printf("Enter %d elements:\n", n);
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    int smallest = INT_MAX;
    int secondSmallest = INT_MAX;

    for(i = 0; i < n; i++) {
        if(arr[i] < smallest) {
            secondSmallest = smallest;
            smallest = arr[i];
        }
        else if(arr[i] < secondSmallest && arr[i] != smallest) {
            secondSmallest = arr[i];
        }
    }

    if(secondSmallest == INT_MAX) {
        printf("No second smallest element found (all elements may be equal).\n");
    } else {
        printf("Second smallest element is: %d\n", secondSmallest);
    }
    return 0;
}
