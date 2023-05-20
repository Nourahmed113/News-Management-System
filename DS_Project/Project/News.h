#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include"Admin.h"
#include"Login.h"
#include "User.h"
using namespace std;

struct Date {
    string year;
    string month;
    string day;
};


class News {


public:
    string article_id;
    string category;
    string headline;
    string author;
    Date Date;
    string body;
    float rate=0.0;
    string comment;


    void readNewsFromFile(const string& fileName, const char delimiter, const string& category, unordered_map<string, unordered_map<string, News>>& newshash);

    void add_news(unordered_map<string, unordered_map<string, News>>& newshash);

    void remove_news(string category, string article_id, unordered_map<string, unordered_map<string, News>>& newshash);

    void UpdateNews(string category, string id, unordered_map<string, unordered_map<string, News>>& newshash);

    void read_file(string& category);

    void saved_map(unordered_map<string, unordered_map<string, News>>& newshash, const std::string& category);

    bool comparebyDate(const std::pair<std::string, News>& a, const std::pair<std::string, News>& b)const;

    void displayLatestNews(unordered_map<string, unordered_map<string, News>>& newshash, int numnews);
    
    
};
    
