#pragma once
#include "Ledgers/GameLedgers.hpp"

class InputOrchestrator {
public:
    /**
     * @brief Polls the hardware for keyboard events and updates the dispatch.
     * @param ledger The ledger to be updated with the current input state.
     */
    void execute(InputLedger& ledger);
};