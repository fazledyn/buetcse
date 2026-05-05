#include <stdlib.h>

#include <iostream>
using namespace std;

#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

class Queue {
    int queueInitSize;
    int queueMaxSize;
    int *data;
    int length;
    int front;
    int rear;

   public:
    Queue();
    ~Queue();
    void enqueue(int item);  // insert item in the queue
    int dequeue();           // returns the item according to FIFO
    bool empty();            // return true if Queue is empty
};

Queue::Queue() {
    queueInitSize = 2;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize];  // allocate initial memory
    length = 0;
    front = 0;
    rear = 0;
}

void Queue::enqueue(int item) {
    if (length == queueMaxSize) {
        int *tempData;
        // allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize;
        tempData = new int[queueMaxSize];
        int i, j;
        j = 0;
        for (i = rear; i < length; i++) {
            tempData[j++] = data[i];  // copy items from rear
        }
        for (i = 0; i < rear; i++) {
            tempData[j++] = data[i];  // copy items before rear
        }
        rear = 0;
        front = length;
        delete[] data;    // free the memory allocated before
        data = tempData;  // make list to point to new memory
    }

    data[front] = item;  // store new item
    front = (front + 1) % queueMaxSize;
    length++;
}

bool Queue::empty() {
    if (length == 0)
        return true;
    else
        return false;
}

int Queue::dequeue() {
    if (length == 0)
        return NULL_VALUE;
    int item = data[rear];
    rear = (rear + 1) % queueMaxSize;  // circular queue implementation
    length--;
    return item;
}

Queue::~Queue() {
    if (data)
        delete[] data;  // deallocate memory
    data = 0;           // set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList {
    int *list;
    int length;
    int listMaxSize;
    int listInitSize;

   public:
    ArrayList();
    ~ArrayList();
    int searchItem(int item);
    void insertItem(int item);
    void removeItem(int item);
    void removeItemAt(int item);
    int getItem(int position);
    int getLength();
    bool empty();
    void printList();
};

ArrayList::ArrayList() {
    listInitSize = 2;
    listMaxSize = listInitSize;
    list = new int[listMaxSize];
    length = 0;
}

void ArrayList::insertItem(int newitem) {
    int *tempList;
    if (length == listMaxSize) {
        // allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize;  // doubling memory when array is full
        tempList = new int[listMaxSize];
        int i;
        for (i = 0; i < length; i++) {
            tempList[i] = list[i];  // copy all items from list to tempList
        }
        delete[] list;    // free the memory allocated before
        list = tempList;  // make list to point to new memory
    };

    list[length] = newitem;  // store new item
    length++;
}

int ArrayList::searchItem(int item) {
    int i = 0;
    for (i = 0; i < length; i++) {
        if (list[i] == item)
            return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) {  // do not preserve order of items
    if (position < 0 || position >= length)
        return;  // nothing to remove
    list[position] = list[length - 1];
    length--;
}

void ArrayList::removeItem(int item) {
    int position;
    position = searchItem(item);
    if (position == NULL_VALUE)
        return;  // nothing to remove
    removeItemAt(position);
}

int ArrayList::getItem(int position) {
    if (position < 0 || position >= length)
        return NULL_VALUE;
    return list[position];
}

int ArrayList::getLength() {
    return length;
}

bool ArrayList::empty() {
    if (length == 0)
        return true;
    else
        return false;
}

void ArrayList::printList() {
    int i;
    for (i = 0; i < length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList() {
    if (list)
        delete[] list;
    list = 0;
}

class Graph {
    int nVertices, nEdges;
    bool directed;
    ArrayList *adjList;
    int *color;
    int *parent;
    int *dist;

   public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u, bool out);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source);
};

Graph::Graph(bool dir) {
    nVertices = 0;
    nEdges = 0;
    adjList = 0;
    directed = dir;
}

void Graph::setnVertices(int n) {
    this->nVertices = n;
    if (adjList != 0)
        delete[] adjList;  // delete previous list
    adjList = new ArrayList[nVertices];
}

void Graph::addEdge(int u, int v) {
    if (u < 0 || v < 0 || u >= nVertices || v >= nVertices)
        return;  // vertex out of range
    this->nEdges++;
    adjList[u].insertItem(v);
    if (!directed)
        adjList[v].insertItem(u);
}

void Graph::removeEdge(int u, int v) {
    if (u < 0 || v < 0 || u >= nVertices || v >= nVertices)
        return;
    this->nEdges--;
    adjList[u].removeItem(v);
    if (!directed)
        adjList[v].removeItem(u);
}

bool Graph::isEdge(int u, int v) {
    for (int i = 0; i < adjList[u].getLength(); i++) {
        if (adjList[u].getItem(i) == v) {
            return true;
        }
    }
    return false;
}

int Graph::getDegree(int u, bool out = true) {
    if (out) {
        return adjList[u].getLength();
    } else {
        int deg = 0;
        for (int i = 0; i < nVertices; i++) {
            for (int j = 0; j < adjList[i].getLength(); i++) {
                if (adjList[i].getItem(j) == u) {
                    deg++;
                }
            }
        }
        return deg;
    }
}

void Graph::printAdjVertices(int u) {
    for (int i = 0; i < adjList[u].getLength(); i++) {
        cout << adjList[u].getItem(i) << " ";
    }
}

bool Graph::hasCommonAdjacent(int u, int v) {
    for (int i = 0; i < adjList[u].getLength(); i++) {
        for (int k = 0; k < adjList[v].getLength(); k++) {
            if (adjList[u].getItem(i) == adjList[v].getItem(k)) {
                return true;
            }
        }
    }
    return false;
}

void Graph::bfs(int source) {
    color = new int[nVertices];
    dist = new int[nVertices];
    parent = new int[nVertices];

    for (int i = 0; i < nVertices; i++) {
        color[i] = WHITE;
        dist[i] = NULL_VALUE;
        parent[i] = -1;
    }

    Queue q;
    dist[source] = 0;
    q.enqueue(source);

    while (!q.empty()) {
        int u = q.dequeue();

        for (int i = 0; i < adjList[source].getLength(); i++) {
            if ((adjList[u].getItem(i) == 1) && (color[i] == WHITE)) {
                color[i] = GREY;
                dist[i] = dist[u] + 1;
                parent[i] = u;
                q.enqueue(i);
            }
        }
        color[u] = BLACK;
    }
}

int Graph::getDist(int u, int v) {
    this->bfs(u);
    return dist[v];
}

void Graph::printGraph() {
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for (int i = 0; i < nVertices; i++) {
        printf("%d:", i);
        for (int j = 0; j < adjList[i].getLength(); j++) {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph() {
    delete adjList;
    delete color;
    delete parent;
    delete dist;
}

int main(void) {
    int n;
    int choice;
    bool dir;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d", &choice);
    if (choice == 1)
        dir = true;
    else if (choice == 2)
        dir = false;

    Graph g(dir);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while (1) {
        printf("1. Add Edge         2. Remove Edge         3. Is Edge \n");
        printf("4. Has Common Edge  5. Print Graph         6. Get Degree\n");
        printf("7. Distance         8. Print Adj vertices  9. Exit \n");

        int ch;
        scanf("%d", &ch);
        if (ch == 1) {
            int u, v;
            scanf("%d %d", &u, &v);
            g.addEdge(u, v);
        } else if (ch == 2) {
            int u, v;
            cout << "Enter edges to remove (u v) : ";
            scanf("%d %d", &u, &v);
            g.removeEdge(u, v);
        } else if (ch == 3) {
            int u, v;
            cout << "Enter edges to see if edge or not (u v) : ";
            scanf("%d %d", &u, &v);
            if (g.isEdge(u, v))
                cout << "yes" << endl;
            else
                cout << "no" << endl;
        } else if (ch == 4) {
            int u, v;
            cout << "Enter vertices (u v) : ";
            scanf("%d %d", &u, &v);
            if (g.hasCommonAdjacent(u, v)) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        } else if (ch == 5) {
            g.printGraph();
        } else if (ch == 6) {
            int u, option;
            cout << "Enter vertice to get degree : ";
            cin >> u;
            cout << "Enter 1) In degree   2) Out degree : ";
            cin >> option;
            if (option == 1) {
                cout << "Degree = " << g.getDegree(u, false) << endl;
            } else {
                cout << "Degree = " << g.getDegree(u) << endl;
            }
        } else if (ch == 7) {
            int u, v;
            cout << "Enter vertices to count distance : ";
            scanf("%d %d", &u, &v);
            cout << g.getDist(u, v) << endl;
        } else if (ch == 8) {
            int u;
            cout << "Enter vertex : ";
            cin >> u;
            g.printAdjVertices(u);
        } else if (ch == 9) {
            exit(0);
        }
    }
}
