NAME = minishell

LIBFT = libft/libft.a

LIBFT_DIR = libft

CC = cc

CFLAGS = -Wall -Wextra -Werror

red			= /bin/echo -e "\x1b[31m\#\# $1\x1b[0m"
green		= /bin/echo -e "\x1b[32m\#\# $1\x1b[0m"
yellow		= /bin/echo -e "\x1b[33m\#\# $1\x1b[0m"
blue		= /bin/echo -e "\x1b[34m\#\# $1\x1b[0m"
purple		= /bin/echo -e "\x1b[35m\#\# $1\x1b[0m"

GARBAGE = $(addprefix garbage_collector/, garbage_utils.c garbage.c lock_unlock.c)

BULTINS = $(addprefix builtins/, pwd.c echo.c exit.c cd.c export.c unset.c env.c builtins.c)

PARSING = $(addprefix parsing/, before_tokenise.c parser.c parser2.c tokenizer.c tokenizer2.c tokenizer3.c)

SIGNAUX = $(addprefix signaux/, signaux.c handler_signal.c handler_signal2.c)

EXPAND = $(addprefix expand/, expand.c expand2.c expand3.c)

SRC = main.c \
	main_utils.c\
	utils.c \
	env_utils.c \
	env_utils2.c \
	env_utils3.c \
	min_env_utils.c \
	close.c\
	file_list.c\
	file_list2.c\
	exec.c\
	exec_builtins.c\
	cmd_lst.c\
	exec_child_builtins.c\
	export_utils.c\
	expand_heredoc.c\
	heredoc_utils.c\
	strrdup_add_line.c\
	exec_utils.c\
	exec_cmd.c\
	find_cmd_path.c\
	heredoc.c $(BULTINS) $(GARBAGE) $(PARSING) $(SIGNAUX) $(EXPAND)

SRCS_DIR = src

SRC := $(SRC:%=$(SRCS_DIR)/%)
OBJS_DIR = .objets
OBJ = $(SRC:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

DIR_DUP     = mkdir -p $(@D)

# ---------------------------------- RULES ----------------------------------- #

all: $(LIBFT) $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -Ihdr -Ilibft -lreadline -lft -Llibft -o $(NAME)
	@$(call blue,"✅ $@ build successful!")

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) -Ihdr -Ilibft -c $< -o $@
	@$(call blue,"✅ $< compiled!")

$(LIBFT):
	@$(MAKE) -sC $(LIBFT_DIR)
	@$(call blue,"✅ $@ compiled!")

clean   :
	@rm -rf $(OBJS_DIR)
	@$(call blue,"🗑️ $(NAME) cleaned")

fclean  : clean
	@$(MAKE) -sC $(LIBFT_DIR) fclean
	@rm -rf $(NAME)
	@$(call blue,"🗑️ $(NAME) fcleaned")

re      : fclean all

val	:
	valgrind --suppressions=ignore_readline.supp --leak-check=full --track-fds=yes ./minishell
.PHONY : all bonus clean fclean re run val fun

