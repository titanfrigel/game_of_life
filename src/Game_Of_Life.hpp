/*
** EPITECH PROJECT, 2023
** game_of_life
** File description:
** Game_Of_Life
*/

#include <vector>
#include <string>

#ifndef _GAME_OF_LIFE_HPP_
    #define _GAME_OF_LIFE_HPP_

    class Game_Of_Life {
        private:
            std::vector<std::string> map;
            size_t x;
            size_t y;
            size_t pos_x;
            size_t pos_y;
        public:
            Game_Of_Life(int argc, char **argv);
            ~Game_Of_Life();
            void print_map();
            void actualize_map();
            void create_map();
            void run();
            static int exec_game_of_life(int argc, char **argv);
    };
#endif

