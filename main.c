#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct arguments{
    unsigned int files_count;
    char **files;
}arguments;

void parse_arguments(int argc, char **argv, arguments *args) {
    args->files = malloc(argc * sizeof(char *));
    int index = 0;

    for(int i=1; i<argc; i++) {
        if(strcmp(argv[i], "--help") == 0) {
            printf("./main <files> [--help]\n");
            exit(0);
        } else {
            args->files[index] = argv[i];
            index +=1;
        }
    }

    args->files_count = index;
}
int main(int argc, char **argv) {
    arguments args = {0};
    parse_arguments(argc, argv, &args);
    printf("%d", args.files_count);
    return 0;
}