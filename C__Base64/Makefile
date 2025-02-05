NAME			= ft_base64

CC				= cc
CFLAGS		= -Wall -Wextra -Werror -I get_next_line

OBJS_DIR	= .objs
GNL_DIR		= get_next_line

SRCS			= main.c parser.c encode.c decode.c utils.c
GNL_SRCS	:= get_next_line.c get_next_line_utils.c
GNL_SRCS	:= $(addprefix $(GNL_DIR)/, $(GNL_SRCS))
OBJS			= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
OBJS			+= $(addprefix $(OBJS_DIR)/, $(GNL_SRCS:.c=.o))

RM				= rm -rf

all: $(NAME)

$(OBJS_DIR)/%.o: %.c
	@echo "[Compiling] $(notdir $<) => $(notdir $@)"
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)/$(GNL_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "[Compiling] $(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@echo "[Cleaning] $(OBJS_DIR)/"
	@$(RM) $(OBJS_DIR)

fclean: clean
	@echo "[Cleaning] $(NAME)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
