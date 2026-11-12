# Controlador de aquecimento solar de piscina

[English](README.md)

Projeto de Mario Pin (PU2PTU). O controlador compara as temperaturas da água da piscina e do coletor solar e aciona a bomba de aquecimento conforme a diferença entre elas. Um segundo relé aciona a bomba de filtragem por horário. As versões posteriores acrescentam seleção manual do estado das bombas, circulação programada do circuito de aquecimento e uma interface serial Bluetooth.

![Renderização no KiCad da placa MPS01 revisão 1.1](docs/mps01-1.1.png)

## Hardware

| Placa | Controlador e relógio | Firmware |
| --- | --- | --- |
| [MPS01 1.0](hardware/MPS01/1.0) | ATmega328P a 16 MHz e DS1307 | PCB histórica. Esta revisão inverte SDA e SCL. |
| [MPS01 1.1](hardware/MPS01/1.1) | ATmega328P a 16 MHz e DS1307 | Placa-alvo dos firmwares AVR do acervo. Roteamento I²C corrigido. |
| [MPS02 2.0](hardware/MPS02/2.0) | ESP32-WROOM-32D e DS3231M | Projeto de hardware em KiCad. Esta revisão ficou na etapa de projeto. |

A MPS01 1.1 é a placa-alvo das 13 versões de firmware. A MPS01 usa dois sensores NTC de 10 kΩ, LCD paralelo de 16×2, três botões e relés separados para aquecimento e filtragem. O guia mostra a pinagem Arduino, a função dos conectores e a divergência na identificação dos sensores entre o esquema e o firmware da MPS01. [Guia de hardware e montagem](docs/hardware.pt-BR.md) · [Lista original de componentes](docs/BOM.xlsx)

## Firmware

Cada versão está registrada em um commit, com o mesmo caminho do sketch Arduino, `firmware/PoolHeater/PoolHeater.ino`. Os nomes das versões seguem as pastas originais. A branch principal contém o último sketch do acervo, `v0.3.0_BT`. A versão Bluetooth é experimental e tem um problema conhecido na gravação do modo do filtro na EEPROM.

- [Instalação, primeira partida e operação](docs/firmware.pt-BR.md)
- [Alterações por versão](CHANGELOG.pt-BR.md)
- [Releases no GitHub](https://github.com/mariopin80/Aquecedor_piscina/releases)
- [Sketch de teste da PCB MPS01](examples/teste_PCB)

Instale **Arduino AVR Boards** e **LiquidCrystal** na Arduino IDE. As cópias originais de **BigNums2x2** e **RTC** estão em [libraries/](libraries), com seus arquivos de licença. Copie as duas pastas para o diretório `libraries` do seu sketchbook e abra o sketch. Use **Arduino Uno** como alvo de compilação para o ATmega328P a 16 MHz.

Na primeira partida, teste o controlador em bancada com as cargas das bombas desconectadas. Ajuste o relógio, selecione os modos das bombas e confira as temperaturas antes de configurar o funcionamento automático. Consulte o guia de operação para inicializar a EEPROM de um microcontrolador novo.
