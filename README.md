
---

# **Bar Chart Race**

### **Table of Contents**
1. [Introduction](#introduction)
2. [Input](#input)
3. [Interface](#interface)
4. [Execution](#execution)
5. [System Modeling](#system-modeling)
6. [Output](#output)

---

### **Introduction**

O **Bar Chart Race** é uma aplicação terminal que apresenta uma animação baseada em _bar charts_ (gráficos de barras), mostrando a evolução de dados categóricos ao longo do tempo. Este tipo de visualização é útil para compreender tendências em conjuntos de dados históricos ou dinâmicos.

Cada gráfico consiste em até 15 barras, organizadas por ordem decrescente de valores. O objetivo é criar uma "corrida" visual, onde barras sobem ou descem conforme seus valores variam ao longo dos _frames_ de animação.

---

### **Input**

O sistema lê arquivos de dados no formato **CSV** (_comma-separated values_). O arquivo deve conter as seguintes informações:

- **Cabeçalho** (três primeiras linhas):
  1. Título do gráfico.
  2. Rótulo associado aos valores das barras.
  3. Fonte dos dados.

- **Configuração do gráfico**:
  - Número total de barras a serem exibidas por gráfico.

- **Dados das barras** (uma linha por barra):
  ```
  time_stamp, label, other_info, value, category
  ```
  - **time_stamp**: Momento em que os dados foram coletados (ex.: ano).
  - **label**: Nome do item representado.
  - **other_info**: Informações adicionais (não usadas na visualização).
  - **value**: Valor numérico representado pela barra.
  - **category**: Categoria para mapear cores às barras.

---

### **Interface**

A aplicação é controlada via linha de comando. O formato de uso é:

```
./bcr [<options>] <input_data_file>
Options:
  -b  <num>   Máximo de barras exibidas por gráfico (1 a 15). Default: 5.
  -f  <num>   Velocidade da animação em FPS (1 a 24). Default: 24.
```

**Nota**: Caso o número de barras ou a velocidade não sejam especificados, os valores padrão serão usados.

---

### **Execution**

A execução do programa segue os passos abaixo:

1. Leitura do arquivo de entrada e armazenamento dos dados em memória.
2. Exibição de um resumo das informações do arquivo e categorias encontradas.
3. Início da animação, com gráficos sendo renderizados no terminal.
4. Pausas entre os gráficos para respeitar o _frame rate_ configurado pelo usuário.

#### Estrutura básica do sistema:

- `BarItem`: Representa uma barra individual com `label`, `value`, e `category`.
- `BarChart`: Representa um gráfico completo, contendo um conjunto de barras e um _time_stamp_.
- `Database`: Armazena todos os gráficos do dataset.
- `AnimationManager`: Gerencia o fluxo de execução, leitura de dados, e animação.

---

### **System Modeling**

A animação segue os seguintes estados:

1. **Leitura de dados**: Processa o arquivo de entrada.
2. **Configuração inicial**: Exibe resumo das informações lidas.
3. **Animação**: Exibe os gráficos de barras sequencialmente no terminal.
4. **Encerramento**: Finaliza o programa após a animação.

---

### **Output**

Cada _bar chart_ exibe:

- **Título principal**: Explica o tema dos dados.
- **Título secundário**: Data ou momento do gráfico (ex.: ano).
- **Barras**: Linhas horizontais coloridas, proporcionalmente ao valor representado.
  - Máximo de 15 barras por gráfico.
  - Barras organizadas em ordem decrescente de valor.
- **Eixo X**: Indica valores de referência com marcações (`+`).
- **Legenda de cores**: Mapeia categorias às cores usadas.
- **Fonte dos dados**: Referência ao autor ou instituição responsável.

A animação ocorre em _frames_ sucessivos, simulando a evolução dos dados ao longo do tempo.

---

### **Como executar**

Certifique-se de compilar o projeto corretamente. O comando abaixo é um exemplo para execução da animação com 10 barras e 12 FPS:

```bash
./bcr -b 10 -f 12 cities.dat
```

---

 &copy; DIMAp/UFRN 2020-2024. 