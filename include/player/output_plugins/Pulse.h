/**
 * Pulse.h
 *
 * Module: player
 *
 * Defines the header of the Pulse.c wrapper of the pulseaudio 
 * C library.
 *
 * The naming style breaks with other code written to mark it is 
 * C code.
 *
 */

#ifndef _SIMPLE_PULSE_H
#define _SIMPLE_PULSE_H

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus



#include <pulse/pulseaudio.h> 


int pulse_init();
int pulse_open();
int pulse_close();
int pulse_exit();
int pulse_write(const char *buf, int count);
int pulse_drop();
int pulse_pause();
int pulse_unpause();
int pulse_buffer_space();



#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // _SIMPLE_PULSE_H

