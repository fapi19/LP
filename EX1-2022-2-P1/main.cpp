/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: PC
 *
 * Created on 1 de octubre de 2023, 13:08
 */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;
#include "FuncionesConsultasMedicasPreg1.h"
/*
 * 
 */
int main(int argc, char** argv) {
    int *med_Codigo, ***consultas_int;
    double *med_Precio;
    char **med_Descripcion, ***consultas_char;
    CargarMedicamentos(med_Codigo, med_Descripcion, med_Precio, 
            "Medicinas-Preg01.csv");
    PruebaDeCargaDeMedicamentos(med_Codigo, med_Descripcion, med_Precio,
            "PruebaMedicinas.txt");
    CargarConsultas(consultas_int, consultas_char, "Consultas-Preg01.csv");
    return 0;
}

