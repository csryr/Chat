#include "chatClient.h"

string readData(tcp::socket &socket)
{
    boost::asio::streambuf buf;
    boost::asio::read_until(socket, buf, "\n");
    string data = buffer_cast<const char *>(buf.data());
    return data;
}
void sendData(tcp::socket &socket, const string &message)
{
    write(socket, buffer(message + "\n"));
}
void readerT(tcp::socket &data_socket2)
{
    while (true)
    {

        string response = readData(data_socket2);
        response.pop_back();
        cout << '\r' << response;
    }
}

void writerT(tcp::socket &data_socket, string reply, const string &u_name)
{

    while (true)
    {

        std::this_thread::sleep_for(0.05s);
        cout << "Send message: ";
        getline(cin, reply);
        printf("\033[A\33[2K\r");
        reply = u_name + ": " + reply;
        sendData(data_socket, reply);
    }
}