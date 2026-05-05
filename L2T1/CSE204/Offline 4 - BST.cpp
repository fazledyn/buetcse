#include <iostream>
using namespace std;

class BST {
    int key;
    BST *left, *right, *parent;

    BST *Delete(BST *node, int data) {
        if (node == NULL)
            return node;
        else if (data < node->key)
            node->left = Delete(node->left, data);
        else if (data > node->key)
            node->right = Delete(node->right, data);

        else {
            // 0 chidl
            if (node->left == NULL && node->right == NULL) {
                delete node;
                node = NULL;
            }
            // 1 child
            else if (node->left == NULL) {
                BST *temp = node;
                node = node->right;
                delete temp;
            } else if (node->right == NULL) {
                BST *temp = node;
                node = node->left;
                delete temp;
            }
            //	2 child
            else {
                BST *temp = findMinimum(node->right);
                node->key = temp->key;
                node->right = Delete(node->right, temp->key);
            }
        }
        return node;
    }

   public:
    BST(int data) {
        key = data;
        left = right = parent = NULL;
    }

    void Insert(int data) {
        if (data == key) {
            cout << "already have ";
        } else if (data < key) {
            if (this->left != NULL) {
                this->left->Insert(data);
            } else {
                BST *newNode = new BST(data);
                newNode->parent = this;
                this->left = newNode;
            }
        } else if (data > key) {
            if (this->right != NULL) {
                this->right->Insert(data);
            } else {
                BST *newNode = new BST(data);
                newNode->parent = this;
                this->right = newNode;
            }
        }
    }

    bool Search(int data) {
        bool found = false;

        if (data == key) {
            found = true;
        } else if (data < key) {
            if (this->left != NULL)
                found = this->left->Search(data);
        } else if (data > key) {
            if (this->right != NULL)
                found = this->right->Search(data);
        }
        return found;
    }

    void inOrderTraversal() {
        if (this != NULL) {
            this->left->inOrderTraversal();
            cout << key << "  ";
            this->right->inOrderTraversal();
        }
    }

    void preOrderTraversal() {
        if (this != NULL) {
            cout << key << "  ";
            this->left->preOrderTraversal();
            this->right->preOrderTraversal();
        }
    }

    void Delete(int data) {
        BST *temp = Delete(this, data);
    }

    BST *findMinimum(BST *node) {
        while (node->left != NULL) {
            node = node->left;
        }
        return node;
    }
};

void printMenu() {
    cout << endl;
    cout << "1: Insert		2: Search \n";
    cout << "3: Delete		4: Inorder Traversal \n";
    cout << "5: Preorder Traversal \n";
}

int main() {
    BST tree(50);

    int choice = -1, temp;
    bool exit = false;

    while (!exit) {
        printMenu();
        cout << "Enter choice : ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter to insert: ";
                cin >> temp;
                tree.Insert(temp);
                break;

            case 2:
                cout << "Enter to search: ";
                cin >> temp;

                if (tree.Search(temp))
                    cout << "found" << endl;
                else
                    cout << "not found" << endl;
                break;

            case 3:
                cout << "Enter to delete: ";
                cin >> temp;
                tree.Delete(temp);
                break;

            case 4:
                cout << "Inorder traversal :" << endl;
                tree.inOrderTraversal();
                cout << endl;
                break;

            case 5:
                cout << "Preorder Traversal : " << endl;
                tree.preOrderTraversal();
                cout << endl;
                break;

            default:
                exit = true;
                break;
        }
    }
    return 0;
}
