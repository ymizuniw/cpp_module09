# ifndef PARSE_VALUE_HPP
# define PARSE_VALUE_HPP

# include <string>
# include <sstream>
# include "Error.hpp"

float parseValue(std::string const &val, Error &err);

# endif
