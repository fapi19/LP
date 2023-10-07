/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   FuncionesExamen01Pregunta01.h
 * Author: PC
 *
 * Created on 29 de setiembre de 2023, 20:20
 */

#ifndef FUNCIONESEXAMEN01PREGUNTA01_H
#define FUNCIONESEXAMEN01PREGUNTA01_H


#include <fstream>
using namespace std;
void CargarProductosPedidos(int **&, char **&, int **&, const char *);
void leerDatos(int &, char *&, int &, int &,  int &, int &,int &, int &, 
                    ifstream &);
char *leerCadena(ifstream &);
int buscarProd(int , int **, int );
void agregarProducto(int *&,char *&   , int , int ,int  ,int  , char *);
void agregarPedido(int *& , int dni, int , int ,   int );
void PruebaProductosPedidos(int **, char **,  int **, const char *);
void imprimirProductos(int **, char **,   ofstream &); 
void imprimirPedidos( int **, ofstream &);
void imprimirUNProducto( int *info, char *descri, ofstream &output);
void imprimirPedidos( int **ped_Todo, ofstream &output);
void imprimirUNPedido(int *pedido, ofstream &output);
void ordenarPedidos(int **ped_Todo);
void qSort(int **ped_Todo, int izq, int der);
void cambiar( int *&pedI, int *&pedK);
int comparar( int *ped1, int *ped2);
void asignarPedidos(int ***&cli_DniTelPed,int **& pro_Informacion,int ** ped_Todo);
int obtenerDNI( int *ped, int &codigo, int &cantidad, int &fecha);
int buscarDNI(int dni, int ***cli_DniTelPed);
int hayStock(int **&pro_Informacion, int cantidad, int codigo);
void insertarPedido(int **&cli_DniTelPed,int & numPed,int &capPed,int
                        codigo, int cantidad, int fecha);
void incrementarMemoria(int *&pedidosCli, int &nd, int &cap);

void insertarNivel(int *&pedidosCli, int pos, int codigo, int
                        cantidad, int fecha);
#endif /* FUNCIONESEXAMEN01PREGUNTA01_H */

