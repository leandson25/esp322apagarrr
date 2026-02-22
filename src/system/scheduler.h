#pragma once
#include <Arduino.h>

#define MAX_TASKS 10

struct Task {
    void (*callback)();
    unsigned long interval;
    unsigned long lastRun;
};

class Scheduler {
public:
    Scheduler();
    
    // Inicializa o scheduler
    void init();
    
    void addTask(void (*callback)(), unsigned long intervalMs);
    void update();

private:
    Task _tasks[MAX_TASKS];
    uint8_t _taskCount;
};
