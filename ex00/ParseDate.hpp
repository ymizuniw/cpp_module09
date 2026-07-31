#ifndef PARSE_DATE_HPP
#define PARSE_DATE_HPP

#include "Date.hpp"
#include "Error.hpp"
#include <iostream>

Date parseDate(std::string const& s, Error& err);

#endif
