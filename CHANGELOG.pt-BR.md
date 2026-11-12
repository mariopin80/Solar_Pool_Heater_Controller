# Histórico do firmware

[English](CHANGELOG.md) · [Visão geral](README.pt-BR.md)

As 13 versões são da linha de firmware da MPS01 1.1. As versões seguem os nomes das pastas originais. As datas vêm das anotações originais ou dos cabeçalhos. As mudanças foram conferidas por comparação entre sketches consecutivos.

[Histórico original](docs/original/historico-de-revisao.txt)

## v0.3.0_BT · 2021-11-12

- Acrescenta os comandos seriais `1`–`6` para as duas bombas e `7` para consultar as temperaturas. Reduz os atrasos dos menus.
- Problema conhecido. Os comandos `4`–`6` gravam o modo do aquecedor no endereço do filtro na EEPROM. Pelo painel, o modo do filtro é gravado corretamente.
- O sufixo `_BT` vem da pasta original. O cabeçalho e a tela de partida exibem `0.3.0`.

## v0.2.2 · 2021-10-21

- Inicializa a UART por software em A2/A3 a 9.600 baud para um módulo Bluetooth serial.
- Passa a usar o mesmo cálculo de minutos desde a meia-noite para as duas programações.

## v0.2.1b

- Calcula a média de 50 amostras do ADC por sensor, faz `ICE` e `OVH` piscarem e corrige a comparação do diferencial de desligamento.
- A pasta original identifica a revisão `b`. O cabeçalho e a tela de partida ainda exibem `0.2.1`.

## v0.2.1 · 2021-10-15

- Adiciona ajustes de anticongelamento e sobretemperatura gravados na EEPROM, com indicadores `ICE` e `OVH`.
- Mantém as demandas de aquecimento e circulação entre atualizações e acrescenta margens de retorno nos limites do coletor.

## v0.2.0 · 2021-10-08

- Adiciona horário independente para circulação do circuito de aquecimento e o combina com a demanda térmica no modo automático.
- Inicia o RTC em cada partida e altera o limite fixo de sobretemperatura do coletor para 65 °C.

## v0.1.1 · 2021-06-24

- Acrescenta as primeiras telas de circulação diária e nomeia as constantes de pinos do LCD. As telas de circulação reutilizam os dois horários do filtro.
- O histórico original menciona compensação do desvio do RTC. O ajuste de segundos aparece comentado no sketch.
- O cabeçalho e a tela de partida ainda exibem `0.1.0`.

## v0.1.0 · 2021-06-22

- Marco MVP do projeto. Adiciona modos automático, ligado e desligado independentes para as bombas de aquecimento e filtragem, com gravação na EEPROM.

## v0.0.6 · 2021-06-21

- Atualiza a pinagem dos botões, saídas dos relés e LCD e passa a aplicar o horário do filtro à saída.
- Converte os dois canais como divisores com NTC de acordo com a ligação dos resistores da placa.
- O histórico original registra os primeiros testes com a PCB inicial e uma correção por fios para SDA/SCL invertidos no RTC. O layout MPS01 1.1 corrige esse roteamento.

## v0.0.5 · 2021-05-28

- Adiciona edição de hora, data e dia da semana em telas próprias e os primeiros menus de programação do filtro com gravação na EEPROM.

## v0.0.4 · 2021-05-27

- Integra o RTC DS1307 e os primeiros ajustes de data e hora.
- Reutiliza as rotinas de ajuste nas telas de configuração.

## v0.0.3 · 2021-05-27

- Adiciona offsets de calibração independentes para piscina e coletor, ajustáveis no menu técnico e gravados na EEPROM.

## v0.0.2 · 2021-05-25

- Primeira versão minimamente funcional do aquecedor, com diferenciais de ligar e desligar independentes e limites fixos de temperatura do coletor.
- Acrescenta a conversão do NTC no canal da piscina e mantém a conversão linear no canal do coletor.

## v0.0.1 · 2021-05-13

- Primeiros testes de interface no LCD, exibição de temperaturas, saídas das bombas e ajustes na EEPROM.
- O sketch referencia DS1307 sem incluir RTC.h e usa a variável `segundo` sem declará-la.
