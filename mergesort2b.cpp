#include <iostream>
#include <vector>
#include <thread>
#include <omp.h>
#include <fstream>
using namespace std;

// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(vector<int>& arr, int left, 
                     int mid, int right){
                         
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back 
    // into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], 
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], 
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(vector<int>& arr, int left, int right){

    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Parallele versie van merge sort.
// numThreads geeft aan hoeveel threads deze aanroep maximaal mag gebruiken.
void threadedMergeSort(vector<int>& arr, int left, int right, int numThreads) {

    if (left >= right)
        return;

    // Als er nog maar 1 thread beschikbaar is,
    // ga dan verder met de sequentiële versie.
    if (numThreads <= 1) {
        mergeSort(arr, left, right);
        return;
    }

    int mid = left + (right - left) / 2;

    // Verdeel het aantal beschikbare threads over beide helften.
    // Bijvoorbeeld:
    // 4 -> links 2, rechts 2
    // 3 -> links 1, rechts 2
    int leftThreads = numThreads / 2;
    int rightThreads = numThreads - leftThreads;

    // Sorteer linker- en rechterhelft parallel.
    thread leftThread(threadedMergeSort, ref(arr), left, mid, leftThreads);
    thread rightThread(threadedMergeSort, ref(arr), mid + 1, right, rightThreads);

    // Wacht tot beide threads klaar zijn voordat we gaan mergen.
    leftThread.join();
    rightThread.join();

    // Voeg daarna de twee gesorteerde helften samen.
    merge(arr, left, mid, right);
}


vector<int> readArray(const string& filename) {
    ifstream file(filename);

    if (!file) {
        cerr << "Error: file niet gevonden!" << endl;
        exit(1);
    }

    int n;
    file >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        file >> arr[i];
    }

    return arr;
}

// Driver code
int main(int argc, char* argv[]){
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }

    vector<int> arr = readArray(std::string(argv[1]));
    int n = arr.size();

    // Kies hier het aantal threads: 1, 2, 4 of 8
    int numThreads = 1;

    double start = omp_get_wtime();

    threadedMergeSort(arr, 0, n - 1, numThreads);

    double end = omp_get_wtime();

    cout << "Threads: " << numThreads 
        << " | Tijd: " << (end - start) << " sec" << endl;

    // for (int i = 0; i < arr.size(); i++)
    //     cout << arr[i] << " ";
    // cout << endl;

    return 0;
}