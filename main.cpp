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
  char descripción[50 + 1] = "";
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
struct nodoP {
  Paciente info;
  nodoP *sgte;
};

struct nodoM {
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

void menu(int &);
void menuPacientes();
void menuMedicos();
void menuEspecialidades();
void menuTurnos();
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
  int opcion;
  while (true)
    menu(opcion);

  return 0;
}

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
void menu(int &opcion) {
  int accion = -1;
  switch (opcion) {
  case 1:
    cout << "Gestión de Pacientes - Seleccione una acción" << endl;
    cout << "Nuevo paciente (1)" << endl;
    cout << "Buscar paciente (2)" << endl;
    cout << "Listar pacientes (3)" << endl;
    cout << "Volver (0)" << endl;
    cin >> accion;
    break;
  case 2:
    cout << "Gestión de Médicos - Seleccione una acción" << endl;
    cout << "Nuevo médico (1)" << endl;
    cout << "Buscar médico (2)" << endl;
    cout << "Listar médicos (3)" << endl;
    cout << "Ver atenciones efectivas (4)" << endl;
    cout << "Volver (0)" << endl;
    cin >> accion;
    break;
  case 3:
    cout << "Gestión de Turnos - Seleccione una acción" << endl;
    cout << "Listar especialidades (1)" << endl;
    cout << "Buscar especialidad (2)" << endl;
    cout << "Volver (0)" << endl;
    cin >> accion;
    break;
  case 4:
    cout << "Gestión de Turnos - Seleccione una acción" << endl;
    cout << "Nuevo turno (1)" << endl;
    cout << "Actualizar turno (2)" << endl;
    cout << "Turnos pendientes (3)" << endl;
    cout << "Ver cancelaciones (4)" << endl;
    cout << "Volver (0)" << endl;
    cin >> accion;
    break;
  default:
    cout << "Bienvenido al sistema de gestión de turnos de la clínica "
         << "\"Clínica Genial\"" << endl;
    cout << "Menú principal - Seleccione una opción" << endl;
    cout << "Pacientes (1)" << endl;
    cout << "Médicos (2)" << endl;
    cout << "Especialidades (3)" << endl;
    cout << "Turnos (4)" << endl;
    cin >> opcion;
    break;
  }
  if(accion == 0 && opcion != 0) opcion = 0;
}
void menuPacientes() {
  int accion;
  while (accion != 0) {
    cout << "Gestión de Pacientes - Seleccione una acción" << endl;
    cout << "Nuevo paciente (1)" << endl;
    cout << "Buscar paciente (2)" << endl;
    cout << "Listar pacientes (3)" << endl;
    cout << "Volver (0)" << endl;
    cin >> accion;
  }
}

void menuMedicos() {
  int accion;
  while (accion != 0) {
    cout << "Gestión de Médicos - Seleccione una acción" << endl;
    cout << "Nuevo médico (1)" << endl;
    cout << "Buscar médico (2)" << endl;
    cout << "Listar médicos (3)" << endl;
    cout << "Ver atenciones efectivas (4)" << endl;
    cout << "Volver (0)" << endl;
    cin >> accion;
  }
}

void menuEspecialidades() {
  int accion;
  while (accion != 0) {
    cout << "Gestión de Turnos - Seleccione una acción" << endl;
    cout << "Listar especialidades (1)" << endl;
    cout << "Buscar especialidad (2)" << endl;
    cout << "Volver (0)" << endl;
    cin >> accion;
  }
}

void menuTurnos() {
  int accion;
  while (accion != 0) {
    cout << "Gestión de Turnos - Seleccione una acción" << endl;
    cout << "Nuevo turno (1)" << endl;
    cout << "Actualizar turno (2)" << endl;
    cout << "Turnos pendientes (3)" << endl;
    cout << "Ver cancelaciones (4)" << endl;
    cout << "Volver (0)" << endl;
    cin >> accion;
  }
}

int altaPaciente(nodoP *&lista) {}

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
void generarDNI(char *dni) {
  int numDNI = 1 + rand() % 90000000;
  snprintf(dni, 9, "%08d",
           numDNI); // Convertir el número en una cadena de 8 caracteres
}

// Función para generar un número de teléfono aleatorio
void generarTelefono(char *telefono) {
  snprintf(telefono, 21, "+54 9 %02d-%04d-%04d", rand() % 100, rand() % 10000,
           rand() % 10000);
}

// Función para generar un array de pacientes
void generarPacientes(Paciente pacientes[], int N) {
  const char *nombres[] = {"Juan",  "Ana",  "Pedro", "Lucia",  "Carlos",
                           "Maria", "Luis", "Elena", "Miguel", "Laura"};
  const char *apellidos[] = {"Perez", "Gomez",    "Fernandez", "Rodriguez",
                             "Luna",  "Martinez", "Sanchez",   "Diaz",
                             "Silva", "Morales"};
  int numNombres = sizeof(nombres) / sizeof(nombres[0]);
  int numApellidos = sizeof(apellidos) / sizeof(apellidos[0]);

  for (int i = 0; i < N; i++) {
    pacientes[i].id = i + 1; // Asignar un ID secuencial al paciente
    strncpy(pacientes[i].nombre, nombres[rand() % numNombres], 50);
    strncpy(pacientes[i].apellido, apellidos[rand() % numApellidos], 50);
    pacientes[i].edad = 18 + rand() % 83;   // Edad entre 18 y 100 años
    generarDNI(pacientes[i].dni);           // Generar DNI de 8 cifras
    generarTelefono(pacientes[i].telefono); // Generar número de teléfono
  }
}
void generarMedicos(Medico medicos[], int N) {
  for (int i = 0; i < N; i++) {
    medicos[i].id = i + 1;
    snprintf(medicos[i].nombre, sizeof(medicos[i].nombre), "Nombre%d", i + 1);
    snprintf(medicos[i].apellido, sizeof(medicos[i].apellido), "Apellido%d",
             i + 1);
    medicos[i].matricula = 10000 + rand() % 90000; // Matricula de 5 a 6 cifras
    medicos[i].idEspecialidad = 1 + rand() % 20;   // Especialidad entre 1 y 20

    // Asignación de días de atención
    for (int j = 0; j < 7; j++) {
      medicos[i].diasDeAtencion[j] = rand() % 2; // 1 si atiende el día, 0 si no
    }

    // Horario de atención: inicio y fin en rangos enteros o .5
    int horaInicio = 8 + rand() % 5; // entre 8 y 12
    float minInicio = (rand() % 2) == 0 ? 0.0 : 0.5;
    medicos[i].rangoHorario[0] = horaInicio + minInicio;

    int horaFin = horaInicio + 6; // Fin de horario: 4 horas más que inicio
    float minFin = minInicio;
    medicos[i].rangoHorario[1] = horaFin + minFin;

    medicos[i].tiempoDeConsulta =
        15 + (rand() % 4) * 5; // entre 15, 20, 25 o 30 minutos
  }
}
void generarTurnos(infoT turnos[], int N) {
  srand(time(0)); // Semilla para números aleatorios

  for (int i = 0; i < N; i++) {
    infoT nuevoTurno;
    nuevoTurno.idMedico = 1 + rand() % 35; // ID del médico entre 1 y 35
    nuevoTurno.turno.id = i + 1;           // ID secuencial para el turno
    // Genera una hora aleatoria en formato 24 horas con intervalos de 15
    // minutos
    int horaBase = 8 + rand() % 10;  // Hora base entre 8 y 17
    float min = (rand() % 4) * 0.25; // Minuto en .0, .25, .50 o .75
    nuevoTurno.turno.hora = horaBase + min;
    nuevoTurno.turno.dia = 1 + rand() % 30; // Día entre 1 y 30
    nuevoTurno.turno.mes = 1 + rand() % 12; // Mes entre 1 y 12

    // Asignación aleatoria de estatus
    char estatuses[] = {'P', 'A', 'C'};
    nuevoTurno.turno.estatus = estatuses[rand() % 3];

    nuevoTurno.turno.idPaciente =
        1 + rand() % 100; // ID del paciente entre 1 y 100

    turnos[i] = nuevoTurno; // Añadir el turno al vector
  }
}
