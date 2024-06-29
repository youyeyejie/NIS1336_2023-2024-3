#include <iostream>
#include <time.h>       /* time_t, struct tm, difftime, time, mktime */

int main ()
{
  time_t now;
  time(&now);//获取现在的时间

  tm to_tm = *localtime(&now);//将刚刚获取的时间，转换为tm格式
  time_t to_time_t = mktime(&to_tm);//tm 转time_t;
  std::cout<<"to_time_t: "<<to_time_t<<std::endl;//time_t转tm
  std::cout <<"to_tm: "<<to_tm.tm_year<<std::endl;//从1990年经历了多少年

  std::string thisTime = ctime(&to_time_t);//time_t转string,需要传地址
  std::cout<<thisTime<<std::endl;
  thisTime = asctime(&to_tm);//tm转string
  std::cout<<thisTime<<std::endl;

  return 0;
}
