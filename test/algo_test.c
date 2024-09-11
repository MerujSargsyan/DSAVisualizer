#include <animlib.h>

int arr[] = {2, 4, 6, 3, 8, 1, 9};

void print_arr() {
    for(int i = 0; i < 7; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void swap(int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void merge(int s1, int s2) {
    int i = s1;
    int j = s2;
    int n = s2 - s1; // get back n
    while(i - s1 <= n && j - s2 <= n) {
        if(arr[i] > arr[j]) {
            swap(i, j);
            i++;
        } else {
            j++;
        } 
    }
}

void merge_sort() {
    int n = 1;
    while(n < len(arr)) {
        for(int i = 0; i + n < len(arr); i++) {
            merge(i, i + n);
        }
        n *= 2;
    }
}

int main(void) {
    merge_sort();
    print_arr();
    return 0;
}
