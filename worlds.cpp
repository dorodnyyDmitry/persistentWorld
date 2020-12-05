#include "worlds.hpp"

int Planet::gen_nportals(){
    std::random_device r;
    std::default_random_engine re(r());
    int n = 1;
    while(true){
        if(std::round(std::generate_canonical<double, 10>(re)-0.3))
            break;
        n++;
    }
    return n;
}

int Planet::gen_colour(){
    std::random_device r;
    std::default_random_engine re(r());
    std::uniform_int_distribution<> dist(0, COLOUR_MAX);

    return dist(re);
}

int Planet::gen_name(int usize){
    std::random_device r;
    std::default_random_engine re(r());
    std::uniform_int_distribution<> dist(1, usize);
    return dist(re);
}

int Planet::get_exit(){
    for(int i = 0; i<= this->get_nportals(); i++){
        if((*this->get_portals())[i] == 0){
            return i;
        }
    }
    return -1;
}

Planet *Universe::new_planet(){
    while(true){
        Planet* planet = new Planet(this->max_planets);
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
            std::cout << "You are small and insignificant\n";
            delete(planet);
            sleep(1);
        }
    }
}

void Player::use_portal(int nportal){
    if(current_pos->get_nportals() < nportal){
        std::cout << "\nNo such portal here\n";
        return;
    }

    if((*current_pos->get_portals())[nportal] != 0){
        std::cout << "Home sweet home\n";
        current_pos = (*current_pos->get_portals())[nportal];
        return;
    }

    std::unordered_map<int, Planet*> *warpable = this->get_uni()->get_warpable();

    std::random_device r;
    std::default_random_engine re(r());

    double xx = (warpable->size());
    double yy = (this->get_uni()->get_max_planets());
    if(std::generate_canonical<double, 10>(re) <= xx/yy && xx >= 3){
        //auto current_position = this->get_uni()->get_warpable()->extract(current_pos);
        std::cout<< "Familiar place...\n";
        warpable->erase(current_pos->get_name());
        std::cout << "cringe\n";
        std::random_device r;
        std::default_random_engine re(r());


        std::vector<int> p_names;
        //std::pair<int, Planet*> p;
        for(std::unordered_map<int, Planet*>::iterator it = warpable->begin(); it != warpable->end(); ++it){
            if(it->second != 0){
                p_names.push_back(it->first);
                std::cout << it->first << '\n';
            }
        }

        std::uniform_int_distribution<> dist(0, p_names.size());

        int nplanet = dist(re);
        /*auto iter = warpable->begin();
        std::advance(iter, nplanet);*/
        std::cout << p_names[nplanet] << '\n';
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
        std::cout << "Brave new world!\n";
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

