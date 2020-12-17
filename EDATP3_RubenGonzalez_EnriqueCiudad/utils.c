#include "utils.h"

void replaceExtensionByIdx(const char * fileName, char * indexName)
{

	int i;

    if(!fileName || !indexName) return;

	for(i = 0; fileName[i]!='.'; i++){
	    indexName[i]=fileName[i];
	}
	
	indexName[i]= '\0';

	strcat(indexName, ".idx");

    return;
}

bool createTable(const char * tableName) 
{

    FILE *f = NULL;
    char *indexName = NULL;
    int r = NO_DELETED_REGISTERS;
    bool b;

    if(!tableName)
    {
        return false;
    }

    f = fopen(tableName, "rb");

    if(f)
    {
        fclose(f);
        return true;
    }

    f = fopen(tableName, "wb");

    if(!f)
    {
        return false;
    }
    
    fwrite(&r, sizeof(r), 1, f);

    fclose(f);

    indexName = (char *)malloc(strlen(tableName) + 1);

    if(!indexName)
    {
        return false;
    }

    replaceExtensionByIdx(tableName, indexName);

    if((b = createIndex(indexName))==false) return false;
    return b;
    }

bool createIndex(const char *indexName) 
{
    FILE *f = NULL;
    int i = NO_DELETED_REGISTERS;
    
    if(!indexName)
    {
        return false;
    }

    f = fopen(indexName, "r");

    if (f != NULL)
    {
        fclose(f);
        return true;
    }

    f = fopen(indexName, "wb");
    
    if(!f)
    {
        return false;
    }

    fwrite(&i, sizeof(i), 1, f);

    fwrite(&i, sizeof(i), 1, f);
    
    fclose(f);
    return true;
}

void printnode( size_t _level,size_t level,   FILE * indexFileHandler, int node_id, char side)
{
    
	int i,d, id_izq, id_derch,dad, offset;
    char primary[PK_SIZE];
	
	if(!indexFileHandler || level>_level)
    {
        return;
    }

	offset=INDEX_HEADER_SIZE+(node_id)*(4*sizeof(int)+sizeof(primary));
	
	fseek(indexFileHandler, offset,SEEK_SET );

	fread(primary, sizeof(primary), 1,indexFileHandler);

	fread(&id_izq, sizeof(int), 1, indexFileHandler);

	fread(&id_derch, sizeof(int), 1, indexFileHandler);

	fread(&dad, sizeof(int), 1, indexFileHandler);

	fread(&d, sizeof(int), 1,indexFileHandler);
	
	
	for(i=0; i < (int)level; i++)
    {
		printf("\t");
	}

    printf("%c %s (%d) : %d\n", side, primary, node_id, d);

	if(id_izq!=-1) printnode( _level,level+1, indexFileHandler, id_izq, 'l');
	if(id_derch!=-1) printnode( _level, level+1, indexFileHandler, id_derch, 'r');
	
	return;    
}

void printTree(size_t level, const char * indexName)
{
    
    FILE *f;
	int raiz;

    if(!indexName)
    {
        return;
    }

	f=fopen(indexName, "rb");
    if(!f) return;
	fread(&raiz, sizeof(int),1,f);

	if (raiz!=-1)
    {
        printnode(level,0, f,raiz, ' ');
    }

	fclose(f);

    return;
}

bool findKey(const char * book_id, const char * indexName, int * nodeIDOrDataOffset)
{

	FILE *f;
	int node,aux=-1, v, offset;
	char primary[PK_SIZE];

    if(!indexName || !book_id || !nodeIDOrDataOffset) return false;

	f=fopen(indexName, "rb");
	
	if(!f) return false;

	while(1)
    {

        fread(&node, sizeof(node),1,f);

        if(node==-1)
        {
            *nodeIDOrDataOffset=aux;
            fclose(f);
            return false;
        }
        
        aux=node;

        offset=INDEX_HEADER_SIZE+(node)*(4*sizeof(node)+sizeof(primary));
        
        fseek(f, offset,SEEK_SET );

        fread(primary, sizeof(primary), 1,f);

        v=strncmp(book_id, primary, PK_SIZE);


        if(v==0)
        {

            fseek(f, 3*sizeof(node), SEEK_CUR);

            fread(&offset, sizeof(offset), 1, f);

            *nodeIDOrDataOffset=offset;

            return true;
        }	

        else if (v > 0)
        {
            fseek(f, sizeof(node),SEEK_CUR);
        }
	}
	
 }

/*SALEN WARNING PORQUE NO LAS HEMOS IMPLEMENTADO*/
bool addTableEntry(Book * book, const char * tableName, const char * indexName)
{
    /*
    int *nodeIDOrDataoffset;
    int i;
    if((findKey(book->book_id, indexName, nodeIDOrDataoffset)) == true)
    {
        printf("ERROR");
        return false;
    } 
    tableName = fopen(tableName, "rb");
    if(!tableName) return false;
	fread(&i, sizeof(int),1,tableName);
    if(i != NO_DELETED_REGISTERS);    
    */
}

bool addIndexEntry(char * book_id, int bookOffset, const char * indexName)
{
     return true;
}

