#include <lcd_thread.h>
#include "gui/guiapp_resources.h"
#include "gui/guiapp_specifications.h"
#include <Controle_valvula.h>
#include <Controle_saida.h>
#include <Controle_Vent.h>
#include <stdio.h>


void updatescreen (GX_WINDOW *widget);
void tratamento_mensagem_lcd_in(GX_WINDOW *widget, ULONG *msg);
static void update_numeric_prompt_value(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT value);
static void update_prompt_text_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT string_id);
static void update_button_text_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT string_id);

int vent = 1;
int estado_controle_aberturas = 0;
float temperatura_desejada = 20;
float abertura_valvula_quente = 0;

float saidaThreadValvulas[5];

UINT window1_handler(GX_WINDOW *widget, GX_EVENT *event_ptr)
{
    UINT result = gx_window_event_process(widget, event_ptr);

    int pedido = 0; 
    ULONG msg = 0;

    switch (event_ptr->gx_event_type) {
        case GX_SIGNAL(ID_TEMP_MAIS, GX_EVENT_CLICKED):
            pedido = 1;
            tx_queue_send(&fila_pedidos_controle_temp, &pedido, TX_WAIT_FOREVER);
            break;
        case GX_SIGNAL(ID_TEMP_MENOS, GX_EVENT_CLICKED):
            pedido = 2;
            tx_queue_send(&fila_pedidos_controle_temp, &pedido, TX_WAIT_FOREVER);
            break;

        case GX_SIGNAL(ID_VENT_MAIS, GX_EVENT_CLICKED):
            pedido = 1;
            tx_queue_send(&fila_pedidos_controle_vent, &pedido, TX_WAIT_FOREVER);
            break;
        case GX_SIGNAL(ID_VENT_MENOS, GX_EVENT_CLICKED):
            pedido = 2;
            tx_queue_send(&fila_pedidos_controle_vent, &pedido, TX_WAIT_FOREVER);
            break;

        case GX_SIGNAL(id_button_sel, GX_EVENT_CLICKED):
            pedido = 1;
            tx_queue_send(&fila_pedidos_controle_aberturas, &pedido, TX_WAIT_FOREVER);
            break;

            
        default:
        
            gx_window_event_process(widget, event_ptr);
            break;
    }

    return result;
}

void updatescreen (GX_WINDOW *widget) {
    ULONG var_aux, var_aux_decimal;
    

    tx_queue_receive(&valvula_queue, saidaThreadValvulas, 20);
    tx_queue_receive(&fila_controle_abertura, &estado_controle_aberturas, 20);
    tx_queue_receive(&fila_velocidade_vent, &vent, 20);

    /*
    saida[0] = temperatura_atual;
    saida[1] = temperatura_desejada;
    saida[2] = abertura_ar_frio;
    saida[3] = abertura_ar_quente;
    saida[4] = temperatura_mistura;*/

    var_aux = (ULONG)saidaThreadValvulas[0];
    update_numeric_prompt_value(widget, ID_TEMP_ATUAL, var_aux);
    
    var_aux_decimal =(ULONG)((saidaThreadValvulas[0] * 10) - (var_aux * 10));
    update_numeric_prompt_value(widget, ID_TEMP_ATUAL_DECIMAL, var_aux_decimal);

    var_aux = (ULONG)saidaThreadValvulas[1];
    update_numeric_prompt_value(widget, ID_TEMP_ALVO, var_aux);

    var_aux_decimal =(ULONG)((saidaThreadValvulas[1] * 10) - (var_aux * 10));
    update_numeric_prompt_value(widget, ID_TEMP_ALVO_DECIMAL, var_aux_decimal);

    var_aux = (ULONG)saidaThreadValvulas[4];
    update_numeric_prompt_value(widget, ID_TEMP_MISTURA, var_aux);

    var_aux_decimal =(ULONG)((saidaThreadValvulas[4] * 10) - (var_aux * 10));
    update_numeric_prompt_value(widget, ID_TEMP_MISTURA_DECIMAL, var_aux_decimal);

    
    if (estado_controle_aberturas == 0) {
        update_prompt_text_id(widget, id_prompt_sel_atual, GX_STRING_ID_STRING_DESLIGADO);

        update_numeric_prompt_value(widget, ID_VENT_DISPLAY, (ULONG)0);
        update_numeric_prompt_value(widget, ID_VALVULA_FRIA, (ULONG)0);
        update_numeric_prompt_value(widget, ID_VALVULA_QUENTE, (ULONG)0);
    }else{
        update_numeric_prompt_value(widget, ID_VENT_DISPLAY, vent);
        update_numeric_prompt_value(widget, ID_VALVULA_FRIA, (ULONG) saidaThreadValvulas[2]);
        update_numeric_prompt_value(widget, ID_VALVULA_QUENTE, (ULONG) saidaThreadValvulas[3]);

        if (estado_controle_aberturas == 1) {
            update_prompt_text_id(widget, id_prompt_sel_atual, GX_STRING_ID_STRING_PAINEL);
        } else if (estado_controle_aberturas == 2) {
            update_prompt_text_id(widget, id_prompt_sel_atual, GX_STRING_ID_STRING_VIDROS);
        } else if (estado_controle_aberturas == 3) {
            update_prompt_text_id(widget, id_prompt_sel_atual, GX_STRING_ID_STRING_PES);
        }else if (estado_controle_aberturas == 4) {
            update_prompt_text_id(widget, id_prompt_sel_atual, GX_STRING_ID_STRING_TODAS);
        }
    }
}

static void update_prompt_text_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT string_id)
{
    GX_PROMPT * p_prompt = NULL;

    ssp_err_t err = (ssp_err_t)gx_widget_find(p_widget, (USHORT)id, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET**)&p_prompt);
    if (TX_SUCCESS == err)
    {
        gx_prompt_text_id_set(p_prompt, string_id);
    }
}

static void update_button_text_id(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT string_id)
{
    GX_TEXT_BUTTON * p_button = NULL;

    ssp_err_t err = (ssp_err_t)gx_widget_find(p_widget, (USHORT)id, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET**)&p_button);

    if (TX_SUCCESS == err)
    {
        gx_text_button_text_id_set(p_button, string_id);
    }
}

static void update_numeric_prompt_value(GX_WIDGET * p_widget, GX_RESOURCE_ID id, UINT value)
{
    GX_NUMERIC_PROMPT * p_prompt = NULL;

    ssp_err_t err = (ssp_err_t)gx_widget_find(p_widget, (USHORT)id, GX_SEARCH_DEPTH_INFINITE, (GX_WIDGET**)&p_prompt);

    if (TX_SUCCESS == err)
    {
        gx_numeric_prompt_value_set(p_prompt, (INT)value);
    }
}

