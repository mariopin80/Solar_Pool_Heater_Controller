# Instalação e operação do firmware

[English](firmware.md) · [Visão geral do projeto](../README.pt-BR.md)

## Compilação para a MPS01 1.1

1. Baixe o ZIP do código-fonte da `v0.4.0-beta` nos [releases](https://github.com/mariopin80/Aquecedor_piscina/releases). Extraia todo o ZIP para manter juntos o sketch e os arquivos auxiliares.
2. Na Arduino IDE, instale Arduino AVR Boards 1.8.8 e LiquidCrystal 1.0.7. Copie a pasta [BigNums2x2](../libraries/BigNums2x2) para o diretório `libraries` do seu sketchbook. Wire e EEPROM fazem parte do pacote AVR. O Bluetooth também usa SoftwareSerial.
3. Abra `firmware/PoolHeater/PoolHeater.ino`. Selecione **Arduino Uno** para o ATmega328P a 16 MHz. Use o método de gravação do bootloader da placa ou um gravador AVR por ISP.

Para verificar a compilação com Arduino CLI, execute na raiz do repositório

```sh
arduino-cli compile --fqbn arduino:avr:uno --libraries libraries firmware/PoolHeater
```

Para versões anteriores, consulte as instruções de compilação e inicialização da EEPROM disponíveis na tag correspondente. [Releases históricos](https://github.com/mariopin80/Aquecedor_piscina/releases)

## Primeira partida e migração

Na primeira partida, a beta importa temperaturas, modos das bombas e agendas válidos da EEPROM antiga. Campos vazios ou inválidos recebem valores padrão. Com EEPROM virgem, as duas bombas começam em `DESL`. A temperatura-alvo é 25 °C, com diferenciais de 12 °C para ligar e 5 °C para desligar. Os limites de anticongelamento e de coletor quente são 4 °C e 65 °C. A agenda antiga com horário de ligar posterior ao de desligar ficava inativa. A migração a mantém inativa até que seja editada.

A beta grava os novos ajustes em dois registros com CRC nos endereços 80–143. Ao reinstalar um firmware anterior, ele recupera os ajustes anteriores à beta nos endereços 0 a 67. A beta lê seus próprios ajustes nos novos registros. O modo importado do filtro vem do valor encontrado no endereço 52 da EEPROM antiga. Confira esse ajuste ao atualizar da versão Bluetooth.

Na bancada, deixe as cargas das bombas desconectadas. Confira a identificação das duas sondas, a data e a hora e os modos de cada bomba antes de passar para automático. [Guia de hardware](hardware.pt-BR.md)

## Painel

| Ação | Resultado |
| --- | --- |
| Toque curto em **Enter** | Abre um menu ou ajuste, avança ao próximo campo de data ou horário, ou confirma a edição |
| Segure **Enter** por cerca de 0,7 s | Volta um nível ou cancela a edição em curso |
| **+** / **−** | Percorre os itens ou altera o valor em edição |
| Segure **+** / **−** em um ajuste numérico ou de agenda | Repete depois de cerca de 0,44 s e, em seguida, a cada 0,11 s |
| **+** ou **−** na tela inicial | Alterna entre a tela inicial e a visão das duas sondas |

As telas de ajustes mostram `*` durante a edição e `~` enquanto gravam. Após 30 segundos sem interação, o painel volta ao início e descarta a edição em curso. A tela inicial mostra a temperatura da piscina e o motivo do comando da bomba solar. O `F` no canto superior direito indica que a saída do filtro está acionada. Na tela de detalhes, cada sonda mostra a temperatura ou seu diagnóstico.

| Menu | Ajuste |
| --- | --- |
| `BOMBAS` | Modos independentes `AUTO`, `LIGA` e `DESL` |
| `AQUECIMENTO` | Temperatura desejada da piscina |
| `CIRCULACAO` | Dia e horários de circulação do circuito solar |
| `FILTRAGEM` | Dia e horários de filtragem |
| `RELOGIO` | Dia, mês, ano, hora e minuto. O dia da semana é calculado pela data. |
| `AJUSTES TECNICOS` | Diferenciais de ligar e desligar, offsets, anticongelamento e limite de coletor quente |
| `BLUETOOTH` | Em edição, use **+** para ativar ou **−** para desativar. Confirme com **Enter**. |

Para editar uma agenda, confirme o dia, a hora e o minuto de ligar, depois a hora e o minuto de desligar. `TOD` vale para todos os dias, `FDS` para os fins de semana e `UTL` para os dias úteis. Uma programação de sexta-feira das 22:00 às 02:00 termina no sábado às 02:00. Horários iguais desativam a janela. O dia selecionado é o de início.

## Lógica das bombas

- Em `AUTO`, o circuito solar avalia independentemente o anticongelamento, a circulação por coletor quente, a demanda por diferencial e a agenda. O LCD mostra o motivo ativo de maior prioridade, nessa ordem.
- A beta mantém a ação histórica de coletor quente. Ao atingir o limite do coletor, o modo solar `AUTO` pede circulação, com margem de retorno de 3 °C. O anticongelamento tem margem de retorno de 2 °C.
- A falha de qualquer sonda bloqueia o relé solar em todos os modos. Três leituras válidas por sonda liberam o funcionamento. A filtragem continua independente das sondas.
- As agendas são suspensas se o RTC sinalizar parada, devolver data ou hora inválida ou falhar em duas leituras I²C consecutivas. O controle térmico solar continua seguindo as sondas. A filtragem manual fica disponível.
- Os modos manuais `LIGA` e `DESL` confirmados persistem após reiniciar. Selecione `AUTO` para voltar ao controle térmico e às agendas.

## Bluetooth

Ative a comunicação pelo painel. A configuração inicial vem desligada na primeira migração ou com EEPROM virgem. Os pinos A2 e A3 mantêm a UART do módulo a 9.600 baud. O futuro aplicativo poderá consultar temperaturas, comandos dos relés e falhas, além de ajustar modos, agendas, parâmetros térmicos e relógio. [Especificação do protocolo](bluetooth.md)

Para compilar sem Bluetooth, defina `POOLHEATER_ENABLE_BLUETOOTH` como `0` em `Board.h` ou passe `-DPOOLHEATER_ENABLE_BLUETOOTH=0` pela propriedade `compiler.cpp.extra_flags` do Arduino CLI. Os comandos antigos de um caractere podem ser habilitados com `POOLHEATER_ENABLE_LEGACY_BT=1`.

## Verificação

A beta compila para Arduino Uno com Bluetooth, com o módulo removido da compilação e com os comandos antigos opcionais. Os [testes de regressão em computador](../tests/control_and_buttons.cpp) cobrem eventos dos botões, agenda e decisões das bombas. O [comando para rodar os testes](firmware.md#verification) está no guia em inglês. Verifique o LCD, os botões, o RTC, as sondas, os relés e o módulo Bluetooth na bancada da MPS01 1.1 antes de conectar as cargas.
