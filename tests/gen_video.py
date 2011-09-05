#!/usr/bin/python

import Image, ImageDraw
import os, random
import multiprocessing

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
	num = args[0]
	w   = args[1]
	h   = args[2]
	c   = args[3]

	im = Image.new("RGB", (w, h), (0, 0, 0))
	draw = ImageDraw.Draw(im)
	clr = cvt_color(num)
	for j in range(len(clr)):
		draw.point((j, 0), (clr[j] * 255 , clr[j] * 255, clr[j] * 255))

	if c == 1:
		for j in range((w + h) / 4):
			draw.line([random.randint(16, w), random.randint(16, h), random.randint(16, w), random.randint(16, h) ], (random.randint(55, 255), random.randint(55, 255), random.randint(55, 255) ))

	name = "img_%06d.png" % num
	print (name)
	im.save(name)

def gen_images(t, c, w, h, cm):
	arr = range(1, c + 1)
	pool = multiprocessing.Pool(t) # start t worker processes
	args = [[i, w, h, cm] for i in arr]
	pool.map(gen_image, args, 3) # Ensure the chunk size is 3

def coding_video(name, f):
	# xvid 
	name_xvid = "xvid" + name + ".avi"
	cmd = "mencoder mf://*.png -mf fps=%d:type=png -ovc xvid -xvidencopts pass=1:max_bframes=2:chroma_opt:vhq=4:bvhq=1:quant_type=mpeg:threads=12:bitrate=100000000 -o /dev/null" %  f
	os.system(cmd)
	cmd = "mencoder mf://*.png -mf fps=%d:type=png -ovc xvid -xvidencopts pass=2:max_bframes=2:chroma_opt:vhq=4:bvhq=1:quant_type=mpeg:threads=12:bitrate=100000000 -o %s" % (f, name_xvid)
	os.system(cmd)
	
	# vpx 
	name_vpx = "vp80" + name + ".webm"
	cmd = "mencoder mf://*.png -mf fps=%d:type=png -ovc lavc -lavcopts vcodec=libvpx:vpass=1:threads=8:vbitrate=100000000 -o /dev/null" % f 
	os.system(cmd)
	cmd = "mencoder mf://*.png -mf fps=%d:type=png -ovc lavc -lavcopts vcodec=libvpx:vpass=2:threads=8:vbitrate=100000000 -o %s" % (f, name_vpx)
	os.system(cmd)
	
	# h264 
	name_h264 = "h264" + name + ".avi"
	cmd = "mencoder mf://*.png -mf fps=%d:type=png -ovc x264 -x264encopts pass=1:subq=7:frameref=2:me=esa:threads=12:partitions=all:bframes=0:bitrate=100000000 -o /dev/null" % f
	os.system(cmd)
	cmd = "mencoder mf://*.png -mf fps=%d:type=png -ovc x264 -x264encopts pass=2:subq=7:frameref=2:me=esa:threads=12:partitions=all:bframes=0:bitrate=100000000 -o %s" % (f, name_h264)
	os.system(cmd)

	# remove all
	os.system("rm *.png")

def main():
	threads = 4
	# count frames,fps,width,height #
	lst = [
			[600, 30, 1,  256,  256],
			[600, 30, 1, 2912, 2912], 
			[600, 30, 1, 4096, 4096], 
			[600, 30, 1, 5120, 5120], 
			[600, 30, 0,  256,  256],
			[600, 30, 0, 2912, 2912], 
			[600, 30, 0, 4096, 4096], 
			[600, 30, 0, 5120, 5120]
		 ]

	for c, f, cm, w, h in lst:
		gen_images(threads, c, w, h, cm)
		name  = "_%04dx%04d_img_%04d_%2.2ffps_complex_%d" % (w, h, c, f, cm)
		coding_video(name, f)

if __name__ == "__main__":
	main()

	"""[30,   30, 0,   64,   64],
			[3600, 30, 0,  128,  128], 
			[7200, 30, 1,  256,  256], 
			[30,   30, 1, 2048, 2048], 
			[300,  30, 1, 2912, 2912], 
			[300,  30, 0, 4096, 4096], 
			[360,  30, 1, 4096, 4096], 
			[1200, 30, 0, 1920, 1200], 
			[3600, 30, 0,  256,  256], 
			[3600, 60, 0, 2912, 2912], 
			[3600, 30, 0, 4096, 4096], 
			[60,   30, 0, 5120, 5120],
			[360,  60, 1, 5120, 5120]"""
