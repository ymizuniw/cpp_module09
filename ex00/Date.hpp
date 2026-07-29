# ifndef DATE_HPP
# define DATE_HPP

class Date {
    private:
        int day_;
        int month_;
        int year_;
    public:
        Date();
        Date(int day, int month, int year);
        Date(const Date &other);
        Date &operator=(const Date &other);
        bool operator<(const Date &rhs);
        ~Date();
};

# endif
