/*
axis object definition

Three axes define a cube dataset
*/

/* Axis object */
typedef struct {
	string	label;	/* name */
	int	size;	/* length */
	float	first;	/* first value */
	float	delta;	/* sampling rate */
	float	zoom;	/* relative zoom */
	int	dir;	/* direction */
	int	stride;	/* array stride */
	int	prec;	/* slider precision */
	int	scale;	/* slider scaling: 10**scale */
	float	*values;	/* tabulated values */
	string	*script;	/* label for each element */
	} *Axis;

/* typed returns */
extern Axis AxisInit (/*iaxis,step*/);
extern Axis AxisInit2 (/*iaxis,step*/);
extern char* AxisLabel (/*axis*/);
extern float AxisValue (/*axis,index*/);
extern char* AxisScript (/*axis,index*/);
extern float AxisFirst (/*axis*/);
extern float AxisLast (/*axis*/);
extern float AxisDelta (/*axis*/);
extern float AxisZoom (/*axis*/);
extern float* AxisValues (/*axis*/);
