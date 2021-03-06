#include "owner.hpp"
#include "estate.hpp"
#include "main_app.hpp"
#include "config.hpp"
#include <memory>

int main(int argc, const char *argv[]) {
    Owner player("User", "Name", 1500);
    Owner npc1("Mykhailo", "Zgurovsky", Infinity);
    Owner npc2("Petro", "Poroshenko", Infinity);
    Owner npc3("Bill", "Gates", Infinity);
    vector<Owner> npc{npc1, npc2, npc3};
    
    auto e1 = std::make_shared<RealEstate>("Shayrmechnaya", 1000, 200);
    auto e2 = std::make_shared<RealEstate>("Kpi", 100000, 4000);
    auto e3 = std::make_shared<RealEstate>("Roshen", 500000, 10000);
    auto e4 = std::make_shared<RealEstate>("Megasoft",10000, 1000);

   // player.buyEstate(e1);
    npc[0].buyEstate(e2);
    npc[1].buyEstate(e3);
    npc[2].buyEstate(e4);

    MainApp application(player, move(npc), {e1,e2,e3,e4});

    application.startGameLoop();

    return 0;
}
