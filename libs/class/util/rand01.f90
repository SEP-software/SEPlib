real function rand01( iseed)
integer ia, im,       iseed
parameter(ia = 727,im = 524287)
iseed = mod(iseed*ia,im)
rand01 =(float(iseed) - 0.5)/float(im - 1)
return
end  
