#!/bin/bash

# Nombre del ejecutable
EXEC=programa

# Compilación
echo "Compilando..."
clang++ -std=c++17 -Wall -Wextra *.cpp -o $EXEC

# Verifica que la compilación fue exitosa
if [ $? -eq 0 ]; then
    echo "Compilación exitosa. Ejecutando..."
    echo "----------------------"
    ./$EXEC
else
    echo "Error en la compilación."
fi