#include "SW_MCP4017.h"

MCP4017::MCP4017(uint8_t adcAddress, uint8_t maxSteps, float maxOhms)
{
  I2CADCAddress = adcAddress;
  _maxSteps = maxSteps;
  _currentStep = 0;
  _currentRout = 0.0;
  _maxOhm = maxOhms;

  // We are going to assume that Wire.begin() has been called in setup()
}

/////////////////////////////////////////////////////////////////////////////
/*!
	Sets the resistance of the digital pot by sending a number of steps

*/
/////////////////////////////////////////////////////////////////////////////

void MCP4017::setSteps(uint8_t steps)
{

	_currentStep = steps;
	Serial.println(_maxOhm);
	float temp1 = (float)steps / _maxSteps;
	Serial.println(temp1);
	float temp2 = temp1 * _maxOhm;
	Serial.println(temp2);
	_currentRout = temp2 + WIPEROHMS;
	Serial.println(_currentRout);
	//_currentRout = (((float)steps / _maxSteps) * _maxOhm) + WIPEROHMS;
	I2CSendSteps(_currentStep);

}

/////////////////////////////////////////////////////////////////////////////
/*!
	Calculates the number of steps to send based on a desired resistance

*/
/////////////////////////////////////////////////////////////////////////////

void MCP4017::setResistance(double Rout)
{
	
	uint8_t tempsteps = (int)((_maxSteps * (Rout - WIPEROHMS)) / _maxOhm);
	setSteps(tempsteps);

}

/////////////////////////////////////////////////////////////////////////////
/*!
	just in case you need it, a way to calculate the resistance
	since most of these potentiometers loss settings at power down (or they simply loose power)
	they generally default to their midrange
*/
/////////////////////////////////////////////////////////////////////////////

float MCP4017::calcResistance()
{
	//float Rout;
	//Rout = ((_currentStep / _maxSteps) * _maxOhm) + WIPEROHMS;
	return _currentRout;
}

/////////////////////////////////////////////////////////////////////////////
/*!
	Here is our actual method where we send the steps over to the Digital Potentiometer!

*/
/////////////////////////////////////////////////////////////////////////////

void MCP4017::I2CSendSteps(uint8_t steps)
{

	Wire.beginTransmission(I2CADCAddress);
	Wire.write(steps); // 
	Wire.endTransmission();
}


