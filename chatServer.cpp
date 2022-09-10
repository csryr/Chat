#include "chatServer.h"

void chat_room::post(std::string const &message)
{
    for (auto &client : participants)
    {
        client->send(message);
    }
}

void chat_room::remove(std::shared_ptr<session> participant)
{

 participants.erase(participant);

}

session::session(tcp::socket &&socket, chat_room &room)
    : socket(std::move(socket)),
      room_(room)
{
}

void session::start()
{

    read();
}

void session::read()
{

    io::async_read_until(socket, streambuf, "\n", std::bind(&session::on_read, shared_from_this(), _1, _2));
}

void session::on_read(error_code error, std::size_t bytes_transferred)
{

    if (!error)
    {

        std::ostringstream a;
        a << std::istream(&streambuf).rdbuf();
        streambuf.consume(bytes_transferred);
        std::string b = a.str();
        std::cout << b;
        on_send(b);
        read();
    }
    else{

        room_.remove(shared_from_this());
        room_.post("\r A User has disconnected! \n");
        socket.close();

    }
}

void session::on_send(const std::string &message)
{

    room_.post(message);
}

void session::send(const std::string &message)
{

    boost::asio::write(socket, boost::asio::buffer(message + "\n"));
}
server::server(io::io_context &io_context, std::uint16_t port)
    : io_context(io_context), acceptor(io_context, tcp::endpoint(tcp::v4(), port))
{
}

void server::async_accept()
{
    socket.emplace(io_context);

    acceptor.async_accept(*socket, [&](error_code error)
                          {
                              auto client = std::make_shared<session>(std::move(*socket), room_);
                              room_.participants.insert(client);                            
                              client->start();                             
                              async_accept(); });
}
