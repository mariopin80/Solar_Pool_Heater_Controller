# Hardware e montagem

[English](hardware.md) · [Visão geral do projeto](../README.pt-BR.md)

## Projetos KiCad

| Projeto | Esquema | PCB |
| --- | --- | --- |
| MPS01 1.0 | [Esquema](../hardware/MPS01/1.0/Hardware%20Aquecedor.sch) | [PCB](../hardware/MPS01/1.0/Hardware%20Aquecedor.kicad_pcb) |
| MPS01 1.0, layout alternativo | [Mesmo esquema 1.0](../hardware/MPS01/1.0/Hardware%20Aquecedor.sch) | [PCB chamada “v2” no acervo](../hardware/MPS01/1.0/layout-v2/Hardware%20Aquecedor%20v2.kicad_pcb) |
| MPS01 1.1 | [Esquema](../hardware/MPS01/1.1/Hardware%20Aquecedor%201.1.sch) | [PCB com SDA e SCL corrigidos](../hardware/MPS01/1.1/Hardware%20Aquecedor%201.1.kicad_pcb) |
| MPS02 2.0 | [Esquema](../hardware/MPS02/2.0/Hardware%20Aquecedor%202.0.sch) · [PDF](../hardware/MPS02/2.0/esquema.pdf) | [PCB](../hardware/MPS02/2.0/Hardware%20Aquecedor%202.0.kicad_pcb) |

Os arquivos de projeto estão no formato legado do KiCad 5. Abra o `.pro`, o `.sch` e o `.kicad_pcb` da mesma revisão. O esquema da MPS01 usa a biblioteca local de símbolos `atmega`. Mantenha essa biblioteca, o `sym-lib-table` e o cache de símbolos junto ao esquema.

Os dois arquivos de fabricação originais são do layout MPS01 chamado “v2”. Ambos são anteriores à correção de SDA/SCL da revisão 1.1. Para fabricar, exporte os Gerbers a partir da PCB da revisão escolhida. [Gerbers e arquivos de furação originais](../hardware/MPS01/1.0/layout-v2/fabrication)

Para montar a placa, siga os valores e os identificadores do esquema da revisão escolhida. A planilha de 2021 é a lista de componentes original do projeto MPS01. [BOM](BOM.xlsx)

## Pinagem da MPS01 1.1

A MPS01 1.1 é a placa-alvo do firmware. Esta tabela vale a partir do firmware `v0.0.6`. Os protótipos anteriores usam outras atribuições para os botões, os relés e o LCD, conforme as declarações de cada sketch.

| Sinal | Pino Arduino | Ligação na MPS01 |
| --- | --- | --- |
| Menu / Enter | D4 | SW1, ativo em nível baixo |
| Próximo / + | D3 | SW2, ativo em nível baixo |
| Voltar / − | D2 | SW3, ativo em nível baixo |
| Comando da bomba de aquecimento | D6 | Driver de K1, contatos em J5 |
| Comando da bomba de filtragem | D5 | Driver de K2, contatos em J6 |
| NTC da piscina no firmware | A0 | J3, identificado como `CLT_TMP` no KiCad |
| NTC do coletor no firmware | A1 | J4, identificado como `PSC_TMP` no KiCad |
| LCD RS | D8 | DS1 pino 4 |
| LCD E | D9 | DS1 pino 6 |
| LCD D4 | D13 | DS1 pino 11 |
| LCD D5 | D12 | DS1 pino 12 |
| LCD D6 | D11 | DS1 pino 13 |
| LCD D7 | D10 | DS1 pino 14 |
| RTC SDA | A4 | DS1307 pino 5, roteamento da 1.1 |
| RTC SCL | A5 | DS1307 pino 6, roteamento da 1.1 |
| RX da UART por software | A2 / D16 | Sketches com Bluetooth a partir da `v0.2.2` |
| TX da UART por software | A3 / D17 | Sketches com Bluetooth a partir da `v0.2.2` |

Em cada entrada NTC, o pino 1 é o nó de medição e o pino 2 é o terra. A PCB MPS01 tem um resistor de 10 kΩ ligado ao positivo em cada entrada. O firmware espera NTCs de 10 kΩ com beta de 3.600 K. Confirme qual temperatura varia no LCD ao testar cada sensor, antes de verificar o acionamento da bomba de aquecimento. No [pinout original](original/pinout-arduino.txt), os nomes dos sensores seguem as redes do KiCad e há um erro de digitação no LCD D4. A tabela acima segue o sketch nos dois casos.

A MPS01 1.0 e o layout alternativo “v2” ligam os pinos 27 e 28 do ATmega328P a SCL e SDA, respectivamente. Essa inversão motivou a revisão 1.1. O layout original `Hardware Aquecedor v1.1 SDA-SCL OK` liga o pino 27 a SDA e o 28 a SCL. O histórico original registra a correção por fios durante os testes da primeira placa.

O conector J2 da MPS01 é a UART de programação e usa D0/D1 do ATmega. A UART por software para Bluetooth usa os pinos A2/A3 da tabela. Use níveis lógicos compatíveis com o adaptador serial ou módulo escolhido.

## Conectores da MPS02

| Conector | Função no esquema |
| --- | --- |
| J2 | Três entradas de botão e terra |
| J3 | Interface do LCD paralelo |
| J4 | UART de programação |
| J5 | Sensor da piscina |
| J6 | Sensor do coletor |
| J7 | Contatos do relé de aquecimento |
| J8 | Contatos do relé de filtragem |

A MPS02 ficou na etapa de projeto no KiCad, com ESP32-WROOM-32D e DS3231M. Use o esquema 2.0 para consultar sinais e valores dos componentes dessa placa. Os sketches AVR do acervo usam a escala do ADC, a pinagem e o driver de RTC da MPS01.

## Teste de bancada

Para verificar a lógica em um Arduino Uno, monte as ligações da tabela com LCD de 16×2, botões, RTC DS1307 e dois divisores com NTC. Use indicadores no lugar das cargas das bombas. Confira LCD, botões, relógio e as duas temperaturas. Em seguida, acione cada saída pelo menu de bombas. O [sketch de teste de PCB](../examples/teste_PCB) usa a pinagem da MPS01.

As placas originais incluem entrada de rede em J1. Mantenha a entrada de rede e as cargas das bombas desconectadas durante os testes de lógica. Use o esquema e os arquivos de fabricação como referência para a instalação final.
