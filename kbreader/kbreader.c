#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include "_keymap.h"

static struct input_event ev;
static int fd;
static int fd_status = 0;
static ssize_t nread;

int main(int argc, char* argv[]) {
  if(argc < 2) return -1;
  setbuf(stdout, NULL);
  int fd = open(argv[1], O_RDONLY);
  if(fd < 0) return -1;
  while(access(argv[1], R_OK) == 0) {
    nread = read(fd, &ev, sizeof(ev));
    if (nread != sizeof(ev)) {
      perror("Bad event read.");
      return -1;
    }
    if(!(ev.type == EV_KEY)) continue; 
    if(ev.value == 1 || ev.value == 2) printf("%s", key_press(ev.code));
    else if(ev.value == 0) key_release(ev.code);
  }
  close(fd);
  return 0;
}

