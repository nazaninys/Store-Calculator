#include <iostream>
#include <unistd.h> 
#include <stdio.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <vector>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <dirent.h>
#include <limits>
using namespace std;

void open_pipe(vector<string> names, vector<int>& read_fd){
    int num = names.size();

    for(int i = 0 ; i < num ; i++){
        int fd = open(names[i].c_str(), O_RDONLY);
        read_fd.push_back(fd);
    }
}

void read_pipe(vector<string> names, vector<int> read_fd){
    int num = names.size();
    int mini = std::numeric_limits<int>::max();
    int maxi = 0;
    for(int i = 0 ; i < num ; i++){
        char inp[40] = ""; 
        read(read_fd[i], inp, 40);
        if(atoi(inp) == mini || atoi(inp) == maxi)
            cout<<"-1"<<endl;
        else
            cout<<inp<<endl;
        
        close(read_fd[i]);
        remove(names[i].c_str());
    }

}


int main(int argc, char** argv){
    
    
    int num = 0;
    string line;
    vector<string> lines;
    ifstream filename(argv[1]);
    
    while (getline (filename, line)) {
        num ++; 
        lines.push_back(line);
    }
    filename.close(); 
    
    int fd[num][2];
    for (int i=0; i< num; i++)
        pipe(fd[i]);

    vector<int> data;
    vector <int> read_fd;
   
    
    vector<string> names;

    int fdpar[num][2];
    for(int i=0; i< num; i++)
        pipe(fdpar[i]);

    string parid = to_string(getpid());
    for(int i=0; i< num; i++){
        string pipe_name = parid + to_string(i);
        names.push_back(pipe_name);

    }
        
    for(int i=0; i< num; i++){
        
        mkfifo(names[i].c_str(), 0666);

        int id = fork();
        if(id == 0){
           
            char message[40] = "";
            strcpy(message, lines[i].c_str());
            write(fdpar[i][1], message, 40);
            string pipnum = to_string(fdpar[i][0]);
            execl("./command", "command.cpp", argv[2], pipnum.c_str(), names[i].c_str(), NULL);  
        } 
    }


    
    open_pipe(names, read_fd);
    read_pipe(names, read_fd);


    
    exit(0);
    
}