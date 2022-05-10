/* 
Name : Tianhao Yang
Instructor : Dr. Bill Punch
Date : 2018/1/28
Section 012
Project number : 2
Description：This is a program working with loop based on juggler sequence.
*/


#include<iostream>
#include<iomanip>
#include<cmath>

using std :: cout;
using std :: endl;
using std :: cin;
using std :: pow; // get the power of the number
using std :: sqrt;// get the square root of the number
using std :: floor;// rounding any floating point value down to an integer

int main() {

    long a,b,c ;
    long output;
    long longest = 0;
    long biggest = 0;
    long long_starting_num;
    long big_starting_num;
    long i;
    
    cin >> a >> b >> c ; // get three input separated by space
    
    if (a >= 2 and b >= 2 and b > a){ //check that the first two input range numbers are >= 2, and that the smallest (the first entered value) is indeed strictly smaller than the second (the second value). If not, the program prints an error message and halts
    
        if (c == 1){ // when c equal to 1, it shows the sequence for each number in the range on a separate line
            while (a <= b){
                cout << a << ": "; // starting with the number
                long count_num = 1;
                i = a;
                while (i != 2){ // This function follow the rule of juggler sequence that first determined weather is a even or off number. Then do the operation
                    output = 0;
                    if (i%2 == 0)
                        output  = floor (sqrt(i));
                    else
                        output  = floor (sqrt(i)*sqrt(i)*sqrt(i));
                    i = output;
                    
                    cout << output << ",";
                    count_num ++;
                                        
                    if (biggest < output) // These two if statement find the longest and biggest number in the sequence
                    { 
                        biggest = output;
                        big_starting_num = a;
                    }
                
                    if (longest < count_num){
                        longest = count_num ;
                        long_starting_num = a;
                    }
                }
                cout << "1"<< endl;
            a++; // The starting number increase each time until larger than the second value
                
            }
        }
        else { // This function repeat the process above when third value equal to 1. The difference is this function doesn't have any out put.
            while (a <= b){
                long count_num = 1;
                i= a;
                while (i != 2){
                    output = 0;
                    if (i%2 == 0)
                        output  = floor(sqrt(i));
                    else
                        output = floor(sqrt(i)*sqrt(i)*sqrt(i));
                    i = output;
                    
                    count_num ++;
                    
                    if (biggest < output){
                        biggest = output;
                        big_starting_num = a;
                    }
                
                
                    if (longest < count_num){
                        longest = count_num;
                        long_starting_num = a;
                    }
                }
            a++;
            }
        }
    cout << long_starting_num << ", "<< longest << endl; //Output the longest and biggest value and starting number
    cout << big_starting_num << ", "<< biggest << endl; 
    }
    else //error message show up when something went wrong
        cout << "Error" << endl;
}