# Simulador de Rede, Versão 3 - com Módulo LoRaWAN

[![codecov](https://codecov.io/gh/nsnam/ns-3-dev-git/branch/master/graph/badge.svg)](https://codecov.io/gh/nsnam/ns-3-dev-git/branch/master/)
[![Gitlab CI](https://gitlab.com/nsnam/ns-3-dev/badges/master/pipeline.svg)](https://gitlab.com/nsnam/ns-3-dev/-/pipelines)
[![Github CI](https://github.com/nsnam/ns-3-dev-git/actions/workflows/per_commit.yml/badge.svg)](https://github.com/nsnam/ns-3-dev-git/actions)

[![Latest Release](https://gitlab.com/nsnam/ns-3-dev/-/badges/release.svg)](https://gitlab.com/nsnam/ns-3-dev/-/releases)

## Licença

Este software é licenciado sob os termos da GNU General Public License v2.0 apenas (GPL-2.0-only).
Consulte o arquivo LICENSE para mais detalhes.

## Índice

* [Visão Geral](#visão-geral-um-projeto-open-source)
* [Visão Geral do Software](#visão-geral-do-software)
* [Módulo LoRaWAN](#módulo-lorawan)
* [Obtendo o ns-3](#obtendo-o-ns-3)
* [Compilando o ns-3](#compilando-o-ns-3)
* [Testando o ns-3](#testando-o-ns-3)
* [Executando o ns-3](#executando-o-ns-3)
* [Executando Exemplos LoRaWAN](#executando-exemplos-lorawan)
* [Documentação do ns-3](#documentação-do-ns-3)
* [Trabalhando com a Versão de Desenvolvimento do ns-3](#trabalhando-com-a-versão-de-desenvolvimento-do-ns-3)
* [Contribuindo para o ns-3](#contribuindo-para-o-ns-3)
* [Relatando Problemas](#relatando-problemas)
* [Fazendo Perguntas](#fazendo-perguntas)
* [Loja de Aplicativos ns-3](#loja-de-aplicativos-ns-3)

> **NOTA**: Informações muito mais detalhadas sobre o ns-3 podem ser encontradas em
<https://www.nsnam.org>

## Visão Geral: Um Projeto Open Source

O ns-3 é um projeto open source gratuito que visa construir um simulador de rede
de eventos discretos direcionado para pesquisa em simulação e educação.
Este é um projeto colaborativo; esperamos que
as peças que faltam dos modelos que ainda não implementamos
sejam contribuídas pela comunidade em um processo de colaboração aberto.
Se você gostaria de contribuir para o ns-3, verifique a seção
[Contribuindo para o ns-3](#contribuindo-para-o-ns-3) abaixo.

Este README extrai alguns detalhes de um tutorial mais extenso
que é mantido em:
<https://www.nsnam.org/documentation/latest/>

## Visão Geral do Software

Do ponto de vista do software, o ns-3 consiste em várias bibliotecas C++
organizadas em torno de diferentes tópicos e tecnologias.
Programas que realmente executam simulações podem ser escritos
em C++ ou Python; o uso do Python é habilitado por
[vinculações C++/Python em tempo de execução](https://cppyy.readthedocs.io/en/latest/). Programas de simulação normalmente
irão vincular ou importar a biblioteca central `core` do ns e quaisquer bibliotecas
adicionais que precisarem. O ns-3 requer uma instalação de compilador C++ moderno
(g++ ou clang++) e o sistema de build [CMake](https://cmake.org).
A maioria dos programas ns-3 são single-threaded; há algum suporte limitado
para paralelização usando o framework [MPI](https://www.nsnam.org/docs/models/html/distributed.html).
O ns-3 também pode executar em um modo de emulação em tempo real, vinculando-se a um
dispositivo Ethernet na máquina host e gerando e consumindo
pacotes em uma rede real. As APIs do ns-3 são documentadas
usando [Doxygen](https://www.doxygen.nl).

O código para o framework e os modelos padrão fornecidos
pelo ns-3 é construído como um conjunto de bibliotecas. As bibliotecas mantidas
pelo projeto open source podem ser encontradas no diretório `src`.
Os usuários podem estender o ns-3 adicionando bibliotecas ao build;
bibliotecas de terceiros podem ser encontradas na [Loja de Aplicativos ns-3](https://www.nsnam.org)
ou em outros lugares em repositórios Git públicos, e são geralmente adicionadas ao diretório `contrib`.

## Módulo LoRaWAN

Esta versão do ns-3 inclui um módulo abrangente para simulação de redes **LoRaWAN (Long Range Wide Area Network)**. O LoRaWAN é um protocolo de rede de baixo consumo de energia projetado para dispositivos IoT que precisam transmitir pequenas quantidades de dados em longas distâncias.

### Características do Módulo LoRaWAN

O módulo LoRaWAN fornece:

- **Modelos de PHY realistas**: Implementação da camada física LoRa com diferentes spreading factors, bandwidths e coding rates
- **Protocolos MAC**: Implementação completa das classes A, B e C de dispositivos LoRaWAN
- **Componentes de rede**: Dispositivos finais, gateways e servidores de rede
- **Algoritmos de controle**: Adaptive Data Rate (ADR), controle de potência e seleção de canais
- **Modelos de energia**: Simulação do consumo de energia dos dispositivos
- **Modelos de propagação**: Implementação de modelos de perda de caminho específicos para LoRaWAN

### Exemplos Disponíveis

O módulo inclui vários exemplos demonstrativos:

- **`simple-network-example`**: Rede básica com um dispositivo final e um gateway
- **`complete-network-example`**: Simulação de rede completa com múltiplos dispositivos e gateways
- **`network-server-example`**: Demonstração do servidor de rede LoRaWAN
- **`adr-example`**: Exemplo do algoritmo Adaptive Data Rate
- **`aloha-throughput`**: Análise de throughput com protocolo ALOHA
- **`frame-counter-update`**: Demonstração da atualização de contadores de frame
- **`lorawan-energy-model-example`**: Simulação do modelo de energia LoRaWAN
- **`parallel-reception-example`**: Recepção paralela em gateways

### Documentação LoRaWAN

- **Documentação completa**: Disponível em `LoRaWAN/doc/lorawan.rst`
- **API Reference**: Documentação detalhada de todas as classes e funções
- **Parâmetros de simulação**: Guia em `LoRaWAN/doc/parametros-simulacao.md`

Para executar exemplos LoRaWAN, consulte a seção [Executando Exemplos LoRaWAN](#executando-exemplos-lorawan).

## Obtendo o ns-3

O ns-3 pode ser obtido baixando um arquivo de código fonte de uma versão lançada,
ou clonando o [repositório Git](https://gitlab.com/nsnam/ns-3-dev.git) do projeto.

A partir da versão 3.45 do ns-3, existem duas versões
de arquivos de código fonte que são publicadas com cada lançamento:

1. ns-3.##.tar.bz2
1. ns-allinone-3.##.tar.bz2

O primeiro arquivo é simplesmente um arquivo comprimido do mesmo código
que se pode obter fazendo checkout do código taggeado da versão
do repositório Git ns-3-dev. O segundo arquivo consiste no
ns-3 mais módulos contribuídos adicionais que são mantidos fora
do projeto principal open source ns-3, mas que foram revisados
pelos mantenedores e levemente testados para compatibilidade com a
versão. Os módulos contribuídos incluídos na versão `allinone`
mudarão ao longo do tempo conforme novas bibliotecas de terceiros emergem enquanto outras
podem perder compatibilidade com a linha principal do ns-3 (por exemplo, se elas se tornarem
não mantidas).

## Compilando o ns-3

Como mencionado acima, o ns-3 usa o sistema de build CMake, mas
o projeto mantém um wrapper customizado em torno do CMake
chamado ferramenta `ns3`. Esta ferramenta fornece uma
API [similar ao Waf](https://waf.io)
para o gerenciador de build CMake subjacente.
Para compilar o conjunto de bibliotecas padrão e os programas
de exemplo incluídos neste pacote, você precisa usar a
ferramenta `ns3`. Esta ferramenta fornece uma API similar ao Waf para o
gerenciador de build CMake subjacente.
Informações detalhadas sobre como usar o `ns3` estão incluídas no
[guia de início rápido](doc/installation/source/quick-start.rst).

Antes de compilar o ns-3, você deve configurá-lo.
Este passo permite a configuração das opções de build,
como habilitar exemplos, testes e mais.

Para configurar o ns-3 com exemplos e testes habilitados,
execute o seguinte comando no diretório principal do ns-3:

```shell
./ns3 configure --enable-examples --enable-tests
```

Em seguida, compile o ns-3 executando o seguinte comando:

```shell
./ns3 build
```

Por padrão, os artefatos de build serão armazenados no diretório `build/`.

### Plataformas Suportadas

Espera-se que a base de código atual compile e execute no
conjunto de plataformas listadas no arquivo [notas de lançamento](RELEASE_NOTES.md).

Outras plataformas podem ou não funcionar: recebemos patches para
melhorar a portabilidade do código para essas outras plataformas.

## Testando o ns-3

O ns-3 contém suítes de teste para validar os modelos e detectar regressões.
Para executar a suíte de testes, execute o seguinte comando no diretório principal do ns-3:

```shell
./test.py
```

Mais informações sobre os testes do ns-3 estão disponíveis na
seção [framework de testes](doc/manual/source/test-framework.rst) do manual.

## Executando o ns-3

Em sistemas Linux recentes, uma vez que você tenha compilado o ns-3 (com exemplos
habilitados), deve ser fácil executar os programas de exemplo com o
seguinte comando, como:

```shell
./ns3 run simple-global-routing
```

Esse programa deve gerar um arquivo de trace de texto `simple-global-routing.tr`
e um conjunto de arquivos de trace PCAP binários `simple-global-routing-xx-xx.pcap`,
que podem ser lidos por `tcpdump -n -tt -r filename.pcap`.
O código fonte do programa pode ser encontrado no diretório `examples/routing`.

## Executando Exemplos LoRaWAN

Para executar os exemplos específicos do LoRaWAN, use os seguintes comandos:

### Exemplo Básico de Rede LoRaWAN
```shell
./ns3 run simple-network-example
```

### Exemplo Completo de Rede LoRaWAN
```shell
./ns3 run complete-network-example
```

### Exemplo com Servidor de Rede
```shell
./ns3 run network-server-example
```

### Exemplo de Adaptive Data Rate (ADR)
```shell
./ns3 run adr-example
```

### Análise de Throughput ALOHA
```shell
./ns3 run aloha-throughput
```

### Exemplo de Modelo de Energia LoRaWAN
```shell
./ns3 run lorawan-energy-model-example
```

### Exemplo de Recepção Paralela
```shell
./ns3 run parallel-reception-example
```

Para ver opções adicionais de qualquer exemplo, use:
```shell
./ns3 run <exemplo> -- --help
```

Por exemplo:
```shell
./ns3 run simple-network-example -- --help
```

## Executando o ns-3 a partir do Python

Se você não planeja modificar os módulos upstream do ns-3, pode obter
uma versão pré-compilada das vinculações Python do ns-3. É recomendado
criar um ambiente virtual Python para isolar diferentes pacotes de aplicação
dos pacotes do sistema (instaláveis via gerenciadores de pacotes do SO).

```shell
python3 -m venv ns3env
source ./ns3env/bin/activate
pip install ns3
```

Se você não tem o `pip`, consulte os documentos
sobre [como instalá-lo](https://pip.pypa.io/en/stable/installation/).

Após instalar o pacote `ns3`, você pode então criar seu script de simulação Python.
Abaixo está um script de demonstração trivial para começar.

```python
from ns import ns

ns.LogComponentEnable("Simulator", ns.LOG_LEVEL_ALL)

ns.Simulator.Stop(ns.Seconds(10))
ns.Simulator.Run()
ns.Simulator.Destroy()
```

A simulação levará um tempo para iniciar, enquanto as vinculações são carregadas.
O script acima imprimirá as mensagens de log para os comandos chamados.

Use `help(ns)` para verificar os protótipos para todas as funções definidas no
namespace ns3. Para obter resultados mais úteis, consulte classes específicas de
interesse e suas funções, por exemplo, `help(ns.Simulator)`.

Ponteiros inteligentes `Ptr<>` podem ser diferenciados de objetos verificando se
`__deref__` está listado em `dir(variable)`. Para desreferenciar o ponteiro,
use `variable.__deref__()`.

A maioria das simulações ns-3 são escritas em C++ e a documentação é
orientada para usuários C++. Os programas tutoriais do ns-3 (`first.cc`,
`second.cc`, etc.) têm equivalentes em Python, se você está procurando
alguma orientação inicial sobre como usar a API Python. A
API Python pode não ser tão completa quanto a API C++, e um guia de API
para quais APIs C++ são suportadas ou não no Python atualmente não existem.
O projeto está procurando mantenedores Python adicionais para melhorar
o suporte para futuros usuários Python.

## Documentação do ns-3

Uma vez que você tenha verificado que sua compilação do ns-3 funciona executando
o exemplo `simple-global-routing` conforme descrito na seção [executando o ns-3](#executando-o-ns-3),
é bem provável que você queira começar a ler
alguma documentação do ns-3.

Toda essa documentação deve estar sempre disponível no
site do ns-3: <https://www.nsnam.org/documentation/>.

Esta documentação inclui:

* um tutorial
* um manual de referência
* modelos na biblioteca de modelos ns-3
* um wiki para dicas contribuídas pelos usuários: <https://www.nsnam.org/wiki/>
* documentação da API gerada usando doxygen: este é
  um manual de referência, provavelmente não muito adequado
  como texto introdutório:
  <https://www.nsnam.org/doxygen/index.html>

### Documentação Específica do LoRaWAN

Para o módulo LoRaWAN, documentação adicional está disponível:

* **Documentação do modelo LoRaWAN**: `LoRaWAN/doc/lorawan.rst`
* **Parâmetros de simulação**: `LoRaWAN/doc/parametros-simulacao.md`
* **Exemplos comentados**: Códigos fonte em `LoRaWAN/examples/`
* **API Reference LoRaWAN**: Documentação detalhada das classes LoRaWAN
* **Figuras e diagramas**: `LoRaWAN/doc/figures/`

## Trabalhando com a Versão de Desenvolvimento do ns-3

Se você quiser baixar e usar a versão de desenvolvimento do ns-3, você
precisa usar a ferramenta `git`. Uma folha de referência rápida e simples está incluída
no manual, mas ler os tutoriais Git
encontrados na Internet geralmente é uma boa ideia se você não está
familiarizado com ele.

Se você instalou com sucesso o Git, pode obter
uma cópia da versão de desenvolvimento com o seguinte comando:

```shell
git clone https://gitlab.com/nsnam/ns-3-dev.git
```

No entanto, recomendamos seguir as diretrizes do GitLab para iniciantes,
que incluem criar uma conta GitLab, fazer fork do projeto ns-3-dev
sob o nome da nova conta, e então clonar o repositório com fork.
Você pode encontrar mais informações no [manual](https://www.nsnam.org/docs/manual/html/working-with-git.html).

## Contribuindo para o ns-3

O processo de contribuição para o projeto ns-3 varia com
as pessoas envolvidas, a quantidade de tempo que podem investir
e o tipo de modelo em que querem trabalhar, mas o processo atual
que o projeto tenta seguir está descrito no
site [contributing code](https://www.nsnam.org/developers/contributing-code/)
e no arquivo [CONTRIBUTING.md](CONTRIBUTING.md).

## Relatando Problemas

Se você gostaria de relatar um problema, pode abrir uma nova issue no
[rastreador de issues do GitLab](https://gitlab.com/nsnam/ns-3-dev/-/issues).
Antes de criar uma nova issue, verifique se o problema que você está enfrentando
já foi relatado e contribua para a discussão, se necessário.

## Fazendo Perguntas

O ns-3 tem um [fórum oficial ns-3-users](https://groups.google.com/g/ns-3-users)
onde a comunidade faz perguntas e compartilha conselhos úteis.
Além disso, o ns-3 tem o [chat Zulip ns-3](https://ns-3.zulipchat.com/), usado para discutir
questões de desenvolvimento e perguntas entre mantenedores e a comunidade.

Use os recursos acima para fazer perguntas sobre o ns-3, em vez de criar issues.

## Loja de Aplicativos ns-3

A [Loja de Aplicativos ns-3](https://apps.nsnam.org/) oficial é um diretório centralizado
listando módulos de terceiros para ns-3 disponíveis na Internet.

Mais informações sobre como submeter um módulo ns-3 para a Loja de Aplicativos ns-3 estão disponíveis
na [documentação da Loja de Aplicativos ns-3](https://www.nsnam.org/docs/contributing/html/external.html).

---

## Sobre Esta Versão LoRaWAN

Esta versão do ns-3 foi estendida com um módulo LoRaWAN abrangente para simulação de redes IoT de longo alcance. O módulo foi desenvolvido pela Universidade de Pádua e é mantido como parte do ecossistema ns-3.

### Funcionalidades Principais do LoRaWAN

- **Simulação realista de redes LoRaWAN** com dispositivos finais, gateways e servidores de rede
- **Implementação completa do protocolo LoRaWAN** incluindo classes A, B e C de dispositivos
- **Modelos de energia precisos** para análise do consumo de energia dos dispositivos
- **Algoritmos de otimização** como Adaptive Data Rate (ADR) e controle de potência
- **Modelos de propagação especializados** para comunicações de longo alcance
- **Análise de desempenho** com métricas detalhadas de throughput, latência e consumo de energia

### Aplicações Típicas

- Pesquisa em redes IoT de baixo consumo
- Análise de desempenho de protocolos LoRaWAN
- Otimização de algoritmos de controle de rede
- Estudos de capacidade e cobertura
- Análise de consumo de energia em dispositivos IoT
- Desenvolvimento de aplicações smart city e agricultura inteligente

Para mais informações sobre LoRaWAN, consulte a [documentação oficial da LoRa Alliance](https://lora-alliance.org/).
