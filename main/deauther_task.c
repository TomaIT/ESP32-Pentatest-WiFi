/*
 * deauther_task.c
 *
 *  Created on: 25 ott 2018
 *      Author: giova
 */
#include "Functions_wrapper.h"

uint8_t deauthPacket[26] = {
      /*  0 - 1  */ 0xc0, 0x00, //type, subtype c0: deauth (a0: disassociate)
      /*  2 - 3  */ 0x00, 0x00, //duration (SDK takes care of that)
      /*  4 - 9  */ 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,//reciever (target)
      /* 10 - 15 */ 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, //source (ap)
      /* 16 - 21 */ 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, //BSSID (ap)
      /* 22 - 23 */ 0x00, 0x00, //fragment & squence number
      /* 24 - 25 */ 0x01, 0x00 //reason code (1 = unspecified reason)
 };

void deauther_task(void *vParameters){

}
