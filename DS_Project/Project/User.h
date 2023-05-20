#pragma once
using namespace std;
#include <unordered_map>
#include <string>
#include <cstring>
#include<vector>
#include "News.h"
#include"Admin.h"
#include "Login.h"
#include "NewsController.h"
#ifndef FILENAME_H
#define FILENAME_H


; class News;

class User
{
	public:
		std::string username, password;
		// Global variable to store user credentials
		std::unordered_map<std::string, std::string> user_credentials;
	
		void register_user();

		void login_user(std:: string username , std:: string password);

		
		void RateArticle(std:: string category, std:: string id, unordered_map<string, unordered_map<string, News>>& newshash, vector<float>& ratingsVec);

		void removeArticleForUser(std:: string& category, std:: string& id, string& username, unordered_map<string, unordered_map<string, News>>& newshash, vector<float>& ratingsVec);

		void AddComments(std:: string category, string id, unordered_map<string, unordered_map<string, News>>& newshash);

		void save_user_behavior(const unordered_map<string, string>& user_credentials, unordered_map<string, unordered_map<string, News>>& newshash,string& username);

		void save_behavior(const unordered_map<string, string>& user_credentials, unordered_map<string, unordered_map<string, News>>& newshash, string& username);

};

#endif
