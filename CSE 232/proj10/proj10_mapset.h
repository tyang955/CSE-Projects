
/* 
Name : Tianhao Yang
Instructor : Dr. Bill Punch
Date : 2018/4/9
Section 012
Project number :10
Description：This is a program to continue creating a combination data structure, MapSet, which combines a map and a set. But using a array to achieve.
*/



#ifndef MAP_SET
#define MAP_SET

#include<iostream>
using std::ostream;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<utility>
using std::pair;
#include<initializer_list>
using std::initializer_list;
#include<algorithm>
using std::sort; using std::lower_bound;
#include<sstream>
using std::ostringstream;
#include <iterator> 
using std::distance;

//
// Node
//
template<typename K, typename V>
struct Node {//This will take the place of the pair from the STL. Which gives a two elements combol. Type with template type K and V.
    K first ;
    V second ;
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
  Node<K,V>* ary_;
  size_t last_ = 0;
  size_t capacity_;
  Node<K,V>* find_key(K);
  void grow ();
 public:
  MapSet(int sz = 2);
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
    if (ms.last_>0){
        for (int i=0;i<ms.last_-1;i++){
            out << ms.ary_[i].first<<":"<<ms.ary_[i].second<< ", ";
        }
        out << ms.ary_[ms.last_-1].first<<":"<<ms.ary_[ms.last_-1].second;
    }
    return out;
  }  
};

template<typename K, typename V>
MapSet<K,V>::MapSet(int capacity){// one int argument that set the capacity of the MapSet
    ary_ = new Node<K,V>[capacity]{};//Set the capacity_ of ary_ to the int number
    capacity_ = capacity;
    last_ = 0;
}

template<typename K, typename V>
MapSet<K,V>::MapSet(initializer_list< Node<K,V> > il){//Pass all the Node element in initializer_list into MapSet. In a correct order. 
    capacity_=il.size();
    ary_ = new Node<K,V>[capacity_];
    for(auto itr = il.begin(); itr != il.end(); ++itr){// using iterator and add function to pass each element in initializer_list to ary_
        if((*this).add(*itr)==true){
        }
    }
}

template<typename K, typename V>
MapSet<K,V>::MapSet(const MapSet &ms){//set the MapSet bo be the same.
    capacity_ = ms.capacity_;
    last_ = ms.last_;
    ary_ = new Node<K,V>[capacity_];// copy all the element from ms.ary_ to ary_
    copy(ms.ary_, ms.ary_+ms.last_, ary_);
}

// copy and swap
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::operator=(MapSet<K,V> ms){//equal = operator that set two MapSet to be same. 
    capacity_ = ms.capacity_;
    last_ = ms.last_;
    swap(ms.ary_, ary_);// swap all the element from two ary_
    return *this;
}

template<typename K, typename V>
MapSet<K,V>::~MapSet(){// clear the ary_ in MapSet
    delete [] ary_;
}

template<typename K, typename V>
size_t MapSet<K,V>::size(){// find the size of the MapSet. Which is equal to the num last_ in the MapSet
    size_t size;
    size = last_;
    return size;
}

template<typename K, typename V>
void MapSet<K,V>::grow(){// double the capacity_ of the MapSet by times it by two.
    if (last_ == capacity_){
        capacity_ *= 2;
        Node<K,V>* new_ary = new Node<K,V>[capacity_]{};
        copy(ary_, ary_+last_, new_ary);// Double the capacity_ and copy all the element from ary_ to new_ary
        swap(ary_,new_ary);// swap it from the new_ary to ary_
        delete [] new_ary;
    }
}

template<typename K, typename V>
Node<K,V>* MapSet<K,V>::find_key(K key){// Using lower_bound function that find the element from the begin pointer to the end pointer that the key is bigger or equal to the argument Key.
    Node<K,V>* pointer;
    pointer =   lower_bound(ary_, ary_+last_, 
                key,
                [] (Node<K,V> x, K key) 
                { return x.first < key; });// Lamada function that find the right pointer
    return pointer;
}

template<typename K, typename V>
bool MapSet<K,V>::add(Node<K,V> n){// Takes Node argument that add the Node into MapSet
    auto pointer = find_key (n.first);
    if (last_ == capacity_)//check for capacity_ first before add
        capacity_*=2;
    if (pointer == nullptr){//If there is no bigger or same key in MapSet. Add it to the end
        ary_[last_]=n;
        last_+=1;
        return true;
    }
    if((*pointer).first != n.first){//If the pointer find a Node and the key is not equal to the searching Node Key.
        if ((pointer != nullptr and (*pointer).first != n.first) or (pointer == nullptr)){
            Node<K,V>* new_ary_ = new Node<K,V>[capacity_]{};// create a new ary_ with capacity_
            copy(ary_, pointer, new_ary_);//copy the first element to the element before pointer
            new_ary_[pointer-ary_] = n;// Set the index of the insert location to be the new adding Node
            copy(pointer,ary_+last_, new_ary_+(distance (ary_,pointer+1)));// Copy the rest of the ary_ into new_ary_
            swap(ary_,new_ary_);// swap two array
            delete [] new_ary_;
            last_+=1;
            return true;

        }
        else
            return false; 
    }
    else
        return false;
}

template<typename K, typename V>
bool MapSet<K,V>::remove(K key){//Takes one argument. Similiar to add function
    auto pointer = find_key (key);
    if (pointer != nullptr){// If the pointer equal to nullptr. Means the key is not in ary_
        if (pointer == ary_ and (*pointer).first == key){// If the pointer is the first element of ary_
            Node<K,V>* new_ary_ = new Node<K,V>[capacity_]{};
            copy(pointer+1,ary_+last_ ,new_ary_);// copy from the second to the end
            swap(ary_,new_ary_); //swap two array
            delete [] new_ary_;
            last_-=1;
            return true;
        }
        else if ((*pointer).first == key){// If the pointer find the key in the ary_
            Node<K,V>* new_ary_ = new Node<K,V>[capacity_]{};
            copy(ary_, pointer, new_ary_);// copy from the first to the pointer to new_ary_
            copy(pointer+1,ary_+last_ ,new_ary_+(distance (ary_,pointer)));//copy the one after the pointer to new_ary_
            swap(ary_,new_ary_);
            delete [] new_ary_;
            last_-=1;
            return true;
        }
        else 
            return false;
    }
    return false;
}

template<typename K, typename V>
Node<K,V> MapSet<K,V>::get(K key){//Takes one argument. find the Node if the key is in MapSet
    Node<K,V> s ;
    s.first = "";
    s.second = 0;
    auto pointer = find_key (key);
    if ((*pointer).first == key){// If the key equal to what pointer find
            s.first = (*pointer).first;// Set s to be same to the pointer
            s.second = (*pointer).second;
    }
    return s;
}

template<typename K, typename V>
bool MapSet<K,V>::update(K key, V value){//Takes two argument, Find the Node if the key is in the MapSet and put a new value into the key
    auto pointer = find_key (key);
    if (pointer != (ary_+last_) and (*pointer).first == key){//if the find_key find the right keu
        (*pointer).second = value;//set the value by argument value
        return true;
    }
    else
        return false;
}

template<typename K, typename V>
int MapSet<K,V>::compare(MapSet &ms){// Takes a MapSet argument.
    for (int i= 0; i < last_ and i < ms.last_ ; i ++){// If in the given length
        if (ary_[i] == ms.ary_[i])// If the value is same. continue
            continue;
        if(ary_[i] < ms.ary_[i])// If the argument MapSet bigger. return -1
            return -1;
        else // else return 1
            return 1;
    }
    if (last_ > ms.last_)// IF under the length. The MapSet are same. The size determine which one is the big one
        return 1;
    else if (last_ < ms.last_)
        return -1;
    else 
        return 0;
}

template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_union(MapSet<K,V> &ms){// Takes a MapSet argument. Set the new MapSet to the calling MapSet. 
    MapSet<K,V> new_ms;
    new_ms = *this;
    for (int i= 0; i < ms.size();i++)// For each Node in argument MapSet. If the calling MapSet doesn't have the Node. Add it into the new MapSet
        new_ms.add(ms.ary_[i]);
    return new_ms;
}

template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_intersection(MapSet<K,V> &ms){// Takes a Mapset argument. Find the mapset_intersection of two MapSet
    MapSet<K,V> new_ms;
    size_t count = 0;
    for (int i= 0; i < ms.size();i++){//using a for loop to pass each element in the argument MapSet
        auto pointer = find_key (ms.ary_[i].first);// If the Node is able to find in the calling MapSet. Add it to the new MapSet
        if ((*pointer).first == ms.ary_[i].first){
            if (new_ms.last_ == new_ms.capacity_)
                capacity_*=2;
            new_ms.ary_[count] = *pointer;
            count +=1;
            new_ms.last_+=1;
        }
    }
    return new_ms;
}

#endif