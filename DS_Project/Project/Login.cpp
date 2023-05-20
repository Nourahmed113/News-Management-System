#include "Login.h"
#include "Admin.h"
#include"News.h"
#include "NewsController.h"
#include <iostream>
#include <string>
#include<unordered_map>
using namespace std;


struct Category {

    string name;
    string path;
    
};


Category categories[] = {

    {"Business", "Business001.txt"},
    {"Business", "Business009.txt"},
    {"Business", "002.txt"},
    {"Business", "004.txt"},
    {"Business", "054.txt"},
    {"Entertainment", "entertainment001.txt"},
    {"Entertainment", "entertainment002.txt"},
    {"Entertainment", "entertainment003.txt"},
    {"Entertainment", "entertainment004.txt"},
    {"Entertainment", "entertainment005.txt"},
    {"Politics","politics001.txt"},
    {"Politics","politics002.txt"},
    {"Politics","politics003.txt"},
    {"Politics","politics004.txt"},
    {"Politics","politics005.txt"},
    {"Sport","sport501.txt"},
    {"Sport","sport502.txt"},
    {"Sport","sport503.txt"},
    {"Sport","sport504.txt"},
    {"Sport","sport505.txt"},
    {"Tech","tech387.txt"},
    {"Tech","tech390.txt"},
    {"Tech","tech392.txt"},
    {"Tech","tech393.txt"},
    {"Tech","tech394.txt"}
};


int num_categories = sizeof(categories) / sizeof(Category);


Login::Login() : username("Nour"), password("123456") {}
unordered_map<string, unordered_map<string, News>> newshash;
vector<float> ratingsVec;
std::unordered_map<std::string, std::string> user_credentials;
unordered_map<string, unordered_map<string, vector<string>>> comments;



bool Login::login(string username, string password) {

    News news;
    string category;

        for (int i = 0; i < num_categories; i++) {
            if (categories[i].name == category) {
                news.readNewsFromFile(categories[i].path, '/', category,newshash);
            }
        }
        NewsController newsCont;
        Admin admin;
        User user;
        char answer;
        string cat;
        while (true) {

            if (this->username == username && this->password == password) {
                std::cout << "Login successful!" << endl;
                std::cout << "Welcome back Nour !" << endl;
                while (true) {
                    // display the menu options
                    std::cout << "Choose an option:" << endl;
                    std::cout << "1. View News in a specific category" << endl;
                    std::cout << "2. Update News" << endl;
                    std::cout << "3. Post News in an existing category" << endl;
                    std::cout << "4. Remove News" << endl;
                    std::cout << "5. Add new category and assign news to them" << endl;
                    std::cout << "6. Display Average Rate of articles" << endl;
                    std::cout << "7. Exit" << endl;

                    int choice;
                    cin >> choice;

                    switch (choice) {
                    // display a specific category
                    case 1: {

                        cout << "Enter a category: " << endl;
                        cin.ignore();
                        getline(std::cin, category);
                        cout << endl;
                        cout << endl;


                        for (int i = 0; i < num_categories; i++) {
                            if (categories[i].name == category) {
                                news.readNewsFromFile(categories[i].path, '/', category, newshash);

                            }
                        }
                        news.displayLatestNews(newshash, 5);
                        news.saved_map(newshash, category);
                        break;
                
                    }
                    // update 
                    case 2: {
                        cout << "Enter the category of the news article to update" << endl;
                        cin >> category;
                        cout << "Enter the article id of the news article to update " << endl;
                        cin >> news.article_id;
                        news.UpdateNews(category, news.article_id,newshash);
                        news.displayLatestNews(newshash, 5);
                        news.saved_map(newshash,category);
                        cout << endl;
                        cout << endl;
                        break;
                    }
                          // post news 
                    case 3: {
                        cout << "Add news as an admin" << endl;
                        do {
                            news.add_news(newshash);
                            cout << endl;
                      
                            std::cout << "Do you want add another article ? (Y/N) " << endl;
                            std::cin >> answer;

                        } while (answer == 'Y' || answer == 'y');
                        news.saved_map(newshash,category);
                        break;
                    }
                          //remove news
                    case 4: {
                        cout << endl;

                        cout << "Enter the category you want to remove" << endl;

                        cin >> cat;
                        cout << "Enter article id you want to remove from " << cat << " category" << endl;
                        cin >> news.article_id;
                        news.remove_news(cat, news.article_id,newshash);
                        cout << "Articles after removing" << endl;
                        news.displayLatestNews(newshash, 5);
                        news.saved_map(newshash,category);
                        break;
                    }
                          // add new category and assign news to them
                    case 5: {
                        cout << "Add category" << endl;
                        do {
                            cin >> cat;
                            admin.AddNewCategory(cat,newshash);
                            cout << "Do you want to continue ? " << endl;
                            cin >> answer;
                        } while (answer == 'Y' || answer == 'y');
                        news.displayLatestNews(newshash, 5);
                        news.saved_map(newshash,category);
                        break;
                    }
                   
                    // display average rate
                    case 6: {
                        admin.AverageRate();
                        break;
                    }
                    case 7: {
                        exit(0);
                        break;
                    }
                    default:
                        cout << "Invalid choice." << endl;
                    }
                }
                return true;
                  
            }
            else {
                user.login_user(username, password);
                cout << endl;
                cout << "Welcome back " << username << " ! " << endl;
                cout << endl;
                while (true) {

                    int c;
                    cout << "1. View Your Previous Changes " << endl;
                    cout << "2. View Latest News " << endl;
                    cout << "3. Type the Name of the Category you want to preview " << endl;
                    cout << "4. Exit" << endl;
                    cin >> c;
                    switch (c) {
                        case 1: {
                            cout << endl;
                            newsCont.read_user_file(username);
                            break;
                        }
                        case 2: {
                            string ct;
                            cout << "Enter Category" << endl;
                            cin >> ct;
                            for (int i = 0; i < num_categories; i++) {
                                if (categories[i].name == ct) {
                                    news.readNewsFromFile(categories[i].path, '/', ct, newshash);
                                }
                            }
                            cout << endl;
                            news.displayLatestNews(newshash, 5);
                            break;
                        }

              
                         case 3: {
                             cout << "Business" << endl;
                             cout << "Politics" << endl;
                             cout << "Entertainment" << endl;
                             cout << "Sport" << endl;
                             cout << "Tech " << endl;
                             cout << endl;

                             cin.ignore();
                             getline(std::cin, category);

                             for (int i = 0; i < num_categories; i++) {
                                 if (categories[i].name == category) {
                                     news.readNewsFromFile(categories[i].path, '/', category, newshash);

                                 }
                             }
                             cout << endl;
                             cout << endl;
                             cout << "latest news in " << category << "  category: " << endl;
                             news.read_file(category);
                             break;
                         }
                         case 4: {
                             exit(0);
                             break;
                         }
                    }
               
                    cout << endl;
                    cout << endl;
                    cout << "If you want to rate an article Press 1 " << endl;
                    cout << "If you want to add a comment on an article Press 2 " << endl;
                    cout << "To mark an article as spam Press 3 " << endl;
                    cout << "If you want to choose your preferred categories Press 4 " << endl;

                    int userChoice;
                    cin >> userChoice;
                    if (userChoice == 1) {
                        do {
                            cout << "Enter the category of the article you want to rate" << endl;
                            cin >> category;
                            cout << "Enter the ID of the article you want to rate" << endl;
                            cin >> news.article_id;
                            user.RateArticle(category, news.article_id, newshash, ratingsVec);

                            cout << endl;
                            cout << "Do you want to add any other rating ?" << endl;
                            cin >> answer;

                        } while (answer == 'y' || answer == 'Y');


                        news.saved_map(newshash, category);
                        user.removeArticleForUser(category, news.article_id, username, newshash, ratingsVec);
                        user.save_user_behavior(user_credentials, newshash, username);
                        user.save_behavior(user_credentials, newshash, username);
                        cout << endl;

                        news.displayLatestNews(newshash, 5);

                    }
                    else if (userChoice == 2) {
                        do {

                            cout << "Enter the category of the article you want to comment" << endl;
                            cin >> category;
                            cout << "Enter the ID of the article you want to comment" << endl;
                            cin >> news.article_id;
                            user.AddComments(category, news.article_id, newshash);
                            cout << endl;
                            cout << "Do you want to add any other comment ?" << endl;
                            cin >> answer;

                        } while (answer == 'y' || answer == 'Y');

                        news.saved_map(newshash, category);
                        news.displayLatestNews(newshash, 5);
                        user.save_user_behavior(user_credentials, newshash, username);
                    }
                    else if (userChoice == 3) {

                        do {
                            std::cout << "Enter the category of the article you want to mark as spam" << endl;
                            std::cin >> category;
                            std::cout << "Enter the ID of the article you want to mark as spam" << endl;
                            std::cin >> news.article_id;
                            news.remove_news(category, news.article_id, newshash);
                            news.displayLatestNews(newshash, 5);
                            user.save_user_behavior(user_credentials, newshash, username);

                            cout << endl;
                            cout << "Do you want to add any other rating ?" << endl;
                            cin >> answer;

                        } while (answer == 'y' || answer == 'Y');
                    }
                    else if (userChoice == 4) {
                        string c1, c2, c3;
                        cout << "choose your most preferred 3 categories " << endl;
                        cin >> c1;
                        cin >> c2;
                        cin >> c3;
                        cout << "your preferred categories are: " << c1 << "and " << c2 << "and " << c3 << endl;
                    }

                    break;
                }
  
            }
        }
}

