/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "ClientesPreg1.h"
#include "FuncionesExamen01Pregunta01.h"
#define INCREMENTO 5

//412041,TORTILLAS DE MAIZ 1KG,7.91%,1.78,14.93,15.95,71378466,26/10/2020
//Codigo, descripcion, descuento(si tiene),cantidad,precio, stock,DNI,fecha
void CargarProductosPedidos(int **&pro_Informacion, char **&pro_Descripcion,
        int **&ped_Todo, const char *nombArch){
    ifstream input(nombArch, ios::in);
    if( not input.is_open()){
        cout << "ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    
    //METODO EXACTO - buffers
    int *bufferProInformacion[200]{}, *bufferPedTodo[200]{};
    char *bufferProDescripcion[200]{};
    int nProd = 0, nPed = 0, posProd;
    int codigo, descuento, cantidad, precio, stock, dni, fecha;
    char *descripcion;
    while(true){
        leerDatos(codigo, descripcion, descuento, cantidad, precio, stock,
                dni, fecha, input);
        //cout << codigo << endl; probanding
        if(input.eof()) break;
        //PRODUCTOS NO REPETIDOS
        posProd = buscarProd(codigo, bufferProInformacion, nProd);
        if(posProd == -1){ // si no se ha repetido se agrega
            agregarProducto(bufferProInformacion[nProd], bufferProDescripcion[nProd]
                    , codigo, descuento, precio, stock, descripcion);
            nProd ++;
        }
        //y en cualquier caso se agrega el pedido
        agregarPedido( bufferPedTodo[nPed], dni, fecha, cantidad, codigo);
        nPed ++;
    }  
    nProd++, nPed ++;
    pro_Descripcion = new char *[nProd]{};
    pro_Informacion = new int *[nProd]{};
    for(int i=0;i<nProd;i++){
        pro_Descripcion[i] = bufferProDescripcion[i] ;
        pro_Informacion[i] = bufferProInformacion[i] ; 
    }
    ped_Todo = new int *[nPed]{};
    for(int i=0;i<nPed;i++){
        ped_Todo[i] = bufferPedTodo[i]; 
    }
}

void leerDatos(int &codigo, char *&descripcion, int &descuento, int &cantidad,
        int &precio, int &stock,int &dni, int &fecha, ifstream &input){
    double auxCant, auxPrec, auxStock;
    char car;
    input >> codigo;
    if(input.eof()) return ;
    input.get(); // coma
    descripcion = leerCadena(input);
    // ya he leido hasta la coma
    input >> auxCant;
    if(input.get() == '%'){  // si si es el descuento
        descuento = auxCant*100;
        input >> car >> auxCant;
    }
    input >> car >> auxPrec >> car >> auxStock >>  car >> dni >> car ;
    int dd, mm , aa;
    input >> dd >> car >> mm >> car >> aa;
    fecha = dd + mm*100 + aa*10000;
    //ya esta el descuento, falta la cantidad, precio, stock
    stock = auxStock * 100;
    precio  = auxPrec * 100;
    cantidad = auxCant * 100;
}

char *leerCadena(ifstream &input){
    char buffer[150], *cad;
    input.getline(buffer, 150, ',');
    cad = new char[strlen(buffer)+1];
    strcpy(cad, buffer);
    return cad;
}

int buscarProd(int codigo, int **bufferProInformacion, int n){
    for(int i=0;i<n;i++){
        //debemos hacer aterrizaje jijiji amo a mi novia mucho
        int *aterrizajeCodigo = bufferProInformacion[i];
        if( codigo == aterrizajeCodigo[0]) return i;
    }
    return -1;
}

void agregarProducto(int *&bufferProInformacion,char *& bufferProDescripcion
                    , int codigo, int descuento,int  precio,int  stock, 
                        char *descripcion){
    //ya estamos en la posicion dada por lo cual debemos reservar memoria
    // para el caso de la proinformacion, son 4 espacio
    bufferProInformacion = new int[4];
    bufferProInformacion[0] = codigo;
    bufferProInformacion[1] = descuento;
    bufferProInformacion[2] = precio;
    bufferProInformacion[3] = stock;
    // y en el caso de la descripcion la memoria ya se reservó asi que defrente
    bufferProDescripcion = descripcion;
}

void agregarPedido(int *& bufferPedTodo, int dni, int fecha, int cantidad, 
                    int codigo){
    bufferPedTodo = new int [4];
    bufferPedTodo[0] = dni;
    bufferPedTodo[1] = fecha;
    bufferPedTodo[2] = cantidad;
    bufferPedTodo[3] = codigo;
}

void PruebaProductosPedidos(int **pro_Informacion, char **pro_Descripcion,
        int **ped_Todo, const char *nombArch){
    ofstream output(nombArch, ios::out);
    if(not output.is_open()){
        cout << "ERROR: No se pudo abrir el archivo "<<nombArch<<endl;
        exit(1);
    }
    imprimirProductos(pro_Informacion, pro_Descripcion,output);
    output << endl;
    imprimirPedidos(ped_Todo,output);
}

void imprimirProductos(int **pro_Informacion, char **pro_Descripcion,
                        ofstream &output){
    output << right << setw(10) << "CODIGO" << setw(10)  << "DESCUENTO"
            <<  setw(10) << "PRECIO" << setw(10)  << "STOCK" <<right << endl;
    for(int i=0; pro_Informacion[i];i++){
        imprimirUNProducto(pro_Informacion[i], pro_Descripcion[i],output);
    }
}

void imprimirUNProducto( int *info, char *descri, ofstream &output){
    output << setw(10) << info[0] << setw(10) << info[1] << setw(10) <<
            info[2] << setw(10)  << info[3] << setw(6) << " "<<setw(40)<<
            descri << endl;
}
void imprimirPedidos( int **ped_Todo, ofstream &output){
    output<< right << setw(10) << "DNI" << setw(10) << "FECHA" <<setw(10)
            << "CANTIDAD" << setw(10) << "CODIGO" << endl;
    for(int i=0; ped_Todo[i];i++){
        imprimirUNPedido(ped_Todo[i],output);
    }
}

void imprimirUNPedido(int *pedido, ofstream &output){
    output << setw(10) << pedido[0] << setw(10) << pedido[1] << setw(10)
            << pedido[2] << setw(10) << pedido[3] << endl;
}

void ordenarPedidos(int **ped_Todo){
    int nd = 0;
    while(ped_Todo[nd]) nd++;
    qSort(ped_Todo, 0 , nd -1 );
}

void qSort(int **ped_Todo, int izq, int der){
    int limite, pos;
    if(izq>=der) return;
    pos = (izq + der) /2;
    cambiar(ped_Todo[izq],ped_Todo[pos] );
    limite = izq;
    for(int i=izq+1; i<=der;i++){
        if(comparar(ped_Todo[i], ped_Todo[izq])){
            limite++;
            cambiar(ped_Todo[limite],ped_Todo[i]);
        }
    }
    cambiar(ped_Todo[limite], ped_Todo[izq]);
    qSort(ped_Todo, izq, limite - 1);
    qSort(ped_Todo, limite+1, der);
}

void cambiar( int *&pedI, int *&pedK){
    int *auxPed;
    
    auxPed = pedI;
    pedI = pedK;
    pedK = auxPed;
}

int comparar( int *ped1, int *ped2){
    return ped1[1] < ped2[1] or (ped1[1] == ped2[1] and ped1[0] < ped2[0]);
}

void asignarPedidos(int ***&cli_DniTelPed,int **& pro_Informacion,int ** ped_Todo){
    //SE DEBE ASIGNAR EN LOS CLIENTES SI ES QUE HAY STOCK SUFICIENTE EN  
    // LOS PRODUCTOS SI ES QUE HAY SE RESTA EL STOCK 
    int i=0;
    for(i = 0;cli_DniTelPed[i];i++);
    int numPed[i+1]{} , capPed[i+1]{};  // los contadores 
    // para los pedidos que ya este dentro de los CLIENTES
    //ANALIZANDO DEBEMOS 1RO RECORRER TODOS LOS PEDIDOS
    int pos, codigo, cantidad, fecha;
    int dni;
    for(int j=0; ped_Todo[i];i++){
        dni = obtenerDNI(ped_Todo[i],codigo, cantidad, fecha);
        // ahora debemos ubicar el dni en los clientes
        pos = buscarDNI( dni, cli_DniTelPed);
        // ahora ya tengo la posicion en la cual meter , por lo que pues
        // lo meto XDDDD, SIN OLVIDAR VALIDAR STOCK
        if( pos !=-1 and hayStock(pro_Informacion,cantidad,codigo)){
            insertarPedido(cli_DniTelPed[pos], numPed[pos],capPed[pos], codigo, 
                cantidad, fecha);
        }
         // ya dentro le actualizo num y cap
    }
}

int obtenerDNI( int *ped, int &codigo, int &cantidad, int &fecha){
    codigo = ped[3];
    cantidad = ped[2];
    fecha = ped[1];
    // devolvemos DNI
    return ped[0];
}

int buscarDNI(int dni, int ***cli_DniTelPed){
    for(int i=0;cli_DniTelPed[i];i++){
        int **aterrizaje1 = cli_DniTelPed[i];
        int *aterrizaje2 = aterrizaje1[0];
        int dniAux  = aterrizaje2[0];
        if(dni == dniAux) return i;
    }
    return -1;
}

int hayStock(int **&pro_Informacion, int cantidad, int codigo){
    //cantidad es lo que se solicita debo validar si es que 
    // hay stock en pro y si hay devolvemos 1 y actualizamos el stock
    for(int i=0; pro_Informacion[i];i++){
        int *aterrizajePro = pro_Informacion[i];
        if(codigo == aterrizajePro[0] ){
            // aca ya hemos encontrado 
            // ahora, validemos la cantidad
            if(cantidad<=aterrizajePro[3]){
                //hemos encontrado por lo que primero 
                aterrizajePro[3] -= cantidad;
                return 1;
            }
            break;
        }
    }
    return 0;
}

void insertarPedido(int **&cli_DniTelPed,int & numPed,int &capPed,int
                        codigo, int cantidad, int fecha){
    if(numPed == capPed){
        // se incrementa memoria en al posicion 
        incrementarMemoria(cli_DniTelPed[2], numPed, capPed);
    }
    insertarNivel(cli_DniTelPed[2],numPed-1,codigo, cantidad, fecha);
    numPed ++;
    
}

void incrementarMemoria(int *&pedidosCli, int &nd, int &cap){
    int *auxPed;
    cap += INCREMENTO;
    if(pedidosCli == nullptr){
        pedidosCli = new int[cap*3]{};
        nd = 1;
    }
    else{
        auxPed = new int[cap*3]{};
        for(int i=0; i<nd;i++){
            auxPed[i] = pedidosCli[i];
        }
        delete pedidosCli;
        pedidosCli = auxPed;
    }
}

void insertarNivel(int *&pedidosCli, int pos, int codigo, int
                        cantidad, int fecha){
    //ERROR EN LAS LIBRERIAS
    pedidosCli[pos*3] = fecha;
    pedidosCli[pos*3+1] = codigo;
    pedidosCli[pos*3+2] = cantidad;
}