#include <boost/asio.hpp>
#include <optional>
#include <unordered_set>
#include <iostream>
#include <string>
#include <sstream>

namespace io = boost::asio;
using tcp = io::ip::tcp;
using error_code = boost::system::error_code;
using namespace std::placeholders;


class session;

class chat_room
{

public:
    void post(std::string const &message);
    void remove(std::shared_ptr<session>);
    std::unordered_set<std::shared_ptr<session>> participants;
};

class session : public std::enable_shared_from_this<session>
{
public:
    session(tcp::socket &&socket, chat_room &room);
    void start();
    void read();
    void on_read(error_code error, std::size_t bytes_transferred);
    void on_send(const std::string &message);
    void send(const std::string &message);

    chat_room &room_;
    tcp::socket socket;
    io::streambuf streambuf;
};

class server
{

public:
    server(io::io_context &io_context, std::uint16_t port);

    void async_accept();

private:
    io::io_context &io_context;
    tcp::acceptor acceptor;
    std::optional<tcp::socket> socket;
    chat_room room_;
};
