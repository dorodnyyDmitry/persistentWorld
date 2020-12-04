#include "worlds.hpp"



int Planet::gen_nportals(){
    std::random_device r;
    std::default_random_engine re(r());
    int n = 1;
    while(true){
        if(std::round(std::generate_canonical<double, 10>(re)-0.2))
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
    std::uniform_int_distribution<> dist(0, usize);

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
            this->max_planets *= 10;
            delete(planet);
        }
    }
}

void Player::use_portal(int nportal){
    if(current_pos->get_nportals() < nportal){
        std::cout << "\nNo such portal here\n";
        return;
    }

    std::unordered_map<int, Planet*> *warpable = this->get_uni()->get_warpable();

    std::random_device r;
    std::default_random_engine re(r());
    if(std::generate_canonical<double, 10>(re) >= (warpable->size())/(this->get_uni()->get_max_planets())){
        Planet *warp_to = this->get_uni()->new_planet();
        (*warp_to->get_portals())[warp_to->get_exit()] = current_pos;
        (*current_pos->get_portals())[nportal] = warp_to;
        current_pos = warp_to;

        return;
    }
    else{
        //auto current_position = this->get_uni()->get_warpable()->extract(current_pos);

        warpable->erase(current_pos->get_name());

        std::random_device r;
        std::default_random_engine re(r());
        std::uniform_int_distribution<> dist(0, warpable->size());

        int nplanet = dist(re);
        auto iter = warpable->begin();
        std::advance(iter, nplanet);
        Planet* warp_to = iter->second;
        (*current_pos->get_portals())[nportal] = warp_to;

        (*warp_to->get_portals())[warp_to->get_exit()] = current_pos;

        if(warp_to->get_exit() == -1){
            warpable->erase(warp_to->get_name());
        }

        if(current_pos->get_exit() != -1){
            warpable->insert(std::pair(current_pos->get_name(), current_pos));
        }

        current_pos = warp_to;
    }

}


void Player::where_am_i(){
    std::cout << "On the orbit of: " << current_pos->get_name() << '\n';
    for(int i = 0; i < current_pos->get_nportals(); i++){
        std::cout << i << "====" << (*current_pos->get_portals())[i] << '\n';
    }
}
