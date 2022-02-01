#ifndef COMMAND_CLASS_H
#define COMMAND_CLASS_H

#include <string>
/*
 Dylan Nasution
 CS3307A
 */
class CommandClass {
	private:
		std::string command_text; // name of command and parameters
		std::string result; // captured output (standard output or error)
		int return_code; // 0 if success, -1 if error

	public:
		// Empty parameter constructor
		CommandClass();

		// Constructor
		CommandClass(std::string command);

		// Destructor
		~CommandClass();

		// Execute (sets the result and return_code)
		void execute(); // idk what he wants me to do here

		// Getters
		std::string get_command_text();
		std::string get_result() const;
		int get_return_code() const;

		// Setters 
		void set_command_text(std::string new_command);
};

#endif
