#include "CommandClass.h"
#include <boost/process.hpp>
using namespace boost::process;

/*
 * Dylan Nasution
 * CS3307A
 */

// Empty parameter constructor
CommandClass::CommandClass() {
	command_text = "";
	result = "";
	return_code = 0;
}

// Constructor definition
CommandClass::CommandClass(std::string command) {
	command_text = command;
	result = "";
	return_code = 0;
}

// Destructor definition
CommandClass::~CommandClass() {
}

void CommandClass::execute() {
	ipstream pipe_stream;
	
	// executes commands through child process
        try {
                child c(command_text, (std_out & std_err) > pipe_stream);
		
		std::string line;

                while (pipe_stream && std::getline(pipe_stream, line)) {
			// copy each line of the output into result
			result += line + "\n";
                }
			
                c.wait();
		// copy exit code value into return_code
		return_code = c.exit_code();
        }

        catch (boost::process::process_error e) {
		result = e.what();

		return_code = -1;
        }
}

// Getter definitions
std::string CommandClass::get_command_text() {
	return command_text;
}

std::string CommandClass::get_result() const {
        return result;
} 

int CommandClass::get_return_code() const {
        return return_code;
}

// Setter definitions
void CommandClass::set_command_text(std::string new_command){
	command_text = new_command;
}
