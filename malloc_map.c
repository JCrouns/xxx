#include "so_long.h"

void malloc_map(int c, char **v) {
    int r = 0;
    char *line;
    int rows;
    char **map;
    int cols;
    int fd = open(v[1] , O_RDONLY);
    map = (char **)malloc(sizeof(char *) * rows );
    while((line = get_next_line(fd)) != NULL) {
        map[r] = (char *)malloc(sizeof(char *) * cols +1);
        strncpy(map[r] , line , cols);
        map[r][cols] = '\0';
        free(line);
        r++;
    }
    //3nduii chui leaks khassnui men be3d ncruiyuii xui func bach nloopi 3la map[]][] enfreeyihom
    //also khassnui lprotection ta3 fd ...
        free(map);
    close(fd);
}

