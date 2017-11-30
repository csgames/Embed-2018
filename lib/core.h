#ifndef SIMULATOR_CORE_H
#define SIMULATOR_CORE_H

#include "memory.h"
#include "registers.h"

#include "impl/instruction_factory.h"


class CoreArray;


class Core
{
public:
    Core();

    Core(CoreArray& cores, size_t id, const MemoryInterface& mem);

    void wire(uint8_t membank);

    void initialize();

    void preload();

    void fetch();

    bool execute(const InstructionBase& raw_instruction);

    void step();

    InstructionFactory& get_factory();

    bool operator==(const Core&) const;

    Core(Core&& core) = default;

    Core(Core&) = delete;

    Core& operator=(Core&) = delete;

private:
    Registers registers;
    InstructionFactory factory;

    const MemoryInterface* mem;
    CoreArray* cores;  // TODO: make const

    friend std::ostream& operator<<(std::ostream& os, const Core& core);
};


#endif //SIMULATOR_CORE_H
