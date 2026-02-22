# =============================================
# build.ps1
# Script para compilar o firmware ESP32
# =============================================

# Verifica se PlatformIO está instalado
$PIO = Get-Command platformio -ErrorAction SilentlyContinue

if (-not $PIO) {
    Write-Host "Erro: PlatformIO não encontrado." -ForegroundColor Red
    Write-Host "Instale com: pip install platformio" -ForegroundColor Yellow
    exit 1
}

# Tenta obter o caminho do projeto
try {
    $ProjectPath = Split-Path -Parent $PSScriptRoot
    if (-not $ProjectPath) {
        $ProjectPath = Get-Location
    }
} catch {
    Write-Host "Erro: Não foi possível determinar o diretório do projeto." -ForegroundColor Red
    exit 1
}

Write-Host "Caminho do projeto: $ProjectPath" -ForegroundColor Cyan
Write-Host "Iniciando compilação do firmware ESP32..." -ForegroundColor Cyan

# Executa build completo
& pio run --project-dir $ProjectPath

if ($LASTEXITCODE -eq 0) {
    Write-Host "Compilação concluída com sucesso!" -ForegroundColor Green
    exit 0
} else {
    Write-Host "Erro na compilação do firmware (código: $LASTEXITCODE)." -ForegroundColor Red
    exit $LASTEXITCODE
}
