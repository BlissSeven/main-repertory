// imagesource_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>

#include "tisudshl.h"
#include "CmdHelper.h"
#include <algorithm>
#include <vector>
#include <string>

using namespace std;
using namespace DShowLib;
Grabber m_pGrabber;
FrameHandlerSink::tFHSPtr m_pSink;

/* */
struct Settings {
	bool bDeviceAvail;        std::string szDevice;
	bool bVideoNormAvail;     std::string szVideoNorm;

	std::string szVideoFormat;        

	bool bFrameRateAvail;     double lfFrameRate;        
	bool bInputChannelAvail;  std::string szInputChannel;        
	bool bFlipVAvail;         bool bFlipV;
	bool bFlipHAvail;         bool bFlipH;
}m_tDeviceState;

void set_property()
{
	if (m_tDeviceState.bDeviceAvail)
	{
		m_pGrabber.openDev(m_tDeviceState.szDevice);

		if (m_tDeviceState.bVideoNormAvail)
		{
			m_pGrabber.setVideoNorm(m_tDeviceState.szVideoNorm);
		}

		m_pGrabber.setVideoFormat(m_tDeviceState.szVideoFormat);

		if (m_tDeviceState.bFrameRateAvail)
		{
			m_pGrabber.setFPS(m_tDeviceState.lfFrameRate);
		}

		if (m_tDeviceState.bInputChannelAvail)
		{
			m_pGrabber.setInputChannel(m_tDeviceState.szInputChannel);
		}

		if (m_tDeviceState.bFlipVAvail)
		{
			m_pGrabber.setFlipV(m_tDeviceState.bFlipV);
		}

		if (m_tDeviceState.bFlipHAvail)
		{
			m_pGrabber.setFlipH(m_tDeviceState.bFlipH);
		}
	}
	else
	{
		m_pGrabber.closeDev();
	}

}
void set_property2()
{
	/*
	Grabber grabber1;
	grabber1.openDev( "DFx 31AF03" );
	grabber1.setVideoFormat( "UYVY (1024x768)" );
	grabber1.setFPS( 15.0 );
 
	// Open camera 2
	Grabber grabber2;
	grabber2.openDev( "DFx 31BF03" );
	grabber2.setVideoFormat( "UYVY (1024x768)" );
	grabber2.setFPS( 15.0 );

	// Set sink types:
	// FrameHandlerSink containing a 10-buffer MemBufferCollection of RGB24 images.
	tFrameHandlerSinkPtr pSink1 = FrameHandlerSink::create( eRGB24, 10 );
	grabber1.setSinkType( pSink1 );
	tFrameHandlerSinkPtr pSink2 = FrameHandlerSink::create( eRGB24, 10 );
	grabber2.setSinkType( pSink2 );


*/
	m_pGrabber.openDev(m_tDeviceState.szDevice);//string szDevice
	m_pGrabber.setVideoNorm(m_tDeviceState.szVideoNorm);//string szVideoNorm
	m_pGrabber.setVideoFormat(m_tDeviceState.szVideoFormat);//string szVideoFormat
	m_pGrabber.setFPS(m_tDeviceState.lfFrameRate);//double fps 
	m_pGrabber.setInputChannel(m_tDeviceState.szInputChannel);
	m_pGrabber.setFlipV(m_tDeviceState.bFlipV); // bool bFlipV
	m_pGrabber.setFlipH(m_tDeviceState.bFlipH); // bool bFlipV
	m_pGrabber.closeDev();

}
void show_property()
{
	cout << "m_pGrabber.getDev(): "<< m_pGrabber.getDev().toString() << endl;
	cout << "m_pGrabber.getVideoNorm(): " << m_pGrabber.getVideoNorm().toString() << endl;
	cout << "m_pGrabber.getVideoFormat(): " << m_pGrabber.getVideoFormat().toString() << endl;
	cout << "m_pGrabber.getFPS(): " << m_pGrabber.getFPS() << endl;
	cout << "m_pGrabber.getInputChannel(): " << m_pGrabber.getInputChannel().toString() << endl;

	cout << "m_pGrabber.getFlipV(): " << m_pGrabber.getFlipV() << endl;
	cout << "m_pGrabber.getFlipH(): " << m_pGrabber.getFlipH() << endl;
}
void get_property()
{
	
}
int open_camera()
{
	/*打开相机 生成配置文件 This function displays the device selection dialog and saves the selected device in a configuration file, 
	that is loaded when the function is called again.*/
	if (!setupDeviceFromFile(m_pGrabber))
	{
		return -1;
	}

	Grabber::tVidCapDevListPtr pVidCapDevList = m_pGrabber.getAvailableVideoCaptureDevices();// 获取当前相机列表
	if (pVidCapDevList == 0 || pVidCapDevList->empty())
	{
		cout << "pVidCapDevList == 0 || pVidCapDevList->empty() error!!"<< endl;
		return -1; // No device available.
	}

	/*显示设备名称*/
	vector<string> devicename = toStringArrayPtr(pVidCapDevList);
	for (vector<string>::iterator it = devicename.begin();it!=devicename.end();it++)
	{
		cout << "device name: "<<*it<< endl;
	}

	int choice = presentUserChoice(toStringArrayPtr(pVidCapDevList));///toStringArrayPtr 将其转为vector<string>
	// Open the selected video capture device.
	if (choice == -1)
	{
		cout <<"choice =-1 error!!! " << endl;
		return -1;
	}
	
	m_pGrabber.openDev(pVidCapDevList->at(choice));//
	/*获取当前打开的设备的信息*/
	VideoCaptureDeviceItem m_capDevice = pVidCapDevList->at(choice);
	cout << "m_capDevice.getDisplayName(): "<< m_capDevice.getDisplayName()<< endl;
	cout << "m_capDevice.getName(): " << m_capDevice.getName() << endl;
	cout << "m_capDevice.getUniqueName(): " << m_capDevice.getUniqueName() << endl;
	

	/* 显示当前相机支持 视频格式 getAvailableVideoFormatDescs*/
	Grabber::tVidFmtDescListPtr DecriptionList;
	cout << "getAvailableVideoFormatDescs:  " << endl;
	DecriptionList = m_pGrabber.getAvailableVideoFormatDescs();
	for (Grabber::tVidFmtDescList::iterator pDescription = DecriptionList->begin(); pDescription != DecriptionList->end(); pDescription++)
	{
		printf("%s\n", (*pDescription)->toString().c_str());
	}
	/*video norms*/
	cout << "getAvailableVideoNorms:  "<< endl;
	DecriptionList = m_pGrabber.getAvailableVideoNorms();
	for (Grabber::tVidFmtDescList::iterator pDescription = DecriptionList->begin(); pDescription != DecriptionList->end(); pDescription++)
	{
		printf("%s\n", (*pDescription)->toString().c_str());
	}

	// Get the current video format size 获取当前视频格式大小
	cout<<"m_Grabber.getAcqSizeMaxX(): "<<m_pGrabber.getAcqSizeMaxX()<<endl;
	cout<<"m_pGrabber.getAcqSizeMaxY(): "<< m_pGrabber.getAcqSizeMaxY()<<endl;

	// Turn off the default window position, so the grabber can change
	// the video window size. 关闭默认窗口大小设置
	m_pGrabber.setDefaultWindowPosition(false);

	// Set the new window size 设置窗口大小
	//m_pGrabber.setWindowSize(lWidth, lHeight);

	//设置相对父窗口的位置
	//m_pGrabber.setWindowPosition();

												 // We use snap mode.
	m_pSink->setSnapMode(true);
	// Set the sink.
	m_pGrabber.setSinkType(m_pSink);

	// Prepare the live mode, to get the output size if the sink.
	if (!m_pGrabber.prepareLive(false))
	{
		std::cerr << "Could not render the VideoFormat into a eY800 sink.";
		return -1;
	}
	/*获取相机输出视频格式*/
	FrameTypeInfo info;
	m_pSink->getOutputFrameType(info);
	BYTE* pBuf[5];
	cout << "info.buffersize:  " << info.buffersize << endl;
	cout << "info.dim:  x:" << info.dim.cx<<" y: "<<info.dim.cy << endl;
	cout << "info.subtype:  " << info.subtype.Data1<<"  "<< info.subtype.Data2<<"  "<< info.subtype.Data3<<"  "<< info.subtype.Data4 << endl;
	// Allocate 5 image buffers of the above calculate buffer size.
	//分配5个buffer
	for (int i = 0; i < 5; ++i)
	{
		pBuf[i] = new BYTE[info.buffersize];
	}

	m_pSink = FrameHandlerSink::create(eY800, 1);//// 创建sink(内存池）handle，设置内存池图像格式为eY800. 8-bit grayscale format, 1？？？5

	// Create a new MemBuffer collection that uses our own image buffers.
	tMemBufferCollectionPtr pCollection = MemBufferCollection::create(info, 5, pBuf);
	if (pCollection == 0 || !m_pSink->setMemBufferCollection(pCollection))
	{
		std::cerr << "Could not set the new MemBufferCollection, because types do not match.";
		return -1;
	}

	m_pGrabber.startLive(false); //Start live mode for fast snapping

	// Snap 5 images. The images are copied to the MemBufferCollection the
	// application created above.
	m_pSink->snapImages(5);


	/*显示相机属性*/
	cout << "m_pGrabber->getDev().toString(); "<< m_pGrabber.getDev().toString()<< endl;
	// Stop the live video.
	m_pGrabber.stopLive();

	// Close the device.
	m_pGrabber.closeDev();

	// Save the five captured images in the MemBuffer collection to separate files.
	//pCollection->save("file*.bmp");

	// Free the five buffers in the MemBuffer collection.
	for (int j = 0; j < 5; ++j)
	{
		delete pBuf[j];
	}
}
int main()
{
	if (!DShowLib::InitLibrary())
	{
		cout << "DShowLib::InitLibrary error!!!" << endl;
		return FALSE;
	}

	//// Let the sink create a matching MemBufferCollection with 1 buffer.
	m_pSink= FrameHandlerSink::create(eY800, 1);//// 创建sink(内存池）handle，设置内存池图像格式为eY800. //8-bit grayscale format,
//eRGB32    eRGB24  eRGB565   eRGB555   eRGB8

	m_pSink->setSnapMode(true); //设置为snap 模式

	m_pGrabber.setSinkType(m_pSink);
	
	// Show the device page.
	m_pGrabber.showDevicePage();

	// Check if there is a valid device.
	if (m_pGrabber.isDevValid())
	{
		//m_pGrabber.openDev(0);
		// Set the window that should display the live video.
		//m_pGrabber->setHWND(m_hWnd);！！！！！！
		// Start the live video.
		m_pGrabber.startLive();// 显示实时图像
	}
	else
	{
		cout <<"m_pGrabber.isDevValid() error!!" << endl;
		//AfxMessageBox(TEXT("No device was selected."));
	}



	/* 获取一帧图像并保存*/
//	m_pSink->snapImages(1);
//	m_pSink->getLastAcqMemBuffer()->save("image.bmp");

	/* 关闭后释放资源*/
	m_pGrabber.stopLive();//// Stop live mode.
	m_pGrabber.closeDev();//// this call will also succeed if no device is open

	ExitLibrary();
	cout << "hello "<< endl;
    return 0;
}

