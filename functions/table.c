#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../defs.h"
#include "funcs.h"

void createTable(){
    char tableName[15];
    char attrb[20];
    scanf(" %[^\n]", tableName);

    FILE *file;
    file = fopen("~/Desktop/Projects/projeto-sgbd-itp/teste.txt", "w");
    fprintf(file, "hello world");
    //verificar se já existe tabela com esse nome
}

void listTables(){
    char tableName[15];
}

void listDataFromTable(){
    char tableName[15];

    //importar do txt
    //printar
}

void deleteLine(){
    char tableName[15];
    char pk[15];
    //verificar se a pk existe
    listDataFromTable();
    //verificar se é essa msm
    //apagar linha no txt
    listDataFromTable();
}

void dropTable(){
    char tableName[15];
    //apagar .txt
}

void addData(){
    char tableName[15];
    
    listDataFromTable();
    //verificar se a pk já existe
    //atualizar txt
}

void searchData(){
    char tableName[15];
    char nameCol[15];
    char filter[2];
    //bater o filtro com o tipo de dado da coluna
}