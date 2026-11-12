# Instalação e operação do firmware

[English](firmware.md) · [Visão geral do projeto](../README.pt-BR.md)

## Compilação para a MPS01 1.1

1. Baixe o ZIP do código-fonte do [release](https://github.com/mariopin80/Aquecedor_piscina/releases) desejado ou faça checkout da tag. Abra `firmware/PoolHeater/PoolHeater.ino`.
2. Na Arduino IDE, instale o pacote Arduino AVR Boards e a biblioteca LiquidCrystal. Copie as [pastas BigNums2x2 e RTC](../libraries) para o diretório `libraries` do seu sketchbook. EEPROM, SoftwareSerial e Wire fazem parte do pacote AVR.
3. Selecione **Arduino Uno** para o ATmega328P a 16 MHz. Use a porta serial e o procedimento de gravação correspondentes ao bootloader. Para um AVR novo, programe o microcontrolador com um gravador AVR antes de usar a gravação serial.

Para compilar com Arduino CLI, execute na raiz do repositório

```sh
arduino-cli core update-index
arduino-cli core install arduino:avr
arduino-cli lib install LiquidCrystal
arduino-cli compile --fqbn arduino:avr:uno --libraries libraries firmware/PoolHeater
```

As 13 versões do acervo são da MPS01 1.1. Nos protótipos mais antigos, confira a pinagem nas declarações de cada sketch. [Guia de hardware](hardware.pt-BR.md)

## Primeira partida

Os sketches históricos leem os ajustes diretamente da EEPROM. Em um microcontrolador novo, inicialize a memória uma vez, com as cargas das bombas desconectadas. O bloco comentado `USAR SOMENTE na montagem inicial` em `setup()` traz os valores iniciais originais. Habilite-o numa cópia local para a primeira gravação. A partir da `v0.2.0`, o horário de circulação também usa os bytes 24, 26, 34, 36, 44 e 46. Acrescente estas gravações ao mesmo bloco temporário na primeira partida.

```cpp
EEPROM.update(24, 0);
EEPROM.update(26, 0);
EEPROM.update(34, 0);
EEPROM.update(36, 0);
EEPROM.update(44, 0);
EEPROM.update(46, 0);
```

Em seguida, grave novamente o sketch original para que as próximas partidas conservem os ajustes. Confira hora, data e dia da semana do RTC no menu. Horários de ligar e desligar iguais a 00:00 produzem um intervalo vazio.

## Painel

A sequência abaixo corresponde às versões `v0.2.2` e `v0.3.0_BT`.

| Tela | Operação |
| --- | --- |
| Inicial | O número grande é a temperatura da piscina. Pressione **+** para consultar as duas temperaturas e **Enter** para abrir a sequência de ajustes. |
| `ESTADO BOMBAS` | Pressione **+** para abrir os modos. Use **Enter** para editar e confirmar cada bomba em sequência. Selecione `AUTO`, `LIGA` ou `DESL` com **+** e **−**. |
| `AJUSTE AQUECEDOR` | Pressione **+** para ajustar `TEMP PISCINA` e, em seguida, o dia e os horários de circulação em `C DIA`. |
| `AJUSTE FILTRO` | Pressione **+** para ajustar o dia e os horários do filtro em `PROG.1`. |
| `AJUSTE DATA/HORA` | Pressione **+** para ajustar hora, data e dia da semana. |
| `CONFIG TECNICA` | Pressione **+** para ajustar os diferenciais, os offsets dos sensores e os limites de anticongelamento e sobretemperatura. |

No título de um menu, **Enter** avança para o título seguinte e **−** retorna à tela inicial. Dentro de um ajuste, use **Enter** para editar ou confirmar e **+**/**−** para alterar o valor. Na programação, `TOD` significa todos os dias, `FDS` fins de semana e `UTL` dias úteis. Use um horário de ligar anterior ao de desligar no mesmo dia. O código compara os dois horários dentro de um único dia.

Em `AUTO`, a bomba de aquecimento segue a demanda por diferencial, os limites de temperatura do coletor e o horário de circulação. A bomba do filtro segue seu próprio horário. Os modos manuais `LIGA` e `DESL` comandam a saída diretamente e ignoram a lógica automática.

## Bluetooth experimental

A `v0.2.2` inicializa a UART por software. A `v0.3.0_BT` acrescenta comandos de um caractere a 9.600 baud.

| Caractere | Comando |
| --- | --- |
| `1` / `2` / `3` | Bomba de aquecimento em automático / ligada / desligada |
| `4` / `5` / `6` | Bomba de filtragem em automático / ligada / desligada |
| `7` | Retorna as temperaturas da piscina e do coletor |

Os comandos `4` a `6` atualizam o modo do filtro na RAM e gravam o modo do **aquecedor** no endereço do filtro na EEPROM. Ajuste o modo do filtro pelo painel para gravá-lo corretamente e mantê-lo após desligar e ligar. O release preserva a implementação Bluetooth original como referência.
