#pragma once

#include <Arduino.h>
#include <Preferences.h>

class Storage {
public:
    Storage();

    // Inicialização
    bool init();                          // Inicializa com namespace padrão
    bool begin(const char* namespaceName); // Inicializa com namespace específico
    void end();                           // Finaliza e libera recursos

    // Operações de storage
    void saveString(const String& key, const String& value);
    String loadString(const String& key, const String& defaultValue);
    void saveInt(const String& key, int value);
    int loadInt(const String& key, int defaultValue);

    // Métodos do ciclo de vida
    void loadConfig();  // Carrega configurações salvas
    void update();      // Atualização periódica

    // Verifica se está inicializado
    bool isInitialized() const { return _initialized; }

private:
    Preferences _prefs;
    bool _initialized;
};
