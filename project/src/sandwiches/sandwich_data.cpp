/***
    Copyright 2013 Moises J. Bonilla Caraballo (Neodivert)

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

#include "sandwich_data.hpp"

namespace jdb {


/***
 * 1. Initialization
 ***/

SandwichData::SandwichData( tinyxml2::XMLElement* xmlElement )
{
    loadFromXML( xmlElement );
}


/***
 * 2. Loading
 ***/

void SandwichData::loadFromXML( tinyxml2::XMLElement* xmlElement )
{
    m2g::GraphicsLoader graphicsLoader;

    std::cout << "Loading SandwichData from XML: " << std::endl;

    graphicsLoader.loadAnimationData( animationData, "data/img/sandwiches", "sandwich_01.png" );

    baseLine.loadFromXML( xmlElement->FirstChildElement( "base_line" ) );
    std::cout << "SandwichData - base line: (x: " << baseLine.x << ", y: " << baseLine.y << ", width: " << baseLine.width << ")" << std::endl;
}


} // namespace jdb