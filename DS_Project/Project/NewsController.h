#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include"Admin.h"
#include"Login.h"
#include "User.h"
#include "News.h"
using namespace std;


class NewsController
{
public:
	
	News readNewsFromFile(const string& fileName, const char delimiter, const string& category, unordered_map<string, unordered_map<string, News>>& newshash);

	void add_admin_news(unordered_map<string, unordered_map<string, News>>&newshash);

	void remove(string category, string article_id, unordered_map<string, unordered_map<string, News>>& newshash);

	News Update(string category, string id, unordered_map<string, unordered_map<string, News>>& newshash);

	void read_from_file(string& category);

	News Rate(string category, string id, unordered_map<string, unordered_map<string, News>>& newshash, vector<float>& ratingsVec);

	void avgRate();

	News AddCategory(string category, unordered_map<string, unordered_map<string, News>> & newshash);
	
	void save(unordered_map<string, unordered_map<string, News>>& newshash, const std::string& category);

	void read_user_file(string& username);

	News AddComm(string category, string id, unordered_map<string, unordered_map<string, News>>& newshash);

};

