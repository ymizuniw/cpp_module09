
# include "Date.hpp"

Date::Date(): err_() {}
Date::Date(int day, int month, int year, Error &err): day_(day), month_(month), year_(year), err_(err){}
Date::Date(const Date &other){ if (this==&other) return ; day_=other.day_; month_=other.month_; year_=other.year_; err_=other.err_;}
Date &Date::operator=(const Date &other){ if (this==&other) return(*this); day_=other.day_; month_=other.month_; year_=other.year_; err_=other.err_; return (*this);}
bool Date::operator<(const Date &rhs){if (year_<rhs.year_) return (true); else if (year_>rhs.year_) return (false); else if (month_<rhs.month_) return (true); else if (month_>rhs.month_) return (false); else if (day_<rhs.day_) return (true); else if (day_>rhs.day_) return (false); return (false);}
Date::~Date(){}
