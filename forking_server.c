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
  char buff[BUFFER_SIZE];
  int to_client;
  int from_client;
  int pid = getpid();
  while(1){
    from_client = server_handshake(&to_client);
    if(getpid() != pid){
      subserver(from_client);
    }
  }
}

void subserver(int from_client) {
  
}

void process(char * s) {
}
