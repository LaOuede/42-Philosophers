# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/11 12:57:00 by gle-roux          #+#    #+#              #
#    Updated: 2023/07/25 11:53:45 by gle-roux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------#
#                          BANNER & COLOR SETTINGS                             #
#------------------------------------------------------------------------------#

#Banner
define BANNER1
                   
$G         _     $Y_$G _                       _                   
$G   _ __ | |__ $Y(_)$G | ___  ___  ___  _ __ | |__   ___ _ __ ___ 
$G  | '_ \| '_ \| | |/ $Y_$G \/ __|/ $Y_$G \| '_ \| '_ \ / $Y_$G \ '__/ __| 
$C  | |_) | | | | | | $Y(_)$G \__ \ $Y(_)$G | |_) | | | |  __/ |  \__ \ 
$C  | .__/|_| |_|_|_|\___/|___/\___/| .__/|_| |_|\___|_|  |___/ 
$C  |_|                             |_|                         
endef
export BANNER1

# Colors settings
R = $(shell tput -Txterm setaf 1)
G = $(shell tput -Txterm setaf 2)
Y = $(shell tput -Txterm setaf 3)
Z = $(shell tput -Txterm setaf 5)
C = $(shell tput -Txterm setaf 6)
W = $(shell tput -Txterm setaf 7)

# Print settings
ERASE_LINE	=	\033[2K\r

#------------------------------------------------------------------------------#
#                                   TOOLS                                      #
#------------------------------------------------------------------------------#
define HELP
---------------------------------------------------------------
$YTools available :$W
make help		$Y->$W Display tools available
make norm		$Y->$W Run Norminette
make pdf 		$Y->$W Open PDF subject
---------------------------------------------------------------
endef
export HELP

#------------------------------------------------------------------------------#
#                                VARIABLES                                     #
#------------------------------------------------------------------------------#

# Compiler and flags
CC		=	gcc
CFLAGS	= 	-g -Wall -Wextra -Werror 
#CFLAGS	= 	-fsanitize=address
#CFLAGS	=	-g -Wall -Wextra -Werror -fsanitize=thread

# Remove
RM		=	rm -rf

# Librairies names
NAME		=	philo

# Dir. and files names
SRCS_DIR	=	./src/
SRCS_LIST	=	initialization.c \
				main.c \
				parsing.c \
				routine.c \
				routine_alone.c \
				utils.c \
				monitoring.c \
				utils_print.c \
				utils_time.c
SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR	=	./obj/
OBJS_LIST	=	$(patsubst %.c, %.o, $(SRCS_LIST))
OBJS		=	$(addprefix $(OBJS_DIR), $(OBJS_LIST))

# Headers
HEADER_DIR	=	./include/
HEADER_LIST	=	philosophers.h
HEADER	 	=	$(addprefix $(HEADER_DIR), $(HEADER_LIST))

# Evaluator variable
USER		=	$(shell whoami)

#------------------------------------------------------------------------------#
#                                  RULES                                       #
#------------------------------------------------------------------------------#

# Executable creation
all: dir $(NAME)
	@echo $Y"$$BANNER1\n"$W
	@echo "			...powered by $Ygle-roux🐭$W"
	@echo "				...evaluated by $Y$(USER)\n\n$W"

#Create directory for *.o files
dir:
	@mkdir -p $(OBJS_DIR)

# Compilation
$(NAME): $(OBJS)
	@echo "$(ERASE_LINE)$W\n>>>>>>>>>>>>>>>>>>> $YCompilation $Wis $Gdone ✅ $W<<<<<<<<<<<<<<<<<<<<"
	@$(CC) $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "\n-------------- If help is needed, type $Ymake help $W--------------"
	@echo "\n>>>>>>>>>>>>>>>>>>> $YPHILOSOPHERS $Wis $Gready ✅$W <<<<<<<<<<<<<<<<<<"

# Create all files .o (object) from files .c (source code)
$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADER)
	@printf "$(ERASE_LINE) $GCompiling : $Z$(notdir $<)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Remove objects
clean:
	@echo "\n$W>>>>>>>>>>>>>>>>>>>>>>>>>>> $YCLEANING $W<<<<<<<<<<<<<<<<<<<<<<<<<<\n"
	@$(RM) $(OBJS_DIR)
	@echo "$W------------------ $(NAME): $(OBJS_DIR) was $Rdeleted ❌$W----------------"

# Remove executables
fclean: clean
	@$(RM) $(NAME)
	@echo "\n$W-------- All exec. and archives successfully $Rdeleted ❌$W--------\n"
	@echo "$W>>>>>>>>>>>>>>>>>>>>> $YCleaning $Wis $Gdone ✅ $W<<<<<<<<<<<<<<<<<<<<<\n"

# Remove objects and executables and remake
re: fclean
	@$(MAKE) all

# Display tools available
help:
	@echo "$$HELP"

# Open the subject
pdf:
	@open https://cdn.intra.42.fr/pdf/pdf/66945/fr.subject.pdf

# Run norminette
norm :
	@echo "\n$W>>>>>>>>>>>>>>>>>>>>>>>>>> $YNORMINETTE $W<<<<<<<<<<<<<<<<<<<<<<<<<<$W\n"
	@norminette $(SRCS) $(HEADER)
	@echo "\n$W>>>>>>>>>>>>>>>>>>>>>>>> $YNORMINETTE ✅ $W<<<<<<<<<<<<<<<<<<<<<<<<<$W\n"

# Avoids file-target name conflicts
.PHONY: all dir clean fclean re help pdf norm