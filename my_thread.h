//
//  my_thread_v3.h
//  PAPI
//
//  Created by 김재구 on 2017. 6. 21..
//  Copyright © 2017년 김재구. All rights reserved.
//

#ifndef my_thread_h
#define my_thread_h

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "parse.h"
#define DEFAULT_THREAD_NUM 4
#define MAX_THREAD_NUM 10

pthread_t thread_ary[MAX_THREAD_NUM];
pthread_mutex_t mutex_ary[MAX_THREAD_NUM];
pthread_mutex_t global_mutex;
int fd_ary[MAX_THREAD_NUM][2];
int fd_ary_idx;

char thread_input_buffer[MAX_THREAD_NUM][1024];
int input_stream_end;

typedef struct THREAD_PARAM{
    int thread_id;
}PARAM;

typedef struct command
{
    const char **argv;
}command;

void * thread_exec(void *p);
int spawn_proc (int in, int out, struct command *cmd);
void fork_pipes(int num_of_cmd, command * cmd, int cmd_num);

#endif /* my_thread_h */
