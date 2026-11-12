# Revisão do firmware MPS01

[Guia da 0.4.0-beta](firmware.pt-BR.md) · [Protocolo Bluetooth](bluetooth.md)

A revisão partiu da `v0.3.0_BT`, último sketch histórico da MPS01 1.1. Essa versão já comandava dois relés, tinha histerese por diferencial, ajustes de offset, agenda semanal de filtragem e circulação e comandos Bluetooth. A `v0.2.2` inicializava a UART. A interpretação dos comandos surgiu na `v0.3.0_BT`.

## Achados no código e tratamento na beta

| Área | Comportamento na 0.3.0_BT | Alteração na 0.4.0-beta |
| --- | --- | --- |
| Botões e menus | As telas testam níveis elétricos em laços com `delay()`. Uma tecla mantida pode ser lida em telas consecutivas. Toques curtos podem passar durante as esperas. | Cada tecla gera eventos após 24 ms de nível estável. Enter curto confirma ao soltar. Enter longo volta ou cancela. `+` e `−` repetem ao manter a tecla somente durante edições. |
| LCD e laço principal | A lógica de controle é chamada de dentro dos menus. As telas limpam o LCD em diversas transições e reescrevem campos continuamente. | O controle roda no laço principal. A tela usa dois buffers fixos e grava apenas as células que mudaram. A edição tem confirmação e retorna à tela inicial após 30 s sem interação. |
| Sondas | O cálculo do NTC aplica logaritmo e divisão sem testar os extremos do ADC. Um circuito aberto ou curto pode ser interpretado como condição térmica que pede circulação. | A média de 16 amostras por canal é atualizada a cada 250 ms. Diagnóstico de curto, circuito aberto e fora de faixa. Qualquer falha bloqueia a saída solar, inclusive em modo manual. A filtragem continua independente. A saída solar só é liberada após três leituras válidas por sonda. |
| Histerese | O mesmo estado guarda a demanda térmica, o anticongelamento e a circulação por coletor quente. A saída pode continuar ligada quando o motivo original já cessou. | Há histereses independentes para aquecimento, anticongelamento e coletor quente. O painel e o protocolo indicam o motivo da saída. A circulação por coletor quente começa ao atingir o limite configurado e termina com uma queda de 3 °C. A demanda por diferencial tem histerese de 0,5 °C na temperatura da piscina. |
| Agenda | As saídas são atualizadas apenas em dias selecionados. Ao trocar de dia, um estado pode ficar retido. Horários que cruzam meia-noite são descartados. | O intervalo é recalculado a partir do relógio. Uma agenda que atravessa a meia-noite segue o dia de início. Horários iguais desabilitam a janela. |
| Relógio | A agenda usa os dados da iteração anterior. Data e hora vêm de leituras I²C separadas. | Os sete registradores do DS1307 são lidos juntos, com timeout de I²C e validação de data e hora. O dia da semana vem do calendário. A agenda tolera uma falha de leitura I²C isolada. Uma segunda falha ou um relógio inválido suspende a agenda. O controle térmico segue as sondas válidas. |
| EEPROM | Uma EEPROM vazia pode fornecer índices de tela, modos e horários fora da faixa. Comandos Bluetooth `4`–`6` salvam o modo do aquecedor no endereço do filtro. | Importação dos parâmetros legados válidos, valores padrão para campos inválidos, dois registros com CRC e confirmação no último byte. A mesma estrutura guarda o modo correto de cada bomba para o painel e o Bluetooth. |
| Comunicação | Comandos de um caractere, sem confirmação das mudanças e com telemetria restrita a duas temperaturas. | Protocolo UART v1 com resposta por ID, estado das saídas, diagnóstico, edição de parâmetros, agendas e relógio. Controle local para ativar/desativar a UART e opção de removê-la na compilação. |

A conversão usa o divisor de 10 kΩ e beta de 3600 K do projeto. A conta passou a subtrair 273,15 para converter de kelvin para Celsius. Os canais do firmware associam A0 à piscina e A1 ao coletor. Na PCB, os nomes das redes `CLT_TMP` e `PSC_TMP` aparecem invertidos em relação a esse uso. [Pinagem e conectores](hardware.pt-BR.md#pinagem-da-mps01-11)

## Recursos observados em produtos comerciais

| Recurso | Referência comercial | Aplicação à MPS01 |
| --- | --- | --- |
| Manual temporizado | O Full Gauge Microsol SWP Advanced volta a automático após um período em manual. | Boa próxima função para as duas bombas. Na beta, o modo manual continua até o operador alterá-lo. |
| Múltiplas janelas de filtragem | O Full Gauge Microsol II power tem até quatro eventos por dia na agenda do apoio. | Duas janelas independentes já permitiriam dividir a filtragem em manhã e tarde. A beta mantém uma janela por bomba. |
| Resfriamento noturno | Full Gauge Microsol SWP Advanced e Pentair SolarTouch oferecem resfriamento pelo coletor. | Pode ser uma opção desligada de fábrica. Precisa de diferencial invertido, limite de temperatura da piscina e janela de horário. |
| Tempo mínimo de circulação e proteção por temperatura alta | O Microsol SWP Advanced prevê duração mínima no anticongelamento e desliga a bomba acima de um limite do coletor. | Separar o tempo mínimo de anticongelamento da estratégia de coletor quente. Antes de oferecer a opção de bloqueio por calor, conferir o tipo de coletor, a tubulação e a temperatura real de retorno da instalação. |
| Diagnóstico e acessórios | O SolarTouch distingue sensores abertos e em curto e tem diagnóstico de comunicação de bomba em configurações compatíveis. | A beta distingue falhas de sonda. Confirmar fluxo, falta de água ou funcionamento real da bomba requer sensor ou retorno de estado. |
| Bloqueio de ajuste técnico | O Microsol SWP Advanced usa código para edição dos parâmetros avançados. | Útil se o painel for operado por várias pessoas. Pode ser implementado depois, sem condicionar a navegação básica da beta. |

Referências de produto

- [Manual Full Gauge Microsol SWP Advanced](https://www.fullgauge.com.br/public/uploads/files/products/manual-de-produto-129-382.pdf)
- [Full Gauge Microsol II power](https://www.fullgauge.com/br/produtos/microsol-2-power/)
- [Manual Pentair SolarTouch](https://www.pentair.com/content/dam/extranet/nam/pentair-pool/residential/automation/solartouch/manual/SolarTouch_Solar_Controller_System_Installation_and_Users_Guide_English.pdf)

## Verificação em bancada

1. Sem as bombas conectadas, teste toques curtos, Enter longo, repetição em um ajuste e cancelamento. Confira se o LCD volta ao início depois de 30 s.
2. Use dois NTCs ou resistores equivalentes. Verifique as temperaturas, o acionamento solar por diferencial e o diagnóstico dos dois canais ao simular circuito aberto e curto. Confirme que a saída solar cai e a filtragem continua seguindo seu modo.
3. No RTC, programe uma agenda perto da virada do dia. Confira a saída antes, durante e depois da janela e teste a filtragem automática com o relógio indisponível.
4. Ative o Bluetooth pelo painel, use `INFO`, `STATUS` e `GET` e altere o filtro com `MODE`. Após o campo `saving` voltar a zero, reinicie e confira o modo persistido. Desative o Bluetooth pelo painel e confirme a operação local.
