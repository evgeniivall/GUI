#include "gui.h"
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#define cls() system("cls")
#endif

#ifdef __unix__
#include <termios.h>
#include <unistd.h>
#define cls() system("clear")
#endif

GUI::GUI(int size, std::string* names, void (*func[])(), std::string head, color color)
{
    optionsAmount = size;
    optionsArray = new options[optionsAmount];
    for(int i = 0; i < optionsAmount; i++)
    {
        optionsArray[i].p = func[i];
        optionsArray[i].name = names[i];
    }
    position = 0;
    optionColor = new int[optionsAmount];
    Header = head;
    emphasizingColor = color;
    Enter = false;
}

std::string GUI::ColoredOut(std::string text, int type, int color, int bg)
{
    bool flag = false;
    std::string str = "\x1b[";
    if(color != 0)
    {
        str += std::to_string(color);
        flag = true;
    }
    if(type != 0)
    {
        if(flag)
            str += ";";
        str += std::to_string(type);
        flag = true;
    }
    if(bg != 0)
    {
        if(flag)
            str += ";";
        str += std::to_string(bg);
    }
    str = str + "m" + text + "\x1b[0m";

    return str;
}

void GUI::Show()
{
    Display();
    optionsArray[position].p();

}

void GUI::Display()
{
    cls();
    if(Enter)
        return;
    std::cout << Header << std::endl;
    for (int i = 0; i < optionsAmount; i++)
    {
        optionColor[i] = 0;
    }
    optionColor[position] = emphasizingColor;
    for (int i = 0; i < optionsAmount; i++)
    {
        std::cout << ColoredOut(optionsArray[i].name, 0, optionColor[i], 0);
        std::cout << std::endl;
    }
    Navigator();
    Display();

}

void GUI::Navigator()
{
#ifdef __unix__

    struct termios oldt,
        newt;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    int key = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );

    if((char)key == '\n')
        Enter = true;
    if (key == 27)
    {
        key = getchar();
        if (key == '[')
        {
            key = getchar();
            switch (key)
            {
                case 'B':
                {
                    if (position + 1 < optionsAmount)
                        ++position;
                    else
                        position = 0;
                    break;
                }
                case 'A':
                {
                    if (position - 1 >= 0)
                        --position;
                    else
                        position = optionsAmount - 1;
                    break;
                }

            }
        }
    }
#endif
#ifdef _WIN32

    int key = _getch();

        switch (key)
        {
            case 80:
            {
                if (position + 1 < optionsAmount)
                    ++position;
                else
                    position = 0;
                break;
            }
            case 72:
            {
                if (position - 1 >= 0)
                    --position;
                else
                    position = optionsAmount - 1;
                break;
            }
            case 13:
            {
                Enter = true;
                break;
            }

        }

#endif
}

