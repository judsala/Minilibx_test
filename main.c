#include "mlx_int.h"
#include "mlx.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 500

/* função para fechar a janela com esc */
typedef struct s_data
{
    void    *mlx_ptr;
    void    *win_ptr;
}   t_data;

/* Esta função precisa existir mas não será usada no momento */
int handle_no_event(void *data)
{
    return (0);
}

/* função que é ativada toda vez q a tecla for (des)pressionada */
int handle_input(int keysym, t_data *data)
{
    if (keysym == XK_Escape)
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    return (0);    
}

int main(void)
{
    t_data  data;

    data.mlx_ptr = mlx_init();
    if (data.mlx_ptr == NULL)
        return (1);
    data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Window da Ju");
    if (data.win_ptr == NULL)
    {
        free(data.win_ptr);
        return (1);
    }
    
    /* Esse hook é acionado qdo não há nenhum evento processado */
    mlx_loop_hook(data.mlx_ptr, &handle_no_event, &data);
    /* Esse hook obtém o evento */
    mlx_key_hook(data.win_ptr, &handle_input, &data);

    /* O loop mantém a janela aberto e pára qdo a tecla ESC é (des)pressionada, pois a janela será destruída */
    mlx_loop(data.mlx_ptr);

    /* Sai do loop qdo não há mais janela e executa esse código */
    mlx_destroy_display(data.mlx_ptr);
    free(data.mlx_ptr);
}