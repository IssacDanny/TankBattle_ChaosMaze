#pragma once
#include "Ledgers/GameLedgers.hpp"
#include "Orchestrators/TimeOrchestrator.hpp"
#include "Orchestrators/InputOrchestrator.hpp"
#include "Orchestrators/WorldUpdateOrchestrator.hpp"
#include "Orchestrators/RenderOrchestrator.hpp"

class GameLoopOrchestrator {
private:
    // The Ledgers (S)
    TimeLedger    time;
    InputLedger   input;
    WorldLedger   world;
    DisplayLedger display;

    // The High Command (Primary Orchestrators)
    TimeOrchestrator        timeOfficer;
    InputOrchestrator       inputOfficer;
    WorldUpdateOrchestrator worldOfficer;
    RenderOrchestrator      renderOfficer;

    // Private helper to initialise the hardware and load assets
    bool initialise();
    void shutdown();

public:
    /**
     * @brief The entry point of the Game.
     * Contains the primary reactive loop.
     */
    void execute();
};