#include <bits/stdc++.h>
using namespace std;

#define SIZE 10

template <class X>
class Queue {
    int front = 0, rear = -1;
    X *que;
    int capacity = SIZE;

   public:
    Queue() {
        que = new X[capacity];
    }

    int getCapacity() {
        return capacity;
    }

    void enQueue(X data) {
        if (size() < capacity - 1) {
            que[++rear] = data;
        } else {
            cout << "already 10 items. increasing... " << endl;

            capacity += SIZE;
            X *temp = new X[capacity];

            for (int i = front; i <= rear; i++) {
                temp[i] = que[i];
            }
            delete[] que;

            que = temp;
            que[++rear] = data;
        }
    }

    X deQueue() {
        if (!empty()) {
            return que[front++];
        } else {
            cout << "empty queue : ";
            return que[0];
        }
    }

    bool empty() {
        return front > rear;
    }

    void print() {
        for (int i = front; i <= rear; i++) {
            cout << que[i] << ", ";
        }
        cout << endl;
        cout << "front = " << front << " rear = " << rear << endl;
        cout << "capacity = " << capacity << " size = " << size() << endl;
    }

    int size() {
        return (rear - front) + 1;
    }

    int getFront() {
        return front;
    }

    int getRear() {
        return rear;
    }
};

void printMenu() {
    cout << " Press 1 : enQueue |";
    cout << " Press 2 : deQueue |";
    cout << " Press 3 : Front |";
    cout << " Press 4 : Rear |";
    cout << " Press 5 : Size |";
    cout << " Default : Exit " << endl;
    cout << " Enter choice : ";
}

int main() {
    Queue<int> q;

    bool menuOn = true;
    int choice = -1;

    while (menuOn) {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                int temp;
                cout << "Enter number to enQueue : ";
                cin >> temp;
                q.enQueue(temp);
                break;

            case 2:
                cout << "deQueue = " << q.deQueue() << endl;
                break;

            case 3:
                cout << "Front = " << q.getFront() << endl;
                break;

            case 4:
                cout << "Rear = " << q.getRear() << endl;
                break;

            case 5:
                cout << "Size = " << q.size() << endl;
                break;

            default:
                menuOn = false;
                break;
        }
    }
    return 0;
}
