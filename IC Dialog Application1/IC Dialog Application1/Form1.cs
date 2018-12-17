using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace IC_Dialog_Application1
{
    public partial class Form1 : Form
    {
        // This attribute controls whether the live display is scaled in order
        // to match the size of the IC Imaging Control window on the form.
        private bool m_bFitImageToWindow = true;

        private delegate void DeviceLostDelegate();

        private delegate void ShowBufferDelegate(TIS.Imaging.ImageBuffer buffer);

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // Try to load the previously used device. 
            try
            {
                icImagingControl1.LoadDeviceStateFromFile("device.xml", true);
            }
            catch
            {
                // Either the xml file does not exist or the device
                // could not be loaded. In both cases we do nothing and proceed.
            }

            cmdLive.Enabled = icImagingControl1.DeviceValid;
            cmdProperties.Enabled = icImagingControl1.DeviceValid;

            if (m_bFitImageToWindow)
            {
                // Adjust live display size to the control size.
                icImagingControl1.LiveDisplayDefault = false;
                icImagingControl1.LiveDisplayHeight = icImagingControl1.Height;
                icImagingControl1.LiveDisplayWidth = icImagingControl1.Width;
            }



            icImagingControl1.LiveCaptureLastImage = false;

        }

        /// <summary>
        /// Stop the live video stream, if the application is closed.
        /// </summary>
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (icImagingControl1.DeviceValid)
            {
                icImagingControl1.LiveStop();
            }
        }

        /// <summary>
        /// Adjust live display size to the control size.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form1_SizeChanged(object sender, EventArgs e)
        {
            if (m_bFitImageToWindow)
            {
                if (icImagingControl1.DeviceValid)
                {
                    icImagingControl1.LiveDisplayHeight = icImagingControl1.Height;
                    icImagingControl1.LiveDisplayWidth = icImagingControl1.Width;
                }
            }
        }

        /// <summary>
        /// Show the device selection dialog of IC Imaging Control.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmdDevice_Click(object sender, EventArgs e)
        {
            OpenNewVideoCaptureDevice();
        }

        /// <summary>
        /// Show the device's property dialog for exposure, brightness etc.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmdProperties_Click(object sender, EventArgs e)
        {
            ShowDeviceProperties();
        }

        /// <summary>
        /// Start/stop the live video and update the state of the start/stop button.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmdLive_Click(object sender, EventArgs e)
        {
            if (icImagingControl1.LiveVideoRunning)
            {
                StopLiveVideo();
            }
            else
            {
                StartLiveVideo();
            }
        }

        ////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////

        /// <summary>
        /// Start the live video and update the state of the start/stop button.
        /// </summary>
        private void StartLiveVideo()
        {
            icImagingControl1.LiveStart();
            cmdLive.Text = "Stop Live";
        }

        /// <summary>
        /// Stop the live video and update the state of the start/stop button.
        /// </summary>
        private void StopLiveVideo()
        {
            icImagingControl1.LiveStop();
            cmdLive.Text = "Start Live";
        }

        /// <summary>
        /// Show the device selection dialog of IC Imaging Control.
        /// </summary>
        private void OpenNewVideoCaptureDevice()
        {
            if (icImagingControl1.DeviceValid)
            {
                StopLiveVideo();
            }
            else
            {
                icImagingControl1.Device = "";
            }
            icImagingControl1.ShowDeviceSettingsDialog();
            cmdLive.Enabled = icImagingControl1.DeviceValid;
            cmdProperties.Enabled = icImagingControl1.DeviceValid;
            if (icImagingControl1.DeviceValid)
            {
                // Save the currently used device into a file in order to be able to open it
                // automatically at the next program start.
                icImagingControl1.SaveDeviceStateToFile("device.xml");
            }
        }

        /// <summary>
        /// Show the device's property dialog for modifying exposure, brightness etc. 
        /// All changes are saved to the file 'device.xml'.
        /// </summary>
        private void ShowDeviceProperties()
        {
            if (icImagingControl1.DeviceValid)
            {
                icImagingControl1.ShowPropertyDialog();
                icImagingControl1.SaveDeviceStateToFile("device.xml");
            }
        }






        /// <summary>
        /// Call the image processing method manually from a button.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cmdProcess_Click(object sender, EventArgs e)
        {
            ProcessImage();
        }

        /// <summary>
        /// Perfrom image processing. This method is called from a button,
		/// but can also be called from a timer.
        /// </summary>
        private void ProcessImage()
        {
            TIS.Imaging.ImageBuffer ImgBuffer;
            int x, y;
            int BytesPerLine;

            Cursor = Cursors.WaitCursor;
            icImagingControl1.MemorySnapImage();


            // Stop the live video, so the processed image can be displayed.
            StopLiveVideo();


            ImgBuffer = icImagingControl1.ImageActiveBuffer;
            // Calculate the number of bytes per line. 
            BytesPerLine = ImgBuffer.BitsPerPixel / 8 * ImgBuffer.PixelPerLine;

            // Start the image processing. It is contained in an "unsafe" section,
            // because a pointer to the image data is used.
            unsafe
            {
                // TODO: Insert your own image processing here.
                byte* pDatabyte = ImgBuffer.GetImageData();
                for (y = 0; y < ImgBuffer.Lines; y++)
                {
                    for (x = 0; x < BytesPerLine; x++)
                    {
                        *pDatabyte = (byte)(255 - *pDatabyte);
                        pDatabyte++;
                    }
                }
            }


            // Display the processed image in the IC Imaging Control window.
            icImagingControl1.DisplayImageBuffer(ImgBuffer);


            Cursor = Cursors.Default;
        }

        /// <summary>
        /// Handle the DeviceLost event.
        /// </summary>
        private void DeviceLost()
        {
            MessageBox.Show("Device Lost!");
            cmdLive.Text = "Start Live";
            cmdLive.Enabled = false;
            cmdProperties.Enabled = false;
        }

        private void icImagingControl1_DeviceLost(object sender, TIS.Imaging.ICImagingControl.DeviceLostEventArgs e)
        {
            BeginInvoke(new DeviceLostDelegate(ref DeviceLost));
        }
    }
}
