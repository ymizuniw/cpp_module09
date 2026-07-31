# include <sstream>
# include <iomanip>

std::string int_to_string(int n)
{
    std::stringstream ss;
    ss << n;
    return (ss.str());
}

std::string float_to_string(float n)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << n;
    return (ss.str());
}

// int main(void)
// {
//     int n = 100;
//     std::cout << int_to_string(n) << std::endl;
//     return (0);
// }
