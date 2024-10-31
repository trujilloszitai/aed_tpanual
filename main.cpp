#include <iostream>
#include <cstring>
using namespace std;

// Estructuras - Entidades
struct Paciente {
    int id = 0;
    char nombre[50+1] = "";
    char apellido[50+1] = "";
    int edad = 0;
    char dni[8+1] = "";
    char telefono[10+1] = "";
};

struct Medico {
    int id = 0;
    char nombre[50+1] = "";
    char apellido[50+1] = "";
    int matricula = 0;
    int idEspecialidad = 0;
    int diasDeAtencion[7] = {0};
    float rengoHorario[2] = {0.0};
    int tiempoDeConsulta = 0;
};

struct Especialidad {
    int id = 0;
    char descripción[50+1] = "";
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
struct nodoP {
    Paciente info;
    nodoP* sgte;
};

struct nodoM {
    Medico info;
    nodoM* sgte;
};

struct infoT {
    int idMedico;
    Turno turno;
};

struct nodoT {
    infoT info;
    nodoT* sgte;
};

int main()
{

    return 0;
}

nodoP* leerArchivoPacientes(FILE* f) {

}

nodoM* leerArchivoMedicos(FILE* f) {

}

nodoT* leerArchivoTurnos(FILE* f) {

}

void menu() {

}

int altaPaciente(nodoP*& lista) {

}

int altaTurno(nodoT*& lista) {

}

int altaMedico(nodoM*& lista) {

}

int actualizarEstatus(nodoM* listaM, nodoT*& listaT, int idMedico) {

}

void turnosPendientes(nodoM* listaM, nodoT*& listaT, int idMedico, int mes) {

}

void atencionesEfectivas(nodoM* listaM, nodoT*& listaT, int mes) {

}

void cancelacionesPorMes(nodoM* listaM, nodoT*& listaT, nodoP*& listaP, int mes) {

}
