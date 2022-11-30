#include "mlx.h"

int	main(void)
{
	void	*mlx;
	void	*img;
	void	*mlx_win;
	int		i;
	int		j;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "So_Long");
	img = mlx_xpm_file_to_image(mlx, "zombie_front1.xpm", &i, &j);
	mlx_put_image_to_window(mlx, mlx_win, img, 250, 250);
	mlx_loop(mlx);
}