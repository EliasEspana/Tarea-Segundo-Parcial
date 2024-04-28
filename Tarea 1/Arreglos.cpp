#include <iostream>
using namespace std;

main(){	


string id,nombres,apellidos;
int tam = 4, suma = 0, promedio = 0;	
int notas [tam];
char res;

	do{	
	cout<<"Ingrese ID: "<<endl;
	cin>>id;
	cin.ignore();
	cout<<"Ingrese Nombres: "<<endl;
	getline(cin,nombres);
	cout<<"Ingrese apellidos: "<<endl;
	getline(cin,apellidos);
	
	for(int i=0; i<tam;i++){
		cout<<"Ingrese nota "<<i<<":";
		cin>>notas[i];
		}
	
	for(int i=0; i<tam; i++){
		suma += notas[i]; //suma = suma + notas[i];
	}
	promedio = suma / tam;
	cout<<"El promedio es: "<<promedio<<endl;	
	system("cls");
	if(promedio > 60){
		cout<<"El estudiante "<<id<<" "<<nombres<<" "<<apellidos<<" fue aprovado!"<<endl;
		}
	else{
		cout<<"El estudiante "<<id<<" "<<nombres<<" "<<apellidos<<" fue reprobado!"<<endl;
	};
	cout<<"Desea ingresar mas estudiantes(s/n):";
	cin>>res;
	
    }while(res == 's'|| res == 'S');
}
