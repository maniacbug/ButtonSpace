#include <Bounce.h>
#include <ButtonSpace.h>

// Define keys
//
// These are the pins that the buttons are on.  Buttons are
// connected to GROUND when closed, NOT CONNECTED when open

const uint8_t key_up = 5;
const uint8_t key_down = 4;
const uint8_t key_left = 2;
const uint8_t key_right = 3;
const uint8_t key_A = 7;
const uint8_t key_B = 6;

// Instantiate the button space

const uint8_t keys[] = { key_up,key_down,key_left,key_right,key_A,key_B };
ButtonSpace buttons( sizeof(keys), keys );

void setup(void)
{
    Serial.begin(57600);
    Serial.println("\n\rButtonState/examples/sixbuttons/");

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
            case key_up:
                Serial.println("Pressed: UP");
                break;
            case key_down:
                Serial.println("Pressed: DOWN");
                break;
            case key_left:
                Serial.println("Pressed: LEFT");
                break;
            case key_right:
                Serial.println("Pressed: RIGHT");
                break;
            case key_A:
                Serial.println("Pressed: [A]");
                break;
            case key_B:
                Serial.println("Pressed: [B]");
                break;
            }
        }
    }

    // If there were any keydowns, print the entire state of the buttons
    if (keydowns_occurred)
    {
        Serial.print("Buttons now down: ");
        if ( !buttons.button(key_up)->read() )
            Serial.print("U");
        if ( !buttons.button(key_down)->read() )
            Serial.print("D");
        if ( !buttons.button(key_left)->read() )
            Serial.print("L");
        if ( !buttons.button(key_right)->read() )
            Serial.print("R");
        if ( !buttons.button(key_A)->read() )
            Serial.print("A");
        if ( !buttons.button(key_B)->read() )
            Serial.print("B");
        Serial.println();
    }
}

// vim:ai:cin:sts=4 sw=4 ft=cpp
