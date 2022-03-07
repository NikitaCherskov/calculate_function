#include <iostream>
#include <locale>

float postcalc(char* example, int size)
{
    int i, j;
    int level = 0; //компилятор ругается без = 0
    for (i = 0, level = 0; i < size; i++)
    {
        if (example[i] == '(') //оптимизировать
        {
            level++;
        }
        else if (example[i] == ')')
        {
            level--;
        }
        if (example[i] == '+' && level == 0)
        {
            return postcalc(example, i) + postcalc(&(example[i + 1]), size - (i + 1));
        }
        if (example[i] == '-' && level == 0)
        {
            return postcalc(example, i) - postcalc(&(example[i + 1]), size - (i + 1));
        }
    }
    for (i = size - 1, level = 0; i > -1; i--)
    {
        if (example[i] == ')') //оптимизировать
        {
            level++;
        }
        else if (example[i] == '(')
        {
            level--;
        }
        if (example[i] == '*' && level == 0)
        {
            return postcalc(example, i) * postcalc(&(example[i + 1]), size - (i + 1));
        }
        if (example[i] == '/' && level == 0)
        {
            return postcalc(example, i) / postcalc(&(example[i + 1]), size - (i + 1));
        }
    }
    for (i = 0, level = -1; i < size; i++)
    {
        if (example[i] == '(') //оптимизировать
        {
            for (j = 0; j < size; j++)
            {
                if (example[j] == '(')
                {
                    level++;
                }
                else if (example[j] == ')' && level != 0)
                {
                    level--;
                }
                else if (example[j] == ')' && level == 0)
                {
                    return postcalc(&(example[i + 1]), j - (i + 1));
                }
            }
        }
    }
    char* float_str = new char[size + 1];
    for (i = 0; i < size; i++)
    {
        float_str[i] = example[i];
    }
    float_str[i] = '\0';
    return atof(float_str);
}
float calculate(const char* example)
{
    int i, j;
    int size;
    float answer;
    char* exam;
    for (i = 0, size = 0; example[i] != '\0'; i++)
    {
        if (example[i] != ' ')
        {
            size++;
        }
    }
    exam = new char[size];
    for (i = 0, j = 0; example[i] != '\0'; i++)
    {
        if (example[i] != ' ')
        {
            exam[j] = example[i];
            j++;
        }
    }
    answer = postcalc(exam, size);
    delete[] exam;
    return answer;
}

int main()
{
    setlocale(0, "");
    char* f = new char[100];
    std::cout << "введите форулу:\n";
    std::cin >> f;
    std::cout << "ответ: " << calculate(f);
}