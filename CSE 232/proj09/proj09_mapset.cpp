
/* 
Name : Tianhao Yang
Instructor : Dr. Bill Punch
Date : 2018/4/9
Section 012
Project number :9
Description：This is a program to create a combination data structure by using class. The data structure is MapSet, which combines a map and a
    set, without using its STL counterparts.
*/


#include<iostream>
using std::ostream;
#include<vector>
using std::vector;
#include<string>
using std::string;
#include<algorithm>
using std::lower_bound;
#include<iterator>
using std::ostream_iterator;
#include<utility>
using std::pair;

#include "proj09_mapset.h"

MapSet::MapSet(initializer_list< pair<string,long> > x){//: Take each pair of the initializer_list and place in the vector. The returns vector are sorted.
    for(auto itr = x.begin(); itr != x.end(); ++itr){//go though the initializer_list. 
        auto itr2 = find_key ((*itr).first);//use find key method to determine weather the key is in and where is tne best location for the new key
        if (itr2 != v_.end())
            v_.insert(itr2, *itr);//insert into location before just greater than the key
        else
            v_.push_back(*itr);// Not find the location. Means it is the largest key. push_back into vector.
    }
}

vector< pair <string, long> >::iterator MapSet::find_key(string s){ // a private method. Returns an iterator to a pair<string,long> that is either the first pair in the vector equal to (by key) or greater than the key, or v_.end().
    vector< pair <string, long> >::iterator itr;
    itr = lower_bound(v_.begin(), 
                      v_.end(), 
                      s,		      
                      [] (pair<string,long> x, string s) 
                      { return x.first < s; });// use the algorithm  called lower_bound that returns an iterator goes though the vector. Use a lambda function to take the first key of the pair and compare it to the value we searching
    return itr;
}
size_t MapSet::size(){//use .size() function to determine the size of the MapSet
    size_t size;
    size = v_.size();
    return size;
}

pair<string,long> MapSet::get(string s ){//returns a pair<string,long> that is either a copy of the pair or the default value for pair
    pair<string,long> p = {"",0};
    auto itr = find_key(s) ;
    if (itr != v_.end() and (*itr).first== s){//if the key equal to a key in MapSet. return the pair
        p = *itr;
        return p;
    }
    else
        return p;
}
bool MapSet::update(string s ,long l){// if the string as a key in MapSet. Put new value in for key s. return true. Other wise no action accure and return false
    auto itr = find_key(s) ;
    if (itr != v_.end() and (*itr).first== s){//if the key equal to a key in MapSet. Do changes
        (*itr).second = l;
        return true;
    }
    else 
        return false;
}
bool MapSet::remove (string s ){// if the string as a key in MapSet. Delate key s and its pair. return true. Other wise no action accure and return false
    auto itr = find_key(s) ;
    if (itr != v_.end() and (*itr).first== s){//if the key equal to a key in MapSet. Do changes
        v_.erase(itr);
        return true;
    }
    else
        return false;
}
bool MapSet::add(pair<string,long> p ){// if the string as a key is in the MapSet, do nothing and return false. Otherwise create a pair with the argument values and insert the new pair into the vector
    auto itr = find_key (p.first);
    if (itr != v_.end() and (*itr).first== p.first){//if the key equal to a key in MapSet. Do changes
        return false;
    }
    else{
        v_.insert(itr, p);
        return true;
    }
}
int MapSet::compare(MapSet& ms){// compare two MapSet by the first element in each pair. The first large value occure. if the value from calling MapSet. return 1. Otherwise return -1. If both equal. return 0;
    for (int i= 0; i < v_.size() and i < ms.v_.size();i++){//using the size as limit. compare the value of the key
        if (v_[i].first > ms.v_[i].first)
            return 1;
        else if (v_[i].first < ms.v_[i].first)
            return -1;
      }
    if (v_.size()>ms.v_.size())// within the two size limit. No large value occure. compare the size of each MapSet.
        return 1;
    else if ((v_.size() <ms.v_.size()))
        return -1;
    else 
        return 0;
}
MapSet MapSet::mapset_union (MapSet& ms){// union of two MapSet. return a new_mapset that have the union element of element of each MapSet. In sorted order.
    MapSet new_ms;
    new_ms.v_=v_;//Take calling MapSet as orginal MapSet
    for (int i= 0; i < ms.v_.size();i++){
        auto itr = new_ms.find_key(ms.v_[i].first);//Find if the argument set key are in the new_mapset. 
        if (itr == v_.end() or ms.v_[i].first != (*itr).first)
            new_ms.v_.insert(itr, ms.v_[i]);// If satificed. insert the pair into new_mapset
    }
    return new_ms;
}
MapSet MapSet::mapset_intersection(MapSet& ms){//intersection of two MapSet. return a new_mapset. 
    MapSet new_ms;
    for (int i= 0; i < ms.v_.size();i++){
        auto itr = find_key(ms.v_[i].first);//Taking the argument MapSet key. Use find_key method check if the key in the MapSet
        if (itr != v_.end() and ms.v_[i].first == (*itr).first)
            new_ms.v_.push_back(*itr);//push_back if they both have the key
    }
    return new_ms;
}
ostream& operator<<(ostream& out, MapSet& ms){//Returns the ostream. Take two argument. ostream and MapSet
    for (size_t i= 0; i < ms.size()-1;++i){//for each pair in the MapSet. Pass the first and second into ostream
        out << ms.v_[i].first<<":"<<ms.v_[i].second<<", " ;
    }
    out << ms.v_[ms.size()-1].first<<":"<<ms.v_[ms.size()-1].second;//pass the last pair alone to aviode the "," in the back.
    return out;
}