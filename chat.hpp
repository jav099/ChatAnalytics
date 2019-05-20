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
#include "statistics.hpp"

using namespace std;

struct Message {
    string month = "";
    string day = "";
    string year = "";
    string time = "";
    string sender = "";
    //date in format M/D/YY
    string date = "";
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
    map<int,map<string,int>> yearMonthCount;
    
    map<int,int> yearCount;
    
    
    //Handles all the map setting for the person, also sets the maps for Data
    //increments total words, calls attachmentCounter
    void countingFunc(Message* msg,int& position);
    
    //counts the amount of gifs, images and audio per message.
    //increments the count for the respective person (sender) and for Data.
    void attachmentCounter(const Message* msg, const int& position);
    
    //TODO: Add a way to count common phrases
    int getTotalWords();
    
    string getName();
    
    int getImagesCount();
    
    int getAudioCount();
    
    int getYears();
    
    int getGifCount();
    
    int getTotalAttchments() const;
    
    
    void mapSetter(Message* msg);
    
    vector<Message*> messages;
    vector<map<string, int>> monthCountVect;
    
    friend ostream& operator <<(ostream& os, const map<int,int>& mp);
    
    friend ostream& operator <<(ostream& os, const map<string,int>& mp);
    
    friend ostream& operator <<(ostream& os, const map<int,map<string,int>*>& mp);
    
    string determineDayOfWeek(const string& month,
                              const  string& day, const string& year) const;
    
    bool hasWord(const string& text, const string& word) const;
    
    //TODO:
    //this func should take in as a parameter an array of exceptions
    std::pair<string, int> getWordWIthHighestCount(vector<string>& exc) const;
    
    std::pair<string, int> getWordWIthHighestCount() const;
    
    //returns the count of a certain word
    //if the word is not found it will return 0
    int getCountOfWord(const string& word) const;
    
    void computeTotalWords();
    
    int getMsgCount() const;
    
    //returns the position of the first msg in messages with date of date
    //if no message was found will return -1
    //if the specified date is simply the first message of a certain year
    //then date.second will be set to false, and date.first will be set
    //to the year (two digit year)
    int firstMsgAtDate(const std::pair<string, bool>& date) const;
    
    ~Person();
    
private:
    int totalWords;
    string name;
    int imageCount;
    int gifCount;
    int audioCount;
    int videoCount;
    //probably add count for months
    int startingYear = 0;
    int currentYear = 0;
    int totalAtchments = 0;
    
    
    
};



class Data {
public:
    friend class Person;
    friend class Stats;
    //sets the ifstream
    Data(string& filename, string& p1, string& p2);
    
    Data(string& filename, bool test);
    
    Data(string& filename, Person* p1, Person* p2, bool test);
    
    ifstream chatFile;
    
    map<string,int> uniqueDayWithMessageCount;
    
    //Counts the frequency of each word by calling both person's
    // respective functions which do all the adding of pairs into the
    // maps
    void readMsg();
    
   //sets all the date variables for msg
    //normalizes the month of a message;
    
    void messageSetter(ifstream& chatFile, string& date, Message* msg);
    
    //normalizes str(month) in case it has leftover strings before
    //it is called in message setter
    string dateNormalizer(const string& str) const;
    
 
    
    bool inString(const string& str, const char& c) const;
    
    int getTotalWords() const;
    
    int getImageCount() const;
    
    int getGifCount() const;
    
    int getTotalMessages() const;
    
    int getAudioCount() const;
    
    int getVideoCount() const;
    
    int countOfWord(const string& word) const;
    
    
    //returns the start date in M/D/Y
    string getStartOfChat() const;
    
    //returns how many unique days have at least one message sent
    int getUniqueDaysWithMessage() const;
    
    //returns the pair of the date with the most messages
    std::pair<string, int> getDateWithMostMessages() const;
    
    Person* person1;
    
    Person* person2;
    
    //returns the position of the first msg in messages with date of date
    //if no message was found will return -1
    //if the specified date is simply the first message of a certain year
    //then date.second will be set to false, and date.first will be set
    //to the year (two digit year)
    int firstMsgAtDate(const std::pair<string, bool>& date) const;
    
    string getEndOfChat() const;
    
    vector<Message*> msgVect;
    
    
    ~Data();
    
private:
    int totalWords;
    int imageCount;
    int gifCount;
    int audioCount;
    int videoCount;
    //date in format "M/D/Y"
    string startOfChat;
   
    void setStartOfChatDate(const Message* msg);
    bool forTests = false;
    
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
ostream& operator <<(ostream& os, const map<int,map<string,int>>& mp) {
    for (auto& kv : mp) {
        os << kv.first << endl;
        map<string,int> internalMap = kv.second;
        for (auto kv2 : internalMap) {
            os << " " << kv2.first << " : " << kv2.second;
            os << endl;
        }
    }
    
    return os;
}
#endif /* chat_hpp */
