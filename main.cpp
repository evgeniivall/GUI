#include <iostream>
#include <stdio.h>

#include "gui.h"

void nextMenu();


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


void firstMenu()
{
    std::string n[4] = {"Call A", "Call B", "Next menu","Exit"};
    void (*select[4])() = {a, b, nextMenu, ex};
    GUI g2(4,n,select, "First Menu", red);
    //g2.Show();
    g2.Show()();
}



void nextMenu()
{
    std::string n1[3] = {"Call A", "Call B", "Return to the previus menu"};
    void (*select1[3])() = {a, b, firstMenu};
    GUI g3(3,n1,select1, "Second menu", blue);
    g3.Show()();
    //g3.Show();
}


int main()
{

   firstMenu();



    return 0;
}
