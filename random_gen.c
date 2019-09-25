#include <stdint.h>

unsigned lfsr(const uint16_t seed)
//función para números pseudo-aleatorios usando un Linear-feedback shift register
{
	uint16_t lfsr = seed+1;
	uint16_t bit;      //se define un entero de 16 bits para permitir operaciónes como <<15  

	bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) /* & 1u */;
	lfsr = (lfsr >> 1) | (bit << 15);

	return lfsr;
}
