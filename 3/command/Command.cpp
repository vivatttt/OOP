#include "../command/Command.h"
#include <chrono>

Command::Command() : 
    command_type(set_acceleration), 
    value(0.0)
    {
        timestamp = std::chrono::steady_clock::now();
    }
Command::Command(CommandType _command_type, double _value) : 
    command_type(_command_type), 
    value(_value)
    {
        timestamp = std::chrono::steady_clock::now();
    }