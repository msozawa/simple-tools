# simple-tools
simple tools created for some test, or sample apps


## (1)simple_tra_mon

  A simple traffic monitor from/to eth1 and eth2.
  This application is confirmed to run on CentOS6.5 and 7 with ncurses library.
  
  If you want to monitor except eth1/eth2, modify the following code of "main.c".
  In this code, Left I/F is "eth1" and Right I/F is "eth2".
  (This app watch files in "/sys/class/net/{I/F name}/statistics/".)

  ```c
lLRP = getStatVal( "eth1", STATPATH_RP ); // Left rx_packets
lLRB = getStatVal( "eth1", STATPATH_RB ); // Left rx_bytes
lLTP = getStatVal( "eth1", STATPATH_TP ); // Left tx_packets
lLTB = getStatVal( "eth1", STATPATH_TB ); // Left tx_bytes
lRRP = getStatVal( "eth2", STATPATH_RP ); // Right rx_packets
lRRB = getStatVal( "eth2", STATPATH_RB ); // Right rx_bytes
lRTP = getStatVal( "eth2", STATPATH_TP ); // Right tx_packets
lRTB = getStatVal( "eth2", STATPATH_TB ); // Right tx_bytes
  ```


### compile
$ make

### run
$ ./simple_tra_mon

then, this app starts to monitor trrafic and you can see like following screen.

![スクリーンショット](https://github.com/msozawa/pics/blob/master/stm_screen_shot.png "スクリーンショット")


## (2)tcps

  This program behaves as TCP Server and dumps received data as HEX and ASCII.
  (Invisible character (space, tab, newline(0x13, 0x10)) are displayed as '.')

  ```
$ ./tcps 22222
(then, this program is received HTTP GET request...)
47 45 54 20 2f 20 48 54 54 50 2f 31 2e 31 0d 0a   GET./.HTTP/1.1..             
48 6f 73 74 3a 20 31 32 37 2e 30 2e 30 2e 31 3a   Host:.127.0.0.1:             
32 32 32 32 32 0d 0a 41 63 63 65 70 74 3a 20 2a   22222..Accept:.*             
2f 2a 0d 0a 41 63 63 65 70 74 2d 4c 61 6e 67 75   /*..Accept-Langu             
61 67 65 3a 20 6a 61 2d 6a 70 0d 0a 43 6f 6e 6e   age:.ja-jp..Conn             
65 63 74 69 6f 6e 3a 20 6b 65 65 70 2d 61 6c 69   ection:.keep-ali             
76 65 0d 0a 41 63 63 65 70 74 2d 45 6e 63 6f 64   ve..Accept-Encod             
69 6e 67 3a 20 67 7a 69 70 2c 20 64 65 66 6c 61   ing:.gzip,.defla             
74 65 0d 0a 55 73 65 72 2d 41 67 65 6e 74 3a 20   te..User-Agent:.             
52 65 73 74 65 64 2f 32 30 30 39 20 43 46 4e 65   Rested/2009.CFNe             
74 77 6f 72 6b 2f 38 30 37 2e 30 2e 34 20 44 61   twork/807.0.4.Da             
72 77 69 6e 2f 31 36 2e 30 2e 30 20 28 78 38 36   rwin/16.0.0.(x86             
5f 36 34 29 0d 0a 0d 0a                           _64)....   
  ```
  
### compile
$ cc tcps.c -o tcps

### run
$ ./tcps port-number
