#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void main(){
	int sp;
	char buf[5];
	struct sockaddr_in ad;

	sp = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&ad, 0, sizeof(ad));
	ad.sin_family=AF_INET;
	ad.sin_addr.s_addr=inet_addr("127.0.0.1");
	ad.sin_port=htons(11234);

	connect(sp, (struct sockaddr * ) &ad, sizeof(ad));

	read(sp, buf, 5);
	printf("%s", buf);

	close(sp);
	exit(0);
}
