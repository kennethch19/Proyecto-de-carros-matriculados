#include<iostream>
#include<windows.h>
#include <conio.h>
#include <stdio.h>
#include <codecvt>
using namespace std;

void gotoxy(int x, int y) {
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


int main(){
    SetConsoleOutputCP(CP_UTF8);
    std::wcout.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

    system("cls");
    setColor(4);
    gotoxy(40, 0); cout << "UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE";
    setColor(2);
    gotoxy(0, 2); cout << "REGISTRO DE CARROS MATRICULADOS";
    setColor(3);
    gotoxy(0, 4); cout << "Integrantes:DYLAN FERNANDO LAYEDRA JACOME.KENNETH MIJAEL CHICAIZA MIÑO";
    gotoxy(0, 6); cout << "NRC:4598"<<endl;
    setColor(5);
    system("pause");

    return 0;
}