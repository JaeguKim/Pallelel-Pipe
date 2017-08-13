//
//  my_thread_v3.c
//  PAPI
//
//  Created by 김재구 on 2017. 6. 21..
//  Copyright © 2017년 김재구. All rights reserved.
//

#include "my_thread.h"

void fork_pipes(int num_of_cmd, command * cmd, int cmd_num){
    pid_t pid;
    int fd[2];
    pipe(fd);

    if ((pid = fork() == 0)){
        dup2(fd[0],0);
        close(fd[1]);
        if (num_of_cmd-1 == 1){
                dup2(fd[0],0);
                close(fd[1]);
                execvp(cmd[cmd_num+1].argv[0],(char * const *)cmd[cmd_num+1].argv);
        }
        else{
            fork_pipes(num_of_cmd-1, cmd, cmd_num+1);
        }
    }
    dup2(fd[1],1);
    close(fd[0]);
    execvp (cmd[cmd_num].argv[0], (char * const *)cmd[cmd_num].argv);

}

void *thread_exec(void *p){
    PARAM * param = (PARAM *)p;
    int thread_id = param->thread_id;
    
    command * cmd = (command *)malloc(sizeof(command)*num_of_cmd);
    for (int i = 0; i < num_of_cmd; i++){
        cmd[i].argv = split_cmd[i];
    }
    
    pid_t pid;
    pthread_mutex_lock(&global_mutex);
    int cur_idx = fd_ary_idx;
    pipe(fd_ary[fd_ary_idx++]);
    pthread_mutex_unlock(&global_mutex);
    
    int cmd_num = 0;
    
    if ((pid = fork() == 0)){
         for (int i = 0; i < fd_ary_idx; i++)
         {
             if (i != cur_idx)
                 close(fd_ary[i][1]);
         }
         dup2(fd_ary[cur_idx][0],0);
         close(fd_ary[cur_idx][1]);
         
         if (num_of_cmd == 1)
             execvp (cmd[0].argv[0], (char * const *)cmd[0].argv);
         else
             fork_pipes(num_of_cmd, cmd, cmd_num);
     }
    close(fd_ary[cur_idx][0]);
    
    int write_fd = fd_ary[cur_idx][1];
    
    while (input_stream_end != 1){
        pthread_mutex_lock(&mutex_ary[thread_id]);
        write(write_fd,thread_input_buffer[thread_id],strlen(thread_input_buffer[thread_id]));
        thread_input_buffer[thread_id][0] = '\0';
        pthread_mutex_unlock(&mutex_ary[thread_id]);
    }
    close(write_fd);
    return NULL;
}


