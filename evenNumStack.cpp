//  Created by Majdi Aburamadan on 11/17/12.
//This program will Multiply 2 numbers and add to stack. Multiply all and add to stack
//Count all even numbers and add their sum to the stack.
//No infile
//*********************************************************************************************************

// Specification file for the IntStack class
#ifndef INTSTACK_H
#define INTSTACK_H

class IntStack
{
private:
    int *stackArray;  // Pointer to the stack array
    int stackSize;    // The stack size
    int top;          // Indicates the top of the stack
    
public:
    // Constructor
    IntStack(int);
    
    // Copy constructor
    IntStack(const IntStack &);
    
    // Destructor
    ~IntStack();
    
    // Stack operations
    void push(int);
    void pop(int &);
    bool isFull() const;
    bool isEmpty() const;
};
#endif
// Implementation file for the IntStach class
#include <iostream>
#include "IntStack.h"
using namespace std;

//***********************************************
// Constructor                                  *
// This constructor creates an empty stack. The *
// size parameter is the size of the stack.     *
//***********************************************

IntStack::IntStack(int size)
{
    stackArray = new int[size];
    stackSize = size;
    top = -1;
}

//***********************************************
// Copy constructor                             *
//***********************************************

IntStack::IntStack(const IntStack &obj)
{
    // Create the stack array.
    if (obj.stackSize > 0)
        stackArray = new int[obj.stackSize];
    else
        stackArray = NULL;
    
    // Copy the stackSize attribute.
    stackSize = obj.stackSize;
    
    // Copy the stack contents.
    for (int count = 0; count < stackSize; count++)
        stackArray[count] = obj.stackArray[count];
    
    // Set the top of the stack.
    top = obj.top;
}

//***********************************************
// Destructor                                   *
//***********************************************

IntStack::~IntStack()
{
    delete [] stackArray;
}

//*************************************************
// Member function push pushes the argument onto  *
// the stack.                                     *
//*************************************************

void IntStack::push(int num)
{
    if (isFull())
       {
        cout << "The stack is full.\n";
       }
    else
       {
        top++;
        stackArray[top] = num;
       }
}

//****************************************************
// Member function pop pops the value at the top     *
// of the stack off, and copies it into the variable *
// passed as an argument.                            *
//****************************************************

void IntStack::pop(int &num)
{
    if (isEmpty())
       {
        cout << "The stack is empty.\n";
       }
    else
       {
        num = stackArray[top];
        top--;
       }
}

//***************************************************
// Member function isFull returns true if the stack *
// is full, or false otherwise.                     *
//***************************************************

bool IntStack::isFull() const
{
    bool status;
    
    if (top == stackSize - 1)
        status = true;
    else
        status = false;
    
    return status;
}

//****************************************************
// Member funciton isEmpty returns true if the stack *
// is empty, or false otherwise.                     *
//****************************************************

bool IntStack::isEmpty() const
{
    bool status;
    
    if (top == -1)
        status = true;
    else
        status = false;
    
    return status;
}

// Specification file for the MathStack class
#ifndef MATHSTACK_H
#define MATHSTACK_H
#include "IntStack.h"

class MathStack : public IntStack
{
public:
    // Constructor
    MathStack(int s) : IntStack(s) {}
    
    // MathStack operations
    void add();
    void sub();
    void mult();
    void multAll();
    void countEven();
};
#endif

// Implementation file for the MathStack class
#include "MathStack.h"

//***********************************************
// Member function add. add pops                *
// the first two values off the stack and       *
// adds them. The sum is pushed onto the stack. *
//***********************************************

void MathStack::add()
{
    int num, sum;
    
    // Pop the first two values off the stack.
    pop(sum);
    pop(num);
    
    // Add the two values, store in sum.
    sum += num;
    
    // Push sum back onto the stack.
    push(sum);
}

//***********************************************
// Member function sub. sub pops the            *
// first two values off the stack. The          *
// second value is subtracted from the          *
// first value. The difference is pushed        *
// onto the stack.                              *
//***********************************************

void MathStack::sub()
{
    int num, diff;
    
    // Pop the first two values off the stack.
    pop(diff);
    pop(num);
    
    // Subtract num from diff.
    diff -= num;
    
    // Push diff back onto the stack.
    push(diff);
}

void MathStack::mult()
{
    int num, num2;
    pop(num);
    pop(num2);
    
    num *= num2;
    push(num);

}

void MathStack::multAll()
{
    int array1[stackSize];
    int total;
    
    //total will hold all numbers multiplied
    for (int i = 0; i < stackSize; count++)
       {
        array1[i] = stackArray[i];
        total *= array1[i];
       }
    push(total);
}

//Sum of all the even numbers
void MathStack::countEven()
{

    int evenNum = 0;
    int i = 0;
    while(top != stackSize - 1)
       {
        if(stackArray[i] % 2 == 0)
           {
              evenNum+= stackArray[i];
           }
        i++
       }
    push(evenNum);
}
