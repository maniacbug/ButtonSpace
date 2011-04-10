#include <WProgram.h>
#include <ButtonSpace.h>
#include <Bounce.h>

const int bounce_time = 20; // msec

inline void* operator new(size_t, void* __p)
{
    return __p;
}

ButtonSpace::ButtonSpace(int _num_buttons, const uint8_t* _pins):
    num_buttons(_num_buttons), pins(_pins)
{
    buttons = (Bounce*)malloc( num_buttons * sizeof(Bounce) );

    const uint8_t* current_pin = pins;
    Bounce* current_button = buttons;
    int i = num_buttons;
    //printf("#Buttons: %i\n\r",i);
    while ( i-- )
    {
        //printf("Button %04p: Construct w pin %i\n\r",current_button,*current_pin);
        new (current_button++) Bounce(*current_pin++,bounce_time);
    }

    message_buffer = (uint8_t*)malloc(num_buttons);
}

void ButtonSpace::begin(void)
{
    const uint8_t* current = pins;
    const uint8_t* end = pins + num_buttons;
    while ( current < end )
    {
        pinMode(*current,OUTPUT);
        digitalWrite(*current,HIGH);
        //printf("Pin %i output\n\r",*current);
        ++current;
    }
}

void ButtonSpace::update(void)
{
    Bounce* current = buttons;
    Bounce* end = buttons + num_buttons;
    while ( current < end )
    {
        //printf("Button %04p: Update\n\r",current);
        (current++)->update();
    }
}

boolean ButtonSpace::update(int* num_events, const uint8_t** buffer)
{
    boolean result = false;
    *num_events = 0;
    *buffer = message_buffer;
    uint8_t* current_message = message_buffer;
    memset(message_buffer,0,num_buttons);

    update();

    int i = num_buttons;
    while (i--)
        if (buttons[i].fallingEdge())
        {
            printf("Message #%i = %i\n\r",*num_events,pins[i]);
            *current_message++ = pins[i];
            (*num_events)++;
            result = true;
        }

    return result;
}

Bounce* ButtonSpace::button(uint8_t which) const
{
    //printf("Seeking name %i\n\r",which);
    int i = num_buttons;
    while (i--)
        if (pins[i] == which)
        {
            //printf("Found #%i\n\r",i);
            return buttons + i;
        }
    //printf(" Found none\n\r");
    return NULL;
}

// vim:ai:cin:sts=4 sw=4 ft=cpp
