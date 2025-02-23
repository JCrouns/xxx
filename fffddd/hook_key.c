/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:18:49 by jait-chd          #+#    #+#             */
/*   Updated: 2025/02/23 13:56:07 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int key_hook(int keycode, void *param)
{
    static char **map;
    static int rows;
    static int cols;
    static int *game_status;
    static void *mlx;
    static void *mlx_win;

    if (!map)
        map = ((void **)param)[0];
    if (!rows)
        rows = (int)(size_t)((void **)param)[1];
    if (!cols)
        cols = (int)(size_t)((void **)param)[2];
    if (!game_status)
        game_status = ((void **)param)[3];
    if (!mlx)
        mlx = ((void **)param)[4];
    if (!mlx_win)
        mlx_win = ((void **)param)[5];

    if (keycode == 53) {
        printf("Exiting the game.\n");
        exit(0);
    }

    char direction = '\0';
    if (keycode == 122)
        direction = 'W';
    if (keycode == 115)
        direction = 'S';
    if (keycode == 113)
        direction = 'A';
    if (keycode == 100)
        direction = 'D';

    if (direction != '0') {
        int move_result = move_player(map, rows, cols, direction);
        if (move_result == 1) {
            printf("Player moved!\n");
  //          print_map(map, rows, cols);
            mlx_clear_window(mlx, mlx_win);
            draw_map(mlx, mlx_win, map, rows, cols);
        } else {
            printf("Invalid move\n");
        }
    }

    return 0;
}

