#ifndef __K210_H
#define	__K210_H

#include "main.h"
#include "stdio.h"
#include "usart.h"

void K210Init(void);
void  BaoWuLocation(uint8_t qrcode);
void  K210_Color_Data(uint8_t com_data[]);
void	K210_Qrcode_Data(uint8_t qr_data[]);
void  Forbid(void);


#endif

