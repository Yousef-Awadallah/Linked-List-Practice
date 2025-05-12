#pragma once
#include <iostream>

                //IMPORTANT// 
// *const p_x != const *p_x != *const *p_x //

//class declarations
class Node;
class Linked_list;

//function declarations
std::ostream &operator<<(std::ostream &out, 
Linked_list const &list);

//class definitions
class Node {
    public:
    Node(double const new_value, Node *const p_new_next_node);
    
    Node(Node const &original) = delete;
    Node(Node &&original) = delete;
    Node &operator=(Node const &rhs) = delete;
    Node &operator=(Node &&rhs) = delete;

    double value(double const new_value);
    Node *p_next_node(Node *const p_new_next_node);
    double value() const;
    Node *p_next_node() const;
    private:
    double value_;
    Node *p_next_node_;
};

class Linked_list {
    public:
    Linked_list();

    Linked_list(Linked_list const &original) = delete;
    Linked_list(Linked_list &&original) = delete;
    ~Linked_list();
    Linked_list &operator=(Linked_list const &rhs) = delete;
    Linked_list &operator=(Linked_list &&rhs) = delete;

    double front() const;
    double back() const;
    void push_front(double new_value);
    void push_front(Linked_list &list);
    void push_back(Linked_list &list);
    void pop_front();
    void push_back(double new_value);
    void pop_back();
    void clear();
    bool empty() const;
    std::size_t size() const;
    void swap(Linked_list &list);
    private:
    Node *p_list_head_;
    Node *p_list_tail_;
    std::size_t list_size_;

    friend std::ostream &operator<<(std::ostream &out, 
    Linked_list const &list);
};