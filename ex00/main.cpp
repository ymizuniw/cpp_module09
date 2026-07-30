#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>
#include "DBFile.hpp"
#include "InputFile.hpp"
#include "Date.hpp"

/*
    multimapを使用する
*/
//date validation
/*
    1. the length : 2000-01-01 = 10
    2. check [four digits] [-] [two digits] [-] [two digits]
    3. get yyyy[four digits] (skip++) mm[two digits] (skip++) dd[two digits]
    4. check the range of year, mon, and day.
*/

/*
    ・データベースの検証は、フォーマットエラーが発見されたタイミングで例外を投げる処理でよく、
    状態を返す必要はない。ユーザ定義ではなく内部エラーとみなすからである。
    ・入力ファイルの検証は、1.フォーマットエラー 2.値エラー （date_format > date_value > value_format > value_value）の優先度で処理する。
    ・つまり、これは単なるバリデーションではなくノードごとの状態を持つ構造体を作成する関数である必要がある。
    ・保有量とレートを掛け算して値を算出する必要があるため、日付は文字列で良いが、値はfloatで保存する必要がある。
*/

// search the exact or lower Date for the value-rate matching
std::multimap<Date, float> generateDateReference(std::multimap<Date, float> const &db, std::multimap<Date, float> const &input)
{
    std::multimap<Date, float> ref_data;

    std::multimap<Date, float>::const_iterator db_start = db.begin();
    std::multimap<Date, float>::const_iterator db_end = db.end();
    std::multimap<Date, float>::const_iterator input_it = input.begin();
    std::multimap<Date, float>::const_iterator input_end = input.end();
    std::multimap<Date, float>::const_iterator target_it;
    
    while (input_it!=input_end)
    {
        Date new_date;
        if ((*input_it).first.getError().err_num!=0)
        {
            ref_data.insert(std::make_pair((*input_it).first, (*input_it).second));
            ++input_it;
            continue;
        }
        if (*target_it<*db_start)
        {
            //not found
            new_date = (*input_it).first;
            new_date.setError(2, new_date.getError().line_num, "Not Found [Date]: line: " + std::to_string(new_date.getError().line_num) + " : " + new_date.to_string());
            ref_data.insert(std::make_pair(new_date, (*input_it).second));
            ++input_it;
            continue;
        }
        target_it = std::lower_bound(db_start, db_end, *input_it);
        --target_it;

        float new_val = 0.f;
        if (new_date.getError().err_num==0)
            new_val = (*target_it).second * (*input_it).second;
        else
            new_val = 0.f;
        std::pair<Date, float> pair = std::make_pair((*target_it).first, new_val);
        ref_data.insert(pair);
        ++input_it;
    }
    return (ref_data);
}

// error handling based on the error status of each nodes are needed.
void print_data(std::multimap<Date, float> data)
{
    std::multimap<Date,float>::const_iterator it = data.cbegin();
    std::multimap<Date,float>::const_iterator end_it = data.cend();

    while (it!=end_it)
    {
        if ((*it).first.getError().err_num!=0)
        {
            std::cout << (*it).first.getError().err_msg << std::endl;
            ++it;
            continue;
        }
        std::cout << (*it).first.to_string() + " => " + std::to_string((*it).second) << std::endl;
        ++it;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return (1);
    
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
        print_data(ref);
    } catch(std::exception &e){
        std::cout << e.what() << std::endl;
        return (1);
    }
    return(0);
}
