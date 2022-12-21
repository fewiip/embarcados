/* generated thread header file - do not edit */
#ifndef CONTROLE_VENT_H_
#define CONTROLE_VENT_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void Controle_Vent_entry(void);
                #else
extern void Controle_Vent_entry(void);
#endif
#ifdef __cplusplus
extern "C" {
#endif
extern TX_QUEUE fila_velocidade_vent;
extern TX_QUEUE fila_pedidos_controle_vent;
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* CONTROLE_VENT_H_ */
