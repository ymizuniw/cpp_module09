#include "DBFile.hpp"
#include "Date.hpp"
#include "InputFile.hpp"
#include "utils.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <string>

// search the exact or lower Date for the value-rate matching
std::multimap<Date, float> generateDateReference(std::multimap<Date, float> const& db,
                                                 std::multimap<Date, float> const& input)
{
    std::multimap<Date, float> ref_data;

    std::multimap<Date, float>::iterator db_start = db.begin();
    std::multimap<Date, float>::iterator db_end = db.end();
    std::multimap<Date, float>::iterator input_it = input.begin();
    std::multimap<Date, float>::iterator input_end = input.end();
    std::multimap<Date, float>::iterator target_it;

    while (input_it != input_end) {
        Date input_date = (*input_it).first;
        float input_value = (*input_it).second;

        // input_date hass error
        if (input_date.getError().err_num != 0) {
            ref_data.insert(std::make_pair(input_date, input_value));
            std::cout << input_date.getError().err_msg << std::endl;
            ++input_it;
            continue;
        }
        // no date lower than or equal to input_date
        if (input_date < (*db_start).first) {
            input_date.setError(
                2, input_date.getError().line_num,
                "Not Found [Date]: line: " + int_to_string(input_date.getError().line_num) + " : " +
                    input_date.to_string());
            ref_data.insert(std::make_pair(input_date, input_value));
            std::cout << input_date.getError().err_msg << std::endl;
            ++input_it;
            continue;
        }
        // exact match iterator of input_date and db date
        target_it = db.find(input_date);
        // if no exact match found, get the iterator of db date lower than or equal to input_date
        if (target_it == db_end) {
            target_it = std::lower_bound(db_start, db_end, *input_it);
            --target_it;
        }

        float target_value = (*target_it).second;
        float new_val = 0.f;

        if (input_date.getError().err_num == 0)
            new_val = target_value * input_value;
        ref_data.insert(std::make_pair(input_date, new_val));
        std::cout << input_date.to_string() + " => " + float_to_string(input_value) + " => " +
                         float_to_string(new_val)
                  << std::endl;
        ++input_it;
    }
    return (ref_data);
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "Usage: ./btc <input.csv>" << std::endl;
        return (1);
    }

    try {
        DBFile db("data.csv");
        db.openFile();
        db.checkFormat();
        db.parseFile();

        InputFile input(argv[1]);
        input.openFile();
        input.checkFormat();
        input.parseFile();

        std::multimap<Date, float> ref = generateDateReference(db.getRecord(), input.getRecord());
        // print_data(ref);
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return (1);
    }
    return (0);
}
