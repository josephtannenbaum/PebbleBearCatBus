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

void fmt_time(char ** str, int h, int m, int th, int tm) {
  char * fmt_str; int mins=0; int m_delta=0,t_delta=0;
  if (h == th) { // _MINS
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
    return;
  } else {
    m_delta = tm-m;
    t_delta = th-h;
    if (m_delta < 0) {
      t_delta--;
      m_delta+=60;
    }
    *str = malloc(strlen(fmt_str)+3);
    if (mins) // we're just showing minutes-until
      snprintf(*str, strlen(fmt_str)+3, fmt_str, th,tm,m_delta );
    else
      snprintf(*str, strlen(fmt_str)+3, fmt_str, th,tm,t_delta,m_delta );
  }
}

void get_three_closest(bus_time *** loc_times, int loc_times_size, char * ret[5], char * places[5], int h, int m, const int wd) {
  /*int h1=99,h2=99,h3=99;
  int m1=61,m2=61,m3=61;
  char * p1="ERR";
  char *p2="ERR";
  char *p3="ERR";
  int th, tm;
  for(int i = 0;i<loc_times_size;i++) {
    th = (*loc_times)[i]->h;
    tm = (*loc_times)[i]->m;
    if((th > h) || ((th == h) && (tm >= m))) {
      if((th < h1) || ((th == h1) && (tm < m1))) { // case: ursurp slot 1
        h3 = h2;h2 = h1; // move lower two down
        m3 = m2;m2 = m1;
        p3=p2;p2=p1;
        
        h1=th;
        m1=tm;
        p1 = (*loc_times)[i]->n;
      } else if ((th < h2) || ((th == h2) && (tm < m2))) {// case: ursurp slot 2
        h3 = h2; // move second slot down
        m3 = m2;
        p3 = p2;
        
        h2 = th;
        m2 = tm;
        p2 = (*loc_times)[i]->n;
      } else if ((th < h3) || ((th == h3) && (tm < m3))) {// case: ursurp slot 3
        h3 = th; // just overwrite
        m3 = tm;
        p3 = (*loc_times)[i]->n;
      }
    }
  }
  
  fmt_time(&ret[0], h, m, h1, m1);
  fmt_time(&ret[1], h, m, h2, m2);
  fmt_time(&ret[2], h, m, h3, m3);
  
  places[0] = malloc(4);
  snprintf(places[0], 4, "%s", p1);
  places[1] = malloc(4);
  snprintf(places[1], 4, "%s", p2);
  places[2] = malloc(4);
  snprintf(places[2], 4, "%s", p3);*/
  // OLD
  // NEW
  int hnext[5];
  int mnext[5];
  char * p[5]; 
  for(int i=0;i<5;i++) { 
    p[i] = "ERR";
    mnext[i] = 61;
    hnext[i] = 99;
  }
  int th, tm;
  for(int i = 0;i<loc_times_size;i++) {
    th = (*loc_times)[i]->h;
    tm = (*loc_times)[i]->m;
    if((th > h) || ((th == h) && (tm >= m))) {
      for(int j=0;j<5;j++) {
        if((th < hnext[j]) || ((th == hnext[j]) && (tm < mnext[j]))) { // ursurp slot
          for(int k=4-j;k>j;k--) { // move other slots down
            hnext[k] = hnext[k-1];
            mnext[k] = mnext[k-1];
            p[k] = p[k-1];
          }
          hnext[j] = th;
          mnext[j] = tm;
          p[j] = (*loc_times)[i]->n;
        }
      }
    }
  }
  for(int i=0;i<5;++i) {
    fmt_time(&ret[i], h, m, hnext[i], mnext[i]);
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

void catbus_get_times(int loc, char * outtimes[5], char * places[5]) {
  int h, m, wd,num_times=0; 
  get_time_weekday(&h, &m, &wd);
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
  }
  get_three_closest(&loc_times, num_times, outtimes, places, h,m,wd);
  for(int i=0; i<num_times;i++) free(loc_times[i]->n);
  for(int i=0; i<num_times;i++) free(loc_times[i]);
  free(loc_times);
}