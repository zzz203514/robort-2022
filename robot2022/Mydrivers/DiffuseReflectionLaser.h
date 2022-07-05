#ifndef DIFFUSEREFLECTIONLASER_H_
#define DIFFUSEREFLECTIONLASER_H_

#include "gpio.h"

#define DRLASER_GPIO_PORT  GPIOA
#define LEFT_DRLASER_GPIO_PIN   GPIO_PIN_12
#define RIGHT_DRLASER_GPIO_PIN  GPIO_PIN_3


void DiffuseReflectionLaserChangeSetRight(void);
void DiffuseReflectionLaserChangeSetLeft(void);

#endif
