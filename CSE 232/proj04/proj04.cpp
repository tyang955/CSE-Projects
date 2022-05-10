
/* 
Name : Tianhao Yang
Instructor : Dr. Bill Punch
Date : 2018/2/12
Section 012
Project number :4
Description：This is a program able to identify "palindromic prime" numbers in various bases.
*/


#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<string>
using std::string; using std::to_string; using std:: stol;
#include<cmath>
using std::pow;

const string the_chars = "0123456789abcdef";

//argument is a single string return is a string. Returns a new string which reverses the order of the argument string.
string reverse_string(string x){
    string reverse = "";
    for (int i = x.size()-1;i>=0; i--){//for each char in the string. Reappend to a empty string.
        reverse += x[i];
    }
    return reverse;
}

bool is_palindrome(string x){//Single string argument and bool return. Returns true or false, is the string a palindrome
    string reverse = reverse_string(x);
    if (x == reverse) // use the reverse_string function determined weather the reverse function is same as the old function.
        return true;
    else 
        return false;
}

string long_to_base(long x, long y){//two arguments long , the long converting and the base converting to. Return is string
    if (y==2){//Base 2 binary when y = 2.
        string Binary = "";
        while (x>0){
            long num = x%2;//take the reminder
            string reminder = to_string(num);//make the reminder become string
            x = (x - x%2)/2;//change the original num to new number by divide and subtract the reminder
            Binary.insert(0,reminder);//keep insert to position 0 so it is backward
        }
        return Binary;
    }
    else if (y==10){//the input long is binary, No change but make it to a string
        return to_string(x);
    }
    else if (y==16){//Same process like binary
        string reminder = "";
        string Hexadecimal = "";
        while (x> 0){
            int num = x%16;
            reminder = the_chars[num];//Look up which charactor it represent when num bigger than 9
            Hexadecimal.insert(0,reminder);
            x = (x - x%16)/16;
        }
        return Hexadecimal;
    }
    else
        return 0;
}
bool is_prime(long x){//Takes a single long argument return is bool
    long i = 2;
    while (i<x/2){//divide by nunber from 2 to half of x. If no solution then it is prime.
        if (x%i== 0)
            return 0;
        i++;
    }
    return 1;
}

string is_pal_prime(long x){//takes a single long argument returns one of the following 4 strings: binary-pal-prime decimal-pal-prime hex-pal-prime not-pal-prime.
    if (is_prime(x) == true and is_palindrome(long_to_base(x,2))== true)//if the number satificed two argument then return the matching string.
        return "binary-pal-prime";
    if (is_prime(x) == true and is_palindrome(long_to_base(x,10))== true)
        return "decimal-pal-prime";
    if (is_prime(x) == true and is_palindrome(long_to_base(x,16))== true)
        return "hex-pal-prime";
    else
        return "not-pal-prime";
}


int main (){
long test_num;
cin >> test_num;
cout << boolalpha;

switch(test_num) {

case 1: {
    string input;
    cin >> input;
    cout << reverse_string(input);
    break;
}

case 2:{
    string input;
    cin >> input;
    cout << is_palindrome(input);
    break;
}

case 3:{
    long n, base;
    cin >> n >> base;
    cout << long_to_base(n,base);
    break;
}

case 4:{
    long n;
    cin >> n;
    cout << is_prime(n);
    break;
}

case 5:{
    long n;
    cin >> n;
    cout << is_pal_prime(n);
    break;
}
    
} // of switch
}  // of main
  
