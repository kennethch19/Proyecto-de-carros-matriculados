#include<iostream>
#include<windows.h>
#include <conio.h>
#include <stdio.h>
#include <codecvt>
#include <fstream>
#include <vector>
#include <string>

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
struct Vehiculo {
    string placa;
    string propietario;
    string modelo;
    string color;
};

vector<Vehiculo> vehiculos;

void cargarRegistros() {
    ifstream archivo(FILE_PATH);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo. Se creará uno nuevo al guardar los registros.\n";
        return;
    }
    Vehiculo v;
    while (archivo >> v.placa >> v.propietario >> v.modelo >> v.color) {
        vehiculos.push_back(v);
    }
    archivo.close();
}

void guardarRegistros() {
    ofstream archivo(FILE_PATH);
    if (!archivo) {
        cerr << "Error al abrir el archivo para escritura.\n";
        return;
    }
    for (const auto& v : vehiculos) {
        archivo << v.placa << " " << v.propietario << " " << v.modelo << " " << v.color << "\n";
    }
    archivo.close();
}

void registrarVehiculo() {
    Vehiculo v;
    cout << "Ingrese la placa del vehiculo: ";
    cin >> v.placa;
    cout << "Ingrese el propietario: ";
    cin >> v.propietario;
    cout << "Ingrese el modelo: ";
    cin >> v.modelo;
    cout << "Ingrese el color: ";
    cin >> v.color;
    vehiculos.push_back(v);
    guardarRegistros();
    cout << "Registro guardado correctamente.\n";
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
    setColor(7);


    return 0;
}