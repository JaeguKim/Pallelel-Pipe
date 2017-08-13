# README #
#################README###################   
Version 1 : works well but spawn processes in every line .  
Version 2 : spawn processes and prepare file descriptor before reading line but only works single grep command(eg. cat input.txt | ./papi "grep blackhole") .
  
#################How To Compile?###################   
<Version 1>  
Linux(tested on Ubuntu 16.04.2)  : gcc ppipe.c parse.c my_thread.c -o papi -lpthread   
macOS : gcc ppipe.c parse.c my_thread.c -o papi   

<Version 2>   
Linux(tested on Ubuntu 16.04.2)  : gcc ppipe.c parse.c my_thread_v2.c -o papi -lpthread   
macOS : gcc ppipe.c parse.c my_thread_v2.c -o papi   

<Version 3>   
Linux(tested on Ubuntu 16.04.2)  : gcc ppipe.c my_thread_v3.c parse.c -o papi -lpthread     
   
#################How To Execute?###################   
cat book2.txt | ./papi -c 4 "cat"   
cat book2.txt | ./papi -c 5 "grep paper == cat"   
cat book2.txt | ./papi -c 3 "grep a == sed 's/the//g' == wc -l"   
cat book2.txt | ./papi -c 2 "grep a == sed 's/the//g' == wc -l == cat"    
   
#################ETC################### 
Student Number : 2014105024   
Name : 김재구   
<Milestone>    
Version 1 =>1~5 step complete, command parsing works well BUT spawn every process in one line .  
Version 2 =>1~5 step complete, command pasing works BUT only works grep command not WC or multiple commands   
email : rlaworn1993@gmail.com