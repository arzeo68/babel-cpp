/*
** EPITECH PROJECT, 2020
** babel
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "common/TCP/CommonPackages.hpp"
#include "Callback.hpp"
#include "server/src/Network/Worker.hpp"
#include "server/src/Route/List/Utils.hpp"

Common::Response Server::Route::Listing::StartCall(
    std::shared_ptr<Server::Network::Client> &client,
    const Server::Route::Arguments::RouteHandlerArgs &arg) {
    if (arg.body.empty())
        return Common::BadRequestTemplate;
    if (arg.method != Common::HTTP_POST)
        return Common::InvalidMethodTemplate;
    std::cerr << "Dest " << client->GetUserData().GetName() << " w/ " <<
              client->GetUserData().GetCallState() << " and "
              << client->GetUserData().GetCallerName() << std::endl;
    if (client->GetUserData().GetCallState() != Common::NONE)
        return (Common::Response{
            Common::HTTPCodes_e::HTTP_FORBIDDEN,
            "false - not in call"
        });

    if (auto destClient = client->GetNetwork()->GetClientFromName(
        arg.body[0])) {
        if (!(*destClient)->GetUserData().IsConnected())
            return (Common::Response{
                Common::HTTPCodes_e::HTTP_NOT_FOUND,
                "false",
            });
        std::cerr << "Author: " << client->GetUserData().GetName() << " w/ "
                  << client->GetUserData().GetName() << " && "
                  << (*destClient)->GetUserData().GetName() << " w/ "
                  << (*destClient)->GetUserData().GetCallerName() << std::endl;
        if ((*destClient)->GetUserData().GetCallState() !=
            Common::CallState::NONE) {
            if ((*destClient)->GetUserData().GetCallerName() ==
                client->GetUserData().GetName() &&
                client->GetUserData().GetCallState() ==
                Common::CallState::PENDING)
                return (Utils::ChangeStateCall(client, *destClient,
                                               Common::CallState::ACCEPTED));
            else
                return (Common::Response{
                    Common::HTTPCodes_e::HTTP_FORBIDDEN,
                    "false - wrong caller"
                });
        }
        Common::Response request = {
            Common::HTTPCodes_e::FAKE_HTTP_NOTIFICATION,
            "",
        };
        int port = rand() % (0xFFFF - 0xFDE8 + 1) + 0xFDE8;
        _strcpyC(request.msg, std::string(
            "CALL|START|" + client->GetUserData().GetName() + "|" +
            client->GetUserData().GetIP() +
            "|" + std::to_string(port)).c_str());
        client->GetWorker()->AddNotification(request, arg.body[0]);
        Utils::NotifyUserStatusToFriends(client, Utils::UserState::BUSY);
        (*destClient)->GetUserData().SetCallState(Common::CallState::PENDING,
                                                  client->GetUserData().GetName());
        client->GetUserData().SetCallState(Common::CallState::PENDING,
                                           (*destClient)->GetUserData().GetName());
        std::cerr << "Dest " << (*destClient)->GetUserData().GetName() << " w/ "
                  << (*destClient)->GetUserData().GetCallState() <<
                  " and " << (*destClient)->GetUserData().GetCallerName()
                  << std::endl;
        _strcpyC(request.msg,
                 std::string((*destClient)->GetUserData().GetIP() + "|" +
                             std::to_string(port)).c_str());
        request.code = Common::HTTPCodes_e::HTTP_OK;
        return (request);
    } else {
        return (Common::Response {
            Common::HTTPCodes_e::HTTP_INTERNAL_SERVER_ERROR,
            "false",
        });
    }
}

Common::Response
Server::Route::Listing::EndCall(
    std::shared_ptr<Server::Network::Client> &client,
    const Server::Route::Arguments::RouteHandlerArgs &arg) {
    if (arg.method != Common::HTTP_POST)
        return Common::InvalidMethodTemplate;
    if (client->GetUserData().GetCallState() == Common::CallState::NONE)
        return (Common::Response {
            Common::HTTPCodes_e::HTTP_FORBIDDEN,
            "false"
        });
    if (auto destClient = client->GetNetwork()->GetClientFromName(
        arg.body[0])) {
        Utils::NotifyUserStatusToFriends(client, Utils::UserState::CONNECTED);
        Utils::NotifyUserStatusToFriends((*destClient),
                                         Utils::UserState::CONNECTED);
        if (client->GetUserData().GetCallState() == Common::CallState::ACCEPTED)
            return (Utils::ChangeStateCall(client, *destClient,
                                           Common::CallState::ENDED));
        else
            return (Utils::ChangeStateCall(client, *destClient,
                                           Common::CallState::DECLINED));
    } else {
        return (Common::Response {
            Common::HTTPCodes_e::HTTP_INTERNAL_SERVER_ERROR,
            "false",
        });
    }
}
