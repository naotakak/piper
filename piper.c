#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int READ = 0;
  int WRITE = 1;
  int fds[2];
  int fd2[2];
  pipe(fds);
  pipe(fd2);

  int f = fork();
  if (f != 0) {
    close(fds[READ]);
    int send = 2;
    write(fds[WRITE], &send, sizeof(send));
    printf("[parent] sending %d\n", send);
    close(fd2[WRITE]);
    int recieve;
    read(fd2[READ], &recieve, sizeof(recieve));
    printf("[parent] recieved %d\n", recieve);
  }
  else {
    close(fds[WRITE]);
    int send2;
    read(fds[READ], &send2, sizeof(send2));
    printf("[child] doing quick maths on %d\n", send2);
    send2 = send2 + 2 - 1;
    close(fd2[READ]);
    write(fd2[WRITE], &send2, sizeof(send2));
  }
  return 0;
}
