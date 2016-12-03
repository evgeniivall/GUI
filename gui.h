#ifndef GUI_H
#define GUI_H
#include <iostream>
class GUI
{
public:


   GUI();
   GUI(int size, std::string* names, void (*func[])(), std::string head);
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
