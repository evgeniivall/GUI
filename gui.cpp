#include "gui.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>


GUI::GUI(int size, std::string* names, void (*func[])(), std::string head, color Col)
{
    count = size;
    array = new options[count];
    for(int i = 0; i < count; i++)
    {
        array[i].p = func[i];
        array[i].name = names[i];
    }
    position = 0;
    positionColor = new int[count];
    Header = head;
    defCol = Col;
}

std::string GUI::output(std::string text, int type, int color, int bg)
{
    bool par = 0;
    std::string str = "\x1b[";
    if(color != 0)
    {
        str += std::to_string(color);
        par = 1;
    }
    if(type != 0)
    {
        if(par != 0)
            str += ";";
        str += std::to_string(type);
        par = 1;
    }
    if(bg != 0)
    {
        if(par != 0)
            str += ";";
        str += std::to_string(bg);
    }
    str = str + "m" + text + "\x1b[0m";

    return str;
}

void GUI::func()
{
    Show();
    array[position].p();

}

void GUI::Show()
{
    system("clear");
    if(ifEnter)
    {
        return;
    }
    std::cout << Header << std::endl;
    for (int i = 0; i < count; i++)
    {
        positionColor[i] = 0;
    }
    positionColor[position] = defCol;
    for (int i = 0; i < count; i++)
    {
        std::cout << output(array[i].name, 0, positionColor[i], 0);
        std:: cout << std::endl;
    }
    navigator();
    Show();

}

void GUI::navigator()
{

    struct termios oldt,
        newt;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    int choice = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );

    if((char)choice == '\n')
    {
        //array[position].p();
        ifEnter = 1;
    }
    if (choice == 27)
    {
        choice = getchar();
        if (choice == '[')
        {
            choice = getchar();
            switch (choice)
            {
                case 'B':
                {
                    if (position + 1 < count)
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
                        position = count - 1;
                    break;
                }



            }
        }
    }

}

