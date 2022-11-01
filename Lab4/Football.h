#include <iostream>
#include <map>

namespace Lab4 {
    ///Abstract class of players
    class Player {
    private:
        std::string Name;
        int Time_in_play;
        int Penalty_time;
    public:
        ///Types of player
        enum class  Types{
            Goalkeeper,
            Defender,
            Striker
        } Type_of_player;

        /// @return types of class Types
        virtual Types getType() = 0;
        [[nodiscard]] virtual Player* clone() const = 0;

        ///Set name
        ///@param nam Name
        void setName(std::string nam){ Name =nam;};
        ///@param a Time in play
        void setTime_in_play(int a){Time_in_play = a; };
        ///@param a Penalty time
        void setPenalty_time(int a){Penalty_time = a; };
        void setTypes(int i);

        ///@return Name
        std::string getName(){return  Name;};
        ///@return Time in play
        int &getTime_in_play(){return Time_in_play; };
        ///@return a Penalty time
        int &getPenalty_time(){return Penalty_time; };
    };


    class Goalkeeper : public Player {
    private:
        int Reflected_throws;
        int Missed_throws;
    public:
        Goalkeeper();
        ///virtual functions of set type of player
        virtual Types getType() override { return  Player::Types::Goalkeeper;};
        [[nodiscard]] virtual Goalkeeper* clone() const;

        ///@param a reflected throws
        void setReflected_throws(int a){Reflected_throws = a; };
        ///@param a missed throws
        void setMissed_throws(int a) {Missed_throws = a; };


        ///@return reflected throws
        int &getReflected_throws(){return Reflected_throws; };
        ///@return missed throws
        int &getMissed_throws() {return Missed_throws; };
    };

    class Defender : public Player {
    private:

    public:
        ///virtual functions of set type of player
        virtual Types getType() override { return  Player::Types::Defender;};
        [[nodiscard]] virtual Defender* clone() const;

        Defender();
    };

    class Striker : public Player {
    private:
        int Number_of_effective_throws;
        int Number_of_misses;
    public:
        Striker();
        ///virtual functions of set type of player
        virtual Types getType() override { return  Player::Types::Striker;};
        [[nodiscard]] virtual Striker* clone() const;

        ///@param a number of effective throws
        void setNumber_of_effective_throws(int a) {Number_of_effective_throws = a; };
        ///@param a number of misses
        void setNumber_of_misses(int a){Number_of_misses = a; };


        ///@return number of effective throws
        int &getNumber_of_effective_throws() {return Number_of_effective_throws; };
        ///@return number of misses
        int &getNumber_of_misses(){return Number_of_misses; };
    };

    ///Class descriptions
    class Table {
    private:
        int date;
        std::string Opposing_team_name;
        int Number_of_payers;
        std::map<const std::string, Player *> players;
    public:
        Table(){};
        ~Table(){};

        ///@param date Date match
        ///@param Opposing_team_name Name of opposing team name
        ///@param Number_of_players Number of players
        Table(int , std::string, int);

        ///@return Date of match
        int &getDate(){ return  date;};

        ///Set date of match
        ///@param a Date if match
        void setDate(int a){date = a;};

        ///@return Return opposing team name
        std::string getOpposing_team_name() {return Opposing_team_name;};

        ///
        void setOpposing_team_name(std::string word) {Opposing_team_name = std::move(word);};

        int &getNumber_of_players(){return Number_of_payers;};

        void setNumber_of_players(int a){Number_of_payers = a;};

        void setPlayer(Player *);


        bool insert(const std::string &, const Player *);
        bool replace(const std::string &, const Player *);
        bool remove(const std::string&);

        int & operator [] (Player &);

    };

    class Team_description {
    private:
        std::string Team_name;
        std::string Coach_name;

        class Table *Game_table;//лучше добаить шаблон

    public:
        Team_description();

        const std::string &getTeam_name() const {return Team_name;};//более быстро

        std::string getCoach_name() const {return Coach_name; };

        void setTeam_name(std::string word){ Team_name = word;};

        void setCoach_name(std::string word){ Coach_name = word;};

        void setTable(){Game_table = nullptr;};

        //void searchByDate(class Table *);

        //void deleteByDate(class Table *);

        void insert(Table *);

        Team_description & operator += (struct Table *);

        int Search_by_time(int a);

        void setPlayer_T(Player *, int);
    };

/*
 * class Goalkeeper : public Player
 *
 *
 Player* p = table.getPlayerByID(id);

 if (p.getType() == TypesOfPlayers::Goalkeeper)
 {
    GoalKeeper *gk = static_cast<Goalkeeper*>(p);
 }

 */
}