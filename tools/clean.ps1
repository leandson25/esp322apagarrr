# =============================================
# clean.ps1
# Script para limpar builds antigos e arquivos temporários
# =============================================

$ProjectPath = Resolve-Path ..
$PIO = "platformio"

Write-Host "Iniciando limpeza de arquivos antigos e builds..." -ForegroundColor Cyan

# Remove builds antigos
& $PIO run --target clean --project-dir $ProjectPath

# Opcional: remover arquivos de upload de filesystem antigos
$DataUploadPath = Join-Path $ProjectPath "data/.pio_upload"
if (Test-Path $DataUploadPath) {
    Remove-Item $DataUploadPath -Recurse -Force
    Write-Host "Arquivos antigos de upload removidos." -ForegroundColor Yellow
}

Write-Host "Limpeza concluída!" -ForegroundColor Green
