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

#include "gui/gameStateManager.hpp"
#include "logging/logging.hpp"

GameStateManager::GameStateManager( std::shared_ptr<StateMap> stateMap  )
{
    m_stateMap = stateMap;
}

GameStateManager::~GameStateManager( )
{

}

void GameStateManager::init( const string_t& name )
{
	// Add the first state onto the stack so that things can happen.
	m_stateMap->initStateMap( );
	m_stateStack.push_back( m_stateMap->getStateByName( name ) );
	m_stateStack.back( )->enter( );
}

void GameStateManager::step()
{
    SDL_Event event;
    while ( SDL_PollEvent( &event ) )
    {
        handleEvent( event );
    }
    // Updating before drawing to allow for ImGui to render properly
    update( );
    draw( );
    // Change states if needed
    manipStates();
}

void GameStateManager::exit( )
{
	m_stateStack.back( )->exit( );
}

void GameStateManager::manipStates()
{
    switch ( m_switchStates )
    {
    // Move on if the state doesn't need to be changed
    case StateManip::NONE:
        break;
    case StateManip::PUSH:
        DEBUG("Pushing new state: " + m_newState);
        push( m_newState );
        break;
    case StateManip::POP:
        DEBUG("Popping State");
        pop( );
        break;
    case StateManip::REPLACE:
        DEBUG("Replacing current state with: " + m_newState);
        set( m_newState );
        break;
    }
    // Always reset the switch to avoid bugs.
    m_switchStates = StateManip::NONE;
}

std::shared_ptr<StateMap> GameStateManager::getStateMap( )
{
	return m_stateMap;
}



//-------------------------------------------------------//
//                 Game Runtime Functions                //
//-------------------------------------------------------//

/*
 * Function for calling the current state's drawing function
 */
void GameStateManager::draw( )
{
	m_stateStack.back( )->draw( );
}

/*
 * Function for calling the current state's update function
 */
void GameStateManager::update( )
{
	m_stateStack.back( )->update( );
}

/*
 * Function for handling the current state's events
 */
void GameStateManager::handleEvent( SDL_Event& event )
{
	m_stateStack.back( )->handleEvent( event );
}

//-------------------------------------------------------//
//                    Stack Functions                    //
//-------------------------------------------------------//

/*
 * Push a state onto the front of the stack
 */
void GameStateManager::pushState( const string_t& newState )
{
    m_newState = newState;
    m_switchStates = StateManip::PUSH;
}

/*
 * Pull a state off of the stack
 */
void GameStateManager::popState( )
{
    m_switchStates = StateManip::POP;
}

/*
 * Set the current state directly
 */
void GameStateManager::setState( const string_t& newState )
{
    m_newState = newState;
    m_switchStates = StateManip::REPLACE;
}

/*
 * Push a state onto the front of the stack
 */
void GameStateManager::push( const string_t& newState )
{
    /*
     * When we change states, we want to ensure nothing
     * conflicts with each other. To do that we run
     * exit code, change the state, then run entry code.
     */
    m_stateStack.back( )->exit( );
    m_stateStack.push_back( m_stateMap->getStateByName( newState ) );
    m_stateStack.back( )->enter( );
}

/*
 * Pull a state off of the stack
 */
void GameStateManager::pop( )
{
    /*
     * When we change states, we want to ensure nothing
     * conflicts with each other. To do that we run
     * exit code, change the state, then run entry code.
     */
    m_stateStack.back( )->exit( );
    m_stateStack.pop_back( );
    m_stateStack.back( )->enter( );
}

/*
 * Set the current state directly
 */
void GameStateManager::set( const string_t& newState )
{
    /*
     * When we change states, we want to ensure nothing
     * conflicts with each other. To do that we run
     * exit code, change the state, then run entry code.
     */
    m_stateStack.back( )->exit( );
    m_stateStack.back( ) = m_stateMap->getStateByName( newState );
    m_stateStack.back( )->enter( );

}
