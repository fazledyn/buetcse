#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;
using namespace std::chrono;

void PrintSubset(string word, int index, string current) {
    int len = word.length();

    for (int currIdx = index + 1; currIdx < len; currIdx++) {
        current += word[currIdx];
        cout << current << ", ";
        PrintSubset(word, currIdx, current);
        current.erase(current.length() - 1);
    }
}

void PrintDistinctSubset(string word, int index, string current) {
    for (int i = 0; i < word.length(); i++) {
        for (int j = i + 1; j < word.length(); j++)
            if (word[i] == word[j])
                word.erase(j, 1);
    }
    PrintSubset(word, -1, "");
}

int main(int argc, char const *argv[]) {
    string inputStr;
    static string alphaNumString = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int sampleSize;

    high_resolution_clock::time_point start, end, start2, end2;

    cout << "Enter sample size : ";
    cin >> sampleSize;

    for (int i = 0; i < sampleSize; i++) {
        inputStr += alphaNumString[rand() % alphaNumString.length()];
    }
    inputStr[sampleSize] = 0;

    cout << "Random String : " << inputStr << endl;

    cout << "The distinct subsets : { ";
    start2 = high_resolution_clock::now();
    PrintDistinctSubset(inputStr, -1, "");
    end2 = high_resolution_clock::now();
    cout << "}" << endl;

    auto time = duration_cast<microseconds>(end - start).count();

    cout << "Subset generation time (us) : " << time << endl;
    auto time2 = duration_cast<microseconds>(end2 - start2).count();
    cout << "Subset generation time - distinct (us) : " << time2 << endl;

    return 0;
}
