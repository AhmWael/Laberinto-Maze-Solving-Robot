import sensor, image, time, math, pyb
from pyb import  Pin


pin0 = Pin('P8', Pin.OUT_PP, Pin.PULL_NONE)
pin1 = Pin('P9', Pin.OUT_PP, Pin.PULL_NONE)
pin2 = Pin('P5', Pin.OUT_PP, Pin.PULL_NONE)

led1 = pyb.LED(1)
led2 = pyb.LED(2)
led3 = pyb.LED(3)
led2.on()

##Competition
blackthreshold = (0, 71)

#blackthreshold = (0, 84)
#blackthreshold = (0, 87)
#(0, 45, -128, 127, -128, 127)

#Competition
redthresholds = (11, 51, 23, 82, 20, 70)
greenthresholds = (17, 49, -61, -17, -10, 77)
yellowthresholds = (42, 64, -36, -1, 24, 76)


##School_Day
#redthresholds = (14, 31, 24, 50, -13, 39)
#greenthresholds = (21, 50, -38, -14, -13, 37)
#yellowthresholds = (42, 65, -20, -2, 21, 64)

##School_Night
#blackthreshold = (0, 41)
#redthresholds = (21, 68, 28, 82, -12, 66)
#greenthresholds = (11, 31, -34, -14, -1, 29)
#yellowthresholds = (34, 82, -23, -1, 26, 79)


sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_vflip(True)
sensor.skip_frames(time = 500)

clock = time.clock()

offset = 6
offset_area = 12
times_to_send = 7
letter_counter = 0
letter_to_send = 'N'
color_bool = 0
none_counter = 20

pin0.value(0)
pin1.value(0)
pin2.value(0)

while(True):
    clock.tick()
    img = sensor.snapshot()
    img.lens_corr(2.0)
    led1.off()
    led2.off()
    led3.off()

    color_bool = 0

    letter_blob = -1

    red_blob = -1
    green_blob = -1
    yellow_blob = -1

    #print("letter to send = ", letter_to_send)

    if (none_counter < 20):
        print("just sent a vivtim")
        pin0.value(0)
        pin1.value(0)
        pin2.value(0)

    for red_blob in img.find_blobs([redthresholds], pixels_threshold=150, area_threshold=100, merge=True):
        # These values depend on the blob not being circular - otherwise they will be shaky.
        #print("red area = ", red_blob.area())
        #print("letter to send = ", letter_to_send)
        if(red_blob.area() > 4000):
            color_bool = 1
            if (letter_to_send == 'R'):
                letter_counter += 1
            else :
                #print("here 1")
                letter_counter = 1
                letter_to_send = 'R'
            if (letter_counter >= times_to_send and letter_to_send == 'R' and none_counter >= 20):
                #led1.on()
                print("R Found")
                pin0.value(1)
                pin1.value(0)
                pin2.value(0)
                letter_counter = 0
                none_counter = 0
                break
        #continue
        #print("RED : ")
        #print("Red area = ", red_blob.area())
        #print("cy = ", red_blob.cy())
        #print("cx = ", red_blob.cx())
        #img.draw_rectangle(red_blob.rect(), color=(255,255,255))
        #img.draw_cross(red_blob.cx(), red_blob.cy(), color=(255,255,255))
        #img.draw_keypoints([(red_blob.cx(), red_blob.cy(), int(math.degrees(red_blob.rotation())))], size=10, color=(255,255,255))


    for green_blob in img.find_blobs([greenthresholds], pixels_threshold=150, area_threshold=100, merge=True):
        # These values depend on the blob not being circular - otherwise they will be shaky.
        if(green_blob.area() > 4000):
            color_bool = 1
            if (letter_to_send == 'G'):
                letter_counter += 1
            else :
                letter_counter = 1
                letter_to_send = 'G'
            if (letter_counter >= times_to_send and letter_to_send == 'G' and none_counter >= 20):
                #led1.on()
                print("G Found")
                pin0.value(0)
                pin1.value(1)
                pin2.value(0)
                none_counter = 0
                letter_counter = 0
                break
        #continue
        #print("GREEN : ")
        #print("Green area = ", green_blob.area())
        #print("cy = ", green_blob.cy())
        #print("cx = ", green_blob.cx())
        #img.draw_rectangle(green_blob.rect(), color=(255,255,255))
        #img.draw_cross(green_blob.cx(), green_blob.cy(), color=(255,255,255))
        #img.draw_keypoints([(green_blob.cx(), green_blob.cy(), int(math.degrees(green_blob.rotation())))], size=10, color=(255,255,255))


    for yellow_blob in img.find_blobs([yellowthresholds], pixels_threshold=150, area_threshold=100, merge=True):
        # These values depend on the blob not being circular - otherwise they will be shaky.
        if(yellow_blob.area() > 4000):
            color_bool = 1
            if (letter_to_send == 'Y'):
                letter_counter += 1
            else :
                letter_counter = 1
                letter_to_send = 'Y'
            if (letter_counter >= times_to_send and letter_to_send == 'Y' and none_counter >= 20):
                #led1.on()
                print("Y Found")
                pin0.value(0)
                pin1.value(1)
                pin2.value(1)
                none_counter = 0
                letter_counter = 0
                break
        #continue
        #print("YELLOW : ")
        #print("Yellow area = ", yellow_blob.area())
        #print("cy = ", yellow_blob.cy())
        #print("cx = ", yellow_blob.cx())
        #img.draw_rectangle(yellow_blob.rect(), color=(255,255,255))
        #img.draw_cross(yellow_blob.cx(), yellow_blob.cy(), color=(255,255,255))
        #img.draw_keypoints([(yellow_blob.cx(), yellow_blob.cy(), int(math.degrees(yellow_blob.rotation())))], size=10, color=(255,255,255))

    if (color_bool == 1):
        continue
    img.to_grayscale()
    blobsL = img.find_blobs([blackthreshold], area_threshold=1000)#200

    if blobsL:
        letter_blob = max(blobsL, key=lambda bL: bL.area())
        #print(letter_blob)


    if (letter_blob != -1) :
        try:
            #print("cx = ", letter_blob.cx())
            #print("cy = ", letter_blob.cy())
            #print("Letter area = ", letter_blob.area())
            #print("Letter density = ", letter_blob.density())
            print("Width : ", letter_blob[2])
            print("Height : ", letter_blob[3])
            #4000
            if (letter_blob.cy() < 70 or letter_blob.area() > 5000 or letter_blob.area() < 1500
                or letter_blob.cy() > 180 or letter_blob.density() > 0.75
                or letter_blob.cx() < 70 or letter_blob.cx() > 250):
                print("NEGLECTED**")
                letter_counter = 0
                letter_to_send = 'N'
                none_counter = none_counter + 1
                pin0.value(0)
                pin1.value(0)
                pin2.value(0)
                continue
            if (letter_blob[3] > 175 or letter_blob[2] < 40):
                print("NEGLECTED**")
                letter_counter = 0
                letter_to_send = 'N'
                none_counter = none_counter + 1
                pin0.value(0)
                pin1.value(0)
                pin2.value(0)
                continue

            letter = letter_blob.rect()
            img.draw_rectangle(letter)

            sx = letter[0]
            sy = letter[1]
            ex = letter[0] + letter[2]
            ey = letter[1] + letter[3]
            w = letter[2]
            h = letter[3]
            midx = int(sx + (0.5 * w))
            midy = int(sy + (0.5 * h))
            img.draw_rectangle(midx - offset, midy - offset, offset * 2, offset * 2)
            is_middle = 0
            counter = 0
            for x in range(midx-offset, midx+offset):
                for y in range(midy-offset, midy+offset):
                    binary = (img.get_pixel(x,y) >= blackthreshold[0] and img.get_pixel(x,y) <= blackthreshold[1])
                    counter += binary
            #print("upperLeft_counter", counter)
            if(counter >= offset_area):
                is_middle = 1
                #print("middle counter = ", counter)
            if(is_middle == 0):
                print(letter_to_send)
                if (letter_to_send == 'U'):
                    letter_counter += 1
                else :
                    letter_counter = 1
                    letter_to_send = 'U'
                if (letter_counter >= times_to_send - 4 and letter_to_send == 'U' and none_counter >= 20):
                    #led1.on()
                    print("U Found")
                    pin0.value(1)
                    pin1.value(0)
                    pin2.value(1)
                    none_counter = 0
                    letter_counter = 0
                continue
            upper_left_corner = [sx, sy]
            lower_left_corner = [sx, ey - offset]
            upper_right_corner = [ex - offset, sy]
            lower_right_corner = [ex - offset, ey - offset]
            '''upper_left_corner = [(sx, sy, offset, offset, 0.1)]
            lower_left_corner = [(sx, ey - offset, offset, offset, 0.2)]
            upper_right_corner = [(ex - offset, sy, offset, offset, 0.3)]
            lower_right_corner = [(ex - offset, ey - offset, offset, offset, 0.4)]'''

            is_upper_left = 0
            is_lower_left = 0
            is_upper_right = 0
            is_lower_right = 0

            counter = 0
            for x in range(upper_left_corner[0], upper_left_corner[0] + offset):
                for y in range(upper_left_corner[1], upper_left_corner[1] + offset):
                    binary = (img.get_pixel(x,y) >= blackthreshold[0] and img.get_pixel(x,y) <= blackthreshold[1])
                    counter += binary
            #print("upperLeft_counter", counter)
            if(counter >= offset_area):
                is_upper_left = 1
            #print("upperLeft", counter)
            counter = 0
            for x in range(upper_right_corner[0], upper_right_corner[0] + offset):
                for y in range(upper_right_corner[1], upper_right_corner[1] + offset):
                    binary = (img.get_pixel(x,y) >= blackthreshold[0] and img.get_pixel(x,y) <= blackthreshold[1])
                    counter += binary
            #print("upperRight_counter", counter)
            if(counter >= offset_area):
                is_upper_right = 1
            #print("upperRight", counter)
            counter = 0
            for x in range(lower_left_corner[0], lower_left_corner[0] + offset):
                for y in range(lower_left_corner[1], lower_left_corner[1] + offset):
                    binary = (img.get_pixel(x,y) >= blackthreshold[0] and img.get_pixel(x,y) <= blackthreshold[1])
                    counter += binary
            if(counter >= offset_area):
                is_lower_left = 1
            #print("LowerLeft", counter)
            counter = 0
            for x in range(lower_right_corner[0], lower_right_corner[0] + offset):
                for y in range(lower_right_corner[1], lower_right_corner[1] + offset):
                    binary = (img.get_pixel(x,y) >= blackthreshold[0] and img.get_pixel(x,y) <= blackthreshold[1])
                    counter += binary
            if(counter >= offset_area):
                is_lower_right = 1
            #print("LowerRight", counter)
            '''for x in upper_left_corner:
                blobs = img.find_blobs([blackthreshold],roi=x[0:4])
                if blobs:
                    largest_blob = max(blobs, key=lambda bL: bL.area())
                    #print("Upper_Left: ", largest_blob.area())
                    if (largest_blob.area() > offset_area) :
                        is_upper_left = 1

            for x in lower_left_corner:
                blobs = img.find_blobs([blackthreshold], roi=x[0:4])
                if blobs:
                    largest_blob = max(blobs, key=lambda bL: bL.area())
                    #print("Lower_Left: ", largest_blob.area())
                    if (largest_blob.area() > offset_area) :
                        is_lower_left = 1

            for x in upper_right_corner:
                blobs = img.find_blobs([blackthreshold], roi=x[0:4])
                if blobs:
                    largest_blob = max(blobs, key=lambda bL: bL.area())
                    #print("Upper_Right: ", largest_blob.area())
                    if (largest_blob.area() > offset_area) :
                        is_upper_right = 1

            for x in lower_right_corner:
                blobs = img.find_blobs([blackthreshold], roi=x[0:4])
                if blobs:
                    largest_blob = max(blobs, key=lambda bL: bL.area())
                    #print("Lower_Right: ", largest_blob.area())
                    if (largest_blob.area() > offset_area) :
                        is_lower_right = 1'''
            if (is_upper_left or is_lower_left or is_upper_right or is_lower_right):
                if (letter_to_send == 'H' or letter_to_send == 'S'):
                    letter_counter += 1
                else :
                    letter_counter = 1
                    letter_to_send = 'H'
                #uart.write("H")
                if (letter_counter >= times_to_send - 4 and letter_to_send == 'H' and none_counter >= 20):
                    #led3.on()
                    print("H Found")
                    pin0.value(0)
                    pin1.value(0)
                    pin2.value(1)
                    none_counter = 0
                    letter_counter = 0
                continue
            else:
                #uart.write("S")
                if (letter_to_send == 'S' or letter_to_send == 'H'):
                    letter_counter += 1
                else :
                    letter_counter = 1
                    letter_to_send = 'S'
                if (letter_counter >= times_to_send - 4 and (letter_to_send == 'S' or letter_to_send == 'H')
                    and none_counter >= 20):
                    #led1.on()
                    #led3.on()
                    print("S Found")
                    pin0.value(1)
                    pin1.value(1)
                    pin2.value(0)
                    none_counter = 0
                    letter_counter = 0
                continue
        except:
            print("Error")
    print("None is found")
    none_counter = none_counter + 1
    letter_counter = 0
    letter_to_send = 'N'
    pin0.value(0)
    pin1.value(0)
    pin2.value(0)
    #uart.write("N")
    #pin0.value(0)
    #pin1.value(0)
    #pin2.value(0)



