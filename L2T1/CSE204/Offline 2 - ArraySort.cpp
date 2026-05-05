#include <chrono>
#include <cstdlib>
#include <iostream>
#include <ratio>

using namespace std;
using namespace std::chrono;

void SelectionSort(int arr[], int arraySize) {  //  Descending Order
    int minIndex;
    high_resolution_clock::time_point start, end;

    start = high_resolution_clock::now();

    for (int i = 0; i < arraySize - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < arraySize; j++)
            if (arr[j] > arr[minIndex])
                minIndex = j;

        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
    end = high_resolution_clock::now();

    auto time = duration_cast<microseconds>(end - start).count();
    cout << "Selection sort time (us) : " << time << endl;
}

void InsertionSort(int arr[], int arraySize) {  //  Ascending order

    int key = 0, j;
    ;
    high_resolution_clock::time_point start, end;

    start = high_resolution_clock::now();

    for (int i = 1; i < arraySize; i++) {
        key = arr[i];

        for (j = i - 1; (j >= 0) && (arr[j] > key); j--) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    end = high_resolution_clock::now();

    auto time = duration_cast<microseconds>(end - start).count();
    cout << "Insertion sort time (us) : " << time << endl;
}

void PrintArray(int arr[], int arraySize) {
    for (int i = 0; i < arraySize; i++)
        cout << arr[i] << "  ";
}

int main(int argc, char **argv) {
    srand(time(0));

    int sampleSize;
    cout << "Enter your sample size : ";
    cin >> sampleSize;

    int number1[sampleSize], number2[sampleSize];

    for (int i = 0; i < sampleSize; i++) {
        number1[i] = rand();
        number2[i] = rand();
    }

    cout << endl
         << "Time count for average case : " << endl;
    InsertionSort(number2, sampleSize);
    SelectionSort(number1, sampleSize);

    cout << endl
         << "Time count for best case : " << endl;
    InsertionSort(number2, sampleSize);
    SelectionSort(number1, sampleSize);

    cout << endl
         << "Time count for worst case : " << endl;
    InsertionSort(number1, sampleSize);
    SelectionSort(number2, sampleSize);

    return 0;
}
