/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;
#include "FuncionesConsultasMedicasPreg1.h"
#define INCREMENTO 5
void  CargarMedicamentos( int *&med_Codigo, char **&med_Descripcion, double
                            *&med_Precio, const char *nombArch){
    ifstream input(nombArch,ios::in);
    if( not input.is_open()){
        cout <<" ERROR : No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    int cod;
    char *descripcion;
    double precio;
    //memoria por incremento
    med_Codigo = nullptr;
    med_Descripcion = nullptr;
    med_Precio = nullptr;
    int nd = 0, cap = 0;
    while(true){
        lecturaDatos(cod, descripcion, precio,input);
        if(input.eof()) break;
        if(nd == cap){
            incrementarMemoria(med_Codigo, med_Descripcion, med_Precio, nd, cap);
        }
        med_Codigo[nd-1] = cod;
        med_Descripcion[nd-1] = descripcion;
        med_Precio[nd-1] = precio;
        nd++;
    }
    
}
void lecturaDatos( int &codigo, char *&descripcion, double &precio,
                    ifstream &input){
    input >> codigo;
    if(input.eof()) return;
    input.get();
    descripcion = leerCadena(input);
    input >> precio;
}


char* leerCadena( ifstream &input ){
    char buffer[150], *cad;
    input.getline(buffer,150,',');
    cad =  new char[strlen(buffer)+1];
    strcpy(cad, buffer);
    return cad;
}

void incrementarMemoria(int *&med_Codigo, char **&med_Descripcion, double
                            *&med_Precio, int &nd , int &cap){
    int *auxCodigo;
    char **auxDescripcion;
    double *auxPrecio;
    cap+= INCREMENTO;
    if(med_Codigo == nullptr ){
        med_Codigo = new int [cap]{};
        med_Descripcion = new char *[cap]{};
        med_Precio = new double [cap]{};
        nd = 1;
    }
    else{
        auxCodigo = new int [cap]{};
        auxDescripcion = new char *[cap]{};
        auxPrecio = new double [cap]{};
        for(int i=0; i<nd;i++){
            auxCodigo[i] = med_Codigo[i];
            auxDescripcion[i] = med_Descripcion[i];
            auxPrecio[i] = med_Precio[i];
        }
        delete med_Codigo;
        delete med_Descripcion;
        delete med_Precio;
        med_Codigo = auxCodigo;
        med_Descripcion = auxDescripcion;
        med_Precio = auxPrecio;
    }
}

void PruebaDeCargaDeMedicamentos(int *med_Codigo, char **med_Descripcion, double
                            *med_Precio, const char *nombArch){
    ofstream output(nombArch,ios::out) ;
    if( not output.is_open()){
        cout << "ERROR: No se pudo abrir el archivo "<<nombArch <<endl;
        exit(1);
    }
    output << setprecision(2);
    output << fixed;
    for(int i=0;med_Codigo[i];i++){
        output << med_Codigo[i]<<setw(10) << " "<<setw(40)<<left<<
                med_Descripcion[i] << right << setw(7)<< med_Precio[i]<<endl;
    }
}

void CargarConsultas( int ***&consultas_int, char ***&consultas_char,
                        const char *nombArch){
    
    ifstream input(nombArch, ios::in);
    if( not input.is_open()){
        cout << "ERROR: No se puede abrir el archivo "<< nombArch << endl;
        exit(1);
    }
    int **bufferInt[200]{};
    char **bufferChar[200]{},car;
    int nPacientes = 0, nMedicinas[300]{};
    int *bufferMedicinas[300]{};
    int fecha, dni, posPaciente, valor;
    char *nombre, *codMedico;
    int auxCodigo, auxCantidad, nMedicos[300]{};
    while( true ){
        lecturaDatos1raParte(fecha, dni, nombre, codMedico, input);
        if(input.eof()) break;
        posPaciente = buscarPaciente(bufferInt,dni, nPacientes);
        if(posPaciente == -1){ //osea si es nuevo lo ingreso
            valor = 0;
            ingresarPaciente(bufferInt[nPacientes],
                    bufferChar[nPacientes], dni, nombre, codMedico, fecha,
                    nMedicos[nPacientes], valor);
            posPaciente = nPacientes;
            nPacientes ++;
        }
        else{
            valor = 1;
            ingresarPaciente(bufferInt[posPaciente],
                    bufferChar[posPaciente], dni, nombre, codMedico, fecha,
                    nMedicos[posPaciente], valor );
        }
        //ahora debemos analizar para la gran lista de medicinas
        while(true){
            input >> car;
            if(input.fail()){
                input.clear();
                break;
            }
            input >> auxCodigo;
            input.get();
            input >> auxCantidad;
            ingresarMedicina(bufferInt[posPaciente], auxCodigo, auxCantidad,
                    nMedicinas[posPaciente]);
        }
    }
    //asignarOriginal()
}
void ingresarPaciente( int **paciente, char **medicos, int dni, char *nombre,
        char *codMedico, int fecha, int &nMedicos, int valor){
    int *auxDNI = paciente[0];
    int *auxFecha = paciente[1];
    if(valor == 1){  // valor 1 es si es que es repetido
        if ( fecha > auxFecha[0]){
            auxFecha[0] = fecha;
        }
        medicos[1 + nMedicos] = codMedico;
        nMedicos++;
    }
    // *arreglo de dni
    else{
        auxDNI = new int;
        auxDNI[0] = dni;

        auxFecha = new int;
        auxFecha[0] = fecha;

        medicos[0] = nombre;
        medicos[1] = codMedico;
        nMedicos++;
    }
    
}

void lecturaDatos1raParte(int &fecha, int &dni, char *&nombre, char *&codMedico,
        ifstream &input){
    int dd, mm, aa;
    char car;
    input >> dd >> car >> mm >> car >> aa;
    if(input.eof()) return;
    fecha = dd + 100*mm + 10000*aa;
    input.get();
    input >> dni >> car;
    nombre =leerCadena(input);
    codMedico = leerCadena(input);
}

int buscarPaciente( int ***bufferInt, int dni, int cant){
    for(int i=0;i<cant;i++){
        int **aterrizaje = bufferInt[i];
        int *aterrizaje2 = aterrizaje[0];
        int valorDni = aterrizaje2[0];
        if( dni == valorDni) return i;
    }
    return -1;
}

void ingresarMedicina(int **&paciente, int codigo, int cantidad,int &nMedicinas){
    //debo recorrer 1ro para encontrar si la medicina ya esta
    int posMedicina;
    posMedicina = buscarMedicina(paciente, nMedicinas, codigo);
    if(posMedicina == -1){
        // aca si existe la medicina por lo que debo incrementar la cantidad
        int *aux = paciente[2+posMedicina] ;
        aux[1] += cantidad;
        
    }
    else{
        paciente[2+nMedicinas] = new int [2];
        int *aux = paciente[2+nMedicinas];
        aux[0] = codigo;
        aux[1] = cantidad;
    }
    nMedicinas ++;
}

int buscarMedicina( int **&paciente, int nMedicinas, int codigo){
    int *aterrizaje;
    int valorCodigo;
    for(int i=0; i<nMedicinas;i++){
        //buscamos de acorde , recordemos que a partir de la posicion 2 
        // se encuentran todas las medicinas
        aterrizaje = paciente[2+i];
        valorCodigo = aterrizaje[0];
        if( valorCodigo == codigo) return i;
    }
    return -1;
}