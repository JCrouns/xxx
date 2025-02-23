/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player_position.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:17:51 by jait-chd          #+#    #+#             */
/*   Updated: 2025/02/23 13:23:31 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
int player_row = -1;
int player_col = -1;
int collected_items = 0;
int total_collectables =0;

void find_player_position(char **tab, int rows, int cols)
{
    int r = 0;
    while (r < rows)
    {
        int c = 0;
        while (c < cols)
        {
            if (tab[r][c] == PLAYER)
            {
                player_row = r;
                player_col = c;
                return;
            }
            c++;
        }
        r++;
    }
//    player_row = -1;
  // player_col = -1;
}

int move_player(char **tab, int rows, int cols, char direction)
{
    find_player_position(tab, rows, cols);

    int new_row = player_row;
    int new_col = player_col;

    if (direction == 'W' && new_row > 0 && tab[new_row - 1][new_col] != WALL) {
        new_row--;
    }
    else if (direction == 'S' && new_row < rows - 1 && tab[new_row + 1][new_col] != WALL) {
        new_row++;
    }
    else if (direction == 'A' && new_col > 0 && tab[new_row][new_col - 1] != WALL) {
        new_col--;
    }
    else if (direction == 'D' && new_col < cols - 1 && tab[new_row][new_col + 1] != WALL) {
        new_col++;
    }
    else {
        return 0;
    }

    if (tab[new_row][new_col] == COLLECTABLE) {
        collected_items++;
    }

    tab[player_row][player_col] = SPACE;
    player_row = new_row;
    player_col = new_col;
    tab[player_row][player_col] = PLAYER;

    return 1;
}

