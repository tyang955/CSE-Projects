/* 
Name : Tianhao Yang
Instructor : Dr. Bill Punch
Date : 2018/4/23
Section 012
Project number :11
Description：This is a program to continue creating a combination data structure, MapSet, which combines a map and a set. But using singly linked list as the underlying data structure.
 */



#ifndef MAP_SET
#define MAP_SET

#include<iostream>
using std::ostream;
#include<string>
using std::string;
#include<utility>
using std::pair;
#include<initializer_list>
using std::initializer_list;
#include<sstream>
using std::ostringstream;

//
// Node
//
template<typename K, typename V>
struct Node {//This will take the place of the pair from the STL. Which gives a two elements combol. Type with template type K and V.
    K first ;
    V second ;
    struct Node<K,V> *next;

    Node() = default;
    Node(K,V);
    bool operator<(const Node&) const;
    bool operator==(const Node&) const;
    friend ostream& operator<<(ostream &out, const Node &n){// Usinng ostream operator << to pass the first element and second element
        out << n.first << ":" << n.second;   
        return out;
    }
};

template<typename K, typename V>
Node<K,V>::Node(K key, V value){//2 arg constructor. The first element as key and second one as value
    first = key;
    second = value;
    next = nullptr;
}

template<typename K, typename V>
bool Node<K,V>::operator<(const Node &n) const{//operator< Compares two Node instances based on the first values
    if (first < n.first)
        return true;
    else 
        return false;
}

template<typename K, typename V>
bool Node<K,V>::operator==(const Node &n) const{//operator == check weather two node are same or not
    if (first == n.first)
        return true;
    else 
        return false;
}

//
// MapSet
// 
template<typename K, typename V>
class MapSet{
    private:
        Node<K,V> *head_, *tail_;
        size_t capacity_;
        Node<K,V> *find_key(K);
    public:
        // MapSet(sz = 2);
        MapSet();
        MapSet(initializer_list< Node<K,V> >);
        MapSet (const MapSet&);
        MapSet operator=(MapSet);
        ~MapSet();
        size_t size();
        bool remove (K);  
        bool add(Node<K,V>);
        Node<K,V> get(K);
        bool update(K,V);  
        int compare(MapSet&);
        MapSet mapset_union (MapSet&);
        MapSet mapset_intersection(MapSet&);

        friend ostream& operator<<(ostream &out, const MapSet &ms){// operator << inorder to pass all the element to ostream. The key in Node and value in Node. The ", " between
            if(ms.capacity_ > 0){
                for(auto it = ms.head_; it != nullptr; it = it->next){
                    if(it->next == nullptr){
                        out << it->first << ":" << it->second;
                    }else{
                        out << it->first << ":" << it->second << ", ";
                    }
                }
            }
            return out;
        }  
};

// constructor
template<typename K, typename V>
MapSet<K,V>::MapSet(){
    head_ = tail_ = nullptr;
    capacity_ = 0;
}

// constructor
template<typename K, typename V>
MapSet<K,V>::MapSet(initializer_list< Node<K,V> > il){//Pass all the Node element in initializer_list into MapSet. In a correct order. 
    head_ = tail_ = nullptr;
    capacity_ = 0;

    for(auto itr = il.begin(); itr != il.end(); ++itr){// using iterator and add function to pass each element in initializer_list to ary_
        if((*this).add(*itr) == true){
        }
    }
}

// constructor
template<typename K, typename V>
MapSet<K,V>::MapSet(const MapSet &ms){//set the MapSet bo be the same.
    head_ = tail_ = nullptr;
    capacity_ = 0;

    for(auto it = ms.head_; it != nullptr; it = it->next){
        if((*this).add(*it) == true){
            
        }
    }
}

// copy and swap
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::operator=(MapSet<K,V> ms){//equal = operator that set two MapSet to be same. 
    for(auto it = head_; it != nullptr;){
        auto ptr = it;
        it = it->next;
        delete ptr;//delete each node in turn, the set head_ and tail_
    }
    head_ = tail_ = nullptr;
    capacity_ = 0;

    for(auto it = ms.head_; it != nullptr; it = it->next){// walk down the list, moving head_
        if((*this).add(*it) == true){
        }
    }
    
    return *this;
}

template<typename K, typename V>
MapSet<K,V>::~MapSet(){// clear the ary_ in MapSet
    for(auto it = head_; it != nullptr;){
        auto ptr = it;
        it = it->next;
        delete ptr;
    }
}

template<typename K, typename V>
size_t MapSet<K,V>::size(){
    size_t size;
    size = capacity_;
    return size;
}


template<typename K, typename V>
Node<K,V>* MapSet<K,V>::find_key(K key){// Using lower_bound function that find the element from the begin pointer to the end pointer that the key is bigger or equal to the argument Key.
    Node<K,V>* pointer = nullptr;
    for(auto it = head_; it != nullptr; it = it->next){
        if(it->first <= key){
            pointer = it;
        }else{
            break;
        }
    }
    return pointer;
}

template<typename K, typename V>
bool MapSet<K,V>::add(Node<K,V> n){
    auto pointer = find_key(n.first);
    Node<K, V> *node = nullptr, *ptr = nullptr;

    if (pointer == nullptr){// the node `n` will be a head node
        node = new Node<K, V>;// new node
        node->first = n.first;
        node->second = n.second;
        node->next = nullptr;

        if(capacity_ == 0){ // first node
            head_ = node;
            tail_ = node;
        }else{              // new head node
            node->next = head_;
            head_ = node;
        }
        capacity_ += 1;
        return true;
    }else{
        if(pointer->first == n.first){// node already exsit
            return false;
        }else{// node doesn't exist
            node = new Node<K, V>;// new node
            node->first = n.first;
            node->second = n.second;
            node->next = nullptr;

            ptr = pointer->next;
            if(ptr == nullptr){// the pointer pointed the `tail_` node, then update `tail_` pointer
                tail_->next = node;// here, `tail_` equals to `pointer`
                tail_ = node;
            }else{
                pointer->next = node;// insert the node between the node pointed by `pointer` variable and the node pointed by `pre` variable.
                node->next = ptr;
            }
            capacity_ += 1;
            return true;
        }
    }
    return false;
}

template<typename K, typename V>
bool MapSet<K,V>::remove(K key){ //Takes one argument. Similiar to add function
    auto pointer = find_key(key);
    Node<K, V> *previous = nullptr;
    if(pointer == nullptr){
        return false;
    }else{
        if(pointer->first != key){
            return false;
        }else{
            for(auto it = head_; it != nullptr;){
                if(it->first == key){
                    // remove operation
                    if(previous == nullptr){// it equals to head_
                        if(capacity_ == 1){
                            head_ = tail_ = nullptr;// after remove operation, head_ and tail_ both equal to nullptr
                        }else{
                            head_ = head_->next;// update the head_ variable
                        }
                        break;
                    }else{
                        // previous != null, the MapSet at least has two node, one is pointed by `previous` variable, the other one is pointed by `it` variable
                        if(it == tail_){ // when `it` equals to tail_
                            tail_ = previous; // update `tail_` variable
                            tail_->next = nullptr; // update `tail_`'s next variable
                        }else{
                            previous->next = it->next;
                        }
                    }
                    capacity_ -= 1;
                    delete it; // free the memory
                    break;
                }
                previous = it;  // store the `previous` pointer
                it = it->next;  // next node
            }
            return true; // return true, because `pointer->first` == `key`
        }
    }
    return false;
}

template<typename K, typename V>
Node<K,V> MapSet<K,V>::get(K key){//Takes one argument. find the Node if the key is in MapSet
    Node<K,V> s ;
    s.first = "";
    s.second = 0;
    auto pointer = find_key(key);
    if(pointer != nullptr && pointer->first == key){ // If the key equal to what pointer find
        s.first = (*pointer).first; // Set s to be same to the pointer
        s.second = (*pointer).second;
    }
    return s;
}

template<typename K, typename V>
bool MapSet<K,V>::update(K key, V value){//Takes two argument, Find the Node if the key is in the MapSet and put a new value into the key
    auto pointer = find_key(key);
    if(pointer != nullptr && pointer->first == key){//if the find_key find the right keu
        pointer->second = value;//set the value by argument value
        return true;
    }
    return false;
}

template<typename K, typename V>
int MapSet<K,V>::compare(MapSet &ms){// Takes a MapSet argument.
    for(auto it1 = head_, it2 = ms.head_; it1 != nullptr && it2 != nullptr; it1 = it1->next, it2 = it2->next){
        if(*it1 == *it2){// If the value is same. continue
            continue;
        }
        if(*it1 < *it2){// If the argument MapSet bigger. return -1;
            return -1;
        }else{
            return 1;
        }
    }
    if(capacity_ > ms.capacity_){// If under the length. The MapSet are same. The size determine which one is the big one
        return 1;
    }else if(capacity_ < ms.capacity_){
        return -1;
    }else{
        return 0;
    }
}

template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_union(MapSet<K,V> &ms){// Takes a MapSet argument. Set the new MapSet to the calling MapSet. 
    MapSet<K,V> new_ms;
    new_ms = *this;
    for(auto it = ms.head_; it != nullptr; it = it->next){
        new_ms.add(*it);
    }
    return new_ms;
}

template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_intersection(MapSet<K,V> &ms){// Takes a Mapset argument. Find the mapset_intersection of two MapSet
    MapSet<K,V> new_ms;
    for(auto it = ms.head_; it != nullptr; it = it->next){//using a for loop to pass each element in the argument MapSet
        auto pointer = find_key(it->first);// If the Node is able to find in the calling MapSet. Add it to the new MapSet
        if(pointer != nullptr && pointer->first == it->first){
            new_ms.add(*pointer);
        }
    }
    return new_ms;
}

#endif
