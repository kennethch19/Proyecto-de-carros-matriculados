#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h> 
#include <windows.h> 
#include <iomanip>

using namespace std;

const string FILE_PATH = "vehiculos_datos.txt";

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
        ofstream nuevoArchivo(FILE_PATH); 
        nuevoArchivo.close();
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
        ofstream nuevoArchivo(FILE_PATH); 
        nuevoArchivo.close();
        return;
    }
    for (const auto& v : vehiculos) {
        archivo << v.placa << " " << v.propietario << " " << v.modelo << " " << v.color << "\n";
    }
    archivo.close();
}

void guardarDatos(const vector<Vehiculo> &vehiculos) {
    ofstream archivo("vehiculos_datos.txt", ios::out | ios::trunc);
    if (archivo.is_open()) {
        archivo << left << setw(15) << "Placa" << setw(20) << "Propietario" << setw(20) << "Modelo" << setw(15) << "Color" << endl;
        archivo << "--------------------------------------------------------------------------" << endl;
        for (const auto &v : vehiculos) {
            archivo << left << setw(15) << v.placa << setw(20) << v.propietario << setw(20) << v.modelo << setw(15) << v.color << endl;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo para guardar los datos." << endl;
    }
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
    guardarDatos(vehiculos); // Guardar datos en el archivo de texto
    cout << "Registro guardado correctamente.\n";
}

void actualizarVehiculo() {
    string placa;
    cout << "Ingrese la placa del vehiculo a actualizar: ";
    cin >> placa;
    for (auto& v : vehiculos) {
        if (v.placa == placa) {
            cout << "Ingrese el nuevo propietario: ";
            cin >> v.propietario;
            cout << "Ingrese el nuevo modelo: ";
            cin >> v.modelo;
            cout << "Ingrese el nuevo color: ";
            cin >> v.color;
            guardarRegistros();
            guardarDatos(vehiculos); // Guardar datos en el archivo de texto
            cout << "Registro actualizado correctamente.\n";
            return;
        }
    }
    cout << "No se encontró un vehiculo con esa placa.\n";
}

void verRegistros() {
    if (vehiculos.empty()) {
        cout << "No hay registros disponibles.\n";
        return;
    }
    cout << left << setw(15) << "Placa" << setw(20) << "Propietario" << setw(20) << "Modelo" << setw(15) << "Color" << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    for (const auto& v : vehiculos) {
        cout << left << setw(15) << v.placa << setw(20) << v.propietario << setw(20) << v.modelo << setw(15) << v.color << endl;
    }
}

void eliminarVehiculo() {
    string placa;
    cout << "Ingrese la placa del vehiculo a eliminar: ";
    cin >> placa;
    for (auto it = vehiculos.begin(); it != vehiculos.end(); ++it) {
        if (it->placa == placa) {
            vehiculos.erase(it);
            guardarRegistros();
            guardarDatos(vehiculos); // Guardar datos en el archivo de texto
            cout << "Registro eliminado correctamente.\n";
            return;
        }
    }
    cout << "No se encontró un vehiculo con esa placa.\n";
}

void gotoxy(int x, int y) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void frame() {
    setColor(11); 
    gotoxy(0, 0); std::cout << "+";
    gotoxy(0, 20); std::cout << "+";
    gotoxy(60, 0); std::cout << "+";
    gotoxy(60, 20); std::cout << "+";
    for (int i = 1; i < 60; i++) {
        gotoxy(i, 0); std::cout << "-";
    }
    for (int i = 1; i < 60; i++) {
        gotoxy(i, 3); std::cout << "-";
    }
    gotoxy(2, 2); std::cout << "Registro de Vehiculos";
    for (int l = 1; l < 20; l++) {
        gotoxy(60, l); std::cout << "|";
    }
    for (int j = 1; j < 60; j++) {
        gotoxy(j, 20); std::cout << "-";
    }
    for (int j = 1; j < 60; j++) {
        gotoxy(j, 18); std::cout << "-";
    }
    for (int k = 1; k < 20; k++) {
        gotoxy(0, k); std::cout << "|";
    }
    gotoxy(2, 19); std::cout << "Dylan Layedra - Kenneth Chicaiza";
    setColor(7); 
}

void mostrarFunciones() {
    frame();
    setColor(10); 
    gotoxy(15, 1); std::cout << "Menu de Vehiculos";
    gotoxy(5, 7); std::cout << "1. Registrar vehiculo";
    gotoxy(5, 8); std::cout << "2. Actualizar vehiculo";
    gotoxy(5, 9); std::cout << "3. Ver registros";
    gotoxy(5, 10); std::cout << "4. Eliminar vehiculo";
    setColor(11); 
    gotoxy(5, 11); std::cout << "5. Salir";
    setColor(7); 
}

void mostrarMenu() {
    int opcion = 1;
    char tecla;
    bool enterPressed = false;
    do {
        system("cls"); 
        mostrarFunciones();
        gotoxy(3, 6 + opcion); std::cout << "->";
        do {
            tecla = _getch();
            gotoxy(3, 6 + opcion); std::cout << "  "; 
            switch (tecla) {
                case 72: 
                    if (opcion > 1) opcion--;
                    break;
                case 80: 
                    if (opcion < 5) opcion++;
                    break;
                case 13: 
                    enterPressed = true;
                    break;
            }
            gotoxy(3, 6 + opcion); std::cout << "->"; 
        } while (!enterPressed);
        enterPressed = false;
        system("cls"); 
        switch (opcion) {
            case 1:
                registrarVehiculo();
                break;
            case 2:
                actualizarVehiculo();
                break;
            case 3:
                verRegistros();
                break;
            case 4:
                eliminarVehiculo();
                break;
            case 5:
                cout << "Saliendo...\n";
                break;
        }
        if (opcion != 5) {
            system("pause"); 
        }
    } while (opcion != 5);
}

int main() {
    cargarRegistros();
    mostrarMenu();
    return 0;
}