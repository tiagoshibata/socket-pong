#include <unistd.h>

#include "display.h"
#include "socket.h"

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "Usage: pong-client host port\n");
        return -1;
    }
    int sock = connect_to(argv[1], argv[2]);
    if (sock < 0)
        return -1;
    display_init();

    close(sock);
	return 0;
}
