#include "so_long.h"

void check_arg_count(int c) {
    if (c != 2) {
        write(2, "Number of args are not on point\n", 32);
        exit(EXIT_FAILURE);
    }
}

int open_file(char *file_name) {
    int fd = open(file_name, O_RDONLY);
    if (fd < 0) {
        perror("ERROR opening file");
        exit(EXIT_FAILURE);
    }
    return fd;
}
void print_map(char **tab, int rows, int cols)
{
    int r = 0;
    while (r < rows)
    {
        printf("%s\n", tab[r]);
        r++;
    }

}


int main(int c, char **v) {
    char **map;
    int cols = 0;
    int rows = 0;
    char *line;
    check_arg_count(c);
    int fd = open_file(v[1]);
    while ((line = get_next_line(fd)) != NULL) {
        rows++;
        if (cols == 0) {
            cols = strlen(line) - 1;
        }
        printf("%s", line);
        free(line);
    }


    close(fd);
    int r = 0;
    map = (char **)malloc(sizeof(char *) * rows);
    if(!map) {
        perror("error allocating memory for map");
    }
    fd = open_file(v[1]);
    while ((line = get_next_line(fd)) != NULL) {
        map[r] = (char *)malloc(sizeof(char) * (cols + 1));
        if (!map[r]) {
            perror("Error allocating memory for map row");
            exit(EXIT_FAILURE);
        }
        strncpy(map[r], line, cols);
        map[r][cols] = '\0';
        free(line);
        r++;
    }
    close(fd);
    process_map(map , rows, cols);
    printf("Map checked it is too good except exit\n");
    find_player_position(map, rows, cols);
    mlx_stuff(map, rows, cols);
    return 0;
}

