//class Bounce;
#include <Bounce.h>
#include <WProgram.h>

class ButtonSpace
{
private:
    Bounce* buttons;
    int num_buttons;
    const uint8_t* pins;
    uint8_t* message_buffer;
    uint8_t* current_read;
    int num_keydowns_available;

public:
    /**
     * Constructor
     *
     * Allocates internal space for all buffers
     *
     * @param _num_buttons The number of the buttons to be managed
     * @param _pins The pins corresponding to the buttons to be
     * managed.
     */
    ButtonSpace(int _num_buttons, const uint8_t* _pins);

    /**
     * Prepares buttons for use
     *
     * Sets them all to inputs, engages pull-up resistors
     */
    void begin(void);

    /**
     * Whether there are button presses available in the queue
     *
     * This is part of the new high-level interface to the button
     * board.  Calling this function will update the buttons and
     * queue up the keydowns into a buffer, and return whether
     * there are any keydowns left to process.
     *
     * @todo Create an example for the high-level interface
     *
     * @return whether there are keydowns to be read
     */
    boolean available(void);

    /**
     * Read a single button press from the keydown queue
     *
     * @return the pin# of a button that was pressed
     * recently
     */
    uint8_t read(void);

    /**
     * Clear the pending keydowns
     */
    void flush(void);

    /**
     * Updates the state of buttons
     *
     * As with Bounce.update(), call this regularly in the main loop
     * to ensure the btutons know their latest state.
     */
    void update(void);

    /**
     * Updates the buttons and reports which have just been
     * pressed this cycle
     *
     * @param[out] num_keys Pointer to space for the number of keys that
     * were pressed this cycle.  Ok to pass NULL if you don't care.
     * @param[out] buffer Pointer to space for the buffer.  This returns
     * a pointer to the internal message buffer.  It is valid until the
     * next call to this method.  Ok to pass NULL if you don't care.
     * @return True if there are events to be processed
     */
    boolean update(int* num_keys, const uint8_t** buffer);

    /**
     * Obtain the state of a button
     *
     * @param which Which button to return
     * @returns Reference to the chosen button, or NULL if not found
     */
    Bounce* button(uint8_t which) const;
};
// vim:ai:cin:sts=4 sw=4 ft=cpp
