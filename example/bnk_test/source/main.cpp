/**
   @file example.cpp
   @author Goro Yabu
   @date 2018/11/22
   @date 2019/03/28 Modified for bnk v2.0
   @brief Example Application of BNK. 
**/
#include <iostream>
#include <time.h>
#include <vector>
#include <bnk.hpp>

using namespace std;
using namespace bnk;

/**
   @brief Read present time and put into BNK
**/
int mod1_read()
{
   time_t timer;
   time(&timer);
   cout << "timer " << timer << endl;
   struct tm *t_st;
   t_st = localtime(&timer);
   
   int year = t_st->tm_year+1900;
   int mon = t_st->tm_mon+1;
   int day = t_st->tm_mday;
   int hour = t_st->tm_hour;
   int min = t_st->tm_min;
   int sec = t_st->tm_sec;

   bnk_def<int>("year", 1);
   bnk_def<int>("mon", 1);
   bnk_def<int>("day", 1);
   bnk_def<int>("hour", 1);
   bnk_def<int>("min", 1);
   bnk_def<int>("sec", 1);

   bnk_put("year", year);
   bnk_put("mon", mon);
   bnk_put("day", day);
   bnk_put("hour", hour);
   bnk_put("min", min);
   bnk_put("sec", sec);

   cout << "end mod1" << endl;
   cout << endl;
   
   return 0;
}

/**
   @brief Get data from BNK and calculate Julian Day.
**/
int mod2_jd()
{
    int year, mon, day;

    year = bnk_get<int>("year");
    mon = bnk_get<int>("mon");
    day = bnk_get<int>("day");
    
    double a = (int) (year/100);
    double b = 2 - a + (int) (a/4);
    int JD = (int)(365.25 * year) + (int)(30.6001 * (mon + 1)) + day + b + 1720994.5;

    bnk_def<int>("julianday", 1);
    bnk_put("julianday", JD);
    
    cout << "end mod2" << endl;
    cout << endl;
    
    return 0;
}

/**
   @brief Find divisors of N = min*sec.
**/
int mod3_div()
{
    const int max = 60;
    
    //int min;
    int sec;
    //min = bnk_get<int>("min");
    sec = bnk_get<int>("sec");
    int N = sec;

    int num = 0;
    bnk_def<int>("num_div", 1);
    bnk_def<int>("divisor_of_sec", max);

    vector<int> divisor;
    int i = 1;
    while(i<N+1){
	if(N%i==0){
	    divisor.push_back(i);
	    num = divisor.size();
	}
	if(num>=max) break;
	++i;
    }
    bnk_put("num_div", num);
    bnk_put<int>("divisor_of_sec", divisor, 0, num);
    //bnk_put("divisor", divisor.begin(), divisor.begin()+num);

    cout << "end mod3" << endl;
    cout << endl;
    
    return 0;
}

int main()
{
   mod1_read();

   mod2_jd();

   mod3_div();
   
   bnk_list();
   cout << endl;
   
   bnk_export_all();

   return 0;
}
