/* generated thread source file - do not edit */
#include "Controle_Vent.h"

TX_THREAD Controle_Vent;
void Controle_Vent_create(void);
static void Controle_Vent_func(ULONG thread_input);
static uint8_t Controle_Vent_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.Controle_Vent") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
TX_QUEUE fila_velocidade_vent;
static uint8_t queue_memory_fila_velocidade_vent[20];
TX_QUEUE fila_pedidos_controle_vent;
static uint8_t queue_memory_fila_pedidos_controle_vent[20];
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void Controle_Vent_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */
    UINT err_fila_velocidade_vent;
    err_fila_velocidade_vent = tx_queue_create (&fila_velocidade_vent, (CHAR*) "fila_velocidade_vent", 1,
                                                &queue_memory_fila_velocidade_vent,
                                                sizeof(queue_memory_fila_velocidade_vent));
    if (TX_SUCCESS != err_fila_velocidade_vent)
    {
        tx_startup_err_callback (&fila_velocidade_vent, 0);
    }
    UINT err_fila_pedidos_controle_vent;
    err_fila_pedidos_controle_vent = tx_queue_create (&fila_pedidos_controle_vent, (CHAR*) "fila_pedidos_controle_vent",
                                                      1, &queue_memory_fila_pedidos_controle_vent,
                                                      sizeof(queue_memory_fila_pedidos_controle_vent));
    if (TX_SUCCESS != err_fila_pedidos_controle_vent)
    {
        tx_startup_err_callback (&fila_pedidos_controle_vent, 0);
    }

    UINT err;
    err = tx_thread_create (&Controle_Vent, (CHAR*) "Controle Ventilador", Controle_Vent_func, (ULONG) NULL,
                            &Controle_Vent_stack, 1024, 1, 1, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&Controle_Vent, 0);
    }
}

static void Controle_Vent_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    Controle_Vent_entry ();
}
