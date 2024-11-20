#ifndef COMMAND_H
#define COMMAND_H

#include <chrono>
#include <string>

enum CommandType {
    set_acceleration,
    set_angular_acceleration,
};

class Command {
    public:
        Command();
        Command(CommandType _command_type, double _value);
        std::chrono::time_point<std::chrono::steady_clock> timestamp;
        double value;
        CommandType command_type;
};

#endif