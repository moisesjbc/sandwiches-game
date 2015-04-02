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

#include "survival_level.hpp"

namespace jdb {

SurvivalLevel::SurvivalLevel( sf::RenderWindow& window, SoundManager* soundManager, unsigned int levelIndex ) :
    Level( window, soundManager, levelIndex )
{}


/***
 * 2. Level loading
 ***/

void SurvivalLevel::load( unsigned int index )
{
    tinyxml2::XMLNode* levelNode = nullptr;
    unsigned int i = 0;

    // Open the levels configuration file.
    xmlFile.LoadFile( "data/config/levels.xml" );

    // Iterate over the survival level XML nodes until de number index.
    levelNode = ( xmlFile.FirstChildElement( "levels" )->FirstChildElement( "survival_levels" )->FirstChildElement( "survival_level" ) );
    while( levelNode && ( i < index ) ){
        levelNode = levelNode->NextSiblingElement( "survival_level" );
        i++;
    }

    // If the index XML node doesn't exist, throw an exception.
    if( i < index ){
        throw std::runtime_error( "ERROR: Survival level not found" );
    }

    // Load the sandwiches data.
    loadSandwichData();

    // Load the dangers data.
    loadDangerData();

    // Get the conveyor belt parameters.
    conveyorBelt_.load( (tinyxml2::XMLElement*)levelNode->FirstChildElement( "speed" ) );
}


/***
 * 3. Main loop
 ***/

bool SurvivalLevel::victory() const
{
    return false;
}


bool SurvivalLevel::defeat() const
{
    return (jacobHp_ <= 0);
}


void SurvivalLevel::updateLevelTime( unsigned int ms )
{
    levelTime_ += ms;
}


void SurvivalLevel::resetLevelTime()
{
    levelTime_ = 0;
}

} // namespace jdb
