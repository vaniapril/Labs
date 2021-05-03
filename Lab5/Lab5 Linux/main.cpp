#include <string>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

char* appName1 = "gnome-mines";
char* appName2 = "gnome-terminal";

int main() {
    // name
    if(popen(appName1, "r") == NULL){
        std::cout<<"Error!";
        return 0;
    }
    sleep(1);

    pid_t pid1 = fork();
    if (pid1 == 0){
        char *args[] = { "./Killer", "--name", appName1, NULL};
        if(execvp(args[0], args) == -1){
            std::cout<<"Error!";
        }
        exit(1);
    } else {
        int status;
        waitpid(pid1, &status, 0);
    }

    // id
    FILE *pipe = popen(appName2, "r");
    if(!pipe){
        std::cout<<"Error!";
        return 0;
    }
    sleep(1);

    pid_t pid3 = fork();
    if (pid3 == 0){
        char buf[512];
        std::string str("pgrep ");
        FILE *cmd_pipe = popen(str.append(appName2).c_str(), "r");
        fgets(buf, 512, cmd_pipe);
        pid_t pid = strtoul(buf, NULL, 10);
        char arg[10];
        sprintf(arg, "%ld", (long)pid);
        char *args[] = { "./Killer", "--id", arg, NULL};
        if(execvp(args[0], args) == -1){
            std::cout<<"Error!";
        }
        exit(1);
    } else {
        int status;
        waitpid(pid3, &status, 0);
    }

    // PROC_TO_KILL
    if(popen(appName1, "r") == NULL){
        std::cout<<"Error!";
        return 0;
    }
    if(popen(appName2, "r") == NULL){
        std::cout<<"Error!";
        return 0;
    }
    sleep(1);

    pid_t pid2 = fork();
    if (pid2 == 0){
        std::string str("");
        setenv("PROC_TO_KILL", str.append(appName1).append(",").append(appName2).c_str(), true);
        char *args[] = { "./Killer", NULL};
        if(execvp(args[0], args) == -1){
            std::cout<<"Error!";
        }
        exit(1);
    } else {
        int status;
        waitpid(pid2, &status, 0);
    }
    return 0;
}
