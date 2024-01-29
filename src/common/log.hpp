#pragma once

#include <iostream>
#include <string>

namespace rlog {

// logs info from an API to stdout through std::cout. Takes the form of
// [NAME]: <message>
void info(const std::string&, const std::string&);

// logs general information to the stdout
void info(const std::string&);

// logs warnings to the stdout with a [WARNING] tag coloured in orange
void warning(const std::string&);

// log a warning with an additional tag
void warning(const std::string&, const std::string&);

// logs errors to the stdoput with an [ERROR] tag coloured in red
void error(const std::string&);

// does the same thing as the similar definition to error, except displays an
// API error instead
void error(const std::string&, const std::string&);

}
