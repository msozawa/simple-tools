#include "st_def.h"

int main( int ac, char *av[] )
{
    int iRet;
    int iEnd = ST_DEF_FALSE;
    struct timeval stTime;
    WINDOW *pstWin1=NULL, *pstWin2=NULL, *pstWin3=NULL;
    long lLRP=0, lLRB=0, lLTP=0, lLTB=0, lRRP=0, lRRB=0, lRTP=0, lRTB=0;
    char *sIfNames[ST_DEF_IFNUM] = { "eth1", "eth2" };

    chkExistIfName( ST_DEF_IFNUM, sIfNames );

    // create window
    iRet = createWindow( &pstWin1, &pstWin2, &pstWin3 );
    if ( iRet != ST_DEF_OK ) {
        return ( ST_DEF_NG );
    }

    // main loop
	while ( iEnd != ST_DEF_TRUE )
    {
        // init timeval
        stTime.tv_sec = ST_DEF_WAITSEC;
        stTime.tv_usec = ST_DEF_WAITUSEC;

        // wait events
        iRet = select( 0, NULL, NULL, NULL, &stTime );
        if ( iRet == -1 )
        {
            perror( "select()" );
            return ( ST_DEF_NG );
        }

#if 0 // DUMMY
        lLRP+=5;
        lLRB+=100;
        lLTP+=6;
        lLTB+=120;
        lRRP+=7;
        lRRB+=140;
        lRTP+=8;
        lRTB+=160;
#else
        // get stats
        lLRP = getStatVal( "eth1", STATPATH_RP ); // Left rx_packets
        lLRB = getStatVal( "eth1", STATPATH_RB ); // Left rx_bytes
        lLTP = getStatVal( "eth1", STATPATH_TP ); // Left tx_packets
        lLTB = getStatVal( "eth1", STATPATH_TB ); // Left tx_bytes
        lRRP = getStatVal( "eth2", STATPATH_RP ); // Right rx_packets
        lRRB = getStatVal( "eth2", STATPATH_RB ); // Right rx_bytes
        lRTP = getStatVal( "eth2", STATPATH_TP ); // Right tx_packets
        lRTB = getStatVal( "eth2", STATPATH_TB ); // Right tx_bytes
#endif

        // update stats
        updStat( pstWin1, pstWin2, pstWin3,
                 lLRP, lLRB, lLTP, lLTB, lRRP, lRRB, lRTP, lRTB );
    }

    // destroy window
    (void)destroyWindow( pstWin1, pstWin2, pstWin3 );

    return ( ST_DEF_OK );
}




