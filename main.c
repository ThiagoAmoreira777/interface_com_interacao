#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_2

void led (int vezes){
        gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT); // Configura o pino 2 como saída
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(1000)); // Aguarda 500ms      
    }



void desliga_led(){
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT); // Configura o pino 2 como saída
    gpio_set_level(LED_PIN, 0); // Desliga o LED
}

void app_main(void)
{
    char buffer[50];    // Nosso "balde" de letras
    int index = 0;      // Posição da letra atual
    
    printf("Sistema Pronto! Digite e aperte Enter.\n");

    while (1) {
        int c = getchar(); // Lê um único caractere do terminal

        // Se não houver nada para ler, o getchar retorna um valor especial (EOF)
        if (c != EOF) {
            
            // Se o caractere for 'Enter' (\n ou \r)
            if (c == '\n' || c == '\r') {
                buffer[index] = '\0'; // Finaliza a string com o "caractere nulo"
                
                if (index > 0) { // Só processa se houver algo escrito
                    if (strcmp(buffer, "oi") == 0) {
                        printf("\nOla Thiago! Comando reconhecido.\n");
                        led(1); // Chama a função para piscar o LED
                    } else {
                        printf("\nVoce digitou: %s (Comando desconhecido)\n", buffer);
                        desliga_led(); // Desliga o LED caso o comando seja desconhecido
                    }
                }
                
                index = 0; // Reseta o balde para a próxima palavra
            } 
            else {
                // Se for uma letra comum, guarda no balde e avança a posição
                if (index < sizeof(buffer) - 1) {
                    buffer[index++] = (char)c;
                    putchar(c); // Faz o "eco" (mostra a letra que voce digitou)
                }
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10)); // Pequena pausa
    }
}