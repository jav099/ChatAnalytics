//
//  chat.hpp
//  ChatAnalytics
//
//  Created by Javier Contreras on 5/4/19.
//  Copyright © 2019 Javier Contreras. All rights reserved.
//

#ifndef chat_hpp
#define chat_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <ctime>

using namespace std;

struct Message {
    string month = "";
    string day = "";
    string year = "";
    string time = "";
    string sender = "";
    vector<string> msgTxt;
    
};

class Person {
public:
    friend class Data;
    Person(string name_in);
    map<string,int> wordCount;
    map<string,int> monthCount;
    map<string,int> dayCount;
    //add another map with a format similar to the map below
    //TODO: add here.
    //map with key year, and value monthCount ptr
    map<int,map<string,int>*> yearMonthCount;
    
    map<int,int> yearCount;
    
    
    //Handles all the map setting for the person, also sets the maps for Data
    //increments total words, calls attachmentCounter
    void countingFunc(Message* msg,int& position);
    
    //counts the amount of gifs, images and audio per message.
    //increments the count for the respective person (sender) and for Data.
    void attachmentCounter(const Message* msg);
    
    //TODO: Add a way to count common phrases
    int getTotalWords();
    
    string getName();
    
    int getImagesCount();
    
    int getAudioCount();
    
    int getYears();
    
    int getGifCount();
    
    void mapSetter(Message* msg);
    
    vector<Message*> messages;
    vector<map<string, int>> monthCountVect;
    
    friend ostream& operator <<(ostream& os, const map<int,int>& mp);
    
    friend ostream& operator <<(ostream& os, const map<string,int>& mp);
    
    string determineDayOfWeek(const string& month,
                              const  string& day, const string& year) const;
    
    
    ~Person();
    
private:
    int totalWords;
    string name;
    int imageCount;
    int gifCount;
    int audioCount;
    
    //probably add count for months
    int startingYear = 0;
    int currentYear = 0;
    
};



class Data {
public:
    friend class Person;
    //sets the ifstream
    Data(string& filename);
    
    ifstream chatFile;
    
    map<string,int> wordCount;
    map<int,int> monthCount;
    map<int,int> yearCount;
    
    //Counts the frequency of each word by calling both person's
    // respective functions which do all the adding of pairs into the
    // maps
    void readMsg(Person* person1, Person* person2);
    
   //sets all the date variables for msg
    void messageSetter(ifstream& chatFile, string& date, Message* msg);
    
//    Message* readRestOfMsg(ifstream& chatFile);
    
    string dateNormalizer(const string& str) const;
    
    ~Data();
    
    bool inString(const string& str, const char& c) const;
    
    int getTotalWords();
    
private:
    int totalWords;
    int imageCount;
    int gifCount;
    int audioCount;
    vector<Message*> msgVect;
};

ostream& operator <<(ostream& os, const map<int,int>& mp) {
    for (auto &kv : mp) {
        os << kv.first << " : " << kv.second;
        os << endl;
    }
    return os;
}

ostream& operator <<(ostream& os, const map<string,int>& mp) {
    for (auto &kv : mp) {
        os << kv.first << " : " << kv.second;
        os << endl;
    }
    return os;
}
#endif /* chat_hpp */
