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

#define MAX_LEN 128

int read_file(char *path, char **buffer) {
    int tmp_size = 0;
    int tmp_capacity = MAX_LEN;
    char *tmp = malloc(tmp_capacity * sizeof(char));
    if(tmp==NULL) {
        perror("malloc failed");
        exit(1);
    }
    FILE *f = fopen(path, "r");
    if(f == NULL) {
        perror("fopen failed");
        exit(1);
    }

    int size = 0;
    do {
        if(tmp_size + tmp_capacity >= tmp_capacity) {
            tmp_capacity*=2;
            tmp = realloc(tmp,tmp_capacity);
            if(tmp==NULL) {
                perror("realloc failed");
                exit(1);
            }
        }

        size = fread(tmp + tmp_size, sizeof(char), MAX_LEN, f);
        tmp_size += size;
    }while(size > 0);

    fclose(f);
    tmp[tmp_size] = '\0';
    *buffer = tmp; 

    return tmp_size;
}

int main(int argc, char **argv) {
    arguments args = {0};
    parse_arguments(argc, argv, &args);

    char *buffer = NULL;
    int buffer_size = 0;
    for(int i=0; i<args.files_count; i++) {
        char* content = NULL;
        int size = read_file(args.files[i], &content);

        buffer = realloc(buffer, buffer_size + size + 1);
        memcpy(buffer+buffer_size, content, size);
        buffer_size += size;
        buffer[buffer_size] = '\0';

        free(content);
    }

    free(args.files);
    // printf("%s", buffer);
    fwrite(buffer, sizeof(char), buffer_size, stdout);
    free(buffer);
    
    return 0;
}