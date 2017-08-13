/* Compile with: g++ -Wall –Werror -o shell shell.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "parse.h"
#include "my_thread.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int is_integer(char *s) {
    size_t size = strlen(s);
    
    if (size == 0) return 0;
    for (int i = 0; i < (int) size; i++) {
        if (s[i] < '0' || s[i] > '9') return 0;
    }
    return 1;
}

int main(int argc, char * argv[]) {
    fd_ary_idx = 0;
    int num_of_thread = DEFAULT_THREAD_NUM;
    input_stream_end = 0;
    //printf("argc : %d\n",argc);
    
    /* CASE : ./ppipe -c n "commands"*/
    if (argc == 4){
        if (strcmp(argv[1],"-c") == 0 && is_integer(argv[2])){
            num_of_thread = atoi(argv[2]);
        }
        else{
            fputs("Parameter Format Error : ppipe -c n\n",stderr);
            exit(1);
        }
    }
    
    
    char line_buf[1024];
    
    /*copy command string*/
    int command_str_len = strlen(argv[argc-1]);
    command_str = (char *)malloc(sizeof(char)*(command_str_len+1));
    
    for (int i = 0; i < command_str_len; i++){
        command_str[i] = argv[argc-1][i];
    }
    command_str[command_str_len] = NULL;
    
    /*parse command string */
    num_of_cmd = calc_num_of_cmd(command_str);
    split_cmd = parse_cmd(command_str);
    
    /*mutex init*/
    for (int i = 0; i < num_of_thread; i++)
    {
        pthread_mutex_init(&mutex_ary[i], NULL);
        thread_input_buffer[i][0] = '\0';
    }
    pthread_mutex_init(&global_mutex, NULL);

    /*execute threads*/
    for (int i = 0; i < num_of_thread; i++)
    {
        PARAM * param = (PARAM *)malloc(sizeof(PARAM));
        param->thread_id = i;
        pthread_create(&thread_ary[i],NULL,thread_exec,(void *)param);
        sleep(1);
    }
    
    /*read each line from previous program*/
    int cur_buf_idx = 0;
    while (fgets(line_buf, sizeof(line_buf), stdin) != NULL)
    {
        /*CRITICAL SECTION : write to thread buffer*/
        pthread_mutex_lock(&mutex_ary[cur_buf_idx]);
        strcpy(thread_input_buffer[cur_buf_idx],line_buf);
        pthread_mutex_unlock(&mutex_ary[cur_buf_idx]);
        
        cur_buf_idx++;
        if (cur_buf_idx > num_of_thread-1)
            cur_buf_idx = 0;
        //ssleep(1);
    }
    
    /*notify input stream is over*/
    input_stream_end = 1;
    
    /*waiting threads*/
    for (int i = 0; i < num_of_thread; i++)
        pthread_join(thread_ary[i], NULL);
    
    //printf("thread is all terminated!\n");
    return 0;
    
    
    
}
