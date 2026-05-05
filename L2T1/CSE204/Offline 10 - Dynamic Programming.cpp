#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

string FindLCS(string first, string second) {
    int row = first.length() + 1;
    int col = second.length() + 1;

    int arr[row][col];

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            arr[i][j] = 0;
        }
    }

    for (int i = 1; i < row; i++) {
        for (int j = 1; j < col; j++) {
            if (first[i - 1] == second[j - 1]) {
                arr[i][j] = arr[i - 1][j - 1] + 1;
            } else {
                arr[i][j] = max(arr[i - 1][j], arr[i][j - 1]);
            }
        }
    }

    int r = row - 1, c = col - 1;
    string lcs = "";

    while (arr[r][c] != 0) {
        if (arr[r][c - 1] == arr[r - 1][c]) {
            if (arr[r][c] == arr[r - 1][c - 1] + 1)
                lcs += first[r - 1];  // upore left e paise

            r -= 1;
            c -= 1;
        }

        if (arr[r - 1][c] > arr[r][c - 1]) {
            r -= 1;
        }

        if (arr[r][c - 1] > arr[r - 1][c]) {
            c -= 1;
        }
    }

    reverse(lcs.begin(), lcs.end());
    return lcs;
}

int main() {
    string first, second;

    cout << "Enter first text: ";
    cin >> first;
    cout << "Enter second text: ";
    cin >> second;

    cout << "LCS: " << FindLCS(first, second) << endl;
    return 0;
}
