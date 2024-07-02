#include <QApplication>
#include <QMainWindow>
#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"
#include "utils.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Node<double>* root_node =  new Node(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double>* n1 = new Node(1.2);
    Node<double>* n2 = new Node(1.3);
    Node<double>* n3 = new Node(1.4);
    Node<double>* n4 = new Node(1.5);
    Node<double>* n5 = new Node(1.6);


    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    
    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

    std::cout << "Pre order traversal: \n";
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        std::cout << node->get_value() << " ";
    }
    std::cout << std::endl;

    std::cout << "Post order traversal: \n";
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        std::cout << node->get_value() << " ";
    }
    std::cout << std::endl;

    std::cout << "In order traversal: \n";
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        std::cout << node->get_value() << " ";
    }
    std::cout << std::endl;

    std::cout << "BFS scan:\n";
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
        std::cout << node->get_value() << " ";
    }
    std::cout << std::endl;

    std::cout << "DFS scan:\n";
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
        std::cout << node->get_value() << " ";
    }
    std::cout << std::endl;

    std::cout << "Min-Heap Traversal:\n";
    for (auto it = tree.myHeap(); it != Tree<double>::MinHeapIterator(nullptr); ++it) {
        std::cout << it->get_value() << " ";
    }
    std::cout << endl;

     // Should print the graph using GUI.
    cout << "Printing the graph using GUI...\n";
    // cout<<tree;
    
    return 0;
}
