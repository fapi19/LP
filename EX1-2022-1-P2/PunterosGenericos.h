/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   PunterosGenericos.h
 * Author: PC
 *
 * Created on 1 de octubre de 2023, 11:37
 */

#ifndef PUNTEROSGENERICOS_H
#define PUNTEROSGENERICOS_H

void cargaproductos( void *&productos);
void* leerProductos(ifstream &input);
char* leerCadena(ifstream &input);
void asignarOriginal(void *&productos, void **bufferProductos, int nd);
void cargapedidos( void *&pedidos);
void* leerPedidos(ifstream &input);
void procesaclientes(void *productos, void *pedidos, void *&clientes);
int buscarCliente(void **bufferClientes, int dni, int nd);
void* crearCliente(int dni,char* nombreCliente, int &cantPedidos);
#endif /* PUNTEROSGENERICOS_H */

