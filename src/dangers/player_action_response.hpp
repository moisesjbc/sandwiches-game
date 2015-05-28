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

#ifndef PLAYER_ACTION_RESPONSE_HPP
#define PLAYER_ACTION_RESPONSE_HPP

#include "player_action.hpp"
#include <tinyxml2.h>
#include <string>
#include <stdexcept>

namespace jdb {

const int HP_ALL = 156474;

// TODO: Separate two structs "PlayerActionConditions" and
// "PlayerActionResponses" (affects XML).
struct PlayerActionResponse
{
    // Conditions
    PlayerAction playerAction;
    int minHp;
    int maxHp;

    // Responses
    int hpVariation;
    int newState;
    int newDanger; // TODO: Remove this attribute or at least invalid
    // silmultaneus state and danger transitions (affects XML).

    // When this transition is done, add this "score bonus" to player's score.
    unsigned int scoreBonus;

    // When this transitions is done, add this "hp bonuts" to player's hp.
    unsigned int hpBonus;


    /***
     * 1. Initialization
     ***/
    PlayerActionResponse( tinyxml2::XMLElement* xmlElement );


    /***
     * 2. Auxiliar methods
     ***/
    static PlayerAction getPlayerActionFromString( std::string str );
};

} // namespace jdb

#endif // PLAYER_ACTION_RESPONSE_HPP
