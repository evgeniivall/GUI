#include "gui.h"
#include <iostream>
#define TAB "\t"

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
    optionsAmount_ = size;
    optionsArray_ = new options[optionsAmount_];
    for(int i = 0; i < optionsAmount_; i++)
    {
        optionsArray_[i].p = func[i];
        optionsArray_[i].name = names[i];
    }
    position_ = 0;
    optionColor_ = new int[optionsAmount_];
    Header_ = head;
    emphasizingColor_ = color;
    enter_ = false;
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

//void GUI::Show()
void (*GUI::Show())()
{
    Display();
    //optionsArray_[position_].p();
    return (optionsArray_[position_].p);

}

void GUI::Display()
{
    cls();
    if(enter_)
        return;
    //std::cout << TAB << Header_ << std::endl << std::endl;
    std::cout << TAB << ColoredOut(Header_,1,0,0) << std::endl << std::endl;
    for (int i = 0; i < optionsAmount_; i++)
    {
        optionColor_[i] = 0;
    }
    optionColor_[position_] = emphasizingColor_;
    for (int i = 0; i < optionsAmount_; i++)
    {
        std::cout << TAB << ColoredOut(optionsArray_[i].name, 0, optionColor_[i], 0);
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
        enter_ = true;
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
                    if (position_ + 1 < optionsAmount_)
                        ++position_;
                    else
                        position_ = 0;
                    break;
                }
                case 'A':
                {
                    if (position_ - 1 >= 0)
                        --position_;
                    else
                        position_ = optionsAmount_ - 1;
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
                if (position_ + 1 < optionsAmount_)
                    ++position_;
                else
                    position_ = 0;
                break;
            }
            case 72:
            {
                if (position_ - 1 >= 0)
                    --position_;
                else
                    position_ = optionsAmount_ - 1;
                break;
            }
            case 13:
            {
                enter_ = true;
                break;
            }

        }

#endif
}

