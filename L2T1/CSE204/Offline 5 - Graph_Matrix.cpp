#include <stdlib.h>

#include <iostream>
using namespace std;
#define NULL_VALUE -999999
#define INFINITY 999999

#define WHITE 0
#define GREY 1
#define BLACK 2

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
    void enqueue(int item);  //insert item in the queue
    int dequeue();           //returns the item according to FIFO
    bool empty();            //return true if Queue is empty
};

Queue::Queue() {
    queueInitSize = 2;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize];  //allocate initial memory
    length = 0;
    front = 0;
    rear = 0;
}

void Queue::enqueue(int item) {
    if (length == queueMaxSize) {
        int *tempData;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize;
        tempData = new int[queueMaxSize];
        int i, j;
        j = 0;
        for (i = rear; i < length; i++) {
            tempData[j++] = data[i];  //copy items from rear
        }
        for (i = 0; i < rear; i++) {
            tempData[j++] = data[i];  //copy items before rear
        }
        rear = 0;
        front = length;
        delete[] data;    //free the memory allocated before
        data = tempData;  //make list to point to new memory
    }

    data[front] = item;  //store new item
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
        delete[] data;  //deallocate memory
    data = 0;           //set to NULL
}

class Graph {
    int nVertices, nEdges;
    bool directed;
    int **matrix;  //adjacency matrix to store the graph
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation
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
    void bfs(int source);  //will run bfs in the graph
};

Graph::Graph(bool dir) {
    nVertices = 0;
    nEdges = 0;
    matrix = 0;
    directed = dir;  //set direction of the graph
                     //define other variables to be initialized
}

void Graph::setnVertices(int n) {
    this->nVertices = n;

    //allocate space for the matrix
    matrix = new int *[nVertices];
    for (int i = 0; i < nVertices; i++) {
        matrix[i] = new int[nVertices];
        for (int j = 0; j < nVertices; j++)
            matrix[i][j] = 0;  //initialize the matrix cells to 0
    }
}

void Graph::addEdge(int u, int v) {
    //write your code here
    if (u < 0 || u >= nVertices || v < 0 || v >= nVertices)
        return;
    matrix[u][v] = 1;
    if (!directed)
        matrix[v][u] = 1;
    this->nEdges++;
}

void Graph::removeEdge(int u, int v) {
    if (u < 0 || u >= nVertices || v < 0 || v >= nVertices)
        return;
    matrix[u][v] = 0;
    if (!directed) {
        matrix[v][u] = 0;
    }
    this->nEdges--;
}

bool Graph::isEdge(int u, int v) {
    //returns true if (u,v) is an edge, otherwise should return false
    if (matrix[u][v] == 1)
        return true;
    else
        return false;
}

int Graph::getDegree(int u, bool out = true) {
    //returns the degree of vertex u
    int deg = 0;
    if (out) {
        for (int i = 0; i < nVertices; i++) {
            if (matrix[u][i] == 1)
                deg++;
        }
    } else {
        for (int i = 0; i < nVertices; i++) {
            if (matrix[i][u] == 1)
                deg++;
        }
    }
    return deg;
}

void Graph::printAdjVertices(int u) {
    //prints all adjacent vertices of a vertex u
    for (int i = 0; i < nVertices; i++) {
        if (directed) {
            if (matrix[u][i] == 1) {
                cout << i << " ";
            }
        } else {
            if ((matrix[u][i] == 1) || (matrix[i][u] == 1)) {
                cout << i << " ";
            }
        }
    }
    cout << endl;
}

bool Graph::hasCommonAdjacent(int u, int v) {
    //returns true if vertices u and v have common adjacent vertices
    for (int i = 0; i < nVertices; i++) {
        if ((matrix[u][i] == 1) && (matrix[v][i] == 1))
            return true;
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

        for (int i = 0; i < nVertices; i++) {
            if ((matrix[u][i] == 1) && (color[i] == WHITE)) {
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
        for (int j = 0; j < nVertices; j++) {
            if (matrix[i][j] == 1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph() {
    //write your destructor here
    delete matrix;
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
