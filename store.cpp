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
#include <limits>
#include <errno.h>
using namespace std;
extern int errno;

int date_check_min(string data, vector<int>first){
    
    vector<int> dest;
    stringstream s(data);
    string word;
    while (getline(s, word, '/')) {
        dest.push_back(stoi(word));
    } 

   

    
    if((dest[0] > first[0]) || (dest[0] == first[0] && dest[1] > first[1]) || (dest[0] == first[0] && dest[1] == first[1] && dest[2]>=first[2]) )
        return 1;
    else 
        return 0;

    
}

int date_check_max(string data, vector<int>first){
    
    vector<int> dest;
    stringstream s(data);
    string word;
    while (getline(s, word, '/')) {
        dest.push_back(stoi(word));
    } 
    
    


    if((dest[0] < first[0]) || (dest[0] == first[0] && dest[1] < first[1]) || (dest[0] == first[0] && dest[1] == first[1] && dest[2]<=first[2]) )
        return 1;
    else 
        return 0;

    
}

int find_max(vector<char*> input, vector<vector<string>> data){
    vector<int> first;
    char *token = strtok(input[2], "/");
    while (token != NULL){
        
        first.push_back(atoi(token));
        token = strtok(NULL, "/");
    }

    vector<int> second;
    char *token2 = strtok(input[3], "/");
    while (token2 != NULL){
        
        second.push_back(atoi(token2));
        token2 = strtok(NULL, "/");
    }
    int maxi = 0;
    for(int i=0; i<data.size(); i++){
        if(strcmp(data[i][1].c_str(), input[1]) == 0){

            if(date_check_min(data[i][0], first) && date_check_max(data[i][0], second) ){
                
                if(stoi(data[i][2]) > maxi)
                    maxi = stoi(data[i][2]);
            }

            
        }
    }
    
    return maxi;

}

int find_min(vector<char*> input, vector<vector<string>> data){
    vector<int> first;
    char *token = strtok(input[2], "/");
    while (token != NULL){
        
        first.push_back(atoi(token));
        token = strtok(NULL, "/");
    }

    vector<int> second;
    char *token2 = strtok(input[3], "/");
    while (token2 != NULL){
        
        second.push_back(atoi(token2));
        token2 = strtok(NULL, "/");
    }
    int mini = std::numeric_limits<int>::max();
    for(int i=0; i<data.size(); i++){
        if(strcmp(data[i][1].c_str(), input[1]) == 0){

            if(date_check_min(data[i][0], first) && date_check_max(data[i][0], second) ){
                
                if(stoi(data[i][2]) < mini)
                    mini = stoi(data[i][2]);
            }

            
        }
    }
    
    return mini;

}



int main(int argc, char** argv){
    

    
    vector<char*> input;
    char readmessage[40];
    int fd = atoi(argv[2]);
    read(fd, readmessage, sizeof(readmessage));
    close(fd);
    char *token = strtok(readmessage, " ");
    
    while (token != NULL){
        
        input.push_back(token);
        token = strtok(NULL, " ");
    }

    vector<vector<string>> data;
    fstream fin; 
    fin.open(argv[1], ios::in); 
    string line;
    int i =0;
    while(getline(fin, line)){
        stringstream s(line);
        string word;
        
        data.push_back(vector<string>());
         while (getline(s, word, ',')) {
           data[i].push_back(word);
        } 

        i++;    
    }
   
   
    

    if(strcmp(input[0] ,"MAX") == 0){
        int maxi = find_max(input , data);
        string maxi_s = to_string(maxi);
        int pipe = open(argv[3], O_WRONLY);
        write(pipe, maxi_s.c_str(), maxi_s.size() + 1);
        close(pipe);
    }
   
    if(strcmp(input[0] ,"MIN") == 0){

        int mini = find_min(input , data);
        string mini_s = to_string(mini);
        int pipe = open(argv[3], O_WRONLY);
        write(pipe, mini_s.c_str(), mini_s.size() + 1);
        close(pipe);
    
    }



   
    exit(0);
 
    
    
}