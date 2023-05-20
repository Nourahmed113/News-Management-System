#ifndef LOGIN_H
#define LOGIN_H
#include"Admin.h"
#include "User.h"
#include"User.h"
#include <string>

class Login {
public:
    Login();

    bool login(std::string username, std::string password);
    
private:
    std::string username;
    std::string password;
};

#endif
