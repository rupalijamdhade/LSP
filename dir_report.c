#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

long total_size = 0;
int file_count = 0;
int dir_count = 0;
char largest_file[256];
long largest_size = 0;

void scan(const char *path)
{
    DIR *dp;
    struct dirent *entry;
    struct stat sb;
    char fullpath[512];

    dp = opendir(path);
    if (!dp) return;

    dir_count++;

    while ((entry = readdir(dp)) != NULL)
    {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        sprintf(fullpath, "%s/%s", path, entry->d_name);
        lstat(fullpath, &sb);

        if (S_ISDIR(sb.st_mode))
        {
            scan(fullpath);
        }
        else if (S_ISREG(sb.st_mode))
        {
            file_count++;
            total_size += sb.st_size;

            if (sb.st_size > largest_size)
            {
                largest_size = sb.st_size;
                strcpy(largest_file, entry->d_name);
            }
        }
    }
    closedir(dp);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    scan(argv[1]);

    printf("Files : %d\n", file_count);
    printf("Dirs  : %d\n", dir_count);
    printf("Total Size : %ld bytes\n", total_size);
    printf("Largest : %s (%ld bytes)\n", largest_file, largest_size);

    return 0;
}
