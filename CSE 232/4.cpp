#include<iostream>
#include<iomanip>
#include<cmath>

using std::cout;
using std::endl;
using std::cin;


int main() {
    long input;
    long cnt = -1;
    long sum = 0;
    cin >> input;
    if (input <= 0)
        cout << "Error" << endl;
    else if (input < 9)
        cout << "0 " << input << endl;

    else if (input > 9){
        while ( input > 9 ){
            while (input > 9) {
                sum = sum + (input%10);
                input = input/10;
            cnt = cnt + 1;
            }
        }
        cout << cnt << " " << input << endl;}
}
