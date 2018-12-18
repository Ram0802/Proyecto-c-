#ifndef VIAJES_H_INCLUDED
#define VIAJES_H_INCLUDED

/*struct fecha_viaje{
    int dia,mes,anio;
};

fecha_viaje cargar_fechav(){
    fecha_viaje f;
    cout << "DIA: ";
    cin >>f.dia;
    cout << endl;
    cout << "MES: ";
    cin >> f.mes;
    cout << endl;
    cout << "ANIO: ";
    cin >> f.anio;
    cout << endl;
    return f;
}

void mostrar_fechaViaje(struct fecha_viaje f){
    cout << f.dia<<"/"<<f.mes<<"/"<<f.anio<<endl;
}*/


struct viajes{
    int IDViaje; ///- Autonumerico.
    char DNIChofer[10]; ///---> tiene que estar en el archivo choferes
    int IDCliente; ///---> tiene que estar en el archivo clientes
    ///fecha_viaje FechaViaje;
    int Viajedia,Viajemes,Viajeanio;
    int HoraSalida;
    float Kilometraje;
    float Importe;
    char Patente[10];
    int Calificacion;
    bool Estado;
};


///DIRECCION
///CONSTANTES
const char DireccionV[] = "Viajes.dat"; ///Viajes
///PROTOTIPOS
void Alta_Viaje();
int cant_viajes();
int Buscar_Viaje(char);
viajes cargar_viaje();
void mostrar_viaje(viajes);
void Listar_viajes();
void Listar_viajexID();
bool guardar_viaje(viajes);
viajes Leer_viaje(int);
void baja_viajexID();
int comparar_ID(int*);
int estado(viajes,int);
bool modificar(viajes, int*);
int validar_HoraSalida(int);
int validar_Kilometraje(float);
int validar_Importe(float);
int validar_Calificacion(int);
int verificar_DNI(char*);
int verificar_idCliente(int);
int verificar_FechaViaje(int,int,int);
void Menu_viajes();

viajes cargar_viajes(){
    viajes v;
    v.IDViaje=cant_viajes();
    cout << "DNI: ";
    cin >> v.DNIChofer;
    if(verificar_DNI(v.DNIChofer)==-1){
        cout << "INGRESE UN DNI VALIDO"<<endl;
        exit(-1);
    }
    cout << "ID DEL CLIENTE: ";
    cin >> v.IDCliente;
    if(verificar_idCliente(v.IDCliente)==-1){
        cout << "INGRESE UN ID DE CLIENTE VALIDO"<<endl;
        exit(-1);
    }
    cout << "FECHA DE VIAJE: "<<endl;
    ///v.FechaViaje = cargar_fechav();
    cout << "DIA: ";
    cin >>  v.Viajedia;
    cout << "MES: ";
    cin >> v.Viajemes;
    cout << "ANIO: ";
    cin >> v.Viajeanio;
    if(verificar_FechaViaje(v.Viajedia,v.Viajemes,v.Viajeanio)==-1){
        cout << "INGRESE UNA FECHA VALIDA"<<endl;
        exit(-1);
    }
    cout <<"HORARIO DE SALIDA: ";
    cin >> v.HoraSalida;
    if(validar_HoraSalida(v.HoraSalida)==-1){
        cout << "INGRESE UNA HORA VALIDA"<<endl;
        exit(-1);
    }
    cout <<"KILOMETRAJE: ";
    cin >> v.Kilometraje;
    if(validar_Kilometraje(v.Kilometraje)==-1){
        cout << "INGRESE UN KILOMETRAJE VALIDO"<<endl;
        exit(-1);
    }
    cout <<"IMPORTE: ";
    cin >> v.Importe;
    if(validar_Importe(v.Importe)==-1){
        cout << "INGRESE UN IMPORTE VALIDO"<<endl;
        exit(-1);
    }
    cout <<"PATENTE: ";
    cin >> v.Patente;
    cout <<"CALIFICACION: ";
    cin >> v.Calificacion;
    if(validar_Calificacion(v.Calificacion)==-1){
        cout << "INGRESE UNA CALIFICACION VALIDA"<<endl;
        exit(-1);
    }
    v.Estado=true;
    return v;
}

int verificar_DNI(char *DNI){
    struct Chofer reg;
    FILE *p;
    p = fopen(Direccion,"rb");
    if(p==NULL){
        exit(-1);
    }
    while(fread(&reg,sizeof(Chofer),1,p)==1){
        if(strcmp(DNI,reg.DNI)==0){
            if(reg.Estado==1){
                fclose(p);
                return 1;
            }
            else{
                fclose(p);
                return -1;
            }
        }
    }
    fclose(p);
    return -1;
}

int verificar_idCliente(int id){
    struct Cliente reg;
    int ID_Real;
    ID_Real=id-1;
    FILE *p;
    p = fopen(DireccionC, "rb");
    if(p==NULL){
        exit(-1);
    }
    while(fread(&reg,sizeof(Cliente),1,p)==1){
        if(ID_Real==reg.IDCliente){
            if(reg.Estado==1){
                fclose(p);
                return 1;
            }
            else{
                fclose(p);
                return -1;
            }
        }
    }
    fclose(p);
    return -1;
}

int verificar_FechaViaje(int dia, int mes, int anio){
    Fecha f;
    f=obtener_fecha_sistema();
    /*if(dia<=f.dia && mes<=f.mes &&anio <= f.anio){
    return 1;
  }*///cout << f.dia<<"/"<<f.mes<<"/"<<f.anio;
  if(anio<=f.anio || anio==f.anio ||anio<f.anio){
    if(mes<=f.mes){
        if(dia<f.dia){
            return 1;
        }
    }
    else{
        if(anio<f.anio){
            return 1;
        }else{
            if(dia>f.dia && mes<f.mes){
                return 1;
            }
        }

    }

  }
    if(dia>f.dia && anio<f.anio){
        return 1;

    }
        //cout << endl <<dia << "/" << mes << "/" <<anio;
  return -1;
}
int validar_HoraSalida(int Hora){
    if(Hora >=0 && Hora<=23){
        return 1;
    }
    return -1;
}
int validar_Kilometraje(float Kilometraje){
    if(Kilometraje>0){
        return 1;
    }
    return -1;
}
int validar_Importe(float Importe){
    if(Importe>0){
        return 1;
    }
    return -1;
}
int validar_Calificacion(int Calificacion){
    if(Calificacion>=0 && Calificacion<=5){
        return 1;
    }
    return -1;
}

int cant_viajes(){
    int creg=1, cbytes;
      FILE *p;
      p = fopen(DireccionV, "rb");
      if (p == NULL){
        return 0;
      }
      fseek(p, 0, SEEK_END);
      cbytes=ftell(p);
      fclose(p);
      creg=cbytes/sizeof(viajes);
      return creg;
}


void mostrar_viaje(viajes reg){
    cout << "\n ID VIAJE         : " <<reg.IDViaje+1<<endl;
    cout << "\n DNI DEL CHOFER   : "<<reg.DNIChofer<<endl;
    cout << "\n ID DEL CLIENTE   : "<<reg.IDCliente<<endl;
    cout << "\n FECHA DE VIAJE   : ";
    //mostrar_fechaViaje(reg.FechaViaje);
    cout << reg.Viajedia<<"/"<<reg.Viajemes<<"/"<<reg.Viajeanio<<endl;
    cout <<"\n HORA DE SALIDA   : "<<reg.HoraSalida<<endl;
    cout <<"\n KILOMETRAJE      : "<<reg.Kilometraje<<endl;
    cout <<"\n IMPORTE          : "<<reg.Importe<<endl;
    cout <<"\n PATENTE          : "<<reg.Patente<<endl;
    cout <<"\n CALIFICACION     : "<<reg.Calificacion<<endl;
    cout <<"\n ESTADO           : "<<reg.Estado<<endl;
    cout <<" ==================================== " <<endl;

}

bool guardar_viaje(viajes reg){
  FILE *p;
  p = fopen(DireccionV, "ab");
  if (p == NULL){
    return false;
  }
  fwrite(&reg, sizeof(viajes), 1, p);
  fclose(p);
  return true;
}

viajes Leer_viaje(int pos){
      FILE *p;
      struct viajes reg;
      p = fopen(DireccionV, "rb");
      if (p == NULL){
        return reg;
      }
      fseek(p, pos * sizeof(viajes), 0);
      fread(&reg, sizeof(viajes), 1, p);
      fclose(p);
      return reg;
}

void Alta_Viaje(){
    struct viajes reg;
    reg = cargar_viajes();
    if(guardar_viaje(reg)==true){
        cout << "EL VIAJE SE HA GUARDADO CON EXITO..." <<endl;
    }
    else{
        cout << "EL VIAJE NO PUDO GUARDARSE..."<<endl;
    }
}

void Listar_viajes(){
      int i, tam;
      tam =cant_viajes();
      struct viajes reg;
      for(i=0; i<tam; i++){
            if(estado(reg,i)==-1){
            reg = Leer_viaje(i);
            mostrar_viaje(reg);
            }
        }
}

/*void Listar_viajes()
{
    int i=0;
    struct viajes reg;
    FILE *p;
    p= fopen(DireccionV,"rb");
    if(p==NULL){
        exit(1);
    }
    while(fread(&reg,sizeof(reg),1,p)==1){
        cout << "ID VIAJE         : " <<i<<endl;
        mostrar_viaje(reg);
        i++;
    }
    fclose(p);
}*/
int comparar_ID(int ID){
    viajes reg;
    FILE *p;
    p = fopen(DireccionV,"rb");
    if(p==NULL){
        return -1;
    }
    while(fread(&reg, sizeof(reg), 1,p)==1){
        if(ID == reg.IDViaje){
            fclose(p);
            return 1;
        }
    }
    fclose(p);
    return -1;
}

void Listar_viajexID(){
    struct viajes reg;
    int ID, ID_Real;
    cout << "INGRESE EL ID DE VIAJE: ";
    cin >> ID;
    ID_Real=ID-1;
    if(comparar_ID(ID_Real)==1){
        ///cout << "ESE REGISTRO ESTA EN LOS DATOS"<<endl;
        if(estado(reg,ID_Real)==-1){
        reg = Leer_viaje(ID_Real);
        mostrar_viaje(reg);
        }
        else{
            cout << "ESE ID ESTA DADO DE BAJA..."<<endl;
        }
    }
    else{
        cout << "NO EXISTE ESE ID..."<<endl;
        return;
    }
}

int estado(viajes reg, int pos){
      FILE *p;
      p = fopen(DireccionV, "rb");
      if (p == NULL){
        return 1;
      }
      fseek(p, pos * sizeof(viajes), 0);
      fread(&reg, sizeof(viajes), 1, p);
        if(reg.Estado==true){
            fclose(p);
            return -1;
        }
      fclose(p);
      return 1;
}

bool modificar(viajes reg, int pos){
      FILE *p;
      p = fopen(DireccionV, "rb+");
      if (p == NULL){
        exit(-1);
      }
      fseek(p, pos * sizeof(viajes), 0);
      fwrite(&reg, sizeof(viajes), 1, p);
      fclose(p);
      return false;
}

void baja_viajexID(){
    struct viajes reg;
    int ID,ID_Real;
    cout << "INGRESE EL ID DE VIAJE: ";
    cin >> ID;
    ID_Real=ID-1;
    if(comparar_ID(ID_Real)==1){

        if(estado(reg,ID_Real)!=1){
        reg = Leer_viaje(ID_Real);
        mostrar_viaje(reg);
        reg.Estado=false;
        if(modificar(reg,ID_Real)==false){
            cout << "DADO DE BAJA CON EXITO"<<endl;
        }
        }else{
            cout << "YA ESTA DADO DE BAJA..."<<endl;
        }

    }
    else{
        cout << "NO EXISTE ESE ID..."<<endl;
        return;
    }
}

void Menu_viajes(){
    system("color 4F");
    int op;
    while(true){
                        cout << "\t MENU VIAJES \t"<<endl;
                        cout << "-------------------------------"<<endl;
                        cout << "\n 1-NUEVO VIAJE"<<endl;
                        cout << "\n 2-LISTAR VIAJE X ID VIAJE"<<endl;
                        cout << "\n 3-LISTAR TODOS LOS VIAJES"<<endl;
                        cout << "\n 4-ELIMINAR VIAJE"<<endl;
                        cout << "-------------------------------"<<endl;
                        cout << "\n 0-VOLVER AL MENU PRINCIPAL"<<endl<<endl;
                        cout << "-------------------------------"<<endl;
                        cout << "INGRESE UNA OPCION: ";
                        cin >> op;

                        switch(op){
                            case 1:
                                system("cls");
                                ///ALTA VIAJE
                                Alta_Viaje();
                                system("pause > NUL");
                                system("cls");
                                break;
                            case 2:
                                system("cls");
                                ///LISTAR VIAJE X ID
                                Listar_viajexID();
                                system("pause > NUL");
                                system("cls");
                                break;
                            case 3:
                                system("cls");
                                ///LISTAR VIAJES
                                Listar_viajes();
                                system("pause > NUL");
                                system("cls");
                                break;
                            case 4:
                                system("cls");
                                ///ELIMINAR VIAJE
                                baja_viajexID();
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
                                cout << "OPCION NO VALIDA..."<<endl;
                                system("pause > NUL");
                                system("cls");
                                break;
                        }
            }
}


#endif // VIAJES_H_INCLUDED
