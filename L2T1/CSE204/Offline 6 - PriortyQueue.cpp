#include <algorithm>
#include <iostream>
using namespace std;

#define SIZE 30
#define INFINITY 9999999
#define GARBAGE 66666666

class PriorityQueue {
    int *data;
    int largest, heapSize;

   public:
    PriorityQueue();
    ~PriorityQueue();
    void MaxHeapify(int i);
    void IncreaseKey(int i, int key);
    void DecreaseKey(int i, int key);
    void Insert(int key);
    void Print();

    int FindMax();
    int ExtractMax();
    int Length();
    int Parent(int i);
    int Left(int i);
    int Right(int i);
    int HeapSize();
};

PriorityQueue::PriorityQueue() {
    data = new int[SIZE];
    data[0] = 0;
    heapSize = 0;
    largest = 0;
}

int PriorityQueue::Parent(int i) {
    return i / 2;
}

int PriorityQueue::Left(int i) {
    return 2 * i;
}

int PriorityQueue::Right(int i) {
    return 2 * i + 1;
}

int PriorityQueue::FindMax() {
    return data[1];
}

int PriorityQueue::HeapSize() {
    heapSize = data[0];
    return heapSize;
}

void PriorityQueue::MaxHeapify(int i) {
    int l = Left(i);
    int r = Right(i);

    if ((l <= data[0]) && (data[l] > data[i]))
        largest = l;
    else
        largest = i;

    if ((r <= data[0]) && (data[r] > data[largest]))
        largest = r;

    if (largest != i) {
        swap(data[i], data[largest]);
        MaxHeapify(largest);
    }
}

int PriorityQueue::Length() {
    return heapSize;
}

void PriorityQueue::Print() {
    for (int i = 1; i <= data[0]; i++)
        cout << data[i] << "   ";
    cout << endl;
}

int PriorityQueue::ExtractMax() {
    if (data[0] < 1) {
        cout << " Heap Underflow " << endl;
        return GARBAGE;
    }

    int max = data[1];
    data[1] = data[data[0]];
    data[0]--;
    MaxHeapify(1);

    return max;
}

void PriorityQueue::IncreaseKey(int i, int key) {
    if (key < data[i])
        cout << " Key is smaller than current one " << endl;

    data[i] = key;
    while ((i > 1) && (data[Parent(i)] < data[i])) {
        swap(data[Parent(i)], data[i]);
        i = Parent(i);
    }
}

void PriorityQueue::DecreaseKey(int i, int key) {
    if (key > data[i])
        cout << " Key is larger than current " << endl;

    data[i] = key;
    MaxHeapify(i);
}

void PriorityQueue::Insert(int key) {
    heapSize++;
    data[0]++;

    data[data[0]] = -INFINITY;
    IncreaseKey(heapSize, key);
}

PriorityQueue::~PriorityQueue() {
    delete data;
}

int main() {
    PriorityQueue q;
    int choice = -1, value, key;

    while (true) {
        cout << "1. Insert      2. Find Max     3. Extract Max" << endl;
        cout << "4. Incr. Key   5. Decr. Key    6. Print        7. Exit" << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - -" << endl;

        cin >> choice;
        if (choice == 1) {
            cout << "Insert : ";
            cin >> value;
            q.Insert(value);
        } else if (choice == 2) {
            cout << "Max is : " << q.FindMax() << endl;
        } else if (choice == 3) {
            cout << "Extracted Max : " << q.ExtractMax() << endl;
        } else if (choice == 4) {
            cout << "Incr. Enter (i key) : ";
            cin >> value >> key;
        } else if (choice == 5) {
            cout << "Decr. Enter (i key) : ";
            cin >> value >> key;
        } else if (choice == 6) {
            cout << endl
                 << "Current Priority Queue : " << endl;
            q.Print();
            cout << endl;
        } else if (choice == 7) {
            break;
        }
    }

    return 0;
}
