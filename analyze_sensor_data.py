#!/usr/bin/env python3
"""
Análise de Dados da Simulação LoRaWAN com Sensores IoT
======================================================

Este script analisa os dados gerados pela simulação NS-3 de sensores IoT
com LoRaWAN, extraindo informações sobre:
- Distribuição de temperatura e umidade
- Posição dos dispositivos e gateways
- Performance da rede
- Estatísticas dos sensores

Autor: Enhanced LoRaWAN IoT Sensor Simulation
Data: 2024
"""

import os
import re
from datetime import datetime, timedelta

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


class LoRaWANSensorAnalyzer:
    def __init__(self, base_path="."):
        self.base_path = base_path
        self.sensor_data = []
        self.positions = {}
        self.gateways = {}
        
    def parse_log_file(self, log_file="enhanced-sensor-simulation.log"):
        """Extrai dados dos sensores do arquivo de log da simulação"""
        log_path = os.path.join(self.base_path, log_file)
        
        # Padrão regex para extrair dados dos sensores
        sensor_pattern = r'Sensor (\d+) generated data: Temp=([\d.-]+)°C, Humidity=([\d.-]+)%, Battery=([\d.-]+)V, Seq=(\d+)'
        
        # Se não há arquivo de log específico, simula dados baseados na saída da simulação
        if not os.path.exists(log_path):
            print(f"Log file {log_file} not found. Generating sample data...")
            self._generate_sample_data()
            return
            
        with open(log_path, 'r') as f:
            for line in f:
                match = re.search(sensor_pattern, line)
                if match:
                    device_id = int(match.group(1))
                    temperature = float(match.group(2))
                    humidity = float(match.group(3))
                    battery = float(match.group(4))
                    sequence = int(match.group(5))
                    
                    self.sensor_data.append({
                        'device_id': device_id,
                        'temperature': temperature,
                        'humidity': humidity,
                        'battery': battery,
                        'sequence': sequence,
                        'timestamp': sequence * 300  # 5 minutos entre leituras
                    })

    def _generate_sample_data(self):
        """Gera dados de exemplo baseados nos parâmetros da simulação"""
        print("Gerando dados de exemplo para análise...")
        
        # Simula 100 dispositivos, 24 leituras cada (2 horas, 5 min intervalo)
        np.random.seed(42)  # Para reprodutibilidade
        
        for device_id in range(1000, 1100):  # IDs 1000-1099
            for seq in range(24):  # 24 leituras
                # Ambiente urbano: temp média 25°C ± 8°C, umidade 55% ± 20%
                temperature = np.random.normal(25.0, 8.0)
                humidity = np.random.normal(55.0, 20.0)
                humidity = max(0, min(100, humidity))  # Limita entre 0-100%
                
                # Bateria degradando lentamente
                battery = 3.7 - (seq * 0.001)  # Diminui 1mV por leitura
                
                self.sensor_data.append({
                    'device_id': device_id,
                    'temperature': temperature,
                    'humidity': humidity,
                    'battery': battery,
                    'sequence': seq,
                    'timestamp': seq * 300  # 5 minutos entre leituras
                })

    def load_positions(self, positions_file="enhanced-sensor-positions.dat"):
        """Carrega posições dos dispositivos e gateways"""
        positions_path = os.path.join(self.base_path, positions_file)
        
        if not os.path.exists(positions_path):
            print(f"Positions file {positions_file} not found.")
            return
            
        with open(positions_path, 'r') as f:
            for line in f:
                if line.startswith('#'):
                    continue
                    
                parts = line.strip().split()
                if len(parts) >= 5:
                    device_id = int(parts[0])
                    x, y, z = float(parts[1]), float(parts[2]), float(parts[3])
                    device_type = parts[4]
                    
                    if device_type == "SENSOR":
                        self.positions[device_id] = (x, y, z)
                    elif device_type == "GATEWAY":
                        self.gateways[device_id] = (x, y, z)

    def analyze_sensor_data(self):
        """Realiza análise estatística dos dados dos sensores"""
        if not self.sensor_data:
            print("Nenhum dado de sensor encontrado!")
            return
            
        df = pd.DataFrame(self.sensor_data)
        
        print("=== Análise dos Dados dos Sensores IoT ===")
        print(f"Total de leituras: {len(df)}")
        print(f"Dispositivos únicos: {df['device_id'].nunique()}")
        print(f"Sequências por dispositivo: {df['sequence'].max() + 1}")
        
        print("\n--- Estatísticas de Temperatura ---")
        print(f"Temperatura média: {df['temperature'].mean():.2f}°C")
        print(f"Temperatura min/max: {df['temperature'].min():.2f}°C / {df['temperature'].max():.2f}°C")
        print(f"Desvio padrão: {df['temperature'].std():.2f}°C")
        
        print("\n--- Estatísticas de Umidade ---")
        print(f"Umidade média: {df['humidity'].mean():.2f}%")
        print(f"Umidade min/max: {df['humidity'].min():.2f}% / {df['humidity'].max():.2f}%")
        print(f"Desvio padrão: {df['humidity'].std():.2f}%")
        
        print("\n--- Estatísticas de Bateria ---")
        print(f"Bateria média: {df['battery'].mean():.3f}V")
        print(f"Bateria min/max: {df['battery'].min():.3f}V / {df['battery'].max():.3f}V")
        
        return df

    def plot_sensor_analysis(self, df):
        """Gera gráficos de análise dos dados dos sensores"""
        plt.style.use('default')
        fig, axes = plt.subplots(2, 3, figsize=(15, 10))
        fig.suptitle('Análise de Dados dos Sensores IoT - Simulação LoRaWAN', fontsize=16)
        
        # Distribuição de temperatura
        axes[0, 0].hist(df['temperature'], bins=30, alpha=0.7, color='red', edgecolor='black')
        axes[0, 0].set_title('Distribuição de Temperatura')
        axes[0, 0].set_xlabel('Temperatura (°C)')
        axes[0, 0].set_ylabel('Frequência')
        axes[0, 0].grid(True, alpha=0.3)
        
        # Distribuição de umidade
        axes[0, 1].hist(df['humidity'], bins=30, alpha=0.7, color='blue', edgecolor='black')
        axes[0, 1].set_title('Distribuição de Umidade')
        axes[0, 1].set_xlabel('Umidade (%)')
        axes[0, 1].set_ylabel('Frequência')
        axes[0, 1].grid(True, alpha=0.3)
        
        # Correlação temperatura vs umidade
        axes[0, 2].scatter(df['temperature'], df['humidity'], alpha=0.5, s=10)
        axes[0, 2].set_title('Temperatura vs Umidade')
        axes[0, 2].set_xlabel('Temperatura (°C)')
        axes[0, 2].set_ylabel('Umidade (%)')
        axes[0, 2].grid(True, alpha=0.3)
        
        # Evolução temporal da temperatura (exemplo de alguns dispositivos)
        sample_devices = df['device_id'].unique()[:5]
        for device in sample_devices:
            device_data = df[df['device_id'] == device].sort_values('sequence')
            axes[1, 0].plot(device_data['sequence'], device_data['temperature'], 
                           label=f'Sensor {device}', marker='o', markersize=3)
        axes[1, 0].set_title('Evolução Temporal - Temperatura')
        axes[1, 0].set_xlabel('Sequência de Leitura')
        axes[1, 0].set_ylabel('Temperatura (°C)')
        axes[1, 0].legend()
        axes[1, 0].grid(True, alpha=0.3)
        
        # Degradação da bateria
        for device in sample_devices:
            device_data = df[df['device_id'] == device].sort_values('sequence')
            axes[1, 1].plot(device_data['sequence'], device_data['battery'], 
                           label=f'Sensor {device}', marker='o', markersize=3)
        axes[1, 1].set_title('Degradação da Bateria')
        axes[1, 1].set_xlabel('Sequência de Leitura')
        axes[1, 1].set_ylabel('Tensão da Bateria (V)')
        axes[1, 1].legend()
        axes[1, 1].grid(True, alpha=0.3)
        
        # Mapa de posições dos dispositivos
        if self.positions and self.gateways:
            # Posições dos sensores
            sensor_x = [pos[0] for pos in self.positions.values()]
            sensor_y = [pos[1] for pos in self.positions.values()]
            axes[1, 2].scatter(sensor_x, sensor_y, c='blue', s=20, alpha=0.6, label='Sensores')
            
            # Posições dos gateways
            gw_x = [pos[0] for pos in self.gateways.values()]
            gw_y = [pos[1] for pos in self.gateways.values()]
            axes[1, 2].scatter(gw_x, gw_y, c='red', s=100, marker='^', label='Gateways')
            
            axes[1, 2].set_title('Distribuição Espacial da Rede')
            axes[1, 2].set_xlabel('Posição X (m)')
            axes[1, 2].set_ylabel('Posição Y (m)')
            axes[1, 2].legend()
            axes[1, 2].grid(True, alpha=0.3)
        else:
            axes[1, 2].text(0.5, 0.5, 'Dados de posição\nnão disponíveis', 
                           ha='center', va='center', transform=axes[1, 2].transAxes)
            axes[1, 2].set_title('Distribuição Espacial da Rede')
        
        plt.tight_layout()
        plt.savefig('enhanced-sensor-analysis.png', dpi=300, bbox_inches='tight')
        plt.show()

    def generate_report(self, df):
        """Gera relatório completo da análise"""
        report_file = "enhanced-sensor-analysis-report.txt"
        
        with open(report_file, 'w') as f:
            f.write("=== RELATÓRIO DE ANÁLISE DOS SENSORES IoT LoRaWAN ===\n")
            f.write(f"Gerado em: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}\n\n")
            
            f.write("RESUMO DA SIMULAÇÃO:\n")
            f.write(f"- Total de leituras de sensores: {len(df):,}\n")
            f.write(f"- Dispositivos IoT simulados: {df['device_id'].nunique()}\n")
            f.write(f"- Período de simulação: {df['sequence'].max() + 1} leituras (2 horas)\n")
            f.write(f"- Intervalo entre leituras: 5 minutos\n")
            f.write(f"- Tipo de ambiente: Urbano\n\n")
            
            f.write("ANÁLISE DOS DADOS DE TEMPERATURA:\n")
            f.write(f"- Temperatura média: {df['temperature'].mean():.2f}°C\n")
            f.write(f"- Faixa de temperatura: {df['temperature'].min():.2f}°C a {df['temperature'].max():.2f}°C\n")
            f.write(f"- Desvio padrão: {df['temperature'].std():.2f}°C\n")
            f.write(f"- Mediana: {df['temperature'].median():.2f}°C\n\n")
            
            f.write("ANÁLISE DOS DADOS DE UMIDADE:\n")
            f.write(f"- Umidade média: {df['humidity'].mean():.2f}%\n")
            f.write(f"- Faixa de umidade: {df['humidity'].min():.2f}% a {df['humidity'].max():.2f}%\n")
            f.write(f"- Desvio padrão: {df['humidity'].std():.2f}%\n")
            f.write(f"- Mediana: {df['humidity'].median():.2f}%\n\n")
            
            f.write("ANÁLISE DO SISTEMA DE ENERGIA:\n")
            f.write(f"- Tensão inicial da bateria: {df['battery'].max():.3f}V\n")
            f.write(f"- Tensão final da bateria: {df['battery'].min():.3f}V\n")
            f.write(f"- Degradação total: {(df['battery'].max() - df['battery'].min()) * 1000:.1f}mV\n")
            f.write(f"- Taxa de degradação: {((df['battery'].max() - df['battery'].min()) / (df['sequence'].max() + 1)) * 1000:.3f}mV por leitura\n\n")
            
            f.write("DISTRIBUIÇÃO ESPACIAL:\n")
            f.write(f"- Sensores posicionados: {len(self.positions)}\n")
            f.write(f"- Gateways instalados: {len(self.gateways)}\n")
            f.write(f"- Raio da rede: 2000 metros\n\n")
            
            f.write("ARQUIVOS GERADOS:\n")
            f.write("- enhanced-sensor-analysis.png: Gráficos de análise\n")
            f.write("- enhanced-sensor-analysis-report.txt: Este relatório\n")
            f.write("- enhanced-sensor-simulation-summary.txt: Resumo da simulação\n")
            f.write("- enhanced-sensor-positions.dat: Posições dos dispositivos\n")
            f.write("- enhanced-sensor-device-status.dat: Status dos dispositivos\n")
            f.write("- enhanced-sensor-global-performance.dat: Performance da rede\n")
        
        print(f"\nRelatório salvo em: {report_file}")

def main():
    print("=== Analisador de Dados da Simulação LoRaWAN IoT ===")
    
    analyzer = LoRaWANSensorAnalyzer()
    
    # Carrega dados
    analyzer.parse_log_file()
    analyzer.load_positions()
    
    # Realiza análise
    df = analyzer.analyze_sensor_data()
    
    if df is not None and not df.empty:
        # Gera gráficos
        analyzer.plot_sensor_analysis(df)
        
        # Gera relatório
        analyzer.generate_report(df)
        
        print("\n=== Análise Concluída ===")
        print("Verifique os arquivos gerados:")
        print("- enhanced-sensor-analysis.png: Gráficos")
        print("- enhanced-sensor-analysis-report.txt: Relatório detalhado")
    else:
        print("Erro: Não foi possível carregar os dados dos sensores.")

if __name__ == "__main__":
    main()