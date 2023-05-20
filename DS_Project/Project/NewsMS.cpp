#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <string>
#include <map>
#include <unordered_map>
#include <iomanip>
#include <numeric>
#include"Admin.h"
#include "Login.h"
#include"News.h"
#include "User.h"
using namespace std;
char Biganswer;


int main() {

    User user;
    Login login;


    cout << "Welcome to News Management System " << endl;
    cout << "1. Register " << endl;
    cout << "2. Login " << endl;

    int choice;
    cin >> choice;
    if (choice == 1) {
        string username, password;
        user.register_user();
        cout << " Log in " << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        login.login(username, password);
    }
    else {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        login.login(username,password);
    }


        return 0;
}
