#ifndef CHOFERES_H_INCLUDED
#define CHOFERES_H_INCLUDED

/*struct FechaIngreso{
    int dia, mes, anio;
};
struct FechaVencimiento{
    int dia, mes, anio;
};

FechaIngreso cargar_fechaIngreso(){
    FechaIngreso f;
    cout << "DIA: ";
    cin >> f.dia;
    cout << "MES: ";
    cin >> f.mes;
    cout << "ANIO: ";
    cin >>f.anio;
    cout << endl;
    return f;
}

void mostrar_fechaIngreso(struct FechaIngreso Fi){
    cout << Fi.dia<<"/"<<Fi.mes<<"/"<<Fi.anio<<endl;
}

FechaVencimiento cargar_fechaVencimiento(){
    FechaVencimiento fech;
    cout << "DIA: ";
    cin >> fech.dia;
    cout << "MES: ";
    cin >> fech.mes;
    cout << "ANIO: ";
    cin >>fech.anio;
    return fech;
}

void mostrar_fechaVencimiento(struct FechaVencimiento Fv){
    cout << Fv.dia<<"/"<<Fv.mes<<"/"<<Fv.anio<<endl;
}*/

struct Chofer{
    char DNI[10];
    char Apellido[50];
    char Nombre[50];
    int INdia,INmes,INanio;
    char CUIT[20];
    int TipoRegistro;
    //FechaVencimiento Fvencimiento;
    int VNdia,VNmes,VNanio;
    char Telefono[10];
    bool Estado;

};
///CONSTANTES
const char Direccion[] = "Choferes.dat"; ///Choferes
///PROTOTIPOS
int validar_dni(char*);
int validar_cuit(char*);
void Alta_Chofer();
void modificar_Chofer();
int cant_registros();
int Buscar_Chofer(char);
Chofer cargar_chofer();
void mostrar_chofer(Chofer);
void Listar_Choferes();
void Listar_choferxDNI();
bool guardar_chofer(Chofer, int);
Chofer Leer_Chofer(int);
void baja_choferxDNI();
int comparar_cadena(char,char);
int validar_TipoRegistro(int);
int validar_FechaIngreso(int,int,int);
int validar_FechaVencimiento(int,int,int);
void Menu_chofer();

Chofer cargar_chofer(){
    Chofer c;
    cout << "\n DNI: ";
    cin >> c.DNI;
    if(cant_registros()==0){
    }
    else{
        if(validar_dni(c.DNI)==1){
            cout << "ESTE DNI YA EXISTE, INGRESE OTRO DNI"<<endl;
            system("pause > NUL");
            exit(-1);
        }
    }
    cout << endl;
    cout << "\n APELLIDO: ";
    cin >> c.Apellido;
    cout << endl;
    cout << "\n NOMBRE: ";
    cin >> c.Nombre;
    cout << endl;
    cout << "\n FECHA DE INGRESO: "<<endl;
    cin.ignore();
    cout << "DIA: ";
    cin >> c.INdia;
    cout << "MES: ";
    cin >> c.INmes;
    cout << "ANIO: ";
    cin >> c.INanio;
    if(validar_FechaIngreso(c.INdia,c.INmes,c.INanio)==-1){
            cout << "ESTA FECHA DE INGRESO NO ES VALIDA"<<endl;
            system("pause > NUL");
            exit(-1);
        }
    cout << endl;
    cout << "\n CUIT: ";
    cin >> c.CUIT;
    if(cant_registros()==0){
    }
    else{
            if(validar_cuit(c.CUIT)==1){
            cout << "ESTE CUIT YA EXISTE, INGRESE OTRO CUIT"<<endl;
            system("pause > NUL");
            exit(-1);
    }
    }
    cout << endl;
    cout << "\n TIPO DE REGISTRO(1,2,3): ";
    cin >> c.TipoRegistro;
    if(validar_TipoRegistro(c.TipoRegistro)==-1){
        cout << "ESTE TIPO DE REGISTRO NO EXISTE, VUELVA A INTENTARLO CON 1, 2 O 3"<<endl;
        system("pause > NUL");
        exit(-1);
    }
    cout << endl;
    cout << "\n FECHA DE VENCIMIENTO DE REGISTRO: "<<endl;
    ///c.Fvencimiento = cargar_fechaVencimiento();
    cin.ignore();
    cout << "DIA: ";
    cin >> c.VNdia;
    cout << "MES: ";
    cin >> c.VNmes;
    cout << "ANIO: ";
    cin >> c.VNanio;
    if(validar_FechaVencimiento(c.VNdia,c.VNmes,c.VNanio)==-1){
            cout << "ESTA FECHA DE VENCIMIENTO NO ES VALIDA"<<endl;
            system("pause > NUL");
            exit(-1);
        }
    cout << endl;
    cout << "\n TELEFONO(Puede no ingresarlo, no es obligatorio): ";
    ///cin >> c.Telefono;
    cin.ignore();
    cin.getline(c.Telefono,strlen(c.Telefono)+1);
    c.Estado=true;
    cout << endl;
    return c;
}


int validar_dni(char *dni){
    struct Chofer reg;
    FILE *p;
    p = fopen(Direccion,"rb");
    if(p==NULL){
        exit(1);
    }
    while(fread(&reg, sizeof(reg),1,p)==1){
        if(strcmp(dni,reg.DNI)==0){
            fclose(p);
            return 1;
        }
    }
    fclose(p);
    return -1;
}

int validar_cuit(char *cuit){
    struct Chofer reg;
    FILE *p;
    p = fopen(Direccion,"rb");
    if(p==NULL){
        exit(1);
    }
    while(fread(&reg, sizeof(reg),1,p)==1){
        if(strcmp(cuit,reg.CUIT)==0){
            fclose(p);
            return 1;
        }
    }
    fclose(p);
    return -1;
}

int validar_TipoRegistro(int TipoRegistro){
    if(TipoRegistro==1||TipoRegistro==2||TipoRegistro==3){
        return 1;
    }
    return -1;
}

int validar_FechaIngreso(int dia,int mes,int anio){
    Fecha f;
    f=obtener_fecha_sistema();
    /*if(dia<=f.dia && mes<=f.mes && anio<=2018){
    return 1;
  }*/
  if(anio<=f.anio){
    if(mes<=f.mes){
        if(dia<=f.dia){
            return 1;
        }
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
    if(dia>f.dia && anio<f.anio){
        return 1;

    }
  return -1;
}

int validar_FechaVencimiento(int vdia,int vmes,int vanio){
    Fecha fv;
    fv=obtener_fecha_sistema();
    /*if(vdia>fv.dia && vmes>fv.mes && vanio>=fv.anio){
        return -1;
    }*/
    /*if(vanio<=fv.anio){
    if(vmes<=fv.mes){
        if(vdia<=fv.dia){
            return -1;
        }
    }
  }*/if(vanio>fv.anio){
    if(vmes>fv.mes){
        if(vdia>=fv.dia){
            return 1;
        }
    }
  }
    if(vanio>fv.anio){
        return 1;
    }

    if(vdia>=fv.dia && vanio>fv.anio){
        return 1;

    }
  return -1;
}



bool guardar_chofer(Chofer registro, int pos){ ///esto recibe el registro recien ingresado y lo escribe y devuelve true, caso contrario hubo un problema
    FILE *p;
    if(pos >=0){
        p = fopen(Direccion,"rb+");
            if(p==NULL){
            return false;
            }
        fseek(p,pos*sizeof(Chofer),0);
    }
    else{
        p = fopen(Direccion,"ab");
        if(p==NULL){
            return false;
        }
    }
    fwrite(&registro,sizeof(Chofer),1,p);
    fclose(p);
    return true;
}

void Alta_Chofer(){
    Chofer c;
    c = cargar_chofer();
    if(guardar_chofer(c,-1)==true){ ///envio el registro que recien ingresaron a guardar_chofer para saber si se guardo bien, si devuelve true, el archivo se guardo.
       cout << "LOS DATOS DEL CHOFER SE HAN GUARDADO CON EXITO";
    }
    else{
        cout << "NO SE PUDIERON GUARDAR LOS DATOS";
    }
}

int cant_registros(){
    FILE *p;
    int cantBytes, cantReg;
    p = fopen(Direccion,"rb");
    if(p==NULL){
        return false;
    }
    fseek(p,0,2);
    cantBytes=ftell(p); ///mi cantidad de bytes de el primer registro.
    fclose(p);
    cantReg=cantBytes/sizeof(Chofer); ///la cantidad de registros es igual a la cantidad de bytes de un registro divido el total del archivo de registros.
    return cantReg;
}

void mostrar_chofer(Chofer c){
    cout << "\n DNI                             : "<<c.DNI<< endl;
    cout << "\n APELLIDO                        : "<<c.Apellido<<endl;
    cout << "\n NOMBRE                          : "<<c.Nombre<<endl;
    cout << "\n FECHA DE INGRESO                : ";
    //mostrar_fechaIngreso(c.Fingreso);
    cout << c.INdia<<"/"<< c.INmes<<"/"<< c.INanio<<endl;
    cout << endl;
    cout << "\n CUIT                            : "<<c.CUIT<<endl;
    cout << "\n TIPO DE REGISTRO                : "<<c.TipoRegistro<<endl;
    cout << "\n FECHA DE VENCIMIENTO DE REGISTRO: ";
    //mostrar_fechaVencimiento(c.Fvencimiento);
    cout << c.VNdia<<"/"<<c.VNmes <<"/"<< c.VNanio<<endl;
    cout << endl;
    cout << "\n TELEFONO                        : "<<c.Telefono<<endl;
    cout << endl<<endl;
    cout << " ================================================ "<< endl;

}

Chofer Leer_Chofer(int pos){
    Chofer reg;
    FILE *A;
    A = fopen(Direccion,"rb");
    if(A==NULL){
        return reg;
    }
    fseek(A,pos*sizeof(Chofer),0);
    fread(&reg,sizeof(Chofer),1,A);
    fclose(A);
    return reg;
}

/*void Listar_Choferes(){
    struct Chofer c;
    int reg=cant_registros();
    for(int i=0; i<reg;i++){
        c = Leer_Chofer(i);
        if(c.Estado==true){
        mostrar_chofer(c);
        cout << endl;
        }
    }

}*/
void Listar_Choferes(){
  system("cls");
  Chofer reg;
  FILE *p;
  p=fopen(Direccion, "rb");
  if (p == NULL){
    return;
  }
  while(fread(&reg, sizeof(Chofer), 1, p)==1){
    if(reg.Estado==true){
    mostrar_chofer(reg);
    }
  }
  fclose(p);
}

int comparar_cadena(char *DNI, char *DNI2){
    int valor=0;
    int i=-1;
    do{
        i++;
        if(DNI[i]==DNI2[i]){
            if(i>8){
            valor=0;
            }
        }
        else{
            valor=-1;
        }

    }while(DNI[i]!='\0');
    return valor;
}

int Buscar_Chofer(char *DNI){
    struct Chofer reg;
    int cont=0;
    FILE *p;
    p = fopen(Direccion, "rb");
    if(p==NULL){
        return -1;
    }
    while(fread(&reg, sizeof(struct Chofer),1,p)){
        if(comparar_cadena(DNI,reg.DNI)==0){
            fclose(p);
            return cont;
        }
        cont++;
    }
    fclose(p);
    return -1;
}


void Listar_choferxDNI(){
    Chofer c;
    int pos;
    char DNI[10]; ///no se puede utilizar int en DNI solo se puede utilizar el char
    cout << "INGRESE EL DNI DEL CHOFER QUE DESEA BUSCAR: ";
    cin >> DNI;
    pos=Buscar_Chofer(DNI);
    if(pos>=0){
        c= Leer_Chofer(pos);
        if(c.Estado==true){

        mostrar_chofer(c);
        }
        else{
            cout << "NO EXISTE EL CHOFER CON ESE DNI..."<<endl;
        }
    }
    else{
        cout << "NO EXISTE EL CHOFER CON ESE DNI..."<<endl;
    }
}

void modificar_Chofer(){
    int pos;
    char DNI[10];
    Chofer c;
    cout << "INGRESE EL DNI DEL CHOFER QUE DESEA MODIFICAR: ";
    cin >> DNI;

    pos=Buscar_Chofer(DNI);

    if(pos>=0){
        c = Leer_Chofer(pos);
        if(c.Estado==true){
        mostrar_chofer(c);
        cout << endl;
        cout << "INGRESE LA NUEVA FECHA DE VENCIMIENTO DE LA LICENCIA: ";
        ///c.Fvencimiento = cargar_fechaVencimiento();
        cout << "DIA: ";
        cin >> c.VNdia;
        cout << "MES: ";
        cin >> c.VNmes;
        cout << "ANIO: ";
        cin >> c.VNanio;
        cout << endl;
        if(validar_FechaVencimiento(c.VNdia,c.VNmes,c.VNanio)==-1){
            cout << "ESTA FECHA DE VENCIMIENTO NO ES VALIDA"<<endl;
            system("pause > NUL");
            exit(-1);
        }
        guardar_chofer(c,pos);
        cout << "SE HA ACTUALIZADO LA FECHA DE VENCIMIENTO DEL CHOFER CON EXITO!"<<endl;
        }
        else{
            cout << "ESE DNI NO EXISTE O A SIDO DADO DE BAJA..."<<endl;
        }

    }
    else{
        cout << "HUBO UN PROBLEMA, NO SE ENCONTRO EL CHOFER O NO EXISTE"<< endl;
    }

}

/**void baja_choferxDNI(){
    Chofer c;
    int pos;
    char DNI[10], op;
    cout << "INGRESE EL DNI DEL CHOFER QUE SE QUIERE DAR DE BAJA: ";
    cin >> DNI;

    pos=Buscar_Chofer(DNI);

    if(pos>=0){
        c=Leer_Chofer(pos);
        mostrar_chofer(c);
        cout << "ESTA SEGURO QUE QUIERE DARLO DE BAJA? (S/N): ";
        cin >> op;
        cout << endl;
        if(op=='s'||op=='S'){
            c.Estado=false;
            cout << "CHOFER DADO DE BAJA CON EXITO";
        }
        else{
            return;
        }
    }
}*/

void baja_choferxDNI(){
  system("cls");
  struct Chofer reg;
  int  pos;
  char DNI[10];
  cout << "INGRESE EL DNI QUE QUIERE DAR DE BAJA: ";
  cin >> DNI;
  pos = Buscar_Chofer(DNI);

  if (pos >= 0){
    reg = Leer_Chofer(pos);
    cout << endl;
    if(reg.Estado==true){
    mostrar_chofer(reg);
    reg.Estado=false;
    guardar_chofer(reg,pos);
    cout << "CHOFER DADO DE BAJA CON EXITO."<<endl;
  }else{
        cout << "EL CHOFER YA FUE DADO DE BAJA..."<<endl;
  }
  }
  else{
    cout << "NO EXISTE EL CHOFER." << endl;
  }
}

void Menu_chofer(){
    system("color 6F");
    system("cls");
    int op;
    while(true){
            cout << "\t MENU CHOFERES \t"<<endl;
            cout << "------------------------------"<<endl;
            cout << "\n 1-NUEVO CHOFER"<<endl;
            cout << "\n 2-MODIFICAR  CHOFER"<<endl;
            cout << "\n 3-LISTAR CHOFER POR DNI"<<endl;
            cout << "\n 4-LISTAR TODOS LOS CHOFERES"<<endl;
            cout << "\n 5-ELIMINAR CHOFER"<<endl;
            cout << "-----------------------------"<<endl;
            cout << "\n 0-VOLVER AL MENU PRINCIPAL"<<endl<<endl;
            cout << "-----------------------------"<<endl;
            cout << "INGRESE UNA OPCION: ";
            cin >> op;

            switch(op){
            case 1:
                    system("cls");
                    ///Nuevo cliente --> Alta_Cliente();
                    Alta_Chofer();
                    cout << endl;
                    system("pause > NUL");
                    system("cls");
                break;
            case 2:
                    ///Modificar cliente
                    system("cls");
                    modificar_Chofer();
                    cout << endl;
                    system("pause > NUL");
                    system("cls");
                break;
            case 3:
                    system("cls");
                    ///Listar cliente por codigo
                    Listar_choferxDNI();
                    system("pause > NUL");
                    system("cls");
                break;
            case 4:
                    system("cls");
                    ///Listar todos los clientes
                    Listar_Choferes();
                    cout << endl;
                    system("pause > NUL");
                    system("cls");
                break;
            case 5:
                    system("cls");
                    ///Eliminar Cliente
                    baja_choferxDNI();
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

#endif // CHOFERES_H_INCLUDED
