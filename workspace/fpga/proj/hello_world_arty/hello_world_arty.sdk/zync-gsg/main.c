//AXI GPIO driver
#include "xgpio.h"

//send data over UART
#include "xil_printf.h"

//information about AXI peripherals
#include "xparameters.h"

int main()
{
	XGpio gpio;
	u32 btn, led;

	XGpio_Initialize(&gpio, 0);

	XGpio_SetDataDirection(&gpio, 2, 0x00000000); // set LED GPIO channel tristates to All Output
	XGpio_SetDataDirection(&gpio, 1, 0xFFFFFFFF); // set BTN GPIO channel tristates to All Input

	while (1)
	{
		btn = XGpio_DiscreteRead(&gpio, 1);

		if (btn != 0) // turn all LEDs on when any button is pressed
			led = 0xFFFFFFFF;
		else
			led = 0x00000000;

		XGpio_DiscreteWrite(&gpio, 2, led);

		xil_printf("\rbutton state: %08x", btn);
	}
}
