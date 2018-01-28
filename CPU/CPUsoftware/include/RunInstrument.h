#ifndef _RUN_INSTRUMENT_H
#define _RUN_INSTRUMENT_H

#include "LvpsManager.h"
#include "UsbManager.h"
#include "CamManager.h"
#include "DataAcqManager.h"

/* number of seconds CPU waits for other systems to boot */
#define BOOT_TIME 4

/* location of data files */
#define HOME_DIR "/home/software/CPU"
#define DONE_DIR "/home/minieusouser/DONE"
#define DATA_DIR "/home/minieusouser/DATA"

/* software version and date */
#define VERSION 4.5
#define VERSION_DATE_STRING "28/01/2018"

/* class to handle different instrument operational modes */
class RunInstrument {
public:
  CmdLineInputs * CmdLine;
  enum InstrumentMode : uint8_t {
    NIGHT = 0,
    DAY = 1,
    INST_UNDEF = 2,
  };
  InstrumentMode current_inst_mode;
  enum AcquisitionMode : uint8_t {
    STANDARD = 0,
    SCURVE = 1,
    ACQ_UNDEF = 2,
  };
  AcquisitionMode current_acq_mode;

  Config * ConfigOut;
  ZynqManager Zynq;
  LvpsManager Lvps;
  UsbManager Usb;
  CamManager Cam;
  DataAcqManager Daq;

  int check_telnet;
  
  RunInstrument(CmdLineInputs * CmdLine);
  int Start();
  //int Stop();
  
private:
  int StartUp();

  /* execute-and-exit commands */
  int LvpsSwitch();
  int HvpsSwitch();
  int DebugMode();

  /* initialisation */
  int SetInstMode();
  int CheckSystems();
  int SelectAcqOption();

  /* used in operations */
  int LaunchCam();
  int MonitorLightLevel();
  int Acquisition();
 
  /* define main operational procedures */
  int NightOperations();
  int DayOperations();
};

#endif
/* _RUN_INSTRUMENT_H */
