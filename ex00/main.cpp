#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>

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

std::vector<DateValue> generate_date_reference(std::vector<DateValue> const &db_data, std::vector<DateValue> const &input_data)
{
    std::vector<DateValue> ref_data;

    std::vector<DateValue>::const_iterator db_start = db_data.begin();
    std::vector<DateValue>::const_iterator db_end = db_data.end();
    std::vector<DateValue>::const_iterator input_it = input_data.begin();
    std::vector<DateValue>::const_iterator input_end = input_data.end();
    std::vector<DateValue>::const_iterator target_it;
    
    while (input_it!=input_end)
    {
        DateValue new_date;

        if ((*input_it).err.err_num!=0)
        {
            new_date = (*input_it);
            ref_data.push_back(new_date);
            ++input_it;
            continue;
        }
        target_it = std::lower_bound(db_start, db_end, *input_it);
        if (target_it==db_end)
        {
            //not found
            new_date = (*input_it);
            setError(new_date.err, 2, new_date.err.line_num, "Not Found [Date]: line: " + std::to_string(new_date.err.line_num) + " : " + new_date.date);
            ref_data.push_back(new_date);
            ++input_it;
            continue;
        }
        else
        {
            new_date.date = (*target_it).date;
            new_date.err = (*target_it).err;
            if (new_date.err.err_num==0)
                new_date.val = (*target_it).val * (*input_it).val;
            else
                new_date.val = 0.f;
        }
        ref_data.push_back(new_date);
        ++input_it;
    }
    return (ref_data);
}

// bool operator<(const DateValue &other) const; to compare DateValue struct by Date
bool DateValue::operator<(const DateValue &other) const
{
    return (this->date < other.date);
}

// error handling based on the error status of each nodes are needed.
void print_data(std::vector<DateValue> &data)
{
    std::vector<DateValue>::iterator it = data.begin();
    std::vector<DateValue>::iterator end_it = data.end();

    while (it!=end_it)
    {
        if ((*it).err.err_num!=0)
        {
            std::cout << (*it).err.err_msg << std::endl;
            ++it;
            continue;
        }
        std::cout << (*it).date + " => " + std::to_string((*it).val) << std::endl;
        ++it;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        return (1);

    std::ifstream input_file_stream(argv[1], std::ios_base::in);
    
    input_file_stream.exceptions(std::ios_base::badbit);

    try {
        check_fstream_open(input_file_stream);
        check_csv_file(input_file_stream,"date | value", false);

        std::vector<std::vector<std::string> > db_nodes = csv_parser(db_file_stream, ',', true);
        std::vector<std::vector<std::string> > input_nodes = csv_parser(input_file_stream, '|', false);
        trim_spaces_from_input(input_nodes);

        std::vector<DateValue> db_data = parse_data(db_nodes, true);
        std::vector<DateValue> input_data = parse_data(input_nodes, false);

        std::sort(db_data.begin(), db_data.end());
        std::sort(input_data.begin(), input_data.end());
        std::vector<DateValue> referenced_data = generate_date_reference(db_data, input_data);
        print_data(referenced_data);
    } catch(std::exception &e){
        std::cout << e.what() << std::endl;
        return (1);
    }
    return(0);
}
