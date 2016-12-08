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
    void (*Show())();
    GUI();
    GUI(int size, std::string* names, void (*func[])(), std::string head, color color = red);
    //void Show();
    std::string ColoredOut(std::string text, int type, int color, int bg);
    ~GUI()
    {
        delete [] optionsArray_;
        delete [] optionColor_;
    }

private:

    struct options
    {
        void (*p)();
        std::string name;
    };

    int optionsAmount_;
    options* optionsArray_;
    std::string Header_;
    int emphasizingColor_;

    bool enter_;
    int *optionColor_;
    int position_;

    void Display();
    void Navigator();
};


#endif // GUI_H
