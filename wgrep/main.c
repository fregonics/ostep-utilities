#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void validate_input(int argc, char **argv) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

}

FILE *open_file(char *filename) {
    printf("%s", filename);
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    return file;

}

char *str_replace_char(char *str, ssize_t str_size, char to_replace, char replace_with) {
    for(int i = 0; i < str_size; i ++) {
        if(str[i] == to_replace) {
            str[i] = replace_with;
        }
    }

    return str;
}

char *str_rm_chars(char *str, ssize_t str_size, char *to_remove, ssize_t to_remove_size, int *removed_count) {
    int i, j = 0;
    int displacement = 0;

    for(i = 0; i < str_size; i ++) {
        for(j = 0; j < to_remove_size; j ++) {

            if(str[i] == to_remove[j]) {
                displacement ++;
                break;
            }

        }

        if((i + displacement) >= str_size) break;

        str[i] = str[i + displacement];
    }
    
    char *new_str = realloc(str, str_size - displacement);

    (*removed_count) = displacement;
    return new_str;
}

char *str_trim(char *str, ssize_t *str_size) {
    const char to_remove[] = {'\n', '\t'};
    int removed_count = 0;
    
    char *new_str = str_rm_chars(str, (*str_size), to_remove, 2, &removed_count);
    
    (*str_size) = (*str_size) - ((ssize_t) removed_count);
    return new_str;
}

int line_contains_str(char *line, ssize_t line_size, char *str, int str_size) {
   
    long current_index = 0;
    long initial_position = 0;
    int found = 0;

    while ( !found && (initial_position < line_size) )
    {

        if(line[current_index] == str[current_index - initial_position]) {
            
            if((current_index - initial_position + 1) == str_size) {    
                found = 1;
            }

            current_index ++;
        } else {
            current_index ++;
            initial_position = current_index;
        }

        
    }
    
    return found;

}

void search_expression_and_print(char *expr, int expr_length, FILE *stream) {

    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    fwrite("\n", 1, 1, stdout);
    
    while ((nread = getline(&line, &len, stream)) != -1) {
        
        if (line_contains_str(line, nread, expr, expr_length)) {
            //fwrite("\n", 1, 1, stdout);
            line = str_trim(line, &nread);
            fwrite(line, nread, 1, stdout);
            
            if(line[len - 2] != '\n') {
                fwrite("\n", 1, 1, stdout);
            }
        }
        
    }

    free(line);
    
}

int main(int argc, char *argv[])
{
    FILE *stream;
    
    int expr_length = strlen(argv[1]);

    stream = open_file(argv[2]);
    search_expression_and_print(argv[1], expr_length, stream);
    
    fclose(stream);
    exit(EXIT_SUCCESS);
}
