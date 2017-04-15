#ifndef _GLOBALS_H
#define _GLOBALS_H

#define VERSION 1.3
#define VERSION_DATE_STRING "14/04/2017"

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <sys/mount.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <thread>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iostream>
#include <streambuf>

#include "cpu_functions.h"
#include "general.h"
#include "log.h"

/* definitions */
#define HOME_DIR "/home/software/CPU/"
#define CONFIG_FILE_USB "/media/usb/main_cpu.conf"
#define CONFIG_FILE_LOCAL "/home/software/CPU/CPUsoftware/config/main_cpu.conf"
//#define ZYNQ_IP "192.168.7.10"
//#define TELNET_PORT 23
/* for testing in stockholm */
#define ZYNQ_IP "130.237.34.97"
#define TELNET_PORT 5003

/* external variables */
extern std::string log_name;

#endif
