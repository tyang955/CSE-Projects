/* 
Name : Tianhao Yang
Instructor : Dr. Bill Punch
Date : 2018/3/26
Section 012
Project number :8
Description：This is a program to create user-defined data structures to be used in a simple stock market simulation. It include Market struct and Player struct.
*/

#include "proj08_player.h"

using std::string;
using std::to_string;
#include<sstream>
using std::ostringstream;
#include <iostream>
using std::endl;
#include<iomanip>
using std::fixed; using std::setprecision;


bool Player::buy(Market & mk, string symbol, long date, long quantity){//Takes 4 arguement. The Market map. The stock going to buy. The buying date and the quantity of the stock going to buy. Return is a bool.
    string str_date = to_string(date);//convert the date to a string
    for(auto iter = mk.stocks.begin(); iter != mk.stocks.end(); ++iter){
        if (to_string((*iter).first).find(str_date)!=string::npos){//Go through the map and if there is the date key
            for(int i= 0; i<30;++i){//find the index of the stock
                if (mk.symbol_list[i]==symbol){
                    double price = (*iter).second[i];//The price of the stock has the same index
                    if (cash > quantity*price){//if the cash is larger than the cost
                        cash=cash-quantity*price;//subtrack the cost from cash
                        stocks[symbol]+=quantity;//Stock number increase
                        return true;
                    }
                }
            }
        }
    }
    return false;//If no action taken. Return false
}
bool Player::sell(Market &mk, string symbol, long date, long quantity){//Takes 4 arguement. The Market map. The stock going to sell. The selling date and the quantity of the stock going to sell. Return is a bool.
    string str_date = to_string(date);//coonvery the date to string
    for(auto iter = mk.stocks.begin(); iter != mk.stocks.end(); ++iter){
        if (to_string((*iter).first).find(str_date)!=string::npos){////Go through the map and if there is the date key
            for(int i= 0; i<30;++i){//find the index of the stock
                if (mk.symbol_list[i]==symbol){
                    double price = (*iter).second[i];//The price of the stock has the same index
                    if (stocks[symbol]>=quantity){//If player have enough stock to sell
                        cash+=quantity*price;//cash increase
                        stocks[symbol]-=quantity;//stock number hold decrease
                        return true;
                    }
                }
            }
        }
    }
    return false;//If no action taken. Return false
}
string Player::to_str(){//returns a string representation of the player
    ostringstream oss;//using ostringstream
    oss<< fixed << setprecision(2);//fixed and setprecision
    oss << cash<<",";//Put the cash left in the begining
    for(auto iter = stocks.begin(); iter != stocks.end(); ++iter){//go through each stock
        if ((*iter).second!=0)//if the player have the stock
            oss<<(*iter).first<<":"<<(*iter).second<<",";//put into ostringstream
    }
    oss<<endl;
    string str = oss.str();//convert into string 
    string out_str = str.substr(0, str.size()-2);//remove the last endl and ","
    return out_str;
}
Player Player::combine(Player& p2){//returns a new Player that has, as a combination, all the cash and stocks of the two players
    Player c;
    c.stocks=stocks;//copy the stocks form the Player 1
    for(auto iter = p2.stocks.begin(); iter != p2.stocks.end(); ++iter){//go through the stocks from p2 and add to the new player stocks
        c.stocks[(*iter).first]+=(*iter).second;
    }
    c.cash=cash + p2.cash;// Add the cash p1 and p2 have to new player
    stocks.clear();//clear everything form p1
    cash=0;
    p2.stocks.clear();//clear everything form p2
    p2.cash=0;
    return c;
}