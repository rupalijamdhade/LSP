#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    int fd_out, fd_in;
    char buffer[BUF_SIZE];
    ssize_t bytes;

    if (argc < 3)
    {
        printf("Usage: %s <output_file> <input_files...>\n", argv[0]);
        return 1;
    }

    fd_out = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    for (int i = 2; i < argc; i++)
    {
        fd_in = open(argv[i], O_RDONLY);

        while ((bytes = read(fd_in, buffer, BUF_SIZE)) > 0)
        {
            write(fd_out, buffer, bytes);
        }
        close(fd_in);
    }

    close(fd_out);
    return 0;
}
