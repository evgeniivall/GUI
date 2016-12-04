#ifndef GUI_H
#define GUI_H

#include <iostream>

enum color
{
    black = 30,
    red = 31,
    green = 32,
    yellow = 33,
    blue = 34,
    purple = 35,
    light_blue = 36
};

class GUI
{

public:

    GUI();
    GUI(int size, std::string* names, void (*func[])(), std::string head, color color = red);
    void Show();
    std::string ColoredOut(std::string text, int type, int color, int bg);
    ~GUI()
    {
        delete [] optionsArray;
        delete [] optionColor;
    }

private:

    struct options
    {
        void (*p)();
        std::string name;
    };

    int optionsAmount;
    options* optionsArray;
    std::string Header;
    int emphasizingColor;

    bool Enter;
    int *optionColor;
    int position;

    void Display();
    void Navigator();
};


#endif // GUI_H
