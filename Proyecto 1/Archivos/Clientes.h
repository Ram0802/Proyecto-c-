#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

/*struct Fecha_cliente{
    int Dia;
    int Mes;
    int Anio;
};
Fecha_cliente cargar_fecha(){  ///siempre al hacer esto de que ingresen en la estructura para nombrar esta funcion es.
    ///Nombre de la 'struct', despues, el nombre de la funcion.
    Fecha_cliente fech; ///nombro la estructura y le doy como un apodo.
    cout << "Dia: ";
    cin >> fech.Dia;
    cout << "Mes: ";
    cin >> fech.Mes;
    cout << "Anio: ";
    cin >> fech.Anio;
    return fech; ///Y tiene que retornar el apodo, que luego ira como la estructura.
}
void mostrar_Fecha(struct Fecha_cliente f){ ///aca apode a la struct 'Fecha' como f para escribir rapido.
    cout << "FECHA DE NACIMIENTO: " <<f.Dia << "/" << f.Mes << "/" <<f.Anio<<endl;
}*/

struct Cliente{
    int IDCliente; ///despues darle el valor que tendria que llevar y aumentarlo 1 por cada registro de cliente.
    char Apellido[50];
    char Nombre[50];
    ///Fecha_cliente fnac;
    int DiaN,MesN,AnioN;
    char Genero[15];
    bool Estado; ///Para saber si esta activo o no.
};

const char DireccionC[] = "Clientes.dat"; ///Clientes
int comparar_ID_Cliente(int);
bool modificarEstado_Cliente(Cliente,int);
int estado_Cliente(Cliente,int);
void Alta_Cliente();
void modificar_Cliente();
void baja_clienteXid();
int cant_registros_Cliente();
Cliente cargar_cliente();
void mostrar_cliente(Cliente);
void Listar_Clientes();
void Listar_clienteXid();
bool guardar_cliente(Cliente);
Cliente Leer_Cliente(int);
int verificar_FechaNac(int,int,int);
void Menu_Cliente();


int cant_registros_Cliente(){
  int cantReg=0, cantBytes=0;
  FILE *p;
  p = fopen(DireccionC, "rb");
  if (p == NULL){
    return 0;
  }
  fseek(p, 0, SEEK_END);
  cantBytes = ftell(p);
  fclose(p);
  cantReg = cantBytes/sizeof(Cliente);
  return cantReg;
}

Cliente cargar_cliente(){ ///Para guardar un registro
    Cliente c;
    ///cout << "\n ID: "; <--- No es necesario.
    c.IDCliente=cant_registros_Cliente();
    cout << "\n APELLIDO: ";
    cin >> c.Apellido;  ///usar cin.getline y limpiar el buffer con la funcion guardada(parecida a fflush(stdin).
    cout << "\n NOMBRE: ";
    cin >> c.Nombre;
    cout << "\n FECHA DE NACIMIENTO: "<< endl;
    ///c.fnac = cargar_fecha();
    cout << "Dia: ";
    cin >> c.DiaN;
    cout << "Mes: ";
    cin >> c.MesN;
    cout << "Anio: ";
    cin >> c.AnioN;
    if(verificar_FechaNac(c.DiaN,c.MesN,c.AnioN)==-1){
            cout << "ESTA FECHA DE NACIMIENTO NO ES VALIDA POR SER MENOR DE EDAD"<<endl;
            system("pause > NUL");
            exit(-1);
        }
    cout << "\n GENERO: ";
    cin >> c.Genero;
    cout << endl;
    c.Estado=true;
    return c;
}

int verificar_FechaNac(int Dia,int Mes,int Anio){ ///SI RETORNA -1 NO ES VALIDO.
    struct Fecha f;
    f=obtener_fecha_sistema();
    if((Dia>=f.dia&&Mes>=f.mes&&Anio>=f.anio)){
        return -1;
    }
    if((Anio>2000)){
        return -1;
    }
    return 1;
}

bool guardar_cliente(Cliente reg){
  FILE *p;
  p = fopen(DireccionC, "ab");
  if (p == NULL){
    return false;
  }
  fwrite(&reg, sizeof(Cliente), 1, p);
  fclose(p);
  return true;
}

void Alta_Cliente(){ ///AÑADIR CLIENTES UNO POR UNO.
    system("cls"); /// Uso el system cls por que es el que voy a mostrar en pantalla, por lo tanto quiero que me borre lo anterior.
    struct Cliente Caux;
    Caux=cargar_cliente();
    if(guardar_cliente(Caux)==true){
        cout << "EL CLIENTE SE HA GUARDADO CON EXITO"<< endl;
    }
    else{
        cout << "HUBO UN ERROR AL GUARDAR EL CLIENTE"<< endl;
    }
}
///Para un "modificar_cliente"-- el fseek(p,pos*sizeof(Cliente),SEEK_SET); .
///esta futura funcion neceitaria una pos y la estructura y cuando use el fopen que este en modo "rb+".

///Baja logica, va ser que cuando un registro guardado con un bool lo apague(false) y si esta apagado no lo muetsro.
void mostrar_cliente(Cliente c){ ///MUESTRA UN CLIENTE.
    cout << "\n ID                 : "<<c.IDCliente+1<<endl;
    cout << "\n APELLIDO           : "<<c.Apellido<<endl;
    cout << "\n NOMBRE             : "<<c.Nombre<<endl;
    cout << "\n FECHA DE NACIMIENTO: " <<c.DiaN << "/" << c.MesN << "/" <<c.AnioN<<endl;
    cout << "\n GENERO             : "<<c.Genero<<endl;
    cout << " =========================== "<<endl<<endl;
    //cout << "ESTADO   : "<<c.Estado<<endl<<endl;

}

Cliente Leer_Cliente(int pos){ ///LEE EL CLIENTE EN TAL POSICION, RECIBIENDO LA POSICION.
  struct Cliente c;
  FILE *p;
  p = fopen(DireccionC, "rb");
  if (p==NULL){
    return c;
  }
  fseek(p, sizeof(Cliente)*pos, 0);
  fread(&c, sizeof(Cliente), 1, p);
  fclose(p);
  return c;
}

void Listar_Clientes(){
  system("cls");
  Cliente reg;
  FILE *p;
  p=fopen(DireccionC, "rb");
  if (p == NULL){
    return;
  }
  while(fread(&reg, sizeof(Cliente), 1, p)==1){
    if(reg.Estado==true){
    mostrar_cliente(reg);
    }
  }
  fclose(p);
}

int estado_Cliente(Cliente reg, int pos){ ///VERIFICA SI EL ESTADO DEL REGISTRO EN TAL POSICION ES VERDADERO O SI ES FALSO.
      FILE *p;
      p = fopen(DireccionC, "rb");
      if (p == NULL){
        return 1;
      }
      fseek(p, pos * sizeof(Cliente), 0);
      fread(&reg, sizeof(Cliente), 1, p);
        if(reg.Estado==true){
            fclose(p);
            return -1;
        }
      fclose(p);
      return 1;
}

bool modificarEstado_Cliente(Cliente reg, int pos){
      FILE *p;
      p = fopen(DireccionC, "rb+");
      if (p == NULL){
        exit(-1);
      }
      fseek(p, pos * sizeof(Cliente), 0);
      fwrite(&reg, sizeof(Cliente), 1, p);
      fclose(p);
      return false;
}

void Listar_clienteXid(){
  system("cls");
  Cliente Reg;
  int ID,comp=0,ID_Real;
  cout << "INGRESE EL ID DEL CLIENTE QUE DESEA BUSCAR: ";
  cin >> ID;
  ID_Real=ID-1;
  system("cls");
  comp = comparar_ID_Cliente(ID_Real);
  if (comp==1){
        if(estado_Cliente(Reg,ID_Real)==-1){
            Reg = Leer_Cliente(ID_Real);
            mostrar_cliente(Reg);
        }
        else{
            cout << "EL CLIENTE ESTA DADO DE BAJA." << endl;
        }
  }
  else{
    cout << "NO EXISTE EL CLIENTE." << endl;
  }
}

int comparar_ID_Cliente(int ID){
    Cliente reg;
    FILE *p;
    p = fopen(DireccionC,"rb");
    if(p==NULL){
        return -1;
    }
    while(fread(&reg, sizeof(reg), 1,p)==1){
        if(reg.IDCliente==ID){
            fclose(p);
            return 1;
        }
    }
    fclose(p);
    return -1;
}

void baja_clienteXid(){
  system("cls");
  struct Cliente c;
  int ID, ID_Real;
  cout << "ID: ";
  cin >> ID;
  ID_Real=ID-1;
  if (comparar_ID_Cliente(ID_Real)==1){
    if(estado_Cliente(c,ID_Real)==-1){
    c = Leer_Cliente(ID_Real);
    cout << endl;
    mostrar_cliente(c);
    c.Estado=false;
    modificarEstado_Cliente(c,ID_Real);
    cout << "CLIENTE DADO DE BAJA CON EXITO."<<endl;
    }
    else{
        cout << "EL CLIENTE ESTA DADO DE BAJA." << endl;
    }
  }
  else{
    cout << "NO EXISTE EL CLIENTE." << endl;
  }
}

void modificar_Cliente(){
  int ID,ID_Real;
  Cliente c;
  cout << "ID: ";
  cin >> ID;
  ID_Real=ID-1;
  if (comparar_ID_Cliente(ID_Real)==1){
    if(estado_Cliente(c,ID_Real)==-1){
    c = Leer_Cliente(ID_Real);
    cout << endl;
    mostrar_cliente(c);
    cout << endl;
    cout << "NUEVA FECHA DE NACIMIENTO: ";
    ///c.fnac = cargar_fecha();
    cout << "Dia: ";
    cin >> c.DiaN;
    cout << "Mes: ";
    cin >> c.MesN;
    cout << "Anio: ";
    cin >> c.AnioN;
    modificarEstado_Cliente(c, ID_Real);
    cout << endl << "FECHA DE NACIMIENTO DEL CLIENTE GUARDADO." << endl;
    }
    else{
        cout << endl << "EL CLIENTE ESTA DADO DE BAJA." << endl;
    }
  }
  else{
    cout << endl << "NO EXISTE EL CLIENTE." << endl;
  }
}

void Menu_cliente(){
    system("color 1F");
    system("cls");
    int op;
    while(true){
            cout << "\t MENU CLIENTES \t"<<endl;
            cout << "------------------------------"<<endl;
            cout << "\n 1-NUEVO CLIENTE"<<endl;
            cout << "\n 2-MODIFICAR  CLIENTE"<<endl;
            cout << "\n 3-LISTAR CLIENTE POR CODIGO"<<endl;
            cout << "\n 4-LISTAR TODOS LOS CLIENTES"<<endl;
            cout << "\n 5-ELIMINAR CLIENTE"<<endl;
            cout << "-----------------------------"<<endl;
            cout << "\n 0-VOLVER AL MENU PRINCIPAL"<<endl<<endl;
            cout << "-----------------------------"<<endl;
            cout << "INGRESE UNA OPCION: ";
            cin >> op;

            switch(op){
            case 1:
                    system("cls");
                    ///Nuevo cliente --> Alta_Cliente();
                    Alta_Cliente();
                    cout << endl;
                    system("pause > NUL");
                    system("cls");
                break;
            case 2:
                    ///Modificar cliente
                    system("cls");
                    modificar_Cliente();
                    cout << endl;
                    system("pause > NUL");
                    system("cls");
                break;
            case 3:
                    system("cls");
                    ///Listar cliente por codigo
                    Listar_clienteXid();
                    system("pause > NUL");
                    system("cls");
                break;
            case 4:
                    system("cls");
                    ///Listar todos los clientes
                    Listar_Clientes();
                    cout << endl;
                    system("pause > NUL");
                    system("cls");
                break;
            case 5:
                    system("cls");
                    ///Eliminar Cliente
                    baja_clienteXid();
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
                system("pause");
                system("cls");
                continue;
            }


    }
}

#endif // CLIENTES_H_INCLUDED
