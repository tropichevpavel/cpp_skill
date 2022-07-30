
#include <iostream>

void printKMax(int arr[], int n, int k) {
    
	for (int i = 0; i < n - k + 1; ++i) {
        int max = arr[i];
        for (int j = i + 1; j < i + k; ++j)
            max = max < arr[j] ? arr[j] : max;

        std::cout << max << " ";
    }
}

int main() {
	int size = 9;
	int arr[size];
	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;
	arr[3] = 1;
	arr[4] = 4;
	arr[5] = 5;
	arr[6] = 2;
	arr[7] = 3;
	arr[8] = 6;

	printKMax(arr, size, 3);
	return 0;
}
