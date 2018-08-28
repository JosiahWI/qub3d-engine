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
#include "types.hpp"
#include <iostream>
#include <fstream>

/*
 * These macros are to simplify the logging system, calling just FATAL/ERROR/etc...
 * will automatically sort out the function call, making the code cleaner and easier to read.
*/
#define ERROR(message)   qub3d::Logger::logMessage(__FILE__,__LINE__,message, qub3d::LogVerbosity::ERROR)
#define WARNING(message) qub3d::Logger::logMessage(__FILE__,__LINE__,message, qub3d::LogVerbosity::WARNING)
#define INFO(message)    qub3d::Logger::logMessage(__FILE__,__LINE__,message, qub3d::LogVerbosity::INFO)
#define DEBUG(message)   qub3d::Logger::logMessage(__FILE__,__LINE__,message, qub3d::LogVerbosity::DEBUG)

namespace qub3d
{

/* ENUM CLASS for the Logging Verbosity
 * This is what will define whether certain messages are outputted or not.
 *
 * ERROR -> Is for critical messages that result in FAILURES"
 * WARNING-> More verbose logging, for errors that are not FATAL, but are errors none-the-less
 * INFO -> For important information which can aid finding problems quickly
 * DEBUG-> For absolutely everything, like entering a function to exiting the function.
 */
enum class LogVerbosity
{
	ERROR = 0,
	WARNING = 1,
	INFO = 2,
	DEBUG= 3,
};

class Logger
{
public:
	Logger() {}
	~Logger() {}

	// Initialization of logging object
	static void init( string_t logFile, LogVerbosity vbLevel );

	// Destroy the logging object
	static void destroy();

	// Output the message, while keeping in mind the verbosity level
	static void logMessage( string_t errorFile, int lineNumber, string_t message, LogVerbosity verbosity);


private:
	static string_t m_logFile;
	static std::ofstream m_logFileHandle;
	static LogVerbosity m_vbLevel;

	// The lookup table for ENUM
	static const char* LogVerbosityLookup[];
};

} // namespace qub3d
