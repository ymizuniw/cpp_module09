# ifndef PARSE_DATE_HPP
# define PARSE_DATE_HPP

# include "Error.hpp"
# include <iostream>
# include "Date.hpp"

Date parseDate(std::string const &s, Error &err);

# endif
