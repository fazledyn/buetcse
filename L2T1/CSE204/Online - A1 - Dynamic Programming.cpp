// Printing Shortest Common Supersequence

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

string SCS(string first, string second) {
    int row = first.length() + 1;
    int col = second.length() + 1;

    int matrix[row][col];

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i == 0)
                matrix[i][j] = j;
            else if (j == 0)
                matrix[i][j] = i;
            else if (first[i - 1] == second[j - 1])
                matrix[i][j] = 1 + matrix[i - 1][j - 1];
            else
                matrix[i][j] = 1 + min(matrix[i][j - 1], matrix[i - 1][j]);
        }
    }

    int i = row - 1, j = col - 1;
    string scs = "";

    while (i > 0 && j > 0) {
        if (first[i - 1] == second[j - 1]) {
            scs += first[i - 1];
            i--, j--;
        }

        else if (matrix[i][j - 1] > matrix[i - 1][j]) {
            scs += first[i - 1];
            i--;
        }

        else if (matrix[i - 1][j] > matrix[i][j - 1]) {
            scs += second[j - 1];
            j--;
        }
    }

    while (i > 0) {
        scs += first[i - 1];
        i--;
    }

    while (j > 0) {
        scs += second[j - 1];
        j--;
    }

    reverse(scs.begin(), scs.end());
    return scs;
}

int main() {
    string first, second;

    cin >> first;
    cin >> second;
    cout << "SCS: " << SCS(first, second) << endl;
    return 0;
}
