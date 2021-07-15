#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#define OPERATORS 7
#include<string.h>
using namespace std;

struct node
{
    int data;
    struct node *next;
};

struct node *top = NULL;
// create a node with given data
struct node* createNode(int data)
{
    struct node *ptr = new node;
    ptr->data = data;
    ptr->next = NULL;
}
// Operators and its precedence
char precedence[OPERATORS][2] =
{
    {'(', 0},
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2},
    {')', 3}
};

// Pop the top element from the stack
int pop()
{
    struct node *ptr;
    int data;
    if (top == NULL)
        return -1;
    ptr = top;
    top = top->next;
    data = ptr->data;
    free (ptr);
    return (data);
}

// Push the given data into the stack
void push(int data)
{
    struct node *ptr = createNode(data);
    if (top == NULL)
    {
        top = ptr;
        return;
    }
    ptr->next = top;
    top = ptr;
}

// get the index of the given operator
int getIndex(int data)
{
    int i;
    for (i = 0; i < OPERATORS; i++)
    {
        if (data == precedence[i][0])
            return i;
    }
}

// infix to prefix conversion
void in_to_pre(char infix[], char prefix[])
{
    int i, j = 0, data;
    int index1, index2;
    for (i = 0; i < strlen(infix); i++)
    {
        // if the given expression is operand, place in output buffer
        if (infix[i] >= 'a' && infix[i] <= 'z' || infix[i] >= 'A' && infix[i] <= 'Z')
        {
            prefix[j++] = infix[i];
        }
        else if (infix[i] == '(')
        {
            // if the expression is open brace, pop the elements one
            //by one until we encounter close brace

            data = pop();
            while (data != ')')
            {
                prefix[j++] = data;
                data = pop();
            }
        }
        else if (infix[i] == ')')
        {
            // if the expression is close brace, push it into stack
            push(infix[i]);
        }
        else
        {
            data = pop();
            if (data == -1)
            {
                // stack is empty..so, push current expression
                push(infix[i]);
                continue;
            }
            else if (data == ')')
            {
                /*
                if stack top element is close brace, then
                push current input to stack
                */
                push(data);
                push(infix[i]);
                continue;
            }
            index1 = getIndex(data);
            index2 = getIndex(infix[i]);

            // Precedence manipulation stack operator and current expression

            while (precedence[index1][1] > precedence[index2][1])
            {
                prefix[j++] = data;
                data = pop();
                if (data == -1 || data == ')')
                {
                    push(infix[i]);
                    break;
                }
                index1 = getIndex(data);
            }
            if (data != -1)
            {
                push(data);
                push(infix[i]);
            }

        }
    }

    // Pop the remaining data from stack after all processing
    while (1)
    {
        if ((data = pop()) == -1)
            break;
        prefix[j++] = data;
    }
    prefix[j] = '\0';
}

//Infix to postfix conversion
void in_to_post(char infix[], char postfix[])
{
    int i, j = 0, data;
    int index1, index2;
    for (i = 0; i < strlen(infix); i++)
    {
        // given input is operator or not
        if (infix[i] >= 'a' && infix[i] <= 'z' || infix[i] >= 'A' && infix[i] <= 'Z' )
        {
            postfix[j] = infix[i];
            j++;
        }
        else if (infix[i] == ')')
        {
            /*
              Input is close brace.  So, pop all
              elements until we encounter open brace
             */
            data = pop();
            while (data != '(' && data != -1)
            {
                postfix[j++] = data;
                data = pop();
            }
        }
        else if (infix[i] == '(')
        {
            // open brace - push it into stack
            push(infix[i]);
        }
        else
        {
            /*
              take top element from the stack to
              check for operator precedence, to know
              whether the top element is open brace etc.
             */
            data = pop();
            if (data == -1)
            {
                push(infix[i]);
                continue;
            }
            else if (data == '(')
            {
                /*
                  if top element in stack is open brace,
                  then push both top(data) and current input
                  into the stack.
                 */
                push(data);
                push(infix[i]);
                continue;
            }

            index1 = getIndex(data);
            index2 = getIndex(infix[i]);
            while (precedence[index1][1] >= precedence[index2][1])
            {
                /*
                  if the operator in stack has higher precedence
                  than the input operator, then pop the stack
                  operator and place it in output buffer.
                 */
                postfix[j++] = data;
                data = pop();
                if (data == -1)
                {
                    push(infix[i]);
                    break;
                }
                else if (data == '(')
                {
                    push(data);
                    push(infix[i]);
                    data = -1;
                    break;
                }
                index1 = getIndex(data);
            }
            if (data != -1)
            {
                push(data);
                push(infix[i]);
            }

        }
    }


    // After processing all inputs, pop all other elements from stack
    while (1)
    {
        if ((data = pop()) == -1)
            break;
        postfix[j++] = data;
    }
    postfix[j] = '\0';
}


bool isOperand(char x)
{
    return (x >= 'a' && x <= 'z') ||
           (x >= 'A' && x <= 'Z');
}

// Get Infix for a given postfix
// expression
string getInfix(char exp[])
{
    system("color 1F");
    stack<string> s;

    for (int i=0; exp[i]!='\0'; i++)
    {
        // Push operands
        if (isOperand(exp[i]))
        {
            string op(1, exp[i]);
            s.push(op);
        }

        // We assume that input is
        // a valid postfix and expect
        // an operator.
        else
        {
            string op1 = s.top();
            s.pop();
            string op2 = s.top();
            s.pop();
            s.push("(" + op2 + exp[i] +
                   op1 + ")");
        }
    }

    // There must be a single element
    // in stack now which is the required
    // infix.
    return s.top();
}




void cover()
{
    system("color 0E");
    string s =
        "   \n\t\t\t CSE 207 Presentation\n\n"
        "   .............................................................. \t\t\t"
        "   \n\t\tWELCOME TO EXPRESSION TREE PROJECT\t\t\n"
        "   ..............................................................\t\t"
        "   \n\n\t   Course Instructor: DR. Md. Waselul Haque Sadid\n"
        "   \n\t\tGroup Member: "
        "   \n\t\t\t     1. Syed Salman Hayat"
        "   \n\t\t\t     2. Rayhan-E-Zannat";

    cout<<s;

    char c;
    cout << endl << endl << endl<< endl << "   Press any key to continue. . . . . " ;
    cin>>c;
    system("cls");

}
void menu()
{
    system("color 0A");
    int choice;
    cout << endl << endl << endl;

    cout <<"\t\t\t\t        1. SHOW PREFIX AND POSTFIX EXPRESSION.        " << endl;
    cout <<"\t\t\t\t        2. EVALUATE.                          " << endl;
    cout <<"\t\t\t\t        3. EXIT.                                      " << endl<<endl;
}

int main()
{
    cover();
    z:
    menu();

    int choice;
    char input[100],str1[100], output1[100],output2[100],evaluate[100];
    cout << "\t\t" << "Enter your choice : " ;
    cin >> choice ;
    system("cls");
    if(choice == 1)
    {
        cout <<endl<<endl<<"\t\t\t\tEnter Your INFIX Expression: ";
        cin >> input;

        system("color 2F");

        strcpy(str1,input); //input value copy into str1
        in_to_pre(strrev(input), output1);
        //get prefix notation reverse the output
        cout <<endl<<"\t\t\t\t\tPREFIX Expression :  " << strrev(output1) << endl;

        in_to_post(str1, output2);
        cout <<endl<<"\t\t\t\t\tPOSTFIX Expression :  " << output2  << endl;

        strcpy(evaluate,output2);
        cout << endl << endl << endl;
        cout << "\t\t\t2. EVALUATE \t\t\t\t 3. EXIT" << endl << endl;
        cout << "\t\t\tEnter Your Choice: ";
        cin >> choice;
        system("cls");
        if(choice == 2 )
        {
            cout << endl << "\n\n\t\t\t\tAFTER EVALUATING :";
            cout << "\n\t\t\t\t.............................................";
            cout << "\n\t\t\t\t\tINFIX EXPRESSION :  " <<  getInfix(evaluate) << endl;
            cout << "\t\t\t\t.............................................";
        }
        cout << "\n\n\n\t\t\t1. Return To MENU \t\t\t\t 2. EXIT" << endl << endl;
        cout << "\t\t\tENTER YOUR CHOICE: ";
        cin >> choice;
        if(choice == 1)
        {
            system("color 0A");
            system("CLS");
            goto z;
        }
        else
            return 0;
    }
    else if(choice == 2)
    {
        char post[100];
        cout <<"\n\n\t\t\t\tEnter your Postfix Expression: ";
        cin >> post;
        cout << endl << "\n\n\t\t\t\tAFTER EVALUATING :";
        cout << "\n\t\t\t\t.............................................";
        cout << "\n\t\t\t\t\tINFIX EXPRESSION :  " <<  getInfix(post) << endl;
        cout << "\t\t\t\t.............................................";

        cout << "\n\n\n\t\t\t1. Return To MENU \t\t\t\t 2. EXIT" << endl << endl;
        cout << "\t\t\tENTER YOUR CHOICE: ";
        cin >> choice;
        if(choice == 1)
        {
            system("CLS");
            main();
        }
        else
        {
            return 0;
        }

    }
    else if(choice==3)
    {
        return 0;
    }
    else
    {
         system("color 4F");
         cout<<"\n\n\n\nWrong Input Try Again !!!";
         system("CLS");
         goto z;
    }

}
