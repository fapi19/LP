/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: PC
 *
 * Created on 1 de octubre de 2023, 11:31
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "MuestraPunteros.h"
#include "PunterosGenericos.h"
/*
 * 
 */
int main(int argc, char** argv) {
    void *productos, *pedidos, *clientes;
    cargaproductos(productos);
    imprimeproductos(productos);
    cargapedidos(pedidos);
    imprimepedidos(pedidos);
    procesaclientes(productos,pedidos,clientes);
    imprimerepfinal(clientes);
    return 0;
}

