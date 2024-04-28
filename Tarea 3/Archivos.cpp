#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Estudiante {
    int id;
    char nombres[50];
    char apellidos[50];
    float notas[4];
    float promedio;
    char resultado[20];
};

void calcularPromedioYResultado(Estudiante* estudiante) {
    float suma = 0;
    for (int i = 0; i < 4; i++) {
        suma += estudiante->notas[i];
    }
    estudiante->promedio = suma / 4;
    if (estudiante->promedio >= 60) {
        strcpy(estudiante->resultado, "Aprobado");
    } else {
        strcpy(estudiante->resultado, "Reprobado");
    }
}

void crearEstudiante() {
    Estudiante estudiante;
    ofstream archivo("notas.dat", ios::binary | ios::app);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    cout << "Ingrese el ID del estudiante: ";
    cin >> estudiante.id;
    cout << "Ingrese los nombres del estudiante: ";
    cin.ignore();
    cin.getline(estudiante.nombres, 50);
    cout << "Ingrese los apellidos del estudiante: ";
    cin.getline(estudiante.apellidos, 50);
    cout << "Ingrese las 4 notas del estudiante: ";
    for (int i = 0; i < 4; i++) {
        cin >> estudiante.notas[i];
    }

    calcularPromedioYResultado(&estudiante);

    archivo.write(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));

    archivo.close();
}

void mostrarEstudiantes() {
    ifstream archivo("notas.dat", ios::binary);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    Estudiante estudiante;
    while (archivo.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
        cout << "ID: " << estudiante.id << endl;
        cout << "Nombres: " << estudiante.nombres << endl;
        cout << "Apellidos: " << estudiante.apellidos << endl;
        cout << "Notas: ";
        for (int i = 0; i < 4; i++) {
            cout << estudiante.notas[i] << " ";
        }
        cout << endl;
        cout << "Promedio: " << estudiante.promedio << endl;
        cout << "Resultado: " << estudiante.resultado << endl;
        cout << "---------------------------------------" << endl;
    }

    archivo.close();
}

void actualizarEstudiante(int id) {
    fstream archivo("notas.dat", ios::binary | ios::in | ios::out);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    Estudiante estudiante;
    bool encontrado = false;
    while (archivo.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
        if (estudiante.id == id) {
            cout << "Ingrese los nuevos nombres del estudiante: ";
            cin.ignore();
            cin.getline(estudiante.nombres, 50);
            cout << "Ingrese los nuevos apellidos del estudiante: ";
            cin.getline(estudiante.apellidos, 50);
            cout << "Ingrese las 4 nuevas notas del estudiante: ";
            for (int i = 0; i < 4; i++) {
                cin >> estudiante.notas[i];
            }
            calcularPromedioYResultado(&estudiante);

            archivo.seekp(-sizeof(Estudiante), ios::cur);
            archivo.write(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));
            encontrado = true;
            break;
        }
    }

    archivo.close();

    if (!encontrado) {
        cout << "Estudiante no encontrado." << endl;
    } else {
        cout << "Datos del estudiante actualizados correctamente." << endl;
    }
}

void eliminarEstudiante(int id) {
    ifstream archivoEntrada("notas.dat", ios::binary);
    if (!archivoEntrada) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    ofstream archivoSalida("temp.dat", ios::binary);
    if (!archivoSalida) {
        cout << "Error al abrir el archivo temporal." << endl;
        return;
    }

    Estudiante estudiante;
    bool encontrado = false;
    while (archivoEntrada.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
        if (estudiante.id != id) {
            archivoSalida.write(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));
        } else {
            encontrado = true;
        }
    }

    archivoEntrada.close();
    archivoSalida.close();

    remove("notas.dat");
    rename("temp.dat", "notas.dat");

    if (encontrado) {
        cout << "Estudiante eliminado correctamente." << endl;
    } else {
        cout << "Estudiante no encontrado." << endl;
    }
}

int main() {
    int opcion;

    do {
        cout << "1. Crear estudiante" << endl;
        cout << "2. Mostrar estudiantes" << endl;
        cout << "3. Actualizar datos de estudiante" << endl;
        cout << "4. Eliminar estudiante" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                crearEstudiante();
                break;
            case 2:
                mostrarEstudiantes();
                break;
            case 3:
                int id;
                cout << "Ingrese el ID del estudiante a actualizar: ";
                cin >> id;
                actualizarEstudiante(id);
                break;
            case 4:
                int idEliminar;
                cout << "Ingrese el ID del estudiante a eliminar: ";
                cin >> idEliminar;
                eliminarEstudiante(idEliminar);
                break;
            case 0:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while (opcion != 0);

    return 0;
}

