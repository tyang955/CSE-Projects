
/* 
Name : Tianhao Yang
Instructor : Dr. Bill Punch
Date : 2018/2/25
Section 012
Project number :5
Description：This is a program work with Foursquare Cipher. Having the the functions to do encoding and decoding by given message string and two key string.
*/


#include "proj05_functions.h"//Header files that allowed to achieve independent compilations
#include<string>
using std::string;
#include <cctype>
using std::tolower; using std::isalpha;

string clean_string(string s){//takes a string arguement and returns a new string that is all lowercase and consists of only alphabetic characters in orignal string.
    for (std::string::size_type i=0; i<s.length(); ++i){//pass the letters in the string
        if (isalpha(s[i]))//check if the char that passby is a alphabet
            s[i]=tolower(s[i]);//if is a alphabet become lowercase
        else{
            s.erase(i,1);//if the char that passby is not alphabet. Erase it
            --i;
        }
    }
    return s;
}

string create_encoding(string key){//takes in a key, and returns a keyword encoding that there are no repeat letters in the key. Then the rest of the key are follow by alphabetic order. But no repeat letter ocurr.
    string encoding = "";
    for (std::string::size_type i=key.length()-1; i>0; --i){//pass the letters in the string
        if (key.find(key[i])!= i or key[i]== 'q'){//erase the letter if it is repeating or equal to q.
            key.erase(i,1);
        }
    }
    encoding = key;
    char start = 'a';
    while (encoding.length()<25){
        if (encoding.find(start) == string::npos)//compare alphabetic order weather the letter is in the key
            encoding.push_back(start);// if not. push back into the key
        start+=1;
        if (start == 'q')//if equal to 'q'. erase it.
            start +=1 ;
    }
    return encoding;
}

string encode_digraph(string dg, string block1, string block2){//take three arguement. The one need to encode. Two keyword that used as a key.
    string code = "abcdefghijklmnoprstuvwxyz";
    string two_encode = "";
    string first_block = create_encoding(block1);//key string
    string second_block = create_encoding(block2);
    int index1 = code.find(dg[0]);//find the index of dg in alphabetic digraph
    int index2 = code.find(dg[1]);
    int row1 = index1/5;//find each char's row and col.
    int col1 = index1%5;
    int row2 = index2/5;
    int col2 = index2%5;
    int new_index1 = row1*5 + col2;//get each of the char a row and a col and combine them to get the new index.
    int new_index2 = row2*5 + col1;
    two_encode.push_back(first_block[new_index1]);//using pushback to mix the two new letters together
    two_encode.push_back(second_block[new_index2]);
    return two_encode;
}   
        
        
string decode_digraph(string dg, string block1, string block2){//take three arguement. The one need to dncode. Two keyword that used as a key. Sililar to the encode_digraph function. 
    string code = "abcdefghijklmnoprstuvwxyz";
    string two_decode = "";
    string first_block = create_encoding(block1);
    string second_block = create_encoding(block2);
    int index1 = first_block.find(dg[0]);
    int index2 = second_block.find(dg[1]);
    int row1 = index1/5;
    int col1 = index1%5;
    int row2 = index2/5;
    int col2 = index2%5;
    int new_index1 = row1*5 + col2;
    int new_index2 = row2*5 + col1;
    two_decode.push_back(code[new_index1]);
    two_decode.push_back(code[new_index2]);
    return two_decode;
}

string encode(string msg, string key1, string key2){//takes in the message to encode and the two keywords used for encoding. return a string that is encoding msg.
    msg = clean_string(msg);//make sure the string only contains letters.
    if (msg.length()%2==1)//if the original message has an odd number of letters, 'x' is added to the end
        msg.push_back('x');
    string msgencode = "";
    for (std::string::size_type i=0; i<msg.length(); i+=2){//for two letters in a group. Each of the group encode by encode_digraph function.
        string dg = "";
        string new_dg = "";
        dg.push_back(msg[i]);
        dg.push_back(msg[i+1]);//get the two letters by index.
        new_dg = encode_digraph(dg,key1,key2);
        msgencode.append(new_dg);//append new letters to a string
    }
    return msgencode;
}
string decode(string msg, string key1, string key2){//takes in the encoded message to decode and the two keywords used for encoding. Return a string that is decoding msg. Silmilar to the function encode.
    msg = clean_string(msg);
    if (msg.size()%2==1)
        msg.push_back('x');
    string msgdecode = "";
    for (std::string::size_type i=0; i<msg.length(); i+=2){
        string dg = "";
        string new_dg = "";
        dg.push_back(msg[i]);
        dg.push_back(msg[i+1]);
        new_dg = decode_digraph(dg,key1,key2);
        msgdecode.append(new_dg);
    }
    return msgdecode;
}