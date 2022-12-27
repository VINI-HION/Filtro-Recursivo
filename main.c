//////////////////////////////////////////////////////////////////////////////
//                            HION TECNOLOGIA                               //
//                    PROJETO INTEGRADOR - HIONZIN                          //
//                                                                          //
//               Software Filtro Recursivo em Linguagem C                   //
//////////////////////////////////////////////////////////////////////////////
//    Modulo:               DEV KIT ESP                                     //
// Descrição:                                                               //
//   Este software sera a base para filtros Digitais em linguagem c         //
//   Autor:                 Vinicius                                        //
//                                                                          //
// Compilador/Assembler:        Visual studio Code Version: 1.44            //
//                              Node.js: 10.16.3                            //
//                              PlatformIO Home:3.1.1 Core 4.3.1            //
//                              Espressif_IDF-ESP32 (4.0.0)                 //
//                                                                          //
// Hardware:            ESP32 DEvKITC                                       //
//                                                                          //
// Data: <27/12/2022>                                                       //
// Historico:                    Iniciais               Motivo da Mudança   //
//                            do Projetista                                 //
//                                                                          //
// 27/12/2022                     VMN                  stable  (ESP-IDF 4.0)//
//////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//     1.      ARQUIVOS DE DEFINIÇÕES (INCLUDES)                            *
//     1.1       Arquivos includes padrões do  Compilador                   *
/////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
//      1.2   Arquivos includes do ESP-IDF - RTOS                          //
/////////////////////////////////////////////////////////////////////////////

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/////////////////////////////////////////////////////////////////////////////
//      1.3   Arquivos includes de usuário                                 //
/////////////////////////////////////////////////////////////////////////////

// inserir Aqui

/////////////////////////////////////////////////////////////////////////////
//      2.      DECLARAÇÕES                                                //
//      2.1       Constantes Internas                                      //
/////////////////////////////////////////////////////////////////////////////

// inserir aqui

/////////////////////////////////////////////////////////////////////////////
//      2.2   Definições de entradas e saídas                              //
/////////////////////////////////////////////////////////////////////////////

#define DESLIGAR 0
#define Qtd_Amostras 100       // ***Quantas Amostras o filtro terá para filtrar, mude para testar outros filtros***

/////////////////////////////////////////////////////////////////////////////
//      3.   GLOBAIS  TYPEDEF STRUCTs                                      //
/////////////////////////////////////////////////////////////////////////////

// inserir aqui

/////////////////////////////////////////////////////////////////////////////
//      3.1   Variáveis Globais  (Valores Default da Aplicação)
/////////////////////////////////////////////////////////////////////////////

// inserir aqui

/////////////////////////////////////////////////////////////////////////////
//      3.1   Variáveis Locais  (Valores Default da Aplicação)
/////////////////////////////////////////////////////////////////////////////

// inserir aqui

/////////////////////////////////////////////////////////////////////////////
//                            RTOS Task Handles                            //
/////////////////////////////////////////////////////////////////////////////

// inserir Aqui

/////////////////////////////////////////////////////////////////////////////
//                           RTOS Queue Handles                            //
/////////////////////////////////////////////////////////////////////////////

// inserir Aqui

/////////////////////////////////////////////////////////////////////////////
//                         RTOS Semaphore Handles                          //
/////////////////////////////////////////////////////////////////////////////

// inserir Aqui

/////////////////////////////////////////////////////////////////////////////
//                      3.2.   INTERRUPÇÕES                                //
/////////////////////////////////////////////////////////////////////////////

// inserir Aqui

/////////////////////////////////////////////////////////////////////////////
//                    4.   PROTOTIPOS TAREFAS E FUNCOES                    //
/////////////////////////////////////////////////////////////////////////////

//=========================================================================//
//                   Nome da função: xFiltroRecusivo(void *arg)            //
//                                                                         //
// Proposito: Filtrar o sinal vindo da célula de forma recursiva           //
//            fazendo a operação para encontra um valor equidistante[M]    // 
//            na quantidade de em X amostras, controla a saida do filtro   //
//            atravéz da diferença da saturação da amostra atual com as    //
//            100 atnteriores                                              //
//                                                                         //
//                                                                         //
//   Entrada: void                                                         //
//     Saída: void                                                         //
//=========================================================================//
void xFiltroRecusivo(void *arg)
{

//=========================================================================//
//            Variaveis para controle de saturação da entrada              //
//=========================================================================//
    static uint8_t Leitura_analogica = DESLIGAR;                           //Vetor da variavel da célula 1         
    static uint8_t Saida_Filtro = DESLIGAR;                                //saida do filtro apos fazer a comparação o valor equidistante com a entrada atual.
    static uint8_t diferenca = DESLIGAR;                                   //Variavel que salvará a diferenca entre o valor do filtro e a saída

//============================================================================//
// Variaveis para controle do valor equidistante em relação a Qtd de amostras //
//============================================================================//
    static uint8_t contador = DESLIGAR;         
    static uint8_t valor[Qtd_Amostras];
    static uint8_t contas = DESLIGAR;
    static uint8_t media = DESLIGAR;


//=========================================================================//
// Descobre o valor equidistante em 100 amostras                           //
//=========================================================================//
    //Leitura_analogica = Bateria1;    
    valor[contador] = Leitura_analogica;
    contador++;
    if (contador == Qtd_Amostras)
    {
        contador = DESLIGAR;
        for (int j = DESLIGAR; j < Qtd_Amostras; j++)
        {
            media += valor[j];
        }
        contas = (media / Qtd_Amostras);
    }

//=============================================================================//
//controla a saturação da entrada em relçao ao valor equidistante nas amostras //
//=============================================================================//
    if (Leitura_analogica <= contas)
    {
        diferenca = abs(Leitura_analogica - contas);
        Saida_Filtro -= (uint8_t)diferenca / Qtd_Amostras;
    }
    else if (Leitura_analogica >= contas)
    {
        diferenca = abs(Leitura_analogica - contas);
        Saida_Filtro += (uint8_t)diferenca / Qtd_Amostras;
    }
    // Saida_Filtro += (uint8_t)(Leitura_analogica - Saida_Filtro) / (uint8_t)Qtd_Amostras;
    // vetorSaida[0] = Saida_Filtro;
}

/////////////////////////////////////////////////////////////////////////////
//                          5. FUNÇÃO PRINCIPAL                            //
/////////////////////////////////////////////////////////////////////////////

void app_main()
{

    /////////////////////////////////////////////////////////////////////////////
    //                    Declaração de variáveis locais                       //
    /////////////////////////////////////////////////////////////////////////////

    // inserir aqui

    /////////////////////////////////////////////////////////////////////////////
    //           Definição dos valores Iniciais dos pinos do MCU               //
    /////////////////////////////////////////////////////////////////////////////

    // inserir aqui

    /////////////////////////////////////////////////////////////////////////////
    //                   Configuracao Inicial dos PERIFERICOS                  //
    /////////////////////////////////////////////////////////////////////////////

    //inserir aqui

    /////////////////////////////////////////////////////////////////////////////
    //                       Criação da QUEUE's do RTOS                        //
    /////////////////////////////////////////////////////////////////////////////

    // inserir aqui

    /////////////////////////////////////////////////////////////////////////////
    //                      Criação da Semáforos do RTOS                       //
    /////////////////////////////////////////////////////////////////////////////

    // inserir aqui

    /////////////////////////////////////////////////////////////////////////////
    //  Configurações iniciais do microcontrolador e criação das TASKs dp RTOS //
    /////////////////////////////////////////////////////////////////////////////

    xTaskCreatePinnedToCore(xFiltroRecusivo, "xFiltroRecusivo", 2048, NULL, 1, NULL, 1);

    /////////////////////////////////////////////////////////////////////////////
    //    Suspensão de Tarefas que não serão utilizadas no inicio da aplicação //
    /////////////////////////////////////////////////////////////////////////////

    // inserir aqui

    /////////////////////////////////////////////////////////////////////////////
    //                    Habilita as interrupções do MCU                      //
    /////////////////////////////////////////////////////////////////////////////

    // inserir aqui

    /////////////////////////////////////////////////////////////////////////////
    //                 Inicialização das variáveis da MAIN                     //
    /////////////////////////////////////////////////////////////////////////////

    // inserir aqui

    /////////////////////////////////////////////////////////////////////////////
    //                            Loop principal                               //
    /////////////////////////////////////////////////////////////////////////////
}

// FINAL DA FUNCAO PRINCIPAL

/////////////////////////////////////////////////////////////////////////////
//                             FIM DO ARQUIVO                              //
/////////////////////////////////////////////////////////////////////////////