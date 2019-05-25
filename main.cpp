//
//  main.cpp
//  ChatAnalytics
//
//  Created by Javier Contreras on 5/4/19.
//  Copyright © 2019 Javier Contreras. All rights reserved.
//

#include <iostream>
#include "chat.cpp"
#include "statistics.cpp"


using namespace std;
int main(int argc, char* argv[]) {
    //will receive as arguments:
    //1. filename
    //2. Name1;
    //3. Name2;
    
    string filename = "chatVerySmall.txt";
    string name1 = "Javier";
    string name2 = "Jogui";
    Data data(filename, name1, name2);
    string word;
    
    data.dataGatherer();
    Data* dataPtr = &data;
    Stats stats(dataPtr);
    stats.computeAvgResponseTime();
    stats.newMessageSentEvery();
    
    
    std::pair<double, string> avg = stats.getAvgResponseTime();
    std::pair<double, string> newMsgEvery = stats.getAvgNewMessage();
    cout << "The duration of the chat since the first message was of:" << endl;
    cout << stats.getDurationInDays() << " days" << endl << endl;
    cout << "A total of " << data.getTotalMessages() << " messages were sent" << endl;
    
    cout << "The average response time was of: ";
    cout << avg.first << " " << avg.second << endl;
    cout << "On average, a new message was sent every " << newMsgEvery.first << " " << newMsgEvery.second << endl << endl;
    cout << name1 << " sent a total of " << data.person1->getTotalWords() << " words" << endl;
    cout << name2 << " sent a total of " << data.person2->getTotalWords() << " words" << endl;
    
    
    
    cout << "Frequency for each month: " << endl;
    cout << name1 << ":" << endl;
    cout << data.person1->monthCount;
    cout << endl;
    cout << name2 << ":" << endl;
    cout << data.person2->monthCount;
    
    
}
