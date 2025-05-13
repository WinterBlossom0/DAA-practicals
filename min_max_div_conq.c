#include <stdio.h>
#define MAX 100

// Use pointers to return both min and max
void min_max(int arr[], int low, int high, int *min, int *max) {
    // Base case: Only one element
    if (low == high) {
        *min = arr[low];
        *max = arr[low];
        return;
    }
    
    // Base case: Only two elements
    if (low + 1 == high) {
        if (arr[low] < arr[high]) {
            *min = arr[low];
            *max = arr[high];
        } else {
            *min = arr[high];
            *max = arr[low];
        }
        return;
    }
    
    // Divide: Find midpoint
    int mid = (low + high) / 2;
    
    // Variables to store results from recursive calls
    int left_min, left_max, right_min, right_max;
    
    // Conquer: Recursively find min and max in both halves
    min_max(arr, low, mid, &left_min, &left_max);
    min_max(arr, mid + 1, high, &right_min, &right_max);
    
    // Combine: Find overall min and max
    *min = (left_min < right_min) ? left_min : right_min;
    *max = (left_max > right_max) ? left_max : right_max;
}

int main() {
    int arr[MAX];
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    
    printf("Enter the elements:\n");
    for(int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    
    int min, max;
    min_max(arr, 0, n-1, &min, &max);
    
    printf("Minimum: %d, Maximum: %d\n", min, max);
    return 0;
}
