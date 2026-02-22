# =============================================
# monitor.ps1
# Script para monitorar logs do ESP32 via serial
# =============================================

$Port = "COM3"         # Altere conforme sua porta
$Baud = 115200

Write-Host "Abrindo monitor serial na porta $Port com baudrate $Baud..." -ForegroundColor Cyan

# Plataforma PlatformIO serial monitor
$PIO = "platformio"
& $PIO device monitor --port $Port --baud $Baud
