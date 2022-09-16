void DIO_Init (char port ,int pin, int pin_direction);
void DIO_WritePORT (char port , int port_value);
void DIO_WritePin (char port ,int pin, int pin_value);
char DIO_ReadPin (char port ,int pin);
void DIO_TogglePin (char port ,int pin);