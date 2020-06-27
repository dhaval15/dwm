/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 0;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 1;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const int focusonwheel       = 0;
static const char font[]            = "Icons 10";
static const char gruv_back[]       = "#231F20";
static const char gruv_text1[]      = "#554433";
static const char gruv_text2[]      = "#BA8866";
static const char gruv_text3[]      = "#FFCC99";
static const char *colors[][3]      = {
	/*               fg          bg          border       */
	[SchemeNorm] = { gruv_text2, gruv_back,  gruv_text1   },
	[SchemeSel]  = { gruv_back,  gruv_text3, gruv_text3   },
	[SchemeEmp]  = { gruv_text1, gruv_back,  gruv_back    },
	[SchemeLay]  = { gruv_back,  gruv_text2, gruv_back    },
};

static const char *const autostart[] = {
	"alacritty", "-e", "tmux", "new-session", "-s", "Terminal",NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "" };

static const Rule rules[] = {
};

/* layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "TILE",      tile },   
};

/* key definitions */
#define MODKEY Mod4Mask
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */

static const char *exitcmd[]         = { "rofi_exit", NULL };
static const char *wificmd[]         = { "networkmanager_dmenu", "-theme", "wifi", NULL };
static const char *briupcmd[]        = { "dwm_brightness_up", NULL };
static const char *bridowncmd[]      = { "dwm_brightness_down", NULL };
static const char *volupcmd[]        = { "dwm_volume_up", NULL };
static const char *voldowncmd[]      = { "dwm_volume_down", NULL };
static const char *voltogglecmd[]    = { "dwm_volume_toggle", NULL };
static const char *dmenucalc[]       = { "dmenu_calc", NULL };

static Key keys[] = {
	/* modifier                     key                 function            argument */
	{ 0,                            XK_F1,              spawn,              {.v = voltogglecmd } },
	{ 0,                            XK_F2,              spawn,              {.v = voldowncmd } },
	{ 0,                            XK_F3,              spawn,              {.v = volupcmd } },
	{ 0,                            XK_F11,             spawn,              {.v = bridowncmd } },
	{ 0,                            XK_F12,             spawn,              {.v = briupcmd } },
	{ MODKEY,                       XK_w,               spawn,              {.v = wificmd } },
	{ MODKEY,                       XK_quoteright,      spawn,              {.v = dmenucalc } },
	{ MODKEY,                       XK_Escape,          spawn,              {.v = exitcmd } },
	{ MODKEY|ShiftMask,             XK_c,               quit,               {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
};

