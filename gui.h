#ifndef GUI_H
#define GUI_H

#include <iostream>
enum color
{
    red = 31,
    green = 33,
};

class GUI
{
public:


   GUI();
   GUI(int size, std::string* names, void (*func[])(), std::string head, color Col = red);
   void func();


   ~GUI()
   {
        delete [] array;
        delete [] positionColor;
   }

private:
    struct options
    {
        void (*p)();
        std::string name;
    };
    int defCol;
    bool ifEnter = 0;
    options* array;
    int count;
    int *positionColor;
    std::string Header;
    void Show();
    int position;
    std::string output(std::string text, int type, int color, int bg);
    void navigator();
};


#endif // GUI_H
