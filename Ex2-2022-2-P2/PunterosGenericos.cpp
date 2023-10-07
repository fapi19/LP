/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
using namespace std;
#include "FuncionesAuxiliares.h"
#include "PunterosGenericos.h"


void cargamedicinas(void *&medicinas){
    ifstream arch("Medicinas.csv",ios::in);
    if(not arch.is_open()){
        cout<<"No puede abrirse el archivo Medicinas.csv"<<endl;
        exit(1);
    }
    void **lmedicinas;
    int numMedicinas=0;
    void *buffMed[300];
    while(true){
        buffMed[numMedicinas]=leeRegistroMed(arch);
        if(arch.eof())break;
        numMedicinas++;
    }
    lmedicinas=new void *[numMedicinas+1];
    for(int i=0;i<=numMedicinas;i++){
        lmedicinas[i]=buffMed[i];
    }
    medicinas=lmedicinas;
}
void *leeRegistroMed(ifstream &arch){
    int cod;
    int *codigo,*reserva;
    arch>>cod;
    if(arch.eof())return nullptr;
    char cad[200],*nombre;
    double *precio;
    int *stock;
    codigo=new int;
    *codigo=cod;
    precio=new double;
    stock=new int;
    reserva=new int;
    *reserva=0;
    arch.get();
    arch.getline(cad,200,',');
    nombre=new char [strlen(cad)+1];
    strcpy(nombre,cad);
    arch>>*precio;
    arch.get();
    arch>>*stock;
    void **registro;
    registro=new void *[5];
    registro[0]=codigo;
    registro[1]=nombre;
    registro[2]=precio;
    registro[3]=stock;
    registro[4]=reserva;
    return registro;
}

void cargaconsultas( void *&citas){
    ifstream input("Consultas.csv",ios::in); 
    if( not input.is_open()){
        cout << "ERROR: No se pudo abrir el archivo Consutas.csv"<<endl;
        exit(1);
    }
    void **auxCitas, *registro;
    void *bufferCitas[300]{};
    int nCitas = 0;
    while(true){
        registro = leerConsultas(input);
        if( input.eof()) break;
        bufferCitas[nCitas] = registro;
        nCitas ++;
    }
    nCitas++;
    auxCitas = new void*[nCitas];
    for( int i=0;i<nCitas;i++){
        auxCitas[i] = bufferCitas[i];
    }
    citas = auxCitas;
}

void* leerConsultas(ifstream &input){
    void **registro;
    char *ptr_codigo;
    int *ptr_dni, dni;
    char *ptr_nombre,car;
    int *ptr_fecha, fecha, dd , mm , aa;
    int *ptr_cantidad, cantidad;
    ptr_codigo = leerCadena(input);
    if(input.eof()) return nullptr;
    input >> dni >> car;
    ptr_nombre = leerCadena(input);
    input >> dd >> car >> mm >> car >> aa >> car >> cantidad;
    fecha = dd + mm*100 + aa*10000;
    ptr_dni = new int;
    *ptr_dni = dni;
    ptr_fecha = new int;
    *ptr_fecha = fecha;
    ptr_cantidad = new int;
    *ptr_cantidad = cantidad;
    registro = new void*[5];
    registro[0] = ptr_dni;
    registro[1] = ptr_nombre;
    registro[2] = ptr_cantidad;
    registro[3] = new void*[cantidad];
    leerMedicamentos(input, registro[3], cantidad);
    registro[4] = ptr_fecha;
    return registro;
}

char* leerCadena(ifstream &input){
    char buffer[150],*cad;
    input.getline(buffer,150,',');
    cad = new char[ strlen(buffer) + 1];
    strcpy(cad, buffer);
    return cad;
}

void leerMedicamentos(ifstream &input, void *&reg, int cantidad){
    void **registro = (void**)reg;
    for(int i=0;i<cantidad;i++){
        registro[i] = leerUNMedicamento(input);
        input.get();
    }
}

void* leerUNMedicamento( ifstream &input){
    int *cod;
    cod = new int;
    char *estado, c;
    int *cantidad;
    char est = 'S';
    cantidad = new int;
    estado = new char;
    input >> *cod >> c >> *cantidad;
    *estado = est;
    void **registro = new void*[3];
    registro[0] = cod;
    registro[1] = cantidad;
    registro[2] = estado;
    
    return registro;
}

void cargareservas(void *&medicinas, void *&citas){
    //Recorree citas y actualiza medicamentos
    void **auxCitas = (void**)citas;
    for(int i=0; citas[i];i++){
        buscarDatosCitas(auxCitas[i],medicinas);
    }
}

void buscarDatosCitas( void *&cita, void *&medicinas){
    // aca ya me ubique en una cita
    //debo buscar los medicamentos
    void **registro = (void**)cita;
    int *cantidadMedicamentos = registro[2];
    procesarMedicamentos( registro[3], cantidadMedicamentos, medicinas);
}

void procesarMedicamentos( void *recetadas, int cant, void *&medicinas){
    void **medicamentos = (void**)recetadas;
    for(int i=0;i<cant;i++){
        procesaUNMedicamento(medicamentos[i],medicinas);
    }
}

void procesaUNMedicamento( void *medRecetado, void *&medicinas){
    // aca ya me ubique en un medicamento, por lo que debo acceder a su codigo
    void **registro = (void**)medRecetado;
    int *codigo = (int*)registro[0];
    int *cantidad = (int*)registro[1];
    //debo buscar el medicamento
    int stock, reserva;
    void **arrMedicinas = (void**)medicinas;
    int posMedicina = buscarMedicina(*codigo, medicinas,stock,reserva);
    if((stock-reserva)>=cantidad){
        //osea si alcanza , se actualiza
        char *estado = (char*)registro[2];
        *estado  = 'R';
        actualizarStock(cantidad, arrMedicinas[posMedicina]);
    }
}

int buscarMedicina( int codigo, void *medicinas, int &stock, int &reserva){
    void **registro = (void**)medicinas;
    for(int i=0;medicinas[i];i++){
        void *aterrizaje = (void **)medicinas[i];
        int *MedCod = (int*)aterrizaje[0];
        if(*MedCod == codigo){
            //saco el stock y la reserva
            stock = *(int*)aterrizaje[3];
            reserva = *(int*)aterrizaje[4];
            return i;
        }
    }
    return -1;
}

void actualizarStock( int cant, void *medicina){
    void **aterrizaje = (void**)medicina;
    int *reserva = (int*)aterrizaje[4];
   *reserva = *reserva + cant;
}