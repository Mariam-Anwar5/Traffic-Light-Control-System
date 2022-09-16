#include "types.h"
void DIO_Init (uint8 port ,uint32 pin, uint32 pin_direction);
void DIO_WritePORT (uint8 port , uint32 port_value);
void DIO_WritePin (uint8 port ,uint32 pin, uint32 pin_value);
char DIO_ReadPin (uint8 port ,uint32 pin);
void DIO_TogglePin (uint8 port ,uint32 pin);