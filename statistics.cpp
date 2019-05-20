//
//  statistics.cpp
//  ChatAnalytics
//
//  Created by Javier Contreras on 5/16/19.
//  Copyright © 2019 Javier Contreras. All rights reserved.
//

#include "statistics.hpp"


using namespace std;

Stats::Stats(Data* chat_in) : avgResponseTime(0.0), durationInDays(0) {
    chat = chat_in;
    compMap.insert({"A Game Of Thrones",292727});
    compMap.insert({"The Bible", 783137});
    compMap.insert({"The Hunger Games", 99750});
    compMap.insert({"Harry Potter Series", 1084170});
    string date1 = "";
    string date2 = "";
    date1 = chat->startOfChat;
    date2 = chat->getEndOfChat();
    durationInDays = computeDaysInBetween(chat->msgVect[0], chat->msgVect[chat->getTotalMessages()-1]);
}

double Stats::computeDaysInBetween(Message* start, Message* end) {
    string startDate = start->date;
    string endDate = end->date;
    Stats::Date dateStart = convertToDate(start);
    Stats::Date dateEnd = convertToDate(end);
    struct std::tm tm = {0,0,0,dateStart.day,dateStart.month,dateStart.year};
    struct std::tm tm2 = {0,0,0,dateEnd.day,dateEnd.month,dateEnd.year};
    time_t time1 = mktime(&tm);
    time_t time2 = mktime(&tm2);
    string date1 = asctime(&tm);
    string date2 = asctime(&tm2);
    
    double timeInBetweenSeconds = difftime(time2, time1);
    
    double timeInDays = timeInBetweenSeconds / 86400;
    
    return timeInDays;
}

double Stats::getDurationInDays() const {
    return durationInDays;
}


Stats::Date Stats::convertToDate(Message* msg) const {
    string date = msg->date;
    string month = "";
    string day = "";
    string year = "";
    int monthInt;
    int dayInt;
    int yearInt;
    int i = 0;
    while (date[i] != '/') {
        month += date[i];
        i++;
    }
    i++;
    while (date[i] != '/') {
        day += date[i];
        i++;
    }
    i++;
    while (i < date.size()) {
        year += date[i];
        i++;
    }
    Stats::Date dateStruct;
    try {
        monthInt = stoi(month);
        dayInt = stoi(day);
        yearInt = stoi(year);
    } catch (invalid_argument) {
        cout << "String to int conversion failed!";
        assert(false);
    }
    dateStruct.month = monthInt - 1;
    dateStruct.day = dayInt;
    dateStruct.year = yearInt + 100;
    
    Stats::Time tm = convertToTime(msg);
    dateStruct.hour = tm.hour;
    dateStruct.min = tm.min;
    dateStruct.sec = tm.sec;
    
    return dateStruct;
    
}

Stats::Time Stats::convertToTime(Message* msg) const {
    string time = msg->time;
    int secInt = 0;
    int minInt = 0;
    int hrInt = 0;
    string sec = "";
    string min = "";
    string hr = "";
    int i = 0;
    while (time[i] != ':') {
        hr += time[i];
        i++;
    }
    i++;
    while (time[i] != ':') {
        min += time[i];
        i++;
    }
    i++;
    while (time[i] != ' ') {
        sec += time[i];
        i++;
    }
    try {
        hrInt = stoi(hr);
        minInt = stoi(min);
        secInt = stoi(sec);
    } catch (invalid_argument) {
        cout << "String to int conversion failed!";
        assert(false);
    }
    if (time[time.size() - 2] == 'P') {
        hrInt += 12;
    }
    Stats::Time tm;
    tm.hour = hrInt;
    tm.min = minInt;
    tm.sec = secInt;
    
    return tm;
    
}

double Stats::hoursBetweenMessages(Message* m1, Message* m2) const {
    string startDate = m1->date;
    string endDate = m2->date;
    Stats::Date dateStart = convertToDate(m1);
    Stats::Date dateEnd = convertToDate(m2);
    struct std::tm tm =
    {dateStart.sec,dateStart.min,dateStart.hour,dateStart.day,dateStart.month,dateStart.year};
    struct std::tm tm2 =
    {dateEnd.sec,dateEnd.min,dateEnd.hour,dateEnd.day,dateEnd.month,dateEnd.year};
    time_t time1 = mktime(&tm);
    time_t time2 = mktime(&tm2);
    string date1 = asctime(&tm);
    string date2 = asctime(&tm2);
    
    double timeInBetweenSeconds = difftime(time2, time1);
    double hours = timeInBetweenSeconds / (60*60);
    
    return hours;
}

void Stats::computeAvgResponseTime() {
    double avg = 0;
    for (int i = 1; i < (int)chat->msgVect.size(); i++) {
        avg += hoursBetweenMessages(chat->msgVect[i - 1], chat->msgVect[i]);
    }
    
    avg /= chat->getTotalMessages();
    avgResponseTime = avg;
    
}

double Stats::getAvgResponseTime() const {
    return avgResponseTime;
}



//double Stats::timeBetweenMessages(Message *m1, Message *m2) const {
//    
//    
//}



