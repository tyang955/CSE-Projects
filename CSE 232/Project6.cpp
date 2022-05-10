
/* 
Name : Tianhao Yang
Instructor : Dr. Bill Punch
Date : 2018/3/12
Section 012
Project number :6
Description：This is a program work with Fibonacci n-step sequences. Having the the functions to do Fibonacci number encoding by given number limit and  number of seeds required and the number of previous values that are added to create the next number. It also able to transfer the coding value to numbers.
*/
#include "proj06_functions.h"
#include<string>
using std::string;
#include<vector>
using std::vector;
using std::string;
#include <sstream>
using std::ostringstream;

string vec_2_str(const vector<long>& v){//returns a string that represents the values in the vector
    ostringstream oss;//use the ostringstream that able to add and change the stream more eaisier
    for( auto iter = v.cbegin (); iter != v.cend(); ++iter){//run through all the element and add it to the ostringstream
        oss << *iter << "," ;//dereference and seprate by ","
    }
    string result = oss.str();//changed it to string 
    return result.substr(0, result.size() - 1);
}

vector<long> gen_nstep_vector (long limit, long nstep){//generates a vector containing the nstep sequence
    vector<long> nstep_seq = {1,1};//The sequence must bigger or equal to 2. So it must contain "1" and "1"
    for (int i = 2 ; i < nstep; ++i){//Find the seed number first. The number of nstep is the number of seed
        long seed= 0;
        for (int p=0; p < nstep_seq.size();++p)
            seed += nstep_seq[p];//each new seed number is the sum of all previous number.
        nstep_seq.push_back(seed);//push_back the seed number
    }
    while (nstep_seq.back() <= limit){// find all the number that smaller than limit and satififed the sequence rule
        long sum=0;
        for (long i= nstep; i > 0; --i){//Add the number of number that nstep shows.
            sum += nstep_seq[nstep_seq.size()-i];
        }
        nstep_seq.push_back(sum);//Push back to the vector
    }
    nstep_seq.pop_back();//the while loop will add a number the number that just become larger than the limit. So it need to be clear.
    return nstep_seq;
}

string num_to_nstep_coding(long num, long nstep){//returns a binary string which represents num as the nstep sequence. Takes two long arguement. A number limit and a seed number.
    vector<long> v = gen_nstep_vector(num,nstep);//get the sequence
    string result = "";
    for(auto iter=v.rbegin(); iter!=v.rend(); ++iter){//From the larggest to smallest
        if (*iter<=num){//If the number is bigger than the sequence number. Then minus the number
            num = num - *iter;
            result.insert(0,"1");//Add a "1" in the result string
        }
        else
            result.insert(0,"0");//if the number is bigger. Add a "0" and keep going
    }
    return result.substr(1);
}

long nstep_coding_to_num(const string& coding, const vector<long>& nstep_sequence){//converts the nstep coded binary string to a long
    long result = 0;
    for (std::string::size_type i = 0; i < coding.size();++i){//run through each element in the string. 
        if ((coding[i])=='1')//If there is a "1" then add the matching number
            result +=nstep_sequence[i+1];
    }
    return result;
}