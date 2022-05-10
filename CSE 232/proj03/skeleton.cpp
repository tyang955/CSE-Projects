#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<cmath>
#include<string>
using std::to_string; using std::string;

string abIndex_friend(long ab_numerator, long ab_denominator, long f_pair){
  return to_string(ab_numerator) + "/" + to_string(ab_denominator) +
    ":" + to_string(f_pair);
}

long divisor_sum (long x){
	long result = 0;
	for (long i=1; i<=sqrt(x); i++){
		if (x%i==0)
		{
			if (i==(x/i))
				result += i;
			else
				result += (i + x/i);
		}
	}
	return result;
}

long gcd (long x, long y){
    long gcd_num = 1;
    for(long i=2 ; i < x or i < y ; i ++){
        if (x%i == 0 and y%i == 0){
            gcd_num = i;
        }
    }
    return gcd_num;
}

bool is_solitary (long x){
    long divisor_value = divisor_sum (x);
    long gcd_value = gcd(divisor_value,x);
    if (gcd_value > 1)
        return false;
    else
        return true;
}

string friendly_check (long x,long y){
    long ori = x;
    long numer ;
    long denom ;
    while (is_solitary(x) == false){
        long gcdnum = gcd( divisor_sum(x) , x );
        numer = divisor_sum(x)/gcdnum;
        x = x/gcdnum ;
    }
    long i_numer;
    for (long i = 2; i < y ; i ++){
        long new_i = i ;
        while (is_solitary(new_i) == false){
            long i_gcdnum = gcd( divisor_sum(new_i) , new_i );
            i_numer = divisor_sum(new_i)/i_gcdnum;
            new_i = new_i/i_gcdnum ;
            if (numer == i_numer and x == new_i and i!= ori)
                return abIndex_friend( numer , x , i );
        }
        
    }
    return abIndex_friend( numer , denom , -1 );
}

int main (){
    
    
    cout << is_solitary (14256)<< endl;
    cout << divisor_sum(14256)<< endl;
    cout << gcd(divisor_sum(14256),14256) << endl;
    
    cout << is_solitary (108)<< endl;
    cout << divisor_sum(108)<< endl;
    cout << gcd(divisor_sum(108),108) << endl;
    
    
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

