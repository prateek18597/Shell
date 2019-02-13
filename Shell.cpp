#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
using namespace std;

int main()
{
		string func,flag;
		cout<<"->";
		cin>>func;
		cout<<"Prob";
		int rc = fork();
		if (rc < 0) 
		{
			printf("Error\n");
			exit(1);
		} 
		else if (rc == 0) 
		{
			cout<<"Problem Here";
			char *myargs[3];
			myargs[0] = strdup(func);
			myargs[1] = NULL;
			myargs[2] = NULL;
			execvp(myargs[0], myargs);
		}
		else 
		{
			int rc_wait = wait(NULL);
		}
	
	return 0;
}