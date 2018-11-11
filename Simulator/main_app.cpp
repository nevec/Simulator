#include "main_app.hpp"
#include "config.hpp"
#include <ncurses.h>
#include <algorithm>
#include <chrono>
#include <sstream>
using namespace std::chrono;
using namespace std;

void MainApp::startGameLoop()
{
    init();
    showStatus();
    
    while (true) {
        int choice = showMenu("Enter command: ", {
            {"p", "Print my estate"},
            {"e", "Buy estate"},
            {"t", "Buy titushkas"},
            {"b", "Bykanyt'"},
            {"q", "Quit"}
        });
        if (choice == 4)
            return;
        if (choice == 0) {
            vector<string> text;
            int k = 1;
            
            if (player.getEstate().empty()) {
                text.push_back("You haven\'t any estate");
            } else {
                ostringstream buffer;
                for (auto e: player.getEstate()) {
                    buffer.str("");
                    buffer << k << ": " << e->getName();
                    text.push_back(buffer.str());
                    buffer.str("");
                    buffer << "\tprofit: " << e->getProfit() << " price: " << e->getPrice();
                    text.push_back(buffer.str());
                    ++k;
                }
            }
            showPopup(text);
        }
        if (choice == 1) {
            int k = 0, i = 0;
            vector<pair<string, string>> opts;
            map<int, int> indices;
            ostringstream buffer;
            
            for (auto e: game_estate) {
                if (e->getOwner() == &player) {
                    i++;
                    continue;
                }
                buffer.str("");
                buffer << e->getName() << " price: " << e->getPrice() << " owner: ";
                if (e->getOwner() == nullptr)
                    buffer << "none";
                else
                    buffer << e->getOwner()->getName();
                opts.emplace_back(to_string(k+1), buffer.str());
                indices.insert({k, i});
                k++;
                i++;
            }
            opts.emplace_back("b", "Go back");
            int choice = showMenu("Available estate", opts);
            if (choice == opts.size()-1)
                continue;
            try {
                player.buyEstate(game_estate[indices[choice]]);
                showPopup({"Success!"});
            } catch(const exception& e) {
                showPopup({e.what()});
            }
        }
        if (choice == 2) {
            string title = "Titushka price = " + to_string(TitushkaPrice);
            while (true) {
                
                int choice = showMenu(title, {
                    {"1", "Buy 1 titushku"},
                    {"2", "Buy 10 titushkas"},
                    {"b", "Go back"}
                });
                if (choice == 2) {
                    break;
                } else {
                    try {
                        player.buyTitushkas((choice == 0)?1:10);
                        showPopup({"Success!"});
                    } catch(const exception& e) {
                        showPopup({e.what()});
                    }
                }
            }
        }
        if (choice == 3) {
            vector<pair<string, string>> opts;
            int i = 0;
            for (auto o: npc) {
                opts.emplace_back(to_string(i+1), o.getName());
                i++;
            }
            opts.emplace_back("b", "Go back");
            int target = showMenu("Owners:", opts);
            if (target < npc.size()) {
                
                player.doRacket(npc[target]);
            }
        }
    }
}

void MainApp::init()
{
    initscr();
    cbreak();
    keypad(stdscr, true);
    noecho();
    halfdelay(1);
    curs_set(0);
}

void MainApp::showStatus()
{
    move(0, 0);
    clrtoeol();
    mvprintw(0, 0, "%d $, titushki: %d", player.getBalance(), player.getTitushkas());
    refresh();
}

void MainApp::showPopup(vector<string> text)
{
    clear();
    showStatus();
    for (int i=0;i<(int)text.size();++i) {
        mvprintw(2+i, 0, "%s", text[i].c_str());
    }
    refresh();
    while (nextEvent() == ERR) {
        
        continue;
    }
}

int MainApp::showMenu(string title, vector<pair<string, string>> options)
{
    clear();
    showStatus();
    mvprintw(2, 0, title.c_str());
    int k=0;
    for (auto i=options.begin();i!=options.end();++i, ++k) {
        mvprintw(3+k, 0, "%s - %s", i->first.c_str(), i->second.c_str());
    }
    refresh();
    int ch;
    while (true) {
        ch = nextEvent();
        
        if (isalnum(ch)) {
            string k;
            k.push_back(ch);
            auto i = find_if(options.begin(), options.end(), [&k](pair<string, string> a) {
                return a.first == k;
            });
            
            if (i != options.end()) {
                return (int)std::distance(options.begin(), i);
            }
        }
    }
    return 0;
}

int MainApp::nextEvent()
{
    static auto start = high_resolution_clock::now();
    int ch = getch();
    
    auto now = high_resolution_clock::now();
    auto elapsed = duration_cast<milliseconds>(now-start);
    
    if (elapsed.count()>1000 || elapsed.count() == 0) {
        player.addEstateIncome();
        showStatus();
        start = now;
    }
    return ch;
}

MainApp::~MainApp()
{
    endwin();
}

