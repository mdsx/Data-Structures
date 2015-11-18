#include <iostream>
#include "StarNearEarth.h"
#include "FHsparseMat.h"
#include <cmath>
using namespace std;

// SNE_Analyzer class prototype
class SNE_Analyzer : public StarNearEarth
{
private:
   double x, y, z;

public:
   void calcCartCoords();
   double getX() { return x; }
   double getY() { return y; }
   double getZ() { return z; }
   string coordToString();
   SNE_Analyzer & operator=(const StarNearEarth &sne);
};

// SNE_Analyzer method definitions
void SNE_Analyzer::calcCartCoords()
{
   double rAscRad, declRad, r, pi;
   pi = 3.141592653589793238463;

   rAscRad = getRAsc() * (pi / 180);
   declRad = getDec() * (pi / 180);
   r = 3.262 / getParallaxMean();

   x = r * cos(declRad) * cos(rAscRad);
   y = r * cos(declRad) * sin(rAscRad);
   z = r * sin(declRad);
}
string SNE_Analyzer::coordToString()
{
   ostringstream cartCoords;
   cartCoords << "(" << x << ", " << y << ", " << z << ")";
   return cartCoords.str();
}

SNE_Analyzer & SNE_Analyzer::operator=(const StarNearEarth &sne)
{
   setRank(sne.getRank());
   setNameCns(sne.getNameCns());
   setNumComponents(sne.getNumComponents());
   setNameLhs(sne.getNameLhs());
   setRAsc(sne.getRAsc());
   setDec(sne.getDec());
   setPropMotionMag(sne.getPropMotionMag());
   setPropMotionDir(sne.getPropMotionDir());
   setParallaxMean(sne.getParallaxMean());
   setParallaxVariance(sne.getParallaxVariance());
   setWhiteDwarfFlag(sne.getWhiteDwarfFlag());
   setSpectralType(sne.getSpectralType());
   setMagApparent(sne.getMagApparent());
   setMagAbsolute(sne.getMagAbsolute());
   setMass(sne.getMass());
   setNotes(sne.getNotes());
   setNameCommon(sne.getNameCommon());
   calcCartCoords();

   return *this;
}

// --------------- main ---------------
int main()
{
   ostringstream starOut;
   int k, arraySize, row, col;
   double maxX, minX, maxY, minY, maxZ, minZ,
      xRange, yRange, zRange,
      xConversion, yConversion, zConversion;
   StarNearEarthReader starInput("nearest_stars.txt");
   const int NUM_COLS = 70;
   const int NUM_ROWS = 35;

   if (starInput.readError())
   {
      cout << "couldn't open " << starInput.getFileName() << " for input.\n";
      exit(1);
   }

   cout << starInput.getFileName() << endl;
   cout << starInput.getNumStars() << endl;

   // create an array of objects for our own use:
   arraySize = starInput.getNumStars();
   SNE_Analyzer *starArray = new SNE_Analyzer[arraySize];
   for (k = 0; k < arraySize; k++)
      starArray[k] = starInput[k];

   // display cartesian coords
   for (int k = 0; k < arraySize; k++)
      cout << starArray[k].getNameCommon() << " "
      << starArray[k].coordToString() << endl;

   // get max and min coords for scaling
   maxX = minX = maxY = minY = maxZ = minZ = 0;
   for (int k = 0; k < arraySize; k++)
   {
      if (starArray[k].getX() > maxX)
         maxX = starArray[k].getX();
      if (starArray[k].getX() < minX)
         minX = starArray[k].getX();

      if (starArray[k].getY() > maxY)
         maxY = starArray[k].getY();
      if (starArray[k].getY() < minY)
         minY = starArray[k].getY();

      if (starArray[k].getZ() > maxZ)
         maxZ = starArray[k].getZ();
      if (starArray[k].getZ() < minZ)
         minZ = starArray[k].getZ();
   }
   xRange = maxX - minX;
   yRange = maxY - minY;
   zRange = maxZ - minZ;

   xConversion = double(NUM_ROWS) / xRange;
   //yConversion = double(NUM_COLS) / yRange; // for x-y mapping
   zConversion = double(NUM_COLS) / zRange;
   yConversion = double(NUM_ROWS) / yRange; // for y-z mapping

   SparseMat<char> starMap(NUM_ROWS, NUM_COLS, ' ');

   for (k = 0; k < arraySize; k++)
   {
      // for x-y mapping
      //row = xConversion * (starArray[k].getX() - minX);
      //col = yConversion * (starArray[k].getY() - minY);

      // for x-z mapping
      //row = xConversion * (starArray[k].getX() - minX);
      //col = zConversion * (starArray[k].getZ() - minZ);

      // for y-z mapping
      row = (int) yConversion * (starArray[k].getY() - minY);
      col = (int) zConversion * (starArray[k].getZ() - minZ);

      try
      {
         if (starArray[k].getRank() < 10)
            starMap.set(row, col) = char(starArray[k].getRank());
         else
            starMap.set(row, col) = '*';
      }
      catch (...)
      {
         cout << "oops, matrix bounds violation" << endl;
      }
   }

   // for x-y mapping
   //row = xConversion * (-minX);
   //col = yConversion * (-minY);

   // for x-z mapping
   //row = xConversion * (-minX);
   //col = zConversion * (-minZ);

   // for y-z mapping
   row = (int) yConversion * (-minY);
   col = (int) zConversion * (-minZ);

   starMap.set(row, col) = 'S';

   for (row = 0; row < NUM_ROWS; row++)
   {
      for (col = 0; col < NUM_COLS; col++)
      {
         starOut << starMap.get(row, col);
      }
      starOut << "\n";
   }

   cout << "\n\n" << starOut.str();

   delete [] starArray;

   return 0;
}

/* Bonus Assignment 10 Program Output:

The output's formatting looks better in a console window.  Also, the symbols in
place of numerical ranks from getRank() was a nice touch.  Overall fun assignment
to end the quarter.

------------------Run 1: x-y map------------------
nearest_stars.txt
100
Proxima Centauri (-1.54629, -1.18348, -3.76934)
Barnard's Star (-0.056838, -5.94339, 0.487961)
Wolf 359 (-7.43033, 2.11355, 0.950536)
Lalande 21185 (-6.50637, 1.64224, 4.87005)
Sirius (-1.60906, 8.06202, -2.46895)
BL Ceti (7.54093, 3.47728, -2.69018)
Ross 154 (1.91024, -8.64808, -3.91287)
Ross 248 (7.38061, -0.583729, 7.19346)
epsilon Eridani (6.21307, 8.31501, -1.72923)
Lacaille 9352 (8.46565, -2.03763, -6.29226)
Ross 128 (-10.9032, 0.583818, -0.153313)
EZ Aquarii A (10.1892, -3.7814, -2.97361)
Procyon (-4.76796, 10.3068, 1.03849)
61 Cygni A (6.47533, -6.0968, 7.13794)
(no common name) (1.08144, -5.72632, 9.94485)
GX Andromedae (8.33256, 0.669751, 8.07912)
epsilon Indi A (5.65677, -3.15623, -9.89375)
DX Cancri (-6.42159, 8.38202, 5.32847)
tau Ceti (10.2728, 5.01418, -3.26436)
Henry et al. 1997, Henry et al. 2006 (5.02666, 6.91829, -8.40731)
YZ Ceti (11.0276, 3.61023, -3.5473)
Luyten's Star (-4.58412, 11.431, 1.12643)
Henry et al. 2006 (8.72279, 8.20666, 3.63449)
Henry et al. 2006 (1.07874, -5.4123, -11.2968)
Kapteyn's Star (1.89052, 8.83291, -9.03874)
AX Microscopii (7.59934, -6.53329, -8.07708)
Kruger 60 A (6.46881, -2.74612, 11.1147)
Jao et al. 2005, Costa et al. 2005 (-9.60648, 3.10998, -8.45318)
Ross 614 A (-1.70526, 13.2247, -0.655389)
Wolf 1061 (-5.14419, -12.4656, -3.02977)
van Maanen's Star (13.6844, 2.9815, 1.3211)
(no common name) (11.3095, 0.266851, -8.63585)
Wolf 424 A (-13.9874, -2.04595, 2.24423)
TZ Arietis (12.2352, 7.07964, 3.27708)
(no common name) (-0.560574, -5.43191, 13.7496)
(no common name) (-13.8117, 4.4737, -2.91082)
(no common name) (-1.37941, -10.026, -10.8132)
G 208-044 A (5.04504, -9.30115, 10.3675)
WD 1142-645 (-6.39085, 0.398859, -13.6332)
(no common name) (15.1756, 0.445762, -2.0094)
Ross 780 (14.2453, -4.26849, -3.78053)
Henry et al. 2006 (-7.11261, 2.43681, -13.6817)
(no common name) (-11.1567, 2.70545, 10.9043)
(no common name) (-9.16721, 4.7028, 12.0439)
(no common name) (-13.5785, 6.36013, 5.41878)
(no common name) (8.47021, -6.29244, -12.1422)
(no common name) (7.58939, 10.7973, -9.38886)
Costa et al. 2005 (7.97626, 7.63972, -11.85)
(no common name) (-1.16803, -11.6311, -11.415)
omicron 2 Eridani (7.16813, 14.5791, -2.18291)
EV Lacertae (11.1863, -3.69797, 11.5109)
70 Ophiuchi A (0.395798, -16.6257, 0.726099)
Altair (7.68313, -14.6368, 2.57929)
EI Cancri (-11.2661, 11.4397, 5.76843)
Henry et al. 2006 (-0.00434369, 17.0657, 0.80679)
Henry et al. 2006 (4.31746, 16.6814, -2.09934)
(no common name) (-3.4371, 0.184793, 17.2119)
Wolf 498 (-15.3243, -7.61788, 4.55075)
(no common name) (11.7114, -12.4986, -5.22833)
Stein 2051 (3.51678, 8.61724, 15.4759)
(no common name) (-3.59809, 14.7553, 9.96432)
(no common name) (2.40017, -15.3133, 10.0653)
Wolf 1453 (2.30849, 18.4396, -1.19433)
(no common name) (8.13711, 16.5581, -3.11497)
sigma Draconis (2.56145, -6.00814, 17.6198)
(no common name) (-0.806496, 17.4633, -7.0152)
(no common name) (-0.60082, -10.2413, -15.9916)
Wolf 1055 (6.25711, -17.9373, 1.71849)
Ross 47 (1.45407, 18.6368, 4.14063)
(no common name) (-12.7815, -12.502, -7.01238)
Jao et al. 2005 (4.66587, -12.6815, -13.7781)
(no common name) (19.3195, -0.910379, 0.811)
eta Cassiopei A (10.083, 2.19407, 16.3959)
(no common name) (-8.7523, -11.6374, -12.7814)
(no common name) (18.6028, 1.25748, -5.39363)
Ross 882 (-8.5697, 17.4409, 1.20642)
36 Ophiuchi A (-3.3708, -17.0825, -8.72026)
(no common name) (8.6356, -13.4, -11.6253)
82 Eridani (9.28626, 11.0597, -13.4997)
(no common name) (-0.336453, -6.48031, 18.7125)
delta Pavonis (4.28382, -6.80742, -18.2207)
QY Aurigae A (-4.71164, 14.9366, 12.4713)
HN Librae (-15.2876, -12.1909, -4.34181)
(no common name) (-14.1725, 10.1497, 9.86927)
(no common name) (-9.14765, 8.06616, 16.0018)
(no common name) (7.87021, -11.903, -14.3515)
Wolf 562 (-13.0814, -15.5135, -2.75169)
EQ Pegasi (19.2964, -2.38041, 7.05244)
Henry et al. 2006 (-13.6723, 13.6255, 7.73403)
Henry et al. 2006 (-16.0764, -2.74932, -12.9185)
(no common name) (-3.02379, -14.2661, 14.926)
(no common name) (-13.1994, -12.8181, -9.85069)
(no common name) (-5.96815, -14.644, 13.6811)
WD 0552-041 (0.443079, 20.9847, -1.53083)
Wolf 630 A (-5.78606, -20.007, -3.05182)
(no common name) (11.2897, -2.3337, 17.8668)
Jao et al. 2005 (-6.34222, 4.32745, -19.8823)
GL Virginis (-20.8614, -1.7339, 4.11654)
(no common name) (-5.02956, -11.4863, 17.4528)
Ross 104 (-19.3406, 5.17583, 8.42975)


*
*


*      *        *
*          *        *
*    *                               *           *

*   *             *
*  *     *
*                                                *
*
*        *                        * ?   *      *
* *                                    **     *
*                            *                        *
*
* *              ?               ?       *       *
*          *     *?*        S                            *
*                                        *   *
*              *                        *               *
*
*     *   *                      *               *
*                        *
*     *                          *
* * *        **      *   *    ?      *    *         *
*    *
*         * *  *
*              * *    *
*
*           *
*


*     *
*
Press any key to continue . . .


------------------Run 2: x-z map------------------
nearest_stars.txt
100
Proxima Centauri (-1.54629, -1.18348, -3.76934)
Barnard's Star (-0.056838, -5.94339, 0.487961)
Wolf 359 (-7.43033, 2.11355, 0.950536)
Lalande 21185 (-6.50637, 1.64224, 4.87005)
Sirius (-1.60906, 8.06202, -2.46895)
BL Ceti (7.54093, 3.47728, -2.69018)
Ross 154 (1.91024, -8.64808, -3.91287)
Ross 248 (7.38061, -0.583729, 7.19346)
epsilon Eridani (6.21307, 8.31501, -1.72923)
Lacaille 9352 (8.46565, -2.03763, -6.29226)
Ross 128 (-10.9032, 0.583818, -0.153313)
EZ Aquarii A (10.1892, -3.7814, -2.97361)
Procyon (-4.76796, 10.3068, 1.03849)
61 Cygni A (6.47533, -6.0968, 7.13794)
(no common name) (1.08144, -5.72632, 9.94485)
GX Andromedae (8.33256, 0.669751, 8.07912)
epsilon Indi A (5.65677, -3.15623, -9.89375)
DX Cancri (-6.42159, 8.38202, 5.32847)
tau Ceti (10.2728, 5.01418, -3.26436)
Henry et al. 1997, Henry et al. 2006 (5.02666, 6.91829, -8.40731)
YZ Ceti (11.0276, 3.61023, -3.5473)
Luyten's Star (-4.58412, 11.431, 1.12643)
Henry et al. 2006 (8.72279, 8.20666, 3.63449)
Henry et al. 2006 (1.07874, -5.4123, -11.2968)
Kapteyn's Star (1.89052, 8.83291, -9.03874)
AX Microscopii (7.59934, -6.53329, -8.07708)
Kruger 60 A (6.46881, -2.74612, 11.1147)
Jao et al. 2005, Costa et al. 2005 (-9.60648, 3.10998, -8.45318)
Ross 614 A (-1.70526, 13.2247, -0.655389)
Wolf 1061 (-5.14419, -12.4656, -3.02977)
van Maanen's Star (13.6844, 2.9815, 1.3211)
(no common name) (11.3095, 0.266851, -8.63585)
Wolf 424 A (-13.9874, -2.04595, 2.24423)
TZ Arietis (12.2352, 7.07964, 3.27708)
(no common name) (-0.560574, -5.43191, 13.7496)
(no common name) (-13.8117, 4.4737, -2.91082)
(no common name) (-1.37941, -10.026, -10.8132)
G 208-044 A (5.04504, -9.30115, 10.3675)
WD 1142-645 (-6.39085, 0.398859, -13.6332)
(no common name) (15.1756, 0.445762, -2.0094)
Ross 780 (14.2453, -4.26849, -3.78053)
Henry et al. 2006 (-7.11261, 2.43681, -13.6817)
(no common name) (-11.1567, 2.70545, 10.9043)
(no common name) (-9.16721, 4.7028, 12.0439)
(no common name) (-13.5785, 6.36013, 5.41878)
(no common name) (8.47021, -6.29244, -12.1422)
(no common name) (7.58939, 10.7973, -9.38886)
Costa et al. 2005 (7.97626, 7.63972, -11.85)
(no common name) (-1.16803, -11.6311, -11.415)
omicron 2 Eridani (7.16813, 14.5791, -2.18291)
EV Lacertae (11.1863, -3.69797, 11.5109)
70 Ophiuchi A (0.395798, -16.6257, 0.726099)
Altair (7.68313, -14.6368, 2.57929)
EI Cancri (-11.2661, 11.4397, 5.76843)
Henry et al. 2006 (-0.00434369, 17.0657, 0.80679)
Henry et al. 2006 (4.31746, 16.6814, -2.09934)
(no common name) (-3.4371, 0.184793, 17.2119)
Wolf 498 (-15.3243, -7.61788, 4.55075)
(no common name) (11.7114, -12.4986, -5.22833)
Stein 2051 (3.51678, 8.61724, 15.4759)
(no common name) (-3.59809, 14.7553, 9.96432)
(no common name) (2.40017, -15.3133, 10.0653)
Wolf 1453 (2.30849, 18.4396, -1.19433)
(no common name) (8.13711, 16.5581, -3.11497)
sigma Draconis (2.56145, -6.00814, 17.6198)
(no common name) (-0.806496, 17.4633, -7.0152)
(no common name) (-0.60082, -10.2413, -15.9916)
Wolf 1055 (6.25711, -17.9373, 1.71849)
Ross 47 (1.45407, 18.6368, 4.14063)
(no common name) (-12.7815, -12.502, -7.01238)
Jao et al. 2005 (4.66587, -12.6815, -13.7781)
(no common name) (19.3195, -0.910379, 0.811)
eta Cassiopei A (10.083, 2.19407, 16.3959)
(no common name) (-8.7523, -11.6374, -12.7814)
(no common name) (18.6028, 1.25748, -5.39363)
Ross 882 (-8.5697, 17.4409, 1.20642)
36 Ophiuchi A (-3.3708, -17.0825, -8.72026)
(no common name) (8.6356, -13.4, -11.6253)
82 Eridani (9.28626, 11.0597, -13.4997)
(no common name) (-0.336453, -6.48031, 18.7125)
delta Pavonis (4.28382, -6.80742, -18.2207)
QY Aurigae A (-4.71164, 14.9366, 12.4713)
HN Librae (-15.2876, -12.1909, -4.34181)
(no common name) (-14.1725, 10.1497, 9.86927)
(no common name) (-9.14765, 8.06616, 16.0018)
(no common name) (7.87021, -11.903, -14.3515)
Wolf 562 (-13.0814, -15.5135, -2.75169)
EQ Pegasi (19.2964, -2.38041, 7.05244)
Henry et al. 2006 (-13.6723, 13.6255, 7.73403)
Henry et al. 2006 (-16.0764, -2.74932, -12.9185)
(no common name) (-3.02379, -14.2661, 14.926)
(no common name) (-13.1994, -12.8181, -9.85069)
(no common name) (-5.96815, -14.644, 13.6811)
WD 0552-041 (0.443079, 20.9847, -1.53083)
Wolf 630 A (-5.78606, -20.007, -3.05182)
(no common name) (11.2897, -2.3337, 17.8668)
Jao et al. 2005 (-6.34222, 4.32745, -19.8823)
GL Virginis (-20.8614, -1.7339, 4.11654)
(no common name) (-5.02956, -11.4863, 17.4528)
Ross 104 (-19.3406, 5.17583, 8.42975)


*
*


*              *               *
*        *             *
*     *      *              *   *

*         *         *
*                                    *      *
*                        *
*                         ?
*          *                  *             ?*              *
*      *                   *        *
*                                 *            *
*
**      *    ?  ?  *
*                            S*                       *        *
*                *         *          *
*            *                   *             *
*
*       *         *          *                      *
*                           *
*                *      *
*   **   *  *  *    *?         *        *
*                              *
**                                 *
*     *                             *          *
*
*        *
*


*                      *
*
Press any key to continue . . .


------------------Run 3: y-z map------------------
nearest_stars.txt
100
Proxima Centauri (-1.54629, -1.18348, -3.76934)
Barnard's Star (-0.056838, -5.94339, 0.487961)
Wolf 359 (-7.43033, 2.11355, 0.950536)
Lalande 21185 (-6.50637, 1.64224, 4.87005)
Sirius (-1.60906, 8.06202, -2.46895)
BL Ceti (7.54093, 3.47728, -2.69018)
Ross 154 (1.91024, -8.64808, -3.91287)
Ross 248 (7.38061, -0.583729, 7.19346)
epsilon Eridani (6.21307, 8.31501, -1.72923)
Lacaille 9352 (8.46565, -2.03763, -6.29226)
Ross 128 (-10.9032, 0.583818, -0.153313)
EZ Aquarii A (10.1892, -3.7814, -2.97361)
Procyon (-4.76796, 10.3068, 1.03849)
61 Cygni A (6.47533, -6.0968, 7.13794)
(no common name) (1.08144, -5.72632, 9.94485)
GX Andromedae (8.33256, 0.669751, 8.07912)
epsilon Indi A (5.65677, -3.15623, -9.89375)
DX Cancri (-6.42159, 8.38202, 5.32847)
tau Ceti (10.2728, 5.01418, -3.26436)
Henry et al. 1997, Henry et al. 2006 (5.02666, 6.91829, -8.40731)
YZ Ceti (11.0276, 3.61023, -3.5473)
Luyten's Star (-4.58412, 11.431, 1.12643)
Henry et al. 2006 (8.72279, 8.20666, 3.63449)
Henry et al. 2006 (1.07874, -5.4123, -11.2968)
Kapteyn's Star (1.89052, 8.83291, -9.03874)
AX Microscopii (7.59934, -6.53329, -8.07708)
Kruger 60 A (6.46881, -2.74612, 11.1147)
Jao et al. 2005, Costa et al. 2005 (-9.60648, 3.10998, -8.45318)
Ross 614 A (-1.70526, 13.2247, -0.655389)
Wolf 1061 (-5.14419, -12.4656, -3.02977)
van Maanen's Star (13.6844, 2.9815, 1.3211)
(no common name) (11.3095, 0.266851, -8.63585)
Wolf 424 A (-13.9874, -2.04595, 2.24423)
TZ Arietis (12.2352, 7.07964, 3.27708)
(no common name) (-0.560574, -5.43191, 13.7496)
(no common name) (-13.8117, 4.4737, -2.91082)
(no common name) (-1.37941, -10.026, -10.8132)
G 208-044 A (5.04504, -9.30115, 10.3675)
WD 1142-645 (-6.39085, 0.398859, -13.6332)
(no common name) (15.1756, 0.445762, -2.0094)
Ross 780 (14.2453, -4.26849, -3.78053)
Henry et al. 2006 (-7.11261, 2.43681, -13.6817)
(no common name) (-11.1567, 2.70545, 10.9043)
(no common name) (-9.16721, 4.7028, 12.0439)
(no common name) (-13.5785, 6.36013, 5.41878)
(no common name) (8.47021, -6.29244, -12.1422)
(no common name) (7.58939, 10.7973, -9.38886)
Costa et al. 2005 (7.97626, 7.63972, -11.85)
(no common name) (-1.16803, -11.6311, -11.415)
omicron 2 Eridani (7.16813, 14.5791, -2.18291)
EV Lacertae (11.1863, -3.69797, 11.5109)
70 Ophiuchi A (0.395798, -16.6257, 0.726099)
Altair (7.68313, -14.6368, 2.57929)
EI Cancri (-11.2661, 11.4397, 5.76843)
Henry et al. 2006 (-0.00434369, 17.0657, 0.80679)
Henry et al. 2006 (4.31746, 16.6814, -2.09934)
(no common name) (-3.4371, 0.184793, 17.2119)
Wolf 498 (-15.3243, -7.61788, 4.55075)
(no common name) (11.7114, -12.4986, -5.22833)
Stein 2051 (3.51678, 8.61724, 15.4759)
(no common name) (-3.59809, 14.7553, 9.96432)
(no common name) (2.40017, -15.3133, 10.0653)
Wolf 1453 (2.30849, 18.4396, -1.19433)
(no common name) (8.13711, 16.5581, -3.11497)
sigma Draconis (2.56145, -6.00814, 17.6198)
(no common name) (-0.806496, 17.4633, -7.0152)
(no common name) (-0.60082, -10.2413, -15.9916)
Wolf 1055 (6.25711, -17.9373, 1.71849)
Ross 47 (1.45407, 18.6368, 4.14063)
(no common name) (-12.7815, -12.502, -7.01238)
Jao et al. 2005 (4.66587, -12.6815, -13.7781)
(no common name) (19.3195, -0.910379, 0.811)
eta Cassiopei A (10.083, 2.19407, 16.3959)
(no common name) (-8.7523, -11.6374, -12.7814)
(no common name) (18.6028, 1.25748, -5.39363)
Ross 882 (-8.5697, 17.4409, 1.20642)
36 Ophiuchi A (-3.3708, -17.0825, -8.72026)
(no common name) (8.6356, -13.4, -11.6253)
82 Eridani (9.28626, 11.0597, -13.4997)
(no common name) (-0.336453, -6.48031, 18.7125)
delta Pavonis (4.28382, -6.80742, -18.2207)
QY Aurigae A (-4.71164, 14.9366, 12.4713)
HN Librae (-15.2876, -12.1909, -4.34181)
(no common name) (-14.1725, 10.1497, 9.86927)
(no common name) (-9.14765, 8.06616, 16.0018)
(no common name) (7.87021, -11.903, -14.3515)
Wolf 562 (-13.0814, -15.5135, -2.75169)
EQ Pegasi (19.2964, -2.38041, 7.05244)
Henry et al. 2006 (-13.6723, 13.6255, 7.73403)
Henry et al. 2006 (-16.0764, -2.74932, -12.9185)
(no common name) (-3.02379, -14.2661, 14.926)
(no common name) (-13.1994, -12.8181, -9.85069)
(no common name) (-5.96815, -14.644, 13.6811)
WD 0552-041 (0.443079, 20.9847, -1.53083)
Wolf 630 A (-5.78606, -20.007, -3.05182)
(no common name) (11.2897, -2.3337, 17.8668)
Jao et al. 2005 (-6.34222, 4.32745, -19.8823)
GL Virginis (-20.8614, -1.7339, 4.11654)
(no common name) (-5.02956, -11.4863, 17.4528)
Ross 104 (-19.3406, 5.17583, 8.42975)


*
*
*                *
*                      *
*                   * *
*  *
** *  *       *  **  *
*
*         *                                     *

*                                        *
*       *              ?           *    *             * *
*                                            *
*          * *                         *
*           *              *        *      *           *
?       *     *
*        *          *   S                            *
*         *        ?    *
*                         ?                 *        *
*        *?      *
*                            **                   *      *
*
*     *                    *
*           ?                 *  *                 **

*      *                  *               *
*       *
*              *
*                     *   *

* *    *
*         *   *
*

*
Press any key to continue . . .

*/


/* ANSWER KEY:
// Bonus Assignment: SNE_Analyzer
// CS 2C, Foothill College, Michael Loceff, creator

#include <iostream>
using namespace std;

#include "StarNearEarth.h"
#include "FHsparseMat.h"
#include <cmath>

class SNE_Analyzer: public StarNearEarth
{
private:
double x, y, z;

public:
void calcCartCoords();
double getX() { return x; }
double getY() { return y; }
double getZ() { return z; }
string coordToString();
SNE_Analyzer & operator=( const StarNearEarth &sne );
};

void SNE_Analyzer::calcCartCoords()
{
double lyDist, raRadians, decRadians;
const double PI = 3.1415927;

lyDist = 3.262 / getParallaxMean();
raRadians = getRAsc() * PI/180;
decRadians = getDec() * PI/180;

x = lyDist * cos(decRadians) * cos(raRadians);
y = lyDist * cos(decRadians) * sin(raRadians);
z = lyDist * sin(decRadians);
}

string SNE_Analyzer::coordToString()
{
ostringstream os;
os.precision(2);
os.setf(ios::fixed);

os << "(" << x << ", " << y << ", " << z << ")";
return os.str();
}

SNE_Analyzer & SNE_Analyzer::operator=( const StarNearEarth &sne )
{

setRank(sne.getRank());
setNameCns(sne.getNameCns());
setNumComponents(sne.getNumComponents());
setNameLhs(sne.getNameLhs());
setRAsc(sne.getRAsc());
setDec(sne.getDec());
setPropMotionMag(sne.getPropMotionMag());
setPropMotionDir(sne.getPropMotionDir());
setParallaxMean(sne.getParallaxMean());
setParallaxVariance(sne.getParallaxVariance());
setWhiteDwarfFlag(sne.getWhiteDwarfFlag());
setSpectralType(sne.getSpectralType());
setMagApparent(sne.getMagApparent());
setMagAbsolute(sne.getMagAbsolute());
setMass(sne.getMass());
setNotes(sne.getNotes());
setNameCommon(sne.getNameCommon());
calcCartCoords();

return *this;
}



// --------------- main ---------------
int main()
{
string outString, longBlankString
= "                                         "
"                                         ";
int k, arraySize, row, col;
double maxX, minX, maxY, minY, maxZ, minZ,
xRange, yRange, zRange,
xConversion, yConversion, zConversion;
StarNearEarthReader starInput("nearest_stars.txt");
const int NUM_COLS = 70;
const int NUM_ROWS = 35;

if (starInput.readError())
{
cout << "couldn't open " << starInput.getFileName() << " for input.\n";
exit(1);
}

cout << starInput.getFileName() << endl;
cout << starInput.getNumStars() << endl;

// create an array of objects for our own use:
arraySize = starInput.getNumStars();
SNE_Analyzer *starArray = new SNE_Analyzer[arraySize];
for (k = 0; k < arraySize; k++)
starArray[k] =  starInput[k];

// display cartesian coords
for (int k = 0; k < arraySize; k++)
cout << starArray[k].getNameCommon() << " "
<< starArray[k].coordToString() << endl;

// get max and min coords for scaling
maxX = minX = maxY = minY = maxZ = minZ = 0;
for (int k = 0; k < arraySize; k++)
{
if ( starArray[k].getX() > maxX )
maxX = starArray[k].getX();
else if ( starArray[k].getX() < minX )
minX = starArray[k].getX();
if ( starArray[k].getY() > maxY )
maxY = starArray[k].getY();
else if ( starArray[k].getY() < minY )
minY = starArray[k].getY();
if ( starArray[k].getZ() > maxZ )
maxZ = starArray[k].getZ();
else if ( starArray[k].getZ() < minZ )
minZ = starArray[k].getZ();
}
xRange = maxX - minX;
yRange = maxY - minY;
zRange = maxZ - minZ;

// form 50 x 25 grid for display: x-y projection
// xConversion = NUM_ROWS / xRange;
// xConversion = NUM_COLS / xRange;
// yConversion = NUM_COLS / yRange;
yConversion = NUM_ROWS / yRange;
zConversion = NUM_COLS / zRange;
// zConversion = NUM_ROWS / zRange;

SparseMat<char> starMap(NUM_ROWS, NUM_COLS, ' ');

for (k = 0; k < arraySize; k++)
{
// row = (int) (starArray[k].getX() - minX )* xConversion;
// col = (int) (starArray[k].getX() - minX )* xConversion;
// col = (int) (starArray[k].getY() - minY) * yConversion;
row = (int) (starArray[k].getY() - minY) * yConversion;
col = (int) (starArray[k].getZ() - minZ) * zConversion;
// row = (int) (starArray[k].getZ() - minZ) * zConversion;

if (starArray[k].getRank() < 10)
starMap.set(row, col) = '0' + starArray[k].getRank();
else
starMap.set(row, col) = '*';
}

// set sun at center
// row = (int) (0 - minX )* xConversion;
// col = (int) (0 - minX )* xConversion;
// col = (int)  (0 - minY) * yConversion;
row = (int)  (0 - minY) * yConversion;
col = (int)  (0 - minZ) * zConversion;
// row = (int)  (0 - minZ) * zConversion;
starMap.set( row, col) = 'S';

for (row = 0; row < NUM_ROWS; row++)
{
outString = longBlankString.substr(0, NUM_COLS);
for (col = 0; col < NUM_COLS; col++)
outString[col] = starMap.get(row, col);
cout << outString << endl;
}

delete[] starArray;

return 0;
}



--------------- Run ----------------
nearest_stars.txt
100
Proxima Centauri (-1.55, -1.18, -3.77)
Barnard's Star (-0.06, -5.94, 0.49)
Wolf 359 (-7.43, 2.11, 0.95)
Lalande 21185 (-6.51, 1.64, 4.87)
Sirius (-1.61, 8.06, -2.47)
BL Ceti (7.54, 3.48, -2.69)
Ross 154 (1.91, -8.65, -3.91)
Ross 248 (7.38, -0.58, 7.19)
epsilon Eridani (6.21, 8.32, -1.73)
Lacaille 9352 (8.47, -2.04, -6.29)
Ross 128 (-10.90, 0.58, -0.15)
EZ Aquarii A (10.19, -3.78, -2.97)
Procyon (-4.77, 10.31, 1.04)
61 Cygni A (6.48, -6.10, 7.14)
(no common name) (1.08, -5.73, 9.94)
GX Andromedae (8.33, 0.67, 8.08)
epsilon Indi A (5.66, -3.16, -9.89)
DX Cancri (-6.42, 8.38, 5.33)
tau Ceti (10.27, 5.01, -3.26)
Henry et al. 1997, Henry et al. 2006 (5.03, 6.92, -8.41)
YZ Ceti (11.03, 3.61, -3.55)
Luyten's Star (-4.58, 11.43, 1.13)
Henry et al. 2006 (8.72, 8.21, 3.63)
Henry et al. 2006 (1.08, -5.41, -11.30)
Kapteyn's Star (1.89, 8.83, -9.04)
AX Microscopii (7.60, -6.53, -8.08)
Kruger 60 A (6.47, -2.75, 11.11)
Jao et al. 2005, Costa et al. 2005 (-9.61, 3.11, -8.45)
Ross 614 A (-1.71, 13.22, -0.66)
Wolf 1061 (-5.14, -12.47, -3.03)
van Maanen's Star (13.68, 2.98, 1.32)
(no common name) (11.31, 0.27, -8.64)
Wolf 424 A (-13.99, -2.05, 2.24)
TZ Arietis (12.24, 7.08, 3.28)
(no common name) (-0.56, -5.43, 13.75)
(no common name) (-13.81, 4.47, -2.91)
(no common name) (-1.38, -10.03, -10.81)
G 208-044 A (5.05, -9.30, 10.37)
WD 1142-645 (-6.39, 0.40, -13.63)
(no common name) (15.18, 0.45, -2.01)
Ross 780 (14.25, -4.27, -3.78)
Henry et al. 2006 (-7.11, 2.44, -13.68)
(no common name) (-11.16, 2.71, 10.90)
(no common name) (-9.17, 4.70, 12.04)
(no common name) (-13.58, 6.36, 5.42)
(no common name) (8.47, -6.29, -12.14)
(no common name) (7.59, 10.80, -9.39)
Costa et al. 2005 (7.98, 7.64, -11.85)
(no common name) (-1.17, -11.63, -11.42)
omicron 2 Eridani (7.17, 14.58, -2.18)
EV Lacertae (11.19, -3.70, 11.51)
70 Ophiuchi A (0.40, -16.63, 0.73)
Altair (7.68, -14.64, 2.58)
EI Cancri (-11.27, 11.44, 5.77)
Henry et al. 2006 (-0.00, 17.07, 0.81)
Henry et al. 2006 (4.32, 16.68, -2.10)
(no common name) (-3.44, 0.18, 17.21)
Wolf 498 (-15.32, -7.62, 4.55)
(no common name) (11.71, -12.50, -5.23)
Stein 2051 (3.52, 8.62, 15.48)
(no common name) (-3.60, 14.76, 9.96)
(no common name) (2.40, -15.31, 10.07)
Wolf 1453 (2.31, 18.44, -1.19)
(no common name) (8.14, 16.56, -3.11)
sigma Draconis (2.56, -6.01, 17.62)
(no common name) (-0.81, 17.46, -7.02)
(no common name) (-0.60, -10.24, -15.99)
Wolf 1055 (6.26, -17.94, 1.72)
Ross 47 (1.45, 18.64, 4.14)
(no common name) (-12.78, -12.50, -7.01)
Jao et al. 2005 (4.67, -12.68, -13.78)
(no common name) (19.32, -0.91, 0.81)
eta Cassiopei A (10.08, 2.19, 16.40)
(no common name) (-8.75, -11.64, -12.78)
(no common name) (18.60, 1.26, -5.39)
Ross 882 (-8.57, 17.44, 1.21)
36 Ophiuchi A (-3.37, -17.08, -8.72)
(no common name) (8.64, -13.40, -11.63)
82 Eridani (9.29, 11.06, -13.50)
(no common name) (-0.34, -6.48, 18.71)
delta Pavonis (4.28, -6.81, -18.22)
QY Aurigae A (-4.71, 14.94, 12.47)
HN Librae (-15.29, -12.19, -4.34)
(no common name) (-14.17, 10.15, 9.87)
(no common name) (-9.15, 8.07, 16.00)
(no common name) (7.87, -11.90, -14.35)
Wolf 562 (-13.08, -15.51, -2.75)
EQ Pegasi (19.30, -2.38, 7.05)
Henry et al. 2006 (-13.67, 13.63, 7.73)
Henry et al. 2006 (-16.08, -2.75, -12.92)
(no common name) (-3.02, -14.27, 14.93)
(no common name) (-13.20, -12.82, -9.85)
(no common name) (-5.97, -14.64, 13.68)
WD 0552-041 (0.44, 20.98, -1.53)
Wolf 630 A (-5.79, -20.01, -3.05)
(no common name) (11.29, -2.33, 17.87)
Jao et al. 2005 (-6.34, 4.33, -19.88)
GL Virginis (-20.86, -1.73, 4.12)
(no common name) (-5.03, -11.49, 17.45)
Ross 104 (-19.34, 5.18, 8.43)



[XY Plane:]
*           *


*
*        *
*                     *
*    *                            *   *           *
*  *              *

**      *
*                                                 *
*
*                         *4    *      *
*          * *                                     **     *
*    *                         *                       *

* *              1                5        *
*      **          S                            *
*                 *                                            *
7                            *                *
*               *                        *                *
*     *    *                     *                *
*
*                  *      *                 9
*    *        *         8      6      *    *      *  *
*           *      *    *            *
*              *
*               * *    *    *  *
*
*
*
*

*
*  *



[YZ Plane:]
*
*                  *
*
*                     *
*                   * *
*   *   *  *   * * *
*  * *                                                    *
*          *
*
7
*
*          * *    *                2           *   *      *       **
*
*            *                          *
*            *               *       *      *            *
1           *
*           8
*        *     *    *   S        4    *                  *
*                         3 *               *          *
*         *6
*                            *                          *
*                    *
*                         *
*   *           5 9        *   *                 *

*                 *               *
*                           *      *

*             *
*                     *     *
**
*              * *
*          *

*
Press any key to continue . . .
----------------------------------------------------------- */
