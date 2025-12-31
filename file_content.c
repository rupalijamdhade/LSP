#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    char src[100], dest[100], buffer[1024];
    int fd1, fd2, bytes;
    struct stat st;

    printf("Enter source file: ");
    scanf("%s", src);
    printf("Enter destination file: ");
    scanf("%s", dest);

    fd1 = open(src, O_RDONLY);
    if (fd1 == -1) {
        perror("Source open failed");
        return 1;
    }

    stat(src, &st);

    fd2 = open(dest, O_WRONLY | O_CREAT | O_TRUNC, st.st_mode);
    if (fd2 == -1) {
        perror("Destination open failed");
        return 1;
    }

    while ((bytes = read(fd1, buffer, sizeof(buffer))) > 0)
        write(fd2, buffer, bytes);

    printf("File copied successfully\n");

    close(fd1);
    close(fd2);
    return 0;
}
