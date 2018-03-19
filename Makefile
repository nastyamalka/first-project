NAME =				libftprintf.a

CC =				gcc
FLAGS =				-Wall -Werror -Wextra

FT_SRC_DIR =		./libft
PRINTF_SRC_DIR =	./printf
OBJDIR =			objs/


HEADER =			$(FT_SRC_DIR)libft.h
PRINTF_SRC_HEADER =	$(PRINTF_SRC_DIR)ft_printf.h

FT_COMPILED =		ft_atoi.o \
                    ft_bzero.o \
                    ft_countw.o \
                    ft_intrev.o \
                    ft_intsort.o \
                    ft_isalnum.o \
                    ft_isalpha.o \
                    ft_isascii.o \
                    ft_isdigit.o \
                    ft_isprint.o \
                    ft_itoa.o \
                    ft_lstadd.o \
                    ft_lstdel.o \
                    ft_lstdelone.o \
                    ft_lstiter.o \
                    ft_lstmap.o \
                    ft_lstnew.o \
                    ft_memalloc.o \
                    ft_memccpy.o \
                    ft_memchr.o \
                    ft_memcmp.o \
                    ft_memcpy.o \
                   	ft_memdel.o \
                    ft_memmove.o \
                    ft_memset.o \
                    ft_putchar_fd.o \
                    ft_putchar.o \
                    ft_putendl_fd.o \
                    ft_putendl.o \
                    ft_putnbr_fd.o \
                    ft_putnbr.o \
                    ft_putstr_fd.o \
                    ft_putstr.o \
                    ft_strcat.o \
                    ft_strchr.o \
                    ft_strclr.o \
                    ft_strcmp.o \
                    ft_strcpy.o \
                    ft_strdel.o \
                    ft_strdup.o \
                    ft_strequ.o \
                    ft_striter.o \
                    ft_striteri.o \
                    ft_strjoin.o \
                    ft_strlcat.o \
                    ft_strlen.o \
                    ft_strmap.o \
                    ft_strmapi.o \
                    ft_strncat.o \
                    ft_strncmp.o \
                    ft_strncpy.o \
                    ft_strnequ.o \
                    ft_strnew.o \
                    ft_strnstr.o \
                    ft_strrchr.o \
                    ft_strrev.o \
                    ft_strsort.o \
                    ft_strsplit.o \
                    ft_strstr.o \
                    ft_strsub.o \
                    ft_strtrim.o \
                    ft_tolower.o \
                    ft_toupper.o \

PRINTF_COMPILED =	withnorm.o
COMPILED =			$(FT_COMPILED) $(PRINTF_COMPILED)
OBJECTS = $(addprefix ${OBJDIR}, ${COMPILED})

all: $(NAME)

$(NAME): $(COMPILED)
	@ar rc $(NAME) $(COMPILED)
	@ranlib $(NAME)
	@echo "made" $(NAME)

$(FT_COMPILED): %.o: $(FT_SRC_DIR)/%.c
	@$(CC) -c $(FLAGS) -I $(FT_SRC_DIR) $< -o $@

$(PRINTF_COMPILED): %.o: $(PRINTF_SRC_DIR)/%.c
	@$(CC) -c $(FLAGS) -I $(FT_SRC_DIR) -I $(PRINTF_SRC_DIR) $< -o $@

clean:
	@-/bin/rm -f $(COMPILED)

fclean: clean
	@-/bin/rm -f $(NAME)
	@-/bin/rm -f $(FT_COMPILED)

re: fclean all