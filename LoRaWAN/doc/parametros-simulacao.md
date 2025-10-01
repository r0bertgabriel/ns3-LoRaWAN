# Parâmetros de Configuração da Simulação - NS-3 LoRaWAN

Este documento lista e explica todos os principais parâmetros configuráveis do arquivo `examples/complete-network-example.cc`, incluindo opções avançadas para experimentação.

## Parâmetros Básicos

| Parâmetro                | Tipo    | Valor Padrão | Descrição                                                                 |
|-------------------------|---------|--------------|--------------------------------------------------------------------------|
| `nDevices`              | int     | 200          | Número de dispositivos finais (end devices) na simulação.                |
| `nGateways`             | int     | 1            | Número de gateways.                                                      |
| `radiusMeters`          | double  | 6400         | Raio da área de cobertura (em metros).                                   |
| `simulationTimeSeconds` | double  | 600          | Tempo total de simulação (em segundos).                                  |
| `appPeriodSeconds`      | int     | 600          | Intervalo entre transmissões dos dispositivos finais (em segundos).      |
| `realisticChannelModel` | bool    | false        | Ativa modelo de canal realista (prédios e sombra correlacionada).        |
| `printBuildingInfo`     | bool    | true         | Imprime informações dos prédios em arquivo.                              |

## Parâmetros Avançados

### Canal e Propagação

| Parâmetro                        | Tipo    | Valor Padrão | Descrição                                                                 |
|----------------------------------|---------|--------------|--------------------------------------------------------------------------|
| `PathLossExponent`               | double  | 3.76         | Expoente da perda de caminho do modelo log-distance.                      |
| `ReferenceDistance`              | double  | 1            | Distância de referência para o modelo de propagação.                      |
| `ReferenceLoss`                  | double  | 7.7          | Perda de referência (dB) no modelo log-distance.                          |
| `ConstantSpeedPropagationDelay`  | modelo  | -            | Modelo de atraso de propagação (constante).                               |
| `CorrelatedShadowing`            | modelo  | -            | Modelo de sombra correlacionada (ativado se `realisticChannelModel`).     |
| `BuildingPenetrationLoss`        | modelo  | -            | Modelo de penetração em prédios (ativado se `realisticChannelModel`).     |

### Mobilidade

| Parâmetro                        | Tipo    | Valor Padrão | Descrição                                                                 |
|----------------------------------|---------|--------------|--------------------------------------------------------------------------|
| `UniformDiscPositionAllocator`   | modelo  | -            | Distribuição espacial dos dispositivos em disco uniforme.                 |
| `ConstantPositionMobilityModel`  | modelo  | -            | Modelo de mobilidade fixa.                                                |
| `Altura dos dispositivos`        | double  | 1.2 (ED)     | Altura dos dispositivos finais (z = 1.2 m).                              |
| `Altura dos gateways`            | double  | 15.0         | Altura dos gateways (z = 15 m).                                          |

### Prédios (GridBuildingAllocator)

| Parâmetro         | Tipo     | Valor Padrão | Descrição                                      |
|-------------------|----------|--------------|------------------------------------------------|
| `xLength`         | double   | 130          | Comprimento dos prédios (m).                    |
| `deltaX`          | double   | 32           | Espaçamento entre prédios no eixo X (m).        |
| `yLength`         | double   | 64           | Comprimento dos prédios no eixo Y (m).          |
| `deltaY`          | double   | 17           | Espaçamento entre prédios no eixo Y (m).        |
| `Height`          | double   | 6            | Altura dos prédios (m).                         |
| `NRoomsX`         | uint     | 2            | Número de salas no eixo X por prédio.           |
| `NRoomsY`         | uint     | 4            | Número de salas no eixo Y por prédio.           |
| `NFloors`         | uint     | 2            | Número de andares por prédio.                   |
| `GridWidth`       | int      | calculado    | Número de prédios no eixo X (depende do raio).  |
| `GridHeight`      | int      | calculado    | Número de prédios no eixo Y (depende do raio).  |
| `MinX`/`MinY`     | double   | calculado    | Posição inicial do grid de prédios.             |

### Aplicações

| Parâmetro         | Tipo     | Valor Padrão | Descrição                                      |
|-------------------|----------|--------------|------------------------------------------------|
| `PacketSize`      | int      | 23           | Tamanho do pacote transmitido (bytes).          |
| `RandomDelay`     | double   | 0-10         | Atraso aleatório inicial para cada dispositivo. |

### Rede

| Parâmetro         | Tipo     | Valor Padrão | Descrição                                      |
|-------------------|----------|--------------|------------------------------------------------|
| `DataRate`        | string   | "5Mbps"     | Taxa de dados dos links ponto-a-ponto.          |
| `Delay`           | string   | "2ms"       | Atraso dos links ponto-a-ponto.                 |

### Outros

| Parâmetro         | Tipo     | Valor Padrão | Descrição                                      |
|-------------------|----------|--------------|------------------------------------------------|
| `SpreadingFactor` | função   | -            | Fator de espalhamento dos dispositivos (SF).    |
| `EnablePacketTracking` | bool | true         | Ativa rastreamento de pacotes para métricas.    |

## Como Alterar os Parâmetros

- **Via código:** Modifique os valores diretamente nas variáveis do início do arquivo.
- **Via linha de comando:** Use argumentos ao executar a simulação, por exemplo:
  ```sh
  ./waf --run "complete-network-example --nDevices=100 --radius=5000 --simulationTime=300 --appPeriod=60 --realisticChannel=true"
  ```
- **Avançados:** Parâmetros de modelos (propagação, prédios, mobilidade) devem ser alterados diretamente no código.

## Observações
- Parâmetros como `nGateways`, altura dos dispositivos/gateways, tamanho dos prédios, etc., não estão expostos via linha de comando, mas podem ser facilmente modificados no código.
- Para experimentos avançados, recomenda-se alterar os modelos de canal, mobilidade e construção conforme o objetivo do estudo.

---

