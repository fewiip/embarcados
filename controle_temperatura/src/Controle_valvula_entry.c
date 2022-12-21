#include <Controle_valvula.h>
#include <lcd_thread.h>
#include <stdio.h>
#include <Controle_saida.h>
#include "tx_api.h"

extern void initialise_monitor_handles(void);


/* Controle de valvula entry function */

int timer5s = 0;

void timer2Callback(timer_callback_args_t *p_args) {
    (void) p_args;
    timer5s = 0;
	printf("teste timer\n");
}

void Controle_valvula_entry(void)
{
	//0.configurando variaveis
	initialise_monitor_handles();

	float saida[5];

    float massa_ar_frio = 5; 
    float abertura_ar_frio = 50;
    float massa_ar_quente = 5; 
    float abertura_ar_quente = 50;
	
	
    int pedidos = 0;
    int estado = 0;
    
    float temperatura_atual = 20;
    float temperatura_desejada = 20;
	float temperatura_mistura = 20;
	
	float incremento = 0;
	

    uint16_t adc_val;
	uint16_t buffer_adc = 0; 

    UINT status = 0;
    status = g_adc1.p_api->open(g_adc1.p_ctrl, g_adc1.p_cfg);
    status = g_adc1.p_api->scanStatusGet(g_adc1.p_ctrl);
    status = g_adc1.p_api->scanCfg(g_adc1.p_ctrl, g_adc1.p_channel_cfg);
    status = g_adc1.p_api->scanStart(g_adc1.p_ctrl);


    g_timer2.p_api->open(g_timer2.p_ctrl, g_timer2.p_cfg);
    g_timer2.p_api->reset(g_timer2.p_ctrl);


    /*float vteste;
    printf(" --- TIPO ---|--- BYTES ---\n");
    printf(" char .......: %d bytes\n", sizeof(char));
    printf(" short.......: %d bytes\n", sizeof(short));
    printf(" int.........: %d bytes\n", sizeof(int));
    printf(" long........: %d bytes\n", sizeof(long));
    printf(" float ......: %d bytes\n", sizeof(float));
    printf(" double......: %d bytes\n", sizeof(double));
    printf(" long double.: %d bytes\n", sizeof(long double));
    printf(" uint : %d bytes\n", sizeof(uint8_t));
    printf(" ulong : %d bytes\n\n", sizeof(ULONG));
    printf("\nO tamanho de vteste e...: %d \n\n",sizeof vteste);*/


    while (1)
    {
        //1.receives
        //pedidos
		
		//nao quero que bloqueie se nao tiver pedidos novos, entao eu coloco um timeout
        tx_queue_receive(&fila_pedidos_controle_temp, &pedidos, 20);
		tx_queue_receive(&fila_controle_abertura, &estado, 20);



        //2.logica
		
		//pedidos

        if (pedidos == 1) {//pediu pra incrementar
            printf("pediu pra incrementar\n");
            if(temperatura_desejada < 30) {
                temperatura_desejada = temperatura_desejada + 0.5;
            }

            g_timer2.p_api->reset(g_timer2.p_ctrl);
            g_timer2.p_api->start(g_timer2.p_ctrl);
            timer5s = 1;
        }

        if (pedidos == 2) {//pediu pra decrementar
            printf("pediu pra decrementar\n");
            if(temperatura_desejada > 16) {
                temperatura_desejada = temperatura_desejada - 0.5;
            }
            g_timer2.p_api->reset(g_timer2.p_ctrl);
            g_timer2.p_api->start(g_timer2.p_ctrl);
            timer5s = 1;
        }
		
		pedidos = 0;

        
        
		/*
		
		teremos 3 temperaturas:
		-temperatura atual: medida pelo termometro/potenciometro
		-temperatura desejada: ajustada pelo usuario
		-temperatura da mistura de ar frio e quente: eh o que vamos ajustar 
		
		vamos simular que o ar da mistura e o ar da temperatura atual vao se igualando somando ou subtraindo 0.1 a cada tick
		buffer_temp = temperatura_atual;
		temperatura_atual = (temperatura_atual + temperatura_mistura)/2;
		
		Queremos fazer um controle de temperatura entre 16C e 30C
        
        Lembrando que:
        Temperatura da valvula de ar frio = 15C
        Temperatura da valvula de ar quente = 40C
		
		sensor de temperatura:
		queremos uma faixa de 10C e 50C
		então vamos pegar o valor que vem do adc e fazer uma conversão 
		
		valor minimo = 10
		faixa de valores do adc em float = 40 * (valor atual do adc / valor maximo do adc) 
		valor minimo + (faixa de valores do adc em float) 
		
		Operação:
		• Se o sistema está esfriando o interior do veículo (Tdesejado < Treal), a mistura
		de ar quente e frio deve estar 2o abaixo da temperatura desejada
		• Se o sistema está esquentando o interior do veículo (Tdesejado > Treal), a
		mistura de ar quente e frio deve estar 2o acima da temperatura desejada
		• Se o interior do veículo está na temperatura correta (Tdesejado ≈ Treal), a
		mistura de ar quente e frio deve estar igual à temperatura desejada
		*/ 
		
		buffer_adc = adc_val;
		status = g_adc1.p_api->read(g_adc1.p_ctrl, ADC_REG_CHANNEL_0, &adc_val);
		
		if (estado == 0 ||  timer5s == 1) {//desligado
		    printf("estado %d timer %d \n", estado, timer5s);
		            incremento = 0;
		        }


		if(buffer_adc+5 < adc_val || buffer_adc- 5 > adc_val ){
			//mudamos o valor do potenciometro, portanto mudamos a temperatura
			//considerando uma margem de erro
			//printf("mudamos a temp: %d\n ", adc_val);
			
		    //adc configurado pra 10bits = 1023
			temperatura_atual = 10 + (40 * ( (float) adc_val/1024) ); //printf("temp atual %f \n", temperatura_atual);
		}else{
			temperatura_atual = temperatura_atual + incremento;
            //printf("temp atual: %f \n ", temperatura_atual);
		}
		
        
		if (temperatura_desejada  > temperatura_atual + 0.05 || temperatura_desejada  < temperatura_atual - 0.05 ) {//passei muito da faixa de erro
			if (temperatura_desejada < temperatura_atual) {
				//ou: temperatura_atual > temperatura_desejada
				//esfriando ou esfriar
				incremento = -0.1;
                temperatura_mistura = temperatura_desejada -2;
			} else if (temperatura_desejada > temperatura_atual) {
				//ou: temperatura_atual < temperatura_desejada
				//esquentando ou esquentar
				incremento = 0.1;
                temperatura_mistura = temperatura_desejada + 2;
			}
			//printf("teste1\n");

		} else {//temperatura_desejada
			incremento = 0;
			temperatura_mistura = temperatura_desejada;
			//printf("teste2\n");
		}
		


		
        massa_ar_frio = ( -( massa_ar_quente * ( temperatura_mistura - 40.0)) ) / ( temperatura_mistura - 15.0);
        abertura_ar_frio = ( massa_ar_frio/ (massa_ar_frio + massa_ar_quente) ) * 100;
        abertura_ar_quente = ( massa_ar_quente / (massa_ar_frio + massa_ar_quente)) * 100;
        //printf(" abertura valvulas de ar frio: %f, abertura valvulas ar quente: %f \n", abertura_ar_frio, abertura_ar_quente);

        //3.sends
		saida[0] = temperatura_atual;
		saida[1] = temperatura_desejada;
		saida[2] = abertura_ar_frio;
		saida[3] = abertura_ar_quente;
        saida[4] = temperatura_mistura;
        
		tx_queue_send(&valvula_queue, saida, TX_WAIT_FOREVER);
		//tx_queue_send(&valvula_queue, saida, TX_NO_WAIT);
		
        //tx_thread_sleep(100);
    }
}
