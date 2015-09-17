/*
EXECUTING AN APPLICATION USING EXEC COMMANDS
The execvp() family of commands can be used to execute an
application from a process. The system call execvp()
replaces the executing process by a new process image
which executes the application specified as its parameter.
Arguments can also be specified. Refer to online man pages.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
main()
{
char *arglist[3];
/* "cal" is an application which shows the calendar of the
current year and month. "cal" with an argument specifying
year (for example "cal 1999") shows the calendar of that
year. Try out the "cal" command from your command prompt.
Here we execute "cal 2012" using the execvp() system call.
Note that we specify "cal" in the first two arguments. The
reason for this is given in the online man pages for execvp()
*/
/* Initialize the argument list */
arglist[0] = (char *)malloc(4*sizeof(char)); strcpy(arglist[0],"cal");
arglist[1] = (char *)malloc(5*sizeof(char)); strcpy(arglist[1],"2012");
arglist[2] = NULL;
/* Call execvp */
execvp("cal",arglist);
/* The execvp() system call does not return. Note that the
following statement will not be executed.
*/
printf("This statement is not executed if execvp succeeds.\n");
}
