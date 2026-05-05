#include <chrono>
#include <iostream>
using namespace std;

int binarySearch(int arr[], int size, int target) {
    int low = 0, high = size - 1;
    int index = (low + high) / 2;

    while (low <= high) {
        if (arr[index] < target) {
            low = index + 1;
        } else if (arr[index] == target) {
            break;
        } else {
            high = index - 1;
        }
        index = (low + high) / 2;
    }

    if (low > high) {
        index = -1;  // not found
    }
    return index;
}

int linearSearch(int arr[], int size, int target) {
    int index = -1;
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            index = i;
        }
    }
    return index;
}

void timeCountFunction(int sampleSize) {
    using namespace std::chrono;
    cout << "For sample size : " << sampleSize << endl;

    int number[sampleSize];
    for (int i = 0; i < sampleSize; i++) {
        number[i] = rand();
    }

    //  sorting the array
    int temp = 0;
    for (int i = 0; i < sampleSize - 1; i++) {
        for (int j = 0; j < sampleSize - i - 1; j++) {
            if (number[j] > number[j + 1]) {
                temp = number[j];
                number[j] = number[j + 1];
                number[j + 1] = temp;
            }
        }
    }

    int find = rand();  // the int to find

    high_resolution_clock::time_point startLS = high_resolution_clock::now();
    cout << find << " found in index = " << linearSearch(number, sampleSize, find) << " for linear search" << endl;
    high_resolution_clock::time_point endLS = high_resolution_clock::now();

    high_resolution_clock::time_point startBS = high_resolution_clock::now();
    cout << find << " found in index = " << binarySearch(number, sampleSize, find) << " for binary search" << endl;
    high_resolution_clock::time_point endBS = high_resolution_clock::now();

    duration<double> linearTime = duration_cast<duration<double>>(endLS - startLS);
    duration<double> binaryTime = duration_cast<duration<double>>(endBS - startBS);

    cout << "Time(microSecond) for Linear Search = " << 1000000 * linearTime.count() << endl;
    cout << "Time(microSecond) for Binary Search = " << 1000000 * binaryTime.count() << endl;
    cout << endl;
}

int main() {
    int choice, sampleSize;
    cout << "1) Custom input    2) Automatic input" << endl;
    cout << "Enter choice : ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter custom sample size : ";
        cin >> sampleSize;
        timeCountFunction(sampleSize);
    } else if (choice == 2) {
        int sampleArray[8] = {10, 100, 200, 500, 1000, 2000, 5000, 10000};
        for (int i = 0; i < 8; i++) {
            timeCountFunction(sampleArray[i]);
        }
    }
    return 0;
}
