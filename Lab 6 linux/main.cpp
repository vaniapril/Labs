#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <string>
#include <iostream>

const int BUFSIZE = 256;

void procM(){
    std::string str;
    while (std::cin >> str){
        if (str == "stop") break;
        int i = std::atoi(str.c_str());
        i *= 7;
        std::cout << i << ' ';
    }
    std::cout<<"stop\n";
}

void procA(){
    int id = 0;
    std::string str;
    while (std::cin >> str){
        if (str == "stop") break;
        int i = std::atoi(str.c_str());
        i += ++id;
        std::cout << i << ' ';
    }
    std::cout<<"stop\n";
}

void procP(){
    std::string str;
    while (std::cin >> str){
        if (str == "stop") break;
        int i = std::atoi(str.c_str());
        i *= i * i;
        std::cout << i << ' ';
    }
    std::cout<<"stop\n";
}

void procS(){
    int sum = 0;
    std::string str;
    while (std::cin >> str){
        if (str == "stop") break;
        int i = std::atoi(str.c_str());
        sum += i;
    }
    std::cout<<sum<<' ';
}


int main(){
    int fd1[2];
    int fd2[2];
    int fd3[2];
    int fd4[2];
    int fd5[2];

    if (pipe(fd1) == -1){return 1;}
    if (pipe(fd2) == -1){return 1;}
    if (pipe(fd3) == -1){return 1;}
    if (pipe(fd4) == -1){return 1;}
    if (pipe(fd5) == -1){return 1;}

    pid_t pid1 = fork();
    if (pid1 == 0){
        dup2(fd1[0], 0);
        dup2(fd2[1], 1);
        procM();
        exit(0);
    }

    pid_t pid2 = fork();
    if(pid2 == 0){
        dup2(fd2[0], 0);
        dup2(fd3[1], 1);
        procA();
        exit(0);
    }

    pid_t pid3 = fork();
    if(pid3 == 0){
        dup2(fd3[0], 0);
        dup2(fd4[1], 1);
        procP();
        exit(0);
    }

    pid_t pid4 = fork();
    if(pid4 == 0){
        dup2(fd4[0], 0);
        dup2(fd5[1], 1);
        procS();
        exit(0);
    }

    write(fd1[1], "1 2 3 4 5 6 7 8 9 stop\n", BUFSIZE);

    int status;
    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);
    waitpid(pid3, &status, 0);
    waitpid(pid4, &status, 0);

    char buff[BUFSIZE] = {};
    read(fd5[0], buff, BUFSIZE);
    std::cout<<buff;
}