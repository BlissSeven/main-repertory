#ifndef THE_SUM_OF_TWO_H
#define THE_SUM_OF_TWO_H

#include <vector>
#include <iostream>
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* result=new ListNode(0);
        ListNode* temp=result;

        vector<int> v1;
        vector<int> v2;
        vector<int> v3;
        while(l1!=NULL)
        {
            v1.push_back(l1->val);
            l1=l1->next;

        }

        for(auto it=v1.begin();it!=v1.end();it++)
            cout<<*it<<endl;

        while(l2!=NULL)
        {
            v2.push_back(l2->val);
            l2=l2->next;
        }
        for(auto it=v2.begin();it!=v2.end();it++)
            cout<<*it<<endl;

        int sum=0;
        bool prev_of=false;
        if(v1.size()>v2.size())
        {
            auto it=v1.begin();
            auto it2=v2.begin();
            for(;it!=v1.end();it++)
            {
                if(it2!=v2.end())
                {
                    sum=*it+*it2;

                     if(prev_of)
                        sum+=1;
                    if(sum>=10)
                        prev_of=true;
                    else
                        prev_of=false;

                    v3.push_back(sum%10);

                    it2++;
                }
                else
                {
                    if(prev_of)
                        sum=*it+1;
                    else
                        sum=*it;
                    if(sum>=10)
                        prev_of=true;
                    else
                        prev_of=false;
                    v3.push_back(sum%10);
                }

            }
            if(prev_of)
                 v3.push_back(1);

        }
        else
        {
            auto it=v1.begin();
            auto it2=v2.begin();
            for(;it2!=v2.end();it2++)
            {
                if(it!=v1.end())
                {
                    sum=*it+*it2;
                    if(prev_of)
                        sum+=1;
                    if(sum>=10)
                        prev_of=true;
                    else
                        prev_of=false;

                    v3.push_back(sum%10);
                     ++it;
                 }
                else
                {
                    if(prev_of)
                        sum=*it2+1;
                    else
                        sum=*it2;
                    if(sum>=10)
                        prev_of=true;
                    else
                        prev_of=false;
                    v3.push_back(sum%10);
                }

            }
            if(prev_of)
                 v3.push_back(1);
        }

        auto it=v3.begin();

        temp->val=*it;
        it++;
          for(;it!=v3.end();it++)
          {

            temp->next=new ListNode(0);
            temp=temp->next;
            temp->val=*it;
          }

        return result;
    }
};
#endif // THE_SUM_OF_TWO_H
