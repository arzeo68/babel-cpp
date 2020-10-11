/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Generic classes used to create the routes for the API
*/

#include "Route.hpp"

Server::Route::Route::Route(const std::string &name,
                            Server::Route::Route::RouteHandler_t handler) :
    _name(name), _handler(handler) {
}

Common::Response
Server::Route::Route::ExecuteHandler(
    std::shared_ptr<Server::Network::Client> &client,
    Arguments::RouteHandlerArgs const &args) const {
    return (this->_handler(client, args));
}

bool Server::Route::Route::operator==(const std::string &name) {
    return (this->_name == name);
}

bool Server::Route::Route::operator==(const std::string &name) const {
    return (this->_name == name);
}

bool Server::Route::Route::operator!=(const std::string &name) const {
    return (this->_name != name);
}

bool Server::Route::Route::operator!=(const std::string &name) {
    return (this->_name != name);
}

Server::Route::Route::Route(const Route &obj) {
    this->_handler = obj._handler;
    this->_name = obj._name;
    this->_method = obj._method;
}
