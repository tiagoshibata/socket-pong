#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int connect_to(const char *addr, const char *port)
{
    struct addrinfo hints, *addresses_info, *info;
    int sock, ret;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if ((ret = getaddrinfo(addr, port, &hints, &addresses_info))) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ret));
        return -1;
    }
	for (info = addresses_info; info != NULL; info = info->ai_next) {
		if ((sock = socket(info->ai_family, info->ai_socktype, info->ai_protocol)) != -1) {
			if (!connect(sock, info->ai_addr, info->ai_addrlen))
                break;
            fprintf(stderr, "Connecting to family %d, type %d, proto %d", info->ai_family, info->ai_socktype, info->ai_protocol);
            if (info->ai_family == AF_INET || info->ai_family == AF_INET6) {
                char addr_str[INET6_ADDRSTRLEN];
                inet_ntop(info->ai_family, info->ai_addr, addr_str, INET6_ADDRSTRLEN);
                fprintf(stderr, ", %s", addr_str);
            }
            fprintf(stderr, " failed: ");
			perror("connect");
			close(sock);
		}
	}
    freeaddrinfo(addresses_info);
	if (info == NULL) {
		fprintf(stderr, "Failed to connect to %s:%s\n", addr, port);
		return -1;
	}
    return sock;
}
