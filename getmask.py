import numpy as np
import cv2
import time
import hashlib

img=cv2.imread('c:/opencv/wps/20210208_2.jpg')
img_gary=cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
cv2.namedWindow('select', 0) 
cv2.resizeWindow('select', 700, 900) 
while True:

    r=cv2.selectROI('select', img,False)
    # 没有任何选择的情况下退出
    if r[2]==0 :break
    imgselect=img[int(r[1]):int(r[1]+r[3]), int(r[0]):int(r[0]+r[2])]
    imgselect=cv2.cvtColor(imgselect, cv2.COLOR_BGR2GRAY)
    m=hashlib.md5()
    m.update(bytes(str(time.time()),encoding='utf-8'))
    cv2.imwrite('c:/opencv/filter/'+str(m.hexdigest())+'.jpg',imgselect)
    h,w=imgselect.shape[:2]
    res=cv2.matchTemplate(img_gary, imgselect , cv2.TM_CCOEFF_NORMED)
    per=0.8
    loc=np.where(res>=per  )
    i=0
    for pt in zip(*loc[::-1 ]):
        bottom_right=(pt[0]+w,pt[1]+h)
        cv2.rectangle(img, pt, bottom_right, (255,255,0),-1)

cv2.waitKey(0)
cv2.destroyAllWindows()
