/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "FuncionesEx01_20202_Preg1.h"


void leerDatos( void *&pedidos, void *&stock){
    ifstream archpedidos("pedidos.csv", ios::in);
    if( not archpedidos.is_open()){
        cout << "ERROR NO SE PUDO ABRIR EL ARCHIO Pedidos.csv"<<endl;
        exit(1);
    }
    
    leerPedidos(pedidos, archpedidos);
    
    ifstream archstock("stock.csv", ios::in);
    if( not archstock.is_open()){
        cout << "ERROR: No se pudo abrir el archivo stock.csv"<<endl;
        exit(1);
    }
    
    leerStock(stock, archstock);
}

void leerPedidos( void *&pedidos, ifstream &input){
    
}