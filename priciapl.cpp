#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h> 
#include <windows.h> 
#include <iomanip>
#include <locale.h> // Incluir biblioteca locale.h

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
    while (archivo >> v.placa >> ws && getline(archivo, v.propietario, '\t') && archivo >> v.modelo >> v.color >> v.cedula) {
        vehiculos.push_back(v);
    }
    archivo.close();
}

void guardarRegistros() {
    ofstream archivo(FILE_PATH, ios::out | ios::trunc); // Abrir en modo truncar para sobrescribir
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
    ofstream archivo(FILE_PATH, ios::out | ios::trunc); // Abrir en modo truncar para sobrescribir
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

bool esPlacaValida(const string& placa) {
    if (placa.length() != 7) return false;
    for (int i = 0; i < 3; i++) {
        if (!isupper(placa[i])) return false;
    }
    for (int i = 3; i < 7; i++) {
        if (!isdigit(placa[i])) return false;
    }
    return true;
}

void ingresarPlaca(const string &msj, string &valor) {
    char c;
    cout << msj;
    valor.clear();
    while (true) {
        c = _getch();
        if (c == 13 && esPlacaValida(valor)) { // Enter key and valid plate
            break;
        } else if (c == 8 && !valor.empty()) { // Backspace key
            cout << "\b \b";
            valor.pop_back();
        } else if ((valor.size() < 3 && isupper(c)) || (valor.size() >= 3 && valor.size() < 7 && isdigit(c))) {
            cout << c;
            valor.push_back(c);
        } else if (valor.size() < 3 && islower(c)) { // Convert lowercase to uppercase
            c = toupper(c);
            cout << c;
            valor.push_back(c);
        }
    }
    cout << endl;
    if (!esPlacaValida(valor)) {
        cout << "Placa invalida. Intente nuevamente." << endl;
        ingresarPlaca(msj, valor);
    }
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
    gotoxy(5, 5); std::cout << "Ingrese los datos del propietario:";
    gotoxy(5, 7); std::cout << "Cedula: ";
    ingresarCedula("", v.cedula);

    // Verificar si la cédula ya existe
    for (const auto& vehiculo : vehiculos) {
        if (vehiculo.cedula == v.cedula) {
            v.propietario = vehiculo.propietario;
            gotoxy(5, 9); std::cout << "Nombre y Apellido: " << v.propietario;
            break;
        }
    }

    if (v.propietario.empty()) {
        gotoxy(5, 9); std::cout << "Nombre y Apellido: ";
        ingresarTexto("", v.propietario, esSoloLetras);
    }

    gotoxy(5, 11); std::cout << "Ingrese los datos del vehiculo:";
    gotoxy(5, 13); std::cout << "Placa: ";
    ingresarPlaca("", v.placa);

    // Verificar si la placa ya existe
    for (const auto& vehiculo : vehiculos) {
        if (vehiculo.placa == v.placa) {
            v = vehiculo;
            gotoxy(5, 15); std::cout << "Modelo: " << v.modelo;
            gotoxy(5, 17); std::cout << "Color: " << v.color;
            cout << "\nDatos del vehiculo cargados automaticamente.\n";
            return; // No guardar el registro nuevamente
        }
    }

    gotoxy(5, 15); std::cout << "Modelo: ";
    ingresarTexto("", v.modelo, esSoloLetras);
    gotoxy(5, 17); std::cout << "Color: ";
    ingresarTexto("", v.color, esSoloLetras);
    vehiculos.push_back(v);
    guardarDatos(vehiculos); // Guardar todos los datos para evitar duplicados
    cout << "Registro guardado correctamente.\n";
}

void registrarVehiculoCliente(const string& nombre, const string& cedula) {
    Vehiculo v;
    v.propietario = nombre;
    v.cedula = cedula;
    system("cls");
    frame();
    gotoxy(5, 5); std::cout << "Ingrese los datos del vehiculo:";
    gotoxy(5, 7); std::cout << "Propietario: " << v.propietario;
    gotoxy(5, 9); std::cout << "Cedula: " << v.cedula;
    gotoxy(5, 11); std::cout << "Placa: ";
    ingresarPlaca("", v.placa);

    // Verificar si la placa ya existe
    for (const auto& vehiculo : vehiculos) {
        if (vehiculo.placa == v.placa) {
            v = vehiculo;
            gotoxy(5, 13); std::cout << "Modelo: " << v.modelo;
            gotoxy(5, 15); std::cout << "Color: " << v.color;
            cout << "\nDatos del vehiculo cargados automaticamente.\n";
            return; // No guardar el registro nuevamente
        }
    }

    gotoxy(5, 13); std::cout << "Modelo: ";
    ingresarTexto("", v.modelo, esSoloLetras);
    gotoxy(5, 15); std::cout << "Color: ";
    ingresarTexto("", v.color, esSoloLetras);
    vehiculos.push_back(v);
    guardarDatos(vehiculos); // Guardar todos los datos para evitar duplicados
    cout << "Registro guardado correctamente.\n";
}

void actualizarVehiculo() {
    string placa;
    cout << "Ingrese la placa del vehiculo a actualizar: ";
    ingresarPlaca("", placa);
    for (auto& v : vehiculos) {
        if (v.placa == placa) {
            cout << "Modelo actual: " << v.modelo << endl;
            cout << "Color actual: " << v.color << endl;
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
    ifstream archivo(FILE_PATH);
    if (!archivo) {
        cout << "No se pudo abrir el archivo de registros.\n";
        return;
    }
    string linea;
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }
    archivo.close();
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

void eliminarTodosLosVehiculos() {
    vehiculos.clear();
    guardarRegistros();
    guardarDatos(vehiculos);
    cout << "Todos los registros han sido eliminados correctamente.\n";
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
    gotoxy(0, 25); std::cout << "+";
    gotoxy(70, 0); std::cout << "+";
    gotoxy(70, 25); std::cout << "+";
    for (int i = 1; i < 70; i++) {
        gotoxy(i, 0); std::cout << "-";
    }
    for (int i = 1; i < 70; i++) {
        gotoxy(i, 3); std::cout << "-";
    }
    setColor(10); // Cambiar el color a verde
    gotoxy(2, 2); std::cout << "Registro de Vehiculos";
    setColor(11); 
    for (int l = 1; l < 25; l++) {
        gotoxy(70, l); std::cout << "|";
    }
    for (int j = 1; j < 70; j++) {
        gotoxy(j, 25); std::cout << "-";
    }
    for (int j = 1; j < 70; j++) {
        gotoxy(j, 23); std::cout << "-";
    }
    for (int k = 1; k < 25; k++) {
        gotoxy(0, k); std::cout << "|";
    }
    gotoxy(2, 24); std::cout << "Dylan Layedra - Kenneth Chicaiza";
    setColor(7); 
    time_t now = time(0);
    tm* time = localtime(&now);
    std::vector<std::string> mes = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12" };
    int year = 1900 + time->tm_year;
    gotoxy(58, 1); std::cout << time->tm_mday << "/" << mes[time->tm_mon] << "/" << year;
    gotoxy(60, 2); std::cout << time->tm_hour << ":" << time->tm_min << ":" << time->tm_sec;
    setColor(7); 
}

void mostrarFuncionesAdmin() {
    frame();
    setColor(10); // Cambiar el color a verde
    gotoxy(15, 1); std::cout << "Menu de Vehiculos (Admin)";
    setColor(14); // Cambiar el color a amarillo
    gotoxy(5, 7); std::cout << "1. Registrar vehiculo";
    gotoxy(5, 8); std::cout << "2. Actualizar vehiculo";
    gotoxy(5, 9); std::cout << "3. Ver registros";
    gotoxy(5, 10); std::cout << "4. Eliminar vehiculo";
    gotoxy(5, 11); std::cout << "5. Eliminar todos los vehiculos";
    setColor(12); // Cambiar el color a rojo
    gotoxy(5, 12); std::cout << "6. Regresar";
    setColor(7); 
}

void verMisVehiculos(const string& cedula) {
    ifstream archivo(FILE_PATH);
    if (!archivo) {
        cout << "No se pudo abrir el archivo de registros.\n";
        return;
    }
    string linea;
    bool encontrado = false;
    cout << left << setw(15) << "Placa" << setw(20) << "Propietario" << setw(20) << "Modelo" << setw(15) << "Color" << setw(15) << "Cedula" << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
    while (getline(archivo, linea)) {
        if (linea.find(cedula) != string::npos) {
            cout << linea << endl;
            encontrado = true;
        }
    }
    if (!encontrado) {
        cout << "No se encontraron vehiculos registrados con su cedula.\n";
    }
    archivo.close();
}

void mostrarFuncionesCliente() { 
    frame();
    setColor(10); // Cambiar el color a verde
    gotoxy(15, 1); std::cout << "Menu de Vehiculos (Cliente)";
    setColor(14); // Cambiar el color a amarillo
    gotoxy(5, 7); std::cout << "1. Registrar vehiculo";
    gotoxy(5, 8); std::cout << "2. Actualizar vehiculo";
    gotoxy(5, 9); std::cout << "3. Ver mis vehiculos";
    setColor(12); // Cambiar el color a rojo
    gotoxy(5, 10); std::cout << "4. Regresar";
    setColor(7); 
}

void mostrarMenuAdmin() {
    int opcion = 1;
    char tecla;
    bool enterPressed = false;
    do {
        system("cls"); 
        mostrarFuncionesAdmin();
        gotoxy(3, 6 + opcion); std::cout << "->";
        do {
            tecla = _getch();
            gotoxy(3, 6 + opcion); std::cout << "  "; 
            switch (tecla) {
                case 72: 
                    if (opcion > 1) opcion--;
                    break;
                case 80: 
                    if (opcion < 6) opcion++;
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
                eliminarTodosLosVehiculos();
                break;
            case 6:
                cout << "Saliendo...\n";
                break;
        }
        if (opcion != 6) {
            system("pause"); 
        }
    } while (opcion != 6);
}

void mostrarMenuCliente(const string& nombre, const string& cedula) {
    int opcion = 1;
    char tecla;
    bool enterPressed = false;
    do {
        system("cls"); 
        mostrarFuncionesCliente();
        gotoxy(3, 6 + opcion); std::cout << "->";
        do {
            tecla = _getch();
            gotoxy(3, 6 + opcion); std::cout << "  "; 
            switch (tecla) {
                case 72: 
                    if (opcion > 1) opcion--;
                    break;
                case 80: 
                    if (opcion < 4) opcion++;
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
                registrarVehiculoCliente(nombre, cedula);
                break;
            case 2:
                actualizarVehiculo();
                break;
            case 3:
                verMisVehiculos(cedula);
                break;
            case 4:
                cout << "Saliendo...\n";
                break;
        }
        if (opcion != 4) {
            system("pause"); 
        }
    } while (opcion != 4);
}

bool verificarContrasena() {
    string contrasena;
    gotoxy(5, 7); std::cout << "Ingrese la contraseña: ";
    char c;
    while ((c = _getch()) != 13) { // 13 es el código ASCII para Enter
        if (c == 8 && !contrasena.empty()) { // Backspace
            cout << "\b \b";
            contrasena.pop_back();
        } else if (isalnum(c)) {
            cout << '*';
            contrasena.push_back(c);
        }
    }
    cout << endl;
    return contrasena == "1234";
}

void seleccionarUsuario() {
    int opcion = 1;
    char tecla;
    bool enterPressed = false;
    do {
        system("cls");
        frame();
        gotoxy(15, 1); std::cout << "Seleccione el tipo de usuario:";
        setColor(5); // Morado para Administrador
        gotoxy(5, 7); std::cout << (opcion == 1 ? "-> " : "   ") << "1. Administrador";
        setColor(13); // Rosado para Cliente
        gotoxy(5, 8); std::cout << (opcion == 2 ? "-> " : "   ") << "2. Cliente";
        setColor(7); // Resetear color
        do {
            tecla = _getch();
            switch (tecla) {
                case 72: // Flecha arriba
                    if (opcion > 1) opcion--;
                    break;
                case 80: // Flecha abajo
                    if (opcion < 2) opcion++;
                    break;
                case 13: // Enter
                    enterPressed = true;
                    break;
            }
            gotoxy(5, 7); setColor(5); std::cout << (opcion == 1 ? "-> " : "   ") << "1. Administrador";
            gotoxy(5, 8); setColor(13); std::cout << (opcion == 2 ? "-> " : "   ") << "2. Cliente";
            setColor(7); // Resetear color
        } while (!enterPressed);
        enterPressed = false;
        system("cls"); // Borrar la pantalla antes de mostrar el siguiente menú
        frame(); // Mostrar el cuadro nuevamente
        if (opcion == 1) {
            if (verificarContrasena()) {
                system("cls");
                frame();
                mostrarMenuAdmin();
            } else {
                system("cls");
                frame();
                gotoxy(5, 10); std::cout << "Contraseña incorrecta. Intente nuevamente.";
                system("pause");
            }
        } else if (opcion == 2) {
            string nombre, cedula;
            system("cls");
            frame();
            gotoxy(5, 7); std::cout << "Ingrese su nombre y apellido: ";
            ingresarTexto("", nombre, esSoloLetras);
            gotoxy(5, 9); std::cout << "Ingrese su cedula: ";
            ingresarCedula("", cedula);
            if (esCedulaValida(cedula)) {
                system("cls");
                frame();
                mostrarMenuCliente(nombre, cedula);
            } else {
                system("cls");
                frame();
                gotoxy(5, 10); std::cout << "Cedula invalida. Intente nuevamente.";
                system("pause");
            }
        }
    } while (true);
}

void configurarConsola() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "es_ES.UTF-8");
}

int main() {
    configurarConsola();
    cargarRegistros();
    cout << "Registros cargados correctamente.\n";
    seleccionarUsuario();
    return 0;
}