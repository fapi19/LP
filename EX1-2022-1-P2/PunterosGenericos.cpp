/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "MuestraPunteros.h"
#include "PunterosGenericos.h"

void cargaproductos( void *&productos){
    //metodo de memoria exacta por lo que creamos un buffer
    void *bufferProductos[200]{};
    int nProductos = 0;
    void *registro;
    ifstream input("Productos2.csv",ios::in);
    if( not input.is_open()){
        cout << "ERROR: No se puede abrir el archivo Productos2.csv"<<endl;
        exit(1);
    }
    while(true){
        registro = leerProductos(input);
        if(input.eof()) break;
        bufferProductos[nProductos] = registro;
        nProductos ++;
    }   
    asignarOriginal(productos, bufferProductos, nProductos);
}

void* leerProductos(ifstream &input){
    void **registro;
    int *ptr_codigo, codigo;
    char *ptr_descripcion;
    double *ptr_precio, precio;
    int *ptr_cantidad, cantidad;
    char car;
    input >> codigo;
    if(input.eof()) return nullptr;
    input.get();
    ptr_descripcion = leerCadena(input);
    input >> precio >> car >> cantidad;
    //reservemos memoria pa los punteritos y asignamos valor leido
    ptr_codigo = new int;
    *ptr_codigo = codigo;
    ptr_precio = new double;
    *ptr_precio = precio;
    ptr_cantidad = new int;
    *ptr_cantidad = cantidad;
    registro = new void*[4];
    registro[0] = ptr_codigo;
    registro[1] = ptr_descripcion;
    registro[2] = ptr_precio;
    registro[3] = ptr_cantidad;
    return registro;
}

char* leerCadena(ifstream &input){
    char buffer[150], *cad;
    input.getline(buffer, 150, ',');
    cad = new char[ strlen(buffer) + 1 ];
    strcpy(cad,buffer);
    return cad;
}

void asignarOriginal(void *&productos, void **bufferProductos, int nd){
    void **auxProductos = new void*[nd+1]{};
    for(int i=0;i<nd;i++) auxProductos[i] = bufferProductos[i];
    auxProductos[nd] = nullptr;
    productos = auxProductos;
}

void cargapedidos( void *&pedidos){
    ifstream input("Pedidos2.csv",ios::in);
    if( not input.is_open()){
        cout << "ERROR: No se pudo abrir el archivo Pedidos2.csv"<<endl;
        exit(1);
    }
    pedidos = nullptr;
    void *bufferPedidos[200]{};
    int nPedidos = 0;
    void *registro;
    while( true ){
        registro = leerPedidos(input);
        if(input.eof()) break;
        bufferPedidos[nPedidos] = registro;
        nPedidos ++;
    }
    
    asignarOriginal(pedidos, bufferPedidos, nPedidos);
}

void* leerPedidos(ifstream &input){
    void **registro;
    int *ptr_codigo, codigo;
    char *ptr_descripcion;
    int *ptr_cant, cantidad;
    int *ptr_dni, dni;
    int *ptr_fecha, fecha, dd, mm, aa;
    char *ptr_estado, car;
    input >> codigo;
    if(input.eof()) return nullptr;
    input.get();
    ptr_descripcion = leerCadena(input);
    input >> cantidad >> car >> dni >> car >> dd >> car >> mm >> car >> aa;
    fecha = dd + mm*100 + aa*10000;
    ptr_codigo = new int;
    *ptr_codigo = codigo;
    ptr_cant = new int;
    *ptr_cant = cantidad;
    ptr_dni = new int;
    *ptr_dni = dni;
    ptr_fecha = new int;
    *ptr_fecha = fecha;
    ptr_estado = new char;
    *ptr_estado = 'N';
    registro = new void*[6];
    registro[0] = ptr_codigo;
    registro[1] = ptr_descripcion;
    registro[2] = ptr_cant;
    registro[3] = ptr_dni;
    registro[4] = ptr_fecha;
    registro[5] = ptr_estado;
    return registro;
}

void procesaclientes(void *productos, void *pedidos, void *&clientes){
    ifstream input("Clientes2.csv",ios::in);
    if( not input.is_open()){
        cout <<"ERROR: No se pudo abrir el archivo Clientes2.csv"<<endl;
        exit(1);
    }
    char *nombreCliente;
    void *bufferClientes[300]{}, *persona;
    int nClientes = 0, dni,pos, cantPedidos[50]{};
    void *registroCliente ;
    while(true){
        input >> dni;
        if(input.eof()) break;
        input.get();
        nombreCliente = leerCadena(input);
        //ahora insertemos al cliente si es q no esta ya repetido
        pos = buscarCliente(bufferClientes, dni, nClientes);
        cout << pos << endl;
        //cout << "sali" << endl;
        if( pos == -1){//si es nuevo se inserta
            registroCliente =  crearCliente(dni, nombreCliente, cantPedidos[nClientes]);
            bufferClientes[nClientes] = registroCliente;
            pos = nClientes; // para que sea indifrente si se repite o no
            nClientes++;
        }
        //y ahora ingresemos los pedidos de esta persona
        //insertaPedido(bufferClientes[pos], cantPedidos[pos], productos, pedidos);
        
    }
    //RECORDEMOS QUE SON 2 PARTES DE MEM EXACTA
    asignarOriginal(clientes, bufferClientes, nClientes);
    //asignarPedidos(clientes, cantPedidos);
    //ordenarDatos(clientes, nClientes);
}

int buscarCliente(void **bufferClientes, int dni, int nd){
    void **auxClientes;
    for(int i=0;i<nd;i++){
        auxClientes = (void**)bufferClientes[i];
        int *dniAux = (int*)auxClientes[0];
        if( *(int*)auxClientes[0] == dni) return i;
    }
    return -1;
}
void* crearCliente(int dni,char* nombreCliente, int &cantPedidos){
    void **registro ;
    registro = new void*[3];
    int *ptr_dni;
    ptr_dni = new int;
    void **pedidos = new void*[150];
    *ptr_dni = dni;
    registro[0] = ptr_dni;
    registro[1] = nombreCliente;
    registro[2] = pedidos;
    cantPedidos = 0;
    return registro;
}
