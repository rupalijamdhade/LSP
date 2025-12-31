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

    if (argc != 3)
    {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    fd_src = open(argv[1], O_RDONLY);
    if (fd_src < 0)
    {
        perror("Source file open error");
        return 1;
    }

    fd_dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dest < 0)
    {
        perror("Destination file open error");
        close(fd_src);
        return 1;
    }

    while ((bytes = read(fd_src, buffer, BUF_SIZE)) > 0)
    {
        write(fd_dest, buffer, bytes);
    }

    close(fd_src);
    close(fd_dest);

    return 0;
}
