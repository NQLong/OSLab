#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>/*definesfork(),andpid_t.*/
int main(int argc,char **argv){
pid_t child_pid;
sigset_t mask,oldmask;
/*letsforkoffachildprocess...*/
child_pid=fork();
/*checkwhatthefork()callactuallydid*/
if(child_pid==−1){
perror("fork");/*printasystem−definederror
message*/
exit(1);
}
if(child_pid==0){
/*fork()succeeded,we’reinsidethechildprocess*/
signal(SIGUSR1,parentdone);/*setupasignal*/
/*Setupthemaskofsignalstotemporarilyblock.*/
sigemptyset(&mask);
sigaddset(&mask,SIGUSR1);
/*Waitforasignaltoarrive.*/
sigprocmask(SIG_BLOCK,&mask,&oldmask);
while(!usr_interrupt)
sigsuspend(&oldmask);
sigprocmask(SIG_UNBLOCK,&mask,NULL);
printf("World!\n");
fflush(stdout);
}
else{
/*fork()succeeded,we’reinsidetheparentprocess*/
printf("Hello,");
fflush(stdout) ;
kill( child_pid , SIGUSR1 ) ;
wait (NULL) ;
}
return 0 ;
}