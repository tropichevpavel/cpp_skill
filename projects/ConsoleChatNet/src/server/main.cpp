
#include "core/UDPServer.h"

int main()
{
	Server server;
	if (server.init()) server.listen();
	return 0;
}
