//
//  chat.cpp
//  ChatAnalytics
//
//  Created by Javier Contreras on 5/4/19.
//  Copyright © 2019 Javier Contreras. All rights reserved.
//

#include "chat.hpp"
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



Data::Data(string& filename) : totalWords(0), imageCount(0), gifCount(0)
, audioCount(0), videoCount(0), startOfChat(""){
    chatFile.open(filename);
    if (!chatFile.is_open()) {
        cout << "error opening file";
        assert(false);
    }
}
//Counts the frequency of each word by calling Javier's and Mech's
// respective functions which do all the adding of pairs into the
// maps
void Data::readMsg(Person* person1, Person* person2) {
    string person1Name = person1->name;
    string person2Name = person2->name;
    string word;
    Message *msg = nullptr;
    int msgCount = 0;
    int p1Position = -1;
    int p2Position = -1;
    while (chatFile >> word) {
        //if its the start of a new message
        if (inString(word, '[')) {
            msg = new Message;
            messageSetter(chatFile, word, msg);
            msgCount++;
            msgVect.push_back(msg);
            setStartOfChatDate(msg);
            if (msg->sender == person1Name) {
                person1->messages.push_back(msg);
                person1->mapSetter(msg);
                p1Position = -1;
            } else if (msg->sender == person2Name) {
                person2->messages.push_back(msg);
                person2->mapSetter(msg);
                p2Position = -1;
            }
            
        } else {
            msg->msgTxt.push_back(word);
            
            //////
            if (msg->sender == person1Name) {
                p1Position++;
                person1->countingFunc(msg,p1Position);
            } else if (msg->sender == person2Name) {
                p2Position++;
                person2->countingFunc(msg,p2Position);
            }
            ///////
        }
    }
    
}

//sets all the date variables for msg
void Data::messageSetter(ifstream& chatFile, string& date, Message* msg) {
    //i would be the position of the first number in [2/23/17,
    int i = 1;
    string datum = date;
    //this would stop at the '/' before the day
    while (datum[i] != '/') {
        msg->month += datum[i];
        i++;
    }
    //this would stop at the '/' before the year
    while (datum[i+1] != '/') {
        msg->day += datum[i+1];
        i++;
    }
    //this would stop at the ',' in date which should be of form [2/23/17,
    while (datum[i+2] != ',') {
        msg->year += datum[i+2];
        i++;
    }
    
    msg->month = dateNormalizer(msg->month);
    
    getline(chatFile, msg->time, ']');
    getline(chatFile, msg->sender, ':');
    string correctName = msg->sender;
    correctName.erase(std::remove_if(correctName.begin(),
                                     correctName.end(), ::isspace), correctName.end());
    msg->sender = correctName;
}

//Handles all the map setting for the person, also sets the maps for Data
//increments total words, calls attachmentCounter
void Person::countingFunc(Message* msg, int& position) {
    if (totalWords == 0) {
        startingYear = stoi(msg->year)+2000;
    }
    try {
        currentYear = stoi(msg->year)+2000;
    } catch (invalid_argument) {
        cout << "String to int conversion failed!";
        assert(false);
    }
    totalWords++;
    
    if (msg->msgTxt[position] == "omitted") {
        attachmentCounter(msg, position);
    }
    
    //if the word is not in the map
    if (wordCount.count(msg->msgTxt[position]) == 0) {
        wordCount[msg->msgTxt[position]] = 1;
    } else {
        //add one to the word count
        wordCount[msg->msgTxt[position]] += 1;
    }
    
}

void Person::mapSetter(Message* msg) {
    //maybe get rid of this:
    if (totalWords == 0) {
        startingYear = stoi(msg->year)+2000;
    }
    try {
        currentYear = stoi(msg->year)+2000;
    } catch (invalid_argument) {
        cout << "String to int conversion failed!";
        assert(false);
    }
    
    //setting monthCount
    //if we're still in the same year
    map<string, int> stdmap;
    monthCountVect.push_back(stdmap);
    std::pair<string, int> count;
    count.first = msg->month;
    count.second = 0;
    if ((monthCountVect[currentYear-startingYear].insert(count)).second == true) {
        monthCountVect[currentYear-startingYear][msg->month] = 1;
    } else {
        ///this might be wrong way to access it, don't know
        monthCountVect[currentYear-startingYear][msg->month] += 1;
    }
    
    
    //setting day count. Here I will need to use msg year, month, day to
    // figure out which day of the week it is.
    // TODO: dayCount, also add way to see in a particular year which days were
    // had more messages, probably the same for in a month of a particular year
    // use the algorithm used in birthdays for 183
    string day = determineDayOfWeek(msg->month, msg->day, msg->year);
    if (dayCount.count(day) == 0) {
        dayCount[day] = 1;
    } else {
        dayCount[day] += 1;
    }
    
    //setting yearMonthCount
    if (yearMonthCount.count(currentYear) == 0) {
        yearMonthCount[currentYear] = &monthCountVect[currentYear];
    }
    
    //setting year count
    if (currentYear == 0) {
        currentYear = stoi(msg->year)+2000;
    }
    std::pair<int, int> count2;
    count2.first = currentYear;
    count2.second = 0;
    if ((yearCount.insert(count2)).second == true) {
        yearCount[currentYear] = 1;
    } else {
        ///this might be wrong way to access it, don't know
        yearCount[currentYear] += 1;
    }
}

//counts the amount of gifs, images and audio per message.
//increments the count for the respective person (sender)
//messages and then through the whole vector of strings in a message.
//need to use this to multiply total attachments times 2 and then subtract
//from total words
void Person::attachmentCounter(const Message* msg, const int& position) {
    if (msg->msgTxt.size() != 0 && msg->msgTxt.size() != 1 && position > 0) {
        int prevPos = position - 1;
        if (hasWord(msg->msgTxt[prevPos], "image")) {
            imageCount++;
        }
        if (hasWord(msg->msgTxt[prevPos], "GIF")) {
            gifCount++;
        }
        if (hasWord(msg->msgTxt[prevPos], "audio")) {
            audioCount++;
        }
        if (hasWord(msg->msgTxt[prevPos], "video")) {
            videoCount++;
        }
    }
    
}

Person::Person(string name_in) : totalWords(0), name(name_in), imageCount(0),
gifCount(0), audioCount(0), videoCount(0) { }

Data::~Data() {
    int size = (int)msgVect.size();
    for (int i = 0; i < size; i++) {
        delete msgVect[i];
        msgVect[i] = nullptr;
    }
    
}

Person::~Person(){
    int size = (int)messages.size();
    for (int i = 0; i < size; i++) {
        messages[i] = nullptr;
    }
}

int Data::getTotalWords() {
    return totalWords;
}

int Person::getTotalWords() {
    return totalWords;
}

int Person::getImagesCount() {
    return imageCount;
}

string Person::getName() {
    return name;
}

int Person::getAudioCount() {
    return audioCount;
}

int Person::getGifCount() {
    return gifCount;
}

bool Data::inString(const string& str, const char& c) const {
    bool cond1 = str.find(c) != std::string::npos;
    bool cond2 = str.find('/') != std::string::npos;
    bool cond3 = str.find(',') != std::string::npos;
    return cond1 && cond2 && cond3;
}

string Person::determineDayOfWeek(const string& month,
                                  const string& day, const string& year) const {
    int monthInt = 0;
    int dayInt = 0;
    int yearInt = 0;
    try {
        monthInt = stoi(month);
        dayInt = stoi(day);
        yearInt = stoi(year);
    } catch (invalid_argument) {
        cout << "String to int conversion failed!";
        assert(false);
    }
    yearInt += 2000;
    
    
    //stack overflow answer:
    std::tm time_in = { 0, 0, 0, // second, minute, hour
        dayInt, monthInt-1, yearInt - 1900 }; // 1-based day, 0-based month, year since 1900
    
    std::time_t time_temp = std::mktime(&time_in);
    
    const std::tm * time_out = std::localtime(&time_temp);
    
    int determinedDay = 0;
    //Sunday == 0, Monday == 1
    determinedDay = time_out->tm_wday;

    
    
    string daysOfWeek[] = {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };
    
    return daysOfWeek[determinedDay];
    
}

string Data::dateNormalizer(const string& str) const {
    bool flag = false;
    int pos = 0;
    string normalizedDate = "";
    string test = "";
    for (int i = 0; i < str.size() ; i++) {
        test = str[i];
        if (str[i] == '[') {
            flag = true;
            pos = i;
        }
    }
    if (flag == true) {
        for (int i = pos+1; i <= str.size()-1; i++) {
            
            normalizedDate += str[i];
        }
        return normalizedDate;
    }
    return str;
}


void Data::setStartOfChatDate(const Message* msg) {
    assert(msgVect.size() != 0);
    if (msgVect.size() == 1) {
        string date = msg->month + "/" + msg->day + "/" + msg->year + ";";
        startOfChat = date;
    } else {
        return;
    }
}

bool Person::hasWord(const string& text, const string& word) const {
    int counter = 0;
    bool flag = false;
    for (int i = 0; i < text.size(); i++) {
        if (counter < word.size()) {
            if (text[i] == word[counter]) {
                flag = true;
                counter++;
            }
        }
    }
    return flag;
}


string Data::getStartOfChat() const {
    return startOfChat;
}
