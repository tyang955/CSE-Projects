/* 
Name : Tianhao Yang
Instructor : Dr. Bill Punch
Date : 2018/2/5
Section 012
Project number :3
Description：This is a program working with Friendly vs Solitary.
*/





#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<cmath>
#include<string>
using std::to_string; using std::string;

string abIndex_friend(long ab_numerator, long ab_denominator, long f_pair){
  return to_string(ab_numerator) + "/" + to_string(ab_denominator) +
    ":" + to_string(f_pair);
}

long divisor_sum (long x){ // Function divisor_sum. Return is a long. Takes a single long argument, the number to calculate the divisor sum of
	long result = 0;
	for (long i=1; i<=sqrt(x); i++){
		if (x%i==0)
		{
			result += (i + x/i);
		}
	}
	return result;
}

long gcd (long x, long y){//Function Gcd. Return is long. Takes two long arguments, returns the greatest common divisor of the two input values.
    while (y != 0){
        long z = x%y;
        x=y;
        y=z;
    }
    return x;
}

bool is_solitary (long x){ // Function is solitary. Return is bool. Argument is a single long argument. Check if theargument and its divisor sum have as their gcd 1. If so, it is solitary and we return true. If not, well we really don't know but for this function we return false.
    long divisor_value = divisor_sum (x);
    long gcd_value = gcd(divisor_value,x);
    if (gcd_value > 1)
        return false;
    else
        return true;
}

string friendly_check (long x,long y){ // Funtion friendly check. Return is a string (see last item). Takes two numbers: the first an integer to check and the second the upper limit of the other integers we are willing to check against the first number to see if they are a friendly pair
    long ori = x;
    long numer = divisor_sum (x) ;
    while (gcd(numer,x) > 1){
        long divide = gcd(numer,x);
        numer = numer/divide;
        x = x/divide;
    }
    for (long i = 2; i < y ; i ++){
        long new_i = i ;            
        long i_numer = divisor_sum(new_i);
        long i_divide = gcd(i_numer,new_i);
        for (i_divide;i_divide > 1;i_divide = gcd(i_numer,new_i)){
            i_numer = i_numer / i_divide;
            new_i = new_i/ i_divide ;
        }
        if (numer == i_numer and new_i ==x and i != ori)
            return abIndex_friend( numer , x , i );
    }
    return abIndex_friend( numer , x , -1 );
}

int main (){
  cout << boolalpha;   // print true or false for bools
  int test;
  cin >> test;
  switch (test) {
  case 1 : {   // divisor sum test
    long input;
    cin >> input;
    cout << divisor_sum(input) << endl;
    break;
  } // of case 1

  case 2:{    // gcd test
    long first, second;
    cin >> first >> second;
    cout << gcd(first, second) << endl;
    break;
  } // of case 2

  case 3: {    // is_solitary test
    long input;
    cin >> input;
    cout << is_solitary(input) << endl;
    break;
  } // of case 3

  case 4: {
    // friend check. Make sure the return value is the
    // result of calling abIndex_friend, a string!
    long input, limit;
    cin >> input >> limit;
    cout << friendly_check(input, limit) << endl;
    break;
  } // of case 4
    
  } // of switch
} // of main


