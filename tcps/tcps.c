/*********************************************************************
 *
 *  T C P S
 *  TCP Server dump receive data HEX and ASCII
 *
 *  Create: 2016/11/16  M.Ozawa
 *
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define  BUFSIZE  8192
#define  OK          0
#define  NG         -1


/* display string HEX dump and ascii */
void dumpStr( char * pcStr )
{
    char sBuf[BUFSIZE];
    int  iCnt = 0;
    int  iCnt2 = 0;
    char sDispBuf[80];

    memset( sBuf, 0x00, sizeof(sBuf) );
    if ( pcStr != NULL ) {
        strcpy( sBuf, pcStr ); 
    }
    memset( sDispBuf, 0x20, sizeof(sDispBuf) );
    sDispBuf[sizeof(sDispBuf)-1] = 0x00;

    while ( 1 )
    {
        if ( sBuf[iCnt] == '\0' ) {
            printf( "%s\n", sDispBuf );
            break;
        }

        sprintf( &sDispBuf[iCnt2 * 3], "%2.02x ", sBuf[iCnt] );
        sDispBuf[(iCnt2*3)+3] = 0x20;
        if ( 
          ( sBuf[iCnt] == '\r' ) || 
          ( sBuf[iCnt] == 0x20 ) || 
          ( sBuf[iCnt] == '\t' ) || 
          ( sBuf[iCnt] == '\n' ) )
        {
            sDispBuf[iCnt2+50] = '.';
        } else {
            sDispBuf[iCnt2+50] = sBuf[iCnt];
        }
    
        iCnt ++;
        iCnt2 ++;

        if ( ( iCnt % 16 ) == 0 ) {
            printf( "%s\n", sDispBuf );
            memset( sDispBuf, 0x20, sizeof(sDispBuf) );
            sDispBuf[sizeof(sDispBuf)-1] = 0x00;
            iCnt2 = 0;
        }
    }

    return;
}


/* main() */
int main( int ac, char *av[] )
{
    int iSoc;
    struct sockaddr_in stAddr;
    struct sockaddr_in stClient;
    socklen_t iLen;
    int iClSoc;
    struct timeval stTO;
    int iPort = 0;

    char sBuf [BUFSIZE];

    stTO.tv_sec = 1;
    stTO.tv_usec = 0;

    /* parameter check */
    if ( ac != 2 ) {
        perror( "you must set 1st parameter as port number." );
        return ( NG );
    } else {
        if ( ( iPort = atoi( av[1] ) ) == 0 ) {
            perror( "you must set 1st parameter as port number." );
            return ( NG );
        }
    }

    /* create listen socket */
    iSoc = socket( AF_INET, SOCK_STREAM, 0 );
    if ( iSoc < 0 )
    {
        perror( "socket()" );
        return ( NG );
    }

    stAddr.sin_family = AF_INET;
    stAddr.sin_port = htons( iPort );
    stAddr.sin_addr.s_addr = INADDR_ANY;

    /* set socket option */
    setsockopt( iSoc, 
                SOL_SOCKET, 
                SO_REUSEADDR, 
                (const char *)&stTO, 
                sizeof(struct timeval) );

    /* bind address to socket */
    if ( bind( iSoc, (struct sockaddr *)&stAddr, sizeof(stAddr) ) != 0 )
    {
        perror( "bind()" );
        return ( NG );
    }

    /* listen using socket */
    if ( listen( iSoc, 10 ) != 0 )
    {
        perror( "listen()" );
        return ( NG );
    }

    while ( 1 )
    {
        /* accept from client */
        iLen = sizeof( stClient );
        iClSoc = accept( iSoc, (struct sockaddr *)&stClient, &iLen );
        if ( iClSoc < 0 )
        {
            perror( "accept()" );
            break;
        }

        memset( sBuf, 0x00, sizeof(sBuf) );
        recv( iClSoc, sBuf, sizeof(sBuf), 0 );
#if 0
        printf( "%s", sBuf );
#else
        dumpStr( sBuf );
#endif

        send( iClSoc, sBuf, (int)strlen( sBuf ), 0 );

        close( iClSoc );
    }

    close( iSoc );

    return 0;
}

