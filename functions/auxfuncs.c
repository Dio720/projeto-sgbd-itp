#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "funcs.h"

#define MAX_TABLE_NAME 20
#define MAX_NAMES_CONTENT 100
#define MAX_COL_TYPE 10
#define MAX_COL_NAME 25
#define MAX_FILE_NAME 25

int tableCheckError(FILE *tableName){
    if(tableName == NULL){
        printf("Erro ao abrir o arquivo de nomes de tabela");
        fclose(tableName);
        return 1;
    }
    return 0;
}

void initMainTable() {
    FILE *tableOfNames = fopen("txts/main.txt", "r");

    if (tableOfNames == NULL) {
        tableOfNames = fopen("txts/main.txt", "w");
        if (tableOfNames != NULL) {
            char string[35] = "TablesQnt: 0\n==================\n";
            fwrite(string, sizeof(char), strlen(string), tableOfNames);
            fclose(tableOfNames);
        } else {
            printf("Erro ao criar o arquivo\n");
        }
    } else {
        fclose(tableOfNames);
    }
}

void changeTablesQuantity(int addOrDropValue){
    FILE *tableOfNames;
    tableOfNames = fopen("txts/main.txt", "r");

    tableCheckError(tableOfNames);

    char line[15];
    fgets(line, sizeof(line), tableOfNames);

    int current, newTablesQnt;
    if(sscanf(line, "Qnt: %d", &current) != 1){
        printf("Erro ao ler a quantidade de tabelas\n");
        return;
    }
    newTablesQnt = addOrDropValue + current;

    fseek(tableOfNames, 0, SEEK_SET);
    fprintf(tableOfNames, "TablesQnt: %d\n", newTablesQnt);
    fclose(tableOfNames);
}

int isTableNameInUse(char *tableName, char *content){
    char *subString = strtok(content, "\n");

    while (subString != NULL){
        char *nameInUse = strstr(subString, tableName);

        if(nameInUse != NULL){
            return 1;
        }
        subString = strtok(NULL, "\n");
    }
    return 0;
}

bool typeAllowed(char *maybeType){
    char allowedTypes[5][8] = {"int", "float", "double", "char", "string"};

    for(int i = 0; i < 5; i++){
        if(strcasecmp(maybeType, allowedTypes[i]) == 0){
            return true;
        }
    }
    return false;
}

void readTableName(char *tableName){
    printf("Digite o nome da tabela:");
    scanf(" %[^\n]", tableName);
}

void readTableContent(FILE *table, char *tableContent, int maxSize){
    int bytesRead = fread(tableContent, sizeof(char), maxSize - 1, table);
    tableContent[bytesRead] = '\0';

    if (ferror(table)) {
        perror("Erro ao ler o conteúdo");
        fclose(table);
    }
}

void addColumnToFile(FILE *table, char *colType, char *colName){
    char format[MAX_COL_NAME + MAX_COL_TYPE + 5]; // 5 = strlen(" - \n") + 1 (null terminator)
    snprintf(format, sizeof(format), "%s - %s\n", colType, colName);
    fwrite(format, sizeof(char), strlen(format), table);
}

void readColumns(FILE *table){
    char colType[MAX_COL_TYPE];
    char colName[MAX_COL_NAME];

    while (true) {
        scanf("%s", colType);

        if (strcmp("stop", colType) == 0) {
            break;
        }

        scanf("%s", colName);

        if (typeAllowed(colType)) {
            char content[100];
            readTableContent(table, content, sizeof(content));
            if (isTableNameInUse(colName, content)) {
                printf("Nome de coluna já em uso\n");
            } else {
                addColumnToFile(table, colType, colName);
            }
        } else {
            printf("Digite um tipo válido\n");
        }
    }
}