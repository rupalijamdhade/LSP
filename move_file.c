#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() 
{
    char src[100], dest[100], srcpath[200], destpath[200], buffer[1024];
    DIR *dp;
    struct dirent *entry;
    struct stat st;
    int count = 0;

    printf("Enter source directory: ");
    scanf("%s", src);
    printf("Enter destination directory: ");
    scanf("%s", dest);

    dp = opendir(src);
    if (dp == NULL) {
        perror("opendir failed");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL) {
        printf(srcpath, "%s/%s", src, entry->d_name);
        printf(destpath, "%s/%s", dest, entry->d_name);

        stat(srcpath, &st);
        if (S_ISREG(st.st_mode)) {
            if (rename(srcpath, destpath) != 0) {
                int fd1 = open(srcpath, O_RDONLY);
                int fd2 = open(destpath, O_WRONLY | O_CREAT | O_TRUNC, st.st_mode);
                int bytes;

                while ((bytes = read(fd1, buffer, sizeof(buffer))) > 0)
                    write(fd2, buffer, bytes);

                close(fd1);
                close(fd2);
                unlink(srcpath);
            }
            count++;
        }
    }

    closedir(dp);
    printf("Total files moved: %d\n", count);
    return 0;
}
