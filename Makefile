NAME := testsurf
SRC_DIR := ./src/
OBJ_DIR := ./obj/
HEADER_DIR = ./inc/
SRCS :=	$(wildcard $(SRC_DIR)*.cpp) \
		get.cpp \
		post.cpp \
		delete.cpp \
		custom.cpp \
		hosts.cpp
OBJS := $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))
HEADERS = $(wildcard $(HEADER_DIR)*.h)
PLATFORM := $(shell uname -s)
CC := c++
CFLAGS = -g -Wall -Wextra -Werror
INCLUDES = -I $(HEADER_DIR)
LINK := -lcurl
DEPS = $(wildcard $(INC_DIR)*.hpp) Makefile

# Colorcodes
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
BLUE := \033[0;34m
NC := \033[0m

all: $(NAME)

$(NAME): $(OBJS) $(DEPS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LINK) -o $@
	@echo "\n$(GREEN)$(NAME) created$(NC)"
	@echo "$(YELLOW)SUCCESFULLY COMPILED!$(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(DEPS) ofilemessage
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo ".\c"

ofilemessage:
	@echo "compiling $(NAME)-object-files: \c"

clean:
	@echo "$(RED)$(NAME)-object-files deleted$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) deleted$(NC)"

re: fclean all

peace:
	@echo "\n"
	@echo "     .''.    .',"
	@echo "     |  |   /  /"
	@echo "     |  |  /  /"
	@echo "     |  | /  /"
	@echo "     |  |/  ;-._"
	@echo "     }  \` _/  / ;"
	@echo "     |  /\` ) /  /"
	@echo "     | /  /_/\_/\ "
	@echo "     |/  /      |"
	@echo "     (  ' \ '-  |"
	@echo "      \    \`.  /"
	@echo "       |      |"
	@echo "       |      |\n"

.INTERMEDIATE: ofilemessage

.PHONY: clean fclean all re