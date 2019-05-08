// Project UID af1f95f547e44c8ea88730dfb185559d

#include "chat.hpp"
#include "chat.cpp"
#include "unit_test_framework.h"
#include <sstream>

using namespace std;


TEST(DataConstructor) {
    string filename = "chatSmall.txt";
    Data data(filename);
    string word;
    ASSERT_TRUE(data.getTotalWords() == 0);
    data.chatFile >> word;
    ASSERT_TRUE(word == "[8/27/17,")
}

TEST(PersonCtor) {
    string filename = "chatSmall.txt";
    Data data(filename);
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
    Data data(filename);
    string word;
    string name1 = "Javier";
    string name2 = "Kumresh Sharma (eecs)";
    Person jogui(name2);
    Person javier(name1);
    data.readMsg(&javier, &jogui);
    
    cout << javier.getTotalWords() << endl;
    cout << javier.messages.size() << endl;
    cout << jogui.getTotalWords() << endl;
    cout << jogui.messages.size() << endl;
    
    for (int i = 0; i < (int)javier.messages.size(); i++) {
        for (int j = 0; j < (javier.messages[i])->msgTxt.size(); j++) {
            cout << javier.messages[i]->msgTxt[j] << endl;
        }
    }
    cout << "Javier YearCount: " << endl;
    cout << javier.yearCount << endl;
    
    cout << "Kumresh YearCount: " << endl;
    cout << jogui.yearCount << endl;
    
    cout << "Javier wordCount: " << endl;
    cout << javier.wordCount << endl;
    
    cout << "Kumresh wordCount: " << endl;
    cout << jogui.wordCount << endl;
    
    cout << "Javier dayCount" << endl;
    cout << javier.dayCount << endl;
    
    cout << "Kumresh dayCount" << endl;
    cout << jogui.dayCount << endl;
}


TEST(readMsgs2) {
    string filename = "chatVerySmall.txt";
    Data data(filename);
    string word;
    string name1 = "Javier";
    string name2 = "Jogui";
    Person jogui(name2);
    Person javier(name1);
    data.readMsg(&javier, &jogui);
    
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
    
    cout << "Javier wordCount: " << endl;
    cout << javier.wordCount << endl;
    
    cout << "Jogui wordCount: " << endl;
    cout << jogui.wordCount << endl;
    
    cout << "Javier dayCount" << endl;
    cout << javier.dayCount << endl;
    
    cout << "Jogui dayCount" << endl;
    cout << jogui.dayCount << endl;
}


TEST(inString) {
    string filename = "chatVerySmall.txt";
    Data data(filename);
    const string str = "‎[3/23/19,";
    const char c = '[';
    ASSERT_TRUE(data.inString(str, c));
}

TEST(datermineDay) {
    string filename = "chatVerySmall.txt";
    Data data(filename);
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

TEST(bigTest) {
    
    string filename = "theChatFinal.txt";
    Data data(filename);
    string word;
    string name1 = "Javier";
    string name2 = "Mech";
    Person mech(name2);
    Person javier(name1);
    data.readMsg(&javier, &mech);
    
    cout << "Javier Words " << javier.getTotalWords() << endl;
    cout << "Javier Messages " <<javier.messages.size() << endl;
    cout << "Mech Words " <<mech.getTotalWords() << endl;
    cout << "Mech Messages " <<mech.messages.size() << endl;
    
    //    for (int i = 0; i < (int)javier.messages.size(); i++) {
    //        for (int j = 0; j < (javier.messages[i])->msgTxt.size(); j++) {
    //            cout << javier.messages[i]->msgTxt[j] << endl;
    //        }
    //    }
    cout << "Javier YearCount: " << endl;
    cout << javier.yearCount << endl;
    
    cout << "Mech YearCount: " << endl;
    cout << mech.yearCount << endl;
    
//    cout << "Javier wordCount: " << endl;
//    cout << javier.wordCount << endl;
//
//    cout << "Jogui wordCount: " << endl;
//    cout << jogui.wordCount << endl;
    
    cout << "Javier dayCount" << endl;
    cout << javier.dayCount << endl;
    
    cout << "Mech dayCount" << endl;
    cout << mech.dayCount << endl;
    
}

//TEST(emoji) {
//    cout << "\U0001F917\U0001F917\U0001F917";
//
//
//}
TEST_MAIN() // Do NOT put a semicolon here

