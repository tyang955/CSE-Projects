
/* 
Name : Tianhao Yang
Instructor : Dr. Bill Punch
Date : 2018/3/26
Section 012
Project number :8
Description：This is a program to create user-defined data structures to be used in a simple stock market simulation. It include Market struct and Player struct.
*/


#include "proj08_market.h"
#include<fstream>
using std::ifstream;
#include<sstream>
using std::istringstream;
#include <map>
using std::map;
#include<string>
using std::string;
using std::to_string;
#include<algorithm>
using std::find;
#include<iterator>
#include<cctype>
#include<set>
using std::set;
#include<vector>
using std::vector;

Market::Market(string s){// takes a single string argument, a string file name
    ifstream in_file(s);//using the ifstream to open the file.
    string line;
    double value;
    long date;
    while(getline(in_file, line)){//passing everyline from the file while there is line left
        istringstream iss(line);//using istringstream to pass each space seprate elements
        iss >> date;//The first element is date
        while(iss >> value) // Pass the rest elements which is the stock price
            stocks[date].push_back(value);//Push back each value to the vector of the date.
    }
}

double Market:: get_price(string symbol, long date) const{//takes one string arguement and a date arguement. returns the price of the stock on the date if the date is a valid date and the stock symbol is a valid stock symbol
    auto iter = stocks.find(date);
    if (iter != stocks.end()){//If the date is in the stocks map
        for(int i= 0; i<30;++i){//use for loop to find the index of the symbol.
            if (symbol_list[i]==symbol){//The index of symbol is the index of the price
                double price = (*iter).second[i];
                return price;//return price
            }
        }
        return -1.0;//if the symbol is not in the symbol_list return -1.0
    }
    else 
        return -1.0;//if it can not find the date in stocks
}

pair<double, double> Market::high_low_year(long year, string symbol){//Takes a long year arguement and a stock symbol arguement. Returns as a pair the high and low values (in that order) for that stock for the provided year
    pair<double,double> high_low;
    string str_year = to_string(year);//convert long to string
    double high= 0.0;//set a limit for compare
    double low = 99999999.9;
    for(auto iter = stocks.begin(); iter != stocks.end(); ++iter){
        if (to_string((*iter).first).find(str_year)!=string::npos and to_string((*iter).first)[2]==str_year[2]){//If the year is in the stocks date. And the third index of the year match.
            for(int i= 0; i<30;++i){
                if (symbol_list[i]==symbol){//find the index of the symbol in the 30 stocks
                    double price = (*iter).second[i];//find the price of the stock
                    if (price > high)//if price larger than limit. price become new high
                        high = price;
                    if (price <low)//if price smaller than limit. price become new low
                        low = price;
                }
            }
        }
    }
    high_low = {high,low};
    if (high_low.first != 0.0 and high_low.second!=99999999.9)//if the price has changed. Means the date and symbol are now invild. Return the high and low
        return high_low;
    else //otherwise there is an error. return -1.0 and -1.0
        return {-1.0,-1.0};
}


















