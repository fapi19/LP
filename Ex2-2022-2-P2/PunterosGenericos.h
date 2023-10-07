/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   PunterosGenericos.h
 * Author: PC
 *
 * Created on 1 de octubre de 2023, 16:15
 */

#ifndef PUNTEROSGENERICOS_H
#define PUNTEROSGENERICOS_H
void cargamedicinas( void *&medicinas);
void *leeRegistroMed(ifstream &arch);
void cargaconsultas( void *&citas);
void* leerConsultas(ifstream &input);
char* leerCadena(ifstream &input);
void leerMedicamentos(ifstream &input, void *&reg, int cantidad);
void* leerUNMedicamento( ifstream &input);

#endif /* PUNTEROSGENERICOS_H */

