# README #  
# How To Compile?   
Linux(tested on Ubuntu 16.04.2)  : gcc ppipe.c my_thread_v3.c parse.c -o papi -lpthread     
   
# How To Execute?   
cat book2.txt | ./papi -c 4 "cat"   
cat book2.txt | ./papi -c 5 "grep paper == cat"   
cat book2.txt | ./papi -c 3 "grep a == sed 's/the//g' == wc -l"   
cat book2.txt | ./papi -c 2 "grep a == sed 's/the//g' == wc -l == cat"    
   
