/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "SauceCodePro Nerd Font:size=10" };
static const char dmenufont[]       = "Inconsolata-Bold:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#282A36";
static const char col_cyan2[]       = "#82983B";
static const char col_black[]       = "#000000";
static const char col_red[]         = "#ff0000";
static const char col_yellow[]      = "#ffff00";
static const char col_white[]       = "#ffffff";
static const char *colors[][5]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = 	{ col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = 	{ col_gray4, col_cyan,  col_cyan  },
	[SchemeWarn] = 	{ col_cyan2, col_gray1, col_gray2 },
	[SchemeUrgent]=	{ col_white, col_red,    col_red },
};

/* tagging */
static const char *tags[] = { "", "", "", "4", "5", "6", "ﭮ", "", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "qutebrowser",  NULL,       NULL,   1 << 1,       0,           -1 },
	{ "St",		"st",	 "neomutt",   1 << 2,	    0,		 -1 },
	{ "discord", "discord",	 NULL,  1 << 6,    0,	 -1 },
	{ "Spotify",     NULL,       NULL,        1 << 7,         0,     -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
};

/* key definitions */
#define XF86AudioMute			0x1008ff12
#define XF86AudioLowerVolume		0x1008ff11
#define XF86AudioRaiseVolume		0x1008ff13
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
	{ MODKEY|Mod4Mask, 		KEY,      spawn,       {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *cmd_term[]  = { "st", NULL };
static const char *cmd_browser[]  = { "qutebrowser", NULL };
static const char *cmd_fileman[]  = { "st", "-e", "ranger", NULL };
static const char *cmd_mutt[]  = { "st", "-e", "neomutt", NULL };
static const char *cmd_lock[]  = { "i3lock-fancy", "-t", "", NULL };
static const char *cmd_passmenu[] = { "passmenu", NULL };
static const char *cmd_manmenu[] = { "manmenu", NULL };
static const char *cmd_wikimenu[] = { "archhelp", NULL };
static const char *cmd_shutdown[] = { "shutdown.sh", NULL };
static const char *cmd_usbmenu[] = { "usbmenu", NULL };
static const char *cmd_notesmenu[] = {"notesmenu", NULL };
static const char *cmd_soundup[]  = { "amixer", "-q", "sset", "Master", "5%+", NULL };
static const char *cmd_sounddown[]  = { "amixer", "-q", "sset", "Master", "5%-", NULL };
static const char *cmd_soundtoggle[]  = { "amixer", "-q", "sset", "Master", "toggle", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ Mod4Mask,                     XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = cmd_term } },
	{ Mod4Mask,              	XK_l,	   spawn,          {.v = cmd_lock } },
	{ Mod4Mask,              	XK_1,	   spawn,          {.v = cmd_browser } },
	{ Mod4Mask,              	XK_2,	   spawn,          {.v = cmd_fileman } },
	{ Mod4Mask,              	XK_3,	   spawn,          {.v = cmd_mutt } },
	{ Mod4Mask,			XK_p,	   spawn,	   {.v = cmd_passmenu} },
	{ Mod4Mask,			XK_m,	   spawn,	   {.v = cmd_manmenu} },
	{ Mod4Mask,			XK_n,	   spawn,	   {.v = cmd_notesmenu} },
	{ Mod4Mask,			XK_h,	   spawn,	   {.v = cmd_wikimenu} },
	{ Mod4Mask,			XK_u,	   spawn,	   {.v = cmd_usbmenu} },
	{ Mod4Mask,			XK_x,	   spawn,	   {.v = cmd_shutdown} },
	{ 0,		XF86AudioMute,	  	   spawn,	   {.v = cmd_soundtoggle} },
	{ 0,            XF86AudioRaiseVolume,      spawn,          {.v = cmd_soundup } },
	{ 0,            XF86AudioLowerVolume,      spawn,          {.v = cmd_sounddown } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_u,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_o,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY|ControlMask,           XK_j,	   resizeheight,   {.i = +16  } },
	{ MODKEY|ControlMask,           XK_k,	   resizeheight,   {.i = -16  } },
	{ MODKEY|ControlMask,           XK_h,	   resizewidth,    {.i = -16  } },
	{ MODKEY|ControlMask,           XK_l,	   resizewidth,    {.i = +16  } },
	{ MODKEY|ControlMask|ShiftMask, XK_j,	   resizey,	   {.i = +16  } },
	{ MODKEY|ControlMask|ShiftMask, XK_k,	   resizey,	   {.i = -16  } },
	{ MODKEY|ControlMask|ShiftMask, XK_h,	   resizex,        {.i = -16  } },
	{ MODKEY|ControlMask|ShiftMask, XK_l,	   resizex,        {.i = +16  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = cmd_term } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

