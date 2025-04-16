#
#

NOM = libmlx.a
SRC = mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m \
      mlx_xpm.c mlx_int_str_to_wordtab.c mlx_png.c mlx_mouse.m

OBJ1 = $(SRC:.c=.o)
OBJ  = $(OBJ1:.m=.o)

CFLAGS += -O2 -DSTRINGPUTX11 -DGL_SILENCE_DEPRECATION -Wno-deprecated-non-prototype -Wno-deprecated-declarations

all: $(NOM)

$(NOM): $(OBJ)
	ar -r $(NOM) $(OBJ)
	ranlib $(NOM)

clean:
	rm -f $(NOM) $(OBJ) *~
	rm -f mlx_app

re: clean all
