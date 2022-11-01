#include <iostream>
#include <vector>
#include "Football.h"
#include "Dialog.h"

namespace Lab4{

    int getNum(int &a) {
        std::cin >> a;
        if (!std::cin.good())
            return -1;
        return 1;
    }

    int dialog(const char *msgs[], int N) {
        const char *errmsg = "";
        int rc;
        int i, n;
        do {
            std::cout << errmsg << std::endl;
            errmsg = "You are wrong. Repeat, please!";

            std::cout << "Choose the number from alternatives:" << std::endl << std::endl;
            for (i = 0; i < N; ++i)
                std::cout << msgs[i] << std::endl;
            std::cout << std::endl;
            std::cout << "Make your choise -->" << std::endl;


            n = getNum(rc);
            if (n == -1)
                rc = 0;
        } while (rc < 0 || rc >= N);
        return rc;
    }

    void messege_start(Team_description *ep) {
        int (*fptr[])(Team_description *ep) = {nullptr,
                                               D_Add_Team_Description,
                                               D_Add_New_Match,
                                               D_Add_New_Player,

        };

        const char *msgs[] = {"0. Quit",
                              "1. New Team description",
                              "2. Add new match",
                              "3. Add new player"
                    };

        const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

        int rc;
        while (rc = dialog(msgs, NMsgs)) {
            if (fptr[rc](ep) == -1)
                break;
        }


        printf("That's all, bye!");
    }

    int D_Add_Team_Description(Team_description *ep) {
        try {
            std::string team_name;
            std::string coach_name;
            Team_description tmp;
            std::cout << "Write team name: ";
            std::cin >> team_name;
            std::cout << "Write coach name: ";
            std::cin >> coach_name;
            tmp.setTeam_name(team_name);
            tmp.setCoach_name(coach_name);
            tmp.setTable();
            *ep = tmp;
        }
        catch (std::runtime_error& ex) {
            std::cout << ex.what() << std::endl;
            std::cout << "Table with this configuration doesn't exist! The previous Table is saved!" << std::endl;
        }
        return 0;


    }

    int D_Add_New_Match(Team_description *ep){
        try {
            std::string team_name;
            std::string Opposing_team_name;
            std::string Name;
            int Time_in_play, Penalty_time, Number_of_effective_throws, Number_of_misses, Reflected_throws, Missed_throws;
            int a, rc, rc1, enu;
            int ch = 0;
            Player *ptr = nullptr;
            Table table;
            std::cout << "Write date of match: ";
            a = getNum(rc);
            std::cout << "Write number of players: ";
            a = getNum(rc1);
            std::cout << "Write Opposing team name: ";
            std::cin >> Opposing_team_name;
            table.setDate(rc);
            table.setNumber_of_players(rc1);
            table.setOpposing_team_name(Opposing_team_name);
            while (ch < rc1){
                std::cout << "Write name of player: ";
                std::cin >> Name;
                std::cout << "Write time in penalty: ";
                a = getNum(Time_in_play);
                std::cout << "Write penalty time: ";
                a = getNum(Penalty_time);
                std::cout << "Player: 1. Striker 2. Defender 3. Goalkeeper??";
                a = getNum(enu);
                if (enu == 1) {
                    Striker player;
                    std::cout << "Write number of effective throws: ";
                    a = getNum(Number_of_effective_throws);
                    std::cout << "Write number of misses: ";
                    a = getNum(Number_of_misses);
                    player.setNumber_of_effective_throws(Number_of_effective_throws);
                    player.setNumber_of_misses(Number_of_misses);
                    player.setTime_in_play(Time_in_play);
                    player.setPenalty_time(Penalty_time);
                    player.setName(Name);
                    ptr = &player;
                }

                else if (enu == 2) {
                    Defender player;
                    player.setTime_in_play(Time_in_play);
                    player.setPenalty_time(Penalty_time);
                    player.setName(Name);
                    ptr = &player;
                }
                else if (enu == 3) {
                    Goalkeeper player;
                    std::cout << "Write reflected throws: ";
                    a = getNum(Reflected_throws);
                    std::cout << "Write missed throws: ";
                    a = getNum(Missed_throws);
                    player.setReflected_throws(Reflected_throws);
                    player.setMissed_throws(Missed_throws);
                    player.setTime_in_play(Time_in_play);
                    player.setPenalty_time(Penalty_time);
                    player.setName(Name);
                    ptr = &player;
                }
                std::cout << "Вставка игрока в таблицу";

                if (table.insert(Name, ptr))
                    std::cout << "Ok" << std::endl;
                else
                    std::cout << "Error" << std::endl;
                ch++;
            }

            *ep += &table;

        }
        catch (std::runtime_error& ex) {
            std::cout << ex.what() << std::endl;
            std::cout << "Table with this configuration doesn't exist! The previous Table is saved!" << std::endl;
        }
        return 0;
    }

    int D_Add_New_Player(Team_description *ep){
        try {

            int a, rc, date, enu;
            std::cout << "Write date of match: ";//находим нужный матч и туда запихиваем игрока со всем нужным описание
            a = getNum(rc);
            date = ep->Search_by_time(rc);//index of match
            if (date == -1){
                std::cout << "We have not this match";
                return 0;
            }else{
                std::string Name;
                int Time_in_play, Penalty_time;
                std::cout << "Player: 1. Striker 2. Defender 3. Goalkeeper";
                a = getNum(enu);
                if (enu == 1)
                    Player *player = new Striker;
                else if (enu == 2)
                    Player *player = new Defender;
                else if (enu == 3)
                    Player *player = new Goalkeeper;
                std::cout << "Write name of player: ";
                std::cin >> Name;
                std::cout << "Write time in penalty: ";
                a = getNum(Time_in_play);
                std::cout << "Write penalty time: ";
                a = getNum(Penalty_time);


//                player.setPenalty_time(Penalty_time);
//                player.setTime_in_play(Time_in_play);
//                player.setName(Name);
//                ep->setPlayer_T(&player, date);

            }

        }
        catch (std::runtime_error& ex) {
            std::cout << ex.what() << std::endl;
            std::cout << "Table with this configuration doesn't exist! The previous Table is saved!" << std::endl;
        }
        return 0;
    }

    int D_Add_New_Player1(Team_description *ep){
        try {

            int a, rc, rc1;
            std::cout << "Write date of match: ";
            a = getNum(rc);

        }
        catch (std::runtime_error& ex) {
            std::cout << ex.what() << std::endl;
            std::cout << "Table with this configuration doesn't exist! The previous Table is saved!" << std::endl;
        }
        return 0;
    }
}