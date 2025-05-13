#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

# define MAX_LEN 300

void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void hex_to_ascii(const char *hex_input, char *output, int max_output_len){
    char buffer[MAX_LEN];
    strncpy(buffer, hex_input, sizeof(buffer)-1);
    buffer[sizeof(buffer)-1] = '\0';

    char *token = strtok(buffer, ":");
    int index = 0;
    while(index < max_output_len - 1 && token != NULL){
        output[index++] = (char)strtoul(token, NULL, 16);
        token = strtok(NULL, ":");
    }

    for(int i = index; i<max_output_len; i++){
        output[i] = '\0';
    }
}

void prepare_string(const char *input, char *output, int input_type, int max_output_len){
    if(input_type == 1){
        strncpy(output, input, max_output_len-1);
        output[max_output_len-1] = '\0';
    }else{
        hex_to_ascii(input, output, max_output_len);
    }
}

int main(){
    char raw_input[MAX_LEN];
    char source_check[MAX_LEN];
    char gen_check[MAX_LEN];
    int input;

    //source
    printf("for the source, raw string (1) or bytes (2)? ");
    scanf(" %d", &input);
    printf("\n");

    printf("Enter the source checksum: ");
    scanf(" %s", raw_input);
    to_lowercase(raw_input);
    printf("\n");

    prepare_string(raw_input, source_check, input, sizeof(source_check));

    //generated
    printf("for the generated, raw string (1) or bytes (2)? ");
    scanf(" %d", &input);
    printf("\n");
    
    printf("Enter the generated checksum: ");
    scanf(" %s", raw_input);
    to_lowercase(raw_input);
    printf("\n");

    prepare_string(raw_input, gen_check, input, sizeof(gen_check));

    //verify
    if(strcmp(source_check, gen_check) == 0){
        printf("The checksum is valid!\n");
    }else{
        printf("The checksum is NOT valid.\n");
    }
    
    return 0;
}