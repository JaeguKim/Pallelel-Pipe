#include "parse.h"


int findIndexOf(char * values, char find) {
    char * ptr = strchr(values, find);
    if (ptr) {
        int index = (int)(ptr - values);
        return index;
    }
    else {
        //printf("find_index_fail");
        return CANNOT_FIND_SYMBOL;
    }
}

/*split single line based on space, then return array pointer*/
char ** split_space(char * line, int str_len) {
    char *** ptr =(char ***)malloc(sizeof(char **)*MAX_CMD_PARAM_NUM);
    int start_idx = 0;
    char *cmd_name = (char *)malloc(sizeof(char)*40);
    char cp_str[40];
    int is_end = 0;
    int insert_idx = 0;
    
     strcpy(cp_str,line);
    /*In case of command with parameters*/
    if (findIndexOf(line, ' ') != CANNOT_FIND_SYMBOL)
    {
        int last_idx = findIndexOf(cp_str, ' ') - 1;
        for (int i = 0; i <= last_idx; i++) {
            cmd_name[i] = line[i];
        }
        cmd_name[last_idx + 1] = NULL;
        
        ptr[insert_idx++] = cmd_name;
        
        /*mark space char*/
        cp_str[last_idx+1] = 'o';
        
        while (is_end != 1){
            /*find next parameter start point skipping space*/
            for (int i = last_idx+2; i <= str_len-1;i++){
                if (cp_str[i] != ' ')
                {
                    start_idx = i;
                    break;
                }
            }
            
            if (findIndexOf(cp_str, ' ') == CANNOT_FIND_SYMBOL){
                last_idx = str_len - 1;
                is_end = 1;
            }
            else
                last_idx = findIndexOf(line, ' ') - 1;
            char *param = (char *)malloc(sizeof(char)*40);
            int tmp_idx = 0;
            for (int i = start_idx; i <= last_idx; i++) {
                param[tmp_idx++] = line[i];
            }
            param[tmp_idx] = NULL;
            /*Eliminate quotation mark if exist*/
            if (param[0] == '\'' && param[strlen(param)-1] == '\'')
            {
                param[0] = '\0';
                int i = 0;
                for (i = 0; i <= strlen(param)-1; i++)
                    param[i] = param[i+1];
                param[i-2] = NULL;
                //printf("param : %s\n",param);
            }
            ptr[insert_idx++] = param;
            if (is_end == 0)
                cp_str[last_idx+1] = 'o';
        }
    }
    /*In case of command with no parameter*/
    else{
        strcpy(cmd_name,line);
        ptr[0] = cmd_name;
        ptr[1] = NULL;
        return ptr;
    }
    
    ptr[insert_idx] = NULL;
    return ptr;
}

int calc_num_of_cmd(char * line) {
    int num_of_pipe = 0;
    int num_of_double_pipe;
    for (int i = 0; i < strlen(line); i++) {
        if (line[i] == '=')
            num_of_pipe += 1;
    }
    num_of_double_pipe = num_of_pipe / 2;
    return num_of_double_pipe+1;
}

char * slice_str(char * line, int start, int end) {
    char * temp = (char *)malloc(sizeof(char)*40);
    int insert_idx = 0;
    for (int i = start; i <= end; i++) {
        temp[insert_idx++] = line[i];
    }
    temp[insert_idx] = NULL;
    return temp;
}

char *** parse_cmd(char * line){
    /*calculate number of command before final command*/
    int num_of_cmd = calc_num_of_cmd(line);
    //printf("line : %s\n",line);
    //printf("num_of_cmd : %d\n",num_of_cmd);
    char *** temp_split_cmd = (char **)malloc(sizeof(char **)*num_of_cmd);
    int start_index = 0;
    int cmd_insert_idx = 0;
    int pipe_index;
    int end_of_cmd_index;
    
    for (int i = 0; i < num_of_cmd-1; i++) {
        pipe_index = findIndexOf(line, '=');
        end_of_cmd_index = pipe_index - 2;
        //int len = end_of_cmd_index - start_index + 1;
        char temp[40];
        int tmp_insert_idx = 0;
        for (int i = start_index; i <= end_of_cmd_index; i++) {
            temp[tmp_insert_idx++] = line[i];
        }
        temp[tmp_insert_idx] = NULL;
        
        /*add cmd list to array*/
        temp_split_cmd[cmd_insert_idx++] = split_space(temp, strlen(temp));
        //printf("split_cmd[%d] : %s\n",cmd_insert_idx,temp_split_cmd[cmd_insert_idx][0]);
        /*slice array*/
        int start_slice = pipe_index + 3;
        line = slice_str(line, start_slice, strlen(line) - 1);
    }

    //printf("aaa\n");
    char temp[40];
    int tmp_insert_idx = 0;
    
    //temp[tmp_insert_idx] = NULL;
    temp_split_cmd[cmd_insert_idx] = split_space(line, strlen(line));
    //printf("split_cmd[%d] : %s\n",cmd_insert_idx,temp_split_cmd[cmd_insert_idx][1]);
    
    return temp_split_cmd;
}
