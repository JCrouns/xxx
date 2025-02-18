/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:26:19 by jait-chd          #+#    #+#             */
/*   Updated: 2025/02/18 01:06:49 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void map_check_wall(char **tab, int rows, int cols)
{
    int c = 0;
    while (c < cols)
    {
        if (tab[0][c] != WALL || tab[rows - 1][c] != WALL)
        {
            write(2 , "Map must be surrounded by walls \n" , 33);
            exit(1);
        }
        c++;
    }

    int r = 0;
    while (r < rows)
    {
        if (tab[r][0] != WALL || tab[r][cols - 1] != WALL)
        {
            write(2 , "Map must be surrounded by walls.\n", 33);
            exit(1);
        }
        r++;
    }
}

void map_check_player(char **tab, int rows, int cols)
{
    int player_count = 0;
    int r = 0;
    while (r < rows)
    {
        int c = 0;
        while (c < cols)
        {
            if (tab[r][c] == PLAYER)
            {
                player_count++;
            }
            c++;
        }
        r++;
    }

    if (player_count != 1)
    {
        write(2 , "Must be only one player\n" , 24);
        exit(1);
    }
}

void map_check_collectables(char **tab, int rows, int cols)
{
    int collectable_count = 0;
    int total_collectables = 0;
    int r = 0;
    while (r < rows)
    {
        int c = 0;
        while (c < cols)
        {
            if (tab[r][c] == COLLECTABLE)
            {
                collectable_count++;
            }
            c++;
        }
        r++;
    }

    if (collectable_count < 1)
    {
        write(2 , "error on number of collectables\n", 33);
        exit(1);
    }
    total_collectables = collectable_count;
}

void ghayermarghoub_fiha(char **tab, int rows, int cols)
{
    int r = 0;
    while (r < rows)
    {
        int c = 0;
        while (c < cols)
        {
            char ch = tab[r][c];
            if (ch != PLAYER && ch != COLLECTABLE && ch != WALL && ch != SPACE && ch != EXIT)
            {
                write(2 ,"Invalid char\n" , 14);
                exit(1);
            }
            c++;
        }
        r++;
    }
}

void process_map(char **map, int rows, int cols) {
    map_check_wall(map, rows, cols);
    map_check_player(map, rows, cols);
    map_check_collectables(map, rows, cols);
    ghayermarghoub_fiha(map, rows, cols);
}

