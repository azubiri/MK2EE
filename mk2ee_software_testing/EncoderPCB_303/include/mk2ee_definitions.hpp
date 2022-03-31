#ifndef MK2EE_DEFINITIONSH_H
#define MK2EE_DEFINITIONS_H

#define modifyBitPos(n, p, b) ( ( (n) & ~(1 << (p)) ) | ((b) << (p)) ) // Set or clear a bit given a position
#define setBit(n, p) ( (n) | (1 << (p)) )
#define clearBit(n, p) ( (n) & ~(1 << (p)) )

#define prf_0 (GPIOC -> BSRR) = setBit((GPIOC -> BSRR), GPIO_BSRR_BS_3)
#define prf_1 (GPIOC -> BSRR) = clearBit((GPIOC -> BSRR), GPIO_BSRR_BS_3)

#define LED1Red     1
#define LED1Green   2
#define LED1Blue    3
#define LED2Blue    4
#define LED2Green   5
#define LED2Red     6
#define SH_PO_CSn   7

#endif