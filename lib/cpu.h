#ifndef SIMULATOR_CPU_H
#define SIMULATOR_CPU_H


#include "multidimensional_array.h"
#include "core.h"
#include "memory.h"
#include "settings.h"


class Cpu
{
public:
    Cpu();

    void Start();

    Cpu(Cpu&) = delete;

    Cpu& operator=(Cpu&) = delete;

private:
    void linkCores();

    bool running;
    CoreArray cores;
    Memory_t mem;
};


#endif //SIMULATOR_CPU_H