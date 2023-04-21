import sensor, image, time, math, pyb
from pyb import  Pin

blackthreshold = (0, 11, -17, 10, -26, 14)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
#sensor.set_vflip(True)
sensor.skip_frames(time = 500)

clock = time.clock()

while(True):
    clock.tick()
    img = sensor.snapshot()
    img.lens_corr(2.0)

    letter_blob = -1

    blobsL = img.find_blobs([blackthreshold], area_threshold=200)#200

    if blobsL:
        letter_blob = max(blobsL, key=lambda bL: bL.area())

    if letter_blob != -1:
        try:
            letter = letter_blob.rect()
            img.draw_rectangle(letter)
            print("density = ", letter_blob.density())
            if(letter_blob.density() > 0.7):
                print("None is Found")
                continue
            sx = letter[0]
            sy = letter[1]
            ex = letter[0] + letter[2]
            ey = letter[1] + letter[3]
            w = letter[2]
            h = letter[3]
            rw = int(0.05 * w)
            rh = int(0.05 * h)

            mid_roi = (int(sx + w / 2 - rw), int(sy + h / 2 - rh), 2 * rw, 2 * rh)
            img.draw_rectangle(mid_roi)

            is_mid = 0

            blobsR = 0
            for x in [mid_roi]:
                blobsR = img.find_blobs([blackthreshold],roi= x)
                if blobsR:
                    largest_blobR = max(blobsR, key=lambda bL: bL.area())
                    if(largest_blobR.area() >= int(rw * rh / 1.5)):
                        is_mid = 1

            if (is_mid == 0):
                print("U Found")
                continue


            top_roi = (int(sx + w / 2 - rw), int(sy), 2 * rw, 2 * rh)
            bottom_roi = (int(sx + w / 2 - rw), int(sy + h - rh), 2 * rw, 2 * rh)
            img.draw_rectangle(top_roi)
            img.draw_rectangle(bottom_roi)

            is_top = 0
            is_bottom = 0

            blobsR = 0
            for x in [top_roi]:
                blobsR = img.find_blobs([blackthreshold],roi= x)
                if blobsR:
                    largest_blobR = max(blobsR, key=lambda bL: bL.area())
                    if(largest_blobR.area() >= int(rw * rh / 1.5)):
                        is_top = 1

            blobsR = 0
            for x in [bottom_roi]:
                blobsR = img.find_blobs([blackthreshold],roi= x)
                if blobsR:
                    largest_blobR = max(blobsR, key=lambda bL: bL.area())
                    if(largest_blobR.area() >= int(rw * rh / 1.5)):
                        is_bottom = 1


            if ((is_top == 0) and (is_bottom == 0)):
                print("H Found")
                continue

            mid_top_roi = (int(sx + w / 2 - rw), int(sy), 2 * rw, 2 * rh)
            mid_bottom_roi = (int(sx + w / 2 - rw), int(sy + h - rh), 2 * rw, 2 * rh)
            img.draw_rectangle(mid_top_roi)
            img.draw_rectangle(mid_bottom_roi)

            is_mid_top = 0
            is_mid_bottom = 0

            blobsR = 0
            for x in [mid_top_roi]:
                blobsR = img.find_blobs([blackthreshold],roi= x)
                if blobsR:
                    largest_blobR = max(blobsR, key=lambda bL: bL.area())
                    if(largest_blobR.area() >= int(rw * rh / 1.5)):
                        is_mid_top = 1

            blobsR = 0
            for x in [mid_bottom_roi]:
                blobsR = img.find_blobs([blackthreshold],roi= x)
                if blobsR:
                    largest_blobR = max(blobsR, key=lambda bL: bL.area())
                    if(largest_blobR.area() >= int(rw * rh / 1.5)):
                        is_mid_bottom = 1

            if ((is_mid_top == 0) and (is_mid_bottom == 0)):
                print("S Found")
            else :
                print("None is Found")
            continue
        except:
            print("Error")

    print("None is Found")
