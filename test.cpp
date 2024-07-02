#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
// "rodsharon12345@gmail.com"
#include "doctest.hpp"
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"
#include "utils.hpp"

TEST_CASE("Testing Complex class") {
    Complex c1(1.0, 2.0);
    Complex c2(2.0, 3.0);
    CHECK(c1.getReal() == 1.0);
    CHECK(c1.getImag() == 2.0);
    CHECK(c2 > c1);
}
TEST_CASE("checking pre order iterator "){
    Tree<int> t;
    Node<int>* root = new Node<int>(1);
    Node<int>* n1 = new Node<int>(2);
    Node<int>* n2 = new Node<int>(3);
    Node<int>* n3 = new Node<int>(4);
    Node<int>* n4 = new Node<int>(5);
    Node<int>* n5 = new Node<int>(6);
    t.add_root(root);
    t.add_sub_node(root, n1);
    t.add_sub_node(root, n2);
    t.add_sub_node(n1, n3);
    t.add_sub_node(n1, n4);
    t.add_sub_node(n2, n5);
    auto it = t.begin_pre_order();
    CHECK(it->get_value() == 1);
    ++it;
    CHECK(it->get_value() == 2);
    ++it;
    CHECK(it->get_value() == 4);
    ++it;
    CHECK(it->get_value() == 5);
    ++it;
    CHECK(it->get_value() == 3);
    ++it;
    CHECK(it->get_value() == 6);
    ++it;
    CHECK(!(it != t.end_pre_order()));
}
TEST_CASE("checking post order iterator"){
    Tree<int> t;
    Node<int>* root = new Node<int>(1);
    Node<int>* n1 = new Node<int>(2);
    Node<int>* n2 = new Node<int>(3);
    Node<int>* n3 = new Node<int>(4);
    Node<int>* n4 = new Node<int>(5);
    Node<int>* n5 = new Node<int>(6);
    t.add_root(root);
    t.add_sub_node(root, n1);
    t.add_sub_node(root, n2);
    t.add_sub_node(n1, n3);
    t.add_sub_node(n1, n4);
    t.add_sub_node(n2, n5);
    auto it = t.begin_post_order();
    CHECK(it->get_value() == 4);
    ++it;
    CHECK(it->get_value() == 5);
    ++it;
    CHECK(it->get_value() == 2);
    ++it;
    CHECK(it->get_value() == 6);
    ++it;
    CHECK(it->get_value() == 3);
    ++it;
    CHECK(it->get_value() == 1);
    ++it;
    CHECK(!(it != t.end_post_order()));
}
TEST_CASE("checking in order iterator "){
    Tree<int> t;
    Node<int>* root = new Node<int>(1);
    Node<int>* n1 = new Node<int>(2);
    Node<int>* n2 = new Node<int>(3);
    Node<int>* n3 = new Node<int>(4);
    Node<int>* n4 = new Node<int>(5);
    Node<int>* n5 = new Node<int>(6);
    t.add_root(root);
    t.add_sub_node(root, n1);
    t.add_sub_node(root, n2);
    t.add_sub_node(n1, n3);
    t.add_sub_node(n1, n4);
    t.add_sub_node(n2, n5);
    auto it = t.begin_in_order();
    CHECK(it->get_value() == 4);
    ++it;
    CHECK(it->get_value() == 2);
    ++it;
    CHECK(it->get_value() == 5);
    ++it;
    CHECK(it->get_value() == 1);
    ++it;
    CHECK(it->get_value() == 6);
    ++it;
    CHECK(it->get_value() == 3);
    ++it;
    CHECK(!(it != t.end_in_order()));
}
TEST_CASE("bfs scan "){
    Tree<int> t;
    Node<int>* root = new Node<int>(1);
    Node<int>* n1 = new Node<int>(2);
    Node<int>* n2 = new Node<int>(3);
    Node<int>* n3 = new Node<int>(4);
    Node<int>* n4 = new Node<int>(5);
    Node<int>* n5 = new Node<int>(6);
    t.add_root(root);
    t.add_sub_node(root, n1);
    t.add_sub_node(root, n2);
    t.add_sub_node(n1, n3);
    t.add_sub_node(n1, n4);
    t.add_sub_node(n2, n5);
    auto it = t.begin_bfs_scan();
    CHECK(it->get_value() == 1);
    ++it;
    CHECK(it->get_value() == 2);
    ++it;
    CHECK(it->get_value() == 3);
    ++it;
    CHECK(it->get_value() == 4);
    ++it;
    CHECK(it->get_value() == 5);
    ++it;
    CHECK(it->get_value() == 6);
    ++it;
    CHECK(!(it != t.end_bfs_scan()));
}
TEST_CASE("checking dfs scan"){
    Tree<int> t;
    Node<int>* root = new Node<int>(1);
    Node<int>* n1 = new Node<int>(2);
    Node<int>* n2 = new Node<int>(3);
    Node<int>* n3 = new Node<int>(4);
    Node<int>* n4 = new Node<int>(5);
    Node<int>* n5 = new Node<int>(6);
    t.add_root(root);
    t.add_sub_node(root, n1);
    t.add_sub_node(root, n2);
    t.add_sub_node(n1, n3);
    t.add_sub_node(n1, n4);
    t.add_sub_node(n2, n5);
    auto it = t.begin_dfs_scan();
    CHECK(it->get_value() == 1);
    ++it;
    CHECK(it->get_value() == 2);
    ++it;
    CHECK(it->get_value() == 4);
    ++it;
    CHECK(it->get_value() == 5);
    ++it;
    CHECK(it->get_value() == 3);
    ++it;
    CHECK(it->get_value() == 6);
    ++it;
    CHECK(!(it != t.end_dfs_scan()));
}
TEST_CASE("checking myheap iterator "){
    Tree<int> t;
    Node<int>* root = new Node<int>(1);
    Node<int>* n1 = new Node<int>(2);
    Node<int>* n2 = new Node<int>(3);
    Node<int>* n3 = new Node<int>(4);
    Node<int>* n4 = new Node<int>(5);
    Node<int>* n5 = new Node<int>(6);
    t.add_root(root);
    t.add_sub_node(root, n1);
    t.add_sub_node(root, n2);
    t.add_sub_node(n1, n3);
    t.add_sub_node(n1, n4);
    t.add_sub_node(n2, n5);
    auto it = t.myHeap();
    CHECK(it->get_value() == 1);
    ++it;
    CHECK(it->get_value() == 2);
    ++it;
    CHECK(it->get_value() == 3);
    ++it;
    CHECK(it->get_value() == 4);
    ++it;
    CHECK(it->get_value() == 5);
    ++it;
    CHECK(it->get_value() == 6);
    ++it;
    CHECK(!(it != Tree<int>::MinHeapIterator(nullptr)));
}
TEST_CASE("checking adding more negiboors and tree with root 4"){
    Tree<int> t(5);
    Node<int>* root = new Node<int>(1);
    Node<int>* n1 = new Node<int>(2);
    Node<int>* n2 = new Node<int>(3);
    Node<int>* n3 = new Node<int>(4);
    Node<int>* n4 = new Node<int>(5);
    Node<int>* n5 = new Node<int>(6);
    t.add_root(root);
    t.add_sub_node(root, n1);
    t.add_sub_node(root, n2);
    t.add_sub_node(root, n3);
    t.add_sub_node(root, n4);
    t.add_sub_node(root, n5);
    auto it = t.begin_pre_order();
    CHECK(it->get_value() == 1);
    ++it;
    CHECK(it->get_value() == 2);
    ++it;
    CHECK(it->get_value() == 3);
    ++it;
    CHECK(it->get_value() == 4);
    ++it;
    CHECK(it->get_value() == 5);
    ++it;
    CHECK(it->get_value() == 6);
    ++it;
    CHECK(!(it != t.end_pre_order()));
}
TEST_CASE("checking adding more negiboors and tree with root 4 and checking post order"){
    Tree<int> t(2);
    Node<int>* root = new Node<int>(1);
    Node<int>* n1 = new Node<int>(2);
    Node<int>* n2 = new Node<int>(3);
    t.add_root(root);
    t.add_sub_node(root, n1);
    t.add_sub_node(root, n2);
    CHECK(t.getNeighboursSize(t.getRoot()) == 2);

}

