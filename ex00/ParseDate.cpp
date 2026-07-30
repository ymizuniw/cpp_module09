# include "ParseDate.hpp"

bool check_dd_range(int dd, int mm, int yyyy)
{
    int thirty_first[] = {1,3,5,7,8,10,12,-1};
    int thirty[] = {4,6,9,11,-1};

    if (mm==2)
    {
        bool leap_year = ((yyyy%4==0 && yyyy%100!=0) || yyyy%400==0);
        if (leap_year)
        {
            if (!(1<=dd && dd<=29))
                return (false);
        }
        else
        {
            if (!(1<=dd && dd<=28))
                return (false);
        }
        return (true);
    }
    for (int idx=0;thirty_first[idx]!=-1;++idx)
    {
        if (mm==thirty_first[idx])
        {
            if (!(1<=dd && dd<=31))
                return (false);
            return (true);
        }
    }
    for (int idx=0;thirty[idx]!=-1;++idx)
    {
        if (mm==thirty[idx])
        {
            if (!(1<=dd && dd<=30))
                return (false);
            return (true);
        }
    }
    return (true);
}

bool check_date_range(std::string date, Error &err)
{
    int yyyy = 0;
    int mm = 0;
    int dd = 0;

    int i = 0;
    for (;i<4;++i)
        yyyy = yyyy*10 + (date[i] - '0');
    if (!(1900<yyyy && yyyy<=2100))
    {
        err.setError(1, err.line_num, "Invalid Date: [Year]: line: " + std::to_string(err.line_num) + ": " + date);
        return (false);
    }
    i++;
    for (;i<7;++i)
        mm = mm * 10 + (date[i] - '0');
    if (!(1<=mm && mm<=12))
    {
        err.setError(1, err.line_num, "Invalid Date: [Month]: line: " + std::to_string(err.line_num) + ": " + date);
        return (false);
    }
    i++;
    for (;i<10;++i)
        dd = dd * 10 + (date[i] - '0');
    if (!check_dd_range(dd, mm, yyyy))
    {
        err.setError(1, err.line_num, "Invalid Date: [Day]: line: " + std::to_string(err.line_num) + ": " + date);
        return (false);
    }
    return (true);
}

bool check_date_value(std::string const row_value, Error &err)
{
    return (check_date_range(row_value, err));
}

bool check_date_format(std::string date, Error &err)
{
    if (date.length() != 10)
    {
        err.setError(1, err.line_num, "Invalid Date: [Format]: line: " + std::to_string(err.line_num) + ": " + date);
        return (false);
    }
    int i=0;
    for (;i<4;++i)
    {
        if (!std::isdigit(date[i]))
        {
            err.setError(1, err.line_num, "Invalid Date: [Format]: line: " + std::to_string(err.line_num) + ": " + date);
            return (false);
        }
    }
    if (date[i++]!='-')
    {
        err.setError(1, err.line_num, "Invalid [Format]: line: " + std::to_string(err.line_num) + ": " + date);
        return (false);
    }
    for (;i<7;++i)
    {
        if (!std::isdigit(date[i]))
        {
            err.setError(1, err.line_num, "Invalid [Format]: line: " + std::to_string(err.line_num) + ": " + date);
            return (false);
        }
    }
    if (date[i++]!='-')
    {
        err.setError(1, err.line_num, "Invalid [Format]: line: " + std::to_string(err.line_num) + ": " + date);
        return (false);
    }
    for (;i<10;++i)
    {
        if (!std::isdigit(date[i]))
        {
            err.setError(1, err.line_num, "Invalid [Format]: line: " + std::to_string(err.line_num) + ": " + date);
            return (false);
        }
    }
    return (true);
}

Date parseDate(std::string const &s, Error &err)
{
    if (!check_date_format(s, err))
        return (Date(-1,-1,-1, err));
    if (!check_date_value(s, err))
        return (Date(-1,-1,-1, err));
    // 2022-03-29
    int year = 0;
    int month = 0;
    int day = 0;
    int i = 0;
    while (i<4)
    {
        year = year*10 + (s[i]-'0');
        i++;
    }
    i++;
    while (i<7)
    {
        month = month*10 + (s[i]-'0');
        i++;
    }
    i++;
    while (i<10)
    {
        day = day*10 + (s[i]-'0');
        i++;
    }
    return (Date(day, month, year, err));
}
