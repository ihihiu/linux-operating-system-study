#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdlib.h>

void main()
{
	int sp, sa;
	struct sockaddr_in ad;

	memset(&ad, 0, sizeof(ad));
	ad.sin_family=AF_INET;
	ad.sin_addr.s_addr=htonl(INADDR_ANY);
	ad.sin_port=htons(11234);

	sp = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(sp, (struct sockaddr *) &ad, sizeof(ad));

	listen(sp, 10);
	while(1){
		sa=accept(sp,0,0);
		write(sa, "Test", 5);
		close(sa);
	}
}

