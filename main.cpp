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
    {"audio","de","la","que","el","en","y","a","los","se","del","las","un","por","con",
        "una","su","para","es","al","lo","como","más","o","pero","sus","le","ha",
        "Me","sin","sobre","este","ya","cuando","todo","ser","son","dos","fue",
        "también","había","era","muy","hasta","desde","mi","porque","que","qué",
        "solo","sólo","han","hay","vez","puede","todos","asi","así","nos","ni",
        "parte","tiene","él","uno","donde","bien","te","the","be","to","of","and",
        "a","in","that","have","I","this","but","his","by","from","they","say","so",
        "if","eso","omitted","Pero","No","Si","Y","esta","O","eso","\U0000200eimage"
        ,"it","is","sea","Que","for","Es","A","GIF","audio","Ya","está","Como",
        "gif","La","my","Yo","on","Audio","\U0000200eaudio","\U0000200eGIF","Mas",
        "Esta","El","ver","ma","me",
    };
    ofstream out("csvData.txt");
    string filename = "gChatOld.txt";
    string name1 = "Javier";
    string name2 = "Geo";
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
    data.person1->wordCount.erase("omitted");
    data.person2->wordCount.erase("omitted");
    data.person2->wordCount.erase("audio");
    data.person2->wordCount.erase("image");
    data.person2->wordCount.erase("GIF");
    data.person2->wordCount.erase("\U0000200eaudio");
    data.person1->wordCount.erase("\U0000200eaudio");
    std::pair<double, string> avg = stats.getAvgResponseTime();
    std::pair<double, string> newMsgEvery = stats.getAvgNewMessage();
    
    for (int i = 0; i < exceptions.size(); i++) {
        string word = exceptions[i];
        data.person1->exept[word];
        data.person2->exept[word];
    }
    
    vector<pair<string, int>>* vectPtr1Ex = data.person1->top20Words(true);
    vector<pair<string, int>>* vectPtr2Ex = data.person2->top20Words(true);
    vector<pair<string, int>>* vectPtr1NoEx = data.person1->top20Words(false);
    vector<pair<string, int>>* vectPtr2NoEx = data.person2->top20Words(false);
    
    
    out << name1 << ":" << endl;
    out << "month,messages" << endl;
    out << data.person1->monthCount;
    
    out << "%%%%" << endl;
    
    out << name2 << ":" << endl;
    out << "month,messages" << endl;
    out << data.person2->monthCount;
    
    out << "%%%%" << endl;
    
    out << name1 << ":" << endl;
    out << "day,messages" << endl;
    out << data.person1->dayCount;
    
    out << "%%%%" << endl;
    
    out << name2 << ":" << endl;
    out << "day,messages" << endl;
    out << data.person2->dayCount;
    
    out << "%%%%" << endl;
    
    out << name1 << ":" << endl;
    out << "year,messages" << endl;
    out << data.person1->yearCount;
    
    out << "%%%%" << endl;
    
    out << name2 << ":" << endl;
    out << "year,messages" << endl;
    out << data.person2->yearCount;
    
    out << "%%%%" << endl;
    
    out << name1 << ":" << endl;
    out << "word,count" << endl;
    out << vectPtr1Ex;
    
    out << "%%%%" << endl;
    
    out << name2 << ":" << endl;
    out << "word,count" << endl;
    out << vectPtr2Ex;
    
    out << "%%%%" << endl;
    
    out << name1 << ":" << endl;
    out << "word,count" << endl;
    out << vectPtr1NoEx;
    
    out << "%%%%" << endl;
    
    out << name2 << ":" << endl;
    out << "word,count" << endl;
    out << vectPtr2NoEx;
    
    out << "%%%%" << endl;
    
    out << "**********" << endl;
    
    out << "Chat duration: " << endl;
    out << stats.getDurationInDays() << " days" << endl;
    out << "Messages sent:  " << endl;
    out << data.getTotalMessages() << endl;
    std::vector<pair<string, double>> avgWords = data.getAvgWordsPerMessage();
    for (int i = 0; i < 2; i++) {
        out << avgWords[i].first << " average words per message:" << endl;
        out << avgWords[i].second << endl;
    }
    
    out << "The average response time was of: " << endl;
    out << avg.first << " " << avg.second << endl;
    out << "On average, a new message was sent every " << endl;
    out << newMsgEvery.first << " " << newMsgEvery.second << endl;
    out << name1 << " sent a total of: " << endl;
    out << data.person1->getTotalWords() << " words" << endl;
    out << name2 << " sent a total of: " << endl;
    out << data.person2->getTotalWords() << " words" << endl;
    out << name1 << " sent a total of: " << endl;
    out << data.person1->getAudioCount() << " voice messages" << endl;
    out << name2 << " sent a total of: " << endl;
    out << data.person2->getAudioCount()<< " voice messages" << endl;
    out << name1 << " sent a total of: " << endl;
    out << data.person1->getTotalAttchments() << " attachments" << endl;
    out << name2 << " sent a total of: " << endl;
    out << data.person2->getTotalAttchments() << " attachments" << endl;
    
    out << "Days with at least one message:" << endl;
    out << data.getUniqueDaysWithMessage() << endl;
    
    
    
    out << "Comparison for your chat (word count)" << endl;
    out << stats.comparisons().second << " of " << stats.comparisons().first << endl;
    
    
    
    
    
    
    
    
    
}


