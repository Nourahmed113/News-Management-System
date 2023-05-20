#include "Admin.h"
#include "News.h"
#include <iostream>
#include <fstream>
#include<algorithm>
#include<vector>
#include<sstream>
#include<set>
#include<unordered_set>
#include<map>
#include<string>
#include "User.h"
#include "Login.h"
#include "NewsController.h"
using namespace std;


NewsController newsController;

void News::readNewsFromFile(const string& fileName, const char delimiter, const string& category, unordered_map<string, unordered_map<string, News>>& newshash) {
    newsController.readNewsFromFile(fileName, delimiter, category,newshash);
}


void News::add_news(unordered_map<string, unordered_map<string, News>>& newshash) {
    newsController.add_admin_news(newshash);
  
}

void News::UpdateNews(string category, string id, unordered_map<string, unordered_map<string, News>>& newshash) {
    newsController.Update(category,id,newshash);
}



void News::remove_news(string category, string article_id, unordered_map<string, unordered_map<string, News>>& newshash) {
    newsController.remove(category,article_id,newshash);
}


void News::saved_map(unordered_map<string, unordered_map<string, News>>& newshash, const std::string& category) {

    newsController.save(newshash,category);
}

bool News::comparebyDate(const pair<string, News>& a, const pair<string, News>& b) const
{
   if (a.second.Date.year != b.second.Date.year) {
        return a.second.Date.year > b.second.Date.year;
    }
    else if (a.second.Date.month != b.second.Date.month) {
        return a.second.Date.month > b.second.Date.month;
    }
    else {
        return a.second.Date.day > b.second.Date.day;
    }
   
}

void News::read_file(string& category)
{
    newsController.read_from_file(category);
}


void News:: displayLatestNews(unordered_map<string, unordered_map<string, News>>& newshash, int numnews) {
    // Sort the news items by date
    vector<std:: pair<std:: string, News>> sortedNewsVector;

    for (auto& categoryEntry : newshash) {
        for (auto& newsEntry : categoryEntry.second) {
            sortedNewsVector.push_back(make_pair(newsEntry.first, newsEntry.second));
        }
    }

   //std:: sort(sortedNewsVector.begin(), sortedNewsVector.end(), comparebyDate);
    std::sort(sortedNewsVector.begin(), sortedNewsVector.end(), [](const std::pair<std::string, News>& a, const std::pair<std::string, News>& b) {
        return a.second.comparebyDate(a, b);
        });

  
    // Display the latest news items
    cout << endl;
    cout << "Latest News:" << endl;
    cout << endl;

    for (int i = 0; i < numnews && i < sortedNewsVector.size(); i++) {
        const News& newsItem = sortedNewsVector[i].second;
        cout << "Id: " << newsItem.article_id << endl;
        cout << "Category: " << newsItem.category << endl;
        cout << "Headline: " << newsItem.headline << endl;
        cout << "Author: " << newsItem.author << endl;
        cout << "Body: " << newsItem.body << endl;
        cout << "Date: " << newsItem.Date.day << "/" << newsItem.Date.month << "/" << newsItem.Date.year << endl;
        cout << "Rate: " << newsItem.rate << endl;
        cout << "Comment: " << newsItem.comment << endl;
        cout << endl;
    }

}


