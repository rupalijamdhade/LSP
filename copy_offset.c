#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    int fd_src, fd_dest;
    char buffer[BUF_SIZE];
    ssize_t bytes;
    int offset;

    if (argc != 4)
    {
        printf("Usage: %s <source> <destination> <offset>\n", argv[0]);
        return 1;
    }

    offset = atoi(argv[3]);

    fd_src = open(argv[1], O_RDONLY);
    fd_dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    lseek(fd_src, offset, SEEK_SET);

    while ((bytes = read(fd_src, buffer, BUF_SIZE)) > 0)
    {
        write(fd_dest, buffer, bytes);
    }

    close(fd_src);
    close(fd_dest);

    return 0;
}
