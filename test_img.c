#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "mlx.h"

# define WINDOW_WIDTH 800
#define	WINDOW_HEIGHT 500

typedef struct s_img
{
	void	*mlx_img;
	int		i;
	int		j;
}	t_img;

typedef	struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
}	t_data;

int	handle_no_event(void *data)
{
	/* This function needs to exist, but it is useless for the moment */
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "So_Long");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);	
		return (1);
	}
	data.img.mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, "zombie_front1.xpm", &data.img.i, &data.img.j);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 100, 100);

	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	mlx_key_hook(data.win_ptr, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);

	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}