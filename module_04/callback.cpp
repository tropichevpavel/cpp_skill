
#include <iostream>

bool min(const int& a, const int& b) {
    return a < b;
}

bool max(const int& a, const int& b) {
    return a > b;
}

void bubbleSort(int arr[], const int& n, bool (*compare)(const int&, const int&)) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i - 1; j++)
            if ((*compare)(arr[j], arr[j + 1])) {
                arr[j] ^= arr[j + 1];
                arr[j + 1] ^= arr[j];
                arr[j] ^= arr[j + 1];
            }
}

int main() {

    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    bubbleSort(arr, sizeof(arr) / sizeof(arr[0]), max);

    for (int i = 0; i < 10; i++) {
        std::cout << arr[i] << std::endl;
    }

    return 0;
}