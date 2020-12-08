#include "utils.h"
#include <stdlib.h>
#include <string.h>

int no_deleted_registers = NO_DELETED_REGISTERS;

void replaceExtensionByIdx(const char *fileName, char * indexName) 
{
    int i;

    for(i=0; fileName[i]!='.'; i++){
        indexName[i] = fileName[i];
    }

    indexName[i] = '\0';
    
    strcat(indexName, ".idx");

    return;
}


bool createTable(const char * tableName) 
{

    FILE *f = NULL;
    int i = NO_DELETED_REGISTERS;
    char *indexname = NULL;
    if(!tableName){
        return false;
    }

    f = fopen(tableName, "rb");

    if(!f)
    {
        f = fopen(tableName, "wb");
        
        if(!f)
        {
            fclose(f);
            return false;
        }

        fwrite(&i, sizeof(i), 1, f);
        fclose(f);

        indexname = (char *) malloc(strlen(tableName) +1);
        
        if(!indexname)
        {
            return false;
        } 
        
        replaceExtensionByIdx(tableName, indexname);
    
        
        return createIndex(indexname);
    }

    fclose(f);
    return true;
}

bool createIndex(const char *indexName) 
{
	FILE *f=NULL;

	int i=NO_DELETED_REGISTERS;

	if(indexName==NULL) return false;

	f=fopen(indexName, "r");

	if(f){
	fclose(f);
	return true;
	}

	f=fopen(indexName, "wb");
	if(!f) return false;

	fwrite(&i, sizeof(i), 1, f);
	fwrite(&i, sizeof(i), 1, f);

	fclose(f);

	return true;
}
void printnode(size_t _level, size_t level,
               FILE * indexFileHandler, int node_id, char side) {
    int aux, i, reet;
    char c[PK_SIZE];

    if(level < 0 || !indexFileHandler){
        return;
    }

    fread(&aux, sizeof(aux), 1, indexFileHandler);

    fread(&aux, sizeof(aux), 1, indexFileHandler);
    reet = 1;

    for(i=0; i < node_id && reet == 1; i++){
        reet = fread(&c, sizeof(c), 1, indexFileHandler);

        reet = fread(&aux, sizeof(aux), 1, indexFileHandler);

        reet = fread(&aux, sizeof(aux), 1, indexFileHandler);

        reet = fread(&aux, sizeof(aux), 1, indexFileHandler);

        reet = fread(&aux, sizeof(aux), 1, indexFileHandler);
    }

    for(i = 0; i < level; i++){
        printf("\t");
    }

    printf("%c %s (%d): %d", side, c, node_id, aux);

    return;
}

void printTree(size_t level, const char * indexName)
{
    return;
}

bool findKey(const char * book_id, const char *indexName,
             int * nodeIDOrDataOffset)
 {
     return true;
 }

bool addIndexEntry(char * book_id,  int bookOffset, char const * indexName) {
    return true;
}

bool addTableEntry(Book * book, const char * dataName,
                   const char * indexName) {
    return true;
}