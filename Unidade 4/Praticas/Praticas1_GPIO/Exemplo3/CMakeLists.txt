# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# Generated CMake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Detecta o sistema operacional e define caminho do pico-vscode.cmake
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()

set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)

if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Importa o SDK do Raspberry Pi Pico
include(pico_sdk_import.cmake)

# Nome do projeto
project(Exemplo3 C CXX ASM)

# Inicializa o SDK do Raspberry Pi Pico
pico_sdk_init()

# Define o executável principal (Exemplo3)
add_executable(Exemplo3 Exemplo3.c)

# Configurações do projeto
pico_set_program_name(Exemplo3 "Exemplo3")
pico_set_program_version(Exemplo3 "0.1")

# Ativa/desativa saída UART/USB
pico_enable_stdio_uart(Exemplo3 1)
pico_enable_stdio_usb(Exemplo3 0)

# Inclui arquivos de cabeçalho
target_include_directories(Exemplo3 PRIVATE ${CMA

