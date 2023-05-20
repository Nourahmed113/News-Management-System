#include "NewsController.h"
#include "Admin.h"
#include <iostream>
#include <fstream>
#include<sstream>
#include<set>
#include<unordered_set>
#include <algorithm>
#include<map>
#include "News.h"
#include<string>
#include "User.h"
#include "Login.h"
using namespace std;

News news;
string id;

News NewsController::readNewsFromFile(const string& fileName, const char delimiter, const string& category, unordered_map<string, unordered_map<string, News>>& newshash) {
    ifstream inFile(fileName);
    News news;

    if (inFile.is_open()) {
        std::getline(inFile, news.article_id, delimiter);
        std::getline(inFile, news.category, delimiter);
        std::getline(inFile, news.headline, delimiter);
        std::getline(inFile, news.author, delimiter);
        std::getline(inFile, news.Date.day, delimiter);
        std::getline(inFile, news.Date.month, delimiter);
        std::getline(inFile, news.Date.year, delimiter);
        std::getline(inFile, news.body, delimiter);
        (inFile, news.rate, delimiter);
        std::getline(inFile, news.comment, '\0');

        inFile.close();
    }
    newshash[category][news.article_id] = news;
    return news;
}


void NewsController::add_admin_news(unordered_map<string, unordered_map<string, News>>&newshash) {
    cout << "Enter category: ";

    cin >> news.category;

    cout << "Enter news ID: ";
    cin.ignore();
    std::getline(cin, news.article_id);

    cout << "Enter headline: ";
    std::getline(cin, news.headline);

    cout << "Enter author name: ";
    std::getline(cin, news.author);

    cout << "Enter date day: ";
    std::getline(cin, news.Date.day);

    cout << "Enter date month: ";
    std::getline(cin, news.Date.month);

    cout << "Enter date year: ";
    std::getline(cin, news.Date.year);

    cout << "Enter news body: ";
    std::getline(cin, news.body);

    if (newshash.find(news.category) == newshash.end()) {
        newshash[news.category] = unordered_map<string, News>();
    }

    News news_content = { news.article_id,news.category,news.headline, news.author, news.Date.day ,news.Date.month,news.Date.year , news.body };
    newshash[news.category][news.article_id] = news_content;

    cout << "News added successfully!" << endl;

}


void NewsController::remove(string category, string article_id, unordered_map<string, unordered_map<string, News>>& newshash) {
    newshash[category].erase(article_id);
    if (newshash[category].empty()) {
        newshash.erase(category);
    }
}


News NewsController::Update(string category, string id, unordered_map<string, unordered_map<string, News>>& newshash) {
    cout << "choose which part to update: " << endl;
    cout << "1.body " << endl;
    cout << "2.headline " << endl;
    cout << "3.author " << endl;
    
    int ch;
    cin >> ch;
    switch(ch) {

    case 1: {
        string updated_body;
        cout << "Enter the updated body of the news article:" << endl;
        cin.ignore();
        std::getline(cin, updated_body);


        newshash[category][id].body = updated_body;
        cout << "News article with ID " << id << " in category " << category << " has been updated." << endl;
        cout << endl;

        break;
    }
    case 2: {
        string updated_headline;
        cout << "Enter the updated headline of the news article:" << endl;
        cin.ignore();
        std::getline(cin, updated_headline);


        newshash[category][id].headline = updated_headline;
        cout << "News article with ID " << id << " in category " << category << " has been updated." << endl;
        cout << endl;

        break;
    }
    case 3: {
        string updated_author;
        cout << "Enter the updated author of the news article:" << endl;
        cin.ignore();
        std:: getline(cin, updated_author);

        newshash[category][id].author = updated_author;
        cout << "News article with ID " << id << " in category " << category << " has been updated." << endl;
        cout << endl;

        break;
    }
          default:{
                    cout << "Invalid choice." << endl;
          }
   }
    return newshash[category][id];
}


void NewsController::read_from_file(string &category)
{
    std::ifstream file(category + ".txt");
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            // Display or process the line
            std::cout << line << std::endl;
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file: " << category << ".txt" << std::endl;
    }
}

void NewsController::read_user_file(string& username)
{
    std::ifstream file(username + ".txt");
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            // Display or process the line
            std::cout << line << std::endl;
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file: " << username << ".txt" << std::endl;
    }
}



News NewsController::Rate(string category, string id, unordered_map<string, unordered_map<string, News>>& newshash, vector<float> &ratingsVec) {

    double rating;
    cout << "Enter the rating of the news article:" << endl;
    cin >> rating;

    newshash[category][id].rate = rating;
    ratingsVec.push_back(rating);

    return newshash[category][id];
}


void NewsController::avgRate() {
    std::ifstream infile("user_behaviour.txt");
    if (infile.is_open()) {
        std::vector<std::string> search_strings = { "User :", "Article ID:", "User rating:" };
        std::string line;
        std::map<int, std::vector<double>> article_ratings;

        while (std::getline(infile, line)) {
            bool found = false;
            int article_id;
            double rating;

            for (const auto& str : search_strings) {
                if (line.find(str) != std::string::npos) {
                    found = true;
                    cout << endl;

                    if (str == "Article ID:") {
                        article_id = std::stoi(line.substr(line.find(":") + 2));
                    }
                    else if (str == "User rating:") {
                        rating = std::stod(line.substr(line.find(":") + 2));
                        article_ratings[article_id].push_back(rating);
                    }

                    break;
                }
            }

            if (found) {
                std::cout << line << std::endl;
            }
        }

        infile.close();

        for (const auto& pair : article_ratings) {
            int id = pair.first;
            const std::vector<double>& ratings = pair.second;
            double sum_ratings = 0.0;
            double count_ratings = 0.0;
            for (double r : ratings) {
                if (r != 0.0) {
                    sum_ratings += r;
                    count_ratings++;
                }
            }
            if (count_ratings != 0.0) {
                double avg_rating = static_cast<double>(sum_ratings) / count_ratings;
                cout << "----------------------------------------" << endl;
                std::cout << "Article " << id << ": " << avg_rating << std::endl;

            }
        }
    }
}



News NewsController::AddCategory(string category,  unordered_map<string, unordered_map<string, News>> & newshash) {

    ofstream outFile(category + ".txt");

    cout << "Enter news ID: ";
    cin >> news.article_id;

    cout << "Enter headline: ";
    cin.ignore();
    std:: getline(cin, news.headline);

    cout << "Enter author name: ";
    std:: getline(cin, news.author);

    cout << "Enter date day: ";
    std:: getline(cin, news.Date.day);

    cout << "Enter date month: ";
    std::getline(cin, news.Date.month);

    cout << "Enter date year: ";
    std::getline(cin, news.Date.year);

    cout << "Enter news body: ";
    std:: getline(cin, news.body);


   
    outFile << "Article ID: " << news.article_id << endl;
    outFile << "Headline: " << news.headline << endl;
    outFile << "Author: " << news.author << endl;
    outFile << "Date: " << news.Date.day << "/" << news.Date.month << "/" << news.Date.year << endl;
    outFile << "Body: " << news.body << endl;

    

    if (newshash.find(category) == newshash.end()) {
        newshash[category] = unordered_map<string, News>();
    }

    News news_content = { news.article_id,category,news.headline, news.author, news.Date.day ,news.Date.month, news.Date.year , news.body };
   
    newshash[category][news.article_id] = news_content;


    
    return news_content;
}

void NewsController::save(unordered_map<string, unordered_map<string, News>>& newshash, const std::string& category) {
   
    ofstream outFile(category + ".txt");
    if (outFile.is_open()) {
        for (const auto& i : newshash) {
            for (const auto& item : i.second) {
                outFile << "Category :" << item.second.category << endl;
                outFile << "Article ID :" << item.second.article_id << endl;
                outFile << "Headline: " << item.second.headline << endl;
                outFile << "Author: " << item.second.author << endl;
                outFile << "Date: " << item.second.Date.day << '/' << item.second.Date.month << '/' << item.second.Date.year << endl;
                outFile << "Body: " << item.second.body << endl;
                outFile << "Rate: " << item.second.rate << endl;
                outFile << "Comment: " << item.second.comment << endl;
               
            }
        }
      
        outFile.close();
    }
}

News NewsController::AddComm(string category, string id, unordered_map<string, unordered_map<string, News>>& newshash) {

    string comment;
    cout << "Enter you comment :" << endl;
    cin.ignore();
    std::getline(cin, comment);

    newshash[category][id].comment = comment;
    cout << "News article with ID " << id << " in category " << category << " has been updated." << endl;
    cout << endl;

    return newshash[category][id];
}
