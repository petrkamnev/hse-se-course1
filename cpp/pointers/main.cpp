#include <iostream>
#include <algorithm>

struct counter{
    int count;
    counter(){
        count = 0;
    }
    counter(int t){
        count = t;
    }
};

template<typename T>
class UniquePtr{
public:
    UniquePtr(){
        ptr = nullptr;
    }
    explicit UniquePtr(T* pointer){
        ptr = pointer;
    }
    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr(UniquePtr&& other){
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    UniquePtr& operator=(const UniquePtr& other) = delete;
    UniquePtr& operator=(UniquePtr&& other){
        ptr = other.ptr;
        other.ptr = nullptr;
        return *this;
    }
    ~UniquePtr(){
        delete ptr;
    }
    T& operator*() const{
        return *ptr;
    }
    T& operator->() const{
        return *ptr;
    }
    T* release(){
        T* tmp = ptr;
        ptr = nullptr;
        return tmp;
    }
    void reset(){
        if (ptr){delete ptr;}
        ptr = nullptr;
    }
    void swap(UniquePtr& other){
        std::swap(ptr, other.ptr);
    }

private:
    T* ptr;
};

template<typename T>
class SharedPtr{
    public:
    SharedPtr(){
        ptr = nullptr;
    }
    explicit SharedPtr(T* pointer){
        ptr = pointer;
        cnt = new counter(1);
    }
    SharedPtr(const SharedPtr& other){
        ptr = other.ptr;
        cnt = other.cnt;
        cnt->count++;
    }
    SharedPtr(SharedPtr&& other){
        cnt = other.cnt;
        ptr = other.ptr;
        other.cnt = nullptr;
        other.ptr = nullptr;
    }
    SharedPtr& operator=(const SharedPtr& other){
        ptr = other.ptr;
        cnt = other.cnt;
        cnt->count++;
        return *this;
    }
    SharedPtr& operator=(SharedPtr&& other){
        cnt = other.cnt;
        ptr = other.ptr;
        other.cnt = nullptr;
        other.ptr = nullptr;
        return *this;
    }
    ~SharedPtr(){
        if(ptr){
            if (cnt->count == 1){
                delete cnt;
                delete ptr;
                cnt = nullptr;
                cnt = nullptr;
            }
            else {
                cnt->count--;
                ptr = nullptr;
                cnt = nullptr;
            }
        }
    }
    T& operator*() const{
        return *ptr;
    }
    T* operator->() const{
        return ptr;
    }
    T* release(){
        T* tmp = ptr;
        ptr = nullptr;
        if (cnt->count == 1){
            delete cnt;
            cnt = nullptr;
        } else {
            cnt->count--;
            cnt = nullptr;
        }
        return tmp;
    }
    void reset(){
        if (ptr){delete ptr;}
        ptr = nullptr;
    }
    void swap(SharedPtr& other){
        std::swap(ptr, other.ptr);
    }

    private:
    T* ptr;
    counter* cnt;
};

class WeakPtr{

};

int main(int, char**) {
    std::unique_ptr<int> pp(new int(1));
    std::cout << *pp;
    auto sp_a = SharedPtr(new int(1));
    auto sp_b = SharedPtr(sp_a);
}
