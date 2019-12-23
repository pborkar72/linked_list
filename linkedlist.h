//
// Created by prashant on 23/12/19.
//

#ifndef LINKED_LIST_LINKEDLIST_H
#define LINKED_LIST_LINKEDLIST_H
#include <iostream>

//singly linked list implementation
template <class value_type>
class linkedlist{
    public:
        //default constructor
        linkedlist():head{nullptr}, tail{nullptr}, size{0}{}
        //destruct list
        ~linkedlist(){clear();}
        //copy constructor
        linkedlist(const linkedlist& lst);
        //assignment operator
        linkedlist& operator=(const linkedlist& list);
        //print the list
        void print();
        //check for empty-ness
        bool empty(){
            if(!head)
                return true;
            return false;
        }
        //push new value to front
        void push_front(const value_type& value);
        void push_front(value_type&& value);
        //push new value to back
        void push_back(const value_type& value);
        void push_back(value_type&& value);
        //insert new value at given index
        void insert(int index, const value_type& value);
        void insert(int index, value_type&& value);
        //remove all elements from list
        void clear();
        //get front element
        value_type& front(){return head->value;}
        //get last element
        value_type& back(){return tail->last;}
        //remove front element
        void pop_front();
        //remove back element
        void pop_back();
        //remove first occurance of value
        void remove(const value_type& value);
        void remove(value_type&& value);

    private:
        //node definition
        struct Node{
            value_type value;
            Node* next;
            //construct node from lvalue
            Node(const value_type& value, Node* next = nullptr){
                this->value  = value;
                this->next = next;
            }
            //construct node from rvalue
            Node(value_type&& value, Node* next = nullptr){
                this->value = std::move(value);
                this->next = next;
            }
        };

        //data members of list class
        Node* head;
        Node* tail;
        size_t size;
};

//print the list
template <class value_type>
void linkedlist<value_type>::print(){
    if(!head){
        std::cout << "list is empty" << std::endl;
        return;
    }
    Node* current = head;
    //print when node is not null
    while(current){
        std::cout << current->value << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

//push new value to front of list
template <class value_type>
void linkedlist<value_type>::push_front(const value_type& value){
    if(head == nullptr){
        head = new Node(value);
        tail = head;
    }else{
        head = new Node(value, head);
    }
    size++;
}

template <class value_type>
void linkedlist<value_type>::push_front(value_type&& value){
    if(head == nullptr){
        head = new Node(std::move(value));
        tail = head;
    }else{
        head = new Node(std::move(value), head);
    }
    size++;
}

//push new value to back
template <class value_type>
void linkedlist<value_type>::push_back(const value_type& value){
    if(head == nullptr){
        head = new Node(value);
        tail = head;
    }else{
        tail->next = new Node(value);
        tail = tail->next;
    }
    size++;
}

template <class value_type>
void linkedlist<value_type>::push_back(value_type&& value){
    if(head == nullptr){
        head = new Node(std::move(value));
        tail = head;
    }else{
        tail->next = new Node(std::move(value));
        tail = tail->next;
    }
    size++;
}

//remove front element
template <class value_type>
void linkedlist<value_type>::pop_front(){
    if(head == nullptr)
        return;
    Node* oldHead = head;
    head = head->next;
    if(head == nullptr)
        tail = head;
    size--;
    delete oldHead;
}

//remove back element
template <class value_type>
void linkedlist<value_type>::pop_back(){
    if(head == nullptr)
        return;
    if(head == tail){
        delete head;
        head = nullptr;
        tail = nullptr;
        size--;
        return;
    }
    //find node prev to tail
    Node* prev = head;
    while(prev->next != tail)
        prev = prev->next;

    delete tail;
    prev->next = nullptr;
    tail = prev;
    size--;
}

//insert new value at given index
template <class value_type>
void linkedlist<value_type>::insert(int index, const value_type& value){
    if(head == nullptr){
        std::cout << "list is empty" << std::endl;
        return;
    }
    if(index == 0){
        push_front(value);
        return;
    }
    //find node at index-1 position
    Node* current = head;
    int pos = 0;
    while(current && pos != index-1){
        current = current->next;
        pos++;
    }

    if(current == nullptr){
        std::cout << "index out of bounds" << std::endl;
        return;
    }

    if(current == tail){
        push_back(value);
        return;
    }

    Node* new_node = new Node(value, current->next);
    current->next = new_node;
    if(new_node->next == nullptr)
        tail = new_node;
    size++;
}

template <class value_type>
void linkedlist<value_type>::insert(int index, value_type&& value){
    if(head == nullptr){
        std::cout << "list is empty" << std::endl;
        return;
    }
    if(index == 0){
        push_front(std::move(value));
        return;
    }
    //find node at index-1 position
    Node* current = head;
    int pos = 0;
    while(current && pos != index-1){
        current = current->next;
        pos++;
    }

    if(current == nullptr){
        std::cout << "index out of bounds" << std::endl;
        return;
    }

    if(current == tail){
        push_back(std::move(value));
        return;
    }

    Node* new_node = new Node(std::move(value), current->next);
    current->next = new_node;
    if(new_node->next == nullptr)
        tail = new_node;
    size++;
}

//remove first occurance of value
template <class value_type>
void linkedlist<value_type>::remove(const value_type& value){
    if(head == nullptr)
        return;

    if(head->value == value){
        pop_front();
        return;
    }

    //find node prev to node with value
    Node* prev = head;
    while(prev->next && prev->next->value != value)
        prev = prev->next;

    if(prev->next == nullptr)
        return;

    Node* nodeWithValue = prev->next;
    prev->next = prev->next->next;
    delete nodeWithValue;
    if(prev->next == nullptr)
        tail = prev;
    size--;
}

template <class value_type>
void linkedlist<value_type>::remove(value_type&& value){
    if(head == nullptr)
        return;

    if(head->value == value){
        pop_front();
        return;
    }

    //find node prev to node with value
    Node* prev = head;
    while(prev->next && prev->next->value != value)
        prev = prev->next;

    if(prev->next == nullptr)
        return;

    Node* nodeWithValue = prev->next;
    prev->next = prev->next->next;
    delete nodeWithValue;
    if(prev->next == nullptr)
        tail = prev;
    size--;
}

//remove all elements from list
template <class value_type>
void linkedlist<value_type>::clear(){
    while(head){
        Node* oldHead = head;
        head = head->next;
        delete oldHead;
    }
    tail = nullptr;
    size = 0;
}

//copy constructor
template <class value_type>
linkedlist<value_type>::linkedlist(const linkedlist& lst){
    head = nullptr;
    tail = nullptr;
    size = 0;
    Node* current = lst.head;
    while(current){
        push_back(current->value);
        current = current->next;
    }
}

//assignment operator
template <class value_type>
linkedlist<value_type>& linkedlist<value_type>::operator=(const linkedlist& list){
    if(this != &list){
        head = nullptr;
        tail = nullptr;
        size = 0;
        Node* current = list.head;
        while(current){
            push_back(current->value);
            current = current->next;
        }
    }
    return *this;
}

#endif //LINKED_LIST_LINKEDLIST_H
