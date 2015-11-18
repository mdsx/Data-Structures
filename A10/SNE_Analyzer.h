#ifndef SNE_ANALYZER_H
#define SNE_ANALYZER_H

#include "StarNearEarth.h"
#include <cmath>
#include <string>
using namespace std;

// ---------------------- SNE_Analyzer Prototype ------------------------------
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

// SNE_Analyzer method definitions -------------------

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

#endif