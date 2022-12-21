#include <Controle_saida.h>
#include <lcd_thread.h>

#define SAIDA_PES_FECHA 1
#define SAIDA_PES_ABRE 2
#define SAIDA_PAINEL_FECHA 3
#define SAIDA_PAINEL_ABRE 4
#define SAIDA_VIDRO_FECHA 5
#define SAIDA_VIDRO_ABRE 6
#define VENTILACAO_INC 7
#define VENTILACAO_DEC 8
#define RUN 12
#define STOP 13

extern void initialise_monitor_handles(void);
/* Controle de saida entry function */
void Controle_saida_entry(void)
{
    
    /*
    estado == 0
    estado == 1
    estado == 2
    estado == 3
    estado == 4
    */

    int estado = 0;
    int pedido = 0;

    while (1)
    {
        //1.receive
        tx_queue_receive(&fila_pedidos_controle_aberturas, &pedido, 20);

        //2.logica
        if(pedido == 1){//chegou um pedido
            printf("chegou um pedido, ");
            estado+=1;
            //printf("estado %d\n", estado);

            if (estado > 4) {
                estado = 0;
            }
            printf("estado %d\n", estado);
            pedido = 0;
        }
        //printf("estado %d \n ", estado); 

        //3.sent
        tx_queue_send(&fila_controle_abertura, &estado, TX_NO_WAIT);

        tx_thread_sleep (50);
    }
}
