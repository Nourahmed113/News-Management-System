#include <string>
#include <iostream>
#include <cstring>
#include <unordered_map>
#include <fstream>
#include <vector>
#include "Admin.h"
#include "Login.h"
#include"News.h"
#include "User.h"
#include "NewsController.h"
using namespace std;

NewsController newsCont;


void User::register_user()
{

    cout << "WELCOME NEW USER" << endl;
    cout << "Enter a username: ";
    cin >> username;

    // Check if the entered username already exists in the file
    ifstream file("user_credentials.txt");
    string line;
    bool username_taken = false;
    while (getline(file, line)) {
        size_t pos = line.find(",");
        if (pos != string::npos) {
            string file_username = line.substr(0, pos);
            if (username == file_username) {
                username_taken = true;
                break;
            }
        }
    }
    file.close();

    if (username_taken == true) {
        cout << "Username already taken. Please choose a different username." << endl;
        register_user();
        return;
    }

    cout << "Enter a password: ";
    cin >> password;

    // Save the new user's credentials to the file
    ofstream file_out("user_credentials.txt", ios::app); // ios::app opens the file in append mode
    if (file_out.is_open()) {
        file_out << username << "," << password << "\n";
        file_out.close();
        cout << "Registration successful" << endl;
    }
    else {
        cout << "Error: Unable to save user credentials to file." << endl;
    }
}

void User::login_user(string username,string password)
{
    // Check the user's credentials against those in the file
    ifstream file("user_credentials.txt");
    string line;
    bool credentials_found = false;
    while (getline(file, line)) {
        size_t pos = line.find(",");
        if (pos != string::npos) {
            string file_username = line.substr(0, pos);
            string file_password = line.substr(pos + 1);
            if (username == file_username && password == file_password) {
                credentials_found = true;
                break;
            }
        }
    }
    file.close();
    if (credentials_found) {
        cout << "Login successful." << endl;
    }
    else {
        cout << "Invalid username or password. Please try again." << endl;
        exit(0);
    }

}

void User::RateArticle(string category, string id, unordered_map<string, unordered_map<string, News>>& newshash, vector<float>& ratingsVec) {
    newsCont.Rate(category, id, newshash, ratingsVec);
}

void User::AddComments(string category, string id, unordered_map<string, unordered_map<string, News>>& newshash) {
    newsCont.AddComm(category, id, newshash);
}


void User:: save_user_behavior(const unordered_map<string, string>& user_credentials, unordered_map<string, unordered_map<string, News>>& newshash,string &username) {
   
    ofstream outfile(username + ".txt", ios::app);
    if (outfile.is_open()) {

        outfile << "User : " << username << endl;

            for (const auto& i : newshash) {
                
                for (const auto& item : i.second) {
                    outfile << "Article ID: " << item.second.article_id << endl;
                    outfile << "Headline: " << item.second.headline << endl;
                    outfile << "User rating: " << item.second.rate << endl;
                    outfile << "User Comments: " << item.second.comment << endl;
                    // save other relevant information about the user's behavior
                    outfile << endl;
                }
            }
            outfile << endl;

            outfile.close();
            cout << "User behavior saved to file." << endl;
        
    }
    else {
        cout << "Unable to save user behavior to file." << endl;
    }
}

void User::save_behavior(const unordered_map<string, string>& user_credentials, unordered_map<string, unordered_map<string, News>>& newshash, string& username) {

    ofstream outfile("user_behaviour.txt", ios::app);
    if (outfile.is_open()) {

        outfile << "User : " << username << endl;

        for (const auto& i : newshash) {

            for (const auto& item : i.second) {
                outfile << "Article ID: " << item.second.article_id << endl;
                outfile << "Headline: " << item.second.headline << endl;
                outfile << "User rating: " << item.second.rate << endl;
                outfile << "User Comments: " << item.second.comment << endl;
                // save other relevant information about the user's behavior
                outfile << endl;
            }
        }
        outfile << endl;

        outfile.close();
        cout << "User behavior saved to file." << endl;

    }
    else {
        cout << "Unable to save user behavior to file." << endl;
    }
}


void User:: removeArticleForUser(string& category, string& id, string& username, unordered_map<string, unordered_map<string, News>>& newshash, vector<float>& ratingsVec)
{
    
    bool removed = false;
    for (int i = 0; i < ratingsVec.size(); ++i) {
        const News& news = newshash[category][id];
        if (news.rate <= 2.0 ) {
            ratingsVec.erase(ratingsVec.begin() + i);
            removed = true;
            break;
        }
    }
    if (removed) {
        newshash[category].erase(id);
        std::cout << "Article " << id << " removed for user " << username << std::endl;
    }
    else {
        std::cout << "User " << username << " did not rate article " << id << " less than 2.0" << std::endl;
    }
}



