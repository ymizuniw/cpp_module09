# ifndef DATE_HPP
# define DATE_HPP

# include "Error.hpp"

class Date {
    private:
        int day_;
        int month_;
        int year_;
        Error err_;
    public:
        Date();
        Date(int day, int month, int year, Error &err);
        Date(const Date &other);
        Date &operator=(const Date &other);
        bool operator<(const Date &rhs) const;
        ~Date();
        Error getError() const;
        void setError(int err_num, int line_num, std::string err_msg);
        std::string to_string() const;
};

# endif
