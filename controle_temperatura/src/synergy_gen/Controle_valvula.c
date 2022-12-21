/* generated thread source file - do not edit */
#include "Controle_valvula.h"

TX_THREAD Controle_valvula;
void Controle_valvula_create(void);
static void Controle_valvula_func(ULONG thread_input);
static uint8_t Controle_valvula_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.Controle_valvula") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
#if (2) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_timer2) && !defined(SSP_SUPPRESS_ISR_GPT2)
SSP_VECTOR_DEFINE_CHAN(gpt_counter_overflow_isr, GPT, COUNTER_OVERFLOW, 2);
#endif
#endif
static gpt_instance_ctrl_t g_timer2_ctrl;
static const timer_on_gpt_cfg_t g_timer2_extend =
{ .gtioca =
{ .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .gtiocb =
  { .output_enabled = false, .stop_level = GPT_PIN_LEVEL_LOW },
  .shortest_pwm_signal = GPT_SHORTEST_LEVEL_OFF, };
static const timer_cfg_t g_timer2_cfg =
{ .mode = TIMER_MODE_ONE_SHOT,
  .period = 5,
  .unit = TIMER_UNIT_PERIOD_SEC,
  .duty_cycle = 50,
  .duty_cycle_unit = TIMER_PWM_UNIT_RAW_COUNTS,
  .channel = 2,
  .autostart = true,
  .p_callback = timer2Callback,
  .p_context = &g_timer2,
  .p_extend = &g_timer2_extend,
  .irq_ipl = (2), };
/* Instance structure to use this module. */
const timer_instance_t g_timer2 =
{ .p_ctrl = &g_timer2_ctrl, .p_cfg = &g_timer2_cfg, .p_api = &g_timer_on_gpt };
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_adc1) && !defined(SSP_SUPPRESS_ISR_ADC0)
SSP_VECTOR_DEFINE_CHAN(adc_scan_end_isr, ADC, SCAN_END, 0);
#endif
#endif
#if (BSP_IRQ_DISABLED) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_adc1) && !defined(SSP_SUPPRESS_ISR_ADC0)
SSP_VECTOR_DEFINE_CHAN(adc_scan_end_b_isr, ADC, SCAN_END_B, 0);
#endif
#endif
adc_instance_ctrl_t g_adc1_ctrl;
const adc_cfg_t g_adc1_cfg =
{ .unit = 0,
  .mode = ADC_MODE_CONTINUOUS_SCAN,
  .resolution = ADC_RESOLUTION_10_BIT,
  .alignment = ADC_ALIGNMENT_RIGHT,
  .add_average_count = ADC_ADD_OFF,
  .clearing = ADC_CLEAR_AFTER_READ_ON,
  .trigger = ADC_TRIGGER_SOFTWARE,
  .trigger_group_b = ADC_TRIGGER_SYNC_ELC,
  .p_callback = NULL,
  .p_context = &g_adc1,
  .scan_end_ipl = (BSP_IRQ_DISABLED),
  .scan_end_b_ipl = (BSP_IRQ_DISABLED),
  .calib_adc_skip = false,
  .voltage_ref = ADC_EXTERNAL_VOLTAGE,
  .over_current = OVER_CURRENT_DETECTION_ENABLE,
  .pga0 = PGA_DISABLE,
  .pga1 = PGA_DISABLE,
  .pga2 = PGA_DISABLE, };
const adc_channel_cfg_t g_adc1_channel_cfg =
{ .scan_mask = (uint32_t) (
        ((uint64_t) ADC_MASK_CHANNEL_0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
                | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
                | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
                | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
                | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
                | (0)),
  /** Group B channel mask is right shifted by 32 at the end to form the proper mask */
  .scan_mask_group_b = (uint32_t) (
          (((uint64_t) ADC_MASK_CHANNEL_0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
                  | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
                  | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
                  | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
                  | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0) | ((uint64_t) 0)
                  | (0)) >> 32),
  .priority_group_a = ADC_GROUP_A_PRIORITY_OFF, .add_mask = (uint32_t) (
          (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0)
                  | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0) | (0)),
  .sample_hold_mask = (uint32_t) ((0) | (0) | (0)), .sample_hold_states = 24, };
/* Instance structure to use this module. */
const adc_instance_t g_adc1 =
{ .p_ctrl = &g_adc1_ctrl, .p_cfg = &g_adc1_cfg, .p_channel_cfg = &g_adc1_channel_cfg, .p_api = &g_adc_on_adc };
TX_QUEUE valvula_queue;
static uint8_t queue_memory_valvula_queue[50];
TX_QUEUE fila_pedidos_controle_temp;
static uint8_t queue_memory_fila_pedidos_controle_temp[20];
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void Controle_valvula_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */
    UINT err_valvula_queue;
    err_valvula_queue = tx_queue_create (&valvula_queue, (CHAR*) "Valvula queue", 5, &queue_memory_valvula_queue,
                                         sizeof(queue_memory_valvula_queue));
    if (TX_SUCCESS != err_valvula_queue)
    {
        tx_startup_err_callback (&valvula_queue, 0);
    }
    UINT err_fila_pedidos_controle_temp;
    err_fila_pedidos_controle_temp = tx_queue_create (&fila_pedidos_controle_temp, (CHAR*) "fila pedidos controle temp",
                                                      1, &queue_memory_fila_pedidos_controle_temp,
                                                      sizeof(queue_memory_fila_pedidos_controle_temp));
    if (TX_SUCCESS != err_fila_pedidos_controle_temp)
    {
        tx_startup_err_callback (&fila_pedidos_controle_temp, 0);
    }

    UINT err;
    err = tx_thread_create (&Controle_valvula, (CHAR*) "Controle de valvula", Controle_valvula_func, (ULONG) NULL,
                            &Controle_valvula_stack, 1024, 1, 1, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&Controle_valvula, 0);
    }
}

static void Controle_valvula_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    Controle_valvula_entry ();
}
