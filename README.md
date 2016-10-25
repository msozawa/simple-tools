# simple-tools
simple tools created for some test, or sample apps


## (1)simple_tra_mon

A simple traffic monitor from/to eth1 and eth2.
  This application is confirmed to run on CentOS6.5 and 7 with ncurses library.
  
  if you want to monitor except eth1/eth2, modify the following part of "main.c".

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

after, this app starts to monitor trrafic and you can see like following screen.

![スクリーンショット](https://github.com/msozawa/pics/blob/master/stm_screen_shot.png "スクリーンショット")
