////////////////////////////////////////////////////////////////////////////
//
//  Venus Engine Include File.
//  Copyright (C), Venus Interactive Entertainment.2012
// -------------------------------------------------------------------------
//  File name:   VeAudioResource.inl
//  Version:     v1.00
//  Created:     29/7/2013 by Napoleon
//  Compilers:   Visual Studio.NET
//  Description: 
// -------------------------------------------------------------------------
//  History:
//  http://www.venusie.com
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
VE_INLINE void VeAudio::SetVolume(VeFloat32 f32Volume)
{
	m_f32Volume = f32Volume;
}
//--------------------------------------------------------------------------
VE_INLINE VeFloat32 VeAudio::GetVolume()
{
	return m_f32Volume;
}
//--------------------------------------------------------------------------
