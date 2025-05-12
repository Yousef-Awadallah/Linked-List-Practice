#include "Linked_list.hpp"
#include <iostream>
#include <cassert>
#include <stdexcept>

////////////////////////////////
// Node functions definitons //
//////////////////////////////

//constructor (not default constructor)
Node::Node(double const new_value, Node *const p_new_next_node):
value_{new_value},
p_next_node_{p_new_next_node} {

}

//allows assignment for the member function value_
double Node::value(double const new_value) {
    return value_ = new_value;
}

//allows assignment for the member function p_next_node_
Node *Node::p_next_node(Node *const p_new_next_node) {
    return p_next_node_ = p_new_next_node;
}

//allows access to the member function value_
double Node::value() const {
    return value_;
}

//allows access to the member function p_next_node_
Node *Node::p_next_node() const {
    return p_next_node_;
}

///////////////////////////////////////
// Linked_list functions definitons //
/////////////////////////////////////

//default constructor
Linked_list::Linked_list():
p_list_head_{},
p_list_tail_{},
list_size_{} {

}

//destructor
Linked_list::~Linked_list() {
    std::cout << "Destructor is called" << std::endl;
    clear();
}

//returns the first value in the first node in the list
double Linked_list::front() const {
    if (!empty()) {
    return p_list_head_->value();
    } else {
        assert(empty());
        throw std::out_of_range{"There cannot be a value"
        " at the first node if the list is empty"};
    }
}

//returns the first value in the last node in the list
double Linked_list::back() const {
    if (!empty()) {
        return p_list_tail_->value();
    } else {
        assert(empty());
        throw std::out_of_range{"There cannot be a value"
        " at the last node if the list is empty"};
    }
}

//inserts a node at the front of the list
void Linked_list::push_front(double new_value) {

    //critical code begin
    p_list_head_ = new Node{new_value, p_list_head_};
    if (p_list_tail_ == nullptr) {
        p_list_tail_ = p_list_head_;
    }
    ++list_size_;
    //critical code end
    return;
}

void Linked_list::push_front(Linked_list &list) {
    if (this == &list) {
        throw std::invalid_argument{"Cannnot"
        "Concatenate from the front the list to itself"};
    } else if (!list.empty()) {
        if (empty()) {
        swap(list);
        }
        //Critical code begin
        list.p_list_tail_->p_next_node(p_list_head_);
        p_list_head_ = list.p_list_head_;
        list_size_ += list.size();
        list.p_list_tail_ = nullptr;
        list.p_list_head_ = nullptr;
        list.list_size_ = 0;
        //Critical code end
    }
    return;
}

//removes a node at the front of the list
void Linked_list::pop_front() {
    if (!empty()) {

    Node *p_old_head{p_list_head_};
    //critical code begin
    p_list_head_ = p_list_head_->p_next_node();
    if (size() == 1) {
        p_list_tail_ = nullptr;
    }
    --list_size_;
    //critical code end
    delete p_old_head;
    p_old_head = nullptr;
    }
    return;
}

//inserts a node at the end of the list
void Linked_list::push_back(double new_value) {
    if (empty()) {
        return push_front(new_value);
    } else {
        //critical code begin
        p_list_tail_->p_next_node(new
        Node{new_value, nullptr});
        p_list_tail_ = p_list_tail_->p_next_node();
        ++list_size_;
    //critical code end
    }
    return;
}

void Linked_list::push_back(Linked_list &list) {
    swap(list);

    try {
        push_front(list);
    } catch (std::invalid_argument &e) {
        std::cout << "You cannot concatenate"
        "a list to itself from the back" <<
        std::endl;
    }
    return;
}

//removes a node at the end of the list, expensively
void Linked_list::pop_back() {
    if (!empty()) {
        if (size() == 1) {
            return pop_front();
        }
        Node *p_new_list_tail{p_list_head_};

        while (p_new_list_tail->p_next_node() !=
        p_list_tail_) {
        p_new_list_tail = p_new_list_tail->p_next_node();
        }
        //critical code begin
        p_list_tail_ = p_new_list_tail;
        delete p_list_tail_->p_next_node();
        p_list_tail_->p_next_node(nullptr);
        --list_size_;
        //critical code end
    }
    return;
}

//clears the list
void Linked_list::clear() {
    while(!empty()) {
        pop_front();
    }
    return;
}

//check whether the list is empty or not
bool Linked_list::empty() const {
    return (p_list_head_ == nullptr);
}

//return the size of the list
std::size_t Linked_list::size() const {
    return list_size_;
}

void Linked_list::swap(Linked_list &list) {
    Node *tmp{p_list_head_};
    p_list_head_ = list.p_list_head_;
    list.p_list_head_ = tmp;

    Node *tmp_2{p_list_tail_};
    p_list_tail_ = list.p_list_tail_;
    list.p_list_tail_ = tmp;

    std::size_t tmp_3{list_size_};
    list_size_ = list.list_size_;
    list.list_size_ = tmp_3;
    return;
}

//prints instances (objects) of Linked_list by
//overloading the operator left shift
std::ostream &operator<<(std::ostream &out, 
Linked_list const &list) {
    out << "Head -> ";
    Node *p_node{list.p_list_head_};

    while(p_node != nullptr) {
        out << p_node->value() << " -> ";
        p_node = p_node->p_next_node();
    }

    out << "nullptr";

    return out;
}