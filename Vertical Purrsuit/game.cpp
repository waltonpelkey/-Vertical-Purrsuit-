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
#include "Catnip.h"
#include <DisplayManager.h>


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
    // df::splash();

    // Load game resources.
    loadResources();

    // Populate game world with some objects
    populateWorld(); 

    DM.setBackgroundColor(df::WHITE);

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

    // Catnip
    RM.loadSprite("sprites/catnip-spr.txt", "catnip");

    // Sounds
    RM.loadSound("audio/meow-1.wav", "meow-1");
    RM.loadSound("audio/meow-2.wav", "meow-2");
    RM.loadSound("audio/meow-3.wav", "meow-3");
    RM.loadSound("audio/meow-4.wav", "meow-4");
    RM.loadSound("audio/grounded-1.wav", "grounded-1");
    RM.loadSound("audio/grounded-2.wav", "grounded-2");
    RM.loadSound("audio/grounded-3.wav", "grounded-3");
    RM.loadSound("audio/grounded-4.wav", "grounded-4");
    RM.loadSound("audio/cat-reverb.wav", "cat-reverb");

    // Music
    RM.loadMusic("audio/background-music.wav", "background-music");
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

        // Spawn a Fish 20 percent of the time
        if ((rand() % 100) < 20) {
            new Fish(platform);
        }
        // Spawna  catnip 4 percent of the time
        else if ((rand() % 100) < 4){
            new Catnip(platform);
        }
    }

    // Ensure view follows the Cat
    WM.setViewFollowing(cat); 
}