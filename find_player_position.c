/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player_position.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:17:51 by jait-chd          #+#    #+#             */
/*   Updated: 2025/02/18 23:24:10 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//int player_row ;
//int player_col;
//int collected_items =  0;
//int total_collectables = 0;

int find_player_row(char **tab, int rows, int cols)
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
            }
            c++;
        }
        r++;
    }
    return player_row;
}
int find_player_col(char **tab, int rows, int cols)
{
    int r = 0;
    while (r < rows)
    {
        int c = 0;
        while (c < cols)
        {
            if (tab[r][c] == PLAYER)
            {
                player_col = c;
            }
            c++;
        }
        r++;
    }
    return player_col;
}

