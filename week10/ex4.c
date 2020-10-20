#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define PATH "tmp/"


void list_all_hardlinks(ino_t inode_number) {
    char *result = NULL;

    DIR *dir = opendir(PATH);
    if (!dir) {
        printf("Error while opening directory '%s'", PATH);
        return;
    }
    struct dirent *dp;
    char *filepath = NULL;
    while ( (dp = readdir(dir)) ) {
        int new_len = strlen(PATH) + strlen(dp->d_name);
        filepath = realloc(filepath, (new_len)*(sizeof(char)) );
        strcpy(filepath, PATH);
        strcat(filepath, dp->d_name);

        struct stat* statistics = malloc(sizeof(struct stat));
        if (stat(filepath, statistics) == 0 && statistics->st_ino == inode_number) {
            int new_len2;
            if (result != NULL && result != NULL) {
                new_len2 = strlen(result) + strlen(dp->d_name) + 1;
            }
            else {
                new_len2 = 255*2+1;
            }
            result = realloc(result, (new_len2)*sizeof(char) );
            strcat(result, dp->d_name);
            strcat(result, " ");
        }
    }
    printf("%s\n", result);
    free(result);
    return;
}

int main() {
    DIR *dir = opendir(PATH);
    if (!dir) {
        printf("Error while opening directory '%s'", PATH);
        return -1;
    }
    struct dirent *dp;
    char *filepath = NULL;
    while ( (dp = readdir(dir)) ) {
        filepath = realloc(filepath, (strlen(PATH) + strlen(dp->d_name))*(sizeof(char)) );
        strcpy(filepath, PATH);
        strcat(filepath, dp->d_name);

        struct stat* statistics = malloc(sizeof(struct stat));
        if (stat(filepath, statistics) == 0) {
            printf("All names that point to inode %ld: ", statistics->st_ino);
            list_all_hardlinks(statistics->st_ino);
        }
    }
    free(filepath);
    return 0;
}