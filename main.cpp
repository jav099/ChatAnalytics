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
#include <fstream>


ostream& operator<<(ostream& os, vector<pair<string, int>>* vectPtr) {
    for (int i = 0; i < vectPtr->size(); i++) {
        os << ((*vectPtr)[i]).first << "," << ((*vectPtr)[i]).second << endl;
    }
    return os;
}

using namespace std;
int main(int argc, char* argv[]) {
    //will receive as arguments:
    //1. filename
    //2. Name1;
    //3. Name2;
    
    vector<string> exceptions =
    {"de","la","que","el","en","y","a","los","se","del","las","un","por","con",
    "una","su","para","es","al","lo","como","más","o","pero","sus","le","ha",
    "Me","sin","sobre","este","ya","cuando","todo","ser","son","dos","fue",
    "también","había","era","muy","hasta","desde","mi","porque","que","qué",
    "solo","sólo","han","hay","vez","puede","todos","asi","así","nos","ni",
    "parte","tiene","él","uno","donde","bien","te","the","be","to","of","and",
    "a","in","that","have","I","this","but","his","by","from","they","say","so",
    "if","eso","omitted","Pero","No","Si","Y","esta","O","eso","\U0000200eimage"
        ,"it","is","sea","Que","for","Es","A","GIF","audio","Ya","está","Como",
        "gif","La","my","Yo","on"
    };
    ofstream out("csvData.txt");
    string filename = "theChatFinal.txt";
    string name1 = "Javier";
    string name2 = "Mech";
    Data data(filename, name1, name2);
    string word;
    
    data.dataGatherer();
    Data* dataPtr = &data;
    Stats stats(dataPtr);
    stats.computeAvgResponseTime();
    stats.newMessageSentEvery();
    
    data.person1->wordCount.erase("audio");
    data.person1->wordCount.erase("image");
    data.person1->wordCount.erase("GIF");
    data.person2->wordCount.erase("audio");
    data.person2->wordCount.erase("image");
    data.person2->wordCount.erase("GIF");
    std::pair<double, string> avg = stats.getAvgResponseTime();
    std::pair<double, string> newMsgEvery = stats.getAvgNewMessage();
    cout << "Chat duration: " << endl;
    cout << stats.getDurationInDays() << " days" << endl;
    cout << "Messages sent:  " << endl;
    cout << data.getTotalMessages() << endl;
    cout << "The average response time was of: " << endl;
    cout << avg.first << " " << avg.second << endl;
    cout << "On average, a new message was sent every " << endl;
    cout << newMsgEvery.first << " " << newMsgEvery.second << endl;
    cout << name1 << " sent a total of: " << endl;
    cout << data.person1->getTotalWords() << " words" << endl;
    cout << name2 << " sent a total of: " << endl;
    cout << data.person2->getTotalWords() << " words" << endl;
    cout << name1 << " sent a total of: " << endl;
    cout << data.person1->getAudioCount() << " voice messages" << endl;
    cout << name2 << " sent a total of: " << endl;
    cout << data.person2->getAudioCount()<< " voice messages" << endl;
    cout << name1 << " sent a total of: " << endl;
    cout << data.person1->getTotalAttchments() << " attachments" << endl;
    cout << name2 << " sent a total of: " << endl;
    cout << data.person2->getTotalAttchments() << " attachments" << endl;
    
    cout << "Days with at least one message:" << endl;
    cout << data.getUniqueDaysWithMessage() << endl;
    for (int i = 0; i < exceptions.size(); i++) {
        const string word = exceptions[i];
        data.person1->exept[word];
        data.person2->exept[word];
    }
    
    vector<pair<string, int>>* vectPtr1Ex = data.person1->top20Words(true);
    vector<pair<string, int>>* vectPtr2Ex = data.person2->top20Words(true);

    
    out << name1 << ":" << endl;
    out << "month,messages" << endl;
    out << data.person1->monthCount << endl;
    
    out << name2 << ":" << endl;
    out << "month,messages" << endl;
    out << data.person2->monthCount << endl;
    
    out << name1 << ":" << endl;
    out << "day,messages" << endl;
    out << data.person1->dayCount << endl;
    
    out << name2 << ":" << endl;
    out << "day,messages" << endl;
    out << data.person2->dayCount << endl;
    
    out << name1 << ":" << endl;
    out << "year,messages" << endl;
    out << data.person1->yearCount << endl;
    
    out << name2 << ":" << endl;
    out << "year,messages" << endl;
    out << data.person2->yearCount << endl;
    
    out << name1 << ":" << endl;
    out << "word,count" << endl;
    out << vectPtr1Ex << endl;
    
    out << name2 << ":" << endl;
    out << "word,count" << endl;
    out << vectPtr2Ex << endl;
    
    
    
    cout << "Comparison for your chat (word count)" << endl;
    cout << stats.comparisons().second << " of " << stats.comparisons().first << endl;
    
    
    
}


