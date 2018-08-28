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

#include "logging/logging.hpp"
#include <cstdio>
#include <iostream>
#include <fstream>

using namespace qub3d;

// Declarations to get rid of compiler errors
string_t Logger::m_logFile;
std::ofstream Logger::m_logFileHandle;
LogVerbosity Logger::m_vbLevel = LogVerbosity::INFO;


/* ENUM Lookup Table for the LogVerbosity enum class
 * For example, LogVerbosity::INFO is equal to 2,
 * as it is defined in the enum class. If that value
 * is used as an array index, it will return the "string"
 * version. This can then be printed, reducing the need for
 * an unnecessary switch-case statement.
 */
const char* Logger::LogVerbosityLookup[] = {
	"ERROR",
	"WARNING",
	"INFO",
	"DEBUG"
};

void Logger::init( string_t logFile, LogVerbosity verbosityLevel = LogVerbosity::INFO)
{
	// Setting the filenames
	Logger::m_logFile = logFile;

	Logger::m_vbLevel = verbosityLevel;

	// Creating the files
	Logger::m_logFileHandle.open( Logger::m_logFile );
}

void Logger::destroy()
{
	Logger::m_logFileHandle.close();
}

void Logger::logMessage( string_t errorFile, int lineNumber, string_t message, LogVerbosity verbosity)
{
	if (verbosity <= Logger::m_vbLevel ) // Make sure the logging call has a verbosity level below the defined level set at initialisation.
	{
		std::cout << "[" << Logger::LogVerbosityLookup[static_cast<int>(verbosity)] << "] "; // Add the [INFO]/etc... at the beginning, via the use of a lookup table.

		if (verbosity != LogVerbosity::INFO) // Print the erroring file and line number if the message is not classed as INFO
		{
			std::cout<< errorFile << ":" << lineNumber << " ";
		}

		std::cout << message << std::endl;
	}
}
