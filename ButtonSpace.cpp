#include <WProgram.h>
#include <ButtonSpace.h>
#include <Bounce.h>

const int bounce_time = 20; // msec

inline void* operator new(size_t, void* __p)
{
    return __p;
}

ButtonSpace::ButtonSpace(int _num_buttons, const uint8_t* _pins):
    num_buttons(_num_buttons), pins(_pins), num_keydowns_available(0)
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
    if (num_events)
	*num_events = 0;
    if (buffer)
	*buffer = message_buffer;
    uint8_t* current_message = message_buffer;
    memset(message_buffer,0,num_buttons);

    update();

    int i = num_buttons;
    while (i--)
        if (buttons[i].fallingEdge())
        {
            //printf("Message #%i = %i\n\r",*num_events,pins[i]);
            *current_message++ = pins[i];
            if (num_events)
		(*num_events)++;
            result = true;
        }

    return result;
}

boolean ButtonSpace::available(void)
{
    boolean result = false;

    if ( num_keydowns_available )
	result = true;

    // Warning, do not call update() to get more keydowns until
    // all of the current ones have been returned to the user
    else if ( update(&num_keydowns_available,NULL) )
    {
	result = true;
	current_read = message_buffer;
    }

    return result;
}

uint8_t ButtonSpace::read(void)
{
    uint8_t result = 0;

    if ( num_keydowns_available )
    {
	--num_keydowns_available;
	result = *current_read++;
    }

    return result;
}

void ButtonSpace::flush(void)
{
    num_keydowns_available = 0;
}

void ButtonSpace::press_any_key(void)
{
    while ( ! available() );
    flush();
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
