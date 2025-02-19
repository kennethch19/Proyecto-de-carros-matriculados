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
    string cedula; // Añadir campo de cédula
};

vector<Vehiculo> vehiculos;

void cargarRegistros() {
    ifstream archivo(FILE_PATH);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo. Se creara uno nuevo al guardar los registros.\n";
        return;
    }
    string header;
    getline(archivo, header); // Leer la primera línea (encabezado)
    getline(archivo, header); // Leer la segunda línea (separador)
    Vehiculo v;
    while (archivo >> v.placa >> v.propietario >> v.modelo >> v.color >> v.cedula) {
        vehiculos.push_back(v);
    }
    archivo.close();
}

void guardarRegistros() {
    ofstream archivo(FILE_PATH, ios::out | ios::trunc);
    if (!archivo) {
        cerr << "Error al abrir el archivo para escritura.\n";
        return;
    }
    archivo << left << setw(15) << "Placa" << setw(20) << "Propietario" << setw(20) << "Modelo" << setw(15) << "Color" << setw(15) << "Cedula" << endl;
    archivo << "----------------------------------------------------------------------------------------" << endl;
    for (const auto& v : vehiculos) {
        archivo << left << setw(15) << v.placa << setw(20) << v.propietario << setw(20) << v.modelo << setw(15) << v.color << setw(15) << v.cedula << endl;
    }
    archivo.close();
}

void guardarDatos(const vector<Vehiculo> &vehiculos) {
    ofstream archivo(FILE_PATH, ios::out | ios::trunc);
    if (archivo.is_open()) {
        archivo << left << setw(15) << "Placa" << setw(20) << "Propietario" << setw(20) << "Modelo" << setw(15) << "Color" << setw(15) << "Cedula" << endl;
        archivo << "----------------------------------------------------------------------------------------" << endl;
        for (const auto &v : vehiculos) {
            archivo << left << setw(15) << v.placa << setw(20) << v.propietario << setw(20) << v.modelo << setw(15) << v.color << setw(15) << v.cedula << endl;
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo para guardar los datos." << endl;
    }
}

bool esSoloLetras(const string& str) {
    for (char c : str) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}

bool esCedulaValida(const string& cedula) {
    if (cedula.length() != 10) return false;
    int suma = 0;
    for (int i = 0; i < 9; i++) {
        int digito = cedula[i] - '0';
        if (i % 2 == 0) {
            digito *= 2;
            if (digito > 9) digito -= 9;
        }
        suma += digito;
    }
    int ultimoDigito = cedula[9] - '0';
    int decenaSuperior = (suma + 9) / 10 * 10;
    return (decenaSuperior - suma) == ultimoDigito;
}

void ingresarTexto(const string &msj, string &valor, bool (*validacion)(const string&)) {
    char c;
    cout << msj;
    valor.clear();
    while ((c = _getch()) != 13) {
        if (isalpha(c) || c == ' ') {
            cout << c;
            valor.push_back(c);
        } else if (c == 8 && !valor.empty()) { 
            cout << "\b \b";
            valor.pop_back();
        }
    }
    cout << endl;
    if (!validacion(valor)) {
        cout << "Entrada invalida. Intente nuevamente." << endl;
        ingresarTexto(msj, valor, validacion);
    }
}

void ingresarPlaca(const string &msj, string &valor) {
    char c;
    cout << msj;
    valor.clear();
    while ((c = _getch()) != 13) {
        if (isalnum(c)) { // Permitir cualquier carácter alfanumérico
            cout << c;
            valor.push_back(c);
        } else if (c == 8 && !valor.empty()) { 
            cout << "\b \b";
            valor.pop_back();
        }
    }
    cout << endl;
}

void ingresarCedula(const string &msj, string &valor) {
    char c;
    cout << msj;
    valor.clear();
    while ((c = _getch()) != 13) {
        if (isdigit(c) && valor.size() < 10) {
            cout << c;
            valor.push_back(c);
        } else if (c == 8 && !valor.empty()) { 
            cout << "\b \b";
            valor.pop_back();
        }
    }
    cout << endl;
    if (!esCedulaValida(valor)) {
        cout << "Cédula invalida. Intente nuevamente." << endl;
        ingresarCedula(msj, valor);
    }
}

void gotoxy(int x, int y);
void frame();

void registrarVehiculo() {
    Vehiculo v;
    system("cls");
    frame();
    gotoxy(5, 5); std::cout << "Ingrese los datos del vehiculo:";
    gotoxy(5, 7); std::cout << "Cedula: ";
    ingresarCedula("", v.cedula);
    gotoxy(5, 9); std::cout << "Placa: ";
    ingresarPlaca("", v.placa);
    gotoxy(5, 11); std::cout << "Propietario: ";
    ingresarTexto("", v.propietario, esSoloLetras);
    gotoxy(5, 13); std::cout << "Modelo: ";
    ingresarTexto("", v.modelo, esSoloLetras);
    gotoxy(5, 15); std::cout << "Color: ";
    ingresarTexto("", v.color, esSoloLetras);
    vehiculos.push_back(v);
    guardarRegistros();
    guardarDatos(vehiculos);
    cout << "Registro guardado correctamente.\n";
}


void actualizarVehiculo() {
    string placa;
    ingresarPlaca("Ingrese la placa del vehiculo a actualizar: ", placa); // Cambiar el mensaje
    for (auto& v : vehiculos) {
        if (v.placa == placa) {
            ingresarCedula("Ingrese la nueva cedula del propietario: ", v.cedula);
            ingresarTexto("Ingrese el nuevo propietario: ", v.propietario, esSoloLetras);
            ingresarTexto("Ingrese el nuevo modelo: ", v.modelo, esSoloLetras);
            ingresarTexto("Ingrese el nuevo color: ", v.color, esSoloLetras);
            guardarRegistros();
            guardarDatos(vehiculos); // Guardar datos en el archivo de texto
            cout << "Registro actualizado correctamente.\n";
            return;
        }
    }
    cout << "No se encontro un vehiculo con esa placa.\n";
}

void verRegistros() {
    if (vehiculos.empty()) {
        cout << "No hay registros disponibles.\n";
        return;
    }
    cout << left << setw(15) << "Placa" << setw(20) << "Propietario" << setw(20) << "Modelo" << setw(15) << "Color" << setw(15) << "Cedula" << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
    for (const auto& v : vehiculos) {
        cout << left << setw(15) << v.placa << setw(20) << v.propietario << setw(20) << v.modelo << setw(15) << v.color << setw(15) << v.cedula << endl;
    }
}

void eliminarVehiculo() {
    string placa;
    ingresarPlaca("Ingrese la placa del vehiculo a eliminar: ", placa); // Cambiar el mensaje
    for (auto it = vehiculos.begin(); it != vehiculos.end(); ++it) {
        if (it->placa == placa) {
            vehiculos.erase(it);
            guardarRegistros();
            guardarDatos(vehiculos); // Guardar datos en el archivo de texto
            cout << "Registro eliminado correctamente.\n";
            return;
        }
    }
    cout << "No se encontro un vehiculo con esa placa.\n";
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
    setColor(10); // Cambiar el color a verde
    gotoxy(2, 2); std::cout << "Registro de Vehiculos";
    setColor(11); 
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
    time_t now = time(0);
    tm* time = localtime(&now);
    std::vector<std::string> mes = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12" };
    int year = 1900 + time->tm_year;
    gotoxy(48, 1); std::cout << time->tm_mday << "/" << mes[time->tm_mon] << "/" << year;
    gotoxy(50, 2); std::cout << time->tm_hour << ":" << time->tm_min << ":" << time->tm_sec;
    setColor(7); 
}

void mostrarFunciones() {
    frame();
    setColor(10); // Cambiar el color a verde
    gotoxy(15, 1); std::cout << "Menu de Vehiculos";
    setColor(14); // Cambiar el color a amarillo
    gotoxy(5, 7); std::cout << "1. Registrar vehiculo";
    gotoxy(5, 8); std::cout << "2. Actualizar vehiculo";
    gotoxy(5, 9); std::cout << "3. Ver registros";
    gotoxy(5, 10); std::cout << "4. Eliminar vehiculo";
    setColor(12); // Cambiar el color a rojo
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