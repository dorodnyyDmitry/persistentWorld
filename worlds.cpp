#include "worlds.hpp"

int Planet::gen_nportals(std::mt19937 *rnd){
    int n = 1;
    std::uniform_int_distribution<> dist(0, 10);
    while(true){
        if(dist(*rnd) - 3 >= 5)
            break;
        n++;
    }
    return n;
}

int Planet::gen_colour(std::mt19937 *rnd){
    std::uniform_int_distribution<> dist(0, COLOUR_MAX);
    return dist(*rnd);
}

int Planet::gen_name(int usize, std::mt19937 *rnd){
    std::uniform_int_distribution<> dist(1, usize);
    return dist(*rnd);
}

int Planet::get_exit(){
    for(int i = 0; i< this->get_nportals(); i++){
        if((*this->get_portals())[i] == 0){
            return i;
        }
    }
    return -1;
}

Planet *Universe::new_planet(){
    while(true){
        Planet* planet = new Planet(this->max_planets, this->get_rnd());
        auto pexists = this->planets.find(planet->get_name());
        if(pexists == this->planets.end()){
            this->planets.insert(std::pair(planet->get_name(), planet));
            if(planet->get_nportals() >= 2){
                this->warpable.insert(std::pair(planet->get_name(), planet));
            }
            return planet;
        }
        else{
            this->max_planets *= 2;
            delete(planet);
        }
    }
}

void Player::use_portal(int nportal){
    if(current_pos->get_nportals() < nportal){
        //std::cout << "\nNo such portal here\n";
        return;
    }

    if((*current_pos->get_portals())[nportal] != 0){
        //std::cout << "Home sweet home\n";
        current_pos = (*current_pos->get_portals())[nportal];
        return;
    }

    std::unordered_map<int, Planet*> *warpable = this->get_uni()->get_warpable();

    double xx = (warpable->size());
    double yy = (this->get_uni()->get_max_planets());
    std::uniform_int_distribution<> sizedist(0, yy);
    if(sizedist(*this->get_uni()->get_rnd()) <= xx && xx > 10 ){
        //auto current_position = this->get_uni()->get_warpable()->extract(current_pos);
        warpable->erase(current_pos->get_name());

        std::vector<int> p_names;
        //std::pair<int, Planet*> p;

        for(std::unordered_map<int, Planet*>::iterator it = warpable->begin(); it != warpable->end(); ++it){
            if(it->second != 0){
                p_names.push_back(it->first);
            }
        }


        std::uniform_int_distribution<> dist(0, p_names.size()-1);

        int nplanet = dist(*this->get_uni()->get_rnd());

        Planet* warp_to = (*warpable)[p_names[nplanet]];
        (*current_pos->get_portals())[nportal] = warp_to;

        (*warp_to->get_portals())[warp_to->get_exit()] = current_pos;

        if(warp_to->get_exit() == -1){
            this->get_uni()->get_warpable()->erase(warp_to->get_name());
        }

        if(current_pos->get_exit() != -1){
            this->get_uni()->get_warpable()->insert(std::pair(current_pos->get_name(), current_pos));
        }
        current_pos = warp_to;
        return;
    }
    else{
        Planet *warp_to = this->get_uni()->new_planet();

        (*warp_to->get_portals())[warp_to->get_exit()] = current_pos;
        (*current_pos->get_portals())[nportal] = warp_to;
        current_pos = warp_to;
        //std::cout << "Brave new world!\n";
        return;
    }
}


void Player::where_am_i(){
    std::cout << std::endl;
    std::cout << "On the orbit of: " << current_pos->get_name() << '\n';
    std::cout <<"colour: #" << std::hex << current_pos->get_colour() << std::dec << '\n';


    for(int i = 0; i < current_pos->get_nportals(); i++){
        if((*current_pos->get_portals())[i] == 0){
            std::cout << i << "====" << "uncharted\n";
        }
        else{
            std::cout << i << "====" << ((*current_pos->get_portals())[i])->get_name() << '\n';
        }
    }
}

void init_interactive(){
    Universe *world = new Universe(100);
    Planet *starting_planet = world->new_planet();
    Player *player = new Player(starting_planet, world);

    int input = 0;
    while(input != -1){
        std::cout << std::endl;
        std::cout << "1 - where am I\n2 - travel\n3 - save\n4 - load\n5 - exit\n";

        std::cin >> input;
        assert(input > 0 && input <= 5);

        switch (input) {
        case 1:{
            player->where_am_i();
            break;
        }
        case 2:{
            std::cout << "Which portal\n";

            int x;
            std::cin >> x;
            assert(input >= 0 && input <= player->get_pos()->get_nportals());

            player->use_portal(x);
            player->where_am_i();
            break;
        }
        case 3:{
            std::ofstream ofs("save.dat", std::ios::binary);
            boost::archive::binary_oarchive oa(ofs);
            oa << player;
            std::cout << "Saved!\n";
            break;
        }
        case 4:{
            std::ifstream ifs("save.dat", std::ios::binary);
            boost::archive::binary_iarchive ia(ifs);
            ia >> player;
            std::cout << "Loaded!\n";
            break;
        }
        case 5:{
            input = -1;
            break;
        }
        default:
            break;
        }
    }
}


void init_automatic(int jumps){

    Universe world(100);
    Planet *starting_planet = world.new_planet();
    Player player(starting_planet, &world);


    for(;jumps >= 0; jumps--){
        std::uniform_int_distribution<> dist(0, player.get_pos()->get_nportals()-1);
        int x = dist(*world.get_rnd());
        assert(x <= player.get_pos()->get_nportals() && x >= 0);
        player.use_portal(x);
       //player->use_portal(dist(*world->get_rnd()));
    }

    /*std::ofstream ofs("save.dat", std::ios::binary);
    boost::archive::binary_oarchive oa(ofs);
    oa << player;*/
}
