#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <conio.h>
#include <clocale>
#include <ctime>
using namespace std;

#include "Archivos/Fecha.h"
#include "Archivos/Clientes.h"
#include "Archivos/Choferes.h"
#include "Archivos/viajes.h"
#include "Archivos/Reportes.h"
#include "Archivos/Configuracion.h"


int main(){
    setlocale(LC_ALL, "");
    int opc;
    while(2){
        system("cls");
        cout << "\t MENU PRINCIPAL \t"<<endl;
        cout << "-------------------------------"<<endl;
        cout << "\n 1-CLIENTES"<<endl;
        cout << "\n 2-CHOFERES"<<endl;
        cout << "\n 3-VIAJES"<<endl;
        cout << "\n 4-REPORTES"<<endl;
        cout << "\n 5-CONFIGURACION"<<endl;
        cout << "-------------------------------"<<endl;
        cout << "\n 0-SALIR DEL PROGRAMA"<<endl<<endl;
        cout << "-------------------------------"<<endl;
        cout << "INGRESE UNA OPCION: ";
        cin >> opc;

        switch(opc){
            case 1:
                system("cls");
                ///Clientes
                Menu_cliente();
                break;
            case 2:
                system("cls");
                ///Choferes
                Menu_chofer();
                break;
            case 3:
                system("cls");
                ///Viajes
                Menu_viajes();
                break;
            case 4:
                system("cls");
                ///Reportes
                Menu_reportes();
                break;
            case 5:
                system("cls");
                ///Configuracion --> backup y recuperacion.
                Menu_Configuracion();
                break;
            case 0:
                system("cls");
                return 0;
                system("pause > NUL");
                break;
            default:
                system("cls");
                cout << "OPCION NO VALIDA..."<<endl;
                system("pause > NUL");
                break;
        }
    }
return 0;
}
