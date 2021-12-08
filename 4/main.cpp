#include <iostream>
#include "stdio.h"

void print(){
    std::cout << std::endl;
}
template<typename T, typename... Types>
void print(const T& a, const Types&... b){
    std::cout << a << ' ' <<  std::endl;
    print(b...);
}
template <typename... Types> struct tuple;

template<> struct tuple<>{};

template<typename T, typename... Types>
struct tuple<T, Types...>: public tuple<Types...>{
    T value;
};

template<size_t index, typename Ttuple> struct element;

template<typename T, typename... Types>
struct element<0, tuple<T, Types...>> {
    using Type_t = T;
    using TupleType_t = tuple<T, Types...>;
};

template<size_t index, typename T, typename... Types>
struct element<index, tuple<T, Types...>>
        : public element<index - 1, tuple<Types...>>{};

template<size_t index, typename... Types>
typename element<index, tuple<Types...>>::Type_t&
get(tuple<Types...>& a){
    using TupleType_t = typename element<index, tuple<Types...>>::TupleType_t;
    return static_cast<TupleType_t&>(a).value;
}

template<size_t index, typename Ttuple>
void FillTuple(Ttuple& a){}

template <size_t index, typename Ttuple, typename T, typename... Types>
void FillTuple(Ttuple& a, const T& b, const Types&... c){
    get<index>(a) = b;
    FillTuple<index + 1>(a, c...);
}


template<typename... Types>
tuple<Types...> MakeTuple(const Types&... a){
    tuple<Types...> result;
    FillTuple<0>(result, a...);
    return result;
}

int main() {
    auto tuple = MakeTuple(123, 3.14);
    auto a = get<0>(tuple);
    std::cout << a << std::endl;
    return 0;
}
