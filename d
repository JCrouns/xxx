#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include "get_next_line.h"
#include "minilibx-linux/mlx.h"

#define PLAYER 'P'
#define BOSS 'B'
#define COLLECTABLE 'C'
#define WALL '1'
#define SPACE '0'
#define EXIT 'E'

int player_row = -1;
int player_col = -1;
int collected_items = 0;
int total_collectables = 0;

void map_check_wall(char **tab, int rows, int cols)
{
    int c = 0;
    while (c < cols)
    {
        if (tab[0][c] != WALL || tab[rows - 1][c] != WALL)
        {
            perror("Map must be surrounded by walls.\n");
            exit(1);
        }
        c++;
    }

    int r = 0;
    while (r < rows)
    {
        if (tab[r][0] != WALL || tab[r][cols - 1] != WALL)
        {
            perror("Map must be surrounded by walls.\n");
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
        perror("Must be only one player\n");
        exit(1);
    }
}

void map_check_collectables(char **tab, int rows, int cols)
{
    int collectable_count = 0;
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
        perror("error on number of collectables\n");
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
                perror("Invalid character in the map\n");
                exit(1);
            }
            c++;
        }
        r++;
    }
}

void free_map(char **map, int rows)
{
    int r = 0;
    while (r < rows)
    {
        free(map[r]);
        r++;
    }
    free(map);
}

void print_map(char **tab, int rows, int cols)
{
    int r = 0;
    while (r < rows)
    {
        printf("%s\n", tab[r]);
        r++;
    }
    printf("Collected Items: %d/%d\n", collected_items, total_collectables);
}


/*int player_row = -1;
int player_col = -1;
int collected_items = 0;
int total_collectables = 0;*/

void find_player_position(char **tab, int rows, int cols)
{
    int r = 0;
    while (r < rows)
    {
        int c = 0; // إعادة تعيين `c` لكل صف
        while (c < cols)
        {
            if (tab[r][c] == PLAYER)
            {
                player_row = r;
                player_col = c;
                return; // الخروج بمجرد العثور على اللاعب
            }
            c++;
        }
        r++;
    }
    // إذا لم يتم العثور على اللاعب
    player_row = -1;
    player_col = -1;
}

int move_player(char **tab, int rows, int cols, char direction)
{
    find_player_position(tab, rows, cols); // Update player position

    int new_row = player_row;
    int new_col = player_col;

    // Movement logic based on direction
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
        return 0; // Invalid move (hit a wall or out of bounds)
    }

    // If player moves, update map and player position
    if (tab[new_row][new_col] == COLLECTABLE) {
        collected_items++;
    }

    tab[player_row][player_col] = SPACE; // Clear old position
    player_row = new_row;
    player_col = new_col;
    tab[player_row][player_col] = PLAYER; // Update new position

    return 1; // Move was successful
}

void draw_map(void *mlx, void *mlx_win, char **tab, int rows, int cols)
{
    int x, y;
    int width = 64;
    int height = 64;
    void *img;

    char *player_path = "player.xpm";
    char *wall_path = "wall.xpm";
    char *space_path = "empty.xpm";
    char *collectable_path = "fruite.xpm";
    char *exit_path = "exit.xpm";

    for (y = 0; y < rows; y++)
    {
        for (x = 0; x < cols; x++)
        {
            if (tab[y][x] == WALL)
            {
                img = mlx_xpm_file_to_image(mlx, wall_path, &width, &height);
            }
            else if (tab[y][x] == SPACE)
            {
                img = mlx_xpm_file_to_image(mlx, space_path, &width, &height);
            }
            else if (tab[y][x] == PLAYER)
            {
                img = mlx_xpm_file_to_image(mlx, player_path, &width, &height);
            }
            else if (tab[y][x] == COLLECTABLE)
            {
                img = mlx_xpm_file_to_image(mlx, collectable_path, &width, &height);
            }
            else if (tab[y][x] == EXIT)
            {
                img = mlx_xpm_file_to_image(mlx, exit_path, &width, &height);
            }
            else
            {
                img = NULL;
            }

            if (img)
            {
                mlx_put_image_to_window(mlx, mlx_win, img, x * 64, y * 64);
                mlx_destroy_image(mlx, img);
            }
            else
            {
                fprintf(stderr, "Error: Could not load image for tile %c\n", tab[y][x]);
            }
        }
    }
}


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
    if (keycode == 122) // W key
        direction = 'W';
    if (keycode == 115) // S key
        direction = 'S';
    if (keycode == 113) // A key
        direction = 'A';
    if (keycode == 100) // D key
        direction = 'D';

    if (direction != '0') {
        int move_result = move_player(map, rows, cols, direction);
        if (move_result == 1) {
            printf("Player moved!\n");
            print_map(map, rows, cols);
            mlx_clear_window(mlx, mlx_win);
            draw_map(mlx, mlx_win, map, rows, cols);
        } else {
            printf("Invalid move\n");
        }
    }

    return 0;
}


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        perror("Number of arguments not correct");
        return EXIT_FAILURE;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("ERROR opening file");
        return EXIT_FAILURE;
    }

    char *line = NULL;
    char **map = NULL;
    int rows = 0;
    int cols = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        rows++;
        if (cols == 0)
        {
            cols = strlen(line) - 1;
        }
        free(line);
    }

    close(fd);
    fd = open(argv[1], O_RDONLY);

    if (fd < 0)
    {
        perror("ERROR reopening file");
        return EXIT_FAILURE;
    }

    map = (char **)malloc(sizeof(char *) * rows);
    if (!map)
    {
        perror("Error allocating memory for map");
        close(fd);
        return EXIT_FAILURE;
    }

    int r = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        map[r] = (char *)malloc(sizeof(char) * (cols + 1));
        if (!map[r])
        {
            perror("Error allocating memory for map row");
            close(fd);
            free_map(map, r);
            return EXIT_FAILURE;
        }
        strncpy(map[r], line, cols);
        map[r][cols] = '\0';
        free(line);
        r++;
    }

    close(fd);

    map_check_wall(map, rows, cols);
    map_check_player(map, rows, cols);
    map_check_collectables(map, rows, cols);
    ghayermarghoub_fiha(map, rows, cols);
    printf("Map checked and it is success!\n");

    find_player_position(map, rows, cols);

    int game_status = 0;
    void *mlx;
    void *mlx_win;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, cols * 64, rows * 64, "so_long");

    draw_map(mlx, mlx_win, map, rows, cols);

    void *params[6];
    params[0] = map;
    params[1] = (void *)(size_t)rows;
    params[2] = (void *)(size_t)cols;
    params[3] = &game_status;
    params[4] = mlx;
    params[5] = mlx_win;

    mlx_key_hook(mlx_win, key_hook, params);

    mlx_loop(mlx);

    free_map(map, rows);

    return EXIT_SUCCESS;
    }
