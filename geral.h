#ifndef GERAL_H
#define GERAL_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef enum {
    ESPEC_CLINICO, ESPEC_PEDIATRA, ESPEC_DERMATO, ESPEC_CARDIO, ESPEC_PSICO
} Especialidade;

typedef struct {
    int hora;
    int minuto;
} Horario;

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    Data data;
    Horario inicio;
    bool ocupado;
} SlotConsulta;

typedef struct {
    int id;
    char nome[64];
    Especialidade especialidade;
    Horario inicioManha, fimManha;
    Horario inicioTarde, fimTarde;
    int num_atendimentos;
    SlotConsulta *atendimentos;
} medicos;

typedef struct {
    int id;
    char nome[64];
    char contato[64];
} pacientes;

typedef enum {
    CONS_AGENDADA, CONS_CONCLUIDA, CONS_CANCELADA, CONS_FALTA
} StatusConsulta;

typedef struct {
    int id;
    int idMedico;
    int idPaciente;
    Data data;
    Horario inicio;
    Horario fim;
    int indice_atendimento;
    StatusConsulta status;
    int prioridade;
} consultas;

// funcoes gerais 

void limpar_buffer();
int validar_nome(const char *n);
int validar_horario(Horario horario, int minh, int maxh);
int validar_interalo_horario(Horario horainic, Horario horafim);
int validar_contato(const char *contato);
int apenas_numeros();
Horario somar_minutos(Horario h, int minutos);

// funcoe medicos

void adicionar_medico(medicos **medico, int *m, int *idmedico, int *capacidade_medicos);
void listarmedicos(medicos *m, int j);
medicos* buscaidm(medicos *x, int tam, int y);
void atualizarm(medicos *m, int t);
void remover_medico(medicos **medico, int *num_medicos);
int ordenar_medico_id(const void *x, const void *y);
void ordenar_medico_ID(medicos *a, int b);
int comparar_medicos(const void *a, const void *b);
void ordenar_medicos(medicos *x, int n); // ordena por ordem alfabetica
int comparar_medicos_esp(const void *a, const void *b);
void ordenar_medicos_esp(medicos *x, int n);

// funcoes pacientes

void adicionar_paciente(pacientes **paciente, int *p, int *idpaciente, int *capacidade_pacientes);
void listarpacientes(pacientes *x, int n);
pacientes* buscaidp(pacientes *a, int t, int b) ;
void atualizarpacientes(pacientes *p, int t);
void remover_paciente(pacientes **paciente, int *num_pacientes);
int compararpacientes(const void *a, const void *b);
int ordenar_id_paciente(const void *a, const void *b);
void ordenar_paciente_ID(pacientes *p, int n);
void ordenarpacientes(pacientes *x, int n);

// funcoes consultas 

bool anobissexto(int ano);
bool validar_data(Data d);
void processar_turno(medicos *medico, Horario inicio_turno, Horario fim_turno);
bool data_igual(Data a, Data b);
void adicionar_consulta(medicos **medico, int *num_medicos, int *c, consultas **consulta, int *idconsulta, int *capacidade_consultas, int *num_pacientes, pacientes *paciente);
void listarconsultas(medicos *medico, int *num_medicos, int *c, consultas *consulta, int *num_pacientes, pacientes *paciente);
consultas* buscaidc(consultas *consulta, int *c, int idcerto);
void exibir_consulta(medicos *medico, int num_medicos, consultas *consulta, int num_pacientes, pacientes *paciente);
void atualizarconsulta(int *c, consultas **consulta, medicos *medico, int num_medicos, pacientes *paciente, int num_pacientes);
void remover_consulta(consultas **c, int *tc);
void relatorio(consultas *consulta, int nc, medicos *medico, int nm, pacientes *paciente, int np);

#endif