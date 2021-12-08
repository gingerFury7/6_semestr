#include <iostream>
#include <variant>
#include <string>
#include <algorithm>
#include <list>
using namespace std;

class cat {
    string name;
public:
    cat(string n = string{}) : name(n) {}
    void meow() const {
        cout << name << ": Meooow!" << endl << flush;
    }
};
class dog {
    string name;
public:
    dog(string n = string{}) : name(n) {}
    void woof() const {
        cout << name << ": Woof-Woof!" << endl << flush;
    }
};
using animal = variant<dog, cat>;

list<animal> l{ cat{"Murzik"}, dog{"Tuzik"}, cat{"Matilda"} };

template <typename T>
bool is_type(const animal& a) {
    return holds_alternative<T>(a);
}

void NumberOf() {
    int NumberCats = count_if(begin(l), end(l), is_type<cat>);
    int NumberDogs = l.size() - NumberCats;
    cout << "There are "
         << NumberCats << " cats and "
         << NumberDogs << " dogs" << endl << flush;
}
int main(){
    NumberOf();
}
