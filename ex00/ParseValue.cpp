
#include "ParseValue.hpp"
#include <sstream>
#include <iostream>
#include "utils.hpp"

static float try_parse_value(std::string const& val, Error& err)
{
    float try_val;
    std::stringstream ss;
    ss << val;
    ss >> try_val;
    if (ss.fail())
        err.setError(1, err.line_num,
                     "Invalid Value: line: " + int_to_string(err.line_num) + " : " + val);
    return (try_val);
}

float parseValue(std::string const& val, Error& err)
{
    float try_val = try_parse_value(val, err);

    if (err.err_num != 0)
        return (try_val);
    if (try_val < 0.f)
        err.setError(1, err.line_num,
                     "Invalid Value: Not a Positive: line: " + int_to_string(err.line_num) +
                         " : " + val);
    else if (try_val > 1000.f)
        err.setError(1, err.line_num,
                     "Invalid Value: Too Large: line: " + int_to_string(err.line_num) + " : " +
                         val);
    return (try_val);
}
