/*  $NetBSD$  */

/*-
 * Copyright (c) 2020 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__KERNEL_RCSID(0, "$NetBSD$");

#include <sys/param.h>
#include <sys/module.h>
#include <dev/clock_subr.h>

MODULE(MODULE_CLASS_MISC, current_time, NULL);

void print_current_time(void);

/*
 * Function print_time() fetches the epoch seconds/unix time from the 
 * getmicrotime() function and sends its to clock_secs_to_ymdhms(..) in 
 * dev/clock_subr to parse it into readable date and time format and print it. 
 * Please note that the current time is printed in GMT/UTC because the kernel 
 * doesn't have the notion of local timezones.
 */
void
print_current_time(void)
{
	struct timeval tv;
	struct clock_ymdhms dt;
	char w_day[7][10] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", 
		"Friday", "Saturday"}; // To print week day name from week-day number
	
	getmicrotime(&tv); // Outputs the epoch seconds/ unix time 
	clock_secs_to_ymdhms(tv.tv_sec, &dt); // Parses the unix time into date/time
    
	printf("Current Time: %s, %04lu/%02u/%02u %02u:%02u:%02u GMT\n", 
		w_day[dt.dt_wday], dt.dt_year, dt.dt_mon, dt.dt_day, dt.dt_hour, 
		dt.dt_min, dt.dt_sec);
}

static int
current_time_modcmd(modcmd_t cmd, void *arg __unused)
{
	switch (cmd) {
	case MODULE_CMD_INIT:
		printf("current_time example module loaded.\n");
		print_current_time();
		break;

	case MODULE_CMD_FINI:
		printf("current_time example module unloaded.\n");
		break;

	default:
		return ENOTTY;
	}

	return 0;
}
