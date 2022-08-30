#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include <fcntl.h> 
#include<dirent.h> 
#include<sys/types.h> 
#include<string> 
#include<sys/wait.h> 
#include<vector>
#include<fstream>
#include<bits/stdc++.h>
#include <sys/stat.h>
#include <errno.h>

extern int errno ;

using namespace std;

void read_dir(string cur, vector<string>& v){
    DIR* dirp = opendir(cur.c_str());
    struct dirent * child;
    while ((child = readdir(dirp)) != NULL) {
        string s(child->d_name);
        if(s != "." && s!= ".."){
            v.push_back(child->d_name);
        }
    }
    closedir(dirp);
}

void open_pipe(vector<string> names, vector<int>& read_fd){
    int num = names.size();

    for(int i = 0 ; i < num ; i++){
        int fd = open(names[i].c_str(), O_RDONLY);
        read_fd.push_back(fd);
    }
}

void read_pipe(vector<string> names, vector<int> read_fd, vector<int>& data ){
    int num = names.size();

    for(int i = 0 ; i < num ; i++){
        char inp[40] = ""; 
        read(read_fd[i], inp, 40);
        data.push_back(atoi(inp));
        close(read_fd[i]);
        remove(names[i].c_str());
    }

}

int find_max(vector<int> data){
    int maxi = data[0];
    for (int i=1; i< data.size(); i++)
        if(data[i] > maxi)
                maxi = data[i];
    return maxi;
}

int find_min(vector<int> data){
    int mini = data[0];
    for (int i=1; i< data.size(); i++)
        if(data[i] < mini)
            mini = data[i];
    return mini;
}

            
        


int main(int argc, char* argv[]){
    char readmessage[40];
    read(atoi(argv[2]), readmessage, 40);
   

    
    vector<string> dir_names;
    read_dir(argv[1], dir_names);
    int num = dir_names.size();
    
    string cur_dir(argv[1]);

    
    

    vector<int> data;
    vector <int> read_fd;
   
    
    vector<string> names;

    int fdpar[num][2];
    for(int i=0; i< num; i++)
        pipe(fdpar[i]);
    

        
    for(int i=0; i< num; i++){
        
        
        string pipe_name = to_string(getpid()) + dir_names[i];
        mkfifo(pipe_name.c_str(), 0666);

        int id = fork();
        if(id == 0){
           
            write(fdpar[i][1], readmessage, 40);
            string pipnum = to_string(fdpar[i][0]);
            string child_dir = cur_dir + "/" + dir_names[i];
            
            execl("./city", "city.cpp", child_dir.c_str(), pipnum.c_str(), pipe_name.c_str(), NULL);  
        }
        else if(id > 0){
            names.push_back(pipe_name);
        }   
    }


    
    open_pipe(names, read_fd);
    read_pipe(names, read_fd, data);
    
    char *token = strtok(readmessage, " ");

    if(strcmp(token, "MAX") == 0){
        int maxi = find_max(data);
        string maxi_s = to_string(maxi);
        int pipe = open(argv[3], O_WRONLY);
        write(pipe, maxi_s.c_str(), 100);
        close(pipe);
    }

    if(strcmp(token, "MIN") == 0){
        int mini = find_min(data);
        string mini_s = to_string(mini);
        int pipe = open(argv[3], O_WRONLY);
        write(pipe, mini_s.c_str(), 100);
        close(pipe);
    }
    
   
    exit(0);
}