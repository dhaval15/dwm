/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 4;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 22;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int focusonwheel       = 0;
static const char dmenufont[]       = "monospace:size=10";
static const char font[]            = "Icons 10";
static const char col_unfg[]        = "#554433";
static const char col_unbg[]        = "#231F20";
static const char col_unborder[]    = "#231F20";
static const char col_gray1[]       = "#231F20";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#FFCC99";
static const char col_gray4[]       = "#231F20";
static const char col_cyan[]        = "#FFCC99";
static const char *colors[][3]      = {
	/*               fg         bg         border        */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2     },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan      },
	[SchemeUn]   = { col_unfg,  col_unbg,  col_unborder  },
};

static const char *const autostart[] = {
	"nitrogen","--restore",NULL,
	"dwmblocks",NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", ""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	 /*                                                           switch  is                  no
	 * class           instance     title             tag mask    totag   floating  term      swallow  monitor*/
	// Design : 7
	{ "Gimp",          NULL,        NULL,             1 << 6,     1,      0,        0,        1,       -1 },
	{ "Blender",       NULL,        NULL,             1 << 6,     1,      0,        0,        1,       -1 },
	// Media : 6
	{ "vlc",           NULL,	NULL,		  1 << 5,     1,      0,	0,        1,	   -1 },
	{ "Popcorn-Time",  NULL,	NULL,		  1 << 5,     1,      0,	0,        1,	   -1 },
	// Writing : 5
	{ "Alacritty",     NULL,        "Feather",        1 << 4,     1,      0,        0,        1,       -1 },
	{ "Typora",   	   NULL,	NULL,             1 << 4,     1,      0,        0,        1,       -1 },
	// Files : 4
	{ "Nemo",     	   NULL,        NULL,             1 << 3,     1,      0,        0,        1,       -1 },
	// Coding : 3
	{ "Emacs",     	   NULL,        NULL,             1 << 2,     1,      0,        0,        1,       -1 },
	{ "Alacritty",     NULL,        "HashCode",       1 << 2,     1,      0,        0,        1,       -1 },
	// Web : 2
	{ "firefox",       NULL,        NULL,             1 << 1,     1,      0,        0,        1,       -1 },
	{ "Chromium",      NULL,        NULL,             1 << 1,     1,      0,        0,        1,       -1 },
	// Misc : Any
	{ "Alacritty",     NULL,        "Term",           0,          1,      0,        1, 	  1,	   -1 },
	{ NULL,            NULL,        "Event Tester",   0,          1,      0,        0,        1,       -1 },
	// Terminal : 1
	{ "Alacritty",     NULL,        NULL,             1 << 0,     1,      0,        1, 	  1,	   -1 },
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "TILE",      tile },   
	{ "MAX",       monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *exitcmd[]         = { "rofi_exit", NULL };
static const char *dmenucmd[]        = { "rofi", "-show", "drun", "-theme", "apps", NULL };
static const char *wificmd[]         = { "networkmanager_dmenu", "-theme", "wifi", NULL };
static const char *termcmd[]         = { "alacritty", NULL };
static const char *instanttermcmd[]  = { "alacritty", "-t", "Term", NULL };
static const char *briupcmd[]        = { "dwm_brightness_up", NULL };
static const char *bridowncmd[]      = { "dwm_brightness_down", NULL };
static const char *volupcmd[]        = { "dwm_volume_up", NULL };
static const char *voldowncmd[]      = { "dwm_volume_down", NULL };
static const char *voltogglecmd[]    = { "dwm_volume_toggle", NULL };
static const char *openproject[]     = { "rofi_projects", NULL };
static const char *dmenucalc[]       = { "dmenu_calc", NULL };

static Key keys[] = {
	/* modifier                     key                 function            argument */
	{ 0,                            XK_F1,              spawn,              {.v = voltogglecmd } },
	{ 0,                            XK_F2,              spawn,              {.v = voldowncmd } },
	{ 0,                            XK_F3,              spawn,              {.v = volupcmd } },
	{ 0,                            XK_F11,             spawn,              {.v = bridowncmd } },
	{ 0,                            XK_F12,             spawn,              {.v = briupcmd } },
	{ MODKEY,                       XK_space,           spawn,              {.v = dmenucmd } },
	{ MODKEY,                       XK_w,               spawn,              {.v = wificmd } },
	{ MODKEY,                       XK_quoteright,      spawn,              {.v = dmenucalc } },
	{ MODKEY,                       XK_semicolon,       spawn,              {.v = openproject } },
	{ MODKEY,                       XK_Escape,          spawn,              {.v = exitcmd } },
	{ MODKEY,                       XK_Return,          spawn,              {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return,          spawn,              {.v = instanttermcmd } },
	{ MODKEY,                       XK_b,               togglebar,          {0} },
	{ MODKEY,                       XK_Right,           focusstack,         {.i = +1 } },
	{ MODKEY,                       XK_Left,            focusstack,         {.i = -1 } },
	{ MODKEY,                       XK_j,               incnmaster,         {.i = +1 } },
	{ MODKEY,                       XK_k,               incnmaster,         {.i = -1 } },
	{ MODKEY,                       XK_h,               setmfact,           {.f = -0.05} },
	{ MODKEY,                       XK_l,               setmfact,           {.f = +0.05} },
	{ MODKEY,                       XK_s,               togglesticky,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,             view,               {0} },
	{ MODKEY|ShiftMask,             XK_q,               killclient,         {0} },
	{ MODKEY,                       XK_t,               setlayout,          {.v = &layouts[0]} },
	{ MODKEY,	                XK_m,               setlayout,          {.v = &layouts[1]} },
	{ MODKEY,                       XK_p,               view_adjacent,      {.i = -1} },
	{ MODKEY,                       XK_n,               view_adjacent,      {.i = +1} },
	{ MODKEY,                       XK_f,               togglefullscr,      {0} },
	{ MODKEY,                       XK_d,               togglefloating,     {0} },
	{ MODKEY|ShiftMask,             XK_Down,   	    moveresize,         {.v = "0x 10y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Up,     	    moveresize,         {.v = "0x -10y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Right,  	    moveresize,         {.v = "10x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   	    moveresize,         {.v = "-10x 0y 0w 0h" } },
	{ MODKEY|ControlMask,           XK_Down,   	    moveresize,         {.v = "0x 0y 0w 10h" } },
	{ MODKEY|ControlMask,           XK_Up,     	    moveresize,         {.v = "0x 0y 0w -10h" } },
	{ MODKEY|ControlMask,           XK_Right,  	    moveresize,         {.v = "0x 0y 10w 0h" } },
	{ MODKEY|ControlMask,           XK_Left,   	    moveresize,         {.v = "0x 0y -10w 0h" } },
	{ MODKEY|ControlMask,           XK_period,   	    boundresize,        {.i = 10 } },
	{ MODKEY|ControlMask,           XK_comma,     	    boundresize,        {.i = -10} },
	{ MODKEY,                       XK_0,               view,               {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,               tag,                {.ui = ~0 } },
	//{ MODKEY,                       XK_comma,           focusmon,           {.i = -1 } },
	//{ MODKEY,                       XK_period,          focusmon,           {.i = +1 } },
	//{ MODKEY|ShiftMask,             XK_comma,           tagmon,             {.i = -1 } },
	//{ MODKEY|ShiftMask,             XK_period,          tagmon,             {.i = +1 } },
	{ MODKEY,                       XK_minus,           setgaps,            {.i = -1 } },
	{ MODKEY,                       XK_equal,           setgaps,            {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,           setgaps,            {.i = 0  } },
	TAGKEYS(                        XK_1,                                   0)
	TAGKEYS(                        XK_2,                                   1)
	TAGKEYS(                        XK_3,                                   2)
	TAGKEYS(                        XK_4,                                   3)
	TAGKEYS(                        XK_5,                                   4)
	TAGKEYS(                        XK_6,                                   5)
	TAGKEYS(                        XK_7,                                   6)
	{ MODKEY|ShiftMask,             XK_c,               quit,               {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

