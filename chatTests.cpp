

#include "chat.hpp"
#include "chat.cpp"
#include "unit_test_framework.h"
#include <sstream>

using namespace std;


TEST(DataConstructor) {
    string filename = "chatSmall.txt";
    Data data(filename,true);
    string word;
    ASSERT_TRUE(data.getTotalWords() == 0);
    data.chatFile >> word;
    ASSERT_TRUE(word == "[8/27/17,")
}

TEST(PersonCtor) {
    string filename = "chatSmall.txt";
    Data data(filename,true);
    string word;
    string name1 = "Javier";
    string name2 = "Luis";
    Person luis(name2);
    Person javier(name1);
    
    ASSERT_EQUAL(name1, javier.getName());
    ASSERT_EQUAL(name2, luis.getName())
    ASSERT_EQUAL(0, luis.getAudioCount())
    ASSERT_EQUAL(0, javier.getAudioCount());
    ASSERT_EQUAL(0, luis.getGifCount())
    ASSERT_EQUAL(0, javier.getGifCount());
    ASSERT_EQUAL(0, luis.getImagesCount())
    ASSERT_EQUAL(0, javier.getImagesCount());
}

TEST(readMsgsCompile) {
    string filename = "verySmall.txt";
    string name1 = "Javier";
    string name2 = "Kumresh Sharma (eecs)";
    Person jogui(name2);
    Person javier(name1);
    Data data(filename,&javier,&jogui, true);
    string word;
    
    data.readMsg();
    
    cout << javier.getTotalWords() << endl;
    cout << javier.messages.size() << endl;
    cout << jogui.getTotalWords() << endl;
    cout << jogui.messages.size() << endl;
    
//    for (int i = 0; i < (int)javier.messages.size(); i++) {
//        for (int j = 0; j < (javier.messages[i])->msgTxt.size(); j++) {
//            cout << javier.messages[i]->msgTxt[j] << endl;
//        }
//    }
    cout << "Javier YearCount: " << endl;
    cout << javier.yearCount << endl;
    
    cout << "Kumresh YearCount: " << endl;
    cout << jogui.yearCount << endl;
    
//    cout << "Javier wordCount: " << endl;
//    cout << javier.wordCount << endl;
//
//    cout << "Kumresh wordCount: " << endl;
//    cout << jogui.wordCount << endl;
//
    cout << "Javier dayCount" << endl;
    cout << javier.dayCount << endl;
    
    cout << "Kumresh dayCount" << endl;
    cout << jogui.dayCount << endl;
}


TEST(readMsgs2) {
    string filename = "chatVerySmall.txt";
    string name1 = "Javier";
    string name2 = "Jogui";
    Person jogui(name2);
    Person javier(name1);
    Data data(filename,&javier,&jogui, true);
    string word;
    
    data.readMsg();
    
    cout << "Javier Words " << javier.getTotalWords() << endl;
    cout << "Javier Messages " <<javier.messages.size() << endl;
    cout << "Jogui Words " <<jogui.getTotalWords() << endl;
    cout << "Jogui Messages " <<jogui.messages.size() << endl;
    
    //    for (int i = 0; i < (int)javier.messages.size(); i++) {
    //        for (int j = 0; j < (javier.messages[i])->msgTxt.size(); j++) {
    //            cout << javier.messages[i]->msgTxt[j] << endl;
    //        }
    //    }
    cout << "Javier YearCount: " << endl;
    cout << javier.yearCount << endl;
    
    cout << "Jogui YearCount: " << endl;
    cout << jogui.yearCount << endl;
    
//    cout << "Javier wordCount: " << endl;
//    cout << javier.wordCount << endl;
//
//    cout << "Jogui wordCount: " << endl;
//    cout << jogui.wordCount << endl;
    
    cout << "Javier dayCount" << endl;
    cout << javier.dayCount << endl;
    
    cout << "Jogui dayCount" << endl;
    cout << jogui.dayCount << endl;
}


TEST(inString) {
    string filename = "chatVerySmall.txt";
    Data data(filename,true);
    const string str = "‎[3/23/19,";
    const char c = '[';
    ASSERT_TRUE(data.inString(str, c));
}

TEST(datermineDay) {
    string filename = "chatVerySmall.txt";
    Data data(filename, true);
    string name1 = "Javier";
    string name2 = "Jogui";
    Person jogui(name2);
    Person javier(name1);
    string month = "3";
    string day = "15";
    string year = "19";
    string day2 = javier.determineDayOfWeek(month, day, year);
    
    ASSERT_TRUE(day2 == "Friday");
    
}

TEST(AAAhasWord) {
    string name1 = "Javier";
    Person javier(name1);
    string text = "U00000008audio";
    ASSERT_TRUE(javier.hasWord(text, "audio"));
    text = "U00000008image";
    ASSERT_TRUE(javier.hasWord(text, "image"));
    text = "U00000008GIF";
    ASSERT_TRUE(javier.hasWord(text, "GIF"));
    text = "U00000008video";
    ASSERT_TRUE(javier.hasWord(text, "video"));
    text = "U00000008image";
    ASSERT_TRUE(!javier.hasWord(text, "audio"));
}

TEST(setStartDate1) {
    string filename = "chatVerySmall.txt";
    string name1 = "Javier";
    string name2 = "Jogui";
    Person jogui(name2);
    Person javier(name1);
    Data data(filename, &javier, &jogui, true);
    string word;
   
    data.readMsg();
    
    cout << data.getStartOfChat();
    
}


TEST(setStartDate2) {
    string filename = "verySmall.txt";
    string name1 = "Javier";
    string name2 = "Kumresh Sharma (eecs)";
    Person jogui(name2);
    Person javier(name1);
    Data data(filename, &javier, &jogui, true);
    string word;
   
    data.readMsg();
    
    cout << data.getStartOfChat();
    
}

TEST(monthMaps) {
    string filename = "chatVerySmall.txt";
    string name1 = "Javier";
    string name2 = "Jogui";
    Person jogui(name2);
    Person javier(name1);
    Data data(filename, &javier, &jogui, true);
    
    string word;
    
    data.readMsg();
    
    cout << "javier MonthCount: " << endl;
    cout << javier.monthCount;
    cout << endl;
    cout << "jogui yearMonthCount: " << endl;
    cout << jogui.monthCount;
    cout << endl;
    
}

//TEST(AAAnestedMaps) {
//    string filename = "chatVerySmall.txt";
//    Data data(filename);
//    string word;
//    string name1 = "Javier";
//    string name2 = "Jogui";
//    Person jogui(name2);
//    Person javier(name1);
//    data.readMsg(&javier, &jogui);
//
//    cout << "javier yearMonthCount: " << endl;
//    cout << javier.yearMonthCount;
//    cout << endl;
//    cout << "jogui yearMonthCount: " << endl;
//    cout << jogui.yearMonthCount;
//    cout << endl;
//
//}
//
//
//

////////

TEST(bigTest) {

    string filename = "theChatFinal.txt";
    string name1 = "Javier";
    string name2 = "Mech";
    Person mech(name2);
    Person javier(name1);
    Data data(filename, &javier, &mech, true);
    string word;
    
    data.readMsg();
    
//    for (auto kv : mech.wordCount) {
//        if (kv.first == "love") {
//            cout << kv.first << ":" << kv.second <<  endl;
//        }
//    }

    cout << "Javier Words " << javier.getTotalWords() << endl;
    cout << "Javier Messages " << javier.messages.size() << endl;
    cout << "Mech Words " << mech.getTotalWords() << endl;
    cout << "Mech Messages " << mech.messages.size() << endl;

    cout << "Javier YearCount: " << endl;
    cout << javier.yearCount << endl;

    cout << "Mech YearCount: " << endl;
    cout << mech.yearCount << endl;


    cout << "Javier dayCount" << endl;
    cout << javier.dayCount << endl;

    cout << "Mech dayCount" << endl;
    cout << mech.dayCount << endl;

    cout << "javier MonthCount: " << endl;
    cout << javier.monthCount;
    cout << endl;
    cout << "mech MonthCount: " << endl;
    cout << mech.monthCount;
    cout << endl;

    cout << "javier getAttcCount: " << endl;
    cout << javier.getTotalAttchments();
    cout << endl;
    cout << "mech attchCount: " << endl;
    cout << mech.getTotalAttchments();
    cout << endl;
    cout << "javier images: " << endl;
    cout << javier.getImagesCount();
    cout << endl;
    cout << "mech imagesCount: " << endl;
    cout << mech.getImagesCount();
    cout << endl;
    cout << "javier getGifCount: " << endl;
    cout << javier.getGifCount();
    cout << endl;
    cout << "mech getGifCount: " << endl;
    cout << mech.getGifCount();
    cout << endl;
    cout << "javier audioCount: " << endl;
    cout << javier.getAudioCount();
    cout << endl;
    cout << "mech audioCount: " << endl;
    cout << mech.getAudioCount();
    cout << endl;

    cout << "day with the most messages: " << endl;
    std::pair<string, int> max = data.getDateWithMostMessages();
    cout << max.first << " : " << max.second << endl;

    cout << "days with messages: " << endl;
    cout << data.getUniqueDaysWithMessage() << endl;

    std::pair<string,int> max2 = mech.getWordWIthHighestCount();
    cout << "Mech Most used words: " << max2.first << " : " << max2.second << endl;
    max2 = javier.getWordWIthHighestCount();
    cout << "javier Most used words: " << max2.first << " : " << max2.second << endl;
//}
//
//TEST(AttchmentsAndDateWithMostMessages) {
//    string filename = "chatVerySmall.txt";
//    Data data(filename);
//    string word;
//    string name1 = "Javier";
//    string name2 = "Jogui";
//    Person jogui(name2);
//    Person javier(name1);
//    data.readMsg(&javier, &jogui);
//
//    cout << "javier getAttcCount: " << endl;
//    cout << javier.getTotalAttchments();
//    cout << endl;
//    cout << "jogui attchCount: " << endl;
//    cout << jogui.getTotalAttchments();
//    cout << endl;
//    cout << "javier images: " << endl;
//    cout << javier.getImagesCount();
//    cout << endl;
//    cout << "jogui imagesCount: " << endl;
//    cout << jogui.getImagesCount();
//    cout << endl;
//    cout << "javier getGifCount: " << endl;
//    cout << javier.getGifCount();
//    cout << endl;
//    cout << "jogui getGifCount: " << endl;
//    cout << jogui.getGifCount();
//    cout << endl;
//    cout << "javier audioCount: " << endl;
//    cout << javier.getAudioCount();
//    cout << endl;
//    cout << "jogui audioCount: " << endl;
//    cout << jogui.getAudioCount();
//    cout << endl;
//
//    cout << "day with the most messages: " << endl;
//    std::pair<string, int> max = data.getDateWithMostMessages();
//    cout << max.first << " : " << max.second << endl;
//
//    cout << "days with messages: " << endl;
//    cout << data.getUniqueDaysWithMessage() << endl;
    
    
}

//TODO: test firstMsgAtDate, getWordWithHighestCount and getCountOfWord



//TEST(emoji) {
//    cout << "\U0001F917\U0001F917\U0001F917";
//
//
//}
TEST_MAIN() // Do NOT put a semicolon here

