#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

void print_permissions(mode_t mode)
{
    char perm[11] = "----------";

    if (S_ISDIR(mode)) perm[0] = 'd';
    else if (S_ISLNK(mode)) perm[0] = 'l';

    if (mode & S_IRUSR) perm[1] = 'r';
    if (mode & S_IWUSR) perm[2] = 'w';
    if (mode & S_IXUSR) perm[3] = 'x';
    if (mode & S_IRGRP) perm[4] = 'r';
    if (mode & S_IWGRP) perm[5] = 'w';
    if (mode & S_IXGRP) perm[6] = 'x';
    if (mode & S_IROTH) perm[7] = 'r';
    if (mode & S_IWOTH) perm[8] = 'w';
    if (mode & S_IXOTH) perm[9] = 'x';

    printf("%s", perm);
}

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *entry;
    struct stat sb;
    char path[512];

    if (argc != 2)
    {
        printf("Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    dp = opendir(argv[1]);
    if (!dp)
    {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL)
    {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        sprintf(path, "%s/%s", argv[1], entry->d_name);

        lstat(path, &sb);

        printf("Name: %s\n", entry->d_name);

        printf("Type: ");
        if (S_ISREG(sb.st_mode)) printf("File\n");
        else if (S_ISDIR(sb.st_mode)) printf("Directory\n");
        else if (S_ISLNK(sb.st_mode)) printf("Link\n");
        else printf("Other\n");

        printf("Size: %ld bytes\n", sb.st_size);
        printf("Permissions: ");
        print_permissions(sb.st_mode);
        printf("\n");

        printf("Last Modified: %s\n", ctime(&sb.st_mtime));
        printf("--------------------------------\n");
    }

    closedir(dp);
    return 0;
}
