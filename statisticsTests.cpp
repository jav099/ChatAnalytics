//
//  statisticsTests.cpp
//  ChatAnalytics
//
//  Created by Javier Contreras on 5/16/19.
//  Copyright © 2019 Javier Contreras. All rights reserved.
//

#include <stdio.h>
#include "statistics.hpp"
#include "statistics.cpp"
#include "unit_test_framework.h"
#include <sstream>
#include "chat.hpp"
#include "chat.cpp"

using namespace std;

TEST(ctor) {
    string filename = "chatVerySmall.txt";
    string name1 = "Javier";
    string name2 = "Jogui";
    Person jogui(name2);
    Person javier(name1);
    Data data(filename, &javier, &jogui, true);
    data.readMsg();
    Data* dataPtr = &data;
    Stats stats(dataPtr);
    
    cout << stats.getDurationInDays() << endl;
}

TEST(getHoursBetweenMessages) {
    string filename = "chatVerySmall.txt";
    string name1 = "Javier";
    string name2 = "Jogui";
    Person jogui(name2);
    Person javier(name1);
    Data data(filename, &javier, &jogui, true);
    data.readMsg();
    Data* dataPtr = &data;
    Stats stats(dataPtr);
    int hours = stats.hoursBetweenMessages(data.msgVect[3], data.msgVect[4]);
    
    ASSERT_EQUAL(0, hours);

}

TEST(getAvgResponseTime) {
    string filename = "chatVerySmall.txt";
    string name1 = "Javier";
    string name2 = "Jogui";
    Person jogui(name2);
    Person javier(name1);
    Data data(filename, &javier, &jogui, true);
    data.readMsg();
    Data* dataPtr = &data;
    Stats stats(dataPtr);
    stats.computeAvgResponseTime();
    std::pair<double, string> avg = stats.getAvgResponseTime();
    
    cout << avg.first << " " << avg.second << endl;
    
}

TEST(getAvgResponseTimeBig) {
    string filename = "theChatFinal.txt";
    string name1 = "Javier";
    string name2 = "Mech";
    Person jogui(name2);
    Person javier(name1);
    Data data(filename, &javier, &jogui, true);
    data.readMsg();
    Data* dataPtr = &data;
    Stats stats(dataPtr);
    stats.computeAvgResponseTime();
    std::pair<double, string> avg = stats.getAvgResponseTime();
    std::pair<double, string> newMsgEvery = stats.newMessageSentEvery();

    cout << avg.first << " " << avg.second << endl;
    cout << "message was sent every " << newMsgEvery.first << " " << newMsgEvery.second << endl;
    
    
}

TEST_MAIN()
