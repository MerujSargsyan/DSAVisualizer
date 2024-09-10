#include <animlib.h>

typedef struct {
    int val;
    int position;
} merge_entry;

int arr[] = {2, 4, 6, 3, 8, 1, 9};

void print_arr() {
    for(int i = 0; i < 7; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void merge(int left, int middle, int right, merge_entry* aux) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    merge_entry temp_l[n1];
    merge_entry temp_r[n2];

    for(int i = 0; i < n1; i++) {
        temp_l[i] = aux[left + i];
    }
    for(int i = 0; i < n2; i++) {
        temp_r[i] = aux[middle + 1 + i];
    }

    // here is where processes probably happen
    int i = 0;
    int j = 0;
    int k = left;
    while(i < n1 && j < n2) {
        if(temp_l[i].val <= temp_r[j].val) {
            arr[k] = temp_l[i].val;
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

        printf("left: %d, middle:%d\n", left, middle);
        merge_sort(left, middle);
        printf("middle:%d, right:%d\n", middle, right);
        merge_sort(middle+1, right);

        printf("merging: %d, %d, %d\n", left, middle, right);
        merge(left, middle, right);
    }
}

int main(void) {
    merge_sort(0, 7);
    print_arr();
    return 0;
}
