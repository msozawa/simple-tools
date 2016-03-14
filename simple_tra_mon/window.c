#include "st_def.h"

void dispGraph( WINDOW *pstWin,
                long lPre, long lNow, int iY, int iX );
/*
 * void setCaption()
 */
void setCaption( WINDOW *pstWin1, WINDOW *pstWin2, WINDOW *pstWin3 )
{
    wattron( pstWin1, COLOR_PAIR(COL_MGD_BLK) );
    mvwprintw( pstWin1,  1, 1, "Left Interface Rx Packets" );
    mvwprintw( pstWin1, 11, 1, "Left Interface Tx Packets" );
    wrefresh( pstWin1 );
    wattroff( pstWin1, COLOR_PAIR(COL_MGD_BLK) );

    wattron( pstWin1, COLOR_PAIR(COL_CYN_BLK) );
    mvwprintw( pstWin1,  6, 1, "Left Interface Rx Bytes" );
    mvwprintw( pstWin1, 16, 1, "Left Interface Tx Bytes" );
    wrefresh( pstWin1 );
    wattroff( pstWin1, COLOR_PAIR(COL_CYN_BLK) );

    wattron( pstWin2, COLOR_PAIR(COL_MGD_BLK) );
    mvwprintw( pstWin2,  1, 1, "Right Interface Rx Packets" );
    mvwprintw( pstWin2, 11, 1, "Right Interface Tx Packets" );
    wrefresh( pstWin2 );
    wattroff( pstWin2, COLOR_PAIR(COL_MGD_BLK) );

    wattron( pstWin2, COLOR_PAIR(COL_CYN_BLK) );
    mvwprintw( pstWin2,  6, 1, "Right Interface Rx Bytes" );
    mvwprintw( pstWin2, 16, 1, "Right Interface Tx Bytes" );
    wrefresh( pstWin2 );
    wattroff( pstWin2, COLOR_PAIR(COL_CYN_BLK) );

    mvwprintw(pstWin3, 1, 1, "*** simple traffic I/F monitor ***" );
#if 0
    mvwprintw(pstWin3, 2, 1, "Copyright(C) 2015 M.Ozawa All rights reserved." );
#endif
    wrefresh( pstWin3 );

    return;
}

/*
 * void updStat()
 */
void updStat( WINDOW *pstWin1, WINDOW *pstWin2, WINDOW *pstWin3,
              long lLRP, long lLRB, long lLTP, long lLTB,
              long lRRP, long lRRB, long lRTP, long lRTB )
{
    time_t stTime = time( NULL );
    struct tm *pstNow = localtime( &stTime );
    static long lPreLRP, lPreLRB, lPreLTP, lPreLTB,
                lPreRRP, lPreRRB, lPreRTP, lPreRTB;

    // display current time on window3
    mvwprintw( pstWin3, 1, 54, "%d/%2d/%2d %02d:%02d:%02d",
               pstNow->tm_year + 1900,
               pstNow->tm_mon + 1,
               pstNow->tm_mday, pstNow->tm_hour,
               pstNow->tm_min, pstNow->tm_sec );
    wrefresh( pstWin3 );

    // display stats on window1
    dispGraph( pstWin1, lPreLRP, lLRP,  2, 3 );
    dispGraph( pstWin1, lPreLRB, lLRB,  7, 3 );
    dispGraph( pstWin1, lPreLTP, lLTP, 12, 3 );
    dispGraph( pstWin1, lPreLTB, lLTB, 17, 3 );

    mvwprintw( pstWin1,  4, 3, "[%12ld]", lLRP );
    mvwprintw( pstWin1,  9, 3, "[%12ld]", lLRB );
    mvwprintw( pstWin1, 14, 3, "[%12ld]", lLTP );
    mvwprintw( pstWin1, 19, 3, "[%12ld]", lLTB );
    wrefresh( pstWin1 );

    // display stats on window2
    dispGraph( pstWin2, lPreRRP, lRRP,  2, 3 );
    dispGraph( pstWin2, lPreRRB, lRRB,  7, 3 );
    dispGraph( pstWin2, lPreRTP, lRTP, 12, 3 );
    dispGraph( pstWin2, lPreRTB, lRTB, 17, 3 );

    mvwprintw( pstWin2,  4, 3, "[%12ld]", lRRP );
    mvwprintw( pstWin2,  9, 3, "[%12ld]", lRRB );
    mvwprintw( pstWin2, 14, 3, "[%12ld]", lRTP );
    mvwprintw( pstWin2, 19, 3, "[%12ld]", lRTB );
    wrefresh( pstWin2 );

	// keep pre value
    lPreLRP = lLRP;
    lPreLRB = lLRB;
    lPreLTP = lLTP;
    lPreLTB = lLTB;
    lPreRRP = lRRP;
    lPreRRB = lRRB;
    lPreRTP = lRTP;
    lPreRTB = lRTB;

    return;
}

void dispGraph( WINDOW *pstWin,
                long lPre, long lNow, int iY, int iX )
{
    double dNum = (double)( lNow - lPre );
    int iDigit = (int)log10( dNum ) + 1;
    double dScale = pow( 10, (double)iDigit );
    double dPerMem = 0;
    double dLen = 0;
    int iCnt = 0;

    mvwprintw( pstWin, iY, (iX), "0" );
    mvwprintw( pstWin, iY, (iX+6), "%10d", (int)(dScale/2) );
    mvwprintw( pstWin, iY, (iX+20), "%10d", (int)dScale );
    wrefresh( pstWin );

    if ( dScale > 0 ) {
        dPerMem = ( dScale / 30 );
    } else {
        dPerMem = 0;
    }

    if ( dPerMem != 0 ) {
        dLen = ( dNum / dPerMem );
        if ( dLen == 0 ) {
            dLen++;
        }
    } else {
        dLen = 0;
    }

    wattron( pstWin, COLOR_PAIR(COL_BLK_YLW) );
    mvwprintw( pstWin, iY+1, iX, "                              " );
    wrefresh( pstWin );
    wattroff( pstWin, COLOR_PAIR(COL_BLK_YLW) );

    if ( ( dLen > 0 ) && ( dLen <= 30 ) )
    {
        wattron( pstWin, COLOR_PAIR(COL_BLK_BLU) );
        for ( iCnt = 0; iCnt < (int)dLen; iCnt++ )
        {
            mvwprintw( pstWin, iY+1, iX+iCnt, " " );
        }
        wrefresh( pstWin );
        wattroff( pstWin, COLOR_PAIR(COL_BLK_BLU) );
    }

    return;
}


/*
 * int destroyWindow()
 */
int destroyWindow( WINDOW *pstWin1, WINDOW *pstWin2, WINDOW *pstWin3 )
{
    delwin(pstWin1);
    delwin(pstWin2);
    delwin(pstWin3);
    
    endwin();
	return ( ST_DEF_OK );
}

/*
 * int createWindow()
 */
int createWindow( WINDOW **ppstWin1, WINDOW **ppstWin2, WINDOW **ppstWin3 )
{
    // initialize screen 
    if ( initscr() == NULL ) {
        perror( "initscr()" );
        return ( ST_DEF_NG );
    }

#if 0
    if ( LINES < 50 || COLS < 80 ) {   
		endwin();
        fprintf( stderr, "please expand your display size...\n" );
        return ( ST_DEF_NG );
    }   
#endif

    if ( has_colors() == FALSE ) {
        endwin();
        fprintf( stderr, "your terminal does not support color...\n" );
        return ( ST_DEF_NG );
    }

    cbreak();
    noecho();
    start_color();
    initColorPair();

    *ppstWin1 = newwin( 22, 37, 0, 0 );
    if( *ppstWin1 == NULL ) {
        perror( "newwin()" );
        return ( ST_DEF_NG );
    }
    box( *ppstWin1, ACS_VLINE, ACS_HLINE );

    *ppstWin2 = newwin( 22, 37, 0, 37 );
    if( *ppstWin2 == NULL ) {
        perror( "newwin()" );
        return ( ST_DEF_NG );
    }
    box( *ppstWin2, ACS_VLINE, ACS_HLINE );

    *ppstWin3 = newwin( 4, 74, 22, 0 );
    if( *ppstWin3 == NULL ) {
        perror( "newwin()" );
        return ( ST_DEF_NG );
    }
    box( *ppstWin3, ACS_VLINE, ACS_HLINE );

    // set initial value (all zero)
    setCaption( *ppstWin1, *ppstWin2, *ppstWin3 );
    updStat( *ppstWin1, *ppstWin2, *ppstWin3, 0, 0, 0, 0, 0, 0, 0, 0 );

	return ( ST_DEF_OK );
}

