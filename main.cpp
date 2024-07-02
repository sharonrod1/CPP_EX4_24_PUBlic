#include <QApplication>
#include <QMainWindow>
#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Node <Complex>* root_node = new Node(Complex(1.1, 1.1));
    Tree <Complex> tree;
    tree.add_root(root_node);
    Node <Complex>* n1 = new Node(Complex(1.2, 1.2));
    Node <Complex>* n2 = new Node(Complex(1.3, 1.3));
    Node <Complex>* n3 = new Node(Complex(1.4, 1.4));
    Node <Complex>* n4 = new Node(Complex(1.5, 1.5));
    Node <Complex>* n5 = new Node(Complex(1.6, 1.6));
    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
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
    cout<<"minheap traversal: \n";
    for (auto it = tree.myHeap(); it != Tree<Complex>::MinHeapIterator(nullptr); ++it) {
        std::cout << it->get_value() << " ";
    }
    cout<<endl;
    cout<<tree;
    Node<string>* rootnode1=  new Node<string>("0");
    Node<string>* n11=  new Node<string>("1");
    Node<string>* n12=  new Node<string>("2");
    Node<string>* n13=  new Node<string>("3");
    Node<string>* n14=  new Node<string>("4");
    Node<string>* n15=  new Node<string>("5");
    Tree<string> tree1;
    tree1.add_root(rootnode1);
    tree1.add_sub_node(rootnode1,n11);
    tree1.add_sub_node(rootnode1,n12);
    tree1.add_sub_node(n11,n13);
    tree1.add_sub_node(n11,n14);
    tree1.add_sub_node(n12,n15);
    cout<<"Pre order traversal: \n";
    for( auto node=tree1.begin_pre_order();node!=tree1.end_pre_order();++node){
        cout<<node->get_value()<<" ";
    }
    cout<<endl;
    cout<<"Post order traversal: \n";
    for( auto node=tree1.begin_post_order();node!=tree1.end_post_order();++node){
        cout<<node->get_value()<<" ";
    }
    cout<<endl;
    cout<<"In order traversal: \n";
    for (auto it = tree1.myHeap(); it != Tree<string>::MinHeapIterator(nullptr); ++it) {
        std::cout << it->get_value() << " ";
    }
    cout<<endl;
    cout<<tree1;



    return 0;
}