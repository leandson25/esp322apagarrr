#include "scheduler.h"

Scheduler::Scheduler() : _taskCount(0) {}

void Scheduler::init() {
    _taskCount = 0;
}

/**
 * @brief Agenda tarefas periódicas no ESP32 de forma simples.
 */
void Scheduler::addTask(void (*callback)(), unsigned long intervalMs) {
    if (_taskCount >= MAX_TASKS) {
        return; // Não pode adicionar mais tarefas
    }
    _tasks[_taskCount].callback = callback;
    _tasks[_taskCount].interval = intervalMs;
    _tasks[_taskCount].lastRun = millis();
    _taskCount++;
}

void Scheduler::update() {
    unsigned long now = millis();
    for (uint8_t i = 0; i < _taskCount; i++) {
        if (now - _tasks[i].lastRun >= _tasks[i].interval) {
            _tasks[i].callback();
            _tasks[i].lastRun = now;
        }
    }
}
