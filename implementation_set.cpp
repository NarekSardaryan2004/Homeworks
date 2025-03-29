#include <iostream>

template <typename T>
class Node {
public:
    T data;
    Node* left;
    Node* right;

    Node(T val) : data(val), left(nullptr), right(nullptr) {}
};

template <typename T>
class Set {
public:
    Set() : root(nullptr) {}

    ~Set() {
        destroyTree(root);
    }

    void insert(T val) {
        root = insertNode(root, val);
    }

    void remove(T val) {
        root = removeNode(root, val);
    }

    bool find(T val) {
        return findNode(root, val);
    }

    T max_element() {
        if (root == nullptr) {
            throw std::runtime_error("Set is empty");
        }
        Node<T>* current = root;
        while (current->right != nullptr) {
            current = current->right;
        }
        return current->data;
    }

    T min_element() {
        if (root == nullptr) {
            throw std::runtime_error("Set is empty");
        }
        Node<T>* current = root;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current->data;
    }

    void print() {
        inorderTraversal(root);
        std::cout << std::endl;
    }

private:
    Node<T>* root;

    Node<T>* insertNode(Node<T>* node, T val) {
        if (node == nullptr) {
            return new Node<T>(val);
        }
        if (val < node->data) {
            node->left = insertNode(node->left, val);
        } else if (val > node->data) {
            node->right = insertNode(node->right, val);
        }
        return node;
    }

    Node<T>* removeNode(Node<T>* node, T val) {
        if (node == nullptr) return nullptr;

        if (val < node->data) {
            node->left = removeNode(node->left, val);
        } else if (val > node->data) {
            node->right = removeNode(node->right, val);
        } else {
            if (node->left == nullptr) {
                Node<T>* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node<T>* temp = node->left;
                delete node;
                return temp;
            }

            Node<T>* temp = findMin(node->right);
            node->data = temp->data;
            node->right = removeNode(node->right, temp->data);
        }
        return node;
    }

    bool findNode(Node<T>* node, T val) {
        while (node != nullptr) {
            if (val < node->data) {
                node = node->left;
            } else if (val > node->data) {
                node = node->right;
            } else {
                return true;
            }
        }
        return false;
    }

    Node<T>* findMin(Node<T>* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    void inorderTraversal(Node<T>* node) {
        if (node == nullptr) return;
        inorderTraversal(node->left);
        std::cout << node->data << " ";
        inorderTraversal(node->right);
    }

    void destroyTree(Node<T>* node) {
        if (node == nullptr) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
};

int main() {
    Set<int> mySet;
    mySet.insert(5);
    mySet.insert(5);
    mySet.insert(5);
    mySet.insert(3);
    mySet.insert(7);
    mySet.insert(2);
    mySet.insert(4);
    mySet.insert(6);
    mySet.insert(8);

    std::cout << "Set elements: ";
    mySet.print(); 

    std::cout << "Max element: " << mySet.max_element() << std::endl;
    std::cout << "Min element: " << mySet.min_element() << std::endl;
    std::cout << "Find 4: " << (mySet.find(4) ? "Found" : "Not Found") << std::endl;
    std::cout << "Find 10: " << (mySet.find(10) ? "Found" : "Not Found") << std::endl;

    mySet.remove(4);
    std::cout << "After removing 4: ";
    mySet.print(); 

    mySet.remove(5);
    std::cout << "After removing 5: ";
    mySet.print(); 

    return 0;
}
