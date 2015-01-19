/***
    Copyright 2013 - 2015 Moises J. Bonilla Caraballo (Neodivert)

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

#include "main_menu.hpp"
#include <m2g/text/text_renderer.hpp>
#include "../levels/campaign_level.hpp"
#include "../levels/survival_level.hpp"
#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

namespace jdb {

/***
 * 1. Creation
 ****/

MainMenu::MainMenu( Window &window, SoundManager* soundManager ) :
    GameState( window ),
    gui_( window.renderer, { 0, 0, 800, 600 } ), // TODO: Retrieve dimensions from window.
    soundManager_( *soundManager )
{}


/***
 * 3. GameState interface
 ***/

void MainMenu::init()
{
    m2g::TextButtonPtr startCampaignButton( new m2g::TextButton( window_.renderer, "Play campaign" ) );
    startCampaignButton->setPressCallback( [this](){
        std::unique_ptr< Level > level = std::unique_ptr< Level >(
                   new CampaignLevel( window_, &soundManager_, 0 ) );
        level->run();
    });

    m2g::TextButtonPtr startSurvivalButton( new m2g::TextButton( window_.renderer, "Play survival" ) );
    startSurvivalButton->setPressCallback( [this](){
        std::unique_ptr< Level > level = std::unique_ptr< Level >(
                   new SurvivalLevel( window_, &soundManager_, 0 ) );
        level->run();
    });

    m2g::TextButtonPtr exitButton( new m2g::TextButton( window_.renderer, "Exit" ) );
    exitButton->setPressCallback( [this](){
        requestStateExit();
    });

    gui_.addWidget( std::move( startCampaignButton) );
    gui_.addWidget( std::move( startSurvivalButton ) );
    gui_.addWidget( std::move( exitButton ) );
}


void MainMenu::handleEvents()
{
    SDL_Event event;
    std::unique_ptr< Level > level = nullptr;

    SDL_PollEvent( &event );
    if( gui_.handleEvent( event ) ){
        return;
    }
    if( ( event.type == SDL_QUIT ) ||
            ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE ) ){
        requestStateExit();
    }
}


void MainMenu::update()
{
}


void MainMenu::draw()
{
    SDL_SetRenderDrawColor( window_.renderer, 0xDC, 0xF1, 0xF1, 0xFF );
    SDL_RenderClear( window_.renderer );

    gui_.draw();

    SDL_RenderPresent( window_.renderer );
}

void MainMenu::pause()
{
}

void MainMenu::resume()
{

}

} // namespace jdb
