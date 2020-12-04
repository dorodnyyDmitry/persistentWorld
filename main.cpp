#include "worlds.hpp"



int main()
{
    std::srand(std::time(0));

    /*std::ofstream ofs("save.dat", std::ios::binary);
    boost::archive::binary_oarchive oa(ofs);*/

    /*std::ifstream ifs("save.dat", std::ios::binary);
    boost::archive::binary_iarchive ia(ifs);*/


    /*Universe *world = new Universe(100);
    Planet *starting_planet = world->new_planet();

    Player player;
    ia >> player;*/

    /*Player player(starting_planet, world);
    oa << player;*/




    /*Universe *world = new Universe(100);
    Planet *starting_planet = world->new_planet();
    Player *player = new Player(starting_planet, world);

    player->where_am_i();

    oa << starting_planet;*/

    //ia >> ph_planet(100);

    Universe *world = new Universe(100);
    Planet *starting_planet = world->new_planet();
    Player *player = new Player(starting_planet, world);
    int input = 0;
    while(input != -1){
        std::cout << std::endl;
        std::cout << "1 - where am I\n2 - travel\n3 - save\n4 - load\n5 - exit\n";
        std::cin >> input;
        switch (input) {
        case 1:
            player->where_am_i();
            break;
        case 2:
            std::cout << "Which portal\n";
            int x;
            std::cin >> x;
            player->use_portal(x);
            player->where_am_i();
            break;


        case 3:{
            std::ofstream ofs("save.dat", std::ios::binary);
            boost::archive::binary_oarchive oa(ofs);
            oa << player;
            ofs.close();
            break;
        }
        case 4:{
            std::ifstream ifs("save.dat", std::ios::binary);
            boost::archive::binary_iarchive ia(ifs);
            ia >> player;
            ifs.close();
            break;
        }
        case 5:
            input = -1;
            break;
        default:
            break;

        }
    }

    //std::cout << planets.size();
    //Player player(&my_planet);

    //player.where_am_i();

    /*planets.insert(std::make_pair(my_planet.name, my_planet));

    //std::cout << my_planet.name << '\n' << my_planet.colour << '\n' << my_planet.nportals;
    //std::cout << planets[0].name << '\n' << planets[0].colour << '\n' << planets[0].nportals;
    std::cout << planets[my_planet.name].name << '\n' << planets[my_planet.name].colour << '\n' << planets[my_planet.name].nportals;*/

    return 0;
}
