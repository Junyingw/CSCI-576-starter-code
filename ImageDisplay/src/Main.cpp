#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

// Foward declarations of functions included in this code module:
void DrawLine(unsigned char* imgBuf, int w, int h, int x1, int y1, int x2, int y2);
void ColorPixel(unsigned char* imgBuf, int w, int h, int x, int y);

class MyApp : public wxApp
{
public:
	bool OnInit() override;
};

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title);

private:
    void OnTimer(wxTimerEvent &event);
    void OnPaint(wxPaintEvent &event);
    wxImage inImage;
    wxImage outImage;
    wxTimer timer1; 

    int imgOffsetY;
    enum
    {
        TIMER1_ID = wxID_HIGHEST + 1
    };
};

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();

    MyFrame *frame = new MyFrame("Image Display");
    frame->Show(true);

    //deal with command line arguments here
    cout << "Number of command line arguments: " << wxApp::argc << endl;
    cout << "First argument: " << wxApp::argv[0] << endl;

    //return true to continue, false to exit the application
    return true;
}

MyFrame::MyFrame(const wxString &title)
    : wxFrame(NULL, wxID_ANY, title),
        timer1(this, TIMER1_ID)
{
    // Set up the images
    int w = 512;
    int h = 512;

    // //create image programatically
    // //The data must be allocated with malloc(), NOT with operator new. wxWidgets library requires this.
    // unsigned char *inData = (unsigned char*)malloc(w * h * 3 * sizeof(unsigned char));
    // memset(inData, 255, w * h * 3 * sizeof(unsigned char));
    // //the last argument is static_data, if it is false, after this call the pointer to the data is owned by the wxImage object, 
    // //which will be responsible for deleting it. So this means that you should not delete the data yourself.
    // inImage.SetData(inData, w, h, false);

    // unsigned char *outData = (unsigned char*)malloc(w * h * 3 * sizeof(unsigned char));
    // memset(outData, 255, w * h * 3 * sizeof(unsigned char));
    // // the internal data for wxImage is RGB not BGR, you can test by uncommenting the following code
    // // memset(outData, 0, w * h * 3 * sizeof(unsigned char));
    // // for(int i = 0; i < w * h * 3; i += 3)
    // // {
    // //     outData[i] = 255;
    // // }
    // outImage.SetData(outData, w, h, false);

    //the following path requires that you run this program from the build directory
    fs::path p = "../images/Lena-image-with-a-512-512-size.png";
    cout << "Executable working path is " << fs::current_path() << endl;
    cout << "Absolute path for " << p << " is " << fs::absolute(p) << endl;

    //load the image using absolute path, relative path works too, this is just a demonstration.
    inImage.LoadFile(wxString(fs::absolute(p)));
    outImage = inImage.Copy();

    DrawLine(outImage.GetData(), w, h, 0, 0, w - 1, h - 1);
    //save the out image to current working directory using relative path
    outImage.SaveFile("out.png");

    //bind the timer event to the OnTimer function
    Bind(wxEVT_TIMER, &MyFrame::OnTimer, this, timer1.GetId());
    //start the timer, the timer will generate a wxEVT_TIMER event every 1000 milliseconds
    timer1.Start(1000);
    //bind the paint event to the OnPaint function
    Bind(wxEVT_PAINT, &MyFrame::OnPaint, this);
    // Set the frame background color
    SetBackgroundColour(*wxBLACK);
    // Set the frame size
    SetClientSize(w * 2 + 50, h + 100);
}

void MyFrame::OnTimer(wxTimerEvent &event)
{
    memset(inImage.GetData(), rand() % 255, inImage.GetWidth() * inImage.GetHeight() * 3 * sizeof(unsigned char));
    //make OnPaint only update the specified rect area
    RefreshRect(wxRect(0, imgOffsetY, inImage.GetWidth(), inImage.GetHeight()), false);
    //use update to force immediate redraw, but won't work if no area is marked as dirty
    Update();
}

void MyFrame::OnPaint(wxPaintEvent &event)
{
    wxBufferedPaintDC dc(this);

    dc.SetFont(GetFont());
    dc.SetTextForeground(*wxWHITE);
    imgOffsetY = dc.GetCharHeight() * 3;

    wxString text = "Original image (Left)  Image after modification (Right)\nUpdate program with your code to modify input image";
    dc.DrawText(text, 0, 0);
    wxBitmap inImageBitmap = wxBitmap(inImage);
    dc.DrawBitmap(inImageBitmap, 0, imgOffsetY, false);
    wxBitmap outImageBitmap = wxBitmap(outImage);
    dc.DrawBitmap(outImageBitmap, inImage.GetWidth() + 50, imgOffsetY, false);
}

// Colors a pixel at the given (x, y) position black.
void ColorPixel(unsigned char* imgBuf, int w, int h, int x, int y)
{
	imgBuf[(3 * y * w) +  3 * x] = 0;
	imgBuf[(3 * y * w) +  3 * x + 1] = 0;
	imgBuf[(3 * y * w) +  3 * x + 2] = 0;
}

// Draws a line using Bresenham's algorithm.
void DrawLine(unsigned char* imgBuf, int w, int h, int x1, int y1, int x2, int y2)
{
	const bool steep = (abs(y2 - y1) > abs(x2 - x1));
	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;
	int y = (int)y1;

	const int maxX = (int)x2;

	for (int x = (int)x1; x<maxX; x++)
	{
		if (steep)
		{
			ColorPixel(imgBuf, w, h, y, x);
		}
		else
		{
			ColorPixel(imgBuf, w, h, x, y);
		}

		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}
}

wxIMPLEMENT_APP(MyApp);