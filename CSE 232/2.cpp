#include <iostream>
using std::cout; using std::cin; using std::endl; using std::fixed;
#include<iomanip>
using std::setprecision;

int main() {
    long days;
    cin >> days;
    
    long double distance = days * 24 *60 *60 * 14.24 / 149598000 + 39.33 ;
    double kilometers = distance * 149598000;
    double miles = 92955800 * (days * 24 * 60* 60 * 8.85 /92955800 + 39.33);
    double times = kilometers * 2 *1000 / 299792458 /60 /60;
   
    cout << fixed << setprecision(2);
    
    cout << kilometers << endl;
    cout << miles << endl;
    cout << times << endl;
    
}
