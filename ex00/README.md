要件を整理します。

- [仕様] プログラム名は　btc
- [仕様] 一つのファイルを引数に取得する
- [仕様] プログラムは内部DBを持つ
- [前提]　プログラムの内部DBは次のフォーマットに従っている: 
"date,value"
ex)
2022-03-25,44334.33
2022-03-29,47115.93

- [前提] プログラムの引数ファイルの各行は次のフォーマットに従う:  "date | value" 
- [検証] 有効な日付は次のフォーマットに従う: Year-Month-Day
- [検証] 有効な値は正の単精度浮動小数（float）か正の整数(int)で、0以上100以下
- [仕様] c++98で使用可能なコンテナを一つ使用する。このプログラムにはstd::vector<>を使用する。ex01でstd::stack<>, ex02でstd::map<>を使用する。

## プログラムの処理
1. プログラムが引数を受け取る。
2. DBファイルの存在+読み取り権限をチェック
3. ファイルを1行読み取り、"date,exchange_rate"を検証
4. ファイルの存在+読み取り権限をチェック
5. ファイルを一行読み取り、"date | value"を検証
6. Invalid Format と　Value Error の２段階で検証


## パーサの実装方針
1. '|' で行を分割
2. date と　value それぞれの分割された部分文字列についてパース

### Dateの要件
・Year(type=int,size=(1,4), range=(0,2027))
・-(type=char,size=1, exact-match)
・Month(type=int,size=2,range=(01,12))
・-(type=char,size=1, exact-match)
・Day(type=int,size=2,range=DayOfMonth)
・DayOfMonth
- ThirtyFirst=(1,3,5,7,8,10,12)
- Thirty=(4,6,9,11)
- February(if LeapYear: then 29 else 28)
- LeapYear=((Year%4==0 && Year%100!=0) || Year%400==0)
- if m in ThirtyFirst: then (0,31)
- else if m in Thirty: then (0,30)
- else if m == "02" : leapYear=((Year%4==0 && Year%100!=0) || Year%400==0); if leapYear==True: then (0,29) else (0,28)

- type==int : has only numbers isdigit()==True
- Month and Day are handled by exact digits decimal addition. 
    
    draft:
        if (isdigit(n[0]))
            one = n[0];
        else
            return false;
        if (isdigit(n[1]))
            two = one*10 + n[1];
        else
            return false;
        if (isMonth(two))
            return true;
        return false;

 However, year = atoi(n); check if year is in the range specified. 

    draft:
        if (0 < year && year <2028)
            return true;
        return false;

### Valueの要件
1. float としてロードする
2. 符号と範囲を検証
- if n < 0.0f
- if 0.f<=n && n<=100.f


## DB操作の実装方針
1.　データ構造
struct DateRate {
    Date date;
    float rate;
};

2. データ整形

・パース
```
readCSV()
splitCSV()
ParseDate()
ParseRate()
でパース。
```

・ソート
year, month, day の3段階で比較して昇順ソート

bool operator<(d1, d2) {
    if (d1.year < d2.year)
        return (true);
    if (d1.month < d2.month)
        return (true);
    return (d1.day < d2.day);
}

struct DateValueLess {
    bool operator()(const DateValue& lhs, const dateValue& rhs) const {
        return lhs.date < rhs.date;
    }
}

std::sort(data.begin(), data.end(), DateValueLess());


## DB照合の実装方針

1. std::lower_bound() で「引数以下の要素で最大のもの」を返す
2. なかったらエラー
