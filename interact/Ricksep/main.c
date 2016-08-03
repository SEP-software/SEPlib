/*
main program code
*/
#include <sitedef.h>
#if defined (HAVE_MOTIF) || defined(HAVE_ATHENA)
#include <sitedef.h>
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
  sep_add_doc_line("              [stdin] name of input file");
  sep_add_doc_line("");
  sep_add_doc_line("    n1,n2,n3..n5 - integer");
  sep_add_doc_line("              lengths of 3 dimensions, n1 is fastest, e.g. time");
  sep_add_doc_line("");
  sep_add_doc_line("    o1...o5 - float");
  sep_add_doc_line("              [0.] first sample value in each dimension");
  sep_add_doc_line("");
  sep_add_doc_line("    d1...d5 - float");
  sep_add_doc_line("              [1.] sample increment in each dimension");
  sep_add_doc_line("");
  sep_add_doc_line("    z1...z5 - integer");
  sep_add_doc_line("              [1] relative spacing for true size, z3=3 means wide lines");
  sep_add_doc_line("");
  sep_add_doc_line("    label1..5 - char*");
  sep_add_doc_line("              [n1]...[n5] label for each dimension");
  sep_add_doc_line("");
  sep_add_doc_line("    title - char*");
  sep_add_doc_line("              [in] dataset title");
  sep_add_doc_line("");
  sep_add_doc_line("    esize - integer");
  sep_add_doc_line("              [1] data samples are =1 for bytes or =4 for floats");
  sep_add_doc_line("");
  sep_add_doc_line("    pclip - integer");
  sep_add_doc_line("              [255] positive clip value; high= and clip= are synonyms");
  sep_add_doc_line("");
  sep_add_doc_line("    nclip - integer");
  sep_add_doc_line("              [1] negative clip value; low= and clip= are synonyms");
  sep_add_doc_line("");
  sep_add_doc_line("    value - char*");
  sep_add_doc_line("              [sample] name for values on colorbar");
  sep_add_doc_line("");
  sep_add_doc_line("    width,height-integer");
  sep_add_doc_line("              [600] pixel dimension (> 64) or fraction of screen (<= 1.0)");
  sep_add_doc_line("");
  sep_add_doc_line("    pick -file");
  sep_add_doc_line("              pick line data file");
  sep_add_doc_line("");
  sep_add_doc_line("    npick -integer");
  sep_add_doc_line("              [2500]maximum number of picks used");
  sep_add_doc_line("");
  sep_add_doc_line("    style -char*");
  sep_add_doc_line("              [cube] view is front, side, top, plan, array, picks, cube, ");
  sep_add_doc_line("              fence, or transparent");
  sep_add_doc_line("");
  sep_add_doc_line("    orient -char*");
  sep_add_doc_line("              [front] orient is front, side, top");
  sep_add_doc_line("");
  sep_add_doc_line("    origin -char*");
  sep_add_doc_line("              [minimum] frames set to middle or minimum");
  sep_add_doc_line("");
  sep_add_doc_line("    transp -integer");
  sep_add_doc_line("              [0] if 1, transpose down and across");
  sep_add_doc_line("");
  sep_add_doc_line("    shape -char*");
  sep_add_doc_line("              [fit] shape fits screen, true, or pixel");
  sep_add_doc_line("");
  sep_add_doc_line("    movie -char*");
  sep_add_doc_line("              [off] run movie in up, down, left, right, in, or out direction");
  sep_add_doc_line("");
  sep_add_doc_line("    color -char*");
  sep_add_doc_line("              [gray] color is gray, straw, flag, tiger, blue, or rainbow");
  sep_add_doc_line("");
  sep_add_doc_line("    contrast -integer");
  sep_add_doc_line("              [50] contrast is between 0 and 100");
  sep_add_doc_line("");
  sep_add_doc_line("    font -char*");
  sep_add_doc_line("              alternative XWindows font; default bold-courier-20");
  sep_add_doc_line("");
  sep_add_doc_line("    nview -int");
  sep_add_doc_line("               Number of views of the cube to simutaneously display");
  sep_add_doc_line("");
  sep_add_doc_line("    nview_dim -int[2]");
  sep_add_doc_line("               [nview,1] The layout of the views ");
  sep_add_doc_line("");
  sep_add_doc_line("    view_ratiox - float[nview]");
  sep_add_doc_line("               [1./nview_dim[0]..] The percentage of the screen (across) for each view");
  sep_add_doc_line("");
  sep_add_doc_line("    view_ratioy - float[nview]");
  sep_add_doc_line("               [1./nview_dim[1]..] The percentage of the screen (down) for each view");
  sep_add_doc_line("");
  sep_add_doc_line("    norderx - int[5]");
  sep_add_doc_line("               [1,2,3,4,5] The order to display the axes in a given view ");
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
  sep_add_doc_line("    'Main' 'Redraw' -- refresh screen");
  sep_add_doc_line("    'Main' 'Fix Picking -- fix pick changes");
  sep_add_doc_line("    'Main' 'Write Vgrid File (floats)' -- save data files as floats");
  sep_add_doc_line("    'Main' 'Write Vgrid File (bytes)' -- save data files as bytes");
  sep_add_doc_line("    'Main' 'Write Parameter Restart File' -- create a parameter restart file");
  sep_add_doc_line("    'Main' 'Write History File' -- save history list");
  sep_add_doc_line("    'Main' 'Load History File' -- load history list");
  sep_add_doc_line("    'Main' 'Quit'");
  sep_add_doc_line("");
 
  sep_add_doc_line("VIEW FUNCTIONS: select a style and set attributes");
  sep_add_doc_line("    'View' 'Front Face (2D)' -- front face of data cube");
  sep_add_doc_line("    'View' 'Side Face (2D)' -- side face of data cube");
  sep_add_doc_line("    'View' 'Top Face (2D)' -- top face of data cube");
  sep_add_doc_line("    'View' 'Three Faces (2D)' -- all three cube faces");
  sep_add_doc_line("    'View' 'Cube (3D)' -- cube view");
  sep_add_doc_line("    'View' 'Array (3D) ...' -- array of front faces- up to a hundred");
  sep_add_doc_line("    'View' 'Fence (3D) ...' -- show intersecting faces");
  sep_add_doc_line("    'View' 'Transparent Cube (3D) ...' -- transparent volume");
  sep_add_doc_line("    'View' 'Round Robin On/Off' -- collapse multiple views into one view");
  sep_add_doc_line("    'View' 'Next View' -- show next view");
  sep_add_doc_line("    'View' 'Previous View' -- show previous view");
  sep_add_doc_line("    'View' 'Round Robin' KEY 'Shift' + 'r' -- turn feature on/off");
  sep_add_doc_line("    'View' 'Round Robin' KEY '>' -- show next view");
  sep_add_doc_line("    'View' 'Round Robin' KEY '<' -- show previous view");
  sep_add_doc_line("    'Array Panel' 'Direction' <four axes> -- select traversal direction");
  sep_add_doc_line("    'Array Panel' 'ACROSS' -- panels in across direction");
  sep_add_doc_line("    'Array Panel' 'DOWN' -- panels in down direction");
  sep_add_doc_line("    'Array Panel' 'START' -- first panel");
  sep_add_doc_line("    'Array Panel' 'DELTA' -- panel increment");
  sep_add_doc_line("    'Array Panel' 'END' -- last panel; sets delta");
  sep_add_doc_line("    'Array Panel' 'DRAW' -- draw with new parameters");
  sep_add_doc_line("    'Array Panel' 'CLOSE' -- close control panel");
  sep_add_doc_line("    'Array Panel' 'LEFT MOUSE SELECTS PANEL RANGE");
  sep_add_doc_line("    'Fence Panel' 'Toggle Front' -- toggle front plane on");
  sep_add_doc_line("    'Fence Panel' 'Toggle Side' -- toggle side plane on");
  sep_add_doc_line("    'Fence Panel' 'Toggle Top' -- toggle top plane on");
  sep_add_doc_line("    'Fence Panel' 'Transparency' -- set transparency threshhold");
  sep_add_doc_line("    'Fence Panel' 'Draw' -- draw with new parameters");
  sep_add_doc_line("    'Fence Panel' 'Close' -- close control panel");
  sep_add_doc_line("    'Transparency Panel' 'Min' -- set minimum transparency value");
  sep_add_doc_line("    'Transparency Panel' 'Max' -- set maximum transparency value");
  sep_add_doc_line("    'Transparency Panel' 'Transp' -- set transparency value");
  sep_add_doc_line("    'Transparency Panel' 'Draw altogether' -- update screen once");
  sep_add_doc_line("    'Transparency Panel' 'Draw tenth blocks' -- update screen ten times");
  sep_add_doc_line("    'Transparency Panel' 'Draw each plane' -- update screen continuously");
  sep_add_doc_line("    'Transparency Panel' 'Draw' -- draw with new parameters");
  sep_add_doc_line("    'Transparency Panel' 'Close' -- xlose control panel");
  sep_add_doc_line("");
  
  sep_add_doc_line("ORIENT FUNCTIONS: change way axes point; 2-D are in-plane");
  sep_add_doc_line("    'Orient' 'Swap Side & Top Faces(12)' -- rotate axes");
  sep_add_doc_line("    'Orient' 'Swap Front & Side Faces(23)' -- rotate axes");
  sep_add_doc_line("    'Orient' 'Swap Top & Front Faces(13)' -- rotate axes");
  sep_add_doc_line("    'Orient' 'Swap Deep & 4th Axes(14)' -- rotate axes");
  sep_add_doc_line("    'Orient' 'Swap Across & 4th Axes(24)' -- rotate axes");
  sep_add_doc_line("    'Orient' 'Swap Down & 4th Axes(34)' -- rotate axes");
  sep_add_doc_line("    'Orient' 'Swap Deep & 5th Axes(15)' -- rotate axes");
  sep_add_doc_line("    'Orient' 'Swap Across & 5th Axes(25)' -- rotate axes");
  sep_add_doc_line("    'Orient' 'Swap Down & 5th Axes(35)' -- rotate axes");
  sep_add_doc_line("    'Orient' 'Orientation Menu' -- launch orientation panel");
  sep_add_doc_line("    'Orient' 'Flip Down Direction' -- reversal");
  sep_add_doc_line("    'Orient' 'Flip Across Direction' -- reversal");
  sep_add_doc_line("    'Orient' 'Flip Deep Direction' -- reversal");
  sep_add_doc_line("    'Orient' 'Move Frames to Middle' -- cross frames to middle of each axis");
  sep_add_doc_line("    'Orient' 'Move Frames to Corner' -- cross frames to origin of each axis");
  sep_add_doc_line("    'Orient' 'Initial Orientation' -- revert");
  sep_add_doc_line("    'Orient' 'Adjust Labels ...' -- change axes' labels");
  sep_add_doc_line("");
  
  sep_add_doc_line("SIZE FUNCTIONS: set size and shape policy");
  sep_add_doc_line("    'Size' 'Even Cube' -- front fills 2/3 screen, sides 1/3");
  sep_add_doc_line("    'Size' 'True Proportions' -- show cube with true dimensions");
  sep_add_doc_line("    'Size' 'Sample Per Pixel' -- guarantee one sample per pixel");
  sep_add_doc_line("    'Size' 'Interpolate' -- improves large magnifications");
  sep_add_doc_line("    'Size' 'Fine Control ...' -- launch size parameters panel");
  sep_add_doc_line("    'Size' 'Initial Size'");
  sep_add_doc_line("    'Size' 'LEFT MOUSE BOX ZOOMS' -- interactive magnification");
  sep_add_doc_line("    'Size' '+ 'h' KEY ONLY HORZ' -- constrain to horizontal");
  sep_add_doc_line("    'Size' '+ 'v' KEY ONLY VERT' -- constrain to vertical");
  sep_add_doc_line("    'Size' 'LEFT MOUSE CLICK ONLY' -- initial size");
  sep_add_doc_line("    'Size Parameters Panel' 'Minimum' -- minimum sample/value along axis");
  sep_add_doc_line("    'Size Parameters Panel' 'Maximum' -- maximum sample/value along axis");
  sep_add_doc_line("    'Size Parameters Panel' 'Frame' -- frame sample/value along axis");
  sep_add_doc_line("    'Size Parameters Panel' 'Pixels' -- number of pixels along axis");
  sep_add_doc_line("    'Size Parameters Panel' 'Draw' -- draw using these size settings");
  sep_add_doc_line("    'Size Parameters Panel' 'Restore' -- restore current size settings");
  sep_add_doc_line("    'Size Parameters Panel' 'Initial' -- fill in initial settings");
  sep_add_doc_line("    'Size Parameters Panel' 'Close'");
  sep_add_doc_line("");
  
  sep_add_doc_line("NAVIGATE FUNCTIONS: go to part of the cube; run movies");
  sep_add_doc_line("    'Navigate' 'Movie to Boundaries' -- movie loop traverses full cross face");
  sep_add_doc_line("    'Navigate' 'High Speed' -- frames are stored in display terminal");
  sep_add_doc_line("    'Navigate' 'Undo Move' -- undo last command");
  sep_add_doc_line("    'Navigate' 'Redo Move' -- redo last undone command");
  sep_add_doc_line("    'Navigate' 'Undo to Start' -- undo to start of history list");
  sep_add_doc_line("    'Navigate' 'Redo to End' -- redo to end of history list");
  sep_add_doc_line("    'Navigate' 'Animate Undo to Start' -- play movie undo sequence");
  sep_add_doc_line("    'Navigate' 'Animate Redo to End' -- play movie redo sequence");
  sep_add_doc_line("    'Navigate' 'Pause Animation' -- stop movie");
  sep_add_doc_line("    'Navigate' BUTTON 'GO' -- start movie");
  sep_add_doc_line("    'Navigate' BUTTON 'NO' -- stop movie");
  sep_add_doc_line("    'Navigate' BUTTON 'z' -- run/step out direction");
  sep_add_doc_line("    'Navigate' BUTTON 'Z' -- run/step in direction");
  sep_add_doc_line("    'Navigate' BUTTON 'x' -- run/step left direction");
  sep_add_doc_line("    'Navigate' BUTTON 'X' -- run/step right direction");
  sep_add_doc_line("    'Navigate' BUTTON 'y' -- run/step up direction");
  sep_add_doc_line("    'Navigate' BUTTON 'Y' -- run/step down direction");
  sep_add_doc_line("    'Navigate' SLIDER 'Speed' -- animation delay (right=faster)");
  sep_add_doc_line("    'Navigate' 'MIDDLE MOUSE CLICK XFRAMES' -- moves cross frames");
  sep_add_doc_line("    'Navigate' 'MIDDLE MOUSE DRAG MOVIE BOUNDS' -- set movie range");
  sep_add_doc_line("    'Navigate' KEY 'Ctrl' + 'u' -- undo");
  sep_add_doc_line("    'Navigate' KEY 'Ctrl' + 'r' -- redo"); 
  sep_add_doc_line("    'Navigate' KEY 'Ctrl' + 'p' -- pause");
  sep_add_doc_line("");

  sep_add_doc_line("COLOR FUNCTIONS: set color, contrast, and transparency");
  sep_add_doc_line("    'Color' 'Gray' -- grayscale");
  sep_add_doc_line("    'Color' 'Straw' -- blue and yellow");
  sep_add_doc_line("    'Color' 'Flag' -- red, white and blue");
  sep_add_doc_line("    'Color' 'Tiger' -- red, white and black");
  sep_add_doc_line("    'Color' 'Blue' -- blue and white");
  sep_add_doc_line("    'Color' 'Rainbow' -- multi-colored");
  sep_add_doc_line("    'Color' 'AVO' -- amplitude variation with offset");
  sep_add_doc_line("    'Color' 'Veldata' -- velocity analysis");
  sep_add_doc_line("    'Color' 'Overlay' <color-list> -- overlay lines and text");
  sep_add_doc_line("    'Color' 'Mark' <color-list> -- pick color");
  sep_add_doc_line("    'Color' 'Background' <color-list> -- screen background color");
  sep_add_doc_line("    'Color' 'Flip Polarity' -- flips data color");
  sep_add_doc_line("    'Color' SLIDER 'CONTRAST' -- shift color table skew");
  sep_add_doc_line("    'Color' SLIDER 'CENTER' -- shift color table zero point");
  sep_add_doc_line("    'Color' BUTTON 'RESET' -- reset initial contrast");
  sep_add_doc_line("    'Color' BUTTON 'STEP' -- increment contrast");
  sep_add_doc_line("");
  
  sep_add_doc_line("PICK FUNCTIONS: set picking behavior");
  sep_add_doc_line("    'Pick' 'Show/Hide Pick -- make picks visible/invisible");
  sep_add_doc_line("    'Pick' 'Change Pick Properties -- launch pick parameters panel");
  sep_add_doc_line("    'Pick' 'Fix Picking' -- fix pick changes");
  sep_add_doc_line("    'Pick' 'Write to File' -- save picks");
  sep_add_doc_line("    'Pick' 'Read from File' -- read picks");
  sep_add_doc_line("    'Pick' 'Increase Range'");
  sep_add_doc_line("    'Pick' 'Decrease Range'");
  sep_add_doc_line("    'Pick' 'Increase Draw Size'");
  sep_add_doc_line("    'Pick' 'Decrease Draw Size'");
  sep_add_doc_line("    'Pick' 'RIGHT MOUSE MAKES PICK'");
  sep_add_doc_line("    'Pick' '+ 'a' KEY ADDS POINT'");
  sep_add_doc_line("    'Pick' '+ 'm' KEY MOVES NEAREST POINT'");
  sep_add_doc_line("    'Pick' '+ 'd' KEY DELETES NEAREST POINT'");
  sep_add_doc_line("    'Pick' '+ 'q' or '?' KEY INQUIRES NEAREST POINT'");
  sep_add_doc_line("    'Pick' '+ 's' KEY SELECTS SMOOTH REGION'");
  sep_add_doc_line("");

  sep_add_doc_line("EDIT FUNCTIONS: edit grid sub-volume");
  sep_add_doc_line("    'Edit' 'Undo Blob Fill'");
  sep_add_doc_line("    'Edit' 'Interpolate Current Cube Edge Values Across Cube'");
  sep_add_doc_line("    'Edit' 'Undo Cube Edge Interpolation'");
  sep_add_doc_line("    'Edit' ''s' KEY + RIGHT MOUSE DRAG PICKS SUBVOLUME'");
  sep_add_doc_line("    'Edit' 'SET SMOOTH VALUE FROM COLORBAR'");
  sep_add_doc_line("");

  sep_add_doc_line("PATH VIEW FUNCTIONS: display path through cube");
  sep_add_doc_line("    'PathView' 'Path View On/Off' -- toggle path projection on/off");
  sep_add_doc_line("    'PathView' 'Path Start' -- go to start of path");
  sep_add_doc_line("    'PathView' 'Path Middle' -- go to middle of path");
  sep_add_doc_line("    'PathView' 'Path End' -- go to end of path");
  sep_add_doc_line("    'PathView' 'Animate Path Forward' -- play movie along path forward");
  sep_add_doc_line("    'PathView' 'Animate Path Backward' -- play movie along path backward");
  sep_add_doc_line("    'PathView' 'Pause Animation' -- stop movie");
  sep_add_doc_line("    'PathView' KEY '+' -- moves forward on path");
  sep_add_doc_line("    'PathView' KEY '-' -- moves backward on path"); 
  sep_add_doc_line("    'PathView' KEY 'Ctrl' + 'p' -- pause");
  sep_add_doc_line("");

  /**
  sep_add_doc_line("SECTION FUNCTIONS: plot various sections through the data");
  sep_add_doc_line("    'Section' 'On Screen Wiggle Plot'");
  sep_add_doc_line("    'Section' 'On Screen Contour Plot'");
  sep_add_doc_line("    'Section' 'On Screen Greyscale Plot'");
  sep_add_doc_line("    'Section' 'Output View'");
  sep_add_doc_line("    'Section' 'Cubeplot'");
  sep_add_doc_line("    'Section' 'Print Wiggle Plot'");
  sep_add_doc_line("    'Section' 'Print Contour Plot'");
  sep_add_doc_line("    'Section' 'Save Section in File ...'");
  sep_add_doc_line("    'Section' 'Save Profile in File ...'");
  sep_add_doc_line("    'Section' 'CROSS-HAIRS SET PLANES & PROFILES'");
  sep_add_doc_line("");
  **/

  sep_add_doc_line("VELOCITY VIEW FUNCTIONS: merge physical and velocity cubes");
  sep_add_doc_line("    'VelView' 'Separate Cubes' -- distinct cubes");
  sep_add_doc_line("    'VelView' 'Merge by Adjusting Intensities' -- merged cube in place of physical");
  sep_add_doc_line("    'VelView' 'Merge by Copying Differences' -- merged cube in place of physical");
  sep_add_doc_line("    'VelView' SLIDER 'VEL VIEW' -- left=physical, right=velocity, middle=merge");
  sep_add_doc_line("");

  sep_add_doc_line("STATUS FUNCTIONS: print parameters and state variables");
  sep_add_doc_line("    'Status' 'Dataset' -- dataset parameters");
  sep_add_doc_line("    'Status' 'Data Values' -- data value parameters");
  sep_add_doc_line("    'Status' 'Data Axis0' -- value/color axis");
  sep_add_doc_line("    'Status' 'Data Axis1' -- fast axis, usually time");
  sep_add_doc_line("    'Status' 'Data Axis2' -- second data axis, usually CDP");
  sep_add_doc_line("    'Status' 'Data Axis3' -- slow axis, usually section");
  sep_add_doc_line("    'Status' 'Data Axis4' -- slow axis, usually offset");
  sep_add_doc_line("    'Status' 'Data Axis5' -- slow axis, unused");
  sep_add_doc_line("    'Status' 'View' -- view parameters");
  sep_add_doc_line("    'Status' 'Down Axis' -- view down axis parameters");
  sep_add_doc_line("    'Status' 'Across Axis' -- view across axis parameters");
  sep_add_doc_line("    'Status' 'Deep Axis' -- view deep axis parameters");
  sep_add_doc_line("    'Status' '4D Axis' -- view extra axis parameters");
  sep_add_doc_line("    'Status' '5D Axis' -- view extra axis parameters");
  sep_add_doc_line("    'Status' 'Color Axis' -- colorbar axis parameters");
  sep_add_doc_line("    'Status' 'Color' -- color and contrast parameters");
  sep_add_doc_line("    'Status' 'Render' -- rendering parameters");
  sep_add_doc_line("    'Status' 'Graphics' -- draw screen parameters");
  sep_add_doc_line("    'Status' 'Mouse Buttons' -- mouse button functions");
  sep_add_doc_line("    'Status' 'Navigate' -- movie parameters");
  sep_add_doc_line("    'Status' 'Pick' -- pick parameters");
  sep_add_doc_line("    'Status' 'Pick List' -- current pick line parameters");
  sep_add_doc_line("    'Status' 'Edit' -- current sub-volume edit parameters");
  sep_add_doc_line("    'Status' 'Frame List' -- list of screen frames (stdout)");
  sep_add_doc_line("");

  sep_add_doc_line("HELP FUNCTIONS: print self documentation from various places");
  sep_add_doc_line("    'Help' 'Data Parameters'");
  sep_add_doc_line("    'Help' 'Pick Parameters'");
  sep_add_doc_line("    'Help' 'Display Parameters'");
  sep_add_doc_line("    'Help' 'Multiple View Parameters'");
  sep_add_doc_line("    'Help' 'Velocity Analysis Parameters'");
  sep_add_doc_line("    'Help' 'File Formats'");
  sep_add_doc_line("    'Help' 'Windows'");
  sep_add_doc_line("    'Help' 'Navigation Mouse Usage'");
  sep_add_doc_line("    'Help' 'Picking Mouse Usage'");
  sep_add_doc_line("    'Help' 'Annotate Mouse Usage'");
  sep_add_doc_line("    'Help' 'Other Mouse Usage'");
  sep_add_doc_line("    'Help' 'Main Functions'");
  sep_add_doc_line("    'Help' 'View Functions'");
  sep_add_doc_line("    'Help' 'Orient Functions'");
  sep_add_doc_line("    'Help' 'Size Functions'");
  sep_add_doc_line("    'Help' 'Navigate Functions'");
  sep_add_doc_line("    'Help' 'Color Functions'");
  sep_add_doc_line("    'Help' 'Pick Functions'");
  sep_add_doc_line("    'Help' 'Edit Functions'");
  sep_add_doc_line("    'Help', Path View Functions'");
  sep_add_doc_line("    'Help', Velocity View Functions'");
  sep_add_doc_line("    'Help' 'Status Functions'");
  sep_add_doc_line("    'Help' 'Help Functions'");
  sep_add_doc_line("    'Help' 'Examples'");
  sep_add_doc_line("");

  sep_add_doc_line("NOTES");
  sep_add_doc_line("    Parameters:");
  sep_add_doc_line("       style, wide, hite, movie, shape, show_picks, across,");
  sep_add_doc_line("       down, dacross, rate, fence, origin, order.");
  sep_add_doc_line("");
  sep_add_doc_line("    Multiple views specification:");
  sep_add_doc_line("       1st view: <parameter>");
  sep_add_doc_line("       2nd view: <parameter>1");
  sep_add_doc_line("       3rd view: <parameter>2");
  sep_add_doc_line("       ...");
  sep_add_doc_line("");

  sep_add_doc_line("CATEGORY:");
  sep_add_doc_line("    interact");
  sep_add_doc_line("");

  doc(SOURCE);
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
#if defined (HAVE_MOTIF)
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
  fprintf(stderr,"Neither motif or athena was speciefied \n");
  
}
#endif

