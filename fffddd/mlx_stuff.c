/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:18:21 by jait-chd          #+#    #+#             */
/*   Updated: 2025/02/20 20:13:15 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void draw_map(void *mlx, void *mlx_win, char **tab, int rows, int cols)
{
    int width = 64;
    int height = 64;
    void *img;

    int y = 0;
    while (y < rows)
    {
        int x = 0;
        while (x < cols)
        {
            if (tab[y][x] == WALL)
                img = mlx_xpm_file_to_image(mlx, "xpm_files/wall.xpm", &width, &height);
            else if (tab[y][x] == SPACE)
                img = mlx_xpm_file_to_image(mlx, "xpm_files/empty.xpm", &width, &height);
            else if (tab[y][x] == PLAYER)
                img = mlx_xpm_file_to_image(mlx, "xpm_files/player.xpm", &width, &height);
            else if (tab[y][x] == COLLECTABLE)
                img = mlx_xpm_file_to_image(mlx, "xpm_files/fruite.xpm", &width, &height);
            else if (tab[y][x] == EXIT)
                img = mlx_xpm_file_to_image(mlx, "xpm_files/exit.xpm", &width, &height);
            else
                img = NULL;

            if (img)
            {
                mlx_put_image_to_window(mlx, mlx_win, img, x * 64, y * 64);
                mlx_destroy_image(mlx, img);
            }
            else
                write(2, "Error: Could not load image\n", 27);

            x++;
        }
        y++;
    }
}



void mlx_stuff(char **map, int rows, int cols) {
    void *mlx;
    void *mlx_win;
    void *img;
    void *params[6];
    int status_of_game = 0;
    params[0] = map;
    params[1] = (void **)(size_t)rows;
    params[2] = (void **)(size_t)cols;
    params[3] = &status_of_game;
    params[4] = mlx;
    params[5] = mlx_win;
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx , cols*64 , rows*64 , "so_long");
    draw_map(mlx , mlx_win, map , rows, cols);
    mlx_key_hook(mlx_win , key_hook, params);
    mlx_loop(mlx);
}
