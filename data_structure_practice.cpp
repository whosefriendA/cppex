#include<iostream>
#include<list>
//1.
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
    ListNode *detectCycle(ListNode *head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                ListNode* index1 = fast;
                ListNode* index2 = head;
                while (index1 != index2) {
                    index1 = index1->next;
                    index2 = index2->next;
                }
                return index2; 
            }
        }
        return NULL;
    }
};
//2.
class MyStack {
public:
queue<int> queue1;
    MyStack() {
      
    }
    
    void push(int x) {
        queue1.push(x);
    }
    
    int pop() {
        int size=queue1.size();
        size--;
        while(size--){
        queue1.push(queue1.front());
        queue1.pop();
        }
        int temp=queue1.front();
        queue1.pop();
        return temp;
    }
    
    int top() {
       return queue1.back();
    }
    
    bool empty() {
       return queue1.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
 //3.
 class MyQueue {
public:
    std::stack<int> stackin;
    std::stack<int> stackout;
    MyQueue() {
    }
    
    void push(int x) {
        stackin.push(x);
    }
    
    int pop() {
        if(stackout.empty()){
        while(!stackin.empty()){
            stackout.push(stackin.top());
            stackin.pop();
        }
        }
            int temp=stackout.top();
            stackout.pop();
            return temp;
    }
    
    int peek() {
       int res = this->pop();
        stackout.push(res);
        return res;
    }
    
    bool empty() {
        if(stackout.empty()&&stackin.empty())
        return true;
        else return false;

    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */