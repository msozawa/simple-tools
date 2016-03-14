/*
 * header file include
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/stat.h>
#include <math.h>

/*
 * common definition
 */
#define ST_DEF_OK    0
#define ST_DEF_NG   -1

#define ST_DEF_TRUE  1
#define ST_DEF_FALSE 0

#define ST_DEF_BUFLEN  64
#define ST_DEF_MAX_PATH  256

#define ST_DEF_WAITSEC    1
#define ST_DEF_WAITUSEC   0

#define ST_DEF_IFNUM  2

/*
 * Usage:  STATPATH_L
 *        + ifname(ex. "eth0")
 *        + STATPATH_R 
 *        + STATPATH_xx
 * ex.) /sys/class/net/eth0/statistics/rx_packets
 */
#define STATPATH_L "/sys/class/net/"
#define STATPATH_R "/statistics/"
#define STATPATH_RP "rx_packets"
#define STATPATH_RB "rx_bytes"
#define STATPATH_RE "rx_errors"
#define STATPATH_RD "rx_dropped"
#define STATPATH_TP "tx_packets"
#define STATPATH_TB "tx_bytes"
#define STATPATH_TE "tx_errors"
#define STATPATH_TD "tx_dropped"

/*
 * color pair definition
 */
#define COL_BLK_RED 12
#define COL_BLK_GRN 13
#define COL_BLK_YLW 14
#define COL_BLK_BLU 15
#define COL_BLK_MGD 16
#define COL_BLK_CYN 17
#define COL_BLK_WHT 18

#define COL_RED_BLK 21
#define COL_RED_GRN 23
#define COL_RED_YLW 24
#define COL_RED_BLU 25
#define COL_RED_MGD 26
#define COL_RED_CYN 27
#define COL_RED_WHT 28

#define COL_GRN_BLK 31
#define COL_GRN_RED 32
#define COL_GRN_YLW 34
#define COL_GRN_BLU 35
#define COL_GRN_MGD 36
#define COL_GRN_CYN 37
#define COL_GRN_WHT 38

#define COL_YLW_BLK 41
#define COL_YLW_RED 42
#define COL_YLW_GRN 43
#define COL_YLW_BLU 45
#define COL_YLW_MGD 46
#define COL_YLW_CYN 47
#define COL_YLW_WHT 48

#define COL_BLU_BLK 51
#define COL_BLU_RED 52
#define COL_BLU_GRN 53
#define COL_BLU_YLW 54
#define COL_BLU_MGD 56
#define COL_BLU_CYN 57
#define COL_BLU_WHT 58

#define COL_MGD_BLK 61
#define COL_MGD_RED 62
#define COL_MGD_GRN 63
#define COL_MGD_YLW 64
#define COL_MGD_BLU 65
#define COL_MGD_CYN 67
#define COL_MGD_WHT 68

#define COL_CYN_BLK 71
#define COL_CYN_RED 72
#define COL_CYN_GRN 73
#define COL_CYN_YLW 74
#define COL_CYN_BLU 75
#define COL_CYN_MGD 76
#define COL_CYN_WHT 78

#define COL_WHT_BLK 81
#define COL_WHT_RED 82
#define COL_WHT_GRN 83
#define COL_WHT_YLW 84
#define COL_WHT_BLU 85
#define COL_WHT_MGD 86
#define COL_WHT_CYN 87

// debug
#define ST_DEF_DBG(str) {FILE *fp=fopen("dbg.log","a");fputs(str,fp);fclose(fp);}


/*
 * function definition
 */

// init.c
void initColorPair( void );

//windows.c
int destroyWindow( WINDOW *pstWin1, WINDOW *pstWin2, WINDOW *pstWin3 );
int createWindow( WINDOW **ppstWin1, WINDOW **ppstWin2, WINDOW **ppstWin3 );
void setCaption( WINDOW *pstWin1, WINDOW *pstWin2, WINDOW *pstWin3 );
void updStat( WINDOW *pstWin1, WINDOW *pstWin2, WINDOW *pstWin3,
              long lLRP, long lLRB, long lLTP, long lLTB,
              long lRRP, long lRRB, long lRTP, long lRTB );

// if.c
int chkExistIfName( int, char *[] );
int getStatVal( char *, char * );



