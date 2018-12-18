#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

struct Fecha{
  int dia, mes, anio;
};
struct Hora{
  int hora, minuto, segundo;
};
struct FechaHora{
  Fecha f;
  Hora h;
};

FechaHora obtener_fechahora_sistema(){
  ///Necesario para obtener la fecha del sistema
  time_t tiempo;
  struct tm *tmPtr;
  tiempo = time(NULL);
  tmPtr = localtime(&tiempo);

  FechaHora fh;
  fh.f.dia = tmPtr->tm_mday;
  fh.f.mes = tmPtr->tm_mon+1;
  fh.f.anio = tmPtr->tm_year+1900;
  fh.h.hora = tmPtr->tm_hour;
  fh.h.minuto = tmPtr->tm_min;
  fh.h.segundo = tmPtr->tm_sec;
  return fh;
}

Fecha obtener_fecha_sistema(){
  return obtener_fechahora_sistema().f;
}
Hora obtener_hora_sistema(){
  return obtener_fechahora_sistema().h;
}

void mostrar_fecha(Fecha f){
  cout << f.dia << "/" << f.mes << "/" << f.anio;
}
void mostrar_hora(Hora h){
  cout << h.hora << ":" << h.minuto << ":" << h.segundo;
}
void mostrar_fechahora(FechaHora fh){
  mostrar_fecha(fh.f);
  cout << " ";
  mostrar_hora(fh.h);
}

#endif // FECHA_H_INCLUDED
