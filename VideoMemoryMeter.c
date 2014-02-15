/*
htop - VideoMemoryMeter.c
(C) 2014 ...
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

#include "VideoMemoryMeter.h"

#include "CRT.h"
#include "ProcessList.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/param.h>
#include <assert.h>

/*{
#include "Meter.h"
}*/

int VideoMemoryMeter_attributes[] = {
   MEMORY_USED
};

static void VideoMemoryMeter_setValues(Meter* this, char* buffer, int size) {
   long int usedMem = this->pl->usedVMem << 2;
   this->total = this->pl->totalVMem << 2;
   this->values[0] = usedMem;
   snprintf(buffer, size, "%ld/%ldMB", (long int) usedMem / 1024, (long int) this->total / 1024);
}

static void VideoMemoryMeter_display(Object* cast, RichString* out) {
   char buffer[50];
   Meter* this = (Meter*)cast;
   int k = 1024; const char* format = "%ldM ";
   long int totalMem = this->total / k;
   long int usedMem = this->values[0] / k;
   RichString_write(out, CRT_colors[METER_TEXT], ":");
   sprintf(buffer, format, totalMem);
   RichString_append(out, CRT_colors[METER_VALUE], buffer);
   sprintf(buffer, format, usedMem);
   RichString_append(out, CRT_colors[METER_TEXT], "used:");
   RichString_append(out, CRT_colors[MEMORY_USED], buffer);
}

MeterClass VideoMemoryMeter_class = {
   .super = {
      .extends = Class(Meter),
      .delete = Meter_delete,
      .display = VideoMemoryMeter_display,
   },
   .setValues = VideoMemoryMeter_setValues,
   .defaultMode = BAR_METERMODE,
   .maxItems = 3,
   .total = 100.0,
   .attributes = VideoMemoryMeter_attributes,
   "VideoMem",
   "Video Memory",
   "Vid"
};
