#include <iostream>
#include <vector>

class X{};

struct NullType{
};

template<typename Head, typename Tail>
struct TypeList{
    typedef Head head;
    typedef Tail tail;
};

template<typename TList, typename TargetType>
struct indexof;

template<typename TargetType>
struct indexof<NullType, TargetType>{
    const static int x = -1;
};

template<typename Tail, typename TargetType>
struct indexof<TypeList<TargetType, Tail>, TargetType>{
    const static int x = 0;
};
template<typename Head, typename Tail, typename TargetType>
struct indexof<TypeList<Head, Tail>, TargetType>{
    const static int next = indexof<Tail, TargetType>::x;
    const static int x = (next == -1) ? -1:(next + 1);
};
int main(int, char**) {
    
}
