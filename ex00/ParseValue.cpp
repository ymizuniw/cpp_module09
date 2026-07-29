
# include "ParseValue.hpp"

float try_parse_value(std::string const &val, Error &err)
{
    float try_val = 0.0;
    std::stringstream ss(val);
    ss.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    ss >> try_val;
    if (ss.fail())
    {
        err.set_error(1, err.line_num, "Invalid Value: line: " + std::to_string(err.line_num) + " : " + val);
        throw std::runtime_error("DB: " + err.err_msg);
    }
    return (try_val);
}

float parseValue(std::string const &val, Error &err)
{
    float try_val = try_parse_value(val, err);
    if (err.err_num!=0)
        return (try_val);
    if (try_val<0.f)
    {
        throw std::runtime_error("DB: Invalid Value: Not a Positive: line: " + std::to_string(err.line_num) + " : " + val);
        // err.set_error(1, err.line_num, "Invalid Value: Not a Positive: line: " + std::to_string(err.line_num) + " : " + val);
    }
    if (try_val>1000.f)
    {
        throw std::runtime_error("DB: Invalid Value: Too Large: line: " + std::to_string(err.line_num) + " : " + val);
        // err.set_error(1, err.line_num, "Invalid Value: Too Large: line: " + std::to_string(err.line_num) + " : " + val);
    }
    return (try_val);
}
