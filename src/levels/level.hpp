/***
    Copyright 2013, 2014 Moises J. Bonilla Caraballo (Neodivert)

    This file is part of JDB.

    JDB is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    JDB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with JDB.  If not, see <http://www.gnu.org/licenses/>.
 ***/

#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SDL2/SDL.h>
#include "../sandwiches/sandwich.hpp"
#include "../utilities/timer.hpp"
#include "../dangers/danger.hpp"
#include "../tools/tool.hpp"
#include "conveyor_belt.hpp"
#include "../dependencies/m2g/src/drawables/drawables_set.hpp"
#include "../dependencies/m2g/src/text/text_renderer.hpp"

namespace jdb {

class Level
{
    public:
        /***
         * 1. Construction
         ***/
        Level( SDL_Window* window_,
               SDL_Surface* screen_,
               unsigned int screenWidth,
               unsigned int screenHeight );


        /***
         * 2. Level execution
         ***/
        void run( unsigned int levelIndex );


    protected:
        /***
         * 3. Level Loading
         ***/
        virtual void load( unsigned int levelIndex ) = 0;
        void loadSandwichData();
        void loadDangerData();


        /***
         * 4. Main loop
         ***/
        void mainLoop();
        void handleUserInput( const SDL_Event& event, Sandwich** sandwiches );
        virtual bool finishPredicate() const = 0;
        virtual void resetTimer() = 0;


        /***
         * 5. Auxiliar methods
         ***/
        void drawTimer( int time );
        int getSeconds() const ;


    private:
        /***
         * 6. Initialization
         ***/
        void initGUI();


    protected:
        /***
         * Attributes
         ***/
        Timer timer_;

        ConveyorBelt conveyorBelt_;

        tinyxml2::XMLDocument xmlFile;

        m2g::GraphicsLibrary graphicsLibrary_;

        std::vector< DangerDataPtr > dangerData;
        std::vector< SandwichDataPtr > sandwichData;

        SDL_Window* window;
        SDL_Surface* screen;

        std::mutex coutMutex;

        // Players tool
        ToolPtr tool_;

        // Jacob's life
        int jacobHp_;

        // GUI sprites.
        m2g::DrawablesSet guiSprites_;
        m2g::SpritePtr guiToolSelector_;

        // Does player wants to quit the current level?
        bool quitLevel_;

    private:
        glm::mat4 projectionMatrix;
};

} // namespace jdb

#endif // LEVEL_HPP
