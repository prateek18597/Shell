#include<iostream>
using namespace std;
#include<fstream>
#include<unistd.h> 
#include<sys/wait.h>
#include<string>
#define SIZE 10000

int main(int argc, char** argv)
{
	if(argc!=2)
	{
		cout<<"Usage: ./Pipe <File name>"<<endl;
		return 0;
	}
	int nbytes;
	int pipe1[2],pipe2[2];
	if(pipe(pipe1)<0 || pipe(pipe2)<0)
	{
		cout<<"Error in Pipe call"<<endl;
		return 1;
	}
	
	int process1=fork();
	if(process1>0)
	{
		wait(NULL);
	}
	else if(process1==0)
	{
		cout<<"Process1 :  "<<getpid()<<endl;
		string content;
		std::ifstream file(argv[1]);
		if (file.is_open()) 
		{
		    std::string line;
		    while (getline(file, line)) 
		    {
		        content+=line.c_str();
		    }
		    file.close();
		}
		char *str = (char *)content.c_str();
		cout<<"->\t"<<str<<endl;
		write(pipe1[1],str,SIZE);
		return 0; 
    }
    else
    {
    	cout<<"Error in fork"<<endl;
	}
	
	int process2=fork();

	if(process2<0)
	{
		cout<<"Error in the Fork"<<endl;
	}
	else if(process2>0)
	{
		wait(NULL);
	}
	else
	{
		char str[SIZE];
		cout<<"Process2: "<<getpid()<<endl;
		read(pipe1[0], str, SIZE);
		for(int i=1;str[i];i+=2)
		{
			if(str[i]-'A'>=0 && str[i]-'A'<26)
				str[i]+=32;
		}
		cout<<"->\t"<<str<<endl;
		write(pipe1[1],str,SIZE);
		return 0;
	}

	int process3=fork();

	if(process3<0)
	{
		cout<<"Error in fork"<<endl;
	}
	else if(process3>0)
	{
		wait(NULL);
	}
	else
	{
		char str[SIZE];
		cout<<"Process3: "<<getpid()<<endl;
		read(pipe1[0], str, SIZE);
		for(int i=0;str[i];i+=2)
		{
			if(str[i]-'a'>=0 && str[i]-'a'<26)
				str[i]-=32;
		}
		write(pipe1[1],str,SIZE);
		cout<<"->\t"<<str<<endl;
		return 0;
	}

	int process4=fork();

	if(process4<0)
	{
		cout<<"Error in fork"<<endl;
	}
	else if(process4>0)
	{
		wait(NULL);
	}
	else
	{
		char str[SIZE];
		cout<<"Process4: "<<getpid()<<endl;
		read(pipe1[0], str, SIZE);
		int state = 0; 
	    int wc = 0;
	    int i=0;   
	    while (str[i]) 
	    { 
	        if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == ',' || str[i] == '.') 
	            state = 0; 
	        else if (state == 0) 
	        { 
	            state = 1; 
	            ++wc;
	        } 
	  		i++;
	    } 
	    cout<<"->\tWord Count= "<<wc<<endl;
    	return 0;
	}


	return 0;
}
