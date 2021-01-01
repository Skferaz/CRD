#ifndef MYFILE_H_
#define MYFILE_H_

#include<bits/stdc++.h>
#include <ctime>
#include <mutex>    
using namespace std;
map<string,pair<int,time_t>> m;
mutex mtx;

void create(string key,int value,time_t timeout=0)
{
     mtx.lock();
     time_t current_time;
     pair<int,time_t> l;
     if(m.find(key)!=m.end())
           cout<<"error: this key already exists"<<"\n";
     else
      {   int d=0;
          for(auto c:key)
           {
             if(isalpha(c))
               d++;
           }
           if(d==key.length())
           {
             if(m.size()<(1024*1024*1024) and value<=(16*1024*1024))
              {
                if(timeout==0)
                  l ={value,timeout};
                else
                    {
                      current_time=time(NULL)+timeout;
                   l={value,current_time};
                   }
                  if(key.length()<=32)
                    {
                       m[key]=l;
                     }
              }
             else
               cout<<"error: Memory limit exceeded!!"<<"\n";
            }
           else
            cout<<"error: Invalind key_name!! key_name must contain only alphabets and no special characters or numbers"<<"\n";
      }
    mtx.unlock();
}

void read(string key){
      mtx.lock();
     if(m.find(key)==m.end())
      cout<<"error: given key does not exist in database. Please enter a valid key"<<"\n";
      else
      {
        pair<int,time_t> b;
        b=m[key];
        if(b.second!=0)
         {
            if(time(NULL)<b.second)
             {
               string stri=key+":"+to_string(b.first);
               cout<<stri;
              }
             else
                cout<<"error: time-to-live of"<<key<<"has expired"<<"\n";
          }
          else{
            string stri=key+":"+to_string(b.first);
               cout<<stri<<"\n";
           }
                        
       }

     mtx.unlock();
}


void Delete(string key)
{
    mtx.lock();
    if(m.find(key)==m.end())
      cout<<"error: given key does not exist in database. Please enter a valid key";
      else
      {
        pair<int,time_t> b;
        b=m[key];
        if(b.second!=0)
         {
            if(time(NULL)<b.second)
             {
                m.erase(key);
                cout<<"key is successfully deleted";
              }
             else
                cout<<"error: time-to-live of"<<key<<"has expired";
          }
          else{
            m.erase(key);
                cout<<"key is successfully deleted";
           }
                        
       }
     mtx.unlock();
}


void modify(string key,int value)
{
    mtx.lock();
   pair<int,time_t> b;
   b=m[key];
   if(b.second!=0)
   {
      if(time(NULL)<b.second)
       {
              if(m.find(key)==m.end())
                  cout<<"error: given key does not exist in database. Please enter a valid key";
               else
                 {
                     pair<int,time_t> l;
                     l={value,b.second};
                     m[key]=l;
                  }
         }
         else
           cout<<"error: time-to-live of"<<key<<"has expired";     
    }
    else
     {
       if(m.find(key)==m.end())
          cout<<"error: given key does not exist in database. Please enter a valid key";
       else
        {
           pair<int,time_t> l;
                     l={value,b.second};
                     m[key]=l;
        }
     }
      mtx.unlock();     
}

#endif
