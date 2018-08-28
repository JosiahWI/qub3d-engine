/*
 *	 Copyright (C) 2018 Qub³d Engine Group.
 *	 All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without modification,
 *  are permitted provided that the following conditions are met:
 * 
 *  1. Redistributions of source code must retain the above copyright notice, this
 *  list of conditions and the following disclaimer.
 *  
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *  this list of conditions and the following disclaimer in the documentation and/or
 *  other materials provided with the distribution.
 *  
 *  3. Neither the name of the copyright holder nor the names of its contributors
 *  may be used to endorse or promote products derived from this software without
 *  specific prior written permission.
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 *  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 *  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "gameIOManager.hpp"

using namespace qore::game;

GameIOManager::GameIOManager( )
{

}

GameIOManager::~GameIOManager( )
{

}

void GameIOManager::init(const string_t& gamePath )
{
    m_gamePath = gamePath;
}

string_t GameIOManager::getLuaScriptsPath( )
{
    return m_gamePath + "/LuaScripts";
}

string_t GameIOManager::getAssetsPath( AssetType type )
{
    switch ( type )
    {
        case AssetType::MODELS:
            return m_gamePath + "/Models";
        case AssetType::TEXTURES:
            return m_gamePath + "/Textures";
    }
    return 0;
}

string_t GameIOManager::getConfigurationPath( )
{
    return m_gamePath + "/Configuration";
}

string_t GameIOManager::getTexturePath( TextureType type )
{
    string_t partialPath = m_gamePath + getAssetsPath( AssetType::TEXTURES );

    switch ( type )
    {
        case TextureType::GUI:
            return partialPath + "/GUI";
        case TextureType::QUBES:
            return partialPath + "/Qubes";
        case TextureType::ITEMS:
            return partialPath + "/Items";
        case TextureType::ENTITIES:
            return partialPath + "/Entities";
        case TextureType::EFFECTS:
            return partialPath + "/Effects";
        case TextureType::MISC:
            return partialPath + "/Misc";
        case TextureType::ENVIRONMENT:
            return partialPath + "/Environment";
        default:
            return 0;
    }
}
