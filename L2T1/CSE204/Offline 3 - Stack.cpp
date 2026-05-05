#include <bits/stdc++.h>
using namespace std;

#define SIZE 10

template <class X>
class Stack {
    int top = -1;
    X *stk;
    int capacity = SIZE;

   public:
    Stack() {
        stk = new X[capacity];
    }

    int getCapacity() {
        return capacity;
    }

    void push(X data) {
        if (top < capacity - 1) {
            stk[++top] = data;
        }

        else {
            cout << "already 10 items. expanding stack" << endl;

            capacity += SIZE;
            X *temp = new X[capacity];
            cout << "array created " << endl;

            for (int i = 0; i <= top; i++) {
                temp[i] = stk[i];
            }
            cout << "value copied" << endl;

            delete[] stk;
            cout << "stk delete korlam" << endl;

            stk = temp;
            stk[++top] = data;
        }
    }

    X pop() {
        if (!empty()) {
            return stk[top--];
        } else {
            cout << "empty stack - ";
            return stk[0];
        }
    }

    bool empty() {
        return top == -1;
    }

    void print() {
        cout << "size = " << size() << " capacity = " << capacity << endl;
        for (int i = top; i >= 0; i--) {
            cout << stk[i] << ", ";
        }
        cout << endl;
    }

    int size() {
        return top + 1;
    }

    X getTopItem() {
        return stk[top];
    }

    int getTop() {
        return top;
    }
};

void printMenu() {
    cout << " Press 1 : Push |";
    cout << " Press 2 : Pop |";
    cout << " Press 3 : Top |";
    cout << " Press 4 : Size |";
    cout << " Default : Exit " << endl;
    cout << " Enter choice : ";
}

int main(int argc, char const *argv[]) {
    Stack<int> mystk;
    Stack<char> charStk;

    int choice = -1;
    bool menuOn = true;

    while (menuOn) {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                int temp;
                cout << "Enter num to push : ";
                cin >> temp;
                mystk.push(temp);
                break;

            case 2:
                cout << "Pop = " << mystk.pop() << endl;
                ;
                break;

            case 3:
                cout << "Top = " << mystk.getTop() << endl;
                break;

            case 4:
                cout << "Size = " << mystk.size() << endl;
                break;

            default:
                menuOn = false;
                break;
        }
    }
    return 0;
}
