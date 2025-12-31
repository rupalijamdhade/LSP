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
    off_t offset = 0;

    if (argc != 3)
    {
        printf("Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    fd_src = open(argv[1], O_RDONLY);
    fd_dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    while ((bytes = pread(fd_src, buffer, BUF_SIZE, offset)) > 0)
    {
        pwrite(fd_dest, buffer, bytes, offset);
        offset += bytes;
    }

    close(fd_src);
    close(fd_dest);

    return 0;
}
