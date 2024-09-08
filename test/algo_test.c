#include <animlib.h>

int arr[] = {2, 4, 6, 3, 8, 1, 9};

void print_arr() {
    for(int i = 0; i < 7; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void merge(int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    int temp_l[n1];
    int temp_r[n2];

    for(int i = 0; i < n1; i++) {
        temp_l[i] = arr[left + i];
    }
    for(int i = 0; i < n2; i++) {
        temp_r[i] = arr[middle + 1 + i];
    }

    // here is where processes probably happen
    int i = 0;
    int j = 0;
    int k = left;
    while(i < n1 && j < n2) {
        if(temp_l[i] <= temp_r[j]) {
            arr[k] = temp_l[i];
            i++;
        } else {
            arr[k] = temp_r[j];
            j++;
        }
        k++;
    }

    while(i < n1) {
        arr[k] = temp_l[i];
        i++;
        k++;
    }

    while(j < n2) {
        arr[k] = temp_r[j];
        j++;
        k++;
    }
}

void merge_sort(int left, int right) {
    if(left < right) {
        int middle = left + (right - left) / 2;

        merge_sort(left, middle);
        merge_sort(middle+1, right);

        merge(left, middle, right);
    }
}

int main(void) {
    merge_sort(0, 7);
    print_arr();
    return 0;
}
