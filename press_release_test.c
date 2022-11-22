#include "mlx.h"
#include "mlx_int.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 500

typedef struct s_data
{
    void    *mlx_ptr;
    void    *win_ptr;
}   t_data;

int handle_no_event(void *data)
{
    return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);

	printf("Keypress: %d\n", keysym);
	return (0);
}

int	handle_keyrelease(int keysym, void *data)
{
	printf("Keyrelease: %d\n", keysym);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My first window!");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (1);
	}

	/* Setup hooks */ 
	mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
	/* trocou a função mlx_key_hook pela função mlx_hook, por ser mais genérica */
	
	/* função ocorre qdo ESC é pressionada */
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data); /* ADDED */
	/* função ocorre qdo ESC é liberada */
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data); /* CHANGED */

	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}