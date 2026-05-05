#include <cstdlib>
#include <iostream>
using namespace std;

class Activity {
   public:
    int id;
    int start, end;

    Activity() {
        start = abs(rand());
        end = start + abs(rand());
    }
};

void printActivity(Activity act[], int size) {
    for (int i = 0; i < size; i++)
        cout << i << " start: " << act[i].start << " end: " << act[i].end << endl;
}

void GreedyAlgorithm(Activity act[], int size) {
    for (int i = 0; i < size; i++)
        act[i].id = i;

    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < size; j++)
            if (act[j].end < act[minIndex].end)
                minIndex = j;

        Activity temp = act[minIndex];

        act[minIndex] = act[i];
        act[i] = temp;
    }

    int curr = 0;
    cout << endl
         << "Selected activities : ";
    cout << endl
         << "Acitivity : " << curr << endl;

    for (int i = 1; i < size; i++) {
        if (act[i].start >= act[curr].end) {
            curr = i;
            cout << "Activity : " << act[curr].id << endl;
        }
    }
}

int main() {
    int sampleSize;

    cout << "Enter sample size: ";
    cin >> sampleSize;
    cout << endl;

    Activity act[sampleSize];

    printActivity(act, sampleSize);
    GreedyAlgorithm(act, sampleSize);

    return 0;
}
