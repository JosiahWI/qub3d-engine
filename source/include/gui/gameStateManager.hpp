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

#pragma once
#include <vector>
#include <memory>
#include "gui/states/gameState.hpp"
#include "gui/states/stateMap.hpp"

// This is for the Client to manipulate the states independently.

enum class StateManip
{
    NONE, POP, PUSH, REPLACE,
};

/*
 * This class allows for easy management of
 * the different states that the game might
 * such as the main menus
 */
class GameStateManager
{
public:

    explicit GameStateManager(std::shared_ptr<StateMap> stateMap);
    ~GameStateManager();

    void init(const string_t& name);

    void step();

    void exit();

    void manipStates();

    std::shared_ptr<StateMap> getStateMap();

    //-------------------------------------------------------//
    //                 Game Runtime Functions                //
    //-------------------------------------------------------//

    // This calls the current GameState's drawing function.
    void draw();

    // This calls the current GameState's update function.
    void update();

    void handleEvent(SDL_Event& event);

    // These functions are for handling the GameState stack.

    // For pushing a state onto the top of the stack.
    void pushState(const string_t& newState);
    // For pulling one off of the stack.
    void popState();

    // For setting the current state I.E. "MAINMENU->(pushes)LOADING->(sets)PLAYING",
    // so this can happen "PLAYING->(pop)MAINMENU"
    void setState(const string_t& newState);

private:
    void push(const string_t& newState);
    void pop();
    void set(const string_t& newState);

protected:
    std::shared_ptr< StateMap > m_stateMap;
    // The stack of GameStates for easy transition handling
    std::vector< std::shared_ptr<GameState> > m_stateStack;
    StateManip m_switchStates;
    string_t m_newState;
};
