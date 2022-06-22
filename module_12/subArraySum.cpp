
#include <iostream>

bool subArraySum(int arr[], int n, int sum) 
{
    for (int i = 0; i < n; ++i) {
        
        if (arr[i] == sum) {
            std::cout << i << " " << i << std::endl;
            return true;
        }
        
        int summ = arr[i];
        
        for (int j = i + 1; j < n; ++j) {
            summ += arr[j];
            
            if (summ > sum) break;
            else if (summ == sum) {
                std::cout << i << " " << j << std::endl;
                return true;
            }
        }
    }

    std::cout << "-1" << std::endl;
    return false;
} 

int main() {

    int arr[5] = {10, 21, 22, 34, 55};
    subArraySum(arr, 5, 113);

    return 0;
}