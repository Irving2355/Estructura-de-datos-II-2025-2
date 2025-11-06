#!/bin/bash
# Script para automatizar git add, commit y push con fecha actual

# Obtener la fecha actual en formato DD/MM/YYYY
fecha=$(date +"%d/%m/%Y")

# Ejecutar los comandos de git
git add .
git commit -m "Clase $fecha"
git push -u origin main

# Mensaje de confirmación
echo "Cambios subidos correctamente con commit: Clase $fecha"
