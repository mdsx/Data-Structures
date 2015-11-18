// File StarNearEarth.h
// Interface for classes
//   StarNearEarth - Single star object from the RECONS database
//   StarNearEarthReader - Used to read and return StarNearEarth objects
// Author: Michael Loceff c 2009

#ifndef StarNearEarth_H
#define StarNearEarth_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class StarNearEarth
{
public:
   static const unsigned int MIN_STRING = 0;
   static const unsigned int MAX_STRING = 100;
   static const int MIN_DUB = -1000;
   static const int MAX_DUB = 1000;
private:
   string nameCns, spectralType, notes,  nameCommon;
   int rank, nameLhs, numComponents;
   double rAsc, decl,  propMotionMag, propMotionDir, parallaxMean, 
      parallaxVariance, magApparent, magAbsolute, mass;
   bool whiteDwarfFlag;

public:
   StarNearEarth();

   //mutators
   bool setNameCns(string strArg);
   bool setSpectralType(string strArg);
   bool setNotes(string strArg);
   bool setNameCommon(string strArg);

   bool setRank(int intArg);
   bool setNameLhs(int intArg);
   bool setNumComponents(int intArg);

   bool setRAsc(double dblArg);
   bool setDec(double dblArg);
   bool setPropMotionMag(double dblArg);
   bool setPropMotionDir(double dblArg);
   bool setParallaxMean(double dblArg);
   bool setParallaxVariance(double dblArg);
   bool setMagApparent(double dblArg);
   bool setMagAbsolute(double dblArg);
   bool setMass(double dblArg);

   void setWhiteDwarfFlag(bool boolArg);

   // accessors
   string getNameCns() const { return nameCns; }
   string getSpectralType() const { return spectralType; }
   string getNotes() const { return notes; }
   string getNameCommon() const { return nameCommon; }

   int getRank() const { return rank; }
   int getNameLhs() const { return nameLhs; }
   int getNumComponents() const { return numComponents; }

   double getRAsc() const { return rAsc; }
   double getDec() const { return decl; }
   double getPropMotionMag() const { return propMotionMag; }
   double getPropMotionDir() const { return propMotionDir; }
   double getParallaxMean() const { return parallaxMean; }
   double getParallaxVariance() const { return parallaxVariance; }
   double getMagApparent() const { return magApparent; }
   double getMagAbsolute() const { return magAbsolute; }
   double getMass() const { return mass; }
   bool getWhiteDwarfFlag() const { return whiteDwarfFlag; }

   // comparator tools
   // could use static const int, instead:
private:
   static int sortKey;

public:
   enum 
   {
      SORT_BY_NAME_CNS, SORT_BY_SPECTRAL_TYPE, SORT_BY_NAME_COMMON, SORT_BY_RANK,
      SORT_BY_NAME_LHS, SORT_BY_NUM_COMPONENTS, SORT_BY_RA, SORT_BY_DEC, SORT_BY_PROP_MOTION_MAG,
      SORT_BY_PROP_MOTION_DIR, SORT_BY_PARALLAX_MEAN, SORT_BY_PARALLAX_VARIANCE, 
      SORT_BY_MAG_APPARENT, SORT_BY_MAG_ABSOLUTE, SORT_BY_MASS
   };
   static bool setSortType( int whichType );
   bool operator<(const StarNearEarth &other) const;
   bool operator>(const StarNearEarth &other) const;
   bool operator==(const StarNearEarth &other) const;
   bool operator!=(const StarNearEarth &other) const;};

class StarNearEarthReader
{
private:
   vector <StarNearEarth> stars;
   int numStars;
   bool fileOpenError;
   string starFile;
   StarNearEarth readOneStar(string line);
   bool isDataLine(int line_num, string line);


public:
   StarNearEarthReader(string fileName);
   StarNearEarth &operator[](int k);
   string getFileName() { return starFile; }
   bool readError() { return fileOpenError; }
   int getNumStars() { return numStars; }

   // static utilities for converting strings and RA/DEC to single floats
   static double convertRA(string strRA);   // "HH MM SS.S" -> double
   static double convertDEC(string strDMS); // "DDD MM SS.S" -> double
   static double convertToDouble(string strToCnvrt);

private:
   static double dmsToFloatDegree(int deg, int min, double sec);
   static double hmsToFloatDegree(int hr, int min, double sec);
};

StarNearEarth StarNearEarthReader::readOneStar(string line)
{
   int endOfField;
   StarNearEarth star;

   // we show the end column by not pre-computing string length:  END_COL - START_COL + 1
   star.setRank((int)convertToDouble(line.substr(0, 3)));
   star.setNameCns(line.substr(5, 19 - 5 + 1));
   star.setNumComponents((int)convertToDouble(line.substr(20, 21 - 20 + 1)));
   star.setNameLhs((int)convertToDouble(line.substr(23, 28 - 23 + 1)));
   star.setRAsc(convertRA(line.substr(32, 41 - 32 + 1)));
   star.setDec(convertDEC(line.substr(43, 51 - 43 + 1)));
   star.setPropMotionMag(convertToDouble(line.substr(56, 61 - 56 + 1)));
   star.setPropMotionDir(convertToDouble(line.substr(63, 67 - 63 + 1)));
   star.setParallaxMean(convertToDouble(line.substr(73, 79 - 73 + 1)));
   star.setParallaxVariance(convertToDouble(line.substr(81, 87 - 81 + 1)));
   star.setWhiteDwarfFlag((line.substr(95, 1) == "D"));
   star.setSpectralType(line.substr(96, 104 - 96 + 1));
   star.setMagApparent(convertToDouble(line.substr(108, 112 - 108 + 1)));
   star.setMagAbsolute(convertToDouble(line.substr(116, 120 - 116 + 1)));
   star.setMass(convertToDouble(line.substr(123, 127 - 123 + 1)));

   if (line.length() < 132)
      star.setNotes("");
   else
   {
      endOfField = line.length() < 151 ? line.length() : 150;
      star.setNotes(line.substr(131, endOfField - 131));
   }

   if (line.length() < 153)
      star.setNameCommon("(no common name)");
   else
   {
      // logic to remove unwanted eol char from windows buffer
      string tempName;
      char lastChar;
      unsigned long lastPos;

      tempName = line.substr(152, line.length() - 152);

      lastPos = tempName.length() - 1;
      lastChar = tempName[lastPos];
      if (!isprint(lastChar))
         tempName = tempName.substr(0, lastPos);

      star.setNameCommon(tempName);
   }

   return star;
}

double StarNearEarthReader::convertToDouble(string strToCnvrt)
{
   double retDbl;

   istringstream(strToCnvrt) >> retDbl;
   return retDbl;
}

bool StarNearEarthReader::isDataLine(int line_num, string line)
{
   string s;
   if (line.length() < 4)
      return false;

   // check for a line of the form " k.  --- "
   ostringstream cnvrt;
   cnvrt << setw(3) << line_num << ".";
   s = cnvrt.str();

   if (line.substr(0, 4) == s)
      return true;
   return false;
}

StarNearEarth &StarNearEarthReader::operator[](int k)
{
   static StarNearEarth dummy_Return;
   if (k < 0 || k >= numStars)
      return dummy_Return;
   return stars[k];
}

StarNearEarthReader::StarNearEarthReader(string fileName)
{
   int k;
   string name;
   string line, s;
   StarNearEarth star;

   numStars = 0;
   fileOpenError = false;
   starFile = "NO FILE NAME PROVIDED";

   if (fileName.length() == 0)
   {
      fileOpenError = true;
      return;
   }
   starFile = fileName;

   // open file for reading
   ifstream infile(fileName.c_str());
   if (!infile)
   {
      fileOpenError = true;
      return;
   }

   // for each line that starts #. read and add to vector
   for (k = 1; !infile.eof();)
   {
      getline(infile, line);
      if (isDataLine(k, line))
      {
         star = readOneStar(line);
         stars.push_back(star);
         k++;
         numStars++;
      }
   }
   infile.close();
}

// static methods for converting strings and RA/DEC to single floats
double StarNearEarthReader::hmsToFloatDegree(int hr, int min, double sec)
{
   double retDbl;

   retDbl = hr + min / 60. + sec / 3600.;
   retDbl *= 15;
   return retDbl;
}

double StarNearEarthReader::dmsToFloatDegree(int deg, int min, double sec)
{
   double retDbl;
   bool sign = (deg > 0);

   retDbl = abs(deg) + min / 60. + sec / 3600.;
   return sign ? retDbl : -retDbl;
}

double StarNearEarthReader::convertRA(string strRA)
{
   int hr, min;
   double sec, ret_val;

   // cout << " [" << strRA << "] ";
   hr = (int)convertToDouble(strRA.substr(0, 3));
   min = (int)convertToDouble(strRA.substr(3, 3));
   sec = (double)convertToDouble(strRA.substr(6, 4));
   if (sec < 0 || sec > 60.001)  // sanity - for blank seconds
      sec = 0;
   ret_val = hmsToFloatDegree(hr, min, sec);
   return ret_val;
}

double StarNearEarthReader::convertDEC(string strDMS)
{
   int deg, min;
   double sec, ret_val;

   // cout << " [" << strDMS << "] ";
   deg = (int)convertToDouble(strDMS.substr(0, 3));
   min = (int)convertToDouble(strDMS.substr(3, 3));
   sec = (double)convertToDouble(strDMS.substr(6, 4));
   if (sec < 0 || sec > 60.001)  // sanity - for blank seconds
      sec = 0;
   ret_val = dmsToFloatDegree(deg, min, sec);
   return ret_val;
}
// StarNearEarth methods ---------------------------------------------------

// static int initialization
int StarNearEarth::sortKey = StarNearEarth::SORT_BY_RANK;

// default constructor
StarNearEarth::StarNearEarth()
   : nameCns(""), spectralType(""), notes(""), nameCommon(""),
   rank(0), nameLhs(0), numComponents(0),
   rAsc(0), decl(0), propMotionMag(0), propMotionDir(0),
   parallaxMean(0), parallaxVariance(0), magApparent(0), magAbsolute(0),
   mass(0), whiteDwarfFlag(false)
{
}

// mutators
bool StarNearEarth::setNameCns(string strArg)
{
   if (strArg.length() < MIN_STRING || strArg.length() > MAX_STRING)
      return false;
   nameCns = strArg;
   return true;
}
bool StarNearEarth::setSpectralType(string strArg)
{
   if (strArg.length() < MIN_STRING || strArg.length() > MAX_STRING)
      return false;
   spectralType = strArg;
   return true;
}
bool StarNearEarth::setNotes(string strArg)
{
   if (strArg.length() < MIN_STRING || strArg.length() > MAX_STRING)
      return false;
   notes = strArg;
   return true;
}
bool StarNearEarth::setNameCommon(string strArg)
{
   if (strArg.length() < MIN_STRING || strArg.length() > MAX_STRING)
      return false;
   nameCommon = strArg;
   return true;
}

bool StarNearEarth::setRank(int intArg)
{
   if (intArg < 1 || intArg > 999)
      return false;
   rank = intArg;
   return true;
}
bool StarNearEarth::setNameLhs(int intArg)
{
   if (intArg < 1 || intArg > 10000)
      return false;
   nameLhs = intArg;
   return true;
}
bool StarNearEarth::setNumComponents(int intArg)
{
   if (intArg < 1 || intArg > 10)
      return false;
   numComponents = intArg;
   return true;
}

bool StarNearEarth::setRAsc(double dblArg)
{
   if (dblArg < MIN_DUB || dblArg > MAX_DUB)
      return false;
   rAsc = dblArg;
   return true;
}
bool StarNearEarth::setDec(double dblArg)
{
   if (dblArg < MIN_DUB || dblArg > MAX_DUB)
      return false;
   decl = dblArg;
   return true;
}
bool StarNearEarth::setPropMotionMag(double dblArg)
{
   if (dblArg < MIN_DUB || dblArg > MAX_DUB)
      return false;
   propMotionMag = dblArg;
   return true;
}
bool StarNearEarth::setPropMotionDir(double dblArg)
{
   if (dblArg < MIN_DUB || dblArg > MAX_DUB)
      return false;
   propMotionDir = dblArg;
   return true;
}
bool StarNearEarth::setParallaxMean(double dblArg)
{
   if (dblArg < MIN_DUB || dblArg > MAX_DUB)
      return false;
   parallaxMean = dblArg;
   return true;
}
bool StarNearEarth::setParallaxVariance(double dblArg)
{
   if (dblArg < MIN_DUB || dblArg > MAX_DUB)
      return false;
   parallaxVariance = dblArg;
   return true;
}
bool StarNearEarth::setMagApparent(double dblArg)
{
   if (dblArg < -30 || dblArg > 30)
      return false;
   magApparent = dblArg;
   return true;
}
bool StarNearEarth::setMagAbsolute(double dblArg)
{
   if (dblArg < -30 || dblArg > 30)
      return false;
   magAbsolute = dblArg;
   return true;
}
bool StarNearEarth::setMass(double dblArg)
{
   if (mass < 0 || mass > 100)
      return false;
   mass = dblArg;
   return true;
}
void StarNearEarth::setWhiteDwarfFlag(bool boolArg)
{
   whiteDwarfFlag = boolArg;
}

bool StarNearEarth::setSortType(int whichType)
{
   switch (whichType)
   {
   case SORT_BY_NAME_CNS: case SORT_BY_SPECTRAL_TYPE: case SORT_BY_NAME_COMMON:
   case SORT_BY_RANK: case SORT_BY_NAME_LHS: case SORT_BY_NUM_COMPONENTS:
   case SORT_BY_RA: case SORT_BY_DEC: case SORT_BY_PROP_MOTION_MAG:
   case SORT_BY_PROP_MOTION_DIR: case SORT_BY_PARALLAX_MEAN:
   case SORT_BY_PARALLAX_VARIANCE: case SORT_BY_MAG_APPARENT:
   case SORT_BY_MAG_ABSOLUTE: case SORT_BY_MASS:
      sortKey = whichType;
      return true;
   default:
      return false;
   }
   return true;
}

bool StarNearEarth::operator<(const StarNearEarth &other) const
{
   switch (sortKey)
   {
   case SORT_BY_NAME_CNS:
      return (nameCns < other.nameCns);
   case SORT_BY_SPECTRAL_TYPE:
      return (spectralType < other.spectralType);
   case SORT_BY_NAME_COMMON:
      return (nameCommon < other.nameCommon);
   case SORT_BY_RANK:
      return (rank < other.rank);
   case SORT_BY_NAME_LHS:
      return (nameLhs < other.nameLhs);
   case SORT_BY_NUM_COMPONENTS:
      return (numComponents < other.numComponents);
   case SORT_BY_RA:
      return (rAsc < other.rAsc);
   case SORT_BY_DEC:
      return (decl < other.decl);
   case SORT_BY_PROP_MOTION_MAG:
      return (propMotionMag < other.propMotionMag);
   case SORT_BY_PROP_MOTION_DIR:
      return (propMotionDir < other.propMotionDir);
   case SORT_BY_PARALLAX_MEAN:
      return (parallaxMean < other.parallaxMean);
   case SORT_BY_PARALLAX_VARIANCE:
      return (parallaxVariance < other.parallaxVariance);
   case SORT_BY_MAG_APPARENT:
      return (magApparent < other.magApparent);
   case SORT_BY_MAG_ABSOLUTE:
      return (magAbsolute < other.magAbsolute);
   case SORT_BY_MASS:
      return (mass < other.mass);
   default:
      return false;
   }
   return true;
}

bool StarNearEarth::operator>(const StarNearEarth &other) const
{
   return (other < *this);
}

bool StarNearEarth::operator==(const StarNearEarth &other) const
{
   return !(other < *this) && !(*this < other);
}

bool StarNearEarth::operator!=(const StarNearEarth &other) const
{
   return !(other == *this);
}

#endif