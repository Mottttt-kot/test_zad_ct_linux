#include "twomodule.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <map>
#include <fstream>
#define DEBUG

using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//- ���� �������� (��� ������ ���������� ������� ��� ������ �������)
//- ���� ��������(��� ������ ���������� ������� ��� ������ �������)
//- ������ ��������(����� ��������� ����� ������� ��� 10 ���, ���������, ��� ������� ��� ��� ����������� � ����� ������ ������)
//- ������ ��������(����� ��������� ����� ������� ��� 10 ���, ���������, ��� ������� ��� ��� ����������� � ����� ������ ������)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//- ����������� �������������� �� ��� 1 (������� ����� �������� 100)
//-����������� �������������� �� ��� 2 (������� ����� �������� 200)
//- ����������� �������������� �� ��� 3 (������� ����� �������� 100)
//- ����������� �������������� �� ��� 4 (������� ����� �������� 300)
//- UST ������. = 132
//- UST ������. = 114
//- UST ����. = 18
//- RAB ����. = 2
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void write_in_file(map<string, bool>& result)
{
    ofstream out("result.txt");
    if (out.is_open())
    {
        out << "#######################################" << endl;
        for (auto& itr : result)
        {
            out << itr.first << " " << itr.second << std::endl;
        }
        out << "#######################################" << endl;
    }
    out.close();

}
void algor(map<string, bool>& result, map<string,long>& map_k, const long UST_overload,
    const long UST_underloading, const long UST, const long RABB_n) {
    long long sum_K = accumulate(begin(map_k), end(map_k), 0L,
        [](const long previous, const pair<const string, long>& p){ return previous + p.second; });

    map<string, long>::iterator best = max_element(begin(map_k), end(map_k), 
        [](const pair<const string, long>& a, const pair<const string, long>& b)->bool { return a.second < b.second; });
    long max_k = best->second;
    int RABB = 0;
#ifdef DEBUG
    cout << "#########################" << endl;
    cout << "MAX K: " << max_k << endl << "SUM K: " << sum_K << endl;
    //cout << "RAB: " << RABB << endl;
    for (auto& itr : map_k)
    {
        std::cout << itr.first << " " << itr.second << std::endl;
    }
    cout << "#########################" << endl;
#endif // DEBUG
    if (max_k > UST)
    {
        RABB = count_if(begin(map_k), end(map_k), [&max_k](const pair<string, long>& a)
            {
                return a.second > (max_k/2); 
            });
        if (max_k > UST_overload)
        {
            if (result["overload"])
            {
                result["two_overload"] = true;
            }
            result["overload"] = true;
            write_in_file(result);
            return;
        }
        else
        {
            if (RABB == 1)
            {
                write_in_file(result);
                return;
            }
            else if (RABB >= 2)
            {
                if (RABB == RABB_n)
                {
                    write_in_file(result);
                    return;
                }
                else
                {
                    if ((sum_K / (RABB - 1)) > UST_underloading)
                    {
                        write_in_file(result);
                        return;
                    }
                    else
                    {
                        if (result["underloading"])
                        {
                            result["two_underloading"] = true;
                        }
                        result["underloading"] = true;
                    }
                }
            }
        }

    }
    write_in_file(result);

}