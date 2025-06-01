#include<stdio.h>
#include<string.h>
typedef struct arguments{
    unsigned int files_count;
    char **files;
}arguments;

void parse_arguments(int argc, char **argv, arguments *args) {
    for(int i=1; i<argc; i++) {
        if(!strcmp(argv[i], "help")) {
            printf("HELP!!!!");
        }
    }
}
int main(int argc, char **argv) {
    printf("HelloWorld\n");
    arguments *args;
    parse_arguments(argc, argv, args);
    return 0;
}