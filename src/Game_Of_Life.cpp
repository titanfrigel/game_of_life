/*
** EPITECH PROJECT, 2023
** game_of_life
** File description:
** Game_Of_Life
*/

#include "Game_Of_Life.hpp"
#include <cstdio>
#include <cstring>
#include <ncurses.h>
#include <sys/wait.h>
#include <time.h>

void Game_Of_Life::actualize_map()
{
    std::vector<std::string> new_map = this->map;

    for (size_t i = 0; i < this->y; i++) {
        for (size_t j = 0; j < this->x; j++) {
            int nb_neighbours = 0;
            if (i > 0 && j > 0 && this->map[i - 1][j - 1] == 'o')
                nb_neighbours++;
            if (i > 0 && this->map[i - 1][j] == 'o')
                nb_neighbours++;
            if (i > 0 && j < this->x - 1 && this->map[i - 1][j + 1] == 'o')
                nb_neighbours++;
            if (j > 0 && this->map[i][j - 1] == 'o')
                nb_neighbours++;
            if (j < this->x - 1 && this->map[i][j + 1] == 'o')
                nb_neighbours++;
            if (i < this->y - 1 && j > 0 && this->map[i + 1][j - 1] == 'o')
                nb_neighbours++;
            if (i < this->y - 1 && this->map[i + 1][j] == 'o')
                nb_neighbours++;
            if (i < this->y - 1 && j < this->x - 1 && this->map[i + 1][j + 1] == 'o')
                nb_neighbours++;
            if (this->map[i][j] == 'o' && (nb_neighbours < 2 || nb_neighbours > 3))
                new_map[i][j] = ' ';
            if (this->map[i][j] == ' ' && nb_neighbours == 3)
                new_map[i][j] = 'o';
        }
    }
    this->map = new_map;
}

void Game_Of_Life::print_map()
{
    clear();
    for (size_t i = 0; i < x + 2; i++)
        mvprintw(LINES / 2 - y / 2 - 1, COLS / 2 - x / 2 + i, "-");
    for (size_t i = 0; i < y; i++) {
        mvprintw(LINES / 2 - y / 2 + i, COLS / 2 - x / 2, "|");
        for (size_t j = 0; j < x; j++)
            mvprintw(LINES / 2 - y / 2 + i, COLS / 2 - x / 2 + j + 1, "%c", this->map[i][j]);
        mvprintw(LINES / 2 - y / 2 + i, COLS / 2 - x / 2 + x + 1, "|");
    }
    for (size_t i = 0; i < x + 2; i++)
        mvprintw(LINES / 2 - y / 2 + y, COLS / 2 - x / 2 + i, "-");
    refresh();
}

Game_Of_Life::~Game_Of_Life()
{
    endwin();
}

Game_Of_Life::Game_Of_Life(int argc, char **argv) : map(), x(0), y(0), pos_x(0), pos_y(0)
{
    if (argc != 3 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--h") == 0
    || strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "--help") == 0) {
        printf("Usage: ./game_of_life [x] [y]\n");
        return;
    }
    if (atoi(argv[1]) <= 0 || atoi(argv[2]) <= 0) {
        printf("Usage: ./game_of_life [x] [y]\n");
        return;
    }
    this->x = atoi(argv[1]);
    this->y = atoi(argv[2]);
    for (size_t i = 0; i < this->y; i++) {
        this->map.push_back("");
        for (size_t j = 0; j < this->x; j++) {
            this->map[i] += ' ';
        }
    }
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
}

void Game_Of_Life::create_map()
{
    int ch = 0;

    while (ch != 'q') {
        ch = getch();
        if (ch == KEY_UP && this->pos_y > 0)
            this->pos_y--;
        if (ch == KEY_DOWN && this->pos_y < this->y - 1)
            this->pos_y++;
        if (ch == KEY_LEFT && this->pos_x > 0)
            this->pos_x--;
        if (ch == KEY_RIGHT && this->pos_x < this->x - 1)
            this->pos_x++;
        if (ch == ' ')
            this->map[this->pos_y][this->pos_x] = (this->map[this->pos_y][this->pos_x] == 'o') ? ' ' : 'o';
        this->print_map();
        usleep(50000);
    }
}

void Game_Of_Life::run()
{
    int ch = 0;

    while (ch != 'q') {
        ch = getch();
        usleep(250000);
        this->actualize_map();
        this->print_map();
    }
}

int Game_Of_Life::exec_game_of_life(int argc, char **argv)
{
    Game_Of_Life game(argc, argv);

    if (game.x == 0 || game.y == 0)
        return (84);
    if ((int)game.x + 3 > COLS || (int)game.y + 2 > LINES) {
        endwin();
        printf("The map is too big for your terminal.\nMax size: %dx%d\n", COLS - 3, LINES - 2);
        return (84);
    }
    game.print_map();
    game.create_map();
    game.run();
    return (0);
}
