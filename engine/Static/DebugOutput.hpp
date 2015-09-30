#pragma once

#include <SDL_messagebox.h>
#include <string>

#ifndef popup_contents
	#define popup_contents(message) (std::string("File: ") + __FILE__ + "\n\nLine: " + std::to_string(__LINE__) + "\n\nMessage: " + message).c_str()
#endif

#ifndef warning_contents
	#define warning_contents(message, type) printf("-- %s! ----------\nFile: %s\nLine: %d\nMessage: %s\n", type, __FILE__, __LINE__, message)
#endif

#define popup_out(message) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Internal Error!", popup_contents(message), 0)

#ifdef _DEBUG
	#define message_out(message, ...) printf(message, __VA_ARGS__)
	#define	warning_out(message) warning_contents(message, "Warning")
	#define error_out(message) warning_contents(message, "Error"); popup_out(message)
#else
	#define message_out(message, ...) (0)
	#define	warning_out(message) (0)
	#define error_out(message) popup_out(message)
#endif