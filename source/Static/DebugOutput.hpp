#pragma once

#include <SDL_messagebox.h>
#include <string>

#define popup_message(message) (std::string("File: ") + __FILE__ + "\nLine: " + std::to_string(__LINE__) + "\nMessage: '" + message + "'\n").c_str()
#define popup_out(message) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Internal Error!", popup_message(message), 0)

#ifdef _DEBUG
	#define message_out(message, ...) printf(message, __VA_ARGS__)
	#define	warning_out(message) printf("File: %s\nLine: %d\nMessage: '%s'\n", __FILE__, __LINE__, message)
	#define error_out(message) warning_out(message); popup_out(message)
#else
	#define message_out(message, ...) (0)
	#define	warning_out(message) (0)
	#define error_out(message) popup_out(message)
#endif