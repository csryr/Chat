#include "chatServer.h"

int main()
{

    io::io_context io_context;
    server srv(io_context, 7777);

    srv.async_accept();
    io_context.run();
    return 0;
}