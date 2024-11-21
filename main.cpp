#include <iostream>
#include "funciones.h"


using namespace std;

int main()
{
    int num;
    srand(time(NULL)); //semilla
    num = (rand() % 6) + 1;

    setlocale(LC_ALL, "spanish");
    system("color 57"); //background
    mostrar_menu();
    return 0;
}

