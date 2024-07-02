#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <stack>
#include "node.hpp"
#include <queue>
#include <functional>
#include <QApplication>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <utils.hpp>
using namespace std;

template<typename T>
class Tree {
private:
    Node<T>* root;
    unsigned int max_neighbors;

    bool dfs(Node<T>* node, unordered_set<int>& visited) {
        visited.insert(node->id);
        for (Node<T>* neighbor : node->neighbors) {
            if (visited.find(neighbor->id) != visited.end()) {
                return true;
            }
            if (dfs(neighbor, visited)) {
                return true;
            }
        }
        return false;
    }

    void heapify(Node<T>* node) {
        if (node == nullptr) return;
        // Recursively heapify all children
        for (Node<T>* child : node->neighbors) {
            heapify(child);
        }

        // Fix the min-heap property if it's violated
        for (Node<T>* child : node->neighbors) {
            if (child->data < node->data) {
                swap(child->data, node->data);
                heapify(child);
            }
        }
    }

   void deleteTree(Node<T>* node) {
        if (node == nullptr) return;
        for (Node<T>* neighbor : node->neighbors) {
            deleteTree(neighbor);
        }
        
        node->neighbors.clear();
        delete node; // Actually delete the node
    }

public:
    Tree(int maxNeighbors = 2) : root(nullptr), max_neighbors(maxNeighbors) {}
    ~Tree() {
        deleteTree(root);
        root = nullptr;
    }
    double getNeighboursSize(Node<T>* node){
        return node->neighbors.size();
    }

    void add_root(Node<T>* node) {
        if (root == nullptr) {
            root = node;
        } else {
            cout << "Root already exists." << endl;
        }
    }

    Node<T>* getRoot() {
        return root;
    }

    void add_sub_node(Node<T>* parent, Node<T>* child) {
        if (parent->neighbors.size() < max_neighbors && child->neighbors.size() < max_neighbors) {
            parent->neighbors.push_back(child);
            child->parent = parent;
            unordered_set<int> visited;
            if (containsCycle()) {
                parent->neighbors.pop_back();
                child->parent = nullptr;
            } else {
            }
        } else {
            cout << "One of the nodes already has the maximum number of neighbors." << endl;
        }
    }

    bool containsCycle() {
        if (root == nullptr) return false;
        unordered_set<int> visited;
        return dfs(root, visited);
    }

    friend ostream& operator<<(ostream& os, Tree<T>& tree) {
        tree.printTree();
        return os;
    }

    void printTree() {
        QMainWindow window;
        QGraphicsView view(&window);
        QGraphicsScene scene(&view);
        view.setScene(&scene);
        window.setCentralWidget(&view);

        drawTree(&scene, getRoot(), 300, 50, 100);

        window.show();
        QApplication::exec();
    }

     void drawTree(QGraphicsScene *scene, Node<T> *node, double x, double y, double xOffset) {
        if (!node) return;

        QGraphicsEllipseItem *circle = scene->addEllipse(0, 0, 70, 70); // Larger circles for Complex type
        circle->setPos(x, y);
        QGraphicsTextItem *text = scene->addText(toQString(node->get_value()));
        text->setPos(x + 15, y + 25);

        double childYOffset = 150; // More space between levels
        double totalWidth = (node->neighbors.size() - 1) * xOffset;

        for (size_t i = 0; i < node->neighbors.size(); ++i) {
            double childXOffset = x - totalWidth / 2 + i * xOffset;
            scene->addLine(x + 35, y + 70, childXOffset + 35, y + childYOffset); // Adjust line positions
            drawTree(scene, node->neighbors[i], childXOffset, y + childYOffset, xOffset * 0.75); // Adjust xOffset reduction
        }
    }

    class MinHeapIterator {
    private:
        queue<Node<T>*> nodeQueue;
        Node<T>* current;

    public:
        MinHeapIterator(Node<T>* root) : current(nullptr) {
            if (root != nullptr) {
                buildMinHeap(root);
            }
            if (!nodeQueue.empty()) {
                current = nodeQueue.front();
                nodeQueue.pop();
            }
        }

        void buildMinHeap(Node<T>* node) {
            if (node == nullptr) return;

            // Using a min-heap priority queue to store nodes
            priority_queue<Node<T>*, vector<Node<T>*>, function<bool(Node<T>*, Node<T>*)>> pq(
                [](Node<T>* a, Node<T>* b) { return a->data > b->data; });

            queue<Node<T>*> tempQueue;
            tempQueue.push(node);

            while (!tempQueue.empty()) {
                Node<T>* current = tempQueue.front();
                tempQueue.pop();
                pq.push(current);
                for (Node<T>* child : current->neighbors) {
                    tempQueue.push(child);
                }
            }

            while (!pq.empty()) {
                nodeQueue.push(pq.top());
                pq.pop();
            }
        }

        bool operator!=(const MinHeapIterator& other) const {
            return current != other.current;
        }
        

        Node<T>* operator->() {
            return current;
        }

        MinHeapIterator& operator++() {
            if (!nodeQueue.empty()) {
                current = nodeQueue.front();
                nodeQueue.pop();
            } else {
                current = nullptr;
            }
            return *this;
        }

        Node<T>& operator*() {
            return *current;
        }
    };

    MinHeapIterator myHeap() {
        if (max_neighbors != 2) {
            cout << "Heapify only works for binary trees." << endl;
            return MinHeapIterator(nullptr);
        }
        return MinHeapIterator(root);
    }

    class IteratorPreOrder {
    private:
        stack<Node<T>*> nodeStack;
        unordered_set<int> visited;
        Tree<T>* tree;
        Node<T>* current;

    public:
        IteratorPreOrder(Tree<T>* t, Node<T>* startNode = nullptr) : tree(t), current(nullptr) {
            if (startNode != nullptr) {
                nodeStack.push(startNode);
                current = startNode;
                visited.insert(startNode->id);
            }
        }

        bool operator!=(const IteratorPreOrder& other) const {
            return current != other.current;
        }

        bool contains(const unordered_set<int>& s, int v) {
            return s.find(v) != s.end();
        }

        IteratorPreOrder& operator++() {
            if (nodeStack.empty()) {
                current = nullptr;
                return *this;
            }

            current = nodeStack.top();
            nodeStack.pop();

            if (tree->max_neighbors == 2) {
                for (auto it = current->neighbors.rbegin(); it != current->neighbors.rend(); ++it) {
                    if (visited.find((*it)->id) == visited.end()) {
                        nodeStack.push(*it);
                        visited.insert((*it)->id);
                    }
                }
            } else {
                for (auto it = current->neighbors.rbegin(); it != current->neighbors.rend(); ++it) {
                    auto neighbor = *it;
                    if (!contains(visited, neighbor->id)) {
                        nodeStack.push(neighbor);
                        visited.insert(neighbor->id);
                    }
                }
            }

            if (nodeStack.empty()) {
                current = nullptr;
            } else {
                current = nodeStack.top();
            }

            return *this;
        }

        Node<T>* operator->() {
            return current;
        }
    };

    IteratorPreOrder begin_pre_order() {
        return IteratorPreOrder(this, root);
    }

    IteratorPreOrder end_pre_order() {
        return IteratorPreOrder(this, nullptr);
    }

    class IteratorPostOrder {
    private:
        stack<Node<T>*> traversalStack; // the stack that will be used to traverse the tree
        stack<Node<T>*> processingStack; // the final stack that will be used to iterate
        unordered_set<int> visited;
        Tree<T>* tree;
        Node<T>* current;

        void prepareStack() {
            while (!traversalStack.empty()) {
                Node<T>* node = traversalStack.top();
                traversalStack.pop();
                processingStack.push(node);
                for (auto neighbor : node->neighbors) {
                    if (visited.find(neighbor->id) == visited.end()) { // Only nodes that have not been visited
                        traversalStack.push(neighbor);
                        visited.insert(neighbor->id);
                    }
                }
            }
        }

    public:
        IteratorPostOrder(Tree<T>* t, Node<T>* startNode = nullptr) : tree(t), current(nullptr) {
            if (startNode != nullptr) {
                traversalStack.push(startNode);
                visited.insert(startNode->id);
                if (tree->max_neighbors != 2) {
                    processingStack.push(startNode);
                    current = startNode;
                } else {
                    prepareStack();
                    if (!processingStack.empty()) {
                        current = processingStack.top();
                    }
                }
            }
        }

        bool operator!=(const IteratorPostOrder& other) const {
            return current != other.current;
        }

        bool contains(const unordered_set<int>& s, int v) {
            return s.find(v) != s.end();
        }

        Node<T>* operator->() {
            return current;
        }

        IteratorPostOrder& operator++() {
            if (tree->max_neighbors != 2) {
                if (!processingStack.empty()) {
                    current = processingStack.top();
                    processingStack.pop();
                    for (auto it = current->neighbors.rbegin(); it != current->neighbors.rend(); ++it) {
                        auto neighbor = *it;
                        if (!contains(visited, neighbor->id)) {
                            processingStack.push(neighbor);
                            visited.insert(neighbor->id);
                        }
                    }
                    if (processingStack.empty()) {
                        current = nullptr;
                    } else {
                        current = processingStack.top();
                    }
                }
            } else {
                if (!processingStack.empty()) {
                    processingStack.pop();
                    if (!processingStack.empty()) {
                        current = processingStack.top();
                    } else {
                        current = nullptr;
                    }
                } else {
                    current = nullptr;
                }
            }
            return *this;
        }
    };

    IteratorPostOrder begin_post_order() {
        return IteratorPostOrder(this, root);
    }

    IteratorPostOrder end_post_order() {
        return IteratorPostOrder(this, nullptr);
    }

    class IteratorInOrder {
    private:
        stack<Node<T>*> nodeStack;
        unordered_set<int> visited;
        Tree<T>* tree;
        Node<T>* current;

        void pushLeft(Node<T>* node) {
            while (node != nullptr) {
                nodeStack.push(node);
                node = (node->neighbors.size() > 0) ? node->neighbors[0] : nullptr;
            }
        }

    public:
        IteratorInOrder(Tree<T>* t, Node<T>* startNode = nullptr) : tree(t), current(nullptr) {
            if (startNode != nullptr) {
                if (tree->max_neighbors == 2) {
                    pushLeft(startNode);
                } else {
                    nodeStack.push(startNode);
                    current = startNode;
                    visited.insert(startNode->id);
                }
                if (!nodeStack.empty()) {
                    current = nodeStack.top();
                }
            }
        }

        bool operator!=(const IteratorInOrder& other) const {
            return current != other.current;
        }

        bool contains(const unordered_set<int>& s, int v) {
            return s.find(v) != s.end();
        }

        Node<T>* operator->() {
            return current;
        }

        IteratorInOrder& operator++() {
            if (tree->max_neighbors != 2) {
                if (!nodeStack.empty()) {
                    current = nodeStack.top();
                    nodeStack.pop();
                    for (auto it = current->neighbors.rbegin(); it != current->neighbors.rend(); ++it) {
                        auto neighbor = *it;
                        if (!contains(visited, neighbor->id)) {
                            nodeStack.push(neighbor);
                            visited.insert(neighbor->id);
                        }
                    }
                    if (nodeStack.empty()) {
                        current = nullptr;
                    } else {
                        current = nodeStack.top();
                    }
                }
            } else {
                if (!nodeStack.empty()) {
                    Node<T>* node = nodeStack.top();
                    nodeStack.pop();
                    if (node->neighbors.size() > 1) {
                        pushLeft(node->neighbors[1]);
                    }
                    if (!nodeStack.empty()) {
                        current = nodeStack.top();
                    } else {
                        current = nullptr;
                    }
                } else {
                    current = nullptr;
                }
            }
            return *this;
        }

        Node<T>& operator*() {
            return *current;
        }
    };

    IteratorInOrder begin_in_order() {
        return IteratorInOrder(this, root);
    }

    IteratorInOrder end_in_order() {
        return IteratorInOrder(this, nullptr);
    }

    class BfsScan {
    private:
        queue<Node<T>*> nodeQueue;
        unordered_set<int> visited;
        Tree<T>* tree;
        Node<T>* current;

    public:
        BfsScan(Tree<T>* t, Node<T>* startNode = nullptr) : tree(t), current(nullptr) {
            if (startNode != nullptr) {
                nodeQueue.push(startNode);
                visited.insert(startNode->id);
                current = startNode;
            }
        }

        bool operator!=(const BfsScan& other) const {
            return current != other.current;
        }

        Node<T>* operator->() {
            return current;
        }

        Node<T>& operator*() {
            return *current;
        }

        BfsScan& operator++() {
            if (!nodeQueue.empty()) {
                current = nodeQueue.front();
                nodeQueue.pop();
                for (auto neighbor : current->neighbors) {
                    if (visited.find(neighbor->id) == visited.end()) {
                        nodeQueue.push(neighbor);
                        visited.insert(neighbor->id);
                    }
                }
            } else {
                current = nullptr;
                return *this;
            }
            if (nodeQueue.empty()) {
                current = nullptr;
            } else {
                current = nodeQueue.front();
            }
            return *this;
        }
    };

    BfsScan begin_bfs_scan() {
        return BfsScan(this, root);
    }

    BfsScan end_bfs_scan() {
        return BfsScan(this, nullptr);
    }

    BfsScan begin() {
        return BfsScan(this, root);
    }

    BfsScan end() {
        return BfsScan(this, nullptr);
    }

    class dfsScan {
    private:
        stack<Node<T>*> nodeStack;
        unordered_set<int> visited;
        Tree<T>* tree;
        Node<T>* current;

    public:
        dfsScan(Tree<T>* t, Node<T>* startNode = nullptr) : tree(t), current(nullptr) {
            if (startNode != nullptr) {
                nodeStack.push(startNode);
                visited.insert(startNode->id);
                current = startNode;
            }
        }

        bool operator!=(const dfsScan& other) const {
            return current != other.current;
        }

        Node<T>* operator->() {
            return current;
        }

        Node<T>& operator*() {
            return *current;
        }

        bool contains(const unordered_set<int>& s, int v) {
            return s.find(v) != s.end();
        }

        dfsScan& operator++() {
            if (!nodeStack.empty()) {
                current = nodeStack.top();
                nodeStack.pop();
                for (auto it = current->neighbors.rbegin(); it != current->neighbors.rend(); ++it) {
                    auto neighbor = *it;
                    if (!contains(visited, neighbor->id)) {
                        nodeStack.push(neighbor);
                        visited.insert(neighbor->id);
                    }
                }
                if (nodeStack.empty()) {
                    current = nullptr;
                } else {
                    current = nodeStack.top();
                }
            }
            return *this;
        }
    };

    dfsScan begin_dfs_scan() {
        return dfsScan(this, root);
    }

    dfsScan end_dfs_scan() {
        return dfsScan(this, nullptr);
    }
};

#endif
