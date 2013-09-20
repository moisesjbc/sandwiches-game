/***
 * Copyright 2013 Moises J. Bonilla Caraballo (Neodivert)
 *
 * This file is part of Graphic Librarian.
 *
 * Graphic Librarian is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * Graphic Librarian is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Graphic Librarian.  If not, see <http://www.gnu.org/licenses/>.
***/

#ifndef LIBRARY_HPP
#define LIBRARY_HPP

#include "drawables/sprite.hpp"
#include "dependencies/tinyxml2/tinyxml2.h"
#include <string>

namespace m2g {

class Library
{
    private:
        // Vector of tilesets.
        std::vector< std::shared_ptr< m2g::Tileset > > tilesets;

    public:
        /***
         * 1. Initialization and destruction
         ***/
        Library();


        /***
         * 2. File management
         ***/
        void loadFile( const std::string& filePath, bool developerMode = false );
        void saveFile( const char* filePath ) const ;


        /***
         * 3. Setters and getters
         ***/
        const std::shared_ptr< m2g::Tileset > getTileset( const unsigned int& index ) const ;
        const std::vector< std::shared_ptr< m2g::Tileset > >* getTilesets() const ;


        /***
         * 4. Tileset and animation data loading
         ***/
    private:
        std::shared_ptr<Tileset> loadTileset( const tinyxml2::XMLNode* xmlNode, const char* folder = nullptr, bool developerMode = false );
};

} // namespace m2g

#endif // LIBRARY_HPP
