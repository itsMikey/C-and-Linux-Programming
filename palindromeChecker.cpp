//This program will check if parentheses are balanced
//By Majdi Aburamadan
//11-20-12
//Lab 8

#include <queue>
#include <stack>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int i = 0;
    queue <char> myQ;
    stack <char> myS;
    string letters = "(((a+b)))+c)";
    int s = letters.size();
    
    while(i< s){
        if(letters[i] == '(')
           {
            myS.push(letters[i]);
           }
        else if(myS.empty())
           {
           cout << "Unbalanced" << endl;
            
           }
        else if(!(myS.empty()) && letters[i] == ')')
              { myS.pop();}
        i++;
    }
    
    if(myS.empty())
       {
        cout << "The Parentheses are balanced" << endl;
       }
    else
       {
        cout << "No these are not balanced" << endl;
       }
    return 0;
}

    //If one is empty, it will not be a palindrome
    //Put them all in. Deque one and pop one and compare.
    
   /*
    string pal = "kayak";
    int F = pal.size();
    i = 0;
    while(i<s)
       {
        myS.push(pal[i]);
        
       }
    */
    

