//
//  parse.h
//
//
//  Created by 김재구 on 2017. 5. 13..
//
//

#ifndef parse_h
#define parse_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CANNOT_FIND_SYMBOL 9999
#define MAX_CMD_PARAM_NUM 5

char * command_str;
char *** split_cmd;
int num_of_cmd;

int findIndexOf(char * values, char find);
char ** split_space(char * line, int str_len);
int calc_num_of_cmd(char * line);
char * slice_str(char * line, int start, int end);
char *** parse_cmd(char * line);

#endif /* parse_h */
