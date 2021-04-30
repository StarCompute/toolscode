#下面的代码实现打开一张图片，然后手工选择对应的区域，对图片中选择的相同内容区域全部打码
#也可以用其他图片，不用选择区域的方案
#这个功能在处理大规模关键内容替换的时候非常好用！

import numpy as np
import cv2

img=cv2.imread('c:/opencv/chatlist.png')
img_gary=cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

while True:
    r=cv2.selectROI('select', img,False)
    # 没有任何选择的情况下退出
    if r[2]==0 :break
    imgselect=img[int(r[1]):int(r[1]+r[3]), int(r[0]):int(r[0]+r[2])]
    imgselect=cv2.cvtColor(imgselect, cv2.COLOR_BGR2GRAY)
    h,w=imgselect.shape[:2]
    res=cv2.matchTemplate(img_gary, imgselect , cv2.TM_CCOEFF_NORMED)
    per=0.8
    loc=np.where(res>=per  )
    i=0
    for pt in zip(*loc[::-1 ]):
        bottom_right=(pt[0]+w,pt[1]+h)
        cv2.rectangle(img, pt, bottom_right, (255,255,0),-1)

cv2.imwrite('c:/opencv/chatlist_new.jpg', img)
cv2.waitKey(0)
cv2.destroyAllWindows()
