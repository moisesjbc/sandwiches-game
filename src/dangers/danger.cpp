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

#include "danger.hpp"

namespace jdb {

Danger::Danger( DangerDataPtr dangerData_ ) :
    Animation( dangerData_->animationData[ rand() % dangerData_->animationData.size()] )
{
    setDangerData( dangerData_ );
}


/***
 * 2. Getters
 ***/

float Danger::getDamage() const
{
    return hp * dangerData->damageFactor;
}


DangerDataPtr Danger::getDangerData() const
{
    return dangerData;
}

/***
 * 3. Setters
 ***/
// TODO: Overload Animation setters.
void Danger::setDangerData( DangerDataPtr dangerData_ )
{
    dangerData = dangerData_;

    setAnimationData( dangerData->animationData[0] );

    reset();
}

void Danger::setState( int newState )
{
    state = newState;

    setAnimationState( (dangerData->states[newState]).animationState );
}


/***
 * 4. Updating
 ***/

bool Danger::playerAction( PlayerAction playerAction )
{
    unsigned int i = 0;
    bool foundResponse = false;
    const PlayerActionResponse* playerActionResponse;

    // Iterate over the current state's vector of player action responses.
    while( ( i < dangerData->states[state].playerActionResponses.size() )
           && !foundResponse ){

        // Get the current player action response.
        playerActionResponse = &( dangerData->states[state].playerActionResponses[i] );

        // Check if the player action and the current danger's state meets the
        // conditions for applying this response.
        if( ( playerAction == playerActionResponse->playerAction ) &&
              ( hp >= playerActionResponse->minHp ) &&
              ( hp <= playerActionResponse->maxHp ) ){
            foundResponse = true;
        }else{
            i++;
        }
    }

    // If we found the right player action response, we apply it here.
    if( i < dangerData->states[state].playerActionResponses.size() ){

        if( playerActionResponse->hpVariation == HP_ALL ){
            hp = 0;
        }else{
            if( playerActionResponse->dangerPerSecond ){
                hp += playerActionResponse->hpVariation * FPS_INVERSE;
            }else{
                hp += playerActionResponse->hpVariation;
            }
        }

        if( playerActionResponse->newState != -1 ){
            setState( playerActionResponse->newState );
        }

        return true;
    }

    return false;
}


void Danger::reset()
{
    hp = dangerData->initialHp;
    setState( dangerData->initialState );
}

} // namespace jdb