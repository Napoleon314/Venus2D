package com.VenusIE.VeGraphicsTest;
import android.os.Bundle;

public class VeGraphicsTestActivity extends android.app.NativeActivity
{
	static
	{
		System.loadLibrary("VeGraphicsTest");
	}
	
	@Override
    protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);	
	}
	
}
