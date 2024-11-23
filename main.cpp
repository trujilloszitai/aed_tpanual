#include <cstring>
#include <iostream>
using namespace std;

// Estructuras - Entidades
struct Paciente {
  int id = 0;
  char nombre[50 + 1] = "";
  char apellido[50 + 1] = "";
  int edad = 0;
  char dni[8 + 1] = "";
  char telefono[20 + 1] = "";
};

struct Medico {
  int id = 0;
  char nombre[50 + 1] = "";
  char apellido[50 + 1] = "";
  int matricula = 0;
  int idEspecialidad = 0;
  int diasDeAtencion[7] = {0};
  int rangoHorario[2] = {0};
  int tiempoDeConsulta = 0;
};

struct Especialidad {
  int id = 0;
  char descripcion[50 + 1] = "";
};

struct Turno {
  int id = 0;
  int hora = 0;
  int dia = 0;
  int mes = 0;
  char estatus = 'P';
  int idPaciente = 0;
};

// Estructuras - Nodos
struct nodoLP {
  Paciente info;
  nodoLP *sgte;
};

struct nodoLM {
  Medico info;
  nodoLM *sgte;
};

struct nodoT {
  Turno info;
  nodoT *sgte;
};

struct infoT {
  int idMedico;
  nodoT *sublista;
};

struct nodoLT {
  infoT info;
  nodoLT *sgte;
};

void altaPaciente(nodoLP *&);
void pushPaciente(nodoLP *&, Paciente);
void altaMedico(nodoLM *&, nodoLT *&, char[][50 + 1]);
void altaTurno(nodoLT *&, nodoLM *, nodoLP *, char[][50 + 1]);
void pushMedico(nodoLM *&, Medico);
void pushTurno(nodoT *&, Turno);
void pushListaTurno(nodoLT *&, infoT);
infoT crearListaTurnos(int);
nodoLP *buscarPaciente(nodoLP *, char[]);
nodoLM *buscarMedico(nodoLM *, int);
nodoT *buscarListaTurnos(nodoLT *, int);
int turnoDisponible(nodoT *, Turno);
nodoLP *leerArchivoPacientes(FILE *);
nodoLM *leerArchivoMedicos(FILE *);
nodoLT *leerArchivoTurnos();
nodoT *insertarTurnoOrdenado(nodoT *, Turno);
void guardarListaTurnos(nodoLT *lista);
void insertarTurnoEnArchivo(Turno, int);
void cargarArchivoPacientes(FILE *, Paciente[]);
void cargarArchivoMedicos(FILE *, Medico[]);
void cargarArchivoTurnos(FILE *, infoT[]);
int elegirEspecialidad(char[][50 + 1], int);
nodoLM *filtrarMedicos(nodoLM *, int);
void obtenerDia(int, char[]);
void obtenerMes(int, char[]);
int elegirEspecialidad(char[][50 + 1]);
void actualizarStatus(nodoLT *&, int, int);
void actualizarStatus(nodoLT*&, int, int);
void turnosPendientes(nodoLT*, int, int);
void atencionesEfectivas(nodoLT*, int);

int main() {
  char especialidades[20][50 + 1] = {"Cardiologia",      "Pediatria",
                                     "Ginecologia",      "Dermatologia",
                                     "Neurologia",       "Oftalmologia",
                                     "Traumatologia",    "Urologia",
                                     "Oncologia",        "Psiquiatria",
                                     "Endocrinologia",   "Gastroenterologia",
                                     "Neumologia",       "Otorrinolaringologia",
                                     "Reumatologia",     "Cirugia General",
                                     "Medicina Interna", "Nefrologia",
                                     "Hematologia",      "Medicina Familiar"};

  FILE *fPacientes = fopen("pacientes.bin", "rb+");
  FILE *fMedicos = fopen("medicos.bin", "rb+");
  FILE *fTurnos = fopen("turnos.bin", "rb+");

  nodoLM *ListaDeM = leerArchivoMedicos(fMedicos);
  nodoLP *ListaDeP = leerArchivoPacientes(fPacientes);
  nodoLT *ListaLT = leerArchivoTurnos();

  int opcion = 0;
  while (true) {
    int accion = -1;
    if (opcion != 0) {
      switch (opcion) {
      case 1:
        cout << "Gestion de Pacientes - Seleccione una accion" << endl;
        cout << "Nuevo paciente (1)" << endl;
        cout << "Buscar paciente (2)" << endl;
        cout << "Listar pacientes (3)" << endl;
        break;
      case 2:
        cout << "Gestion de Medicos - Seleccione una accion" << endl;
        cout << "Nuevo medico (1)" << endl;
        cout << "Buscar medico (2)" << endl;
        cout << "Listar medicos (3)" << endl;
        cout << "Ver atenciones efectivas (4)" << endl;
        break;
      case 3:
        cout << "Gestion de Especialidades - Seleccione una accion" << endl;
        cout << "Listar especialidades (1)" << endl;
        cout << "Buscar especialidad (2)" << endl;
        break;
      case 4:
        cout << "Gestion de Turnos - Seleccione una accion" << endl;
        cout << "Nuevo turno (1)" << endl;
        cout << "Actualizar turno (2)" << endl;
        cout << "Turnos pendientes (3)" << endl;
        cout << "Ver cancelaciones (4)" << endl;
        break;
      }
      cout << "Volver (0)" << endl;
      cin >> accion;
      if (accion != 0) {
        switch (opcion) {
        case 1:
          // Pacientes
          switch (accion) {
          case 1:
            altaPaciente(ListaDeP);
            break;
          case 2:
            // buscar paciente
            break;
          case 3:
            // listar pacientes
            break;
          }
          break;
        case 2:
          // Medicos
          switch (accion) {
          case 1:
            altaMedico(ListaDeM, ListaLT, especialidades);
            break;
          case 2:
            break;
          case 3:
            break;
          case 4:
          //atenciones efectivas
            int mes;
            cout<<"Ingrese el mes del que quiere ver las atenciones efectivas del 1 al 12, siendo 1 el mes Enero: ";
            cin>>mes;
            atencionesEfectivas(ListaLT, mes);
            break;
          }
          break;
        case 3:
          // Especialidades
          switch (accion) {
          case 1:
            break;
          case 2:
            break;
          }
          break;
        case 4:
          // Turnos
          switch (accion) {
          case 1:
            altaTurno(ListaLT, ListaDeM, ListaDeP, especialidades);
            // nuevo turno
            break;
          case 2:
            // actualizar status
            int idMedico;
            int idTurno;
            cout << "Indique el id del medico: ";
            cin >> idMedico;
            cout << "Indique el id del turno: ";
            cin >> idTurno;
            actualizarStatus(ListaLT, idTurno, idMedico);
            break;
          case 3:
            // turnos pendientes
          int mesIng;
          int idMed;
          cout<<"Ingresar id del medico: ";
          cin>>idMed;
          cout<<"Ingresar mes del 1 al 12, siendo 1 el mes Enero: ";
          cin>>mesIng;
          turnosPendientes(ListaLT, idMed, mesIng);
            break;
          case 4:
            // ver cancelaciones
            break;
          }
          break;
        }
        accion = 0;
      }
    } else {
      cout << "Bienvenido al sistema de gestion de turnos de la clinica "
           << "\"Clinica Genial\"" << endl;
      cout << "Menu principal - Seleccione una opcion" << endl;
      cout << "Pacientes (1)" << endl;
      cout << "Medicos (2)" << endl;
      cout << "Especialidades (3)" << endl;
      cout << "Turnos (4)" << endl;
      cin >> opcion;
    }

    if (accion == 0 && opcion != 0)
      opcion = 0;
  }
  return 0;
}

// ARCHIVOS
nodoLP *leerArchivoPacientes(FILE *f) {
  Paciente p;
  nodoLP *lista = NULL;
  while (fread(&p, sizeof(Paciente), 1, f)) {
    pushPaciente(lista, p);
  }
  return lista;
}

nodoLM *leerArchivoMedicos(FILE *f) {
  Medico m;
  nodoLM *lista = NULL;
  while (fread(&m, sizeof(Medico), 1, f)) {
    pushMedico(lista, m);
  }
  return lista;
}

// nodoLT *leerArchivoTurnos(FILE *f) {
//   Turno t;
//   infoT i;
//   nodoLT *lp = NULL;
//   nodoT *ls = NULL;
//   int ultimoIdMedico = 1;
//   while (fread(&i, sizeof(infoT), 1, f)) {
//     t = i.sublista->info;
//     if (i.idMedico == ultimoIdMedico) {
//       pushTurno(ls, t);
//     } else {
//       ultimoIdMedico = i.idMedico;
//       pushListaTurno(lp, i);
//       ls = NULL;
//     }
//   }
//   return lp;
// }
nodoLT *leerArchivoTurnos() {
  // Leer la cantidad de nodos principales
  FILE* f = fopen("turnos.bin", "rb+");
  int N;
  fread(&N, sizeof(int), 1, f);
  nodoLT *lista = NULL;
  nodoLT *ultimo = NULL;
  for (int i = 0; i < N; i++) {
    // Crear un nuevo nodo principal
    nodoLT *nuevo = new nodoLT;
    nuevo->sgte = NULL;

    // Leer el idMedico
    fread(&nuevo->info.idMedico, sizeof(int), 1, f);

    // Leer la cantidad de turnos en la sublista
    int cantidadTurnos;
    fread(&cantidadTurnos, sizeof(int), 1, f);

    // Leer los turnos de la sublista
    nodoT *sublista = NULL;
    nodoT *ultimoSub = NULL;

    for (int j = 0; j < cantidadTurnos; j++) {
      // Crear un nuevo nodo de turno
      nodoT *nuevoTurno = new nodoT;
      nuevoTurno->sgte = NULL;

      // Leer los datos del turno
      fread(&nuevoTurno->info, sizeof(Turno), 1, f);

      // Insertar en la sublista
      if (sublista == NULL) {
        sublista = nuevoTurno;
      } else {
        ultimoSub->sgte = nuevoTurno;
      }
      ultimoSub = nuevoTurno;
    }

    nuevo->info.sublista = sublista;

    // Insertar en la lista principal
    if (lista == NULL) {
      lista = nuevo;
    } else {
      ultimo->sgte = nuevo;
    }
    ultimo = nuevo;
  }

  fclose(f);
  return lista;
}

void guardarListaTurnos(nodoLT *lista) {
  FILE *fp = fopen("turnos.bin", "rb+");
  // contar cantidad de nodos
  int cantidadNodos = 0;
  nodoLT *temp = lista;
  while (temp != NULL) {
    cantidadNodos++;
    temp = temp->sgte;
  }
  // escribir cantidad de nodos
  fwrite(&cantidadNodos, sizeof(int), 1, fp);
  // escribir nodos y sus sublistas
  temp = lista;
  while (temp != NULL) {
    // Escribir el idMedico
    fwrite(&temp->info.idMedico, sizeof(int), 1, fp);
    // Contar la cantidad de turnos en la sublista
    int cantidadTurnos = 0;
    nodoT *subtemp = temp->info.sublista;
    while (subtemp != NULL) {
      cantidadTurnos++;
      subtemp = subtemp->sgte;
    }
    // Escribir la cantidad de turnos
    fwrite(&cantidadTurnos, sizeof(int), 1, fp);
    // Escribir cada turno en la sublista
    subtemp = temp->info.sublista;
    while (subtemp != NULL) {
      fwrite(&subtemp->info, sizeof(Turno), 1, fp);
      subtemp = subtemp->sgte;
    }
    temp = temp->sgte;
  }
  fclose(fp);
}

// Insertar turno en la sublista
nodoT *insertarTurnoOrdenado(nodoT *sublista, Turno t) {
  nodoT *nuevo = new nodoT;
  nuevo->info = t;
  nuevo->sgte = NULL;
  if (sublista == NULL || sublista->info.id > t.id) {
    nuevo->sgte = sublista;
    return nuevo;
  }
  nodoT *actual = sublista;
  while (actual->sgte != NULL && actual->sgte->info.id < t.id) {
    actual = actual->sgte;
  }
  nuevo->sgte = actual->sgte;
  actual->sgte = nuevo;
  return sublista;
}

void insertarTurnoEnArchivo(Turno nuevoTurno, int idMedico) {
  // Leer la lista desde el archivo
  nodoLT *lista = leerArchivoTurnos();
  // Buscar si el médico ya existe
  nodoLT *actual = lista;
  nodoLT *anterior = NULL;
  while (actual != NULL && actual->info.idMedico < idMedico) {
    anterior = actual;
    actual = actual->sgte;
  }
  if (actual != NULL && actual->info.idMedico == idMedico) {
    // Insertar el turno en la sublista del médico
    nodoT *nuevaSublista = insertarTurnoOrdenado(actual->info.sublista, nuevoTurno);
    actual->info.sublista = nuevaSublista;
  } else {
    // Crear un nuevo nodo para la lista del médico
    nodoLT *nuevoNodo = new nodoLT;
    nuevoNodo->info.idMedico = idMedico;
    nuevoNodo->info.sublista = NULL;
    nuevoNodo->sgte = actual;
    // Insertar el turno en la sublista del nuevo médico
    nuevoNodo->info.sublista =
        insertarTurnoOrdenado(nuevoNodo->info.sublista, nuevoTurno);
    // Conectar el nuevo nodo en la lista principal
    if (anterior == NULL) {
      lista = nuevoNodo; // Es el nuevo primer nodo
    } else {
      anterior->sgte = nuevoNodo;
    }
  }

  // Actualizar el archivo
  guardarLista(lista);

  // Liberar memoria de la lista en memoria
  nodoLT *temp;
  while (lista != NULL) {
    temp = lista;
    lista = lista->sgte;
    nodoT *subtemp;
    while (temp->info.sublista != NULL) {
      subtemp = temp->info.sublista;
      temp->info.sublista = temp->info.sublista->sgte;
      delete subtemp;
    }
    delete temp;
  }
}

int cantRegPacientes(FILE *&f) {
  // preservar la posicion actual
  int posActual = ftell(f);
  fseek(f, 0, SEEK_END);
  int desplaz = ftell(f);
  int cantidad = desplaz / sizeof(Paciente);
  // vuelvo el puntero a donde estaba
  fseek(f, posActual, SEEK_SET);
  return cantidad;
}
int cantRegMedicos(FILE *&f) {
  // preservar la posicion actual
  int posActual = ftell(f);
  fseek(f, 0, SEEK_END);
  int desplaz = ftell(f);
  int cantidad = desplaz / sizeof(Medico);
  // vuelvo el puntero a donde estaba
  fseek(f, posActual, SEEK_SET);
  return cantidad;
}
int cantRegTurnos(FILE *&f) {
  // preservar la posicion actual
  int posActual = ftell(f);
  fseek(f, 0, SEEK_END);
  int desplaz = ftell(f);
  int cantidad = desplaz / sizeof(infoT);
  // vuelvo el puntero a donde estaba
  fseek(f, posActual, SEEK_SET);
  return cantidad;
}

// FUNCIONALIDADES
void altaPaciente(nodoLP *&lista) {
  Paciente nuevoPaciente;
  FILE *f = fopen("pacientes.bin", "rb+");
  int id = cantRegPacientes(f);
  cout << "Nuevo paciente (" << id << ")" << endl;
  cout << "Nombre: ";
  cin >> nuevoPaciente.nombre;
  cout << "Apellido: ";
  cin >> nuevoPaciente.apellido;
  cout << "Edad: ";
  cin >> nuevoPaciente.edad;
  cout << "DNI: ";
  cin >> nuevoPaciente.dni;
  cout << "Telefono: ";
  cin >> nuevoPaciente.telefono;
  pushPaciente(lista, nuevoPaciente);
  fseek(f, id * sizeof(Paciente), SEEK_SET);
  fwrite(&nuevoPaciente, sizeof(Paciente), 1, f);
  fclose(f);
}

// Retorna la posicion de la especialidad elegida
int elegirEspecialidad(char especialidades[][50 + 1], int N) {
  int i, idEspecialidad;
  i = idEspecialidad = 0;
  cout << "Especialidades disponibles" << endl;
  for (; i < N; i++) {
    cout << especialidades[i] << " (" << i + 1 << ") | ";
  }
  cout << endl;

  cout << "Elija la especialidad:";
  while (idEspecialidad < 1 || idEspecialidad > 20) {
    cin >> idEspecialidad;
  }
  return idEspecialidad;
}

int elegirMedico(nodoLM *lista) {
  nodoLM *listaM = lista;
  int idElegido = 0;
  int i = 0;

  if (listaM == NULL) {
    return -1;
  }
  cout << "Medicos disponibles" << endl;
  while (listaM != NULL) {
    Medico m = listaM->info;
    cout << m.apellido << ", " << m.nombre << " (" << m.id << ")" << endl;
    listaM = listaM->sgte;
    i++;
  }

  cout << "Elija el médico deseado: ";
  while (idElegido < 1 || idElegido > i + 1) {
    cin >> idElegido;
    if (idElegido < 1 || idElegido > i + 1)
      cout << "Ingrese un id valido" << endl;
  }
  return idElegido;
}

void altaMedico(nodoLM *&listaM, nodoLT *&listaLT,
                char especialidades[][50 + 1]) {
  Medico newMed;
  FILE *f = fopen("medicos.bin", "rb+");
  int id = cantRegMedicos(f) == 0 ? 1 : cantRegMedicos(f);
  cout << "Nuevo medico (" << id << ")" << endl;
  newMed.id = id;
  cout << "Nombre: ";
  cin >> newMed.nombre;
  cout << "Apellido: ";
  cin >> newMed.apellido;
  cout << "Numero de matricula: " << endl;
  cin >> newMed.matricula;
  newMed.idEspecialidad = elegirEspecialidad(especialidades, 20);
  cout << "Dias en los que atiende (puede seleccionar mas de 1): " << endl;
  int i = 0;
  int dia = 1;
  while (dia != 0 && i < 7) {
    cout << "Domingo (1)" << endl;
    cout << "Lunes (2)" << endl;
    cout << "Martes (3)" << endl;
    cout << "Miercoles (4)" << endl;
    cout << "Jueves (5)" << endl;
    cout << "Viernes (6)" << endl;
    cout << "Sabado (7)" << endl;
    cout << "Listo (0)" << endl;
    cin >> dia;
    newMed.diasDeAtencion[i] = dia;
    i++;
    if (dia == 0 && newMed.diasDeAtencion[0] == 0) {
      cout << "Ingrse al menos 1 dia: " << endl;
      i = 0;
      dia = 1;
    }
  }
  cout << "Ingrese HORA de comienzo de atencion (formato 24hs): " << endl;
  cin >> newMed.rangoHorario[0];
  cout << "Ingrese HORA de finalizacion de atencion: " << endl;
  cin >> newMed.rangoHorario[1];
  int idDurCons;
  cout << "Ingrese el tiempo que duran sus consultas: " << endl;
  cout << "15 minutos (1)" << endl;
  cout << "30 minutos (2)" << endl;
  cout << "45 minutos (3)" << endl;
  cout << "60 minutos (4)" << endl;
  cin >> idDurCons;
  if (idDurCons == 1) {
    newMed.tiempoDeConsulta = 15;
  } else if (idDurCons == 2) {
    newMed.tiempoDeConsulta = 30;
  } else if (idDurCons == 3) {
    newMed.tiempoDeConsulta = 45;
  } else if (idDurCons == 4) {
    newMed.tiempoDeConsulta = 60;
  }
  pushMedico(listaM, newMed);
  fseek(f, id * sizeof(Medico), SEEK_SET);
  fwrite(&newMed, sizeof(Medico), 1, f);
  infoT nuevaLista = crearListaTurnos(id);
  pushListaTurno(listaLT, nuevaLista);
  fclose(f);
}

void altaTurno(nodoLT *&listaLT, nodoLM *listaM, nodoLP *listaP,
               char especialidades[][50 + 1]) {
  int opcion = 0;
  char dniPaciente[8 + 1] = {""};
  int idEspecialidad;
  int idMedico;
  nodoLP *np = NULL;
  cout << "Turnos - Alta de Turno" << endl;
  while (opcion != 1 && opcion != 2) {
    cout << "¿El solicitante ya es paciente de la clinica?" << endl;
    cout << "Si (1)" << endl;
    cout << "No (2)" << endl;
    cin >> opcion;
  }
  if (opcion == 2) {
    cout << "Se procedera a crear un nuevo paciente" << endl;
    altaPaciente(listaP);
    strcpy(dniPaciente, listaP->info.dni);
    np = listaP;
  }
  if (opcion == 1) {
    while (np == NULL) {
      cout << "Ingrese el DNI del paciente: ";
      cin >> dniPaciente;
      np = buscarPaciente(listaP, dniPaciente);
      if (np == NULL)
        cout << "No se ha encontrado al paciente" << endl;
      else {
        Paciente p = np->info;
        idEspecialidad = elegirEspecialidad(especialidades, 20);
        nodoLM *medicosDeEspecialidad = filtrarMedicos(listaM, idEspecialidad);
        idMedico = elegirMedico(medicosDeEspecialidad);
        if (idMedico == -1) {
          cout << "No hay medicos disponibles en este momento" << endl;
        } else {
          nodoT *listaTurnos = buscarListaTurnos(listaLT, idMedico);
          Turno t;
          int disponibilidad;
          cout << "Solicitando turno..." << endl;
          cout << "Mes: ";
          cin >> t.mes;
          cout << "Dia: ";
          cin >> t.dia;
          cout << "Hora: ";
          cin >> t.hora;
          disponibilidad = turnoDisponible(listaTurnos, t);
          switch (disponibilidad) {
          case -1:
            cout << "Ya tiene un turno solicitado para esta fecha" << endl;
            break;
          case 0:
            cout << "No hay un turno disponible para esta fecha" << endl;
          case 1:
            nodoLM *nm = buscarMedico(listaM, idMedico);
            if (nm == NULL)
              cout << "Se ha producido un error inesperado. Intentelo mas "
                      "tarde";
            else {
              Medico m = nm->info;
              char dia[15 + 1];
              char mes[15 + 1];
              int confirmacion = 0;
              t.idPaciente = p.id;
              t.estatus = 'P';
              obtenerDia(t.dia, dia);
              obtenerMes(t.mes, mes);
              cout << "Turno disponible " << endl;
              cout << "Medico: " << m.apellido << ", " << m.nombre << endl;
              cout << dia << " " << t.dia << " de " << mes << " a las "
                   << t.hora << " hs" << endl;
              cout << "¿Desea confirmar el turno?" << endl;
              cout << "Confirmar (1)" << endl;
              cout << "Cancelar (2)" << endl;
              cout << "Ingrese una opción: ";
              while (confirmacion != 1 && confirmacion != 2) {
                cin >> confirmacion;
              }
              if (confirmacion == 1) {
                insertarTurnoEnArchivo(t, idMedico);
              }
            }
          }
        }
      }
    }
  }
}

void actualizarStatus(nodoLT *&listaLT, int idTurno, int IDmedico) {
  nodoLT *listaAux = listaLT;
  char newStat;
  cout << "Seleccione el nuevo status: " << endl;
  cout << "Pendiente (P) " << endl;
  cout << "Cancelado (C) " << endl;
  cout << "Atendido (A) " << endl;
  cout << "No atendido pero sin cancelar (X) " << endl;
  cin >> newStat;
  while (listaAux != NULL && listaAux->info.idMedico != IDmedico) {
    listaAux = listaAux->sgte;
  }
  if (listaAux != NULL && listaAux->info.idMedico == IDmedico) {
    while (listaAux->info.sublista != NULL &&
           listaAux->info.sublista->info.id != idTurno) {
      listaAux->info.sublista = listaAux->info.sublista->sgte;
    }
    if (listaAux->info.sublista != NULL &&
        listaAux->info.sublista->info.id == idTurno) {
      listaAux->info.sublista->info.estatus = newStat;
      cout << "El status se actualizo con exito" << endl;
    } else {
      cout << "El id de turno es erroneo o el turno no existe" << endl;
    }
  } else {
    cout << "El id de medico es erroneo" << endl;
  }
}

void turnosPendientes(nodoLT * listaLT, int idMedico, int mesL) {
  nodoLT * listaAux = listaLT;
  char mesAux[15+1];
  obtenerMes(mesL, mesAux);
  //listar dia hora mes status
  cout<<"Los turnos del mes " << mesAux << " son: "<<endl;
  while(listaAux != NULL && listaAux->info.idMedico != idMedico){
    listaAux = listaAux->sgte;
  }
  char diaAux[15+1];
  while(listaAux != NULL && listaAux->info.sublista != NULL){
    if(listaAux->info.sublista->info.mes == mesL){
      obtenerDia(listaAux->info.sublista->info.dia, diaAux);
      cout<<"Turno dia: "<< diaAux << " | Hora: "<< listaAux->info.sublista->info.hora << "hs | Estado: "<<listaAux->info.sublista->info.estatus<<endl;
    }
    listaAux->info.sublista = listaAux->info.sublista->sgte;
  }
}

void atencionesEfectivas(nodoLT * listaLT, int mesL) {
  nodoLT * listaAux = listaLT;
  char mesAux[15+1];
  obtenerMes(mesL, mesAux);
  int contAtEf = 0;
  while(listaAux != NULL){
    while(listaAux != NULL && listaAux->info.sublista != NULL){
        if(listaAux->info.sublista->info.mes == mesL){
          contAtEf++;
        }
      listaAux->info.sublista = listaAux->info.sublista->sgte;
    }
    listaAux = listaAux->sgte;
  }
  cout<<"La cantidad de atenciones efectivas durante el mes de "<< mesAux << " fueron " << contAtEf << endl;
}

void cancelacionesPorMes(nodoLM *listaM, nodoT *&listaT, nodoLP *&listaP,
                         int mes) {}
void cancelacionesPorMes(nodoLM *listaM, nodoLT *&listaT, nodoLP *&listaP, int mes) {

}

// FUNCIONES DE NODOS
void pushPaciente(nodoLP *&lista, Paciente info) {
  nodoLP *p = new nodoLP();
  p->info = info;
  p->sgte = lista;
  lista = p;
}
void pushMedico(nodoLM *&lista, Medico info) {
  nodoLM *m = new nodoLM();
  m->info = info;
  m->sgte = lista;
  lista = m;
}
void pushTurno(nodoT *&lista, Turno info) {
  nodoT *t = new nodoT();
  t->info = info;
  t->sgte = lista;
  lista = t;
}
void pushListaTurno(nodoLT *&lista, infoT info) {
  nodoLT *lt = new nodoLT();
  lt->info = info;
  lt->sgte = lista;
  lista = lt;
}

infoT crearListaTurnos(int idMedico) {
  infoT i;
  i.idMedico = idMedico;
  i.sublista = NULL;
  FILE *f = fopen("turnos.bin", "rb+");
  int id = cantRegTurnos(f);
  fseek(f, id * sizeof(infoT), SEEK_SET);
  fwrite(&i, sizeof(infoT), 1, f);
  fclose(f);
  return i;
}

nodoLP *buscarPaciente(nodoLP *lista, char dni[]) {
  nodoLP *listaP = lista;
  while (listaP != NULL && strcmp(dni, listaP->info.dni) != 0) {
    listaP = listaP->sgte;
  }
  return listaP;
}

nodoLM *buscarMedico(nodoLM *lista, int id) {
  nodoLM *listaM = lista;
  while (listaM != NULL && id != listaM->info.id) {
    listaM = listaM->sgte;
  }
  return listaM;
}

nodoT *buscarListaTurnos(nodoLT *lista, int idMedico) {
  nodoLT *listaT = lista;
  while (listaT != NULL && listaT->info.idMedico != idMedico) {
    listaT = listaT->sgte;
  }
  return listaT->info.sublista;
}

int turnoDisponible(nodoT *lista, Turno turno) {
  bool disponible = false;
  while (lista != NULL) {
    Turno t = lista->info;
    if (t.mes == turno.mes && t.dia == turno.dia && t.hora == turno.hora) {
      if (t.idPaciente == turno.idPaciente)
        return -1;
      return 0;
    }
    lista = lista->sgte;
  }
  return 1;
}

nodoLM *filtrarMedicos(nodoLM *lista, int idEspecialidad) {
  nodoLM *listaM = lista;
  nodoLM *especialistas = NULL;
  while (listaM != NULL) {
    Medico m = listaM->info;
    cout << m.id << endl;
    if (m.idEspecialidad == idEspecialidad)
      pushMedico(especialistas, m);
    listaM = listaM->sgte;
  }
  return especialistas;
}

void obtenerDia(int dia, char txt[]) {
  char dias[7][15 + 1] = {"Domingo", "Lunes",   "Martes", "Miercoles",
                          "Jueves",  "Viernes", "Sabado"};
  if (dia > 7 || dia < 1)
    dia = 1;
  strcpy(txt, dias[dia % 7] - 1);
}

void obtenerMes(int mes, char txt[]) {
  char meses[12][15 + 1] = {"Enero",      "Febrero", "Marzo",     "Abril",
                            "Mayo",       "Junio",   "Julio",     "Agosto",
                            "Septiembre", "Octubre", "Noviembre", "Diciembre"};
  if (mes > 12 || mes < 1)
    mes = 1;
  strcpy(txt, meses[mes - 1]);
}
