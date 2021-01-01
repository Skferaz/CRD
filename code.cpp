#include<bits/stdc++.h>
#include "hi.h"
#include <ctime>
#include<thread>
using namespace std;
int main()
{
   
   thread t1(create,"rahul",50,(time_t)0);
   t1.join();
   thread t2(read,"rahul");
   t2.join();
   thread t3(Delete,"rahul");
   t3.join();
   
   
   
}
