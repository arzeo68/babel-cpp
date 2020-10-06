/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Router
*/

#include <boost/algorithm/string.hpp>
#include "Router.hpp"

Common::Response Server::Router::Execute(const Common::PackageServer &protocol,
                                         Route::Arguments::RouteHandlerArgs const &args,
                                         Server::Network::Client& client) {
    if (protocol.id >= MAX_ROUTE_ID)
        return (Common::Response {
            Common::HTTPCodes_e::NOT_FOUND,
            "Unknown route"
        });
    else if (protocol.magic != Common::g_MagicNumber)
        return (Common::Response {
            Common::HTTPCodes_e::FORBIDDEN,
            "Forbidden"
        });
    else
        return (this->_routes[protocol.command].ExecuteHandler(client, args));
}

Common::PackageServer Server::Router::FormatRouteArgs(const std::string &string) {
    return *(struct Common::PackageServer *) string.data();
}

Server::Route::Arguments::RouteHandlerArgs
Server::Router::SplitRawData(const Common::PackageServer &protocol) {
    Route::Arguments::RouteHandlerArgs handler;
    std::vector<std::string> subStr;
    // TODO: Escape split character: |
    boost::split(subStr, std::string(protocol.args), boost::is_any_of("|"));

    if (!subStr.empty())
        for (auto& k : subStr)
            handler.body.push_back(k);
    handler.method = protocol.method;
    return (handler);
}
