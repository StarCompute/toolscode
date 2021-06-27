import cv2
import os
import sys
import numpy as np
import math

def caclCar(lastcar,nowcar):
    return math.isqrt((lastcar['x']-nowcar['x'])**2+(lastcar['y']-nowcar['y'])**2)

def getMinDistanceInCars(cararr,cardict):
    mindis=0
    dis=[]
    for c in cararr:
        distance=caclCar(c,cardict)
        # distance=math.isqrt((c['x']-cardict['x'])**2+(c['y']-cardict['y'])**2)
        dis.append(distance)
    if len(dis)>0:mindis=np.min(dis)
    return mindis

video=cv2.VideoCapture('c:/opencv/cars.mp4')
# fourcc=cv2.VideoWriter_fourcc(*'mp4v')
# output=cv2.VideoWriter("c:/opencv/cars3.mp4",fourcc,25,(1280,720),False)

if not video.isOpened():
    print ('open mp4 get error')
    exit()


BS = cv2.createBackgroundSubtractorMOG2(detectShadows=False)

kernel_size = (3,3)
sigma = 1.3

cars=[]

trackno=1
lastObjetects=[]
while True:
    ok,frame=video.read()
    if not ok:
        break

    imggauss = cv2.GaussianBlur(frame, kernel_size, sigma)
    imgmed=cv2.medianBlur(imggauss,1)
    img_gray = cv2.cvtColor(imgmed, cv2.COLOR_BGR2GRAY)
    
    adapthresh=cv2.adaptiveThreshold(img_gray,255,cv2.ADAPTIVE_THRESH_GAUSSIAN_C,cv2.THRESH_BINARY,25,5)
    fgmask = BS.apply(adapthresh)
    
    element11 = cv2.getStructuringElement(cv2.MORPH_RECT,(2,2))
    element211 = cv2.getStructuringElement(cv2.MORPH_RECT, (13, 13))
    image211 = cv2.morphologyEx(fgmask, cv2.MORPH_OPEN,element11)
        # image2112 = cv2.morphologyEx(image211, cv2.MORPH_OPEN,element11)
    image311 = cv2.dilate(image211, element211)
        
    contours, hierarchy = cv2.findContours( image=image311, mode=cv2.RETR_EXTERNAL, method=cv2.CHAIN_APPROX_SIMPLE)
    cnt = len(contours)
    
    tmpLastObjects=[]
    for k in range(1,cnt):
        if len(contours[k])>30:
            x, y, w, h = cv2.boundingRect(contours[k])
            
            # 使用最小外接矩形来计算，防止有些物体的判断是倾斜的
            rect = cv2.minAreaRect(contours[k])
            # print(rect)
            
            rectchild=rect[1]
            cw=rectchild[0]
            ch=rectchild[1]
            #去掉不满足相应比例的数据，对于边缘检测的过滤 
            if cw>1.60*ch or ch>1.60*cw :continue
            # 去掉一定区间外的数据，防止错误的识别。
            if y>497 or y<140:continue
            if w*h<55*55:continue
            # print(x,y,w,h)
            
            # box = cv2.boxPoints(rect)
            # box = np.int0(box)
            # rect_squerr=cv2.contourArea(contours[k])

            Moments=cv2.moments(contours[k])
            # print(Moments)
            cardict={'x':x,'y':y,'w':w,'h':h}
            
            # print(cardict)
            # 如果矩形和现在的所有的矩形比较后距离都大于200或者等于0，则加入Cars数组,说明是新矩形
            cardis=getMinDistanceInCars(lastObjetects,cardict)
            print("d:",cardis)
            cardict['id']=0
            if cardis>100 or cardis==0:
                if y<413:continue
                cardict['id']=trackno
                cars.append(cardict)
                trackno+=1
            else:
                # print (lastObjetects)
                for lastc in lastObjetects:
                    _dis=caclCar(lastc,cardict)
                    print(_dis)
                    if _dis<=80:
                        cardict['id']=lastc['id']
                        # print()
                        break

            tmpLastObjects.append(cardict)
            cv2.rectangle((image311), (x, y), (x+w, y+h), (255, 255, 255), 1)
            cv2.rectangle((adapthresh), (x, y), (x+w, y+h), (255, 255, 0), 1)
            cv2.rectangle((frame), (x, y), (x+w, y+h), (255, 255, 0), 1)
             # cv2.putText(frame, "FPS : " + str(int(fps)), (100,50), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (50,170,50), 2);
            strputTxt='x:'+str(x)+' y:'+str(y)+' w:'+str(w)+' h:'+str(h)
            cv2.putText(frame,strputTxt,(x,y-4),cv2.FONT_HERSHEY_SIMPLEX, 0.40,(255,255,0),1)
            print(cardict)
            if cardict.__contains__('id')==True :
                tracktxt='track:'+str(cardict['id'])
                cv2.putText(frame,tracktxt,(x,y+10+h),cv2.FONT_HERSHEY_SIMPLEX, 0.40,(255,255,0),1)

    cv2.putText(frame, "total cars : " + str(int(len(cars))), (100,50), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (0,255,50), 2)
    lastObjetects=tmpLastObjects
    # output.write(img_gray)
    # timer = cv2.getTickCount()
    # fps = cv2.getTickFrequency() / (cv2.getTickCount() - timer)
    # cv2.imshow("Tracking", adapthresh)
    # cv2.imshow("Tracking", image311)
    # print('car amount:',len(cars))
    cv2.imshow('result',frame)
        # Exit if ESC pressed
    k = cv2.waitKey(0) 
    # print(k)
    if k == 113 : break

print('car amount:',len(cars))
cv2.destroyAllWindows()

