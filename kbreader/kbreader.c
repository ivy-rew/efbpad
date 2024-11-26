#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include "_keymap.h"

static struct input_event ev;
int main(int argc, char* argv[]) {
  if(argc < 2) return -1;
  setbuf(stdout, NULL);
  int fd = open(argv[1], O_RDONLY);
  if(fd < 0) {
    perror("Couldn't open event device.");
    return -1;
  }
  while(1) {
    ssize_t n = read(fd, &ev, sizeof(ev));
    if (n != sizeof(ev)) {
      perror("Bad event read.");
      return -1;
    }
    if(!(ev.type == EV_KEY)) continue; 
    if(ev.value == 1 || ev.value == 2) {
      const char *s = key_press(ev.code);
      n = strlen(s);
      if(printf("%s",s) < n) {
	perror("Failed to print to stdout.");
	return -1;
      }
    }
    else if(ev.value == 0) key_release(ev.code);
  }
  close(fd);
  return 0;
}
