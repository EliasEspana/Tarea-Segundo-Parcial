#include <iostream>
using namespace std;

struct Estudiante {
    int id;
    string nombres;
    string apellidos;
    float notas[4];
    float promedio;
    bool aprobado;
};

void calcularPromedioYEstado(Estudiante* estudiante) {
    float suma = 0;
    for (int i = 0; i < 4; i++) {
        suma += estudiante->notas[i];
    }
    estudiante->promedio = suma / 4;
    estudiante->aprobado = estudiante->promedio >= 60 ? true : false;
}

int main() {
    int cantidadEstudiantes = 0, cantidadNotas = 4;
    cout << "Ingrese la cantidad de Estudiantes: ";
    cin >> cantidadEstudiantes;


    Estudiante* estudiantes = new Estudiante[cantidadEstudiantes];


    for (int i = 0; i < cantidadEstudiantes; i++) {
        cout << "Ingrese el ID del estudiante " << i + 1 << ": ";
        cin >> estudiantes[i].id;
        cout << "Ingrese los nombres del estudiante " << i + 1 << ": ";
        cin >> estudiantes[i].nombres;
        cout << "Ingrese los apellidos del estudiante " << i + 1 << ": ";
        cin >> estudiantes[i].apellidos;

        cout << "Ingrese las notas del estudiante " << i + 1 << ":" << endl;
        for (int j = 0; j < cantidadNotas; j++) {
            cout << "Nota " << j + 1 << ": ";
            cin >> estudiantes[i].notas[j];
        }
        

        calcularPromedioYEstado(&estudiantes[i]);
    }

    cout << "----------Datos de Estudiantes--------" << endl;
    for (int i = 0; i < cantidadEstudiantes; i++) {
        cout << "ID: " << estudiantes[i].id << endl;
        cout << "Nombres: " << estudiantes[i].nombres << endl;
        cout << "Apellidos: " << estudiantes[i].apellidos << endl;
        cout << "Promedio: " << estudiantes[i].promedio << endl;
        if (estudiantes[i].aprobado) {
            cout << "Estado: Aprobado" << endl;
        } else {
            cout << "Estado: Reprobado" << endl;
        }
        cout << "---------------------------------------" << endl;
    }

    delete[] estudiantes;

    return 0;
}
