#include <boost/asio.hpp>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace boost::asio;
using namespace boost::asio::ip;

string readData(tcp::socket &socket);

void sendData(tcp::socket &socket, const string &message);

void readerT(tcp::socket &data_socket2);

void writerT(tcp::socket &data_socket, string reply, const string &u_name);
