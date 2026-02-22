# =============================================
# upload_fs.ps1
# Script para enviar a pasta data/ ao ESP32
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
Write-Host "Iniciando upload de arquivos para ESP32..." -ForegroundColor Cyan

# Executa o upload dos arquivos do filesystem
& pio run --target uploadfs --project-dir $ProjectPath

if ($LASTEXITCODE -eq 0) {
    Write-Host "Upload concluído com sucesso!" -ForegroundColor Green
    exit 0
} elseif ($LASTEXITCODE -eq 1) {
    Write-Host "Erro: ESP32 não conectado ou porta incorreta." -ForegroundColor Red
    Write-Host "Verifique a conexão USB e a configuração da porta em platformio.ini" -ForegroundColor Yellow
} else {
    Write-Host "Erro durante o upload (código: $LASTEXITCODE)." -ForegroundColor Red
}

exit $LASTEXITCODE
