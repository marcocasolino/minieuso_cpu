/* CPU data format definition 
 * for storage of packets coming from the Zynq board 
 * Francesca Capel: capel.francesca@gmail.com
 * NB:the Mini-EUSO CPU is LITTLE ENDIAN 
*/

#ifndef _DATA_FORMAT_H
#define _DATA_FORMAT_H

/* cpu file header */
typedef struct
{
  uint32_t header; /* 'CPU'(31:24) | instrument_id(23:16) | file_type(15:8) | file_ver(7:0) */
  uint32_t run_size; /* number of cpu packets in the run */
} CpuFileHeader; 


/* generic packet header for all cpu packets */
typedef struct
{
  uint32_t header; /* 'PKT_CPU'(31:24) | instrument_id(23:16) | pkt_type(15:8) | pkt_ver(7:0) */
  uint32_t pkt_size; /* size of packet */
  uint32_t pkt_num; /* counter for each pkt_type, reset each run */
} CpuPktHeader; 


#define INSTRUMENT_ME_PDM 1 /* Instrument Mini-EUSO PDM*/
#define RUN_SIZE 10
#define SCURVE_STEPS_MAX 100
#define SCURVE_ADDS_MAX 128
#define SCURVE_FRAMES_MAX (SCURVE_STEPS_MAX * SCURVE_ADDS_MAX)

/* macros for building the headers */
#define BuildCpuFileHeader(data_type, packet_ver) \
  (('CPU'<<24) | (INSTRUMENT_ME_PDM<<16) | ((file_type)<<8) | (file_ver))
#define BuildCpuPktHeader(data_type, packet_ver) \
  (('PKT_CPU'<<24) | (INSTRUMENT_ME_PDM<<16) | ((pkt_type)<<8) | (pkt_ver))


/* Timestamp structure in binary format */
/* Year 0=2017, 1=2018, 2=2019, 3=... */
typedef struct
{
  uint32_t cpu_time_stamp; // year(31:26) | month(25:22) | date(21:17) | hour(16:12) | min(11:6) | sec(5:0)
} CpuTimeStamp;

/* macro for building the timestamp */
#define BuildCpuTimeStamp(year, month, date, hour, min, sec) \
  (((year)<<26) | ((month)<<22) | ((date)<<17) | ((hour)<<12) | ((min)<<6) | (sec))

/* housekeeping packet for other data */
typedef struct
{
  CpuPktHeader hk_packet_header;
  CpuTimeStamp hk_time;
  float photodiode_data[4];
  float sipm_data[64];
  float sipm_single;
  float therm_data[16];
} HK_PACKET;

/* CPU packet for incoming data every 5.34 s */
typedef struct
{
  CpuPktHeader cpu_packet_header;
  CpuTimeStamp cpu_time;
  Z_DATA_TYPE_SCI_POLY_V5 zynq_packet;
  HK_PACKET hk_packet;
  //  uint32_t crc;
} CPU_PACKET;

/* scurve packet for checking pixels */
typedef struct
{
  CpuPktHeader sc_packet_header;
  CpuTimeStamp sc_time;
  uint16_t sc_start;
  uint16_t sc_step;
  uint16_t sc_stop;
  uint16_t sc_add;
  uint8_t sc_data [SCURVE_FRAMES_MAX][N_OF_PIXEL_PER_PDM];
} SCURVE_PACKET;


/* CPU file to store one run of ~40 min */
typedef struct
{
  CpuFileHeader cpu_file_header;
  SCURVE_PACKET scurve_packet;
  CPU_PACKET cpu_run_payload[RUN_SIZE];
} CPU_FILE;


#endif /* _DATA_FORMAT_H */
