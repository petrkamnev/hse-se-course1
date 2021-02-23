#include <cstddef>
#include <cstring>

namespace myvector{

template <typename T>
class vector
{
public:
    vector();
    vector(vector& other);
    vector(vector&& other);
    ~vector();
    vector& operator=(vector& other);
    vector& operator=(vector&& other) noexcept;
    void push_back(const T& value);
    T pop_back();
    T& operator[](std::size_t index);
    void reverse(std::size_t new_size);
private:
    T* m_data;
    std::size_t m_size;
    std::size_t m_capacity;

    static constexpr std::size_t s_initsize = 16;
    static constexpr std::size_t s_increaseCoef = 2;
};

template<typename T>
vector<T>::vector(): m_data(new T[s_initsize]), m_size(0), m_capacity(s_initsize)
{
}

template<typename T>
vector<T>::~vector()
{
    delete [] m_data;
}
template<typename T>
vector<T>::vector(vector& other): m_data(new T[other.m_capacity]), m_size(other.m_size), m_capacity(other.m_capacity){
    memcpy(m_data, other.m_data, sizeof(T)*other.m_size);
}
template<typename T>
vector<T>::vector(vector&& other): m_data(other.m_data), m_size(other.m_size), m_capacity(other.m_capacity){
    other.m_data = nullptr;
}
template<typename T>
vector<T>& vector<T>::operator=(vector& other){
    m_data = new T[other.m_capacity];
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    memcpy(m_data, other.m_data, sizeof(T)*other.m_size);
    return *this;
}
template<typename T>
vector<T>& vector<T>::operator=(vector&& other) noexcept{
    m_data = new T[other.m_capacity];
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    other.m_data = nullptr;
    return *this;
}

template<typename T>
void vector<T>::push_back(const T& value){
    if (m_size == m_capacity){
        const std::size_t new_cap = m_capacity*s_increaseCoef;
        T* mem = new T[new_cap];
        memcpy(mem, m_data, m_size*sizeof(T));
        delete[] m_data;
        m_data = mem;
        capacity = new_cap;
    }
    m_data[m_size++] = value;
}

template<typename T>
T vector<T>::pop_back(){
    if(0 == m_size){
        throw "error";
    }
    return m_data[--m_size];
}

template<typename T>
T& vector<T>::operator[](std::size_t index){
    if (index >= m_size{
        throw "error";
    }
    return m_data[index];
}

template<typename T>
void vector<T>::reverse(std::size_t new_size){
    if(new_size < m_capacity){
        return;
    }
    T* mem = new T[new_size];
    memcpy(mem, m_data, m_size*sizeof(T));
    delete[] m_data;
    m_data = mem;
    capacity = new_size;
}

}