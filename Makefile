# *************************************************************************** #
#                                COMPILATION                                  #
# *************************************************************************** #
CC := cc
CFLAGS := -Wall -Wextra -Werror -g3

# *************************************************************************** #
#                            PROJECT CONFIGURATION                            #
# *************************************************************************** #
PROJECT := cub3D
BONUS := cub3D_bonus
PROJECT_DIR := ./

### SRC_DIR ###
SRC_DIR := src
ERROR_DIR := error
INIT_DIR := init
RENDER_DIR := render
MLX_DIR := mlx

### BONUS_DIR ###
BONUS_DIR := bonus
MINIMAP_DIR := minimap
ROTATE_DIR := rotate
DOOR_DIR := door

# *************************************************************************** #
#                                 INCLUDES                                    #
# *************************************************************************** #
HEADER_DIR := includes
HEADER_BONUS_DIR := includes

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
define SRC_FILE :=
	$(addprefix $(SRC_DIR)/, \
		copy_map.c
	)
endef

define ERROR_FILE :=
	$(addprefix $(SRC_DIR)/$(ERROR_DIR)/, \
		print_error.c
	)
endef
 
define INIT_FILE :=
	$(addprefix $(SRC_DIR)/$(INIT_DIR)/, \
		init_vec.c \
		load_texture.c
	)
endef

define RENDER_FILE :=
	$(addprefix $(SRC_DIR)/$(RENDER_DIR)/, \
		draw_column.c \
		draw_floor_and_ceiling.c
	)
endef

define MLX_FILE :=
	$(addprefix $(SRC_DIR)/$(MLX_DIR)/, \
		ft_mlx_pixel_put.c \
		rotate.c \
		move.c
	)
endef
 
#                       +------------------------------+                      #
#                       +         MANDATORY            +                      #
#                       +------------------------------+                      #
define MANDATORY_SRC_FILE :=
	$(addprefix $(SRC_DIR)/, \
		main.c
	)
endef

define MANDATORY_INIT_FILE :=
	$(addprefix $(SRC_DIR)/$(INIT_DIR)/, \
		free_cub.c \
		init_cub.c
	)
endef

define MANDATORY_RENDER_FILE :=
	$(addprefix $(SRC_DIR)/$(RENDER_DIR)/, \
		render.c
	)
endef

define MANDATORY_MLX_FILE :=
	$(addprefix $(SRC_DIR)/$(MLX_DIR)/, \
		mlx_hook.c
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

define BONUS_ROTATE_FILE :=
	$(addprefix $(BONUS_DIR)/$(ROTATE_DIR)/, \
		rotate_bonus.c		
	)
endef

define BONUS_MINIMAP_FILE :=
	$(addprefix $(BONUS_DIR)/$(MINIMAP_DIR)/, \
		init_minimap_bonus.c \
		draw_minimap_bonus.c
	)
endef

define BONUS_DOOR_FILE :=
	$(addprefix $(BONUS_DIR)/$(DOOR_DIR)/, \
		door_bonus.c
	)
endef

define BONUS_INIT_FILE :=
	$(addprefix $(BONUS_DIR)/$(INIT_DIR)/, \
		init_cub_bonus.c \
		free_cub_bonus.c
	)
endef

define BONUS_RENDER_FILE :=
	$(addprefix $(BONUS_DIR)/$(RENDER_DIR)/, \
		get_hit_pos_bonus.c \
		check_hit_bonus.c \
		correct_perp_wall_dist_bonus.c \
		render_bonus.c
	)
endef

# *************************************************************************** #
#                               OBJECT FILE                                   #
# *************************************************************************** #
OBJ_DIR := .obj
#                       +------------------------------+                      #
#                       +          GLOBAL              +                      #
#                       +------------------------------+                      #
OBJ_SRC := $(addprefix $(OBJ_DIR)/, $(notdir $(SRC_FILE:.c=.o)))
OBJ_ERROR := $(addprefix $(OBJ_DIR)/, $(notdir $(ERROR_FILE:.c=.o)))
OBJ_INIT := $(addprefix $(OBJ_DIR)/, $(notdir $(INIT_FILE:.c=.o)))
OBJ_RENDER := $(addprefix $(OBJ_DIR)/, $(notdir $(RENDER_FILE:.c=.o)))
OBJ_MLX := $(addprefix $(OBJ_DIR)/, $(notdir $(MLX_FILE:.c=.o)))
OBJ := $(OBJ_SRC) $(OBJ_ERROR) $(OBJ_INIT) $(OBJ_RENDER) $(OBJ_MLX)

#                       +------------------------------+                      #
#                       +         MANDATORY            +                      #
#                       +------------------------------+                      #
OBJ_MANDATORY_SRC := $(addprefix $(OBJ_DIR)/, \
					$(notdir $(MANDATORY_SRC_FILE:.c=.o)))
OBJ_MANDATORY_INIT := $(addprefix $(OBJ_DIR)/, \
					$(notdir $(MANDATORY_INIT_FILE:.c=.o)))
OBJ_MANDATORY_RENDER := $(addprefix $(OBJ_DIR)/, \
					$(notdir $(MANDATORY_RENDER_FILE:.c=.o)))
OBJ_MANDATORY_MLX := $(addprefix $(OBJ_DIR)/, \
					 $(notdir $(MANDATORY_MLX_FILE:.c=.o)))
OBJ_MANDATORY := $(OBJ) $(OBJ_MANDATORY_SRC) $(OBJ_MANDATORY_INIT) \
				$(OBJ_MANDATORY_RENDER) $(OBJ_MANDATORY_MLX)

#                       +------------------------------+                      #
#                       +           BONUS              +                      #
#                       +------------------------------+                      #
OBJ_BONUS_SRC := $(addprefix $(OBJ_DIR)/, $(notdir $(BONUS_SRC_FILE:.c=.o)))
OBJ_BONUS_INIT := $(addprefix $(OBJ_DIR)/, $(notdir $(BONUS_INIT_FILE:.c=.o)))
OBJ_BONUS_RENDER := $(addprefix $(OBJ_DIR)/, $(notdir $(BONUS_RENDER_FILE:.c=.o)))
OBJ_BONUS_MINIMAP := $(addprefix $(OBJ_DIR)/, $(notdir $(BONUS_MINIMAP_FILE:.c=.o)))
OBJ_BONUS_ROTATE := $(addprefix $(OBJ_DIR)/, $(notdir $(BONUS_ROTATE_FILE:.c=.o)))
OBJ_BONUS_DOOR := $(addprefix $(OBJ_DIR)/, $(notdir $(BONUS_DOOR_FILE:.c=.o)))
OBJ_BONUS := $(OBJ) $(OBJ_BONUS_SRC) $(OBJ_BONUS_INIT) $(OBJ_BONUS_RENDER) \
			 $(OBJ_BONUS_MINIMAP) $(OBJ_BONUS_ROTATE) $(OBJ_BONUS_DOOR)


# *************************************************************************** #
#                                  RULES                                      #
# *************************************************************************** #
all : $(PROJECT)

bonus : $(OBJ_BONUS)
	@git submodule init
	make -C $(MLX_DIR)
	make -C $(FT_DIR)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(BONUS) $(FT_FLAG) $(MLX_FLAG) $(MATH_FLAG)

$(PROJECT) : $(OBJ_MANDATORY)
	@git submodule init
	make -C $(MLX_DIR)
	make -C $(FT_DIR)
	$(CC) $(CFLAGS) $(OBJ_MANDATORY) -o $(PROJECT) $(FT_FLAG) $(MLX_FLAG) $(MATH_FLAG)

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

### Compiling MLX_FILE ###
$(OBJ_DIR)/%.o : $(SRC_DIR)/$(MLX_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I ./$(HEADER_DIR)  -c $< -o $@

# *************************************************************************** #
#                         MANDATORY COMPILE OBJECT                            #
# *************************************************************************** #

# *************************************************************************** #
#                           BONUS COMPILE OBJECT                              #
# *************************************************************************** #
### Compiling BONUS_SRC_FILE ###
$(OBJ_DIR)/%.o : $(BONUS_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I ./$(HEADER_DIR)  -c $< -o $@

### Compiling BONUS_INIT_FILE ###
$(OBJ_DIR)/%.o : $(BONUS_DIR)/$(INIT_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I ./$(HEADER_DIR)  -c $< -o $@

### Compiling BONUS_RENDER_FILE ###
$(OBJ_DIR)/%.o : $(BONUS_DIR)/$(RENDER_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I ./$(HEADER_DIR)  -c $< -o $@

### Compiling BONUS_MINIMAP_FILE ###
$(OBJ_DIR)/%.o : $(BONUS_DIR)/$(MINIMAP_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I ./$(HEADER_DIR)  -c $< -o $@

### Compiling BONUS_DOOR ###
$(OBJ_DIR)/%.o : $(BONUS_DIR)/$(DOOR_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I ./$(HEADER_DIR)  -c $< -o $@

### Compiling BONUS_ROTATE_FILE ###
$(OBJ_DIR)/%.o : $(BONUS_DIR)/$(ROTATE_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I ./$(HEADER_DIR)  -c $< -o $@

# *************************************************************************** #
#                             CLEAN, FCLEAN, RE                               # 
# *************************************************************************** #
fclean : clean
	rm -f $(PROJECT)
	rm -f $(BONUS)
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
	norminette $(FT_DIR) $(SRC_DIR) $(HEADER_DIR) $(BONUS_DIR)

recub :
	rm -rf ./.obj/
	make

# *************************************************************************** #
#                               PHONY RULES                                   #
# *************************************************************************** #
.PHONY := bonus, all, clean, fclean
