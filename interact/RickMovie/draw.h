/*
draw object definition

Graphics system dependent information
XView/Windows here
*/

/* constants */
#define	OVERLAY_COLOR	1
#define	ERASE_COLOR	0
#define	IMAGE_MASK	254
#define	OVERLAY_MASK	1
#define	CLEAR_MASK	255
#define	NXCOLOR		256

/* Draw object */
typedef struct {
/* mostly XWindows variables */
	Display	*display;	/* XWindows */
	int	screen;	/* XWindows */
	Visual	*visual;
	Colormap	cmap;	/* color map */
	GC	gc;	/* XWindows */
	XImage	*image;	/* XWindows */
	XID	window;	/* XWindows */
	XFontStruct	*font;	/* XWindows */
	Cursor	watch;	/* watch cursor */
	Pixmap	*pms;	/* list of pixmaps */
	int	h0, v0, nh, nv; /* pixmap coordinates */
	int	npmax;	/* number of pixmaps */
	int	npm;	/* number of pixmaps allocated */
	int	wide, hite;	/* previouse window size */
	int	ncolor;	/* number of continguous colors allocated */
	int	base; /* color table bias */
	XColor	color[NXCOLOR];	/* color table */
	 XVisualInfo vinfo;
	unsigned long	mask;	/* plane mask */
	} *Draw;
