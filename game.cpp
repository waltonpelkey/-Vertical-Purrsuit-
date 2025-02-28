//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes
#include "Cat.h"
#include "Floor.h"  


// Function prototypes
void loadResources(void); 
void populateWorld(void);

int main(int argc, char* argv[]) {

    // Start up game manager.
    df::GameManager& game_manager = df::GameManager::getInstance();
    if (game_manager.startUp()) {
        df::LogManager& log_manager = df::LogManager::getInstance();
        log_manager.writeLog("Error starting game manager!");
        game_manager.shutDown();
        return 0;
    }

    // Set flush of logfile during development (when done, make false).
    LM.setFlush(true);

    // Show splash screen.
    df::splash();

    // Load game resources.
    loadResources();

    // Populate game world with some objects
    populateWorld(); 

    // Run game (block until game loop is over)
    GM.run();

    // Shut everything down.
    game_manager.shutDown(); 
}

// Load resources like sprites, sound effects, or music
void loadResources(void) {
    // Load Cat Sprites
    // Cat walking
    RM.loadSprite("sprites/cat-walking-left-spr.txt", "cat-walking-left");
    RM.loadSprite("sprites/cat-walking-right-spr.txt", "cat-walking-right");

    // Cat moving up
    RM.loadSprite("sprites/cat-rising-left-spr.txt", "cat-rising-left");
    RM.loadSprite("sprites/cat-rising-right-spr.txt", "cat-rising-right");

    // Cat moving down
    RM.loadSprite("sprites/cat-dropping-left-spr.txt", "cat-dropping-left");
    RM.loadSprite("sprites/cat-dropping-right-spr.txt", "cat-dropping-right");

    // Cat idle
    RM.loadSprite("sprites/cat-idle-spr.txt", "cat-idle");

    // Floor
    RM.loadSprite("sprites/ground-spr.txt", "floor");
}

// Populate world with objects
void populateWorld(void) {
    new Cat; 
    new Floor;
}