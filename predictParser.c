#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define TOK_SIZE 20

void E();
void T();
void F();
void get_tokens();
void nexttoken();

char lookahead[TOK_SIZE];
char input[100];
char* tokens[100];
int tokenIdx;

int main()
{
    printf("input: ");
    gets(input);  // 입력

    get_tokens();
    
    nexttoken();
    E();
    
    return 0;
}

void error() // 에러 출력
{
    puts("\nerror!"); // 에러를 출력한다.
    exit(1); // 프로그램 종료
}

void get_tokens()
{
    int len = strlen(input);
    int idx = 0;

    for (int i=0; i<100; i++)
        tokens[i] = (char*)malloc(TOK_SIZE * sizeof(char));

    for (int i=0; i<len; )
    {
        char tok[20];
        idx = 0;

        if (input[i] == ' ') 
        {
            i++;
            continue;  
        }

        if (input[i] >= '0' && input[i] <= '9') // 토큰이 숫자
        {
            while (input[i] >= '0' && input[i] <= '9')
                tok[idx++] = input[i++];
            tok[idx] = 0;
        }
        else if ((input[i] >= 'a' && input[i] <= 'z') ||
                    (input[i] >= 'A' && input[i] <= 'Z')) // 토큰이 id
        {
            while ((input[i] >= 'a' && input[i] <= 'z') ||
                    (input[i] >= 'A' && input[i] <= 'Z') ||
                    (input[i] >= '0' && input[i] <= '9'))
                tok[idx++] = input[i++];
            tok[idx] = 0;
        }
        else if (input[i] == '+' || input[i] == '-' || // 토큰이 수학 기호
                    input[i] == '*' || input[i] == '/' ||
                    input[i] == '(' || input[i] == ')')
        {
            tok[idx++] = input[i++]; 
            tok[idx] = 0;
        }
        else if (input[i] == '$') // 토큰이 $
        {
            tok[idx++] = input[i++]; 
            tok[idx] = 0;
            break;
        }
        else // 토큰이 아닐 경우
            error();
        
        strcpy(tokens[tokenIdx++], tok);
    }
    tokenIdx = 0;
}

void nexttoken()
{
    strcpy(lookahead, tokens[tokenIdx++]);
}

void match(char* t)
{
    if (!strcmp(lookahead, t))
        nexttoken();
    else
        error();
}

void E()
{
    T();
    while (1)
    {
        if (!strcmp(lookahead, "+")) 
        {
            match("+");
            T();
            putchar('+');
            putchar(' ');
        }
        else if (!strcmp(lookahead, "-"))
        {
            match("-");
            T();
            putchar('-');
            putchar(' ');   
        }
        else break;
    }
}

void T()
{
    F();
    while (1)
    {
        if (!strcmp(lookahead, "*"))
        {
            match("*");
            F();
            putchar('*');
            putchar(' ');
        }
        else if (!strcmp(lookahead, "/"))
        {
            match("/");
            F();
            putchar('/');
            putchar(' ');
        }
        else break;
    }
}

int isnumber(char * lookahead)
{
    int len = strlen(lookahead);
    for (int i=0; i<len; i++)
    {
        if (!isdigit(lookahead[i]))
            return 0;
    }
    return 1;
}

int isid(char * lookahead)
{
    int len = strlen(lookahead);
    if (!isalpha(lookahead[0]))
        return 0;
    for (int i=1; i<len; i++)
    {
        if (!(isalpha(lookahead[i]) || isdigit(lookahead[i])))
            return 0;
    }
    return 1;
}

void F()
{
    if (isnumber(lookahead))
    {
        fputs(lookahead, stdout);
        match(lookahead);
        putchar(' ');
    }
    else if (isid(lookahead))
    {
        fputs(lookahead, stdout);
        match(lookahead);
        putchar(' ');
    }
    else if (!strcmp(lookahead, "("))
    {
        match("(");
        E();
        match(")");
    }
    else
        error();
}
