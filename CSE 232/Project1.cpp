/* 
Name : Tianhao Yang
Instructor : Dr. Bill Punch
Date : 2018/1/22
Section 012
Project number : 1
Description：This is a program helps calculate the monthly payment of loan car. It ask for six input and have one out put.
*/


#include<iostream>
#include<iomanip>
#include<cmath>

using std::cout;
using std::endl;
using std::cin;
using std::fixed;
using std::setprecision;
using std::scientific;
using std::pow;// This is the function for power in C++, pow(base,power) = base^power

int main() {
    double car_price;
    double sales_tax_rate;
    double downpayment;
    double title_and_fees;
    double yearly_interest_rate;
    double number_of_months_the_loan_will_last;//they define all six number that user are going to input
    
    cin >> car_price;
    cin >> sales_tax_rate;
    cin >> downpayment;
    cin >> title_and_fees;
    cin >> yearly_interest_rate;
    cin >> number_of_months_the_loan_will_last;//this ask for six input of user
    
    car_price = car_price + car_price * sales_tax_rate;
    car_price = car_price;
    car_price = car_price + title_and_fees;
    car_price = car_price;
    car_price = car_price - downpayment;
    car_price = car_price;//It calculate the principal of the car
    double monthly_interest_rate = yearly_interest_rate / 12;
    double monthly_payment = car_price * monthly_interest_rate * pow((1+monthly_interest_rate),number_of_months_the_loan_will_last)/(pow((1+monthly_interest_rate),number_of_months_the_loan_will_last)-1);//it calculate the monthly payment by using Final_price_minus_downpayment * ( (monthly_rate * (1 + monthly_rate)num_months / (1 + monthly_rate)num_months - 1 )
    
    cout << fixed   << setprecision(2) << monthly_payment << scientific<< endl;//it print out the correct value for monthly payment
    
}
