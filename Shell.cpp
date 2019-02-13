#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <limits.h>
using namespace std;

string getexepath()
{
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return std::string( result, (count > 0) ? count : 0 );
}

int main()
{
	while(true)
	{
		string program_name,parameters;
		string path=getexepath();
		int last=0;
		for(int i=0;path[i];i++)
		{
			if(path[i]=='/')
				last=i;
		}
		path=path.substr(0,last);
		cout<<path<<">>>";
		getline (cin, program_name);
		if(program_name=="quit")
			break;
		bool flag=false;
		for(int i=0;program_name[i];i++)
		{
			if(program_name[i]==' ')
			{
				flag=true;
				parameters=program_name.substr(i+1,program_name.length()-i);
				program_name=program_name.substr(0,i);
				break;
			}
		}
		
		int rc = fork();
		if (rc < 0) 
		{
			printf("Error\n");
			exit(1);
		} 
		else if (rc == 0) 
		{
			if(flag==false){
				char *myargs[]={(char*)program_name.c_str(),NULL};
				execvp(myargs[0], myargs);
			}
			else
			{
				char *myargs[]={(char*)program_name.c_str(),(char*)parameters.c_str(),NULL};
				execvp(myargs[0], myargs);
			}

			
		}
		else 
		{
			int rc_wait = wait(NULL);
		}
	}
	return 0;
}