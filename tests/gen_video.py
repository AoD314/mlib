#!/usr/bin/python

import Image, ImageDraw
import os
from multiprocessing import Pool

def cvt_color(num):
	clr = []
	i = 0
	while(num > 1):
		clr += [num % 2]
		num /= 2
	clr += [num % 2]
	return clr

def gen_image(args):
	# num, w, h
	im = Image.new("RGB", (args[1], args[2]), (0, 0, 0))
	draw = ImageDraw.Draw(im)
	clr = cvt_color(i)
	for j in range(len(clr)):
		draw.point((j, 0), (clr[j] * 255 , clr[j] * 255, clr[j] * 255))
	name = "img_%06d.png" % args[0]
	print (name)
	im.save(name)

def gen_images(t, c, w, h):
	arr = range(1, c + 1)
	pool = Pool(processes=4) # start 2 worker processes
	args = [[i, w, h] for i in range(1, c + 1)]
	pool.map(gen_image, args)

def coding_video(name, f):
	# xvid 
	name_xvid = "xvid" + name + ".avi"
	cmd = "mencoder mf://*.png -mf fps=%d:type=png -ovc xvid -xvidencopts pass=1:max_bframes=2:chroma_opt:vhq=4:bvhq=1:quant_type=mpeg:threads=12:bitrate=100000000 -o /dev/null" %  f
	os.system(cmd)
	cmd = "mencoder mf://*.png -mf fps=%d:type=png -ovc xvid -xvidencopts pass=2:max_bframes=2:chroma_opt:vhq=4:bvhq=1:quant_type=mpeg:threads=12:bitrate=100000000 -o %s" % f, name_xvid
	os.system(cmd)
	
	# vpx 
	name_vpx = "vpx" + name + ".webm"
	cmd = "mencoder mf://*.png -mf fps=%d:type=png -ovc lavc -lavcopts vcodec=libvpx:vpass=1:threads=8:vbitrate=100000000 -o /dev/null" % f 
	os.system(cmd)
	cmd = "mencoder mf://*.png -mf fps=%d:type=png -ovc lavc -lavcopts vcodec=libvpx:vpass=2:threads=8:vbitrate=100000000 -o %s" % f, name_vpx
	os.system(cmd)
	
	# h264 
	name_h264 = "h264" + name + ".avi"
	cmd = "mencoder mf://*.png -mf fps=%d:type=png -ovc x264 -x264encopts pass=1:subq=7:frameref=2:me=esa:threads=12:partitions=all:bframes=0:bitrate=100000000 -o /dev/null" % f
	os.system(cmd)
	cmd = "mencoder mf://*.png -mf fps=%d:type=png -ovc x264 -x264encopts pass=2:subq=7:frameref=2:me=esa:threads=12:partitions=all:bframes=0:bitrate=100000000 -o %s" % f, name_h264
	os.system(cmd)

def main():

	threads = 2

	# count frames,fps,width,height #
	lst = [
			[30,   30,   64,   64], 
			[3600, 30,  128,  128], 
			[30,   30, 2048, 2048], 
			[300,  30, 2912, 2912], 
			[300,  30, 4096, 4096], 
			[1200, 30, 1920, 1200], 
			[3600, 30, 256,   256], 
			[3600, 60, 2912, 2912], 
			[3600, 30, 4096, 4096], 
			[60,   30, 5120, 5120]
		 ]

	for c, f, w, h in lst:
		gen_images(threads, c, w, h)
		name = "_%04dx%04d_i%04d_%2.2ffps" % w, h, c, f
		coding_video(name, f)

if __name__ == "__main__":
	main()

