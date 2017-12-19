#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client);

static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("luigi");
    exit(0);
  }
}

int main() {
  signal(SIGINT, sighandler);
  int to_client;
  int from_client;
  while(1){
    from_client = server_setup();
  
    int f = fork();

    if (! f){ //subserver
      subserver(from_client);
    }

    else{//main server
      close(from_client);
    }
    
  }
}

void subserver(int from_client) {
    int to_client = server_connect(from_client);
    char *buff = (char *) calloc(BUFFER_SIZE, sizeof(char));
    
    while(read(from_client, buff, BUFFER_SIZE)){
    process(buff);
    write(to_client, buff, BUFFER_SIZE);
    }
    
    exit(0);
}

void process(char * s) {
  char *append = " is very cool";
  strncat(s, append, BUFFER_SIZE - strlen(s));
}
