/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jait-chd <jait-chd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:18:02 by jait-chd          #+#    #+#             */
/*   Updated: 2025/02/18 23:01:56 by jait-chd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"



int move_player(char **tab, int rows, int cols, char direction) {
    //int collected_items = 0;
   // int total_collectables = 0;

    int new_row = player_row;
    int new_col = player_col;
    int row = 0;
    int col = 0;

    if (tab == NULL) {
        printf("Error: tab is NULL.\n");
        return -1;
    }

    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        printf("Error: Invalid row or column index.\n");
        return -1;
    }

    if (direction == 'W') {
        printf("move w\n");
        new_row--;
    } else if (direction == 'S') {
        printf("move s\n");
        new_row++;
    } else if (direction == 'A') {
        printf("move a\n");
        new_col--;
    } else if (direction == 'D') {
        printf("move d\n");
        new_col++;
    }

    //if (new_row < 0 || new_row >= rows || new_col < 0 || new_col >= cols || tab[new_row][new_col] == WALL) {
      //  printf("Invalid move: Out of bounds or hitting a wall.\n");
        //return 0;
    //}

    //tab[row][col] = '0';

    //if (tab[new_row][new_col] == 'C') {
      //  collected_items++;
    //}

    //tab[new_row][new_col] = 'P';
    return 0;
}

