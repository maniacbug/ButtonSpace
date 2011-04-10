#include <Bounce.h>
#include <ButtonSpace.h>

// Define keys
//
// These are the pins that the buttons are on.  Buttons are
// connected to GROUND when closed, NOT CONNECTED when open

const uint8_t button_one = 2;
const uint8_t button_two = 3;

// Instantiate the button space

const uint8_t keys[] = { button_one, button_two };
ButtonSpace buttons( 2, keys );

void setup(void)
{
    Serial.begin(57600);
    Serial.println("\n\rButtonState/examples/twobuttons/");

    buttons.begin();
}

void loop(void)
{
    bool keydowns_occurred = false;

    // Update the buttons and print a message for each
    int keydown_index;
    const uint8_t* keydowns;
    if ( buttons.update(&keydown_index,&keydowns) )
    {
        keydowns_occurred = true;
        while (keydown_index--)
        {
            switch(keydowns[keydown_index])
            {
            case button_one:
                Serial.println("Pressed: Button 1");
                break;
            case button_two:
                Serial.println("Pressed: Button 2");
                break;
            }
        }
    }

    // If there were any keydowns, print the entire state of the buttons
    if (keydowns_occurred)
    {
        Serial.print("Buttons now down: ");
        if ( !buttons.button(button_one)->read() )
            Serial.print("1");
        if ( !buttons.button(button_two)->read() )
            Serial.print("2");
        Serial.println();
    }
}

// vim:ai:cin:sts=4 sw=4 ft=cpp
