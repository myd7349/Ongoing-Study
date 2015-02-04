// 2015-02-03T12:02+08:00

#include "command.h"

#include <iostream>

Command::Command() : options_desc_("Options") 
{
}

void Command::help() const
{
    std::cout << options_desc_;
}

void Command::notify_err(const char *what, const utility::string_t &command)
{
    ucerr << U("Failed to parse \"") << command << U("\" command: ");
    std::cerr << what << ". ";
    ucerr << U("Type \"help ") << command << U("\" for the usage of this command.\n");
}