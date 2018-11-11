#ifndef main_app_hpp
#define main_app_hpp

#include "owner.hpp"
#include "estate.hpp"
#include <utility>
#include <map>
using std::move;
using std::map;
using std::pair;

class MainApp {
private:
    Owner player;
    vector<Owner> npc;
    vector<shared_ptr<RealEstate>> game_estate;
    
public:
    MainApp(Owner player, vector<Owner> npc, vector<shared_ptr<RealEstate>> estate) :
        player(move(player)), npc(move(npc)), game_estate(move(estate)) {}
    void startGameLoop();
    ~MainApp();
private:
    void init();
    void showStatus();
    void showPopup(vector<string> text);
    int showMenu(string title, vector<pair<string, string>> options);
    int nextEvent();
};

#endif /* main_app_hpp */
