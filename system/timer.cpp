#include "external_devices.hpp"


//================================================
//              USING FOR TIMER
//
//================================================

/****************************************************************
 * config_timer
 ***************************************************************/
int external_devices::config_timer_us(uint16 value)
{
        timer.it_value.tv_sec           = 0;
        timer.it_value.tv_usec          = value;

        timer.it_interval.tv_sec        = 0;
        timer.it_interval.tv_usec       = value;

        return 0;
}

/****************************************************************
 * enable_timer
 ***************************************************************/
int external_devices::enable_timer()
{
        setitimer(ITIMER_REAL,&timer, NULL);


        return 0;
}

/****************************************************************
 * disable_timer
 ***************************************************************/
int external_devices::disable_timer()
{
        timer.it_value.tv_sec          = 0;    // set 0 to disable timer
        timer.it_value.tv_usec         = 0;    // set 0 to disable timer

        timer.it_interval.tv_sec       = 0;    // set 0 to use timer only once
        timer.it_interval.tv_usec      = 0;    // set 0 to use timer only once
        setitimer(ITIMER_REAL,&timer, NULL);
        return 0;
}

