import sensor, image, time, math, pyb
from pyb import  Pin


pin0 = Pin('P8', Pin.OUT_PP, Pin.PULL_NONE)
pin1 = Pin('P9', Pin.OUT_PP, Pin.PULL_NONE)
pin2 = Pin('P5', Pin.OUT_PP, Pin.PULL_NONE)

led1 = pyb.LED(1)
led2 = pyb.LED(2)
led3 = pyb.LED(3)
led2.on()

blackthreshold = (0, 68)
#(0, 45, -128, 127, -128, 127)

redthresholds = (13, 57, 40, 75, 2, 60)
greenthresholds = (25, 54, -56, -21, 14, 51)
yellowthresholds = (67, 81, -28, -5, 24, 74)


sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.set_vflip(True)
sensor.skip_frames(time = 500)

clock = time.clock()

offset = 6
offset_area = 12
times_to_send = 10
letter_counter = 0
letter_to_send = 'N'

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


    letter_blob = -1

    red_blob = -1
    green_blob = -1
    yellow_blob = -1


'''
    for red_blob in img.find_blobs([redthresholds], pixels_threshold=150, area_threshold=100, merge=True):
        # These values depend on the blob not being circular - otherwise they will be shaky.
        if(red_blob.area() > 1750):
            print("RED Victim Found")
            print("Red area = ", red_blob.area())
            img.draw_rectangle(red_blob.rect(), color=(255,255,255))
            pin0.value(1)
            pin1.value(0)
            pin2.value(0)
            time.sleep(1.5)
            pin0.value(0)
            pin1.value(0)
            pin2.value(0)
            time.sleep(7)
            letter_counter = 0
            letter_to_send = 'N'
            break
        #print("RED : ")
        #print("Red area = ", red_blob.area())
        #print("cy = ", red_blob.cy())
        #print("cx = ", red_blob.cx())
        #img.draw_rectangle(red_blob.rect(), color=(255,255,255))
        #img.draw_cross(red_blob.cx(), red_blob.cy(), color=(255,255,255))
        #img.draw_keypoints([(red_blob.cx(), red_blob.cy(), int(math.degrees(red_blob.rotation())))], size=10, color=(255,255,255))


    for green_blob in img.find_blobs([greenthresholds], pixels_threshold=150, area_threshold=100, merge=True):
        # These values depend on the blob not being circular - otherwise they will be shaky.
        if(green_blob.area() > 1750):
            print("GREEN Victim Found")
            img.draw_rectangle(green_blob.rect(), color=(255,255,255))
            pin0.value(0)
            pin1.value(1)
            pin2.value(0)
            time.sleep(1.5)
            pin0.value(0)
            pin1.value(0)
            pin2.value(0)
            time.sleep(7)
            letter_counter = 0
            letter_to_send = 'N'
            break
        #print("GREEN : ")
        #print("area = ", green_blob.area())
        #print("cy = ", green_blob.cy())
        #print("cx = ", green_blob.cx())
        #img.draw_rectangle(green_blob.rect(), color=(255,255,255))
        #img.draw_cross(green_blob.cx(), green_blob.cy(), color=(255,255,255))
        #img.draw_keypoints([(green_blob.cx(), green_blob.cy(), int(math.degrees(green_blob.rotation())))], size=10, color=(255,255,255))


    for yellow_blob in img.find_blobs([yellowthresholds], pixels_threshold=150, area_threshold=100, merge=True):
        # These values depend on the blob not being circular - otherwise they will be shaky.
        if(yellow_blob.area() > 1750):
            print("YELLOW Victim Found")
            img.draw_rectangle(yellow_blob.rect(), color=(255,255,255))
            pin0.value(0)
            pin1.value(1)
            pin2.value(1)
            time.sleep(1.5)
            pin0.value(0)
            pin1.value(0)
            pin2.value(0)
            time.sleep(7)
            letter_counter = 0
            letter_to_send = 'N'
            break
        #print("YELLOW : ")
        #print("area = ", yellow_blob.area())
        #print("cy = ", yellow_blob.cy())
        #print("cx = ", yellow_blob.cx())
        #img.draw_rectangle(yellow_blob.rect(), color=(255,255,255))
        #img.draw_cross(yellow_blob.cx(), yellow_blob.cy(), color=(255,255,255))
        #img.draw_keypoints([(yellow_blob.cx(), yellow_blob.cy(), int(math.degrees(yellow_blob.rotation())))], size=10, color=(255,255,255))
'''

    img.to_grayscale()
    blobsL = img.find_blobs([blackthreshold], area_threshold=1000)#200

    if blobsL:
        letter_blob = max(blobsL, key=lambda bL: bL.area())
        #print(letter_blob)


    if (letter_blob != -1) :
        try:
            #print("cy = ", letter_blob.cy())
            print("area = ", letter_blob.area())
            if (letter_blob.cy() < 60):
                letter_counter = 0
                letter_to_send = 'N'
                continue

            letter = letter_blob.rect()
            img.draw_rectangle(letter)

            sx = letter[0]
            sy = letter[1]
            ex = letter[0] + letter[2]
            ey = letter[1] + letter[3]

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
            if (is_upper_left and is_lower_left and is_upper_right and is_lower_right):
                if (letter_to_send == 'H'):
                    letter_counter += 1
                else :
                    letter_counter = 1
                    letter_to_send = 'H'
                #uart.write("H")
                if (letter_counter >= times_to_send and letter_to_send == 'H'):
                    led3.on()
                    print("H Found")
                    pin0.value(0)
                    pin1.value(0)
                    pin2.value(1)
                    time.sleep(1.5)
                    pin0.value(0)
                    pin1.value(0)
                    pin2.value(0)
                    time.sleep(7)
                    letter_counter = 0
                    letter_to_send = 'N'
                continue
            elif (is_upper_left and is_lower_left == 0 and is_upper_right and is_lower_right == 0):
                #uart.write("U")
                if (letter_to_send == 'U'):
                    letter_counter += 1
                else :
                    letter_counter = 1
                    letter_to_send = 'U'
                if (letter_counter >= times_to_send and letter_to_send == 'U'):
                    led1.on()
                    print("U Found")
                    pin0.value(1)
                    pin1.value(0)
                    pin2.value(1)
                    time.sleep(1.5)#3
                    pin0.value(0)
                    pin1.value(0)
                    pin2.value(0)
                    time.sleep(7)
                    letter_counter = 0
                    letter_to_send = 'N'
                continue
            elif (is_upper_left == 0 and is_lower_left == 0 and is_upper_right == 0 and is_lower_right == 0):
                #uart.write("S")
                if (letter_to_send == 'S'):
                    letter_counter += 1
                else :
                    letter_counter = 1
                    letter_to_send = 'S'
                if (letter_counter >= times_to_send and letter_to_send == 'S'):
                    led1.on()
                    led3.on()
                    print("S Found")
                    pin0.value(1)
                    pin1.value(1)
                    pin2.value(0)
                    time.sleep(1.5)
                    pin0.value(0)
                    pin1.value(0)
                    pin2.value(0)
                    time.sleep(7)
                    letter_counter = 0
                    letter_to_send = 'N'
                continue
        except:
            print("Error")
    print("None is found")
    letter_counter = 0
    letter_to_send = 'N'
    pin0.value(0)
    pin1.value(0)
    pin2.value(0)
    #uart.write("N")
    #pin0.value(0)
    #pin1.value(0)
    #pin2.value(0)



