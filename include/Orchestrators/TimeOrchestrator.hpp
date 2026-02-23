#pragma once
#include "Ledgers/GameLedgers.hpp"

class TimeOrchestrator {
public:
    /**
     * @brief Calculates the elapsed time since the last frame.
     * @param ledger The ledger to be updated with the new Delta Time.
     */
    void execute(TimeLedger& ledger);
};