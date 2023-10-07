/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: PC
 *
 * Created on 29 de setiembre de 2023, 20:14
 */
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "ClientesPreg1.h"
#include "FuncionesExamen01Pregunta01.h"
/*
 * 
 */
int main(int argc, char** argv) {
    int ***cli_DniTelPed, **pro_Informacion, **ped_Todo;
    char ***cli_NombreCategoria, **pro_Descripcion;
    CargaDeClientes(cli_DniTelPed, cli_NombreCategoria, "ClientesPreg01.csv");
    PruebaDeClientes(cli_DniTelPed, cli_NombreCategoria, 
            "PruebaClientes01.txt");
    CargarProductosPedidos(pro_Informacion, pro_Descripcion, ped_Todo,
            "PedidosPreg01.csv");
    PruebaProductosPedidos(pro_Informacion, pro_Descripcion, ped_Todo,
            "PruebaProductosPedidos01.txt");
    ordenarPedidos(ped_Todo);
    PruebaProductosPedidos(pro_Informacion, pro_Descripcion, ped_Todo,
            "PruebaProductosPedidos02.txt");
    asignarPedidos(cli_DniTelPed, pro_Informacion, ped_Todo);
    PruebaProductosPedidos(pro_Informacion, pro_Descripcion, ped_Todo,
            "PruebaPeroductosPedidos03.txt");
    PruebaDeClientes(cli_DniTelPed, cli_NombreCategoria, 
            "PruebaClientes02.txt");
    return 0;
}

