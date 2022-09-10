#include "chatClient.h"

int main(int argc, char *argv[])
{

    string u_name, reply;
    io_context io_context;
    ip::tcp::socket client_socket(io_context);
    client_socket.connect(tcp::endpoint(address::from_string("127.0.0.1"), 7777));

    cout << "Enter your name: ";
    getline(cin, u_name);
    sendData(client_socket, u_name + " has joined!");

    std::thread t1(readerT, std::ref(client_socket));
    std::thread t2(writerT, std::ref(client_socket), reply, u_name);

    t1.join();
    t2.join();
    return 0;
}