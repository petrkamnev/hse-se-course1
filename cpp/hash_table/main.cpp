#include <iostream>
#include <vector>
#include <list>
template<typename Key, typename Type, typename Hash=std::hash<Key>>
class unordered_map{
public:
    typedef Key key_type;
    typedef Type mapped_type;
    typedef std::pair<Key, Type> value_type;
    struct Node{
        Node(value_type value_, Node* next_, Node* prev_):value(value_), next(next_), prev(prev_){}
        value_type value;
        Node* next;
        Node* prev; 
    };
    unordered_map(std::size_t bucket_count):table(bucket_count){
        head->next = &tail;
        tail->prev = &head;
    }
    class iterator{
        public:
        iterator& operator ++(){
            ptr = ptr->next;
            return *this;
        }
        iterator operator ++(int){
            iterator copy(*this);
            ++(*this);
            return copy;
        }
        bool operator==(const iterator& other)const{
            return ptr == other.ptr;
        }
        bool operator!=(const iterator& other)const{
            return !(*this == other);
        }
        Node* operator*(){
            return ptr;
        }
        value_type* operator->(){
            return &(ptr->value);
        }
        private:
        Node* ptr;
    };
    std::size_t bucket_count()const{
        return table.size();
    }
    std::size_t size()const{
        return size_;
    }
    float load_factor()const{
        return bucket_count == 0 ? 0 : static_cast<float>(size)/bucket_count();
    }
    float max_load_factor()const noexcept{
        return max_load_factor_;
    }
    void max_load_factor(float tmp){
        max_load_factor_ = tmp;
    }
    iterator begin(){
        return head->next;
    }
    iterator end(){
        return tail;
    }
    std::pair<iterator, bool> insert(const value_type& value){
        std::size_t bucket_pos = hash(value.first)%bucket_count;
        auto it = std::find_if(table[bucket_pos].begin(), table[bucket_pos].end(), [&](const Node& node) {
                return node.value.first == value.first;
            });
        if (it == table[bucket_pos].end()){
            if(bucket_pos + 1 = bucket_count){
                Node node
            }
            Node node(value, table[bucket_pos + 1].begin(), table[bucket_pos + 1].end());
            table[bucket_pos].push_back(node);
            return make_pair(&(*it))
        }
    }
protected:
    Node* head;
    Node* tail;
    Hash hash;
    std::size_t size_;
    std::vector<std::list<Node>> table;
    float max_load_factor_ = 290;
};

int main(int, char**) {
    std::cout << "Hello, world!\n";
}
