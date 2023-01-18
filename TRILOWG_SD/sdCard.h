#include "experimentData.h"

#include <SD.h>
File TRILowG_SD_Data;

String initializeSD(String date = "12/05/2022")
{
  String firstLine = "SD Initialization Sucessful - ";
  if(!SD.begin(BUILTIN_SDCARD)) return "SD initialization failed";
  
  TRILowG_SD_Data = SD.open("TRILowG_DataLog.tri", FILE_WRITE);
  if(!TRILowG_SD_Data) return "File initialization failed";

  TRILowG_SD_Data.println();
  TRILowG_SD_Data.println("Test of Robotic Intrusion in Low Gravity");
  TRILowG_SD_Data.println("project by Nicholas Nacleiro");
  TRILowG_SD_Data.print("Data series collected on "); TRILowG_SD_Data.println(date);
  TRILowG_SD_Data.println("Phase \t System time \t Phase time \t RP force \t TED force \t Pressure 1 \t Pressure 2");
  TRILowG_SD_Data.println("p(/) \t Ts(ms) \t Tp(ms) \t Frp(lbf) \t Fted(lbf) \t P1(psi) \t P2(psi)");

  TRILowG_SD_Data.close();

  firstLine.append(date);
  return firstLine;
}

String writeToSD(DataPoint& reading)
{
  String line;

  line.append(reading.experimentPhase); line.append("\t");
  line.append(reading.systemTime); line.append("\t");
  line.append(reading.phaseTime); line.append("\t");
  line.append(reading.rpForce * 5.0 / 32767); line.append("\t\t");
  line.append(reading.tedForce * 5.0 / 32767); line.append("\t\t");
  line.append(reading.pressure1); line.append("\t");
  line.append(reading.pressure2); line.append("\t\t");

  TRILowG_SD_Data = SD.open("TRILowG_DataLog.tri", FILE_WRITE);
  if(!TRILowG_SD_Data) return "File initialization failed";
  
  TRILowG_SD_Data.println(line);
  TRILowG_SD_Data.close();
  
  return line;
}
