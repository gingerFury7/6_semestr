#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <cstddef>

using namespace std;

template <typename T0 = nullptr_t, typename T1 = nullptr_t, typename T2 = nullptr_t, typename T3 = nullptr_t, typename T4 = nullptr_t>
class Tuple{
private:
    T0 a0;
    T1 a1;
    T2 a2;
    T3 a3;
    T4 a4;
public:
    Tuple() {}

    Tuple (T0 t0 = nullptr, T1 t1 = nullptr, T2 t2 = nullptr, T3 t3 = nullptr, T4 t4 = nullptr):
        a0(t0), a1(t1), a2(t2), a3(t3), a4(t4) {};

    template<int i>
    auto get(){
        return NULL;
    }

    template<> auto get<0>(){ return &a0; }
    template<> auto get<1>(){ return &a1; }
    template<> auto get<2>(){ return &a2; }
    template<> auto get<3>(){ return &a3; }
    template<> auto get<4>(){ return &a4; }


};

int main() {
    Tuple <int, double, string, char> a(123, 3.14, "foo",'t');
    cout << *a.get<0>() << endl;
    *a.get<2>() = "assadsad";
    cout << *a.get<2>() << endl;
}
