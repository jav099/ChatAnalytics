//
//  statistics.hpp
//  ChatAnalytics
//
//  Created by Javier Contreras on 5/16/19.
//  Copyright © 2019 Javier Contreras. All rights reserved.
//

#ifndef statistics_hpp
#define statistics_hpp

#include <stdio.h>
#include "chat.hpp"
#include <cmath>
#include <string>
#include <map>
#include <set>
#include <ctime>
#include <iomanip>
#include <sstream>



class Stats {
public:
    
    Stats(Data* chat_in);
    //pair will contain the time and the unit of time (hours or minutes)
    std::pair<double,string> getAvgResponseTime() const;
    std::pair<double,string> getAvgNewMessage() const;
    double getDurationInDays() const;
   // add version of this func since a particular date.
    void computeAvgResponseTime();
    double hoursBetweenMessages(Message* m1, Message* m2) const;
    void newMessageSentEvery();
    double hoursToMinutes(double& hours) const;
    
    pair<string, double> comparisons() const;
    
    //move this to private after testing
    Data* chat;
    
    std::map<string, int> compMap;
private:
    double durationInDays;
    std::pair<double, string> avgResponseTime;
    std::pair<double, string> newMsgEvery;
    double computeDaysInBetween(Message* start, Message* end);
    
    struct Date {
        int month = 0;
        int day = 0;
        int year = 0;
        int sec = 0;
        int min = 0;
        int hour = 0;
    };
    struct Time {
        //0-59
        int sec = 0;
        //0-59
        int min = 0;
        //0-23
        int hour = 0;
    };
    //must receive in format M/D/YY
    Date convertToDate(Message* msg) const;
    Time convertToTime(Message* msg) const;
    
    
};




#endif /* statistics_hpp */
