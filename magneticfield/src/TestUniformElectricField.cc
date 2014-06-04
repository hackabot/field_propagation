//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: TestUniformElectricField.cc 68055 2013-03-13 14:43:28Z gcosmo $
//
// 
//
// Class for creation of uniform Electric Field
//
// 30.1.97 V.Grichine
//
// -------------------------------------------------------------------

#include "TestUniformElectricField.hh"
#include "G4PhysicalConstants.hh"

TestUniformElectricField::TestUniformElectricField(const Vector FieldVector )
{
      fFieldComponents[0] = 0.0;
      fFieldComponents[1] = 0.0;
      fFieldComponents[2] = 0.0;
      fFieldComponents[3] = FieldVector.x();
      fFieldComponents[4] = FieldVector.y();
      fFieldComponents[5] = FieldVector.z();
}
   
TestUniformElectricField::TestUniformElectricField(G4double vField,
                                               G4double vTheta,
                                               G4double vPhi    )
{
   if ( (vField<0) || (vTheta<0) || (vTheta>pi) || (vPhi<0) || (vPhi>twopi) )
   {
      G4Exception("TestUniformElectricField::TestUniformElectricField()",
                  "GeomField0002", FatalException, "Invalid parameters.");
   }

   fFieldComponents[0] = 0.0;
   fFieldComponents[1] = 0.0;
   fFieldComponents[2] = 0.0;
   fFieldComponents[3] = vField*std::sin(vTheta)*std::cos(vPhi) ;
   fFieldComponents[4] = vField*std::sin(vTheta)*std::sin(vPhi) ;
   fFieldComponents[5] = vField*std::cos(vTheta) ;
}

TestUniformElectricField* TestUniformElectricField::Clone() const
{
    return new TestUniformElectricField( Vector(this->fFieldComponents[3],this->fFieldComponents[4],this->fFieldComponents[5]) );
}

TestUniformElectricField::~TestUniformElectricField()
{
}

TestUniformElectricField::TestUniformElectricField (const TestUniformElectricField &p)
   : G4ElectricField(p)
{
   for (G4int i=0; i<6; i++)
      fFieldComponents[i] = p.fFieldComponents[i];
}

TestUniformElectricField&
TestUniformElectricField::operator = (const TestUniformElectricField &p)
{
   for (G4int i=0; i<6; i++)
      fFieldComponents[i] = p.fFieldComponents[i];
   return *this;
}

// ------------------------------------------------------------------------

void TestUniformElectricField::GetFieldValue (const G4double[4],
                                            G4double *fieldBandE ) const 
{
   fieldBandE[0]= 0.0;
   fieldBandE[1]= 0.0;
   fieldBandE[2]= 0.0;
   fieldBandE[3]= fFieldComponents[3] ;
   fieldBandE[4]= fFieldComponents[4] ;
   fieldBandE[5]= fFieldComponents[5] ;
}
