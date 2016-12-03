#include <iostream>
#include <stdio.h>

#include "gui.h"




void a()
{
    system("clear");
    std::cout << "A";
    getchar();

}
void b()
{
    system("clear");
    std::cout << "B";
    getchar();

}

void ex()
{
    exit(1);
}

void nextMenu()
{
    std::string n1[3] = {"Call A", "Call B", "Exit"};
    void (*select1[3])() = {a, b, ex};
    GUI g3(3,n1,select1, "Second menu");
    g3.func();
}




int main()
{

    std::string n[4] = {"Call A", "Call B", "Next menu","Exit"};
    void (*select[4])() = {a, b, nextMenu, ex};
    GUI g2(4,n,select, "First Menu", green);
    g2.func();



    return 0;
}
