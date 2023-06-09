##
## EPITECH PROJECT, 2023
## game_of_life
## File description:
## Makefile
##

CC = g++

CFLAGS = -W -Wall -Wextra -g2 -O2

INCLUDES = -I./src

LFLAGS =

LIBS = -lncurses

SRC_PATH = src/

SRCS_NAME = main.cpp Game_Of_Life.cpp

MAIN = game_of_life

SRCS = $(patsubst %, $(SRC_PATH)%, $(SRCS_NAME))

OBJS = $(SRCS:.cpp=.o)

all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

%.o : %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean :
	$(RM) $(OBJS) *~

fclean : clean
	$(RM) $(MAIN)

re : fclean all
