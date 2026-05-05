#include <iostream>

#define MAX 1000
using namespace std;

class Node {
   public:
    int data;
    int parent;
    int rank;
};

class DisjointSet {
    Node node[MAX];
    int totalSize = 0;

    void Link(int x, int y) {
        if (node[x].rank > node[y].rank)
            node[y].parent = x;
        else {
            node[x].parent = y;
            if (node[x].rank == node[y].rank)
                node[y].rank = node[y].rank + 1;
        }
    }

   public:
    void makeSet(int x) {
        node[x].parent = x;
        node[x].rank = 0;
        totalSize++;
    }

    int findSet(int x) {
        if (x != node[x].parent)
            node[x].parent = findSet(node[x].parent);

        return node[x].parent;
    }

    void Union(int x, int y) {
        Link(findSet(x), findSet(y));
    }

    void print(int x) {
        for (int i = 0; i < totalSize; i++) {
            if (x == node[i].parent)
                cout << i << " ";
        }
        cout << endl;
    }

    int getSize() {
        return totalSize;
    }
};

void printMenu() {
    cout << endl;
    cout << "1. Make Set" << endl;
    cout << "2. Find Set" << endl;
    cout << "3. Union" << endl;
    cout << "4. Print Set" << endl;
    cout << "5. Total size " << endl;
    cout << "Anything else to exit" << endl;
    cout << "Enter a choice: ";
}

int main() {
    int choice, temp, tempx;
    bool isOn = true;

    DisjointSet ds;

    while (isOn) {
        printMenu();
        cin >> choice;

        if (choice == 1) {
            cout << "Enter a number to make set: ";
            cin >> temp;

            ds.makeSet(temp);
        } else if (choice == 2) {
            cout << "Enter number to find set: ";
            cin >> temp;

            cout << "The set is in: " << ds.findSet(temp) << endl;
        } else if (choice == 3) {
            cout << "Enter 2 numbers to union sets: ";

            cin >> temp >> tempx;
            ds.Union(temp, tempx);
        } else if (choice == 4) {
            cout << "Enter parent to print set: ";

            cin >> temp;
            ds.print(temp);
        } else if (choice == 6) {
            cout << "Current set size: " << ds.getSize() << endl;
        } else {
            isOn = false;
        }
    }

    cout << endl
         << "- - program ended - -" << endl;
    return 0;
}
