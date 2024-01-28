#include <gui/screen1_screen/Screen1View.hpp>
#include <cstring>
#include <texts/TextKeysAndLanguages.hpp>
#include <touchgfx/Utils.hpp>

Screen1View::Screen1View()
{
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::canTest_Data(char* data) //will place the unmarshalled can data into text buffer for display on gui - highest level
{
    Unicode::strncpy(textArea1Buffer, data, strlen(data));

	//touchgfx_printf("Displaying.. \n");
	//touchgfx_printf("%s \n", guiTest);

	//Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%u", 9);
    textArea1.invalidate();
}

