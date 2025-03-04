/*$

=head1 NAME

Rickmovie - displays cubic array of data

=head1 SYNOPSIS

Rickmovie in=datafile [ data pars ] [ display pars ]

=head1 DESCRIPTION

Display cubic array of data in XWindows-Motif

=head1 INPUT PARAMETERS

=over 4

=item in          - file     

      [stdin]    name of input file

=item n1,n2,n3..5 - integer  

      length of 3 dimensions, n1 is fastest, e.g. time

=item o1...o5     - float    

      [0.]first sample value in each dimension

=item d1...d5     - float    

      [1.]sample increment in each dimension

=item z1...z5     - integer  

      [1]relative spacing for true size, z3=3 means wide lines

=item label1..5   - char*    

      [n1]...[n5]label for each dimension

=item title       - char*    

      [in]   dataset title

=item script      - file     

      script file with label for every panel (n3 dimension)

=item segy        - integer  

      [0]data format is segy or not

=item vgrid       - integer   

      specify vgrid choice

=item esize       - integer  

      [1]  data samples are =1 for bytes or =4 for floats

=item hbytes      - integer  

      [0,3600]header bytes to skip; 3600 for segy=1

=item pclip       - integer  

      [255]  positive clip value; high= and clip= are synonyms

=item nclip       - integer  

      [1]  negative clip value; low= and clip= are synonyms

=item value       - char*    

      [sample] name for values on colorbar

=item width,height-integer   

      [600]pixel dimension (> 64) or fraction of screen (<= 1.0)

=item pick        -file       

      pick line data file

=item npick       -integer    

      [2500]maximum number of picks used

=item style       -char*      

      [cube]view is front, side, top, plan, array, picks, cube, 
      fence, or transparent

=item orient      -char*      

      [front]    orient is front, side, top

=item origin      -char*      

      [minimum]   frames set to middle or minimum

=item transp      -integer    

      [0] if 1, transpose down and across

=item shape       -char*      

      [fit]   shape fits screen, true, or pixel

=item movie       -char*      

      [off] run movie in up, down, left, right, in, or out direction

=item color       -char*      

      [gray]color is gray, straw, flag, tiger, blue, or rainbow

=item contrast    -integer    

      [50]  contrast is between 0 and 100

=item font        -char*      

      alternative XWindows font; default bold-courier-20

=back

 

=head1 DATA ARGUMENTS

=over 4

=item in=datafile       vgrid format - bytes or float with header

=item in=datafile n1= n2= n3= segy=1  segy/SU format - float traces with headers

=item in=datafile n1= n2= n3=  bytes format (SEPlib) - byte array without header

=item in=datafile n1= n2= n3= esize=4  float format - float array without header

=back

 

=head1 FILE FORMATS

=over 4

=item seplib, bytes input data set: (user supplied)

      2-D of 3-D array of unsigned byte integers 0-255.
      Use segy2movie to convert segy.
      Use Byte to convert seplib floating point.

=item seplib, float input data set: (user supplied)

      2-D of 3-D array of float numbers

=item segy, su input data set: (user supplied)

      Two dataset headers.
      n2 x n3 segy traces.
      Each trace 240 bytes + n1 IEEE floating point samples.
      Use suread to convert tape dataset.

=item vgrid, (read or written by Movie).

      cubic array of data.
      100 byte tail describing dimensions.

=item script file: (user supplied)

      Text file.
      Each line of text annotates an n3 direction frame.

=item pick file: (generated by program or user supplied)

      First line is dataset name.
      Second line is dataset dimensions.
      Third line are axes labels.
      Followed by pick-lines:
       First line is ID and frame.
       Following lines are pick points:
        three coordinates and data value.

=item par file: (user supplied or generated by Save State menu)

      List of parameters in name=value form. Free format.
      Last of duplicates used.

=back

 

=head1 WINDOWS

=over 4

=item (1) Menubar on top.

=item (2) Message window below menubar.

=item (3) Control panel below message window.

=item (4) Color spectrum below control panel.
      Line shows relative data sample distribution.
      Bar shows last pick value or range of values.
      Mouse click-drag-up specifies a value range.

=item (5) Resizable image window.  Responds to following mouse clicks:

=back

 

=head1 MOUSE USAGE

=over 4

=item LEFT: zoom; MIDDLE: navigate; RIGHT: pick.

=item LEFT click-drag-up: zoom window.

=item LEFT click only: initial size.

=item LEFT click-drag-up + 'h' key: zoom horizontal only.

=item LEFT click-drag-up + 'v' key: zoom vertical only.

=item LEFT click-drag-up in ARRAY window: those panels.

=item MIDDLE click: select cross frames.

=item MIDDLE click-drag-up: select an animation range.

=item RIGHT click: pick a point on the image.

=item RIGHT click + 'a' key: add a point to end of pick line.

=item RIGHT click + 'm' key: move nearest point in pick line.

=item RIGHT click + 'd' key: delete nearest point in pick line.

=item RIGHT click-drag-up + 's' key:select seed point & sub-volume pick bounds.

=item COLORBAR ANY click-drag-up: replace sub-volume range with this new range.

=back

 

=head1 INTERACTIVE CONTROLS

 

=head1 MAIN FUNCTIONS: Interface to system

=over 4

=item  "Main"  "Redraw" -- refresh damaged screen

=item  "Main"  "Write vgrid file (floats)" -- save data files as floats in 
               seplib/vgrid format

=item  "Main"  "Write vgrid file (bytes)" -- save data files as bytes in 
               seplib/vgrid format

=item  "Main"  "Write parameter restart file" -- create a parameter restart file

=item  "Main"  "Debug" -- dump various arrays for programmer debugging

=item  "Main"  "Quit"

=back

 

=head1 STYLE FUNCTIONS: Select a style and set attributes

=over 4

=item  "View"  "Front (2D)" -- Front face of data cube

=item  "View"  "Side (2D)" -- Side face of data cube

=item  "View"  "Top (2D)" -- Top face of data cube

=item  "View"  "Plan (2D)" -- All three cube faces

=item  "View"  "Array (3D) ..." -- Array of front faces- up to a hundred

=item  "View"  "Pick (3D) ..." -- Array of picked faces

=item  "View"  "Cube (3D)" -- Cube view

=item  "View"  "Fence (3D) ..." -- Show intersecting faces

=item  "View"  "Transparent (3D) ..." -- Transparent volume

=item  "Array Panel" "Direction" <four axes> -- Select through direction

=item  "Array Panel" "Down" -- Panels in down direction

=item  "Array Panel" "Across" -- Panels in across direction

=item  "Array Panel" "Start" -- First panel

=item  "Array Panel" "Delta" -- Panel increment

=item  "Array Panel" "End" -- Last panel; sets delta

=item  "Array Panel" "Draw" -- Draw with new parameters

=item  "Array Panel" "Close" -- Close control panel

=item  "Array Panel" "LEFT MOUSE SELECTS PANEL RANGE

=item  "Fence Panel" "Toggle Front" -- Toggle front plane on

=item  "Fence Panel" "Toggle Side" -- Toggle side plane on

=item  "Fence Panel" "Toggle Top" -- Toggle top plane on

=item  "Fence Panel" "Transparency" -- Set transparency threshhold

=item  "Fence Panel" "Draw" -- Draw with new parameters

=item  "Fence Panel" "Close" -- Close control panel

=item  "Transparency Panel"  "Min" -- Set minimum transparency value

=item  "Transparency Panel"  "Max" -- Set maximum transparency value

=item  "Transparency Panel"  "Transp" -- Set transparency value

=item  "Transparency Panel"  "Draw altogether" -- Update screen once

=item  "Transparency Panel"  "Draw tenth blocks" -- Update screen ten times

=item  "Transparency Panel"  "Draw each plane" -- Update screen continuously

=item  "Transparency Panel"  "Draw" -- Draw with new parameters

=item  "Transparency Panel"  "Close" -- Close control panel

=back

 

=head1 ORIENT FUNCTIONS: change way axes point; 2-D are in-plane

=over 4

=item  "Orient"  "Side<->Top (2-D)" -- Rotate axes

=item  "Orient"  "Front<->Side (3-D)" -- Rotate axes

=item  "Orient"  "Top<->Front (3-D)" -- Rotate axes

=item  "Orient"  "Front<->Extra (4-D)" -- Rotate axes

=item  "Orient"  "Side<->Extra (4-D)" -- Rotate axes

=item  "Orient"  "Top<->Extra (4-D)" -- Rotate axes

=item  "Orient"  "<-Down-> (2-D)" -- Reversal

=item  "Orient"  "<-Across-> (2-D)" -- Reversal

=item  "Orient"  "<-Deep-> (3-D)" -- Reversal

=item  "Orient"  "Frames to Origin" -- Cross frames to start of origin of 
                 each axis

=item  "Orient"  "Frames in Middle" -- Cross frames in middle of each frame

=item  "Orient"  "Labels Set .." -- Control panel to adjust labeling

=item  "Orient"  "Reset Initial"

=back

 

=head1 SIZE FUNCTIONS: set size and shape policy

=over 4

=item  "Size"  "Fit Screen" -- Front fills 2/3s screen; sides 1/3

=item  "Size"  "True Proportions"

=item  "Size"  "Sample per Pixel"

=item  "Size"  "Interpolate" -- Improves large magnifications

=item  "Size"  "Size Set .." -- Launch size setting control panel

=item  "Size Set"  "Minimum" -- Minimum sample/value along axis

=item  "Size Set"  "Maximum" -- Maximum sample/value along axis

=item  "Size Set"  "Frame" -- Frame sample/value along axis

=item  "Size Set"  "Pixels" -- Pixels along axis

=item  "Size Set"  "Draw" -- Draw these size settings

=item  "Size Set"  "Current" -- Restore current size settings

=item  "Size Set"  "Initial" -- Fill in initial settings

=item  "Size Set"  "Close" -- Close size settings panel

=item  "Size"  "Reset Initial"

=item  "Size"  "LEFT MOUSE BOX ZOOMS" -- interactive magnification

=item  "Size"  "+ 'h' KEY ONLY HORZ" -- constrain to horizontal

=item  "Size"  "+ 'v' KEY ONLY VERT" -- constrain to vertical

=item  "Size"  "LEFT MOUSE CLICK ONLY" -- initial size

=back

 

=head1 MOVIE FUNCTIONS: go to part of the cube; run movies

=over 4

=item  "Navigate"  "Reset Bounds" -- Movie loop traverses full cross face

=item  "Navigate"  "High Speed" -- Frames are stored in displat terminal

=item  "Navigate" BUTTON "GO" -- Start movie

=item  "Navigate" BUTTON "NO" -- Stop movie

=item  "Navigate" BUTTON " z " -- Run/step in direction

=item  "Navigate" BUTTON " Z " -- Run/step out direction

=item  "Navigate" BUTTON " < " -- Run/step left direction

=item  "Navigate" BUTTON " > " -- Run/step right direction

=item  "Navigate" BUTTON " ^ " -- Run/step up direction

=item  "Navigate" BUTTON " v " -- Run/step down direction

=item  "Navigate" SLIDER " Speed " -- Delay between frames

=item  "Navigate"  "MIDDLE MOUSE CLICK Reset cross framesFRAMES" -- X

=item  "Navigate"  "MIDDLE MOUSE DRAG MOVIE BOUNDS" -- Set movie range

=back

 

=head1 COLOR FUNCTIONS: set color, contrast, and transparency

=over 4

=item  "Color" "Gray" -- Grayscale

=item  "Color" "Straw" -- Blue and yellow

=item  "Color" "Flag" -- Red, white and blue

=item  "Color" "Tiger" -- Red, white and black

=item  "Color" "Blue" -- Blue and white

=item  "Color" "Rainbow" -- Multi-colored

=item  "Color" "Graybow" -- Gray plus multi-colored

=item  "Color" "Overlay" <color-list> -- Overlay lines and text

=item  "Color" "Mark" <color-list> -- Pick color

=item  "Color" "Background" <color-list> -- Screen background color

=item  "Color" "Flip Polarity" -- of data-> color

=item  "Color" "Reset Contrast" -- No skew or zero point contrast

=item  "Color" SLIDER "CONTRAST" -- Shift color table skew

=item  "Color" SLIDER "CONTRAST0" -- Shift color table zero point

=item "Color" BUTTON "Reset" -- Reset initial contrast

=back

 

=head1 PICK FUNCTIONS: set picking behavior

=over 4

=item  "Pick"  "Clear Current Line" -- Erase pick line or sub-volume

=item  "Pick"  "Write pick file" -- Write to pick= now

=item  "Pick"  "Read pick file" -- Read from pick= now

=item  "Pick"  "RIGHT MOUSE MAKES PICK" -- right mouse button manipulates picks

=item  "Pick"  "+ 'a' KEY ADDS POINT TO END OF LINE"

=item  "Pick"  "+ 'i' KEY INSERTS POINT BETWEEN NEAREST POINTS"

=item  "Pick"  "+ 'm' KEY MOVES NEAREST POINT"

=item  "Pick"  "+ 'd' KEY DELETES NEAREST POINT"

=item  "Pick"  "+ 's' KEY + DRAGGING PICKS SUB-VOLUME"

=back

 

=head1 EDIT FUNCTIONS: edit grid sub-volume

=over 4

=item  "Edit"  "Clear Sub-volume pick" -- Clear current subvolume

=item  "Edit"  "Smooth Sub-volume" -- Smooth sub-volume to boundary value

=item  "Edit"  "Undo Smooth" -- Restore sub-volume

=item  "Edit"  "Grade Sub-volume" -- Grade sub-volume to boundary plane values

=item  "Edit"  "Undo grade"

=item  "Edit"  "Sub-volume Neighborhood" <6, 18, 26> -- Cube connectivity of 
               sub-volume

=item  "Edit"  "COLOR BAR MOUSE SETS SMOOTH RANGE"

=back

 

=head1 SECTION FUNCTION: plot various sections through the data

=over 4

=item  "Section" "On screen wiggle plot ..." "Front, side or top plane"

=item  "Section" "On screen contour plot ..."  "Front, side or top plane"

=item  "Section" "On screen graph profile ..." "Down, across, or deep profile"

=item  "Section" "Print wiggle plot ..." "Front, side or top plane"

=item  "Section" "Print contour plot ..."  "Front, side or top plane"

=item  "Section" "Print graph profile ..." "Down, across, or deep profile"

=item  "Section" "Save section in file ..."  "Front, side or top plane"

=item  "Section" "Save profile in file ..." "Save down, across, or deep profile"

=item  "Section" "PLANES AND PROFILES ARE SELECTED AT CROSS-HAIRS"

=back

 

=head1 STATUS FUNCTIONS: print parameters and state variables

=over 4

=item  "Status"  "Dataset" -- Dataset parameters

=item  "Status"  "Data Values" -- Data value parameters

=item  "Status"  "Data Axis0" -- Value/color axis

=item  "Status"  "Data Axis1" -- Fast axis, usually time

=item  "Status"  "Data Axis2" -- Second data axis, usually CDP

=item  "Status"  "Data Axis3" -- Slow axis, usually section

=item  "Status"  "Data Axis4" -- Slow axis, usually offset

=item  "Status"  "Data Axis5" -- Slow axis, unused

=item  "Status"  "View" -- View parameters

=item  "Status"  "Down Axis" -- View down axis parameters

=item  "Status"  "Across Axis" -- View across axis parameters

=item  "Status"  "Deep Axis" -- View deep axis parameters

=item  "Status"  "Extra Axis" -- View extra axis parameters

=item  "Status"  "Color Axis" -- Colorbar axis parameters

=item  "Status"  "Color" -- Color and contrast parameters

=item  "Status"  "Render" -- Rendering parameters

=item  "Status"  "Draw" -- Draw screen parameters

=item  "Status"  "Mouse Buttons" -- Mouse button functions

=item  "Status"  "Navigate" -- Movie parameters

=item  "Status"  "Pick" -- Pick parameters

=item  "Status"  "Pick List" -- Current pick line parameters

=item  "Status"  "sub-volume" -- Current mark sub-volume

=item  "Status"  "Frame List" -- List of screen frames

=back

 

=head1 HELP FUNCTIONS: print self documentation from various places

=over 4

=item  "Help"  "Command Line Args"

=item  "Help"  "File Formats"

=item  "Help"  "Windows"

=item  "Help"  "Mouse Usage"

=item  "Help"  "Main Functions"

=item  "Help"  "View Functions"

=item  "Help"  "Orient Functions"

=item  "Help"  "Size Functions"

=item  "Help"  "Navigate Functions"

=item  "Help"  "Color Functions"

=item  "Help"  "Picking Functions"

=item  "Help"  "Status Functions"

=back

 

=head1 CATEGORY

B<interact> 

=cut

/*
main program code
*/
#include <sepConfig.h>
#if defined (HAVE_MOTIF) || defined(HAVE_ATHENA)
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include "main.h"
#include "axis.h"
#include "data.h"
#include "map.h"
#include "render.h"
#include "plane.h"
#include "view.h"
#include "pik.h"
#include "pick.h"
#include "color.h"
#include "colorbar.h"
#include "draw.h"
#include "region.h"
#if defined (HAVE_STDLIB_H)
#include<stdlib.h>
#else
extern int atoi();
#endif /* HAVE_STDLIB  */
#include "movie.h"
#include "ui.h"

#ifdef SEPLIB
#define OUT "/dev/null"
#include <sep.main>
#endif

#ifdef SU
char *sdoc[] = { ""};
#endif


/* current dataset, render */
Data data = 0;
Render render = 0;
View view = 0;
int _core = 16*1024*1024;
int _alloc = 0;
int memwatch = 0;

#ifdef SEPLIB
int MAIN (void)
	{
#else
int	sepxargc;
char	**sepxargv;
int	infd = 0;
int	outfd = 1;
FILE	*instream = stdin;
FILE	*outstream = stdout;
string	in = "stdin";
string	out = "stdout";

int main (int argc, char **argv)
	{
	extern int sepxargc;
	extern char **sepxargv, *help;
	extern int infd, outfd;
	extern FILE *instream, *outstream;
	extern string in, out;

	sepxargc = argc;
	sepxargv = argv;
	/* selfdoc */
	if (argc == 1 && lseek(infd,0,2) == 0) {
		HelpMore ("Movie","END");
		exit(0);
		}
	GetparInit (sepxargc,sepxargv);
	if (GETPARSTRING ("in","s",in)) {
		if ((infd = open (in,0)) < 0) err ("cant open in= file");
		if ((instream = fdopen (infd,"r")) == NULL) err ("can't open in= file");
		}
	if (GETPARSTRING ("out","s",out)) {
		if ((outfd = open (out,2)) < 0)
		if ((outfd = creat (out,0664)) < 0) err ("cant open out= file");
		if ((outstream = fdopen (outfd,"a")) == NULL) err ("can't open out= file");
		}
#endif
/*	_core = core();*/
	GETPARINT ("memwatch","d",&memwatch);
	/* initialize objects */
	data = DataInit ();
	MovieInit ();
	render = RenderInit ();
	PlaneInit ();
	view = ViewInit (data);
	PickInit ();
	PikInit ();
	RegionInit ();
#if defined (HAVE_MOTIF)
	UIInit (sepxargc,sepxargv);
#endif
#if defined(XAW)
	UIInit ();
#endif
	/* interactive loop */
	UIMain ();
        return EXIT_SUCCESS;
	}

void MainFirst (void)
	{
	DrawInit ();
	ColorbarInit ();
	ColorInit ();
	RenderMap (render);
	DataLoad ();
#if defined(XAW) 
	ViewSize0 ();
#endif
	if (MovieRun()) MovieOn();
#ifdef SEPLIB
	hclose ();
#endif
	}

#ifdef SU
GETPARSTRING (name,type,var)
char *name, *type, *var;
	{
	char *str;
	int status;

	status = getparstring (name,&str);
	if (status) strcpy (var,str);
	return (status);
	}
#endif

static int core (void)
	{
	FILE *fd;
	string line;

	fgets(line,sizeof(line),fd=popen("/vol/admin/bin/physmem","r"));
	pclose (fd);
	return (atoi(line)*1024);
	}
#else
#include<seplib.h>
int main (int argc, char **argv)
  {
	fprintf(stderr,"Neaither motif or athena was speciefied \n");

        return(EXIT_FAILURE);
  }
#endif

