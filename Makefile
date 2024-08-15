# *************************************************************************** #
#                                COMPILATION                                  #
# *************************************************************************** #
CC := cc
CFLAGS := -Wall -Wextra -Werror -g3

# *************************************************************************** #
#                            PROJECT CONFIGURATION                            #
# *************************************************************************** #
PROJECT := cub3D
PROJECT_DIR := ./

### SRC_DIR ###
SRC_DIR := src
ERROR_DIR := error
INIT_DIR := init
RENDER_DIR := render

### BONUS_DIR ###
BONUS_DIR := bonus
MINIMAP_DIR := minimap

# *************************************************************************** #
#                                 INCLUDES                                    #
# *************************************************************************** #
HEADER_DIR := includes

# *************************************************************************** #
#                                MLX LIBRARY                                  #
# *************************************************************************** #
MLX_DIR := mlx
MLX_FLAG := -L$(MLX_DIR) -lmlx -lXext -lX11

# *************************************************************************** #
#                                MATH LIBRARY                                 #
# *************************************************************************** #
MATH_FLAG := -lm

# *************************************************************************** #
#                                  LIBFT                                      #
# *************************************************************************** #
FT_DIR := ./libft
FT := ft
FT_FLAG := -L$(FT_DIR) -l$(FT)
 
# *************************************************************************** #
#                                 SOURCE FILE                                 #
# *************************************************************************** #
#                       +------------------------------+                      #
#                       +          GLOBAL              +                      #
#                       +------------------------------+                      #

#                       +------------------------------+                      #
#                       +         MANDATORY            +                      #
#                       +------------------------------+                      #
define SRC_FILE :=
	$(addprefix $(SRC_DIR)/, \
		ft_mlx_pixel_put.c \
		mlx_hook.c \
		main.c
	)
endef

define ERROR_FILE :=
	$(addprefix $(SRC_DIR)/$(ERROR_DIR)/, \
		print_error.c
	)
endef
 
define RENDER_FILE :=
	$(addprefix $(SRC_DIR)/$(RENDER_DIR)/, \
		draw_column.c \
		draw_floor_and_ceiling.c \
		render.c
	)
endef
 
define INIT_FILE :=
	$(addprefix $(SRC_DIR)/$(INIT_DIR)/, \
		free_cub.c \
		init_vec.c \
		init_cub.c \
	)
endef

#                       +------------------------------+                      #
#                       +           BONUS              +                      #
#                       +------------------------------+                      #
define BONUS_SRC_FILE :=
	$(addprefix $(BONUS_DIR)/, \
		main_bonus.c
	)
endef

define BONUS_MINIMAP_FILE :=
	$(addprefix $(BONUS_DIR)/$(MINIMAP_DIR)/, \
		minimap_bonus.c
	)
endef

# Minimap
# define MINIMAP_FILE :=
#
# MINIMAP_DIR := minimap
# MINIMAP_FILE := init_minimap.c \
# 			   draw_minimap.c

# *************************************************************************** #
#                               OBJECT FILE                                   #
# *************************************************************************** #
OBJ_DIR := .obj
#                       +------------------------------+                      #
#                       +         MANDATORY            +                      #
#                       +------------------------------+                      #
OBJ_SRC := $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILE:.c=.o)))
OBJ_ERROR := $(addprefix $(OBJ_DIR)/, $(notdir $(ERROR_FILE:.c=.o)))
OBJ_INIT := $(addprefix $(OBJ_DIR)/, $(notdir $(INIT_FILE:.c=.o)))
OBJ_RENDER := $(addprefix $(OBJ_DIR)/, $(notdir $(RENDER_FILE:.c=.o)))
OBJ := $(OBJ_SRC) $(OBJ_ERROR) $(OBJ_INIT) $(OBJ_RENDER)

#                       +------------------------------+                      #
#                       +           BONUS              +                      #
#                       +------------------------------+                      #
OBJ_BONUS_SRC := $(addprefix $(OBJ_DIR)/, $(notdir $(OBJ_BONUS_SRC:.c=.o)))
OBJ_BONUS_MINIMAP := $(addprefix $(OBJ_DIR)/, $(notdir $(OBJ_BONUS_MINIMAP:.c=.o)))
OBJ_BONUS := $(OBJ_BONUS_SRC) $(OBJ_BONUS_MINIMAP)



# *************************************************************************** #
#                                  RULES                                      #
# *************************************************************************** #
all : $(PROJECT)

bonus : $(OBJ_BONUS)
	@git submodule init
	make -C $(MLX_DIR)
	make -C $(FT_DIR)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(PROJECT) $(FT_FLAG) $(MLX_FLAG) $(MATH_FLAG)

$(PROJECT) : $(OBJ)
	@git submodule init
	make -C $(MLX_DIR)
	make -C $(FT_DIR)
	$(CC) $(CFLAGS) $(OBJ) -o $(PROJECT) $(FT_FLAG) $(MLX_FLAG) $(MATH_FLAG)

# *************************************************************************** #
#                            SRC COMPILE OBJECT                               #
# *************************************************************************** #
### Compiling SRC_FILE ###
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I ./$(HEADER_DIR)  -c $< -o $@

### Compiling ERROR_FILE ###
$(OBJ_DIR)/%.o : $(SRC_DIR)/$(ERROR_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I ./$(HEADER_DIR)  -c $< -o $@

### Compiling INIT_FILE ###
$(OBJ_DIR)/%.o : $(SRC_DIR)/$(INIT_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I ./$(HEADER_DIR)  -c $< -o $@

### Compiling RENDER_FILE ###
$(OBJ_DIR)/%.o : $(SRC_DIR)/$(RENDER_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I ./$(HEADER_DIR)  -c $< -o $@

# *************************************************************************** #
#                           BONUS COMPILE OBJECT                              #
# *************************************************************************** #
### Compiling BONUS_SRC_FILE ###
$(OBJ_DIR)/%.o : $(BONUS_SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I ./$(HEADER_DIR)  -c $< -o $@

### Compiling BONUS_MINIMAP_FILE ###
$(OBJ_DIR)/%.o : $(BONUS_SRC_DIR)/$(BONUS_MINIMAP_FILE)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I ./$(HEADER_DIR)  -c $< -o $@

# *************************************************************************** #
#                             CLEAN, FCLEAN, RE                               # 
# *************************************************************************** #
fclean : clean
	rm -f $(PROJECT)
	make fclean -C $(FT_DIR)

#Suppresion des fichiers objet
clean :
	rm -f $(OBJ_DIR)/*.o
	@rm -df $(OBJ_DIR)/
	# rm -f $(BONUS_DIR)/$(OBJ_DIR)/*.o
	# @rm -df $(BONUS_DIR)/$(OBJ_DIR)/
	make clean -C $(FT_DIR)
	make clean -C $(MLX_DIR)

re : fclean all

# *************************************************************************** #
#                              CUSTOM RULES                                   #
# *************************************************************************** #
norminette :
	norminette $(FT_DIR) $(SRC_DIR) $(HEADER_DIR)

# *************************************************************************** #
#                               PHONY RULES                                   #
# *************************************************************************** #
.PHONY := bonus, all, clean, fclean
