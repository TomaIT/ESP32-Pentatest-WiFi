/*
 * spam_beacon_task.c
 *
 *  Created on: 25 ott 2018
 *      Author: giova
 */
#include "Functions_wrapper.h"

#define BEACON_SSID_OFFSET 38
#define SRCADDR_OFFSET 10
#define BSSID_OFFSET 16
#define CHANNEL_OFFSET 66

uint8_t beacon[] = {
	0x80, 0x00,							// 0-1: Frame Control
	0x00, 0x00,							// 2-3: Duration
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff,				// 4-9: Destination address (broadcast)
	0xca, 0xcc, 0xad, 0x1d, 0x10, 0x06,				// 10-15: Source address
	0xca, 0xcc, 0xad, 0x1d, 0x10, 0x06,				// 16-21: BSSID
	0x00, 0x00,							// 22-23: Sequence / fragment number
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,			// 24-31: Timestamp (GETS OVERWRITTEN TO 0 BY HARDWARE)
	0x64, 0x00,							// 32-33: Beacon interval
	0x31, 0x04,							// 34-35: Capability info
	0x00, 0x10, /*SSID*/
	'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0',
	0x01, 0x08, 0x82, 0x84,	0x8b, 0x96, 0x0c, 0x12, 0x18, 0x24,	// 39-48: Supported rates
	0x03, 0x01, 0x01,						// 49-51: DS Parameter set, current channel 1 (= 0x01),
	0x05, 0x04, 0x01, 0x02, 0x00, 0x00,				// 52-57: Traffic Indication Map

};

void spam_beacon_task(void *vParameters){
	srand(time(NULL));
	uint8_t countMac,ch;
	int i,timesleep,count_OK;
	esp_err_t err;

	for(countMac=0,ch=1,timesleep=512,count_OK=0;1;countMac++){
		usleep(timesleep);
		for(i=0;i<16;i++)
			beacon[BEACON_SSID_OFFSET+i]=rand()%95+32;
		beacon[SRCADDR_OFFSET + 5] = countMac;
		beacon[BSSID_OFFSET + 5] = countMac;
		beacon[CHANNEL_OFFSET]=ch;
		err=esp_wifi_80211_tx(WIFI_IF_AP, beacon, sizeof(beacon), false);
		if(err!=ESP_OK){
			count_OK=0;
			timesleep++;
		}
		if(err==ESP_OK){
			count_OK++;
			if(count_OK>=1024){
				timesleep--;
				count_OK=0;
			}
			ch++;
			if(ch>11)
				ch=1;
		}
	}

}

