#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>

#define MAX 9999
using namespace std;
using namespace std::chrono;

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1, MAX);

void averageCase(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = dis(gen);
    }
}

void bestCase(int *arr, int n) {
    arr[0] = abs(dis(gen));
    for (int i = 1; i < n; i++) {
        arr[i] = arr[i - 1] + abs(dis(gen));
    }
}

void worstCase(int *arr, int n) {
    arr[n - 1] = 0;
    for (int i = n - 1; i >= 0; i--) {
        arr[i - 1] = arr[i] + abs(dis(gen));
    }
}

void merge(int *arr, int left, int mid, int right) {
    int nLeft = mid - left + 1;
    int nRight = right - mid;
    int Left[nLeft], Right[nRight];

    for (int i = 0; i < nLeft; i++) Left[i] = arr[left + i];

    for (int i = 0; i < nRight; i++) Right[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while ((i < nLeft) && (j < nRight)) {
        if (Left[i] <= Right[j]) {
            arr[k] = Left[i];
            i++;
        } else {
            arr[k] = Right[j];
            j++;
        }
        k++;
    }

    while (i < nLeft) {
        arr[k] = Left[i];
        i++;
        k++;
    }

    while (j < nRight) {
        arr[k] = Right[j];
        j++;
        k++;
    }
}

void mergeSort(int *num, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(num, left, mid);
        mergeSort(num, mid + 1, right);
        merge(num, left, mid, right);
    }
}

int divide(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);

    return i + 1;
}

void quickSort(int *arr, int low, int high) {
    if (low < high) {
        int idx = divide(arr, low, high);

        quickSort(arr, low, idx - 1);
        quickSort(arr, idx + 1, high);
    }
}

void printArray(int *arr, int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int choice, n;
    int *arr1, *arr2;
    high_resolution_clock::time_point start, end;

    bool on = true;
    while (on) {
        cout << "1. Generate average case \n";
        cout << "2. Generate best case \n";
        cout << "3. Generate worst case \n";
        cout << "4. Apply Merge sort \n";
        cout << "5. Apply Quicksort \n";
        cout << "6. Print array \n";
        cout << "7. Exit \n";
        cout << "> ";

        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Number of elements: ";
                cin >> n;
                arr1 = new int[n];
                arr2 = new int[n];
                averageCase(arr1, n);
                averageCase(arr2, n);
                break;

            case 2:
                cout << "Number of elements: ";
                cin >> n;
                arr1 = new int[n];
                arr2 = new int[n];
                bestCase(arr1, n);
                bestCase(arr2, n);
                break;

            case 3:
                cout << "Number of elements: ";
                cin >> n;
                arr1 = new int[n];
                arr2 = new int[n];
                worstCase(arr1, n);
                worstCase(arr2, n);
                break;

            case 4: {
                cout << "Applying merge sort\n";

                start = high_resolution_clock::now();
                mergeSort(arr1, 0, n - 1);
                end = high_resolution_clock::now();
                auto time1 = duration_cast<microseconds>(end - start).count();

                cout << "Time taken to finish(us) : " << time1 << endl;
                break;
            }

            case 5: {
                cout << "Applying quicksort\n";

                start = high_resolution_clock::now();
                quickSort(arr2, 0, n - 1);
                end = high_resolution_clock::now();
                auto time2 = duration_cast<microseconds>(end - start).count();

                cout << "Time taken to finish(us) : " << time2 << endl;
                break;
            }

            case 6:
                cout << "Array(M): ";
                printArray(arr1, n);
                cout << endl
                     << "Array(Q): ";
                printArray(arr2, n);
                break;

            default:
                on = false;
                break;
        }
    }
}
