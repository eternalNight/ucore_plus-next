#ifndef __PALACIOS_H_
#define __PALACIOS_H_

#include <palacios/vmm.h>
#include <palacios/vmm_host_events.h>

extern void send_key_to_palacios(unsigned char status, unsigned char scan_code);
extern void send_mouse_to_palacios(unsigned char packet[3]);
extern void send_tick_to_palacios(unsigned int period_us);
int palacios_init(void *);
int RunVMM();

#endif // __PALACIOS_H_
