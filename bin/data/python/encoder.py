import gaugette.rotary_encoder
import gaugette.switch

A_PIN = 7
B_PIN = 9
SW_PIN = 8

counter = 0
# no worker thread
# encoder = gaugette.rotary_encoder.RotaryEncoder(A_PIN, B_PIN)

# worker thread used
encoder = gaugette.rotary_encoder.RotaryEncoder.Worker(A_PIN, B_PIN)
encoder.start()

switch = gaugette.switch.Switch(SW_PIN)
last_state = None

while True:
    # get rotation direction from encoder
    delta = encoder.get_delta()
    if delta!=0:
        print "rotate %d" % delta
        counter += 1
        if counter > 100:
            counter = 0

        text_file = open("rot.txt", "w")
        text_file.write("%s\n" % delta)
        text_file.write("%s" % counter)
        text_file.close()

    # get button state from encoder
    sw_state = switch.get_state()
    if sw_state != last_state:
        print "switch %d" % sw_state
        last_state = sw_state
        text_file = open("switch.txt", "w")
        text_file.write("%s" % sw_state)
        text_file.close()