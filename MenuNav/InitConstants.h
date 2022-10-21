/*============================================================================*/
/*       1         2         3         4         5         6         7        */
/*3456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================*/
/*                                             .                              */
/*                                               RRRR WW  WW   WTTTTTTHH  HH  */
/*                                               RR RR WW WWW  W  TT  HH  HH  */
/*      Header   :	InitConstants.h				 RRRR   WWWWWWWW  TT  HHHHHH  */
/*                                               RR RR   WWW WWW  TT  HH  HH  */
/*      Module   :  			                 RR  R    WW  WW  TT  HH  HH  */
/*                                                                            */
/*      Project  :  			                   Rheinisch-Westfaelische    */
/*                                               Technische Hochschule Aachen */
/*      Purpose  :                                                            */
/*                                                                            */
/*                                                 Copyright (c)  1998-2001   */
/*                                                 by  RWTH-Aachen, Germany   */
/*                                                 All rights reserved.       */
/*                                             .                              */
/*============================================================================*/
/*                                                                            */
/*    THIS SOFTWARE IS PROVIDED 'AS IS'. ANY WARRANTIES ARE DISCLAIMED. IN    */
/*    NO CASE SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DAMAGES.    */
/*    REDISTRIBUTION AND USE OF THE NON MODIFIED TOOLKIT IS PERMITTED. OWN    */
/*    DEVELOPMENTS BASED ON THIS TOOLKIT MUST BE CLEARLY DECLARED AS SUCH.    */
/*                                                                            */
/*============================================================================*/
/* $Id: InitConstants.h 49363 2015-04-20 14:24:47Z dz762974 $ */

#ifndef INITCONSTANTS_H
#define INITCONSTANTS_H

/*============================================================================*/
/* INCLUDES																	  */
/*============================================================================*/
#include <string>
#include <VistaBase/VistaColor.h>

/*============================================================================*/
/* CLASS DEFINITION															  */
/*============================================================================*/

class InitConstants
{
public:
	std::string		strPathToFile;

	float			m_nMinClipPercentage;
	float			m_nMaxClipPercentage;
	int				m_nClipLevelMin;
	int				m_nClipLevelMax;
	float			m_nSmoothingFactor;
	float			m_nSmoothedStrength;
};

bool LoadConfigSettings( InitConstants& initConstants, const std::string& sFileName);

#endif

/*============================================================================*/
/* END OF FILE																  */
/*============================================================================*/
