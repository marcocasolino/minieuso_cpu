/*-------------------------------
                                 
TEST CPU PROGRAM                 
V1.1: April 2017                 
                                 
Full PDM data acquisition chain	 
                                  
Francesca Capel                  
capel.francesca@gmail.com         
                                 
--------------------------------*/
#include "globals.h"

int main(void) {

  /* definitions */
  config config_out;
  
  /* start-up */
  printf("TEST CPU SOFTWARE Version: %.2f Date: %s\n", VERSION, VERSION_DATE_STRING);

  /* create the log file */
  std::ofstream log_file(log_name,std::ios::out);
  logstream clog(log_file, logstream::all);
  clog << std::endl;
  clog << "info: " << logstream::info << "log created" << std::endl;
  
  /* reload and parse the configuration file */
  std::string config_file = "../config/dummy.conf";
  std::string config_file_local = "../config/dummy_local.conf";
  config_out = configure(config_file, config_file_local);

  /* test the connection to the zynq board */
  check_telnet(ZYNQ_IP, TELNET_PORT);
  
  /* check the instrument and HV status */
  inst_status();
  hvps_status();

  /* turn on the HV */
  hvps_turnon(config_out.cathode_voltage, config_out.dynode_voltage);

  /* take an scurve */
  scurve(config_out.scurve_start, config_out.scurve_step, config_out.scurve_stop, config_out.scurve_acc);
  
  return 0; 
}


  
