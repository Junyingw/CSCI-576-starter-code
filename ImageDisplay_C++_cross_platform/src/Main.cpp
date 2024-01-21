#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

/**
 * Display an image using WxWidgets.
 * https://www.wxwidgets.org/
 */

/** Declarations*/

/**
 * Class that implements wxApp
 */
class MyApp : public wxApp {
 public:
  bool OnInit() override;
};

/**
 * Class that implements wxFrame.
 * This frame serves as the top level window for the program
 */
class MyFrame : public wxFrame {
 public:
  MyFrame(const wxString &title, string imagePath);

 private:
  void OnPaint(wxPaintEvent &event);
  wxImage inImage;
  wxScrolledWindow *scrolledWindow;
  int width;
  int height;
};

/** Utility function to read image data */
unsigned char *readImageData(string imagePath, int width, int height);

/** Definitions */

/**
 * Init method for the app.
 * Here we process the command line arguments and
 * instantiate the frame.
 */
bool MyApp::OnInit() {
  wxInitAllImageHandlers();

  // deal with command line arguments here
  cout << "Number of command line arguments: " << wxApp::argc << endl;
  if (wxApp::argc != 2) {
    cerr << "The executable should be invoked with exactly one filepath "
            "argument. Example ./MyImageApplication '../../Lena_512_512.rgb'"
         << endl;
    exit(1);
  }
  cout << "First argument: " << wxApp::argv[0] << endl;
  cout << "Second argument: " << wxApp::argv[1] << endl;
  string imagePath = wxApp::argv[1].ToStdString();

  MyFrame *frame = new MyFrame("Image Display", imagePath);
  frame->Show(true);

  // return true to continue, false to exit the application
  return true;
}

/**
 * Constructor for the MyFrame class.
 * Here we read the pixel data from the file and set up the scrollable window.
 */
MyFrame::MyFrame(const wxString &title, string imagePath)
    : wxFrame(NULL, wxID_ANY, title) {

  // Modify the height and width values here to read and display an image with
  // different dimensions.    
  width = 512;
  height = 512;

  unsigned char *inData = readImageData(imagePath, width, height);

  // the last argument is static_data, if it is false, after this call the
  // pointer to the data is owned by the wxImage object, which will be
  // responsible for deleting it. So this means that you should not delete the
  // data yourself.
  inImage.SetData(inData, width, height, false);

  // Set up the scrolled window as a child of this frame
  scrolledWindow = new wxScrolledWindow(this, wxID_ANY);
  scrolledWindow->SetScrollbars(10, 10, width, height);
  scrolledWindow->SetVirtualSize(width, height);

  // Bind the paint event to the OnPaint function of the scrolled window
  scrolledWindow->Bind(wxEVT_PAINT, &MyFrame::OnPaint, this);

  // Set the frame size
  SetClientSize(width, height);

  // Set the frame background color
  SetBackgroundColour(*wxBLACK);
}

/**
 * The OnPaint handler that paints the UI.
 * Here we paint the image pixels into the scrollable window.
 */
void MyFrame::OnPaint(wxPaintEvent &event) {
  wxBufferedPaintDC dc(scrolledWindow);
  scrolledWindow->DoPrepareDC(dc);

  wxBitmap inImageBitmap = wxBitmap(inImage);
  dc.DrawBitmap(inImageBitmap, 0, 0, false);
}

/** Utility function to read image data */
unsigned char *readImageData(string imagePath, int width, int height) {

  // Open the file in binary mode
  ifstream inputFile(imagePath, ios::binary);

  if (!inputFile.is_open()) {
    cerr << "Error Opening File for Reading" << endl;
    exit(1);
  }

  // Create and populate RGB buffers
  vector<char> Rbuf(width * height);
  vector<char> Gbuf(width * height);
  vector<char> Bbuf(width * height);

  /**
   * The input RGB file is formatted as RRRR.....GGGG....BBBB.
   * i.e the R values of all the pixels followed by the G values
   * of all the pixels followed by the B values of all pixels.
   * Hence we read the data in that order.
   */

  inputFile.read(Rbuf.data(), width * height);
  inputFile.read(Gbuf.data(), width * height);
  inputFile.read(Bbuf.data(), width * height);

  inputFile.close();

  /**
   * Allocate a buffer to store the pixel values
   * The data must be allocated with malloc(), NOT with operator new. wxWidgets
   * library requires this.
   */
  unsigned char *inData =
      (unsigned char *)malloc(width * height * 3 * sizeof(unsigned char));
      
  for (int i = 0; i < height * width; i++) {
    // We populate RGB values of each pixel in that order
    // RGB.RGB.RGB and so on for all pixels
    inData[3 * i] = Rbuf[i];
    inData[3 * i + 1] = Gbuf[i];
    inData[3 * i + 2] = Bbuf[i];
  }

  return inData;
}

wxIMPLEMENT_APP(MyApp);