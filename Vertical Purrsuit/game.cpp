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
#include "Platform.h" 
#include "Score.h"
#include "Fish.h"


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

    // Platforms
    RM.loadSprite("sprites/baseplatform-spr.txt", "base-platform");
    RM.loadSprite("sprites/bottomspikeplat-spr.txt", "bottom-spike-platform");
    RM.loadSprite("sprites/spiderplatform-spr.txt", "spider-platform");
    RM.loadSprite("sprites/topbottomspikesplat.txt", "top-bottom-spike-platform");

    // Fish
    RM.loadSprite("sprites/fish-spr.txt", "fish");
}

// Populate world with objects
void populateWorld(void) {
    // Set world size (must be larger than the view size)
    df::Box world_boundary(df::Vector(0, 0), 78, 5000); 
    WM.setBoundary(world_boundary); 

    // Set the initial view size
    df::Box view_window(df::Vector(0, 216), 80, 24);  // Centered on Cat 
    WM.setView(view_window); 

    Cat* cat = new Cat(); 
    Floor* floor = new Floor(); 
    Score* score = new Score(cat);
    
    for (float y = 0; y < 4990; y += 10) {
        Platform* platform = new Platform(y + ((rand() % 1) + 1));

        // Spawn a Fish 5 percent of the time
        if ((rand() % 100) < 5) {
            new Fish(platform);

        }
    }

    // Ensure view follows the Cat
    WM.setViewFollowing(cat); 
}