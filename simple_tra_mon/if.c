#include "st_def.h"


/*
 *
 */
int chkExistIfName( int iIfCnt, char * pcIfName[] )
{
    struct stat stStat;
    char sStatPath[ST_DEF_MAX_PATH+1];
    int iCnt = 0;

    for ( iCnt = 1; iCnt < iIfCnt; iCnt++ )
    {
        memset( &stStat, 0x00, sizeof(struct stat) );
        memset( sStatPath, 0x00, sizeof(sStatPath) );
        sprintf( sStatPath, "%s%s", STATPATH_L, pcIfName[iCnt] );
        if ( -1 == stat( sStatPath, &stStat ) )
        {
            fprintf( stderr, "interface %s does not exist...\n", 
                     pcIfName[iCnt] );
            return ( ST_DEF_NG );
        }
    }
    return( ST_DEF_OK );
}


/*
 *
 */
int getStatVal( char * pcIfName, char * pcStatKind )
{
    int iRet = 0;
    FILE * fp = NULL;
    char sStatPath[ST_DEF_MAX_PATH+1];
	char sRetBuf[ST_DEF_BUFLEN+1];

    memset( sStatPath, 0x00, sizeof(sStatPath) );
    sprintf( sStatPath, "%s%s%s%s", 
              STATPATH_L, pcIfName, STATPATH_R, pcStatKind );

    memset( sRetBuf, 0x00, sizeof(sRetBuf) );
    fp = fopen( sStatPath, "r" );
    if ( fp == NULL )
    {
        perror( "fopen()" );
        return ( ST_DEF_NG );
    }
    
    fgets( sRetBuf, ST_DEF_BUFLEN, fp );

    iRet = atoi( sRetBuf );

    if ( EOF == fclose( fp ) )
    {
        perror( "fclose()" );
        return ( ST_DEF_NG );
    }

    return ( iRet );
}
		
