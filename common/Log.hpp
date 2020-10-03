/*
** EPITECH PROJECT, 2020
** babel
** File description:
** Simple logger.
*/

#ifndef BABEL_LOG_HPP
#define BABEL_LOG_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <ctime>
#include <iomanip>


namespace Common::Log {
    enum LogLevel_e : uint16_t {
        DEBUG = 0b0001u,
        INFO = 0b0010u,
        WARN = 0b01000u,
        ERROR = 0b10000u,
    };

    class Log {
        public:
        explicit Log(const std::string &title, const std::string &path,
                     uint8_t log_level = DEBUG | INFO | WARN | ERROR);

        ~Log() = default;

        template<typename ...variadic>
        void Debug(variadic &&... args) {
            return (this->Write(DEBUG, args...));
        }

        template<typename ...variadic>
        void Warning(variadic &&... args) {
            return (this->Write(WARN, args...));
        }

        template<typename ...variadic>
        void Error(variadic &&... args) {
            return (this->Write(ERROR, args...));
        }

        template<typename ...variadic>
        void Info(variadic &&... args) {
            return (this->Write(INFO, args...));
        }


        private:
        static std::string GetCurrentTime() {
            time_t rawtime;
            struct tm *timeinfo;
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            char buffer[80];
            strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
            return (buffer);
        }

        template<typename ...variadic>
        void Write(LogLevel_e level, variadic &&... args) {
            if ((level & this->_level) == 0)
                return;
            std::string prefix("[" + Common::Log::Log::GetCurrentTime() + "/" +
                               _map.find(level)->second + "]" + " ");
            std::cout << prefix;
            (std::cout << ... << args) << std::endl;
            this->_file << prefix;
            (this->_file << ... << args) << std::endl;
        }

        std::string _title;
        std::ofstream _file;
        LogLevel_e _level;
        const std::map<uint8_t, std::string> _map = {
            {DEBUG, "debug"},
            {INFO,  "info"},
            {WARN,  "warning"},
            {ERROR, "error"},
        };
    };

    class InvalidPath : std::exception {
        public:
        explicit InvalidPath(const std::string &path);

        const char *what() const noexcept override;

        private:
        std::string _path;
    };
}


#endif //BABEL_LOG_HPP
