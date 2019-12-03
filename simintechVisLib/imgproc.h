#define EXPORT extern "C" __declspec(dllexport)

#include "core.h"

using namespace cv;
using namespace std;

//// Functions

/** @brief Converts an image from one color space to another 
@param src: input image.
@param dst: output image.
@param code: Specifies the type of conversion
*/
EXPORT int sim_convertColor(void* src, void** dst, int code);

/** @brief The function applies fixed-level thresholding to a multiple-channel array
@param src: input image.
@param dst: output image.
@param thresh threshold value.
@param maxval maximum value to use with the #THRESH_BINARY and #THRESH_BINARY_INV thresholding
@param type: Thresholding type
*/
EXPORT int sim_threshold(void* src, void** dst, double thresh, double maxval, int type);

/** @brief Applies an adaptive threshold to an array.
@param src: input image.
@param dst: output image.
@param maxValue Non-zero value assigned to the pixels for which the condition is satisfied
@param adaptiveMethod Adaptive thresholding algorithm to use, see #AdaptiveThresholdTypes.
@param maxval maximum value to use with the #THRESH_BINARY and #THRESH_BINARY_INV thresholding
@param thresholdType Thresholding type that must be either #THRESH_BINARY or #THRESH_BINARY_INV,
see #ThresholdTypes.
@param blockSize Size of a pixel neighborhood that is used to calculate a threshold value for the
pixel: 3, 5, 7, and so on.
@param C Constant subtracted from the mean or weighted mean (see the details below). Normally, it
is positive but may be zero or negative as well.
*/
EXPORT int sim_adaptiveThreshold(void* src, void** dst, double maxValue, int adaptiveMethod,
	int thresholdType, int blockSize, double C);

/** @brief Creates one 3-channel array out of several single-channel ones.
@param src1: 1 input channel.
@param src2: 2 input channel.
@param src3: 3 input channel.
@param dst: output image.
*/
EXPORT int sim_merge(void* src1, void* src2, void* src3, void** dst);

/** @brief Divides a 3-channel array into several single-channel arrays.
@param src1: input channel.
@param dst1: 1 output image.
@param dst2: 2 output image.
@param dst3: 3 output image.
*/
EXPORT int sim_split(void* src1, void** dst1, void** dst2, void** dst3);

/** @brief Takes rectangle area from image.
@param src: input image.
@param dst: output image.
@param x: Rectangle coordinate X
@param y: Rectangle coordinate Y
@param h: Height of rectangle
@param w: Width of rectangle
*/
EXPORT int sim_roi(void* src, void** dst, int x, int y, int w, int h);

/** @brief Checks if array elements lie between the elements of two other arrays.
@param src: input array.
@param dst: output array.
@param low: inclusive lower boundary array or a scalar.
@param up: inclusive upper boundary array or a scalar.
*/
EXPORT int sim_inRange(void* src, void** dst, float* low, float* up);

/** @brief Blurs an image using a Gaussian filter.
@param src: input image.
@param dst: output image.
@param ksize Gaussian kernel size. ksize.width and ksize.height can differ but they both must be
positive and odd. Or, they can be zero's and then they are computed from sigma.
@param sigmaX Gaussian kernel standard deviation in X direction.
@param sigmaY Gaussian kernel standard deviation in Y direction; if sigmaY is zero, it is set to be
equal to sigmaX, if both sigmas are zeros, they are computed from ksize.width and ksize.height,
respectively (see #getGaussianKernel for details); to fully control the result regardless of
possible future modifications of all this semantics, it is recommended to specify all of ksize,
sigmaX, and sigmaY.
*/
EXPORT int sim_gaussianBlur(void* src, void** dst, int ksizeX, int ksizeY, double sigmaX, double sigmaY);

/** @brief Applies the bilateral filter to an image.
@param src: input image.
@param dst: output image.
@param d Diameter of each pixel neighborhood that is used during filtering. If it is non-positive,
it is computed from sigmaSpace.
@param sigmaColor Filter sigma in the color space. A larger value of the parameter means that
farther colors within the pixel neighborhood (see sigmaSpace) will be mixed together, resulting
in larger areas of semi-equal color.
@param sigmaSpace Filter sigma in the coordinate space. A larger value of the parameter means that
farther pixels will influence each other as long as their colors are close enough (see sigmaColor
). When d\>0, it specifies the neighborhood size regardless of sigmaSpace. Otherwise, d is
proportional to sigmaSpace.
*/
EXPORT int sim_bilateralFilter(void* src, void** dst, int d,	double sigmaColor, double sigmaSpace);

/** @brief Calculates the normalized sum of squares of the pixel values overlapping the filter.
@param src input image
@param dst output image of the same size and type as _src
@param ddepth the output image depth (-1 to use src.depth())
@param ksize kernel size
@param anchor kernel anchor point. The default value of Point(-1, -1) denotes that the anchor is at the kernel
center.
@param normalize flag, specifying whether the kernel is to be normalized by it's area or not.
*/
EXPORT int sim_boxFilter(void* src, void** dst, int ddepth,
	int ksizeX, int ksizeY, int anchorX, int anchorY,
	bool normalize);

/** @brief Blurs an image using the normalized box filter.
@param src input image;
@param dst output image of the same size and type as src.
@param ksize blurring kernel size.
@param anchor anchor point; default value Point(-1,-1) means that the anchor is at the kernel
center.
 */
EXPORT int sim_blur(void* src, void** dst,
	int ksizeX, int ksizeY, int anchorX, int anchorY);

/** @brief Convolves an image with the kernel.
@param src input image.
@param dst output image of the same size and the same number of channels as src.
@param ddepth desired depth of the destination image, see @ref filter_depths "combinations"
@param ksize number of elements of convolution kernel matrix
@param kernel convolution kernel (or rather a correlation kernel), a single-channel floating point
matrix; if you want to apply different kernels to different channels, split the image into
separate color planes using split and process them individually.
@param anchor anchor of the kernel that indicates the relative position of a filtered point within
the kernel; the anchor should lie within the kernel; default value (-1,-1) means that the anchor
is at the kernel center.
@param delta optional value added to the filtered pixels before storing them in dst.
@param borderType pixel extrapolation method, see #BorderTypes
@sa  sepFilter2D, dft, matchTemplate
 */
EXPORT int sim_filter2D(void* src, void** dst, int ddepth,
	int ksize, float *kernel, int anchorX, int anchorY,
	double delta);

/** @brief Calculates the first, second, third, or mixed image derivatives using an extended Sobel operator.
@param src input image.
@param dst output image of the same size and the same number of channels as src .
@param ddepth output image depth
@param dx order of the derivative x.
@param dy order of the derivative y.
@param ksize size of the extended Sobel kernel; it must be 1, 3, 5, or 7.
@param scale optional scale factor for the computed derivative values; by default, no scaling is
applied (see #getDerivKernels for details).
@param delta optional delta value that is added to the results prior to storing them in dst.
 */
EXPORT int sim_sobel(void* src, void** dst, int ddepth,
	int dx, int dy, int ksize,
	double scale, double delta);

/** @brief Calculates the first x- or y- image derivative using Scharr operator.
@param src input image.
@param dst output image of the same size and the same number of channels as src.
@param ddepth output image depth, see @ref filter_depths "combinations"
@param dx order of the derivative x.
@param dy order of the derivative y.
@param scale optional scale factor for the computed derivative values; by default, no scaling is
applied (see #getDerivKernels for details).
@param delta optional delta value that is added to the results prior to storing them in dst.
@sa  cartToPolar
 */
EXPORT int sim_scharr(void* src, void** dst, int ddepth,
	int dx, int dy, double scale, double delta);

/** @brief Calculates the Laplacian of an image.
@param src Source image.
@param dst Destination image of the same size and the same number of channels as src .
@param ddepth Desired depth of the destination image.
@param ksize Aperture size used to compute the second-derivative filters. See #getDerivKernels for
details. The size must be positive and odd.
@param scale Optional scale factor for the computed Laplacian values. By default, no scaling is
applied. See #getDerivKernels for details.
@param delta Optional delta value that is added to the results prior to storing them in dst .
 */
EXPORT int sim_laplacian(void* src, void** dst, int ddepth,
	int ksize, double scale, double delta);

/** @brief Finds edges in an image using the Canny algorithm 
@param image 8-bit input image.
@param edges output edge map; single channels 8-bit image, which has the same size as image .
@param threshold1 first threshold for the hysteresis procedure.
@param threshold2 second threshold for the hysteresis procedure.
@param apertureSize aperture size for the Sobel operator.
@param L2gradient a flag, indicating whether a more accurate \f$L_2\f$ norm
\f$=\sqrt{(dI/dx)^2 + (dI/dy)^2}\f$ should be used to calculate the image gradient magnitude (
L2gradient=true ), or whether the default \f$L_1\f$ norm \f$=|dI/dx|+|dI/dy|\f$ is enough (
L2gradient=false ).
 */
EXPORT int sim_canny(void* src, void** dst, double threshold1, double threshold2,
	int apertureSize, bool L2gradient);

/** @brief Harris corner detector.
@param src Input single-channel 8-bit or floating-point image.
@param dst Image to store the Harris detector responses. It has the type CV_32FC1 and the same
size as src .
@param blockSize Neighborhood size (see the details on #cornerEigenValsAndVecs ).
@param ksize Aperture parameter for the Sobel operator.
@param k Harris detector free parameter.
 */
EXPORT int sim_cornerHarris(void* src, void** dst, int blockSize,
	int ksize, double k);

/** @brief Dilates an image by using a specific structuring element.
@param src input image; the number of channels can be arbitrary, but the depth should be one of
CV_8U, CV_16U, CV_16S, CV_32F or CV_64F.
@param dst output image of the same size and type as src.
@param shape Element shape
@param blockSize Size of the structuring element.
@param ksize Anchor position of structuring Element.
 */
EXPORT int sim_dilate(void* src, void** dst, int blockSize, int ksize, int kShape);

/** @brief Erodes an image by using a specific structuring element.
@param src input image; the number of channels can be arbitrary, but the depth should be one of
CV_8U, CV_16U, CV_16S, CV_32F or CV_64F.
@param dst output image of the same size and type as src.
@param shape Element shape
@param blockSize Size of the structuring element.
@param ksize Anchor position of structuring Element.
 */
EXPORT int sim_erode(void* src, void** dst, int blockSize, int ksize, int kShape);


/** @brief Resizes an image.
@param src input image.
@param dst output image; it has the size dsize (when it is non-zero) or the size computed from
src.size(), fx, and fy; the type of dst is the same as of src.
@param ksizeX output image size;
@param ksizeY output image size;
@param fx scale factor along the horizontal axis; when it equals 0
@param fy scale factor along the vertical axis; when it equals 0
@param interpolation interpolation method
 */
EXPORT int sim_resizeP(void* src, void** dst, int ksizeX, int ksizeY, double fx, double,
	int interpolation);

/** @brief Resizes an image.
@param src input image.
@param dst output image; it has the size dsize (when it is non-zero) or the size computed from
src.size(), fx, and fy; the type of dst is the same as of src.
@param ksizeX output image size;
@param ksizeY output image size;
 */
EXPORT int sim_resize(void* src, void** dst, int ksizeX, int ksizeY);

/** @brief Applies a perspective transformation to an image.
@param src input image.
@param dst output image that has the same type as src.
@param M 2 times 3 transformation matrix.
@param dsizeX size of the output image.
@param dsizeY size of the output image.
 */
EXPORT int sim_warpAffine(void* src, void** dst,
	double* M, int dsizeX, int dsizeY,
	int flags);

/** @brief Applies a perspective transformation to an image.
@param src input image.
@param dst output image that has the same type as src.
@param srcPts - Array contains transformation points (x1,y1, x2,y2, x3,y3) on input image
@param dstPts - Array contains transformation points (x1,y1, x2,y2, x3,y3) on output image
@param dsizeX size of the output image.
@param dsizeY size of the output image.
 */
EXPORT int sim_warpPerspective(void* src, void** dst,
	float* srcPts, float* dstPts, int dsizeY, int dsizeX);

/** @brief Fills a connected component with the given color.
@param src input 8-bit 3-channel image.
@param dst output 8-bit 3-channel image.
@param pX Starting point x coordinate.
@param pY Starting point y coordinate.
@param color New color 3 uchar values
 */
EXPORT int sim_floodFill(void* src, void** dst,
	int pX, int py, uchar* color);
