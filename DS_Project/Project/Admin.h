#pragma once
using namespace std;
#include "NewsController.h"
#include <string>
#include "News.h"
#include <unordered_map>
#ifndef NEWS_H
#define NEWS_H
#include "User.h"
#include "Login.h"



;  class Admin {

public:

        unordered_map<string, unordered_map<string, News>> newshash;

        
        void AddNewCategory(string category, unordered_map<string, unordered_map<string, News>> &newshah);

        void AverageRate();
};

#endif



