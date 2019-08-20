#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <limits.h>
#include <errno.h>

#define MAX_BUFFER_SIZE 1024
#define FUNC_SUCCESS 1
#define EOF_ERROR 2
#define INPUT_FAILED 3

#define OUT_OF_LONG -1
#define OUT_OF_INTEGER -2
#define NOT_NUMBER -3

int get_integer(int *num, FILE *stream);
int get_str(char *str, FILE *stream);
int str_to_int(int *num, FILE *stream);
void print_fgets_error(int error_num);
void print_getint_error(int error_num);


int main(void){
    int x;
    x = get_integer(&x, stdin);
    printf("ret = %d\n",x);

    return EXIT_SUCCESS;
}

int get_integer(int *num, FILE *stream){
    int x;

    switch(str_to_int(&x, stream)){
        case FUNC_SUCCESS:
            return x;
        case OUT_OF_LONG:
            fprintf(stderr, "OUT OF LONG");
            break;
        case OUT_OF_INTEGER:
            fprintf(stderr, "OUT OF INTEGER.");
            break;
        case NOT_NUMBER:
            fprintf(stderr, "NOT NUMBER.");
            break;
        default:
            fprintf(stderr, "NOT DEFINED ERROR OCCURED IN NUMCHECK.");
            break;
    }

    exit(EXIT_FAILURE);
}

int str_to_int(int *num, FILE *stream){
    int error_num = INPUT_FAILED;
    int number;

    char buf[MAX_BUFFER_SIZE] = {'\0'};

    if((error_num = get_str(buf, stream)) != FUNC_SUCCESS){
        print_fgets_error(error_num);
    }

    char *endptr;
    errno = 0;

    number = strtol(buf, &endptr, 10);  //文字列をlong型数値に変換
    
    if(errno == ERANGE){                //longの範囲を超えた
        return OUT_OF_LONG;
    }
    
    if(*endptr && *endptr != '\n'){     //数値でない部分が含まれていた
        return NOT_NUMBER;
    }

    if(number < INT_MIN || number > INT_MAX){     //intの範囲を超えた
        return OUT_OF_INTEGER;
    }

    *num = (int)number;

    return FUNC_SUCCESS;
}

//ストリームから一行を取得する関数
int get_str(char *buf, FILE *stream){

    
    //バファサイズ以下の一行を読み込む
    if(!fgets(buf, MAX_BUFFER_SIZE, stream)){
        //EOFチェック
        if(feof(stream)){
            return EOF_ERROR;
        }
        return INPUT_FAILED;
    }
 
    return FUNC_SUCCESS;

}

void print_fgets_error(int error_num){
    switch(error_num){
        case EOF_ERROR:
            fprintf(stderr, "FGETS RETURN EOF.");
            break;
        case INPUT_FAILED:
            fprintf(stderr, "FGETS RETURN EOF.");
            break;
        default:
            fprintf(stderr, "NOT DEFINED ERROR OCCURED IN FGETS.");
            break;
    }

    exit(EXIT_FAILURE);
}

void print_getint_error(int error_num){
    switch(error_num){
        case OUT_OF_LONG:
            fprintf(stderr, "OUT OF LONG'S RANGE.");
            break;
        case NOT_NUMBER:
            fprintf(stderr, "NOT NUMBER ERROR.");
            break;
        case OUT_OF_INTEGER:
            fprintf(stderr, "OUT OF INTEGER'S RANGE.");
            break;
        default:
            fprintf(stderr, "NOT DEFINED ERROR OCCURED IN GETINT.");
            break;
    }

    exit(EXIT_FAILURE);
}
