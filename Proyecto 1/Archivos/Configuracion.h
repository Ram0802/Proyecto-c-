#ifndef CONFIGURACION_H_INCLUDED
#define CONFIGURACION_H_INCLUDED

void Menu_Configuracion(){
    system("color 8F");
    int op;
    while(true){
            cout << "\t MENU CONFIGURACION \t"<<endl;
            cout << "------------------------------"<<endl;
            cout << "\n 1-REALIZAR BACKUP"<<endl;
            cout << "\n 2-RESTAURAR BACKUP"<<endl;
            cout << "-----------------------------"<<endl;
            cout << "\n 0-VOLVER AL MENU PRINCIPAL"<<endl<<endl;
            cout << "-----------------------------"<<endl;
            cout << "INGRESE UNA OPCION: ";
            cin >> op;

            switch(op){
            case 1:
                    system("cls");
                    ///HACER BACKUP
                    system("copy Clientes.dat backup\\Clientes.bkp");
                    system("copy Choferes.dat backup\\Choferes.bkp");
                    system("copy Viajes.dat backup\\Viajes.bkp");
                    cout << "BACKUP EXITOSO"<<endl;
                    system("pause");
                    system("cls");
                break;
            case 2:
                    ///RECUPERAR BACKUP
                    system("cls");
                    system("copy backup\\Clientes.bkp Clientes.dat");
                    system("copy backup\\Choferes.bkp Choferes.dat");
                    system("copy backup\\Viajes.bkp Viajes.dat");
                    cout << "RESTAURACION EXITOSO"<<endl;
                    system("pause");
                    system("cls");
                break;
            case 0:
                system("cls");
                system("color 03");
                return;
            break;
            default:
                system("cls");
                cout << "INGRESE UNA OPCION VALIDA"<<endl;
                system("pause > NUL");
                system("cls");
                continue;
            }


    }
}



#endif // CONFIGURACION_H_INCLUDED
