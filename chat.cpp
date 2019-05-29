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



Data::Data(string& filename, string& p1, string& p2) : totalWords(0), imageCount(0), gifCount(0)
, audioCount(0), videoCount(0), startOfChat(""){
    chatFile.open(filename);
    if (!chatFile.is_open()) {
        cout << "error opening file";
        assert(false);
    }
    person1 = new Person(p1);
    person2 = new Person(p2);
    forTests = false;
}

Data::Data(string& filename, Person* p1, Person* p2, bool test) : totalWords(0), imageCount(0), gifCount(0)
, audioCount(0), videoCount(0), startOfChat(""){
    chatFile.open(filename);
    if (!chatFile.is_open()) {
        cout << "error opening file";
        assert(false);
    }
    person1 = p1;
    person2 = p2;
    forTests = test;
}

Data::Data(string& filename, bool test) : totalWords(0), imageCount(0), gifCount(0)
, audioCount(0), videoCount(0), startOfChat(""){
    chatFile.open(filename);
    if (!chatFile.is_open()) {
        cout << "error opening file";
        assert(false);
    }
    forTests = test;
}
//Counts the frequency of each word by calling Javier's and Mech's
// respective functions which do all the adding of pairs into the
// maps
void Data::dataGatherer() {
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
            if (msgCount > 1) {
                if (msgVect[msgCount - 2]->sender != msgVect[msgCount - 1]->sender) {
                    responseVect.push_back(msg);
                }
            }
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
    person1->computeTotalWords();
    person2->computeTotalWords();
    totalWords = person1->getTotalWords() + person2->getTotalWords();
    imageCount = person1->getImagesCount() + person2->getImagesCount();
    gifCount = person1->gifCount + person2->gifCount;
    audioCount = person1->audioCount + person2->audioCount;
    videoCount = person1->videoCount + person2->videoCount;
    
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
    msg->date = msg->month + "/" + msg->day + "/" + msg->year;
    getline(chatFile, msg->time, ']');
    getline(chatFile, msg->sender, ':');
    string correctName = msg->sender;
    correctName.erase(std::remove_if(correctName.begin(),
                                     correctName.end(), ::isspace), correctName.end());
    msg->sender = correctName;
    if (uniqueDayWithMessageCount.count(msg->date) == 0) {
        uniqueDayWithMessageCount[msg->date] = 1;
    } else {
        uniqueDayWithMessageCount[msg->date] += 1;
    }
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
    if (monthCount.count(stoi(msg->month)) == 0) {
        monthCount[stoi(msg->month)] = 1;
    } else {
        monthCount[stoi(msg->month)] += 1;
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
    //if we're still in the same year
//    map<string, int> stdmap;
//    monthCountVect.push_back(stdmap);
//    std::pair<string, int> count;
//    count.first = msg->month;
//    count.second = 0;
//    
//    if ((monthCountVect[currentYear-startingYear].count(msg->month) == 0)) {
//        monthCountVect[currentYear-startingYear][msg->month] = 1;
//    } else {
//        monthCountVect[currentYear-startingYear][msg->month] += 1;
//    }
//    if (yearMonthCount.count(currentYear) == 0) {
//        yearMonthCount[currentYear] = monthCountVect[currentYear-startingYear];
//    }
    
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
            totalAtchments++;
        }
        if (hasWord(msg->msgTxt[prevPos], "GIF")) {
            gifCount++;
            totalAtchments++;
        }
        if (hasWord(msg->msgTxt[prevPos], "audio")) {
            audioCount++;
            totalAtchments++;
        }
        if (hasWord(msg->msgTxt[prevPos], "video")) {
            videoCount++;
            totalAtchments++;
        }
    }
    
}

Person::Person(string name_in) : totalWords(0), name(name_in), imageCount(0),
gifCount(0), audioCount(0), videoCount(0), startingYear(0), currentYear(0), totalAtchments(0) { }

Data::~Data() {
    int size = (int)msgVect.size();
    for (int i = 0; i < size; i++) {
        delete msgVect[i];
        msgVect[i] = nullptr;
    }
    if (!forTests) {
        delete person1;
        delete person2;
    }
}

Person::~Person(){
    int size = (int)messages.size();
    for (int i = 0; i < size; i++) {
        messages[i] = nullptr;
    }
    delete retVect;
}

int Data::getTotalWords() const {
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

int Person::getTotalAttchments() const {
    return totalAtchments;
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
        string date = msg->month + "/" + msg->day + "/" + msg->year;
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
            } else {
                flag = false;
            }
        }
    }
    return flag;
}


string Data::getStartOfChat() const {
    return startOfChat;
}

int Data::getUniqueDaysWithMessage() const {
    return (int)uniqueDayWithMessageCount.size();
}

std::pair<string, int> Data::getDateWithMostMessages() const {
    int currentMax = 0;
    std::pair<string, int>  maxPair;
    for (auto &kv : uniqueDayWithMessageCount) {
        if (kv.second > currentMax) {
            currentMax = kv.second;
            maxPair.first = kv.first;
            maxPair.second = currentMax;
        }
    }
    return maxPair;
}

std::pair<string, int> Person::getWordWIthHighestCount(map<string,int>& exc) const {
    int currentMax = 0;
    bool notFoundInVect = true;
    std::pair<string, int>  maxPair;
    for (auto &kv : wordCount) {
        if (exc.count(kv.first) == 0) {
            notFoundInVect = true;
        } else {
            notFoundInVect = false;
        }
        if (kv.second > currentMax && notFoundInVect) {
            currentMax = kv.second;
            maxPair.first = kv.first;
            maxPair.second = currentMax;
        }
    }
    return maxPair;
}

std::pair<string, int> Person::getWordWIthHighestCount() const {
    int currentMax = 0;
    std::pair<string, int>  maxPair;
    for (auto &kv : wordCount) {
        if (kv.second > currentMax) {
            currentMax = kv.second;
            maxPair.first = kv.first;
            maxPair.second = currentMax;
        }
    }
    return maxPair;
}


void Person::computeTotalWords() {
    totalWords -= (totalAtchments * 2);
}

int Person::getMsgCount() const {
    return (int)messages.size();
}

int Data::getImageCount() const {
    return imageCount;
}

int Data::getGifCount() const {
    return gifCount;
}

int Data::getTotalMessages() const {
    return (int)msgVect.size();
}

int Data::getAudioCount() const {
    return audioCount;
}

int Data::getVideoCount() const {
    return videoCount;
}

int Person::firstMsgAtDate(const std::pair<string,bool>& date) const {
    for (int i = 0; i < (int)messages.size(); i++) {
        if (date.second) {
            if (messages[i]->date == date.first) {
                return i;
            }
        } else {
            if (messages[i]->year == date.first) {
                return i;
            }
        }
    }
    return -1;
}

int Data::firstMsgAtDate(const std::pair<string,bool>& date) const {
    for (int i = 0; i < (int)msgVect.size(); i++) {
        if (date.second) {
            if (msgVect[i]->date == date.first) {
                return i;
            }
        } else {
            if (msgVect[i]->year == date.first) {
                return i;
            }
        }
    }
    return -1;
}

int Person::getCountOfWord(const string& word) const {
    auto it = wordCount.find(word);
    if (it != wordCount.end()) {
        return it->second;
    } else {
        return 0;
    }
}

int Data::countOfWord(const string& word) const {
    int count = 0;
    auto itP1 = person1->wordCount.find(word);
    if (itP1 != person1->wordCount.end()) {
        count += itP1->second;
    }
    auto itP2 = person2->wordCount.find(word);
    if (itP2 != person2->wordCount.end()) {
        count += itP2->second;
    }
    return count;
}


string Data::getEndOfChat() const {
    string date = msgVect[(int)msgVect.size() - 1]->date;
    return date;
}

vector<pair<string, int>>* Person::top20Words(bool exeptions) {
    map<string,int> wordCountCopy = wordCount;
    vector<pair<string, int>>* vect = new vector<pair<string, int>>;
    bool notFoundInVect = true;
    if (exeptions) {
        for (int i = 0; i < 20; i++) {
            int max = 0;
            pair<string, int> maxPair;
            for (auto &it : wordCountCopy) {
                if (it.second > max) {
                    if (exept.count(it.first) == 0) {
                        notFoundInVect = true;
                    } else {
                        notFoundInVect = false;
                    }
                    if (notFoundInVect) {
                        max = it.second;
                        maxPair = it;
                    }
                }
            }
            wordCountCopy.erase(maxPair.first);
            (*vect).push_back(maxPair);
        }
    } else {
        wordCount.erase("omitted");
        for (int i = 0; i < 20; i++) {
            pair<string, int> maxPair;
            int max = 0;
            for (auto it : wordCount) {
                 if (it.second > max) {
                     max = it.second;
                     maxPair = it;
                 }
            }
            wordCount.erase(maxPair.first);
            (*vect).push_back(maxPair);
        }
    }
    retVect = vect;
    return vect;
}
