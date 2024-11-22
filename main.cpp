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
void pushMedico(nodoLM *&, Medico);
void pushTurno(nodoT *&, Turno);
void pushListaTurno(nodoLT *&, infoT);
nodoLP *buscarPaciente(nodoLP *, char[]);
nodoLP *leerArchivoPacientes(FILE *);
nodoLM *leerArchivoMedicos(FILE *);
nodoLT *leerArchivoTurnos(FILE *);
void cargarArchivoPacientes(FILE *, Paciente[]);
void cargarArchivoMedicos(FILE *, Medico[]);
void cargarArchivoTurnos(FILE *, infoT[]);
int elegirEspecialidad(char[][50 + 1]);

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

  FILE *fPacientes = fopen("pacientes.bin", "rb");
  FILE *fMedicos = fopen("medicos.bin", "rb");
  FILE *fTurnos = fopen("turnos.bin", "rb");

  nodoLM *ListaDeM = leerArchivoMedicos(fMedicos);
  nodoLP *ListaDeP = leerArchivoPacientes(fPacientes);
  nodoLT *ListaDeListasT = leerArchivoTurnos(fTurnos);

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
            altaPaciente(ListaDeP);
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

nodoLT *leerArchivoTurnos(FILE *f) {
  Turno t;
  infoT i;
  nodoLT *lp = NULL;
  nodoT *ls = NULL;
  int ultimoIdMedico = 1;
  while (fread(&i, sizeof(infoT), 1, f)) {
    t = i.sublista->info;
    if (i.idMedico == ultimoIdMedico) {
      pushTurno(ls, t);
    } else {
      ultimoIdMedico = i.idMedico;
      pushListaTurno(lp, i);
      ls = NULL;
    }
  }
  return lp;
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
}

// Retorna la posicion de la especialidad elegida
int elegirEspecialidad(char especialidades[][50 + 1]) {
  int i, idEspecialidad;
  i = idEspecialidad = 0;
  cout << "Especialidades disponibles" << endl;
  for (i; i < 5; i++) {
    cout << especialidades[i] << " (" << i + 1 << ") | ";
    cout << especialidades[i + 5] << " (" << i + 5 + 1 << ") | ";
    cout << especialidades[i + 10] << " (" << i + 10 + 1 << ") | ";
    cout << especialidades[i + 15] << " (" << i + 15 + 1 << ") | " << endl;
  }

  while(idEspecialidad < 1 || idEspecialidad > 20) {
      cout << "Elija la especialidad:";
      cin >> idEspecialidad;
  }

  return idEspecialidad;
}

void altaTurno(nodoLT *&listaT, nodoLP *&listaP, char especialidades[][50+1]) {
  int opcion;
  char dniPaciente[8 + 1] = {""};
  int idEspecialidad;
  nodoLP *p = NULL;
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
    p = listaP;
  }
  if (opcion == 1) {
    while (p == NULL) {
      cout << "Ingrese el DNI del paciente: ";
      cin >> dniPaciente;
      p = buscarPaciente(listaP, dniPaciente);
      if (p == NULL)
        cout << "No se ha encontrado al paciente" << endl;
    }
  }

  idEspecialidad = elegirEspecialidad(especialidades);
}

void altaMedico(nodoLM *&lista) {}

void actualizarEstatus(nodoLM *listaM, nodoT *&listaT, int idMedico) {}

void turnosPendientes(nodoLM *listaM, nodoT *&listaT, int idMedico, int mes) {}

void atencionesEfectivas(nodoLM *listaM, nodoT *&listaT, int mes) {}

void cancelacionesPorMes(nodoLM *listaM, nodoT *&listaT, nodoLP *&listaP,
                         int mes) {}

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

nodoLP *buscarPaciente(nodoLP *lista, char dni[]) {
  nodoLP *listaP = lista;
  while (listaP != NULL && strcmp(dni, listaP->info.dni) != 0) {
    listaP = listaP->sgte;
  }
  if (strcmp(dni, listaP->info.dni) == 0)
    return listaP;
  return NULL;
}

nodoLM *filtrarMedicos(nodoLM* lista, int idEspecialidad) {
    nodoLM* listaM = lista;
    nodoLM* especialistas = NULL;
    while(lista != NULL) {
        Medico m = listaM->info;
        if(m.idEspecialidad == idEspecialidad) pushMedico(especialistas, m);
        listaM = listaM->sgte;
    }
    return especialistas;
}
