#include <iostream>
#include <csignal>
#include <cstring>
#include <unistd.h>

int endWithId(pid_t pid){
    if (pid){
        printf("Kill pid %i\n", pid);
        kill(pid, SIGKILL);
    } else {
        printf("Invalid pid\n");
    }
    return 0;
}

int endWithName(std::string name){
    char buf[512];
    std::string str("pgrep ");
    FILE *cmd_pipe = popen(str.append(name).c_str(), "r");
    fgets(buf, 512, cmd_pipe);
    pid_t pid = strtoul(buf, NULL, 10);
    printf("%s pid is %i\n", name.c_str(), pid);
    endWithId(pid);
    return 0;
}

int endWithNames(std::string names){
    for (int index = 0; index != -1 ;) {
        index = names.find(',');
        std::string name = names.substr(0, index);
        endWithName(name.c_str());
        names = names.substr(index + 1, names.length());
    }
    return 0;
}

int main(int argc, char* argv[]){
    if (argc > 2){
        if(strcmp(argv[1], "--id") == 0){
            endWithId(atoi( argv[2]));
        }
        if(strcmp(argv[1], "--name") == 0){
            endWithName(argv[2]);
        }
    }

    const char* names = getenv("PROC_TO_KILL");
    if(names){
        endWithNames(names);
    }
    return 0;
}