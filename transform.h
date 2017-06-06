#ifndef TRANSFORM_H_
#define TRANSFORM_H_

int  transform(unsigned char* src,unsigned int srcWidth, unsigned int srcHeight,unsigned char* dst, unsigned int dstWidth,
                unsigned int dstHeight, float rotationCos, float rotationSin, int translationX,int translationY);

#endif // TRANSFORM_H_
