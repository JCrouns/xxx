#include "so_long.h"

void read_map(int c, char **v ) {
    int fd;
    int rows ;
    int cols ;
    char *line;
    fd = open(v[1] , O_RDONLY);
    while((line = get_next_line(fd)) != NULL) {
         rows++;
         if(cols = 0)
             cols = strlen(line) -1;
         printf("%s" , line);
         free(line);
    }
    close(fd);
}


