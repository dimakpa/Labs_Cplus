#include <iostream>
#include "Football.h"
#include "cstring"
#include "string"
#include <sstream>

namespace Lab4{

    Goalkeeper::Goalkeeper() {

    }

    Goalkeeper *Goalkeeper::clone() const {
        return new Goalkeeper(*this);
    }

    Defender::Defender() {

    }

    Striker::Striker() {

    }

    Striker *Striker::clone() const {
        return new Striker(*this);
    }

    Defender *Defender::clone() const {
        return new Defender(*this);
    }
    Table::Table(int a, std::string word, int N) {
        date = a;
        Opposing_team_name = word;
        Number_of_payers = N;
    }

    Team_description::Team_description() {

    }

    void Team_description::insert(Table *table){
        int i =0, k;
        if (this->Game_table == nullptr){
            this->Game_table = new Table;
            this->Game_table = table;
        } else{
            while (this[i].Game_table != nullptr)
                i++;
            this[i].Game_table = new Table;
            this[i].Game_table = table;
        }
    }

    Team_description &Team_description::operator += (struct Table *table){
        insert(table);
        return *this;
    }

    int Team_description::Search_by_time(int date){
        int k=0;
        if (this->Game_table != nullptr){
            while (this[k].Game_table != nullptr && this[k].Game_table->getDate() != date)
                k++;
            if (this[k].Game_table == nullptr)
                return -1;
            else
                return k;
        }
        else{
            return -1;
        }
    }

    void Team_description::setPlayer_T(Player *player, int date){
        this[date].Game_table->setPlayer(player);
    }

    void Table::setPlayer(Player *player){

    }

    int & Table::operator [] (Player &pl){
        std::string string;
        //std::cin >> string;
        insert(string, &pl);


    }

    bool Table::insert(const std::string &s, const Player *pl){
        bool res = false;
        std::map<const std::string, Player *>::iterator p = players.find(s);
        if (p == players.end()){
            std::pair<std::map<const std::string, Player *>::iterator, bool> pp =
                    players.insert(std::make_pair(s, pl->clone()));
            if (!pp.second)
                throw std::runtime_error("can't insert new item into map");
            res = true;
        }
        return res;
    }


}