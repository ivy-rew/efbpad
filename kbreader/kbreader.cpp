#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include "_keymap.hpp"

static KeycodeTranslation kt;
struct input_event ev;
std::deque<char> chque;
int fd;
ssize_t nread;
int fd_status = 0;

int main(int argc, char* argv[]) {
  if(argc < 2) return -1;
  setbuf(stdout, NULL);
  fd = open(argv[1], O_RDONLY);
  if(fd < 0) return -1;
  while(access(argv[1], R_OK) == 0) {
    nread = read(fd, &ev, sizeof(ev));
    if (nread != sizeof(ev)) return -1;
    if(ev.value == 1 || ev.value == 2) kt.press(ev.code, chque);
    else if(ev.value == 0) kt.release(ev.code, chque);
    for(; !chque.empty(); chque.pop_front())
      printf("%i\n", chque.front()); // putchar(chque.front());
  }
  close(fd);
  return 0;
}

