### COMPILATION ###
CC = cc
CFLAGS = -Wall -Wextra -Werror

### INCLUDES ###
PROJECT = cub3D
PROJECT_DIR = ./

SRC_DIR = src
SRC_FILE = 
			$(SRC_DIR)/main.c
			   
### HEADER FILE ###
HEADER_DIR = includes

# MNIILIBX
MLX_DIR = mlx
MLX_FLAG = -L$(MLX_DIR) -lmlx -lXext -lX11

# MATH
MATH_FLAG = -lm

# LIBFT
FT_DIR = ./libft
FT = ft
FT_FLAG = -L$(FT_DIR) -l$(FT)

## OBJECT FILE ###
OBJ_DIR = .obj
OBJ_SRC = $(addprefix $(SRC_DIR)/, $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILE:.c=.o))))

.PHONY = bonus, all, clean, fclean

### RULES ###
all : $(PROJECT)

# bonus : all

$(PROJECT) : $(OBJ_SRC) $(OBJ_TOOLS)
	@git submodule init
	make -C $(MLX_DIR)
	make -C $(FT_DIR)
	$(CC) $(CFLAGS) $(OBJ_SRC) -o $(PROJECT) $(FT_FLAG) $(MLX_FLAG) $(MATH_FLAG)

$(SRC_DIR)/$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I ./$(HEADER_DIR)  -c $< -o $@

fclean : clean
	rm -f $(PROJECT)
	make fclean -C $(FT_DIR)

#Suppresion des fichiers objet
clean :
	rm -f $(SRC_DIR)/$(OBJ_DIR)/*.o
	@rm -df $(SRC_DIR)/$(OBJ_DIR)/
	rm -f $(BONUS_DIR)/$(OBJ_DIR)/*.o
	@rm -df $(BONUS_DIR)/$(OBJ_DIR)/
	make clean -C $(FT_DIR)
	make clean -C $(MLX_DIR)

re : fclean all

norminette :
	norminette $(FT_DIR) $(SRC_DIR) $(HEADER_DIR)
