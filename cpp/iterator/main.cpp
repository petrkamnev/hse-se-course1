#include <iostream>

template<typename Type, std::size_t size_>
class array{
    public:
    typedef Type* pointer;
    typedef Type& ref;
    typedef Type value_type;
    ref operator[](std::size_t ind){
        return a[ind];
    }
    class iterator{
        public:
        iterator(pointer ptr_):ptr(ptr_){}
        iterator(const iterator& other) = default;
        iterator& operator[](std::size_t ind){
            return ptr[index];
        }
        ref operator*(){
            return *ptr;
        }
        pointer operator->(){
            return ptr;;
        }
        iterator& operator++(){
            ++ptr;
            return *this;
        }
        iterator operator++(int){
            iterator tmp = *this;
            ++this;
            return tmp;
        }
        iterator& operator--(){
            --ptr;
            return *this;
        }
        iterator operator --(int){
            iterator tmp = *this;
            --this;
            return tmp;
        }
        
        private:
        pointer ptr;
    };
    template <typename... U>
    array(U... x) : a {x...} {

    }
    iterator begin(){
        return a;
    }
    iterator end(){
        return &(a[size_]);
    }
    private:
    value_type a[size_];
};

int main(int, char**) {
    std::cout << "Hello, world!\n";
}
