import gaugette.rotary_encoder

A_PIN = 7
B_PIN = 9
encoder = gaugette.rotary_encoder.RotaryEncoder(A_PIN, B_PIN)
while True:
    delta = encoder.get_delta()
    if delta!=0:
        print "rotate %d" % delta
        text_file = open("val.txt", "w")
        text_file.write("%s" % delta)
        text_file.close()