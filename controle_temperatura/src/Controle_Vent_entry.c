#include "Controle_Vent.h"

/* Controle Ventilador entry function */
void Controle_Vent_entry(void)
{
    /* TODO: add your own code here */
    int estado = 1;
    int pedido = 0;
    while (1)
    {
        //1.receive
        tx_queue_receive(&fila_pedidos_controle_vent, &pedido, 20);

        //2.logica
        if(pedido == 1){//chegou um pedido
            printf("chegou um pedido vent\n");
            estado+=1;
            //printf("estado %d\n", estado);

            if (estado > 5) {
                estado = 5;
            }
            pedido = 0;
        }else if (pedido == 2){
            estado-=1;
            if(estado<1){
                estado=1;
            }
            pedido = 0;
        }

        //3.sent
        tx_queue_send(&fila_velocidade_vent, &estado, TX_WAIT_FOREVER);
        /*
        ORIGNAL
        tx_queue_send(&fila_velocidade_vent, &estado, TX_NO_WAIT);
        */

        tx_thread_sleep (100);
    }
}
