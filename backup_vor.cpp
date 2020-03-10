// /**
//  * @file vor.cpp
//  * Implementation of functions in the filler namespace.
//  *
//  */
// // included within  "vor.h" for template instantiation
// #include <math.h>

// /* vorDotDFS given as an example for PA2 */
// animation filler::vorDotDFS(PNG& img, double density, int dotGrid, int
// dotSize,
//                             int frameFreq) {
//   dotColorPicker a(dotGrid, dotSize);
//   return vor<Stack>(img, density, a, frameFreq);
// }

// animation filler::vorSolidDFS(PNG& img, double density, int frameFreq) {
//   /**
//    * @todo Your code here!
//    */
//   solidColorPicker s;
//   return vor<Stack>(img, density, s, frameFreq);
// }

// animation filler::vorFadeDFS(PNG& img, double density, double fadeFactor,
//                              int frameFreq) {
//   /**
//    * @todo Your code here!
//    */
//   fadeColorPicker f(fadeFactor);
//   return vor<Stack>(img, density, f, frameFreq);
// }

// /* vorDotBFS given as an example for PA2 */
// animation filler::vorDotBFS(PNG& img, double density, int dotGrid, int
// dotSize,
//                             int frameFreq) {
//   dotColorPicker a(dotGrid, dotSize);
//   return vor<Queue>(img, density, a, frameFreq);
// }

// animation filler::vorSolidBFS(PNG& img, double density, int frameFreq) {
//   /**
//    * @todo Your code here!
//    */
//   solidColorPicker s;
//   return vor<Queue>(img, density, s, frameFreq);
// }

// animation filler::vorFadeBFS(PNG& img, double density, double fadeFactor,
//                              int frameFreq) {
//   /**
//    * @todo Your code here!
//    */
//   fadeColorPicker f(fadeFactor);
//   return vor<Queue>(img, density, f, frameFreq);
// }

// template <template <class T> class OrderingStructure>
// animation filler::vor(PNG& img, double density, colorPicker& fillColor,
//                       int frameFreq) {
//   /**
//    * @todo You need to implement this function!
//    *
//    * This is a general description of a space filling algorithm, where
//    * the space is partitioned into a set of regions each color of which
//    * is determined by the color of a point
//    * chosen from an original image. We call those original points
//    * "centers." (See pictures in the specification.)
//    *
//    * The algorithm requires ordering structures used to orchestrate
//    * the sequence of points filled. This structure type info is passed to the
//    * fill algorithm via its template parameter. For a breadth-first fill,
//    * we use Queues, and for a depth-first fill, we use Stacks. Function
//    * vorDotDFS provides an example call to function vor.
//    *
//    * The algorithm includes the following steps:
//    * 1) you will first select a random set
//    * of coordinates (and their colors) to use as centers from which to
//    * begin the fill. (this function is in file vor_given.cpp -- for
//    * testing purposes, you'll use regularly spaced points, rather than
//    * random.)
//    * 2) Initialize a structure to use to maintain a collection of
//    * ordering structures
//    *
//    * 3) Initialize the fill: For each center c, in round-robin order,
//    *     do the following:
//    *     a)  add the center to the its ordering structure. (every center
//    *         its own!
//    *     b)  mark the location of that center as processed (the way you
//    *         do this is up to you!)
//    *     c)  we have a choice to actually set the color of the pixel in
//    *         the fill when we add or when we remove. In our test cases,
//    *         we assume that you will change a color when a point is
//    *         added to a structure. (this is mostly relevant for checking
//    *         the animations.)
//    *
//    * 5) Complete the fill: Until all ordering structures (OS) are empty,
//    *    do the following for each OS, in a round robin order, indexing
//    *    the iterations by k (an integer distance from the center):
//    *
//    *      For each point less than or equal to distance k from its center:
//    *      a)Remove the  point p from the ordering structure, and then...
//    *
//    *        i.    add p's unprocessed neighbors to the ordering structure if
//    *              they are within the appropriate distance from the center.
//    We
//    *              describe this more carefully below. We call these the
//    "valid"
//    *              neighbors.
//    *        ii.    use the colorPicker to set the new color of the valid
//    * neighbors. iii.    mark the valid neighbors as processed. iv.    as each
//    * neighbor is processed, if it is an appropriate frame, send the current
//    PNG
//    * to the animation (as described below).
//    *
//    *      b) When implementing your breadth-first and depth-first fills,
//    *            you will need to explore neighboring pixels in some order.
//    *
//    *        For this assignment, each pixel p has *up to* 8 neighbors,
//    * consisting of the 8 pixels who share an edge with p. (We leave it to you
//    to
//    * describe those 8 pixel locations, relative to the location of p.)
//    *
//    *        While the order in which you examine neighbors does not matter
//    *        for a proper fill, you must use the same order as we do for
//    *        your animations to come out like ours!
//    *
//    *        The order you should put
//    *        neighboring pixels **ONTO** the queue or stack is as follows:
//    *        ** UP(-y), UPLEFT(-x,-y), LEFT(-x), LEFTDOWN(-x,+y), DOWN(+y),
//    *        DOWNRIGHT(+x,+y), RIGHT(+x), RIGHTUP(+x,-y)**
//    *
//    *        If you do them in a different order, your fill may
//    *        still work correctly, but your animations will be different
//    *        from the grading scripts!
//    *
//    *        TWO IMPORTANT NOTES:
//    *        1) *UP* here means towards the top of the image, so since an
//    image
//    * has smaller y coordinates at the top, this is in the *negative y*
//    *        direction. Similarly, *DOWN* means in the *positive y*
//    *        direction.
//    *        2) not all of the 8 neighbors will be processed at every
//    iteration
//    * of the while loop. You must assure that all vertices distance k or less
//    *        from the center are processed (colored and put on the queue)
//    before
//    *        ANY whose distance is *greater than* k. k is a non-negative
//    integer.
//    *        Finally, distance is the standard Euclidean distance  (computed
//    *        using the Pythagorean theorem). It is this requirement that
//    assures
//    *        that the fill grows outward from the center in the shape of a
//    * circle, rather than a diamond or a square.
//    *
//    *      c) For every g pixels filled, **starting at the gth pixel**, you
//    *        must add a frame to the animation, where g = frameFreq.
//    *
//    *        For example, if frameFreq is 4, then after the 4th pixel has
//    *        been filled you should add a frame to the animation, then again
//    *        after the 8th pixel, etc.  You must only add frames for the
//    *        number of pixels that have been filled, not the number that
//    *        have been checked. So if frameFreq is set to 1, a pixel should
//    *        be filled every frame.
//    *      d) Finally, as you leave the function, send one last frame to the
//    *        animation. This frame will be the final result of the fill, and
//    *        it will be the one we test against.
//    */

//   /* Your code here. As a point of reference, we used three different helper
//    * functions to complete this code. You may add as many as you wish, since
//    * we will be grading vor.h. File "vor_given.cpp also includes the function
//    * used to generate the original set of centers.
//    */

//   // step 1:
//   vector<center> centers = randSample(img, density);
//   vector<point> centerPoints;
//   for (unsigned i = 0; i < centers.size(); i++) {
//     point p(centers[i]);
//     p.x = centers[i].x;
//     p.y = centers[i].y;
//     centerPoints.push_back(p);
//   }

//   // step 2:
//   vector<OrderingStructure<point>> OS(centerPoints.size());

//   // step 3:
//   bool unprocessed[img.height()][img.width()];
//   for (unsigned i = 0; i < img.height(); i++) {
//     for (unsigned j = 0; j < img.width(); j++) {
//       unprocessed[i][j] = true;
//     }
//   }
//   for (unsigned i = 0; i < centerPoints.size(); i++) {
//     HSLAPixel* centerPointPixel =
//         img.getPixel(centerPoints[i].x, centerPoints[i].y);
//     *centerPointPixel = fillColor(centerPoints[i]);
//     OS[i].add(centerPoints[i]);
//     unprocessed[centerPoints[i].y][centerPoints[i].x] = false;
//   }

//   // step 5:
//   int k = 0;
//   int noPixelFilled = 0;
//   animation imgAnimation;
//   bool listOfEmptyOS[centerPoints.size()];
//   for (int i = 0; i < centerPoints.size(); i++) {
//     listOfEmptyOS[i] = false;
//   }
//   int numberOfEmptyOS = 0;
//   bool isThereRemoval = false;

//   while (numberOfEmptyOS < centerPoints.size()) {
//     numberOfEmptyOS = 0;
//     isThereRemoval = false;
//     for (unsigned i = 0; i < OS.size(); i++) {
//       if (!OS[i].isEmpty()) {
//         point currPoint = OS[i].peek();
//         double distCenter = sqrt(pow((double)(currPoint.x - currPoint.c.x),
//         2) +
//                                  pow((double)(currPoint.y - currPoint.c.y),
//                                  2));
//         if (distCenter < k + 1) {
//           OS[i].remove();

//           // Up case
//           if (currPoint.y - 1 > 0 &&
//               unprocessed[(currPoint.y - 1)][currPoint.x]) {
//             point currPointUp(currPoint.x, currPoint.y - 1, currPoint.c, k +
//             1); OS[i].add(currPointUp); HSLAPixel* currPixelUp =
//             img.getPixel(currPoint.x, currPoint.y - 1); *currPixelUp =
//             fillColor(currPointUp); unprocessed[currPoint.y - 1][currPoint.x]
//             = false; noPixelFilled++; addFrame(frameFreq, imgAnimation, img,
//             noPixelFilled); isThereRemoval = true;
//           }

//           // Up left case
//           if (currPoint.x - 1 > 0 && currPoint.y - 1 > 0 &&
//               unprocessed[currPoint.y - 1][currPoint.x - 1]) {
//             point currPointUpLeft(currPoint.x - 1, currPoint.y - 1,
//             currPoint.c,
//                                   k + 1);
//             OS[i].add(currPointUpLeft);
//             HSLAPixel* currPixelUpLeft =
//                 img.getPixel(currPoint.x - 1, currPoint.y - 1);
//             *currPixelUpLeft = fillColor(currPointUpLeft);
//             unprocessed[currPoint.y - 1][currPoint.x - 1] = false;
//             noPixelFilled++;
//             addFrame(frameFreq, imgAnimation, img, noPixelFilled);
//             isThereRemoval = true;
//           }

//           // Left case
//           if (currPoint.x - 1 > 0 &&
//               unprocessed[currPoint.y][currPoint.x - 1]) {
//             point currPointLeft(currPoint.x - 1, currPoint.y, currPoint.c,
//                                 k + 1);
//             OS[i].add(currPointLeft);
//             HSLAPixel* currPixelLeft =
//                 img.getPixel(currPoint.x - 1, currPoint.y);
//             *currPixelLeft = fillColor(currPointLeft);
//             unprocessed[currPoint.y][currPoint.x - 1] = false;
//             noPixelFilled++;
//             addFrame(frameFreq, imgAnimation, img, noPixelFilled);
//             isThereRemoval = true;
//           }

//           // Left down
//           if (currPoint.x - 1 > 0 && currPoint.y + 1 < img.height() &&
//               unprocessed[currPoint.y + 1][currPoint.x - 1]) {
//             point currPointLeftDown(currPoint.x - 1, currPoint.y + 1,
//                                     currPoint.c, k + 1);
//             OS[i].add(currPointLeftDown);
//             HSLAPixel* currPixelLeftDown =
//                 img.getPixel(currPoint.x - 1, currPoint.y + 1);
//             *currPixelLeftDown = fillColor(currPointLeftDown);
//             unprocessed[currPoint.y + 1][currPoint.x - 1] = false;
//             noPixelFilled++;
//             addFrame(frameFreq, imgAnimation, img, noPixelFilled);
//             isThereRemoval = true;
//           }

//           // Down case
//           if (currPoint.y + 1 < img.height() &&
//               unprocessed[currPoint.y + 1][currPoint.x]) {
//             point currPointDown(currPoint.x, currPoint.y + 1, currPoint.c,
//                                 k + 1);
//             OS[i].add(currPointDown);
//             HSLAPixel* currPixelDown =
//                 img.getPixel(currPoint.x, currPoint.y + 1);
//             *currPixelDown = fillColor(currPointDown);
//             unprocessed[currPoint.y + 1][currPoint.x] = false;
//             noPixelFilled++;
//             addFrame(frameFreq, imgAnimation, img, noPixelFilled);
//             isThereRemoval = true;
//           }

//           // Down right case
//           if (currPoint.x + 1 < img.width() && currPoint.y + 1 < img.height()
//           &&
//               unprocessed[currPoint.y + 1][currPoint.x + 1]) {
//             point currPointDownRight(currPoint.x + 1, currPoint.y + 1,
//                                      currPoint.c, k + 1);
//             OS[i].add(currPointDownRight);
//             HSLAPixel* currPixelDownRight =
//                 img.getPixel(currPoint.x + 1, currPoint.y + 1);
//             *currPixelDownRight = fillColor(currPointDownRight);
//             unprocessed[currPoint.y + 1][currPoint.x + 1] = false;
//             noPixelFilled++;
//             addFrame(frameFreq, imgAnimation, img, noPixelFilled);
//             isThereRemoval = true;
//           }

//           // Right case
//           if (currPoint.x + 1 < img.width() &&
//               unprocessed[currPoint.y][currPoint.x + 1]) {
//             point currPointRight(currPoint.x + 1, currPoint.y, currPoint.c,
//                                  k + 1);
//             OS[i].add(currPointRight);
//             HSLAPixel* currPixelRight =
//                 img.getPixel(currPoint.x + 1, currPoint.y);
//             *currPixelRight = fillColor(currPointRight);
//             unprocessed[currPoint.y][currPoint.x + 1] = false;
//             noPixelFilled++;
//             addFrame(frameFreq, imgAnimation, img, noPixelFilled);
//             isThereRemoval = true;
//           }

//           // Right up case
//           if (currPoint.x + 1 < img.width() && currPoint.y - 1 > 0 &&
//               unprocessed[currPoint.y - 1][currPoint.x + 1]) {
//             point currPointRightUp(currPoint.x + 1, currPoint.y - 1,
//                                    currPoint.c, k + 1);
//             OS[i].add(currPointRightUp);
//             HSLAPixel* currPixelRightUp =
//                 img.getPixel(currPoint.x + 1, currPoint.y - 1);
//             *currPixelRightUp = fillColor(currPointRightUp);
//             unprocessed[currPoint.y - 1][currPoint.x + 1] = false;
//             noPixelFilled++;
//             addFrame(frameFreq, imgAnimation, img, noPixelFilled);
//             isThereRemoval = true;
//           }
//         }
//       } else {
//         listOfEmptyOS[i] = true;
//       }
//     }

//     if (!isThereRemoval) {
//       k++;
//     }

//     for (int i = 0; i < centerPoints.size(); i++) {
//       if (listOfEmptyOS[i]) {
//         numberOfEmptyOS++;
//       }
//     }
//   }
//   imgAnimation.addFrame(img);
//   return imgAnimation;
// }

// void filler::processNeighboringPixel(int x, int y, center c, int level, int
// i,
//                                      vector<OrderingStructure<point>>& OS,
//                                      PNG& img, int frameFreq,
//                                      animation& imgAnimation,
//                                      colorPicker& fillColor, int&
//                                      noPixelFilled, bool& isThereRemoval) {
//   point currPointNeighbor(x, y, c, level);
//   OS[i].add(currPointNeighbor);
//   HSLAPixel* currPixelNeighbor = img.getPixel(x, y);
//   *currPixelNeighbor = fillColor(currPointNeighbor);
//   noPixelFilled++;
//   addFrame(frameFreq, imgAnimation, img, noPixelFilled);
//   isThereRemoval = true;
// }

// void filler::addFrame(int frameFreq, animation& imgAnimation, PNG& img,
//                       int noPixelFilled) {
//   if (noPixelFilled % frameFreq == 0) {
//     imgAnimation.addFrame(img);
//   }
// }