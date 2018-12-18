#ifndef REPORTES_H_INCLUDED
#define REPORTES_H_INCLUDED


void Menu_reportes();
void ponerceroV(int*);
void Reporte1();
void Reporte2();
void Reporte3();
void ReporteB();
void ponercerov2(int*);
int buscarmenor(int*);
void buscardni(int);
void ponercero2(int*);
void ReporteC();
int comparacion(int);

///Direccion = Choferes.dat
///DireccionC = Clientes.dat
///DireccionV = Viajes.dat

void Reporte1(){
    ///Para cada cliente la cantidad de viajes realizados por cada mes del año actual.
    struct viajes reg;
    //struct fecha_viaje aux;
    int vec[12];
    ponerceroV(vec);
    FILE *P;
    P = fopen(DireccionV,"rb");
    if(P==NULL){
        exit(-1);
    }
    while(fread(&reg,sizeof(viajes),1,P)==1){
        if(reg.Viajeanio==2018){
        vec[reg.Viajemes-1]++;
        }
    }
    fclose(P);
    for(int j=0;j<12;j++){
        cout << "MES: "<<j+1<<endl;
        cout<<"CANTIDAD DE VIAJES: "<<vec[j]<<endl;
        cout << " ============================ "<<endl;
    }
}
void ponerceroV(int *vec){
    int i;
    for(i=0;i<12;i++){
        vec[i]=0;
    }
}

void Reporte2(){
    struct Chofer reg;
    //struct FechaVencimiento aux;
    int i=0;
    FILE *p;
    p=fopen(Direccion,"rb");
    if(p==NULL){
        exit(-1);
    }
    while(fread(&reg,sizeof(reg),1,p)==1){
        if(reg.VNmes==10&&reg.VNanio==2018){
            i++;
        }
    }
    fclose(p);
    cout << "CHOFERES A LOS QUE LES VENCE LA LICENCIA EN OCTUBRE DE 2018: "<<i<<endl;
}

/*void Reporte3(){
    struct Cliente reg;
    int i=0;
    FILE *p;
    p = fopen(DireccionC,"rb");
    if(p==NULL){
        exit(-1);
    }
    while(fread(&reg,sizeof(Cliente),1,p)==1){
        if(comparacion(reg.IDCliente)!=1){
            i++;
        }
    }
    fclose(p);
    cout <<"CLIENTES QUE NO REALIZARON VIAJES: "<<i<<endl;
}*/

/*int comparacion(int ID){
    struct viajes reg;
    //int i=0;
    FILE *p;
    p = fopen(DireccionV,"rb");
    if(p==NULL){
        exit(-1);
    }
    while(fread(&reg,sizeof(viajes),1,p)==1){
        if(ID==reg.IDCliente-1){ ///reg.idCliente-1 por que en viajes.h eso no estaba
                return 1;
        }
        //i++;
    }
    fclose(p);
    return -1;
}*/
void Reporte3(){  ///EL MISMO QUE EL REPORTE 3 COMUN, PERO ESTE MUESTRA LOS CLIENTES QUE NO REALIZARON NINGUN VIAJE.
    struct Cliente reg;
    int i=0,cant;
    int v[cant_registros_Cliente()];
    ponercero2(v);
    FILE *p;
    p = fopen(DireccionC,"rb");
    if(p==NULL){
        exit(-1);
    }
    while(fread(&reg,sizeof(Cliente),1,p)==1){
        if(comparacion(reg.IDCliente)!=1){
            i++;
            v[i]=reg.IDCliente;

        }
    }
    cant=i;
    fclose(p);
    cout <<"CLIENTES QUE NO REALIZARON VIAJES: "<<cant<<endl;
    for(int i=0;i<cant;i++){
    //cout << "cont: "<<i+1<<endl;
    reg=Leer_Cliente(v[i+1]); ///el i+1 es para que cuente apartir del 1 y en adelante
    mostrar_cliente(reg);

    //

    }
}
void ponercero2(int *vec){
    int i;
    for(i=0;i<cant_registros_Cliente();i++){
        vec[i]=0;
    }
}
int comparacion(int ID){
    struct viajes reg;
    //int i=0;
    FILE *p;
    p = fopen(DireccionV,"rb");
    if(p==NULL){
        exit(-1);
    }
    while(fread(&reg,sizeof(viajes),1,p)==1){
        if(ID==reg.IDCliente-1){
                return 1;
        }
        //i++;
    }
    fclose(p);
    return -1;
}

void ReporteB(){
    struct viajes reg;
    int vec[6];
    int minimo=0;
    ponercerov2(vec);
    //char DNI[10];
    FILE *p;
    p=fopen(DireccionV,"rb");
    if(p==NULL){
        exit(-1);
    }
    while(fread(&reg,sizeof(reg),1,p)==1){
        if(reg.Viajemes<7 && reg.Viajemes>0){
            vec[reg.Viajemes-1]+=reg.Importe;
        }
    }
    fclose(p);
    minimo=buscarmenor(vec);
    buscardni(minimo);
    ///mostrarv(vec);
}

void ponercerov2(int *v){
    for(int i=0;i<6;i++){
        v[i]=0;
    }
}

int buscarmenor(int *v){
    int mesmax=0;
    for(int i=0; i<6;i++){
        if(i==0){
            mesmax=i;
        }
        if(v[mesmax]<v[i] && v[i]!=0){
            mesmax=i;
        }
    }
    return mesmax;
}

void buscardni(int minimo){
    struct viajes reg;
    struct Chofer aux;
    int i=0,pos;
    char DNI[10];
    FILE *a;
    a= fopen(DireccionV, "rb");
    if(a==NULL){
        exit(-1);
    }
    while(fread(&reg,sizeof(reg),1,a)==1){

            if(reg.Viajemes==minimo){
                i++;
                strcpy(DNI,reg.DNIChofer);
            }
    }
    fclose(a);
    cout << "EL CHOFER QUE MENOS RECAUDO EN EL PRIMER SEMESTRE: "<<endl;
    pos=Buscar_Chofer(DNI);
    aux= Leer_Chofer(pos);
    mostrar_chofer(aux);

}
void ReporteC(){
    struct viajes reg;
    struct Chofer aux;
    struct Cliente aux2;
    int maximoKM=0, IDmax=0,i=0, pos=0;
    char DNImax[10];
    FILE *p;
    p=fopen(DireccionV,"rb");
    if(p==NULL){
        exit(-1);
    }
    while(fread(&reg,sizeof(reg),1,p)==1){

        if(i==0){
            maximoKM=reg.Kilometraje;
            strcpy(DNImax,reg.DNIChofer);
            IDmax=reg.IDCliente;
        }
        if(reg.Kilometraje>maximoKM){
            maximoKM=reg.Kilometraje;
            strcpy(DNImax,reg.DNIChofer);
            IDmax=reg.IDCliente;
        }
        i++;
    }
    fclose(p);
    cout<< "ID: "<< IDmax<<endl;
    aux2 = Leer_Cliente(IDmax-1); ///el menos 1 es para encontrar su posicion real.
    mostrar_cliente(aux2);
    //cout<< "DNI: "<< DNImax<<endl;
    pos=Buscar_Chofer(DNImax);
    aux= Leer_Chofer(pos);
    mostrar_chofer(aux);
    cout<< "MAXIMO KILOMETRAJE: "<< maximoKM<<endl;
}

void Menu_reportes(){
    system("color 30");
    int op;
    while(true){
            cout << "\t MENU REPORTES \t"<<endl;
            cout << "------------------------------"<<endl;
            cout << "\n 1-REPORTE \"1\" "<<endl;
            cout << "\n 2-REPORTE \"2\""<<endl;
            cout << "\n 3-REPORTE \"3\""<<endl;
            cout << "\n 4-REPORTE \"4\""<<endl;
            cout << "\n 5-REPORTE \"5\""<<endl;
            cout << "-----------------------------"<<endl;
            cout << "\n 0-VOLVER AL MENU PRINCIPAL"<<endl<<endl;
            cout << "-----------------------------"<<endl;
            cout << "INGRESE UNA OPCION: ";
            cin >> op;

            switch(op){
            case 1:
                    system("cls");
                    ///REPORTE 1
                    Reporte1();
                    system("pause > NUL");
                    system("cls");
                break;
            case 2:
                    ///REPORTE 2
                    system("cls");
                    Reporte2();
                    system("pause > NUL");
                    system("cls");
                break;
            case 3:
                    system("cls");
                    ///REPORTE 3
                    Reporte3();
                    system("pause > NUL");
                    system("cls");
                break;
            case 4:
                system("cls");
                ReporteB();
                system("pause > NUL");
                system("cls");
                break;
            case 5:
                system("cls");
                ReporteC();
                system("pause > NUL");
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

#endif // REPORTES_H_INCLUDED
