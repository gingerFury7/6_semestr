#include <iostream>
#include "stdio.h"

template <typename T>
class SmartPointer {
private:
    T *ptr;
    int *count;
public:
    SmartPointer(T *p = nullptr){
        ptr = p;
        if (p != NULL){
            count = new int(1);
        }
        else {
            count = nullptr;
        }
    }
    SmartPointer(SmartPointer &p){
        *this =  p;
    }
    ~SmartPointer(){
        (*count)--;
        if ((*count) == 0){
            delete this -> ptr;
            ptr = nullptr;
        }
        this -> ptr = nullptr;
    }
    SmartPointer& operator=(const SmartPointer<T> &p){
        if (count != nullptr){
            (*count)--;
            if ((*count) == 0){
                delete count;
                delete ptr;
            }
        }
        ptr = p.ptr;
        count = p.count;
        if(count != nullptr){
            (*count)++;
        }
        return *this;
    }
    SmartPointer& operator=(T* p)
    {
        if (count == nullptr)
        {
            count = new int(1);
        }
        else
        {
            (*count)--;
            count = new int(1);
            ptr = p;
        }
        return *this;
    }
    T& operator*(){
        return *ptr;
    }
};

int main() {
    int* p= new int(10);
    SmartPointer<int> a(p);
    SmartPointer<int> b(a);
    SmartPointer<int> c;
    c=a;
}
