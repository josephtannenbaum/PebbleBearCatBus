#include "pebble.h"
#include "schedule.h"

#define PM_MINS "%d:%dpm (%d minutes)"
#define AM_MINS "%d:%dam (%d minutes)"
#define PM_MINS_ZMIN "%d:0%dpm (%d minutes)"
#define AM_MINS_ZMIN "%d:0%dam (%d minutes)"
#define PM_HRS "%d:%dpm (%d hrs, %d mins)"
#define AM_HRS "%d:%dam (%d hrs, %d mins)"
#define PM_HRS_ZMIN "%d:0%dpm (%d hrs, %d mins)"
#define AM_HRS_ZMIN "%d:0%dam (%d hrs, %d mins)"
#define NO_MORE_BUS "No more buses!"
  
#define BUS_TIME(v, hr, min, name) v->h = hr;v->m = min; v->n = name;

bus_time ** get_union_times(void) {
  bus_time ** union_times = (bus_time **) malloc(115 * sizeof(*union_times));
  for(int i=0; i<115;i++) union_times[i]=malloc(sizeof(struct bus_time)); 
  BUS_TIME(union_times[0],9,00, "WS")
  BUS_TIME(union_times[1],10,00, "WS")
  BUS_TIME(union_times[2],11,00, "WS")
  BUS_TIME(union_times[3],12,00, "WS")
  BUS_TIME(union_times[4],13,00, "WS")
  BUS_TIME(union_times[5],14,00, "WS")
  BUS_TIME(union_times[6],15,00, "WS")
  BUS_TIME(union_times[7],16,00, "WS")
  BUS_TIME(union_times[8],17,00, "WS")
  BUS_TIME(union_times[9],18,00, "WS")
  BUS_TIME(union_times[10],19,00, "WS")
  BUS_TIME(union_times[11],20,00, "WS")
  BUS_TIME(union_times[12],21,00, "WS")
  BUS_TIME(union_times[13],22,00, "WS")
  BUS_TIME(union_times[14],23,00, "WS")
  BUS_TIME(union_times[15],24,00, "WS")
  BUS_TIME(union_times[16],10,30, "LRS")
  BUS_TIME(union_times[17],11,30, "LRS")
  BUS_TIME(union_times[18],12,30, "LRS")
  BUS_TIME(union_times[19],13,30, "LRS")
  BUS_TIME(union_times[20],14,30, "LRS")
  BUS_TIME(union_times[21],15,30, "LRS")
  BUS_TIME(union_times[22],16,30, "LRS")
  BUS_TIME(union_times[23],17,30, "LRS")
  BUS_TIME(union_times[24],18,30, "LRS")
  BUS_TIME(union_times[25],19,30, "LRS")
  BUS_TIME(union_times[26],20,30, "LRS")
  BUS_TIME(union_times[27],21,30, "LRS")
  BUS_TIME(union_times[28],22,30, "LRS")
  BUS_TIME(union_times[29],23,30, "LRS")
  BUS_TIME(union_times[30],10,30, "DCR")
  BUS_TIME(union_times[31],11,30, "DCR")
  BUS_TIME(union_times[32],12,30, "DCR")
  BUS_TIME(union_times[33],13,30, "DCR")
  BUS_TIME(union_times[34],14,30, "DCR")
  BUS_TIME(union_times[35],15,30, "DCR")
  BUS_TIME(union_times[36],16,30, "DCR")
  BUS_TIME(union_times[37],17,30, "DCR")
  BUS_TIME(union_times[38],18,30, "DCR")
  BUS_TIME(union_times[39],19,30, "DCR")
  BUS_TIME(union_times[40],20,30, "DCR")
  BUS_TIME(union_times[41],21,30, "DCR")
  BUS_TIME(union_times[42],22,30, "DCR")
  BUS_TIME(union_times[43],23,30, "DCR")
  BUS_TIME(union_times[44],10,30, "RRT")
  BUS_TIME(union_times[45],11,30, "RRT")
  BUS_TIME(union_times[46],12,30, "RRT")
  BUS_TIME(union_times[47],13,30, "RRT")
  BUS_TIME(union_times[48],14,30, "RRT")
  BUS_TIME(union_times[49],15,30, "RRT")
  BUS_TIME(union_times[50],16,30, "RRT")
  BUS_TIME(union_times[51],17,30, "RRT")
  BUS_TIME(union_times[52],18,30, "RRT")
  BUS_TIME(union_times[53],19,30, "RRT")
  BUS_TIME(union_times[54],20,30, "RRT")
  BUS_TIME(union_times[55],21,30, "RRT")
  BUS_TIME(union_times[56],22,30, "RRT")
  BUS_TIME(union_times[57],10,00, "OAK")
  BUS_TIME(union_times[58],11,00, "OAK")
  BUS_TIME(union_times[59],12,00, "OAK")
  BUS_TIME(union_times[60],13,00, "OAK")
  BUS_TIME(union_times[61],14,00, "OAK")
  BUS_TIME(union_times[62],15,00, "OAK")
  BUS_TIME(union_times[63],16,00, "OAK")
  BUS_TIME(union_times[64],17,00, "OAK")
  BUS_TIME(union_times[65],18,00, "OAK")
  BUS_TIME(union_times[66],19,00, "OAK")
  BUS_TIME(union_times[67],20,00, "OAK")
  BUS_TIME(union_times[68],21,00, "OAK")
  BUS_TIME(union_times[69],22,00, "OAK")
  BUS_TIME(union_times[70],10,00, "UP")
  BUS_TIME(union_times[71],11,00, "UP")
  BUS_TIME(union_times[72],12,00, "UP")
  BUS_TIME(union_times[73],13,00, "UP")
  BUS_TIME(union_times[74],14,00, "UP")
  BUS_TIME(union_times[75],15,00, "UP")
  BUS_TIME(union_times[76],16,00, "UP")
  BUS_TIME(union_times[77],17,00, "UP")
  BUS_TIME(union_times[78],18,00, "UP")
  BUS_TIME(union_times[79],19,00, "UP")
  BUS_TIME(union_times[80],20,00, "UP")
  BUS_TIME(union_times[81],21,00, "UP")
  BUS_TIME(union_times[82],22,00, "UP")
  BUS_TIME(union_times[83],23,00, "UP")
  BUS_TIME(union_times[84],24,00, "UP")
  BUS_TIME(union_times[85],9,45, "CS")
  BUS_TIME(union_times[86],10,15, "CS")
  BUS_TIME(union_times[87],10,45, "CS")
  BUS_TIME(union_times[88],11,15, "CS")
  BUS_TIME(union_times[89],11,45, "CS")
  BUS_TIME(union_times[90],12,15, "CS")
  BUS_TIME(union_times[91],12,45, "CS")
  BUS_TIME(union_times[92],13,15, "CS")
  BUS_TIME(union_times[93],13,45, "CS")
  BUS_TIME(union_times[94],14,15, "CS")
  BUS_TIME(union_times[95],14,45, "CS")
  BUS_TIME(union_times[96],15,15, "CS")
  BUS_TIME(union_times[97],15,45, "CS")
  BUS_TIME(union_times[98],16,15, "CS")
  BUS_TIME(union_times[99],16,45, "CS")
  BUS_TIME(union_times[100],17,15, "CS")
  BUS_TIME(union_times[101],17,45, "CS")
  BUS_TIME(union_times[102],18,15, "CS")
  BUS_TIME(union_times[103],18,45, "CS")
  BUS_TIME(union_times[104],19,15, "CS")
  BUS_TIME(union_times[105],19,45, "CS")
  BUS_TIME(union_times[106],20,15, "CS")
  BUS_TIME(union_times[107],20,45, "CS")
  BUS_TIME(union_times[108],21,15, "CS")
  BUS_TIME(union_times[109],21,45, "CS")
  BUS_TIME(union_times[110],22,15, "CS")
  BUS_TIME(union_times[111],22,45, "CS")
  BUS_TIME(union_times[112],23,15, "CS")
  BUS_TIME(union_times[113],23,45, "CS")
  BUS_TIME(union_times[114],24,15, "CS")
  return union_times;
}

bus_time ** get_up_times(void){
  bus_time ** up_times = (bus_time **) malloc(22 * sizeof(*up_times));
  for(int i=0; i<22;i++) up_times[i]=malloc(sizeof(struct bus_time));
  BUS_TIME(up_times[0],10, 5, "UP")
  BUS_TIME(up_times[1],11,5, "UP")
  BUS_TIME(up_times[2],12,5, "UP")
  BUS_TIME(up_times[3],13,5, "UP")
  BUS_TIME(up_times[4],14,5, "UP")
  BUS_TIME(up_times[5],15,5, "UP")
  BUS_TIME(up_times[6],16,5, "UP")
  BUS_TIME(up_times[7],17,5, "UP")
  BUS_TIME(up_times[8],18,5, "UP")
  BUS_TIME(up_times[9],19,5, "UP")
  BUS_TIME(up_times[10],20,5, "UP")
  BUS_TIME(up_times[11],21,5, "UP")
  BUS_TIME(up_times[12],22,5, "UP")
  BUS_TIME(up_times[13],23,5, "UP")
  BUS_TIME(up_times[14],24,5, "UP")
  BUS_TIME(up_times[15],0,18, "DE")
  BUS_TIME(up_times[16],0,48, "DE")
  BUS_TIME(up_times[17],1,18, "DE")
  BUS_TIME(up_times[18],1,48, "DE")
  BUS_TIME(up_times[19],2,18, "DE")
  BUS_TIME(up_times[20],2,48, "DE")
  BUS_TIME(up_times[21],3,18, "DE")
  return up_times;
}

bus_time ** get_udc_times(void){
  bus_time ** udc_times = (bus_time **) malloc(30 * sizeof(*udc_times));
  for(int i=0; i<30;i++) udc_times[i]=malloc(sizeof(struct bus_time));
  BUS_TIME(udc_times[0],9,20, "WS")
  BUS_TIME(udc_times[1],10,20, "WS")
  BUS_TIME(udc_times[2],11,20, "WS")
  BUS_TIME(udc_times[3],12,20, "WS")
  BUS_TIME(udc_times[4],13,20, "WS")
  BUS_TIME(udc_times[5],14,20, "WS")
  BUS_TIME(udc_times[6],15,20, "WS")
  BUS_TIME(udc_times[7],16,20, "WS")
  BUS_TIME(udc_times[8],17,20, "WS")
  BUS_TIME(udc_times[9],18,20, "WS")
  BUS_TIME(udc_times[10],19,20, "WS")
  BUS_TIME(udc_times[11],20,20, "WS")
  BUS_TIME(udc_times[12],21,20, "WS")
  BUS_TIME(udc_times[13],22,20, "WS")
  BUS_TIME(udc_times[14],23,20, "WS")
  BUS_TIME(udc_times[15],24,20, "WS")
  BUS_TIME(udc_times[16],10,41, "DCR")
  BUS_TIME(udc_times[17],11,41, "DCR")
  BUS_TIME(udc_times[18],12,41, "DCR")
  BUS_TIME(udc_times[19],13,41, "DCR")
  BUS_TIME(udc_times[20],14,41, "DCR")
  BUS_TIME(udc_times[21],15,41, "DCR")
  BUS_TIME(udc_times[22],16,41, "DCR")
  BUS_TIME(udc_times[23],17,41, "DCR")
  BUS_TIME(udc_times[24],18,41, "DCR")
  BUS_TIME(udc_times[25],19,41, "DCR")
  BUS_TIME(udc_times[26],20,41, "DCR")
  BUS_TIME(udc_times[27],21,41, "DCR")
  BUS_TIME(udc_times[28],22,41, "DCR")
  BUS_TIME(udc_times[29],23,41, "DCR")
  return udc_times;
}

int fmt_time(char ** str, int h, int m, int th, int tm) {
  char * fmt_str; int mins=0; int m_delta=0,h_delta=0;
  m_delta = tm-m;
  h_delta = th-h;
  if (h == th || (th == h+1 && m_delta < 0)) { // _MINS
    mins=1;
    if (tm < 10) { // _ZMIN
      if (th > 12) {
        th -= 12;
        fmt_str = PM_MINS_ZMIN;    
      } else if (th == 12) {
        fmt_str = PM_MINS_ZMIN;
      } else {
        fmt_str = AM_MINS_ZMIN;
      }
    } else {
      if (th > 12) {
        th -= 12;
        fmt_str = PM_MINS;   
      } else if (th == 12) {
        fmt_str = PM_MINS;
      } else {
        fmt_str = AM_MINS;
      }
    }
  } else { // _HRS
    if (tm < 10) { // _ZMIN
      if (th > 12) {
        th -= 12;
        fmt_str = PM_HRS_ZMIN;       
      } else if (th == 12) {
        fmt_str = PM_HRS_ZMIN;
      } else {
        fmt_str = AM_HRS_ZMIN;
      }
    } else {
      if (th > 12) {
        th -= 12;
        fmt_str =  PM_HRS;       
      } else if (th == 12) {
        fmt_str = PM_HRS;
      } else {
        fmt_str = AM_HRS;
      }
    }
  }
  
  if (th == 99) {
    *str = malloc(strlen(NO_MORE_BUS)+2);
    snprintf(*str, strlen(NO_MORE_BUS)+1, NO_MORE_BUS);
    return 0;
  } else {
    if (m_delta < 0) {
      h_delta--;
      m_delta+=60;
    }
    *str = malloc(strlen(fmt_str)+3);
    if (mins) // we're just showing minutes-until
      snprintf(*str, strlen(fmt_str)+3, fmt_str, th,tm,m_delta );
    else
      snprintf(*str, strlen(fmt_str)+3, fmt_str, th,tm,h_delta,m_delta );
    
    return (h_delta * 60) + m_delta < 10;
  }
}

void get_closest(bus_time *** loc_times, int loc_times_size, const int num_results, char * ret[num_results], char * places[num_results], int * urgent, int h, int m, const int wd) {
  int hnext[num_results];
  int mnext[num_results];
  char * p[num_results]; 
  for(int i=0;i<num_results;i++) { 
    p[i] = "N/A";
    mnext[i] = 61;
    hnext[i] = 99;
  }
  int th, tm;
  for(int i = 0;i<loc_times_size;i++) {
    th = (*loc_times)[i]->h;
    tm = (*loc_times)[i]->m;
    if((th > h) || ((th == h) && (tm >= m))) {
      for(int j=0;j<num_results;j++) {
        if((th < hnext[j]) || ((th == hnext[j]) && (tm < mnext[j]))) { // ursurp slot
          for(int k=num_results-1;k>j;k--) { // move other slots down
            hnext[k] = hnext[k-1];
            mnext[k] = mnext[k-1];
            p[k] = p[k-1];
          }
          hnext[j] = th;
          mnext[j] = tm;
          p[j] = (*loc_times)[i]->n;
          break;
        }
      }
    }
  }
  for(int i=0;i<num_results;++i) {
    urgent[i] = fmt_time(&ret[i], h, m, hnext[i], mnext[i]);
    places[i] = malloc(4);
    snprintf(places[i], 4, "%s", p[i]);
  }
}

static char strftime_buffer[8];

void get_time_weekday(int * h, int * m, int * wd) {
  
  time_t now;
  now = time (NULL);
  struct tm *ts = localtime (&now);
  strftime (strftime_buffer, 100, "%w", ts);
  *wd = atoi(strftime_buffer);
  strftime (strftime_buffer, 100, "%H", ts);
  *h = atoi(strftime_buffer);
  strftime (strftime_buffer, 100, "%M", ts);
  *m = atoi(strftime_buffer);
}

void catbus_get_times(int loc, const int num_results, char * outtimes[num_results], char * places[num_results], int * urgent) {
  int h, m, wd,num_times=0; 
  get_time_weekday(&h, &m, &wd);
  //h=17;m=28;
  bus_time ** loc_times = NULL;
  switch (loc){
    case 0:
      loc_times = get_up_times();
      num_times = 22;
      break;
    case 1:
      loc_times = get_udc_times();
      num_times = 30;
      break;
    default:
      loc_times = get_union_times();
      num_times=115;
      break;
  }
  get_closest(&loc_times,num_times,num_results,outtimes,places,urgent,h,m,wd);
  for(int i=0; i<num_times;i++) free(loc_times[i]->n);
  for(int i=0; i<num_times;i++) free(loc_times[i]);
  free(loc_times);
}