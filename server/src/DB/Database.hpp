/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Class handling database connection and stuffs w/ sqlite
*/

#ifndef BABEL_DATABASE_HPP
#define BABEL_DATABASE_HPP

#include <exception>
#include <cstdint>
#include <string>
#include <sqlite3.h>
#include "common/Log.hpp"
#include "IDatabase.hpp"

namespace Server::Database {
    namespace User {
        enum Data : uint8_t {
            ID = 0,
            NAME = 1,
            PASSWORD = 2,
            STATUS = 3
        };
    }

    class Database : public IDatabase {
        public:
        explicit Database(Common::Log::Log& logger);
        ~Database() override;

        bool ConnectUser(const std::string& name,
                         const std::string& password) override;
        bool
        AddUser(const std::string& name, const std::string& password) override;
        bool UserExists(const std::string& name) override;
        void UpdateStatus(const std::string& name,
                          const std::string& status) override;
        void RegisterTables();

        private:
        typedef int (*DatabaseCallback_t)(void *, int, char **, char **);
        sqlite3 *_handler;
        Common::Log::Log _logger;

        void ExecuteQuery(const std::string& query,
                          DatabaseCallback_t callback = nullptr,
                          void *callback_arg = nullptr);
    };

    namespace Exception {
        class Opening : std::exception {
            public:
            explicit Opening(uint32_t code);
            ~Opening() override = default;

            const char *what() const noexcept override;

            private:
            uint32_t _code;
        };

        class Query : std::exception {
            public:
            Query(uint32_t code, char *error, const std::string& query);
            ~Query() override = default;

            const char *what() const noexcept override;

            private:
            uint32_t _code;
            std::string _error;
            std::string _query;
        };
    };
}


#endif //BABEL_DATABASE_HPP
