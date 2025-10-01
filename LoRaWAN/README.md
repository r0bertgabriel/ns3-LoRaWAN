# LoRaWAN ns-3 module

[![CI](https://github.com/signetlabdei/lorawan/actions/workflows/per-commit.yml/badge.svg)](https://github.com/signetlabdei/lorawan/actions)
[![codecov](https://codecov.io/gh/signetlabdei/lorawan/graph/badge.svg?token=EVBlTb4LgQ)](https://codecov.io/gh/signetlabdei/lorawan)



Este é um módulo para o [ns-3](https://www.nsnam.org "Site do ns-3") que pode ser usado para realizar simulações de uma rede [LoRaWAN](https://lora-alliance.org/about-lorawan "LoRa Alliance").

Links rápidos:

* [Visão geral do modelo de simulação](https://signetlabdei.github.io/lorawan/models/build/html/lorawan.html)
* [Documentação da API](https://signetlabdei.github.io/lorawan/html/d5/d00/group__lorawan.html)

## Primeiros passos

### Pré-requisitos

Para rodar simulações usando este módulo, primeiro é necessário instalar o ns-3. Se você estiver usando Ubuntu/Debian/Mint, instale os pacotes mínimos necessários com:

```bash
sudo apt install g++ python3 cmake ninja-build git ccache
```

Caso contrário, consulte diretamente a [seção de pré-requisitos da página de instalação do ns-3](https://www.nsnam.org/wiki/Installation#Prerequisites).

> Nota: O pacote `ccache` não é estritamente necessário, mas é altamente recomendado. Ele pode acelerar significativamente futuras compilações, economizando dezenas de minutos, embora ocupe cerca de 5GB de espaço em disco. Esse uso pode ser reduzido posteriormente por meio de configuração.

Depois, você deve:

1. Clonar o código principal do ns-3,
2. Clonar este repositório dentro do diretório `src` do ns-3,
3. Fazer checkout da versão do ns-3 suportada por este módulo.

Para instalar este módulo na versão mais recente, use o comando abaixo:

```bash
git clone https://gitlab.com/nsnam/ns-3-dev.git && cd ns-3-dev &&
git clone https://github.com/signetlabdei/lorawan src/lorawan &&
tag=$(< src/lorawan/NS3-VERSION) && tag=${tag#release } && git checkout $tag -b $tag
```

**Nota**: Ao mudar para qualquer commit anterior, *incluindo o último release*, sempre verifique se o ns-3 está na versão correta (arquivo `NS3-VERSION` na raiz deste repositório).

### Compilação

O ns-3 adota uma filosofia voltada ao desenvolvimento. Antes de rodar qualquer coisa, é preciso compilar o código. Existem duas opções:

1. **Compilar o ns-3 inteiro:** Disponibiliza todos os módulos de simulação, configurando e compilando assim (certifique-se de estar na pasta `ns-3-dev`!):

   ```bash
   ./ns3 configure --enable-tests --enable-examples &&
   ./ns3 build
   ```

2. **Compilar apenas o módulo lorawan:** Para acelerar o processo (pode levar mais de 30/40 minutos em hardware lento), altere a configuração:

   ```bash
   ./ns3 clean &&
   ./ns3 configure --enable-tests --enable-examples --enable-modules lorawan &&
   ./ns3 build
   ```

A primeira linha garante que você começa com um build limpo.

Por fim, execute os testes com:

```bash
./test.py
```

Se todos os testes passarem, está tudo pronto.

Se algum teste falhar ou travar, considere abrir uma issue.

## Exemplos de uso

O módulo inclui os seguintes exemplos:

* `simple-network-example`
* `complete-network-example`
* `network-server-example`
* `adr-example`
* `aloha-throughput`
* `frame-counter-update`
* `lora-energy-model-example`
* `parallel-reception-example`

Os exemplos podem ser executados com o comando `./ns3 run example-name` (veja `./ns3 run --help` para mais opções).

## Documentação

* [Visão geral do modelo de simulação](https://signetlabdei.github.io/lorawan/models/build/html/lorawan.html): Descrição dos modelos fundamentais do módulo (fonte em `doc/lorawan.rst`).
* [Documentação da API](https://signetlabdei.github.io/lorawan/html/d5/d00/group__lorawan.html): documentação de todas as classes, funções e variáveis gerada a partir dos comentários Doxygen no código.

Outras fontes úteis:

* [Tutorial do ns-3](https://www.nsnam.org/docs/tutorial/html/ "Tutorial ns-3"): **Comece por aqui se você é novo no ns-3!**
* [Manual do ns-3](https://www.nsnam.org/docs/manual/html/ "Manual ns-3"): Visão geral das ferramentas e abstrações do ns-3.
* A especificação LoRaWAN pode ser baixada no [site da LoRa Alliance](http://www.lora-alliance.org).

## Suporte

Para discutir e obter ajuda sobre o uso deste módulo, abra uma issue aqui.

## Contribuição

Consulte as [diretrizes de contribuição](.github/CONTRIBUTING.md) para informações sobre como contribuir.

## Autores

* Davide Magrin
* Martina Capuzzo
* Stefano Romagnolo
* Michele Luvisotto

## Licença

Este software é licenciado sob os termos da GNU GPLv2 (mesma licença do ns-3). Veja o arquivo LICENSE.md para mais detalhes.

## Agradecimentos e publicações relevantes

A versão inicial deste código foi desenvolvida como parte de uma tese de mestrado na [Universidade de Pádua](https://unipd.it "Unipd homepage"), sob supervisão dos Profs. Lorenzo Vangelista, Michele Zorzi e com ajuda de Marco Centenaro.

Publicações:

* D. Magrin, M. Capuzzo e A. Zanella, "A Thorough Study of LoRaWAN Performance Under Different Parameter Settings," IEEE Internet of Things Journal, 2019. [Link](http://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=8863372&isnumber=6702522).
* M. Capuzzo, D. Magrin e A. Zanella, "Confirmed traffic in LoRaWAN: Pitfalls and countermeasures," 2018 17th Annual Mediterranean Ad Hoc Networking Workshop (Med-Hoc-Net), Capri, 2018. [Link](https://ieeexplore.ieee.org/abstract/document/8407095).
* D. Magrin, M. Centenaro e L. Vangelista, "Performance evaluation of LoRa networks in a smart city scenario," 2017 IEEE International Conference On Communications (ICC), Paris, 2017. [Link](http://ieeexplore.ieee.org/document/7996384/).
* Network level performances of a LoRa system (Tese de Mestrado). [Link](http://tesi.cab.unipd.it/53740/1/dissertation.pdf).
