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
  float rangoHorario[2] = {0.0};
  int tiempoDeConsulta = 0;
};

struct Especialidad {
  int id = 0;
  char descripcion[50 + 1] = "";
};

struct Turno {
  int id = 0;
  float hora = 0;
  int dia = 0;
  int mes = 0;
  char estatus = 'P';
  int idPaciente = 0;
};
struct infoT {
  int idMedico;
  Turno turno;
};

// Estructuras - Nodos
struct nodoLP {
  Paciente info;
  nodoP *sgte;
};

struct nodoLM {
  Medico info;
  nodoM *sgte;
};

struct nodoT {
  infoT info;
  nodoT *sgte;
};

struct nodoLT {
  nodoT *info;
  nodoLT *sgte;
};

int altaPaciente(nodoP *&);
void pushPaciente(nodoP *&, Paciente);
void pushMedico(nodoM *&, Medico);
void pushTurno(nodoT *&, infoT);
void pushListaTurno(nodoLT *&, nodoT *);
nodoP *leerArchivoPacientes(FILE *);
nodoM *leerArchivoMedicos(FILE *);
nodoLT *leerArchivoTurnos(FILE *);
void cargarArchivoPacientes(FILE *, Paciente[]);
void cargarArchivoMedicos(FILE *, Medico[]);
void cargarArchivoTurnos(FILE *, infoT[]);
void generarPacientes(Paciente[], int);
void generarMedicos(Medico[], int);
void generarTurnos(infoT[], int);

int main() {
  // Paciente pacientes[100] = {};
  // Medico medicos[35] = {};
  // infoT turnos[100] = {};

  // generarPacientes(pacientes, 100);
  // generarMedicos(medicos, 35);
  // generarTurnos(turnos, 100);

  // FILE *fPacientes = fopen("pacientes.bin", "wb");
  // FILE *fMedicos = fopen("medicos.bin", "wb");
  // FILE *fTurnos = fopen("turnos.bin", "wb");
  // cargarArchivoPacientes(fPacientes, pacientes);
  // cargarArchivoMedicos(fMedicos, medicos);
  // cargarArchivoTurnos(fTurnos, turnos);
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
        cout << "Gestion de Turnos - Seleccione una accion" << endl;
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
            break;
          case 2:
            break;
          case 3:
            break;
          }
          break;
        case 2:
          // Medicos
          switch (accion) {
          case 1:
            break;
          case 2:
            break;
          case 3:
            break;
          case 4:
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
            break;
          case 2:
            break;
          case 3:
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
nodoP *leerArchivoPacientes(FILE *f) {
  Paciente p;
  nodoP *lista = NULL;
  while (fread(&p, sizeof(Paciente), 1, f)) {
    pushPaciente(lista, p);
  }
  return lista;
}

nodoM *leerArchivoMedicos(FILE *f) {
  Medico m;
  nodoM *lista = NULL;
  while (fread(&m, sizeof(Medico), 1, f)) {
    pushMedico(lista, m);
  }
  return lista;
}

nodoLT *leerArchivoTurnos(FILE *f) {
  Turno t;
  infoT i;
  nodoLT *lp = NULL;
  nodoT *ls = NULL;
  int ultimoIdMedico = 1;
  while (fread(&i, sizeof(infoT), 1, f)) {
    t = i.turno;
    if (i.idMedico == ultimoIdMedico) {
      pushTurno(ls, i);
    } else {
      ultimoIdMedico = i.idMedico;
      pushListaTurno(lp, ls);
      ls = NULL;
    }
  }
  return lp;
}
void cargarArchivoPacientes(FILE *f, Paciente pacientes[]) {
  for (int i = 0; i < 100; i++) {
    Paciente p = pacientes[i];
    fwrite(&p, sizeof(Paciente), 1, f);
  }
  fclose(f);
}
void cargarArchivoMedicos(FILE *f, Medico medicos[]) {
  for (int i = 0; i < 100; i++) {
    Medico m = medicos[i];
    fwrite(&m, sizeof(Medico), 1, f);
  }
  fclose(f);
}
void cargarArchivoTurnos(FILE *f, infoT turnos[]) {
  for (int i = 0; i < 100; i++) {
    infoT t = turnos[i];
    fwrite(&t, sizeof(infoT), 1, f);
  }
  fclose(f);
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
int altaPaciente(nodoP *&lista) {
  Paciente nuevoPaciente;
  FILE *f = fopen("pacientes.bin", "rb+");
  int id = cantRegPacientes(f) + 1;
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
  return id;
}

int altaTurno(nodoT *&lista) {}

int altaMedico(nodoM *&lista) {}

int actualizarEstatus(nodoM *listaM, nodoT *&listaT, int idMedico) {}

void turnosPendientes(nodoM *listaM, nodoT *&listaT, int idMedico, int mes) {}

void atencionesEfectivas(nodoM *listaM, nodoT *&listaT, int mes) {}

void cancelacionesPorMes(nodoM *listaM, nodoT *&listaT, nodoP *&listaP,
                         int mes) {}

// FUNCIONES DE NODOS
void pushPaciente(nodoP *&lista, Paciente info) {
  nodoP *p = new nodoP();
  p->info = info;
  p->sgte = lista;
  lista = p;
}
void pushMedico(nodoM *&lista, Medico info) {
  nodoM *m = new nodoM();
  m->info = info;
  m->sgte = lista;
  lista = m;
}
void pushTurno(nodoT *&lista, infoT info) {
  nodoT *t = new nodoT();
  t->info = info;
  t->sgte = lista;
  lista = t;
}
void pushListaTurno(nodoLT *&lista, nodoT *info) {
  nodoLT *lt = new nodoLT();
  lt->info = info;
  lt->sgte = lista;
  lista = lt;
}

// GENERACIÓN DE DATOS
// Función para generar un número de identificación (DNI) de 8 cifras


// Función para generar un número de teléfono aleatorio


// Función para generar un array de pacientes


    // Horario de atención: inicio y fin en rangos enteros o .5
    //medicos[i].rangoHorario[0] = horaInicio + minInicio;

   // int horaFin = horaInicio + 6; // Fin de horario: 4 horas más que inicio
   // float minFin = minInicio;
    //medicos[i].rangoHorario[1] = horaFin + minFin;

    //medicos[i].tiempoDeConsulta =

