#include "Admin.h"
#include "News.h"
#include <iostream>
#include <fstream>
#include<sstream>
#include<set>
#include<unordered_set>
#include<map>
#include<string>
#include "User.h"
#include "Login.h"
#include "NewsController.h"
using namespace std;


NewsController newsControll;


void Admin::AddNewCategory(string category, unordered_map<string, unordered_map<string, News>> &newshash) {
    newsControll.AddCategory(category,newshash);
}

void Admin::AverageRate() {
    newsControll.avgRate();
}

