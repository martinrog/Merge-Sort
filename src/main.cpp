#include <vector>
#include <algorithm>
#include <iostream>

void mergeSortIterative(std::vector<int>& arr) {
    int n = arr.size();

    // blokgrootte: 1, 2, 4, enz
    for (int unit = 1; unit < n; unit *= 2) {

        // loop over array per 2 blokken
        for (int left = 0; left < n; left += 2 * unit) {

            int mid = std::min(left + unit, n);
            int right = std::min(left + 2 * unit, n);

            // tijdelijke opslag
            std::vector<int> temp;

            int i = left;  // pointer linkerblok
            int j = mid;   // pointer rechterblok

            // merge zolang beide blokken elementen hebben
            while (i < mid && j < right) {
                if (arr[i] <= arr[j]) {
                    temp.push_back(arr[i]);
                    i++;
                } else {
                    temp.push_back(arr[j]);
                    j++;
                }
            }

            // plak alle resterende elementen van linkerblok
            while (i < mid) {
                temp.push_back(arr[i]);
                i++;
            }

            // plak alle resterende elementen van rechterblok
            while (j < right) {
                temp.push_back(arr[j]);
                j++;
            }

            // terugschrijven naar originele array
            for (int k = 0; k < temp.size(); k++) {
                arr[left + k] = temp[k];
            }
        }
    }
}

// simpele test
int main() {
    std::vector<int> arr = {8, 444, 6, 21, 76, 1, 30, 5000};

    mergeSortIterative(arr);

    for (int x : arr) {
        std::cout << x << " ";
    }
    std::cout << std::endl;

    return 0;
}