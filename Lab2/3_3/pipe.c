#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int pipe_fd1[2], pipe_fd2[2];
static int counter = 0;

void INIT(void) {
    if (pipe(pipe_fd1) < 0 || pipe(pipe_fd2) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
}

void WRITE_TO_PARENT(void) {
  /* send parent a message through pipe */
  // TODO
    counter++;
    write ( pipe_fd1 [ 1 ] , &counter , sizeof( counter ) ) ;
    printf("Child sends message to parent: %d\n" , counter);
}

void READ_FROM_PARENT(void) {
  /* read message sent by parent from pipe */
  // TODO
    read( pipe_fd1[ 0 ] , &counter , sizeof( counter ) ) ;
    printf("Child receives message from parent: %d\n" , counter);
}

void WRITE_TO_CHILD(void) {
  /* send child a message through pipe */
  // TODO
    counter++;
    write ( pipe_fd2 [ 1 ] , &counter , sizeof( counter ) ) ;
    printf("Parent sends message to child: %d\n" , counter);
}

void READ_FROM_CHILD(void) {
  /* read the message sent by child from pipe */
  // TODO
    read( pipe_fd2[ 0 ] , &counter , sizeof( counter ) ) ;
    printf("Parent receives message from child: %d\n" , counter);
}

int main(int argc, char* argv[]) {
    INIT();
    __pid_t pid;
    pid = fork();
    // set a timer, process will end after 10 seconds.
    alarm(10);
    if (pid == 0) {
        while (1) {
            sleep(rand() % 2 + 1);
            WRITE_TO_CHILD();
            READ_FROM_CHILD();
        }
    } else {
        while (1) {
            sleep(rand() % 2 + 1);
            READ_FROM_PARENT();
            WRITE_TO_PARENT();
        }
    }
    return 0;
}
