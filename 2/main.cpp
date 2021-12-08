
#include <iostream>

template <typename T>
class deque {
private:
    T* data;
    int size;
    int begin;
    int end;
    const int add = 30;
public:
    deque(const deque<T> &d) {
        *this = d;
    }
//    deque (deque<T> &&d){
//        *this = d;
//
//    }
    ~deque() {
        delete[] data;
    }

    deque() {
        size = 30;
        begin = 15;
        end = 15;
        data = new T[size];
    }
    deque<T> &operator=(deque<T> &val) {
        this->begin = val.begin;
        this->end = val.end;
        this->size = val.size;
        for (int i = val.begin; i < val.end; i++) {
            this->data[i] = val.data[i];
        }
        return *this;
    }
///move semantic
//    deque<T> &operator= (const deque<T> &&val) {
//        delete []  data;
//        data = val.data;
//        size = val.size;
//        begin = val.begin;
//        end = val.end;
//        val.data = nullptr;
//        val.begin = 0;
//        val.size = 0;
//        val.end = 0;
//        return *this;
//    }
    T operator[](int index) {
        return data[begin + index];
    }

    void push_back(T val) {
        if (end < size) {
            data[end++] = val;
        }
        else {
            size += 30;
            T *temp = new T[size];
            for (int i = begin; i < end; i++) {
                temp[i] = data[i];
            }
            temp[end++] = val;
            delete[] data;
            data = temp;
        }
    }
    void push_front(T val){
        if (begin > 0){
            data[--begin] = val;
        }
        else{
            size += add;
            begin += add / 2;
            end += add / 2;
            T *temp  = new T[size];
            for (int i = begin; i < end; i++){
                temp[i] = data[i - 1];
            }
            temp[--begin] = val;
            delete[] data;
            data = temp;
        }
    }
    void pop_back(){
        if (size > 0) { data[end--] = T(); }
    }
    void pop_front(){
        if (size > 0) { data[++begin] = T(); }
    }
    int  Size (){
        return end - begin;
    }
    void print (){
        if (this -> begin == this -> end){
            std::cout << "deque is empty" << std::endl;
            return;
        }
        for (int i = this -> begin; i < this -> end; i++){
            std::cout << this -> data[i] << ' ' << std::endl;
        }
    }
};

int main() {
    deque<int> d;
    d.push_back(12);
    for (int i = 11; i > 0; i--){
        d.push_back(i);
        d.push_front(i);
    }
    d.print();
}