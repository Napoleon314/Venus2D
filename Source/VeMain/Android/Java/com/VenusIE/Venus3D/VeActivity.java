package com.VenusIE.Venus3D;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Locale;

import android.annotation.SuppressLint;
import android.bluetooth.BluetoothAdapter;
import android.content.Context;
import android.net.wifi.WifiManager;
import android.provider.Settings.Secure;
import android.telephony.TelephonyManager;
import android.util.Log;
import android.view.*;
import android.os.*;
import android.view.inputmethod.*;
import android.widget.EditText;

public class VeActivity extends android.app.NativeActivity
{
	private final static int CMD_ENABLE_IME = 1;
	private final static int CMD_DISABLE_IME = 2;

	private static Handler m_kHandler = new Handler()
	{
		@Override
		public void handleMessage(final Message msg)
		{
			VeActivity kActivity = (VeActivity) msg.obj;
			switch (msg.what)
			{
			case CMD_ENABLE_IME:
				kActivity.SetSoftInputEnable(true);
				break;
			case CMD_DISABLE_IME:
				kActivity.SetSoftInputEnable(false);
				break;
			}
		}

	};

	class ImeConnection extends InputConnectionWrapper
	{
		public ImeConnection(InputConnection target, boolean mutable)
		{
			super(target, mutable);
		}

		@Override
		public boolean setComposingText(CharSequence text, int newCursorPosition)
		{
			Log.d("JNI", "setComposingText " + text);
			return super.setComposingText(text, newCursorPosition);
		}

		@Override
		public boolean commitText(CharSequence text, int newCursorPosition)
		{
			Log.d("JNI", "commitText " + text);
			return super.commitText(text, newCursorPosition);
		}

		@Override
		public boolean sendKeyEvent(KeyEvent event)
		{
			Log.d("JNI", "sendKeyEvent ");
			return super.sendKeyEvent(event);
		}

		@Override
		public boolean deleteSurroundingText(int beforeLength, int afterLength)
		{
			if (beforeLength == 1 && afterLength == 0)
			{
				Log.d("JNI", "DELETE!");
			}
			return super.deleteSurroundingText(beforeLength, afterLength);
		}
	}

	class ContentView extends EditText
	{
		public ContentView(Context context)
		{
			super(context);
		}

		@Override
		protected boolean getDefaultEditable()
		{
			return false;
		}
	}

	static public String ms_kDeviceID;
	ContentView m_kView;

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		ms_kDeviceID = GetDeviceID();
		m_kView = new ContentView(this);
		setContentView(m_kView);
	}

	public void SetSoftInputEnable(boolean bEnable)
	{
		InputMethodManager kInput = (InputMethodManager) getSystemService(INPUT_METHOD_SERVICE);
		if (bEnable)
		{
			//m_kView.setEditableFactory(factory);
			//m_kView.setEnabled(true);
			kInput.showSoftInput(m_kView, 0);
		}
		else
		{
			//m_kView.setEnabled(false);
			kInput.hideSoftInputFromWindow(m_kView.getWindowToken(), 0);
		}
	}

	public void jni_EnableIME()
	{
		if (m_kHandler != null)
		{
			final Message kMsg = new Message();
			kMsg.what = CMD_ENABLE_IME;
			kMsg.obj = this;
			m_kHandler.sendMessage(kMsg);
		}
	}

	public void jni_DisableIME()
	{
		if (m_kHandler != null)
		{
			final Message kMsg = new Message();
			kMsg.what = CMD_DISABLE_IME;
			kMsg.obj = this;
			m_kHandler.sendMessage(kMsg);
		}
	}

	public static String jni_GetDeviceID()
	{
		return ms_kDeviceID;
	}

	public static String jni_GetDeviceName()
	{
		return Build.MODEL;
	}

	public static String jni_GetLanguage()
	{
		return Locale.getDefault().getLanguage() + "_"
				+ Locale.getDefault().getCountry();
	}

	@SuppressLint("DefaultLocale")
	@SuppressWarnings("deprecation")
	public String GetDeviceID()
	{
		String szImei = "";
		try
		{
			TelephonyManager TelephonyMgr = (TelephonyManager) getSystemService(TELEPHONY_SERVICE);
			szImei = TelephonyMgr.getDeviceId();
		}
		catch (SecurityException e)
		{
			e.printStackTrace();
		}
		finally
		{
			if (szImei == null || "".equals(szImei))
			{
				szImei = "";
			}
		}
		String m_szDevIDShort = "35" + Build.BOARD.length() % 10
				+ Build.BRAND.length() % 10 + Build.CPU_ABI.length() % 10
				+ Build.DEVICE.length() % 10 + Build.DISPLAY.length() % 10
				+ Build.HOST.length() % 10 + Build.ID.length() % 10
				+ Build.MANUFACTURER.length() % 10 + Build.MODEL.length() % 10
				+ Build.PRODUCT.length() % 10 + Build.TAGS.length() % 10
				+ Build.TYPE.length() % 10 + Build.USER.length() % 10;
		String m_szAndroidID = Secure.getString(getContentResolver(),
				Secure.ANDROID_ID);
		String m_szWLANMAC = "";
		try
		{
			WifiManager wm = (WifiManager) getSystemService(Context.WIFI_SERVICE);
			m_szWLANMAC = wm.getConnectionInfo().getMacAddress();
		}
		catch (SecurityException e)
		{
			e.printStackTrace();
		}
		finally
		{
			if (m_szWLANMAC == null || "".equals(m_szWLANMAC))
			{
				m_szWLANMAC = "";
			}
		}
		String m_szBTMAC = "";
		try
		{
			BluetoothAdapter m_BluetoothAdapter = null;
			m_BluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
			m_szBTMAC = m_BluetoothAdapter.getAddress();
		}
		catch (SecurityException e)
		{
			e.printStackTrace();
		}
		finally
		{
			if (m_szBTMAC == null || "".equals(m_szBTMAC))
			{
				m_szBTMAC = "";
			}
		}
		String m_szLongID = szImei + m_szDevIDShort + m_szAndroidID
				+ m_szWLANMAC + m_szBTMAC;

		MessageDigest m = null;
		try
		{
			m = MessageDigest.getInstance("MD5");
		}
		catch (NoSuchAlgorithmException e)
		{
			e.printStackTrace();
		}
		m.update(m_szLongID.getBytes(), 0, m_szLongID.length());
		byte p_md5Data[] = m.digest();
		String m_szUniqueID = new String();
		for (int i = 0; i < p_md5Data.length; ++i)
		{
			int b = (0xFF & p_md5Data[i]);
			if (b <= 0xF) m_szUniqueID += "0";

			m_szUniqueID += Integer.toHexString(b);
		}
		m_szUniqueID = m_szUniqueID.toUpperCase();
		return m_szUniqueID;
	}
}
