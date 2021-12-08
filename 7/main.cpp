#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>
using namespace std;

template <typename T>
class List {
protected:
    struct Node {
        T data;
        Node* pNext;
        Node(): pNext(NULL){};
        Node(const T &l): data(l), pNext(nullptr){};
    };
    Node* head;
    int size;
public:
    List(){
        head = nullptr;
        size = 0;
    }
    ~List(){
        while (head){
            pop_front();
        }
    };

    void push_front(const T &l){
        Node* node = new Node(l);
        node -> pNext = head;
        head = node;
        ++size;
    };

    void pop_front(){
        if (head){
            Node* NewHead = head -> pNext;
            delete head;
            head = NewHead;
            --size;
        }
    }

    void print(){
        Node* p = head;
        while (p != nullptr){
            cout << p -> data << " ";
            p = p -> pNext;
        }
        cout << endl;
    }

    class ForwardIterator: public iterator<forward_iterator_tag, Node>{
    protected:
        Node* position;
    public:
        ForwardIterator(){
            position = NULL;
        }
        ForwardIterator(Node* p){
            position = p;
        }
        ForwardIterator(const ForwardIterator &iterator){
            position = iterator.position;
        }
        ForwardIterator& operator=(const ForwardIterator &iterator){
            position = iterator.position;
            return *this;
        }
        ForwardIterator& operator*(){
            return position -> data;
        }
        ForwardIterator operator++(){
            return position = position -> pNext;
        }
        friend bool operator==(const ForwardIterator &it1, const ForwardIterator &it2){
            return it1.position == it2.position;
        }
        friend bool operator!=(const ForwardIterator &it1, const ForwardIterator &it2){
            return it1.position != it2.position;
        }
        virtual T operator*() const {
            return position -> data;
        }
    };

    class ReverseIterator: public ForwardIterator {
    protected:
        Node *headPosotion;
    public:
        ReverseIterator() : ForwardIterator() {};

        ReverseIterator(Node *p, Node *hp) : ForwardIterator(p) {
            headPosotion = hp;
        }

        ReverseIterator &operator++() {
            Node *p = this->position;
            if (this->position != headPosotion) {
                this->position = headPosotion;
                while (p != this->position->pNext) {
                    --(*this);
                }
            } else {
                this->position = nullptr;
            }
            return *this;
        }
        virtual T operator*() const {
            return this -> position -> data;
        }
    };

    ReverseIterator begin() const {
        return ReverseIterator (head, head);
    };
    ReverseIterator end() const {
        return ReverseIterator (nullptr, head);
    };
    ReverseIterator rBegin() const{
        return ++((*this).end());
    };
    ReverseIterator rEnd() const{
        return ReverseIterator(nullptr, head);
    };



};

int main() {
    List<int> l = List<int> ();
    l.push_front(3);
    l.push_front(4);
    l.push_front(5);
    l.print();
    cout << endl;
    for (auto i = l.begin(); i != l.end(); ++i){
        cout << *(i) << endl;
    }
    cout << endl;
    for (auto i = l.rBegin(); i != l.rEnd(); ++i){
        cout << *(i) << endl;
    }

    return 0;
}
