/*$

=head1 NAME

Ricksep - displays cubic array of data

=head1 SYNOPSIS

Ricksep in=datafile [ data pars ] [ display pars ]

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


=item esize       - integer  

      [1]  data samples are =1 for bytes or =4 for floats

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

=item nview       -int

       Number of views of the cube to simutaneously display

=item nview_dim  -int[2]

       [nview,1] The layout of the views 

=item view_ratiox - float[nview]

       [1./nview_dim[0]..]   The percentage of the screen (across) for each view

=item view_ratioy - float[nview]

       [1./nview_dim[1]..]   The percentage of the screen (down) for each view

=item norderx   - int[5] 

       [1,2,3,4,5]  The order to display the axes in a given view 
          

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

=item  'Main'  'Redraw' -- refresh damaged screen

=item  'Main'  'Write vgrid file (floats)' -- save data files as floats in 
               seplib/vgrid format

=item  'Main'  'Write vgrid file (bytes)' -- save data files as bytes in 
               seplib/vgrid format

=item  'Main'  'Write parameter restart file' -- create a parameter restart file

=item  'Main'  'Debug' -- dump various arrays for programmer debugging

=item  'Main'  'Quit'

=back

 

=head1 STYLE FUNCTIONS: Select a style and set attributes

=over 4

=item  'View'  'Front (2D)' -- Front face of data cube

=item  'View'  'Side (2D)' -- Side face of data cube

=item  'View'  'Top (2D)' -- Top face of data cube

=item  'View'  'Plan (2D)' -- All three cube faces

=item  'View'  'Array (3D) ...' -- Array of front faces- up to a hundred

=item  'View'  'Pick (3D) ...' -- Array of picked faces

=item  'View'  'Cube (3D)' -- Cube view

=item  'View'  'Fence (3D) ...' -- Show intersecting faces

=item  'View'  'Transparent (3D) ...' -- Transparent volume

=item  'Array Panel' 'Direction' <four axes> -- Select through direction

=item  'Array Panel' 'Down' -- Panels in down direction

=item  'Array Panel' 'Across' -- Panels in across direction

=item  'Array Panel' 'Start' -- First panel

=item  'Array Panel' 'Delta' -- Panel increment

=item  'Array Panel' 'End' -- Last panel; sets delta

=item  'Array Panel' 'Draw' -- Draw with new parameters

=item  'Array Panel' 'Close' -- Close control panel

=item  'Array Panel' 'LEFT MOUSE SELECTS PANEL RANGE

=item  'Fence Panel' 'Toggle Front' -- Toggle front plane on

=item  'Fence Panel' 'Toggle Side' -- Toggle side plane on

=item  'Fence Panel' 'Toggle Top' -- Toggle top plane on

=item  'Fence Panel' 'Transparency' -- Set transparency threshhold

=item  'Fence Panel' 'Draw' -- Draw with new parameters

=item  'Fence Panel' 'Close' -- Close control panel

=item  'Transparency Panel'  'Min' -- Set minimum transparency value

=item  'Transparency Panel'  'Max' -- Set maximum transparency value

=item  'Transparency Panel'  'Transp' -- Set transparency value

=item  'Transparency Panel'  'Draw altogether' -- Update screen once

=item  'Transparency Panel'  'Draw tenth blocks' -- Update screen ten times

=item  'Transparency Panel'  'Draw each plane' -- Update screen continuously

=item  'Transparency Panel'  'Draw' -- Draw with new parameters

=item  'Transparency Panel'  'Close' -- Close control panel

=back

 

=head1 ORIENT FUNCTIONS: change way axes point; 2-D are in-plane

=over 4

=item  'Orient'  'Side<->Top (2-D)' -- Rotate axes

=item  'Orient'  'Front<->Side (3-D)' -- Rotate axes

=item  'Orient'  'Top<->Front (3-D)' -- Rotate axes

=item  'Orient'  'Front<->Extra (4-D)' -- Rotate axes

=item  'Orient'  'Side<->Extra (4-D)' -- Rotate axes

=item  'Orient'  'Top<->Extra (4-D)' -- Rotate axes

=item  'Orient'  '<-Down-> (2-D)' -- Reversal

=item  'Orient'  '<-Across-> (2-D)' -- Reversal

=item  'Orient'  '<-Deep-> (3-D)' -- Reversal

=item  'Orient'  'Frames to Origin' -- Cross frames to start of origin of 
                 each axis

=item  'Orient'  'Frames in Middle' -- Cross frames in middle of each frame

=item  'Orient'  'Labels Set ..' -- Control panel to adjust labeling

=item  'Orient'  'Reset Initial'

=back

 

=head1 SIZE FUNCTIONS: set size and shape policy

=over 4

=item  'Size'  'Fit Screen' -- Front fills 2/3s screen; sides 1/3

=item  'Size'  'True Proportions'

=item  'Size'  'Sample per Pixel'

=item  'Size'  'Interpolate' -- Improves large magnifications

=item  'Size'  'Size Set ..' -- Launch size setting control panel

=item  'Size Set'  'Minimum' -- Minimum sample/value along axis

=item  'Size Set'  'Maximum' -- Maximum sample/value along axis

=item  'Size Set'  'Frame' -- Frame sample/value along axis

=item  'Size Set'  'Pixels' -- Pixels along axis

=item  'Size Set'  'Draw' -- Draw these size settings

=item  'Size Set'  'Current' -- Restore current size settings

=item  'Size Set'  'Initial' -- Fill in initial settings

=item  'Size Set'  'Close' -- Close size settings panel

=item  'Size'  'Reset Initial'

=item  'Size'  'LEFT MOUSE BOX ZOOMS' -- interactive magnification

=item  'Size'  '+ 'h' KEY ONLY HORZ' -- constrain to horizontal

=item  'Size'  '+ 'v' KEY ONLY VERT' -- constrain to vertical

=item  'Size'  'LEFT MOUSE CLICK ONLY' -- initial size

=back

 

=head1 MOVIE FUNCTIONS: go to part of the cube; run movies

=over 4

=item  'Navigate'  'Reset Bounds' -- Movie loop traverses full cross face

=item  'Navigate'  'High Speed' -- Frames are stored in displat terminal

=item  'Navigate' BUTTON 'GO' -- Start movie

=item  'Navigate' BUTTON 'NO' -- Stop movie

=item  'Navigate' BUTTON ' z ' -- Run/step in direction

=item  'Navigate' BUTTON ' Z ' -- Run/step out direction

=item  'Navigate' BUTTON ' < ' -- Run/step left direction

=item  'Navigate' BUTTON ' > ' -- Run/step right direction

=item  'Navigate' BUTTON ' ^ ' -- Run/step up direction

=item  'Navigate' BUTTON ' v ' -- Run/step down direction

=item  'Navigate' SLIDER ' Speed ' -- Delay between frames

=item  'Navigate'  'MIDDLE MOUSE CLICK Reset cross framesFRAMES' -- X

=item  'Navigate'  'MIDDLE MOUSE DRAG MOVIE BOUNDS' -- Set movie range

=back

 

=head1 COLOR FUNCTIONS: set color, contrast, and transparency

=over 4

=item  'Color' 'Gray' -- Grayscale

=item  'Color' 'Straw' -- Blue and yellow

=item  'Color' 'Flag' -- Red, white and blue

=item  'Color' 'Tiger' -- Red, white and black

=item  'Color' 'Blue' -- Blue and white

=item  'Color' 'Rainbow' -- Multi-colored

=item  'Color' 'Graybow' -- Gray plus multi-colored

=item  'Color' 'Overlay' <color-list> -- Overlay lines and text

=item  'Color' 'Mark' <color-list> -- Pick color

=item  'Color' 'Background' <color-list> -- Screen background color

=item  'Color' 'Flip Polarity' -- of data-> color

=item  'Color' 'Reset Contrast' -- No skew or zero point contrast

=item  'Color' SLIDER 'CONTRAST' -- Shift color table skew

=item  'Color' SLIDER 'CONTRAST0' -- Shift color table zero point

=item 'Color' BUTTON 'Reset' -- Reset initial contrast

=back

 

=head1 PICK FUNCTIONS: set picking behavior

=over 4

=item  'Pick'  'Clear Current Line' -- Erase pick line or sub-volume

=item  'Pick'  'Write pick file' -- Write to pick= now

=item  'Pick'  'Read pick file' -- Read from pick= now

=item  'Pick'  'RIGHT MOUSE MAKES PICK' -- right mouse button manipulates picks

=item  'Pick'  '+ 'a' KEY ADDS POINT TO END OF LINE'

=item  'Pick'  '+ 'i' KEY INSERTS POINT BETWEEN NEAREST POINTS'

=item  'Pick'  '+ 'm' KEY MOVES NEAREST POINT'

=item  'Pick'  '+ 'd' KEY DELETES NEAREST POINT'

=item  'Pick'  '+ 's' KEY + DRAGGING PICKS SUB-VOLUME'

=back

 

=head1 EDIT FUNCTIONS: edit grid sub-volume

=over 4

=item  'Edit'  'Clear Sub-volume pick' -- Clear current subvolume

=item  'Edit'  'Smooth Sub-volume' -- Smooth sub-volume to boundary value

=item  'Edit'  'Undo Smooth' -- Restore sub-volume

=item  'Edit'  'Grade Sub-volume' -- Grade sub-volume to boundary plane values

=item  'Edit'  'Undo grade'

=item  'Edit'  'Sub-volume Neighborhood' <6, 18, 26> -- Cube connectivity of 
               sub-volume

=item  'Edit'  'COLOR BAR MOUSE SETS SMOOTH RANGE'

=back

 

=head1 SECTION FUNCTION: plot various sections through the data

=over 4

=item  'Section' 'On screen wiggle plot ...' 'Front, side or top plane'

=item  'Section' 'On screen contour plot ...'  'Front, side or top plane'

=item  'Section' 'On screen graph profile ...' 'Down, across, or deep profile'

=item  'Section' 'Print wiggle plot ...' 'Front, side or top plane'

=item  'Section' 'Print contour plot ...'  'Front, side or top plane'

=item  'Section' 'Print graph profile ...' 'Down, across, or deep profile'

=item  'Section' 'Save section in file ...'  'Front, side or top plane'

=item  'Section' 'Save profile in file ...' 'Save down, across, or deep profile'

=item  'Section' 'PLANES AND PROFILES ARE SELECTED AT CROSS-HAIRS'

=back

 

=head1 STATUS FUNCTIONS: print parameters and state variables

=over 4

=item  'Status'  'Dataset' -- Dataset parameters

=item  'Status'  'Data Values' -- Data value parameters

=item  'Status'  'Data Axis0' -- Value/color axis

=item  'Status'  'Data Axis1' -- Fast axis, usually time

=item  'Status'  'Data Axis2' -- Second data axis, usually CDP

=item  'Status'  'Data Axis3' -- Slow axis, usually section

=item  'Status'  'Data Axis4' -- Slow axis, usually offset

=item  'Status'  'Data Axis5' -- Slow axis, unused

=item  'Status'  'View' -- View parameters

=item  'Status'  'Down Axis' -- View down axis parameters

=item  'Status'  'Across Axis' -- View across axis parameters

=item  'Status'  'Deep Axis' -- View deep axis parameters

=item  'Status'  'Extra Axis' -- View extra axis parameters

=item  'Status'  'Color Axis' -- Colorbar axis parameters

=item  'Status'  'Color' -- Color and contrast parameters

=item  'Status'  'Render' -- Rendering parameters

=item  'Status'  'Draw' -- Draw screen parameters

=item  'Status'  'Mouse Buttons' -- Mouse button functions

=item  'Status'  'Navigate' -- Movie parameters

=item  'Status'  'Pick' -- Pick parameters

=item  'Status'  'Pick List' -- Current pick line parameters

=item  'Status'  'sub-volume' -- Current mark sub-volume

=item  'Status'  'Frame List' -- List of screen frames

=back

 

=head1 HELP FUNCTIONS: print self documentation from various places

=over 4

=item  'Help'  'Command Line Args'

=item  'Help'  'File Formats'

=item  'Help'  'Windows'

=item  'Help'  'Mouse Usage'

=item  'Help'  'Main Functions'

=item  'Help'  'View Functions'

=item  'Help'  'Orient Functions'

=item  'Help'  'Size Functions'

=item  'Help'  'Navigate Functions'

=item  'Help'  'Color Functions'

=item  'Help'  'Picking Functions'

=item  'Help'  'Status Functions'

=back


=head1 NOTES

style, wide,hite,movie,shape,show_picks,across,down,
dacross,rate,fence,origin, and order should
reference multiple views with:

1st view: style
2nd view: style2
3rd view: style3

etc.



 

=head1 CATEGORY

B<interact> 

=cut
*/

/*
main program code
*/
#include <sepConfig.h>
#if defined (MOTIF_FOUND) || defined(HAVE_ATHENA)
#include "rick.h"
#if defined (HAVE_STDLIB_H)
#include<stdlib.h>
#else
extern int atoi();
#endif /* HAVE_STDLIB  */

#include <stdio.h>
#ifdef SEPLIB
#define OUT "/dev/null"
#include <seplib.h>
#endif

/* current dataset, render */
/*View view = 0;*/
int _core = 16*1024*1024;
int _alloc = 0;
int memwatch = 0;

int	sepxargc;
char	**sepxargv;
main (argc,argv)
int argc; char **argv;
	{
	extern int sepxargc;
	extern char **sepxargv, *help;
	extern string in, out;

#ifdef SEPLIB
        extern int sepxargc;
        extern char **sepxargv;
#endif
        extern char *help;
        extern string in, out;
                                                                                
#ifdef SEPLIB
        sepxargc = argc;
        sepxargv = argv;
        /* selfdoc */
        getch_add_string("head=/dev/null header=n HEAD=/dev/null");
        initpar (sepxargc,sepxargv);
sep_add_doc_line("NAME");
sep_add_doc_line("    Ricksep - displays cubic array of data");
sep_add_doc_line("");
sep_add_doc_line("SYNOPSIS");
sep_add_doc_line("    Ricksep in=datafile [ data pars ] [ display pars ]");
sep_add_doc_line("");
sep_add_doc_line("DESCRIPTION");
sep_add_doc_line("    Display cubic array of data in XWindows-Motif");
sep_add_doc_line("");
sep_add_doc_line("INPUT PARAMETERS");
sep_add_doc_line("    in - file");
sep_add_doc_line("              [stdin]    name of input file");
sep_add_doc_line("");
sep_add_doc_line("    n1,n2,n3..5 - integer");
sep_add_doc_line("              length of 3 dimensions, n1 is fastest, e.g. time");
sep_add_doc_line("");
sep_add_doc_line("    o1...o5 - float");
sep_add_doc_line("              [0.]first sample value in each dimension");
sep_add_doc_line("");
sep_add_doc_line("    d1...d5 - float");
sep_add_doc_line("              [1.]sample increment in each dimension");
sep_add_doc_line("");
sep_add_doc_line("    z1...z5 - integer");
sep_add_doc_line("              [1]relative spacing for true size, z3=3 means wide lines");
sep_add_doc_line("");
sep_add_doc_line("    label1..5 - char*");
sep_add_doc_line("              [n1]...[n5]label for each dimension");
sep_add_doc_line("");
sep_add_doc_line("    title - char*");
sep_add_doc_line("              [in]   dataset title");
sep_add_doc_line("");
sep_add_doc_line("    esize - integer");
sep_add_doc_line("              [1]  data samples are =1 for bytes or =4 for floats");
sep_add_doc_line("");
sep_add_doc_line("    pclip - integer");
sep_add_doc_line("              [255]  positive clip value; high= and clip= are synonyms");
sep_add_doc_line("");
sep_add_doc_line("    nclip - integer");
sep_add_doc_line("              [1]  negative clip value; low= and clip= are synonyms");
sep_add_doc_line("");
sep_add_doc_line("    value - char*");
sep_add_doc_line("              [sample] name for values on colorbar");
sep_add_doc_line("");
sep_add_doc_line("    width,height-integer");
sep_add_doc_line("              [600]pixel dimension (> 64) or fraction of screen (<= 1.0)");
sep_add_doc_line("");
sep_add_doc_line("    pick -file");
sep_add_doc_line("              pick line data file");
sep_add_doc_line("");
sep_add_doc_line("    npick -integer");
sep_add_doc_line("              [2500]maximum number of picks used");
sep_add_doc_line("");
sep_add_doc_line("    style -char*");
sep_add_doc_line("              [cube]view is front, side, top, plan, array, picks, cube, ");
sep_add_doc_line("              fence, or transparent");
sep_add_doc_line("");
sep_add_doc_line("    orient -char*");
sep_add_doc_line("              [front]    orient is front, side, top");
sep_add_doc_line("");
sep_add_doc_line("    origin -char*");
sep_add_doc_line("              [minimum]   frames set to middle or minimum");
sep_add_doc_line("");
sep_add_doc_line("    transp -integer");
sep_add_doc_line("              [0] if 1, transpose down and across");
sep_add_doc_line("");
sep_add_doc_line("    shape -char*");
sep_add_doc_line("              [fit]   shape fits screen, true, or pixel");
sep_add_doc_line("");
sep_add_doc_line("    movie -char*");
sep_add_doc_line("              [off] run movie in up, down, left, right, in, or out direction");
sep_add_doc_line("");
sep_add_doc_line("    color -char*");
sep_add_doc_line("              [gray]color is gray, straw, flag, tiger, blue, or rainbow");
sep_add_doc_line("");
sep_add_doc_line("    contrast -integer");
sep_add_doc_line("              [50]  contrast is between 0 and 100");
sep_add_doc_line("");
sep_add_doc_line("    font -char*");
sep_add_doc_line("              alternative XWindows font; default bold-courier-20");
sep_add_doc_line("");
sep_add_doc_line("    nview -int");
sep_add_doc_line("               Number of views of the cube to simutaneously display");
sep_add_doc_line("");
sep_add_doc_line("    nview_dim -int[2]");
sep_add_doc_line("               [nview,1] The layout of the views");
sep_add_doc_line("");
sep_add_doc_line("    view_ratiox - float[nview]");
sep_add_doc_line("               [1./nview_dim[0]..]   The percentage of the screen (across) for each view");
sep_add_doc_line("");
sep_add_doc_line("    view_ratioy - float[nview]");
sep_add_doc_line("               [1./nview_dim[1]..]   The percentage of the screen (down) for each view");
sep_add_doc_line("");
sep_add_doc_line("    norderx - int[5]");
sep_add_doc_line("               [1,2,3,4,5]  The order to display the axes in a given view");
sep_add_doc_line("");
sep_add_doc_line("DATA ARGUMENTS");
sep_add_doc_line("    in=datafile vgrid format - bytes or float with header");
sep_add_doc_line("    in=datafile n1= n2= n3= segy=1 segy/SU format - float traces with");
sep_add_doc_line("    headers");
sep_add_doc_line("    in=datafile n1= n2= n3= bytes format (SEPlib) - byte array without");
sep_add_doc_line("    header");
sep_add_doc_line("    in=datafile n1= n2= n3= esize=4 float format - float array without");
sep_add_doc_line("    header");
sep_add_doc_line("");
sep_add_doc_line("FILE FORMATS");
sep_add_doc_line("    seplib, bytes input data set: (user supplied)");
sep_add_doc_line("              2-D of 3-D array of unsigned byte integers 0-255.");
sep_add_doc_line("              Use segy2movie to convert segy.");
sep_add_doc_line("              Use Byte to convert seplib floating point.");
sep_add_doc_line("");
sep_add_doc_line("    seplib, float input data set: (user supplied)");
sep_add_doc_line("              2-D of 3-D array of float numbers");
sep_add_doc_line("");
sep_add_doc_line("    segy, su input data set: (user supplied)");
sep_add_doc_line("              Two dataset headers.");
sep_add_doc_line("              n2 x n3 segy traces.");
sep_add_doc_line("              Each trace 240 bytes + n1 IEEE floating point samples.");
sep_add_doc_line("              Use suread to convert tape dataset.");
sep_add_doc_line("");
sep_add_doc_line("    vgrid, (read or written by Movie).");
sep_add_doc_line("              cubic array of data.");
sep_add_doc_line("              100 byte tail describing dimensions.");
sep_add_doc_line("");
sep_add_doc_line("    script file: (user supplied)");
sep_add_doc_line("              Text file.");
sep_add_doc_line("              Each line of text annotates an n3 direction frame.");
sep_add_doc_line("");
sep_add_doc_line("    pick file: (generated by program or user supplied)");
sep_add_doc_line("              First line is dataset name.");
sep_add_doc_line("              Second line is dataset dimensions.");
sep_add_doc_line("              Third line are axes labels.");
sep_add_doc_line("              Followed by pick-lines:");
sep_add_doc_line("               First line is ID and frame.");
sep_add_doc_line("               Following lines are pick points:");
sep_add_doc_line("                three coordinates and data value.");
sep_add_doc_line("");
sep_add_doc_line("    par file: (user supplied or generated by Save State menu)");
sep_add_doc_line("              List of parameters in name=value form. Free format.");
sep_add_doc_line("              Last of duplicates used.");
sep_add_doc_line("");
sep_add_doc_line("WINDOWS");
sep_add_doc_line("    (1) Menubar on top.");
sep_add_doc_line("    (2) Message window below menubar.");
sep_add_doc_line("    (3) Control panel below message window.");
sep_add_doc_line("    (4) Color spectrum below control panel. Line shows relative data sample");
sep_add_doc_line("    distribution. Bar shows last pick value or range of values. Mouse");
sep_add_doc_line("    click-drag-up specifies a value range.");
sep_add_doc_line("    (5) Resizable image window. Responds to following mouse clicks:");
sep_add_doc_line("");
sep_add_doc_line("MOUSE USAGE");
sep_add_doc_line("    LEFT: zoom; MIDDLE: navigate; RIGHT: pick.");
sep_add_doc_line("    LEFT click-drag-up: zoom window.");
sep_add_doc_line("    LEFT click only: initial size.");
sep_add_doc_line("    LEFT click-drag-up + 'h' key: zoom horizontal only.");
sep_add_doc_line("    LEFT click-drag-up + 'v' key: zoom vertical only.");
sep_add_doc_line("    LEFT click-drag-up in ARRAY window: those panels.");
sep_add_doc_line("    MIDDLE click: select cross frames.");
sep_add_doc_line("    MIDDLE click-drag-up: select an animation range.");
sep_add_doc_line("    RIGHT click: pick a point on the image.");
sep_add_doc_line("    RIGHT click + 'a' key: add a point to end of pick line.");
sep_add_doc_line("    RIGHT click + 'm' key: move nearest point in pick line.");
sep_add_doc_line("    RIGHT click + 'd' key: delete nearest point in pick line.");
sep_add_doc_line("    RIGHT click-drag-up + 's' key:select seed point & sub-volume pick");
sep_add_doc_line("    bounds.");
sep_add_doc_line("    COLORBAR ANY click-drag-up: replace sub-volume range with this new");
sep_add_doc_line("    range.");
sep_add_doc_line("");
sep_add_doc_line("INTERACTIVE CONTROLS");
sep_add_doc_line("MAIN FUNCTIONS: Interface to system");
sep_add_doc_line("    'Main' 'Redraw' -- refresh damaged screen");
sep_add_doc_line("    'Main' 'Write vgrid file (floats)' -- save data files as floats in");
sep_add_doc_line("    seplib/vgrid format");
sep_add_doc_line("    'Main' 'Write vgrid file (bytes)' -- save data files as bytes in");
sep_add_doc_line("    seplib/vgrid format");
sep_add_doc_line("    'Main' 'Write parameter restart file' -- create a parameter restart file");
sep_add_doc_line("    'Main' 'Debug' -- dump various arrays for programmer debugging");
sep_add_doc_line("    'Main' 'Quit'");
sep_add_doc_line("");
sep_add_doc_line("STYLE FUNCTIONS: Select a style and set attributes");
sep_add_doc_line("    'View' 'Front (2D)' -- Front face of data cube");
sep_add_doc_line("    'View' 'Side (2D)' -- Side face of data cube");
sep_add_doc_line("    'View' 'Top (2D)' -- Top face of data cube");
sep_add_doc_line("    'View' 'Plan (2D)' -- All three cube faces");
sep_add_doc_line("    'View' 'Array (3D) ...' -- Array of front faces- up to a hundred");
sep_add_doc_line("    'View' 'Pick (3D) ...' -- Array of picked faces");
sep_add_doc_line("    'View' 'Cube (3D)' -- Cube view");
sep_add_doc_line("    'View' 'Fence (3D) ...' -- Show intersecting faces");
sep_add_doc_line("    'View' 'Transparent (3D) ...' -- Transparent volume");
sep_add_doc_line("    'Array Panel' 'Direction' <four axes> -- Select through direction");
sep_add_doc_line("    'Array Panel' 'Down' -- Panels in down direction");
sep_add_doc_line("    'Array Panel' 'Across' -- Panels in across direction");
sep_add_doc_line("    'Array Panel' 'Start' -- First panel");
sep_add_doc_line("    'Array Panel' 'Delta' -- Panel increment");
sep_add_doc_line("    'Array Panel' 'End' -- Last panel; sets delta");
sep_add_doc_line("    'Array Panel' 'Draw' -- Draw with new parameters");
sep_add_doc_line("    'Array Panel' 'Close' -- Close control panel");
sep_add_doc_line("    'Array Panel' 'LEFT MOUSE SELECTS PANEL RANGE");
sep_add_doc_line("    'Fence Panel' 'Toggle Front' -- Toggle front plane on");
sep_add_doc_line("    'Fence Panel' 'Toggle Side' -- Toggle side plane on");
sep_add_doc_line("    'Fence Panel' 'Toggle Top' -- Toggle top plane on");
sep_add_doc_line("    'Fence Panel' 'Transparency' -- Set transparency threshhold");
sep_add_doc_line("    'Fence Panel' 'Draw' -- Draw with new parameters");
sep_add_doc_line("    'Fence Panel' 'Close' -- Close control panel");
sep_add_doc_line("    'Transparency Panel' 'Min' -- Set minimum transparency value");
sep_add_doc_line("    'Transparency Panel' 'Max' -- Set maximum transparency value");
sep_add_doc_line("    'Transparency Panel' 'Transp' -- Set transparency value");
sep_add_doc_line("    'Transparency Panel' 'Draw altogether' -- Update screen once");
sep_add_doc_line("    'Transparency Panel' 'Draw tenth blocks' -- Update screen ten times");
sep_add_doc_line("    'Transparency Panel' 'Draw each plane' -- Update screen continuously");
sep_add_doc_line("    'Transparency Panel' 'Draw' -- Draw with new parameters");
sep_add_doc_line("    'Transparency Panel' 'Close' -- Close control panel");
sep_add_doc_line("");
sep_add_doc_line("ORIENT FUNCTIONS: change way axes point; 2-D are in-plane");
sep_add_doc_line("    'Orient' 'Side<->Top (2-D)' -- Rotate axes");
sep_add_doc_line("    'Orient' 'Front<->Side (3-D)' -- Rotate axes");
sep_add_doc_line("    'Orient' 'Top<->Front (3-D)' -- Rotate axes");
sep_add_doc_line("    'Orient' 'Front<->Extra (4-D)' -- Rotate axes");
sep_add_doc_line("    'Orient' 'Side<->Extra (4-D)' -- Rotate axes");
sep_add_doc_line("    'Orient' 'Top<->Extra (4-D)' -- Rotate axes");
sep_add_doc_line("    'Orient' '<-Down-> (2-D)' -- Reversal");
sep_add_doc_line("    'Orient' '<-Across-> (2-D)' -- Reversal");
sep_add_doc_line("    'Orient' '<-Deep-> (3-D)' -- Reversal");
sep_add_doc_line("    'Orient' 'Frames to Origin' -- Cross frames to start of origin of each");
sep_add_doc_line("    axis");
sep_add_doc_line("    'Orient' 'Frames in Middle' -- Cross frames in middle of each frame");
sep_add_doc_line("    'Orient' 'Labels Set ..' -- Control panel to adjust labeling");
sep_add_doc_line("    'Orient' 'Reset Initial'");
sep_add_doc_line("");
sep_add_doc_line("SIZE FUNCTIONS: set size and shape policy");
sep_add_doc_line("    'Size' 'Fit Screen' -- Front fills 2/3s screen; sides 1/3");
sep_add_doc_line("    'Size' 'True Proportions'");
sep_add_doc_line("    'Size' 'Sample per Pixel'");
sep_add_doc_line("    'Size' 'Interpolate' -- Improves large magnifications");
sep_add_doc_line("    'Size' 'Size Set ..' -- Launch size setting control panel");
sep_add_doc_line("    'Size Set' 'Minimum' -- Minimum sample/value along axis");
sep_add_doc_line("    'Size Set' 'Maximum' -- Maximum sample/value along axis");
sep_add_doc_line("    'Size Set' 'Frame' -- Frame sample/value along axis");
sep_add_doc_line("    'Size Set' 'Pixels' -- Pixels along axis");
sep_add_doc_line("    'Size Set' 'Draw' -- Draw these size settings");
sep_add_doc_line("    'Size Set' 'Current' -- Restore current size settings");
sep_add_doc_line("    'Size Set' 'Initial' -- Fill in initial settings");
sep_add_doc_line("    'Size Set' 'Close' -- Close size settings panel");
sep_add_doc_line("    'Size' 'Reset Initial'");
sep_add_doc_line("    'Size' 'LEFT MOUSE BOX ZOOMS' -- interactive magnification");
sep_add_doc_line("    'Size' '+ 'h' KEY ONLY HORZ' -- constrain to horizontal");
sep_add_doc_line("    'Size' '+ 'v' KEY ONLY VERT' -- constrain to vertical");
sep_add_doc_line("    'Size' 'LEFT MOUSE CLICK ONLY' -- initial size");
sep_add_doc_line("");
sep_add_doc_line("MOVIE FUNCTIONS: go to part of the cube; run movies");
sep_add_doc_line("    'Navigate' 'Reset Bounds' -- Movie loop traverses full cross face");
sep_add_doc_line("    'Navigate' 'High Speed' -- Frames are stored in displat terminal");
sep_add_doc_line("    'Navigate' BUTTON 'GO' -- Start movie");
sep_add_doc_line("    'Navigate' BUTTON 'NO' -- Stop movie");
sep_add_doc_line("    'Navigate' BUTTON ' z ' -- Run/step in direction");
sep_add_doc_line("    'Navigate' BUTTON ' Z ' -- Run/step out direction");
sep_add_doc_line("    'Navigate' BUTTON ' < ' -- Run/step left direction");
sep_add_doc_line("    'Navigate' BUTTON ' > ' -- Run/step right direction");
sep_add_doc_line("    'Navigate' BUTTON ' ^ ' -- Run/step up direction");
sep_add_doc_line("    'Navigate' BUTTON ' v ' -- Run/step down direction");
sep_add_doc_line("    'Navigate' SLIDER ' Speed ' -- Delay between frames");
sep_add_doc_line("    'Navigate' 'MIDDLE MOUSE CLICK Reset cross framesFRAMES' -- X");
sep_add_doc_line("    'Navigate' 'MIDDLE MOUSE DRAG MOVIE BOUNDS' -- Set movie range");
sep_add_doc_line("");
sep_add_doc_line("COLOR FUNCTIONS: set color, contrast, and transparency");
sep_add_doc_line("    'Color' 'Gray' -- Grayscale");
sep_add_doc_line("    'Color' 'Straw' -- Blue and yellow");
sep_add_doc_line("    'Color' 'Flag' -- Red, white and blue");
sep_add_doc_line("    'Color' 'Tiger' -- Red, white and black");
sep_add_doc_line("    'Color' 'Blue' -- Blue and white");
sep_add_doc_line("    'Color' 'Rainbow' -- Multi-colored");
sep_add_doc_line("    'Color' 'Graybow' -- Gray plus multi-colored");
sep_add_doc_line("    'Color' 'Overlay' <color-list> -- Overlay lines and text");
sep_add_doc_line("    'Color' 'Mark' <color-list> -- Pick color");
sep_add_doc_line("    'Color' 'Background' <color-list> -- Screen background color");
sep_add_doc_line("    'Color' 'Flip Polarity' -- of data-> color");
sep_add_doc_line("    'Color' 'Reset Contrast' -- No skew or zero point contrast");
sep_add_doc_line("    'Color' SLIDER 'CONTRAST' -- Shift color table skew");
sep_add_doc_line("    'Color' SLIDER 'CONTRAST0' -- Shift color table zero point");
sep_add_doc_line("    'Color' BUTTON 'Reset' -- Reset initial contrast");
sep_add_doc_line("");
sep_add_doc_line("PICK FUNCTIONS: set picking behavior");
sep_add_doc_line("    'Pick' 'Clear Current Line' -- Erase pick line or sub-volume");
sep_add_doc_line("    'Pick' 'Write pick file' -- Write to pick= now");
sep_add_doc_line("    'Pick' 'Read pick file' -- Read from pick= now");
sep_add_doc_line("    'Pick' 'RIGHT MOUSE MAKES PICK' -- right mouse button manipulates picks");
sep_add_doc_line("    'Pick' '+ 'a' KEY ADDS POINT TO END OF LINE'");
sep_add_doc_line("    'Pick' '+ 'i' KEY INSERTS POINT BETWEEN NEAREST POINTS'");
sep_add_doc_line("    'Pick' '+ 'm' KEY MOVES NEAREST POINT'");
sep_add_doc_line("    'Pick' '+ 'd' KEY DELETES NEAREST POINT'");
sep_add_doc_line("    'Pick' '+ 's' KEY + DRAGGING PICKS SUB-VOLUME'");
sep_add_doc_line("");
sep_add_doc_line("EDIT FUNCTIONS: edit grid sub-volume");
sep_add_doc_line("    'Edit' 'Clear Sub-volume pick' -- Clear current subvolume");
sep_add_doc_line("    'Edit' 'Smooth Sub-volume' -- Smooth sub-volume to boundary value");
sep_add_doc_line("    'Edit' 'Undo Smooth' -- Restore sub-volume");
sep_add_doc_line("    'Edit' 'Grade Sub-volume' -- Grade sub-volume to boundary plane values");
sep_add_doc_line("    'Edit' 'Undo grade'");
sep_add_doc_line("    'Edit' 'Sub-volume Neighborhood' <6, 18, 26> -- Cube connectivity of");
sep_add_doc_line("    sub-volume");
sep_add_doc_line("    'Edit' 'COLOR BAR MOUSE SETS SMOOTH RANGE'");
sep_add_doc_line("");
sep_add_doc_line("SECTION FUNCTION: plot various sections through the data");
sep_add_doc_line("    'Section' 'On screen wiggle plot ...' 'Front, side or top plane'");
sep_add_doc_line("    'Section' 'On screen contour plot ...' 'Front, side or top plane'");
sep_add_doc_line("    'Section' 'On screen graph profile ...' 'Down, across, or deep profile'");
sep_add_doc_line("    'Section' 'Print wiggle plot ...' 'Front, side or top plane'");
sep_add_doc_line("    'Section' 'Print contour plot ...' 'Front, side or top plane'");
sep_add_doc_line("    'Section' 'Print graph profile ...' 'Down, across, or deep profile'");
sep_add_doc_line("    'Section' 'Save section in file ...' 'Front, side or top plane'");
sep_add_doc_line("    'Section' 'Save profile in file ...' 'Save down, across, or deep");
sep_add_doc_line("    profile'");
sep_add_doc_line("    'Section' 'PLANES AND PROFILES ARE SELECTED AT CROSS-HAIRS'");
sep_add_doc_line("");
sep_add_doc_line("STATUS FUNCTIONS: print parameters and state variables");
sep_add_doc_line("    'Status' 'Dataset' -- Dataset parameters");
sep_add_doc_line("    'Status' 'Data Values' -- Data value parameters");
sep_add_doc_line("    'Status' 'Data Axis0' -- Value/color axis");
sep_add_doc_line("    'Status' 'Data Axis1' -- Fast axis, usually time");
sep_add_doc_line("    'Status' 'Data Axis2' -- Second data axis, usually CDP");
sep_add_doc_line("    'Status' 'Data Axis3' -- Slow axis, usually section");
sep_add_doc_line("    'Status' 'Data Axis4' -- Slow axis, usually offset");
sep_add_doc_line("    'Status' 'Data Axis5' -- Slow axis, unused");
sep_add_doc_line("    'Status' 'View' -- View parameters");
sep_add_doc_line("    'Status' 'Down Axis' -- View down axis parameters");
sep_add_doc_line("    'Status' 'Across Axis' -- View across axis parameters");
sep_add_doc_line("    'Status' 'Deep Axis' -- View deep axis parameters");
sep_add_doc_line("    'Status' 'Extra Axis' -- View extra axis parameters");
sep_add_doc_line("    'Status' 'Color Axis' -- Colorbar axis parameters");
sep_add_doc_line("    'Status' 'Color' -- Color and contrast parameters");
sep_add_doc_line("    'Status' 'Render' -- Rendering parameters");
sep_add_doc_line("    'Status' 'Draw' -- Draw screen parameters");
sep_add_doc_line("    'Status' 'Mouse Buttons' -- Mouse button functions");
sep_add_doc_line("    'Status' 'Navigate' -- Movie parameters");
sep_add_doc_line("    'Status' 'Pick' -- Pick parameters");
sep_add_doc_line("    'Status' 'Pick List' -- Current pick line parameters");
sep_add_doc_line("    'Status' 'sub-volume' -- Current mark sub-volume");
sep_add_doc_line("    'Status' 'Frame List' -- List of screen frames");
sep_add_doc_line("");
sep_add_doc_line("HELP FUNCTIONS: print self documentation from various places");
sep_add_doc_line("    'Help' 'Command Line Args'");
sep_add_doc_line("    'Help' 'File Formats'");
sep_add_doc_line("    'Help' 'Windows'");
sep_add_doc_line("    'Help' 'Mouse Usage'");
sep_add_doc_line("    'Help' 'Main Functions'");
sep_add_doc_line("    'Help' 'View Functions'");
sep_add_doc_line("    'Help' 'Orient Functions'");
sep_add_doc_line("    'Help' 'Size Functions'");
sep_add_doc_line("    'Help' 'Navigate Functions'");
sep_add_doc_line("    'Help' 'Color Functions'");
sep_add_doc_line("    'Help' 'Picking Functions'");
sep_add_doc_line("    'Help' 'Status Functions'");
sep_add_doc_line("");
sep_add_doc_line("NOTES");
sep_add_doc_line("    style, wide,hite,movie,shape,show_picks,across,down,");
sep_add_doc_line("    dacross,rate,fence,origin, and order should reference multiple views");
sep_add_doc_line("    with:");
sep_add_doc_line("");
sep_add_doc_line("    1st view: style 2nd view: style2 3rd view: style3");
sep_add_doc_line("");
sep_add_doc_line("    etc.");
sep_add_doc_line("");
sep_add_doc_line("CATEGORY");
sep_add_doc_line("    interact");
sep_add_doc_line("");

        doc(""/*SOURCE*/);
#else
      initargs(argc,argv);
        requestdoc(0);
#endif
                                                                                
	rick_getch ("memwatch","d",&memwatch);
	/* initialize objects */
	DataInit ();
	ViewsInit ();
	MovieInit ();
	RenderInit ();
	PlaneInit ();
	PickInit ();
	PikInit ();
	AnoInit ();
	RegionInit ();
	set_data_lists();
#if defined (MOTIF_FOUND)
	UIInit (sepxargc,sepxargv);
#endif
#if defined(XAW)
	UIInit ();
#endif
	/* interactive loop */
	UIMain ();
  return(0);
	}

void MainFirst ()
	{
 int i;
	View myv;

	DrawInit ();
	ColorbarInit ();
	ColorInit ();
	RenderMap ();
	DataLoad ();
#if defined(XAW) 
	ViewSize0 ();
#endif

	 



	if (MovieRun()) MovieOn();
#ifdef SEPLIB
/*	hclose ();*/
#endif
	}


core ()
	{
	FILE *fd;
	string line;

	fgets(line,sizeof(line),fd=popen("/vol/admin/bin/physmem","r"));
	pclose (fd);
	return (atoi(line)*1024);
	}
#else
#include<seplib.h>
main (argc,argv)
int argc; char **argv;
  {
	fprintf(stderr,"Neaither motif or athena was speciefied \n");

	}
#endif

