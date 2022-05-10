
/* 
Name : Tianhao Yang
Instructor : Dr. Bill Punch
Date : 2018/3/19
Section 012
Project number :7
Description：This is a program to manage a list of computer servers, where each server hosts multiple users. The server data is stored as an associative data structure type. This function are able to add a user to a server, disconnect a user from a server, balance the server load
*/


#include "proj07_functions.h"
#include <iostream>
using std::endl; using std::boolalpha;using std::ostream;
#include <map>
#include<string>
using std::string;
#include<algorithm>
using std::find;
using std::set_intersection;using std::set_symmetric_difference;
#include<iterator>
using std::back_inserter; using std::ostream_iterator; using std::distance;
#include<sstream>
using std::ostringstream;using std::istringstream;
#include<map>
#include<cctype>
using std::map;
#include<set>
using std::set;
#include<fstream>
using std::ifstream;
#include <ostream>
#include<stdexcept>
using std::domain_error;
using std::invalid_argument;


ServerData ParseServerData(const std::string &fname){
    ifstream in_file(fname);//open the file
    if (in_file.is_open()==0){//if the file name cannot be opened, the function throws an invalid_argument exception
        throw std::invalid_argument("");
    }
    string line,c1,c2,c3;
    ServerData sd;
    while(getline(in_file, line)){//pass each line from the file to a istringstream
        istringstream iss(line);
        iss>>c3>>c2>>c1;//get the stringstream by their space seprate
        if (c2 == "join"){//if the second word of the string is join
            auto iter2 = sd[c1].find(c3);
            if (iter2 == sd[c1].end())//if the name is not in the server
                sd[c1].insert(c3);//add the name to the server
        }
        else if (c2 == "leave"){
            sd[c1].erase(c3);//if the second word is leave. delate the name from the server.
        }
        else{
            throw domain_error("");//if any of the input lines has a command other than leave or join, the function throws a domain_error exception
        }
    }
    return sd;
}
void PrintAll(std::ostream & out, const ServerData &sd){//Prints the contents of sd to out
    for (auto iter = sd.begin(); iter != sd.end(); ++iter){//pass each key in the ServerData by iterator
        std::ostringstream temp;//in order to modify in the end. create a new ostringstream
        temp << (*iter).first << " : ";
        for (auto element : (*iter).second)
            temp << element << " ";//pass each element in the key using iterator
        temp << endl;
        string temp_str = temp.str();//convert the ostringstream to a string. Thus able to delate the last space.
        string out_str = temp_str.substr(0, temp_str.size()-2);//substr to remove last two element
        out << out_str << endl;//put into the ostream
        temp.clear();
    }
}

bool AddConnection(ServerData &sd, ServerName sn, UserName un){//this function connect the user un to the server sn.Takes three arguement and return is a bool
    map<string, set<string>>::iterator iter;
    iter = sd.find(sn);//ask if the server name exist
    if (iter == sd.end()){// if can not find the server.create server and add user to the new server.
        sd.insert({sn,{un}});
        return true;//success add. return true
    }
    else{
        auto iter2 = sd[sn].find(un);//find if the name is exist in the server.
        if (iter2 == sd[sn].end()){//if can not find the name. Add the name
            iter->second.insert(un);
            return true;//success add. return true.
        }
        else 
            return false;//nothing changed. return false
    }
}
bool DeleteConnection(ServerData &sd, ServerName sn, UserName un){//This function tries to disconnect the user un from the server sn, and returns true if d is successfully updated with that information. If the user un is not connected to the server sn, then no action is taken, and the function returns false
    auto iter = sd[sn].find(un);
    if (iter != sd[sn].end()){//if find the user name from the ServerData
        sd[sn].erase(un);//erase the name and return true
        return true;
    }
    else
        return false;
}
set<string> AllServers(const ServerData &sd){//Returns a set<string> which is the set of all servers in the sd
    set<string> as{};
    for (auto iter = sd.begin(); iter != sd.end(); ++iter)//use iterator to pass all the key in the map to a set
        as.insert((*iter).first);
    return as;
}
set<string> AllUsers(const ServerData &sd){//Returns a set<string> which is the set of all users on any server in the sd
    set<string> au{};
    for (auto iter = sd.begin(); iter != sd.end(); ++iter){//pass through all the server
        for (auto element : (*iter).second)//pass through all the element in the server.
            au.insert(element);//add to the new set
    }
    return au;
}
set<string> HasConnections(const ServerData & sd, UserName un){//This function returns a set<string> of all the server names in sd that the user un is currently connected to.
    set<string> hc{};
    for (auto iter = sd.begin(); iter != sd.end(); ++iter){
        for (auto element : (*iter).second){//go through all the server and all the element in the server.
            if (un == element)//if the name equal to the element
                hc.insert((*iter).first);// add the server name to a new set
        }
    }
    return hc;
}
set<string> HasUsers(const ServerData &sd, ServerName sn){//This function returns a set<string> of all the user names in the server sn that are currently connected in sn. Note that the return set could be empty
    set<string> hu{};
    auto iter = sd.find(sn);//find if the server exist in the map. 
    if (iter != sd.end()){
        for (auto element : (*iter).second)// pass through all the element from the server
            hu.insert(element);//put the element in the new set
    }
    return hu;
}

void BalanceServers(ServerData & sd, ServerName s1, ServerName s2){//user in both server are not moving. The users are sorted alphabetically by their name, and the first half are moved to server sn1, and the other half are moved to server sn2
    set<string> temp ;//create two temp set to store user names
    set<string> temp2 ;
    set<string> first = sd[s1];//put the user name into the new set
    set<string> second = sd[s2];
    set_symmetric_difference(//find the set_symmetric_difference using function
        first.begin(), first.end(),//the first set from begin to end
        second.begin(), second.end(),//the second set from begin to end
        inserter(temp,temp.begin()));//insert into the temp set
    set_intersection(//samiliar to the function set_symmetric_difference
        first.begin(), first.end(),
		second.begin(), second.end(),
		inserter(temp2,temp2.begin()));
	sd.erase(s1);//clear both server from map
	sd.erase(s2);
	sd[s1]=temp2;//put the intersection unit into map
	sd[s2]=temp2;
	auto iter = temp.begin();
	int half = temp.size()/2;
	int total = temp.size();
    for (int i = 1; i <= total -half; i++) {//get the element that always half or one more than half
        sd[s1].insert(*iter);//insert into the first server
        ++iter;
    }
    for (int i = total-half+1; i <= total; i++) {//get the rest element
        sd[s2].insert(*iter);//insert into the second server
        ++iter;
    }
}
void CleanAndBalance(ServerData & sd){// removes all duplicate users from sd.The users are distributed to servers in a round-robin fashion in alphabetical order of server and user names
    set<string> as = AllServers(sd);//get all of the server into the new set
    set<string> au = AllUsers(sd);// get all user into new set 
    sd.clear();//clean the ServerData
    auto au_iter = au.begin();
    while(au_iter!= au.end()){//while there are still user left 
        for (auto iter = as.begin(); iter != as.end(); ++iter){//go through each server and put the user one by one
            sd[(*iter)].insert(*au_iter);
            ++au_iter;//go to next user
            if (au_iter == au.end())//if run out of user. The program stop
                break;
        }
    }
}