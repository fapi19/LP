/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   FuncionesConsultasMedicasPreg1.h
 * Author: PC
 *
 * Created on 1 de octubre de 2023, 13:14
 */

#ifndef FUNCIONESCONSULTASMEDICASPREG1_H
#define FUNCIONESCONSULTASMEDICASPREG1_H

void  CargarMedicamentos( int *&med_Codigo, char **&med_Descripcion, double
                            *&med_Precio, const char *nombArch);
void lecturaDatos( int &codigo, char *&descripcion, double &precio,
                    ifstream &input);
char* leerCadena( ifstream &input );
void incrementarMemoria(int *&med_Codigo, char **&med_Descripcion, double
                            *&med_Precio, int &nd , int &cap);
void PruebaDeCargaDeMedicamentos(int *med_Codigo, char **med_Descripcion, double
                            *med_Precio, const char *nombArch);
void CargarConsultas( int ***&consultas_int, char ***&consultas_char,
                        const char *nombArch);
void ingresarPaciente( int **paciente, char **medicos, int dni, char *nombre,
        char *codMedico, int fecha, int &nMedicos, int valor);
void lecturaDatos1raParte(int &fecha, int &dni, char *&nombre, char *&codMedico,
        ifstream &input);
int buscarPaciente( int ***bufferInt, int dni, int cant);
void ingresarMedicina(int **&paciente, int codigo, int cantidad,int &nMedicinas);
int buscarMedicina( int **&paciente, int nMedicinas, int codigo);
#endif /* FUNCIONESCONSULTASMEDICASPREG1_H */

