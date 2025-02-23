#include "so_long.h"

/*int player_row = -1;
int player_col = -1;
int collected_items = 0;
int total_collectables = 0;
*/

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
    void process_map(char **map , int rows , int cols);
    printf("Map checked and it is success!\n");

    find_player_position(map, rows, cols);
    mlx_stuff(map ,rows ,cols);

    free_map(map, rows);

    return EXIT_SUCCESS;
    }
