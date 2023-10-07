/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: PC
 *
 * Created on 7 de octubre de 2023, 11:48
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    void *pedidos, *stock;
    leerDatos(pedidos, stock);
    atiende(pedidos, stock);
    imprimirDatos(pedidos);
    return 0;
}

