```markdown
# Introduction

O projeto **"bar_chart_race"** é uma aplicação em C++ que cria uma animação de gráfico de barras a partir de um conjunto de dados. O programa lê os dados de um arquivo de entrada, processa e armazena essas informações na memória, e então gera uma animação que mostra a evolução dos dados ao longo do tempo. A aplicação permite a personalização de parâmetros, como o número de frames e o número de barras exibidas na animação, proporcionando uma visualização dinâmica e interativa dos dados.

---

## Compilação

### 1. Utilizando o `g++`

Para compilar diretamente utilizando o compilador `g++`, utilize o seguinte comando:

```bash
g++ -Wall -std=c++17 source/main.cpp source/rsc/*.cpp -I source/rsc -o bar_chart_race
```

### 2. Utilizando o `CMake`

O projeto também suporta a compilação com o `CMake`. Siga as etapas abaixo:

1. Gere os arquivos de build:
   ```bash
   cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
   ```

2. Compile o projeto:
   ```bash
   cmake --build build
   ```

3. Instale o binário (opcional):
   ```bash
   cmake --install build --prefix /usr/local
   ```

O executável gerado estará disponível no diretório `build` ou no caminho especificado durante a instalação.

---

## Execução

Após compilar o projeto, execute o programa com a seguinte sintaxe:

```bash
./bar_chart_race -f <número_de_frames> -b <número_de_barras> <caminho_para_arquivo_de_dados>
```

- **`-f`**: Define o número de frames para a animação.
- **`-b`**: Especifica o número de barras a serem exibidas.
- **`<caminho_para_arquivo_de_dados>`**: Caminho para o arquivo contendo os dados a serem processados.

---
```
