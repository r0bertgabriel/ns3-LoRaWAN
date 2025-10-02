# Configurações de Ambiente para Simulação LoRaWAN IoT

## Estrutura Implementada

O sistema implementado suporta simulação completa de sensores IoT com ESP32-like devices para LoRaWAN, incluindo:

### 1. Aplicação de Sensor (SensorPeriodicSender)
- **Localização**: `src/lorawan/model/sensor-periodic-sender.{h,cc}`
- **Funcionalidade**: Simula microcontroladores ESP32 com sensores DHT22
- **Dados simulados**: Temperatura, umidade, nível de bateria, timestamp
- **Protocolo**: Pacotes de 20 bytes via LoRaWAN
- **Degradação realística**: Bateria degrada 0.0001V por transmissão

### 2. Helper para Configuração (SensorPeriodicSenderHelper)
- **Localização**: `src/lorawan/helper/sensor-periodic-sender-helper.{h,cc}`
- **Funcionalidade**: Deploy automatizado de sensores
- **Ambientes suportados**: urbano, rural, indoor, greenhouse, industrial

### 3. Configurações de Ambiente

#### Ambiente Urbano (Padrão)
```cpp
Temperature: 25°C ± 8°C (17-33°C)
Humidity: 55% ± 20% (35-75%)
Características: Densidade alta, interferências RF
```

#### Ambiente Rural
```cpp
Temperature: 20°C ± 12°C (8-32°C)  
Humidity: 70% ± 15% (55-85%)
Características: Área aberta, menos interferências
```

#### Ambiente Indoor
```cpp
Temperature: 22°C ± 3°C (19-25°C)
Humidity: 45% ± 10% (35-55%)
Características: Controlado, atenuação por paredes
```

#### Greenhouse (Estufa)
```cpp
Temperature: 28°C ± 5°C (23-33°C)
Humidity: 80% ± 15% (65-95%)
Características: Alta umidade, temperatura controlada
```

#### Industrial
```cpp
Temperature: 30°C ± 10°C (20-40°C)
Humidity: 60% ± 25% (35-85%)
Características: Variações extremas, interferências
```

## Arquivos de Simulação

### Simulação Principal
- **Arquivo**: `complete-network-enhanced-sensors.cc`
- **Parâmetros configuráveis**: 
  - `--nDevices`: Número de dispositivos (padrão: 100)
  - `--nGateways`: Número de gateways (padrão: 3)  
  - `--simulationTime`: Duração em horas (padrão: 2.0)
  - `--sensorInterval`: Intervalo em minutos (padrão: 5)
  - `--environment`: Tipo de ambiente (padrão: "urban")

### Análise de Dados
- **Script**: `analyze_sensor_data.py`
- **Funcionalidades**:
  - Estatísticas de temperatura e umidade
  - Análise de degradação da bateria
  - Gráficos de tendências
  - Relatórios em texto e PNG

## Estrutura de Dados Simulados

### Payload do Sensor (20 bytes)
```cpp
struct SensorDataPayload {
    uint32_t deviceId;      // ID único do dispositivo (4 bytes)
    uint32_t timestamp;     // Timestamp Unix (4 bytes) 
    float temperature;      // Temperatura em °C (4 bytes)
    float humidity;         // Umidade em % (4 bytes)
    float batteryVoltage;   // Tensão da bateria em V (4 bytes)
};
```

### Arquivos de Saída Gerados
- `enhanced-sensor-simulation-summary.txt`: Resumo da simulação
- `enhanced-sensor-device-status.dat`: Status dos dispositivos
- `enhanced-sensor-global-performance.dat`: Performance da rede
- `enhanced-sensor-positions.dat`: Posições dos nós
- `enhanced-sensor-analysis.png`: Gráficos de análise
- `enhanced-sensor-analysis-report.txt`: Relatório detalhado

## Exemplos de Uso

### Simulação Rápida (Demo)
```bash
./ns3 run "complete-network-enhanced-sensors --nDevices=20 --nGateways=2 --simulationTime=0.5 --sensorInterval=2"
```

### Simulação Completa (Pesquisa)
```bash
./ns3 run "complete-network-enhanced-sensors --nDevices=100 --nGateways=3 --simulationTime=24 --sensorInterval=60"
```

### Diferentes Ambientes
```bash
# Rural
./ns3 run "complete-network-enhanced-sensors --environment=rural"

# Indoor  
./ns3 run "complete-network-enhanced-sensors --environment=indoor"

# Estufa
./ns3 run "complete-network-enhanced-sensors --environment=greenhouse"
```

## Características Implementadas

### Realismo dos Sensores
- ✅ Variação natural de temperatura e umidade
- ✅ Degradação realística da bateria (ESP32 + DHT22)
- ✅ Timestamps precisos para análise temporal
- ✅ IDs únicos para rastreamento de dispositivos
- ✅ Configurações específicas por ambiente

### Rede LoRaWAN
- ✅ Múltiplos gateways com posicionamento estratégico  
- ✅ Modelo de energia completo com baterias de 11.88kJ
- ✅ Trace collection abrangente para análise
- ✅ Configuração ADR (Adaptive Data Rate)
- ✅ Classes A, B, C de dispositivos LoRaWAN

### Análise e Visualização
- ✅ Processamento estatístico completo em Python
- ✅ Gráficos de tendências com matplotlib
- ✅ Relatórios automatizados
- ✅ Métricas de performance da rede
- ✅ Análise de distribuição espacial

## Status de Implementação

✅ **COMPLETO**: Sistema totalmente funcional para pesquisa em LoRaWAN IoT
✅ **TESTADO**: Simulações executadas com sucesso (20-100 dispositivos)
✅ **DOCUMENTADO**: Documentação completa e exemplos de uso
✅ **ANALISADO**: Scripts de análise funcionais com visualizações

Este framework permite pesquisas avançadas em:
- Protocolos LoRaWAN para IoT
- Análise de redes de sensores
- Otimização de consumo energético
- Estudos de cobertura e performance
- Validação de algoritmos de rede

## Próximos Passos Sugeridos

1. **Mobilidade**: Adicionar suporte a sensores móveis
2. **Falhas**: Implementar modelos de falha de dispositivos
3. **Machine Learning**: Integrar predição de dados de sensores
4. **Segurança**: Adicionar simulação de ataques e segurança
5. **Escala**: Testar com milhares de dispositivos