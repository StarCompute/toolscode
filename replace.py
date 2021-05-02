import numpy as np
import cv2
import os

# 欲处理的文件夹
sourpath='c:/opencv/wps/'
# 欲过滤的图片文件夹
filterpath='c:/opencv/filter/'
# 处理过后保存的文件夹
targetpath='c:/opencv/wps2/'


spath=os.listdir(sourpath)
for f in spath:
    filename=sourpath+f
    img=cv2.imread(filename)
    img_gary=cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    print(filename)
    filterfiles=os.listdir(filterpath)
    per=0.7

    for childfilter in filterfiles:
        filterfilename=filterpath+childfilter
        imgfilter=cv2.imread(filterfilename,0)
        h,w=imgfilter.shape[:2]
        res=cv2.matchTemplate(img_gary, imgfilter , cv2.TM_CCOEFF_NORMED)
        loc=np.where(res>=per  )

        for pt in zip(*loc[::-1 ]):
            bottom_right=(pt[0]+w,pt[1]+h)
            cv2.rectangle(img, pt, bottom_right, (0,0,0),-1)


    cv2.imwrite(targetpath+f, img)
