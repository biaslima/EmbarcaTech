# Ebook - Arquitetura de Sistemas Embarcados

# A arquitetura

![image.png](image.png)

- Hardware → Componentes físicos que formam o hardware;
- Software → gravados na memória do sistema.

## Hardware

Composto por microcontrolador, memórias externas, interfaces, sensores e atuadores interligados por **barramentos.**

### Barramento

- Harvard → Cada memória possui seu próprio barramento;
    - A MPU acessa as memórias simultaneamente;
    - Mais rápida;
    - Microcontroladores chamados de RISC.
- Von NEUMANN → As memórias e interfaces compartilham o barramento
    - MPU acessa cada informação de cada vez → mais lento;
    - Microcontroladores chamados de CISC;

# Arquitetura em Camadas

### Camada de Hardware

<aside>
❗

Abriga os componentes de hardware do sistema.

</aside>

- **HARDWIRES HW** → composto de componentes físicos interligados dentro de um mesmo chip ou através de trilhas de placas de circuito impresso.
- **SOFTWIRED HW** →  programado em software armazenado em dispositivos lógicos programáveis ou matriz de portas lógicas cujos pontos de interligação podem ser ativados ou não
por software.

### Camada de Software Básico

<aside>
❗

Camada compostas pelas subcamadas device drivers, núcleo operacional e protocolos e serviços.

</aside>

- **Device Drivers** → encapsulam cada um dos dispositivos de hardwares (interagem diretamente com a camada anterior);
- **Núcleo Operacional (Kernel)** → permite a execução concorrente de várias tarefas;
    - Microkernel gerencia e escalona as tarefas;
- **Protocolos e serviços** → protocolos que estruturam e definem os tráfegos de informação.
    - Permite a interoperabilidade entre os sistemas de comunicação.

### Camada de Software de Aplicação

<aside>
❗

Implementa a funcionalidade específica do SE → firmware.

</aside>

# Componentes de um SE

- Sensores;
- Atuadores;
- Componentes digitais;
- Conversores;
- Software;

## Microcontroladores

<aside>
❗

Processadores com muitas funções em chip único.

</aside>

### Field-Progamable Gate Array - FGPA

<aside>
❗

Dispositivos de hardware programáveis e reconfiguráveis online. 

</aside>

- Podem ser do tipo PROM, EPROM e RAM;

### Memória Volátil

<aside>
❗

Memória que mantém dados armazenados durante o uso e são perdidos quando a fonte de energia for desligada;

</aside>

- Memória RAM → um dado pode ser lido ou gravado na memória em um endereço qualquer dela (randômico)

### Memória não Volátil

<aside>
❗

Memória com gravação permanente de dados;

</aside>

# Periféricos e Interfaces

### Timer

<aside>
❗

Conta os pulsos de Clock gerados pelo microcontrolador.

</aside>

- Funcionam de forma independente do MPU;
- Construídos com flip-flops;

### Contadores

<aside>
❗

Contam eventos originados externamente; 

</aside>

### Interfaces Seriais

<aside>
❗

Transporta dados entre as MPU e periféricos de forma serial; 

</aside>

- Permite que a MPU utilize o mesmo canal para se conectar a diferentes periféricos;
- Pode ser assíncrona ou síncrona
    - **Assincrona** → não utiliza nenhum tipo de recurso para sincronizar o envio/recebimento: o sincronismo consiste em o dispositivo receptor saber que esta está na hora de receber um dado.
    - **Síncrona** →  exige que os sinais de Clock do transmissor e receptor precisam estar permanentemente sincronizados.