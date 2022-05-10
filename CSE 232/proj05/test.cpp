#include "proj05_functions.h"
#include<string>
using std::string;
#include <cctype>
using std::tolower; using std::isalpha;
#include<iostream>
using std::cout; 
using std::endl;

string create_encoding(string key){
    string encoding = "";
    for (std::string::size_type i=key.length()-1; i>0; --i){
        
        if (key.find(key[i])!= i or key[i]== 'q'){
            key.erase(i,1);
        }
    }
    encoding = key;
    char start = 'a';
    while (encoding.length()<25){
        if (encoding.find(start) == string::npos)
            encoding.push_back(start);
        start+=1;
        if (start == 'q')
            start +=1 ;
    }
    return encoding;
}

string encode_digraph(string dg, string block1, string block2){
    string code = "abcdefghijklmnoprstuvwxyz";
    string two_encode = "";
    string first_block = create_encoding(block1);
    string second_block = create_encoding(block2);
    int index1 = code.find(dg[0]);
    int index2 = code.find(dg[1]);
    int row1 = index1/5;
    int col1 = index1%5;
    int row2 = index2/5;
    int col2 = index2%5;
    int new_index1 = row1*5 + col2;
    int new_index2 = row2*5 + col1;
    two_encode.push_back(first_block[new_index1]);
    two_encode.push_back(second_block[new_index2]);
    return two_encode;
}

int main(){
    
    string test3 = encode_digraph("he","example","keyword");
    cout << test3 << endl;
    
    /*string example = "example";
    string test1 = create_encoding(example);
    cout << test1 << endl;
    string keyword = "keywoqqqqrd";
    string test2 = create_encoding(keyword);
    cout << test2 << endl;*/
}